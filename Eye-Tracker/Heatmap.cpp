#include "HeatmapUtils.h"
#include "Heatmap.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

// Options
int g_kernel_size = 75;
float g_fade_time = 2.0;
float g_kernel_intensity = 0.1;
float g_base_intensity = 0.1;
float g_max_transparency = 0.6;
bool g_linear_kernel = false;
bool g_realtime_playback = true;
bool g_print_progress = false;
bool g_show_video = true;
bool g_out_video = false;
string g_out_file;
string g_out_four_cc = "MJPG";

// Required arguments
string g_in_video;
string g_data_file;

Mat g_heatmap;	
Mat g_kernel;
Mat g_ones;
Mat g_zeros;
Mat g_fade_mat;

vector<DataPoint> g_data;

// Following are in HSV format
Vec3b g_heat_color1 = Vec3b(0, 255, 255);	// Red
Vec3b g_heat_color2 = Vec3b(170, 255, 255); // Blue

//============================================================================
// heat_point
//============================================================================
/* Initializes heatmap. */
void heatmap_init(Mat& frame, int fps)
{
	g_heatmap = Mat::zeros(frame.rows, frame.cols, CV_32FC1);
	g_ones = Mat::ones(frame.rows, frame.cols, CV_32F);
	g_zeros = Mat::zeros(frame.rows, frame.cols, CV_32F);
	g_fade_mat = Mat::ones(frame.rows, frame.cols, CV_32F);
	
	// Determine how much to fade the heatmap values by each frame
	g_fade_mat.setTo((1.0 / fps) / g_fade_time);
}

//============================================================================
// heat_point
//============================================================================
/* Adds point to g_heatmap */
void heat_point(int x, int y)
{
	// Make sure the coordinates are in bounds
	if (x < 0 || y < 0 || x >= g_heatmap.cols || y >= g_heatmap.rows)
	{
		return;
	}

	// Only update a small portion of the matrix
	const int g_kernel_half = g_kernel_size / 2;
	const int fixed_x = x - g_kernel_half;
	const int fixed_y = y - g_kernel_half;
	const int roi_l = max(fixed_x, 0);
	const int roi_t = max(fixed_y, 0);
	const int roi_w = min(fixed_x + g_kernel_size, g_heatmap.cols) - roi_l;
	const int roi_h = min(fixed_y + g_kernel_size, g_heatmap.rows) - roi_t;

	Mat roi(g_heatmap(Rect(roi_l, roi_t, roi_w, roi_h)));

	const int groi_l = roi_l - fixed_x;
	const int groi_t = roi_t - fixed_y;
	const int groi_w = roi_w;
	const int groi_h = roi_h;

	Mat roi_gauss(g_kernel(Rect(groi_l, groi_t, groi_w, groi_h)));
	roi += roi_gauss;
}

//============================================================================
// decrease_heatmap
//============================================================================
/* Fades the entire heatmap by g_fade_mat amount. */
void decrease_heatmap()
{
	// Fade some of the values in the matrix	
	g_heatmap -= g_fade_mat;
	g_heatmap = max(g_zeros, g_heatmap);
}

//============================================================================
// overlay_heatmap
//============================================================================
/* Draws the heatmap on top of a frame. The frame must be the same size as	*/
/* the heatmap.																*/
void overlay_heatmap(Mat& frame)
{
	// Make sure all values are capped at one
	g_heatmap = min(g_ones, g_heatmap);

	Mat temp_map;
	blur(g_heatmap, temp_map, Size(15, 15));

	for (int r = 0; r < frame.rows; ++r)
	{
		Vec3b* f_ptr = frame.ptr<Vec3b>(r);
		float* h_ptr = temp_map.ptr<float>(r);
		for (int c = 0; c < frame.cols; ++c)
		{
			const float heat_mix = h_ptr[c];
			if (heat_mix > 0.0)
			{
				// in BGR
				const Vec3b i_color = f_ptr[c];

				const Vec3b heat_color = 
					hsv_to_bgr(interpolate_hsv(g_heat_color2, g_heat_color1, heat_mix));

				const float heat_mix2 = std::min(heat_mix, g_max_transparency);

				const Vec3b final_color = interpolate(i_color, heat_color, heat_mix2);
				
				f_ptr[c] = final_color;
			}
		}
	}
}

//============================================================================
// create_kernel
//============================================================================
/* Create the heatmap kernel. This is applied when heat_point() is called. */
void create_kernel()
{
	if (g_linear_kernel)
	{
		// Linear kernel
		const float max_val = 1.0 * g_base_intensity;
		const float min_val = 0.0;
		const float interval = max_val - min_val;

		const int center = g_kernel_size / 2 + 1;
		const float radius = g_kernel_size / 2;

		g_kernel = Mat::zeros(g_kernel_size, g_kernel_size, CV_32F);
		for (int r = 0; r < g_kernel_size; ++r)
		{
			float* ptr = g_kernel.ptr<float>(r);
			for (int c = 0; c < g_kernel_size; ++c)
			{
				// Calculate the distance from the center	
				const float diff_x = static_cast<float>(abs(r - center));
				const float diff_y = static_cast<float>(abs(c - center));
				const float length = sqrt(diff_x*diff_x + diff_y*diff_y);
				if (length <= radius)
				{
					const float b = 1.0 - (length / radius);
					const float val = b*interval + min_val;
					ptr[c] = val;
				}
			}
		}
	}
	else
	{
		// Gaussian kernel
		Mat coeffs = getGaussianKernel(g_kernel_size, 0.0, CV_32F)*150*g_base_intensity;
		g_kernel = coeffs * coeffs.t();
	}
}