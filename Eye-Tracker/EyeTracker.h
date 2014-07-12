#ifndef EYE_TRACKER_H
#define EYE_TRACKER_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <list>
#include <QDebug>
#include "Calibrator.h"

using namespace std;
using namespace cv;
using namespace Nsk;

#define NPOINTS 36
#define H_THRESHOLD 80
#define L_THRESHOLD 0
#define PI (3.141592653589793)
#define WHITE 255
#define BLACK 0
#define REFLECTION 100
#define WIDTH_LIMIT 200
#define HEIGHT_LIMIT 150
#define CENTER_LIST_SIZE 10

#define PUPIL_DETECTION_WINDOW_NAME "pupil detection"
#define MERGE_IMAGE_WINDOW_NAME "mergeImage"
#define SCENE_CAMERA_WINDOW_NAME "scene camera"

class EyeTracker
{
public:
	EyeTracker();
	EyeTracker(int eyeCam, int sceneCam);
	bool isOpened();
	void setEyeCamIndex(int eyeCamIndex);
	void setFrontCamIndex(int frontCamIndex);
	void initialize();
	CvPoint getFocusPoint();
	IplImage *getSceneImage();
	IplImage *getEyeImage();
	void showWindow();
	void showWindows();
	void showMergeImage();
	void hideWindow();
	Point2f whereIsEyeNow();
	void startTracker();
	Point2f doTrack();
	bool isSetCameras();
	CvPoint getCenter() const;
	IplImage * captureSceneFrame();
	void releaseGraySceneImage();
	void captureEyeFrame();
	void releaseGrayEyeImage();
	void calculateScenePoint();
	CvSeq* findSquares();
	void drawTrasholds();
	Point2f detectPupil();
	void noktadanAcil();
	void mergeImage();
	void addToList(const CvPoint &p);
	double angle(CvPoint* pt1, CvPoint* pt2, CvPoint* pt0);
	void drawSquares(CvSeq* squares);
	double *getSceneRate();
	void doHoughTransform();
	~EyeTracker();

	/* New added by by nsk. */
	Calibrator *getCalibrator() { return calibrator; }
	void calibrateLeftTopCorner();
	void calibrateRightTopCorner();
	void calibrateLeftDownCorner();
	void calibrateRightDownCorner();
	void calibrateLeftTopCorner(Point2f& eyePoint);
	void calibrateRightTopCorner(Point2f& eyePoint);
	void calibrateLeftDownCorner(Point2f& eyePoint);
	void calibrateRightDownCorner(Point2f& eyePoint);
	Point2f getEyePointOnWindow() { return calibrator->convertToWindowPoint(whereIsEyeNow()); }
	void calibrate();

	/*##############################################################################*/
	/*						Corneal Reflection Remover Code							*/
	/*##############################################################################*/
	void removeReflection();
	void remove_corneal_reflection( int sx, int sy, int window_size, int biggest_crr, int &crx, int &cry );
	void locate_corneal_reflection( int sx, int sy, int window_size, int biggest_crar, int &crx, int &cry, int &crar);
	int fit_circle_radius_to_corneal_reflection(int cx, int cy, int crar, int biggest_crar, double *sin_array, double *cos_array, int array_len);
	void interpolate_corneal_reflection( int cx, int cy , double *sin_array, double *cos_array, int array_len);

private:
	Calibrator *calibrator;
	int eyeCamIndex;
	int frontCamIndex;
	IplImage *sceneImagePts;			/* Holds picture of scene */
	IplImage *graySceneImagePts;
	IplImage *originalEyeImagePts;		/* Holds unchanged picture of eye */
	IplImage *grayEyeImagePts;
	CvMat *calibMatrix;
	CvCapture *eyeCamera;
	CvCapture *sceneCamera;
	vector<CvPoint> featurePoints;
	CvPoint scenePoint;
	vector<CvPoint> sceneCorner;		/* Bilgisayar ekranı köşeleri */
	double sceneRate[2];
	CvPoint prev_center;
	bool firstDetect;
	list<CvPoint> centerList;
	CvPoint aver_center;
	CvMat *homography;
	CvMat *hedefp; 						/* scenePoint bulmak icin CvMat */
	CvMat *centerMatrix;
	IplImage* threshold_image;
	int cr_window_size;	
	CvPoint corneal_reflection;
	int corneal_reflection_r; 
	int highThreshold;
	int lowThreshold;
	CvMemStorage *squareStorage;		/* Ekran bulmak icin storage */
	int squareThreshold;
	IplImage *mergedImage;
};

#endif