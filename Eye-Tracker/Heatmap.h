#ifndef HEATMAP_H
#define HEATMAP_H

#include "HeatmapUtils.h"

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

//============================================================================
// heat_point
//============================================================================
/* Initializes heatmap. */
void heatmap_init(Mat& frame, int fps);

//============================================================================
// heat_point
//============================================================================
/* Adds point to g_heatmap */
void heat_point(int x, int y);

//============================================================================
// decrease_heatmap
//============================================================================
/* Fades the entire heatmap by g_fade_mat amount. */
void decrease_heatmap();

//============================================================================
// overlay_heatmap
//============================================================================
/* Draws the heatmap on top of a frame. The frame must be the same size as	*/
/* the heatmap.																*/
void overlay_heatmap(Mat& frame);

//============================================================================
// create_kernel
//============================================================================
/* Create the heatmap kernel. This is applied when heat_point() is called. */
void create_kernel();

#endif