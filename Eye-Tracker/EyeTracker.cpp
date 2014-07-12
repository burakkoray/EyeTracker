/**
  *
  *  http://stackoverflow.com/questions/10533233/opencv-c-obj-c-advanced-square-detection
  *
  */

#include "EyeTracker.h"

EyeTracker::EyeTracker()
{
	calibrator = new Calibrator();
	eyeCamera = NULL; 
	sceneCamera = NULL;

	originalEyeImagePts = NULL;
	sceneImagePts = NULL;	
	graySceneImagePts = NULL;
	grayEyeImagePts = NULL;
	threshold_image = NULL;

	calibMatrix = NULL;
	homography = NULL;
	hedefp = NULL;
	centerMatrix = NULL;
}

EyeTracker::EyeTracker(int eyeCamIndex, int frontCamIndex) 
{
	setEyeCamIndex(eyeCamIndex);
	setFrontCamIndex(frontCamIndex);
	initialize();
}

bool EyeTracker::isOpened()
{
	return eyeCamera != NULL && sceneCamera != NULL;
}

void EyeTracker::setEyeCamIndex(int eyeCamIndex)
{
	this->eyeCamIndex = eyeCamIndex;
}

void EyeTracker::setFrontCamIndex(int frontCamIndex)
{
	this->frontCamIndex = frontCamIndex;
}

void EyeTracker::initialize()
{
	eyeCamera = NULL;
	sceneCamera = NULL;
	
	eyeCamera = cvCaptureFromCAM(eyeCamIndex);
    
    #ifndef _WIN32
    cvSetCaptureProperty(eyeCamera,CV_CAP_PROP_FRAME_WIDTH, 320);
    cvSetCaptureProperty(eyeCamera,CV_CAP_PROP_FRAME_HEIGHT, 240);
    #endif

    if( eyeCamera != NULL )
    {
        sceneCamera = cvCaptureFromCAM(frontCamIndex);
        
        #ifndef _WIN32
        cvSetCaptureProperty(sceneCamera,CV_CAP_PROP_FRAME_WIDTH, 320);
        cvSetCaptureProperty(sceneCamera,CV_CAP_PROP_FRAME_HEIGHT, 240);
        #endif

        if( sceneCamera != NULL )
        {
			grayEyeImagePts = NULL;
			graySceneImagePts = NULL;

			prev_center.x = 320;
			prev_center.y = 240;

			firstDetect = false;

			highThreshold = 80;
			lowThreshold = 0;

			corneal_reflection = cvPoint(0,0);
			corneal_reflection_r = 0;
			cr_window_size = 201;

			squareStorage = 0;
			squareThreshold = 50;

			/* Create a memory storage that will contain all the dynamic data */
			squareStorage = cvCreateMemStorage(0);
			//squares = cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), squareStorage );

			homography = cvCreateMat(3, 3, CV_64FC1);
			hedefp = cvCreateMat(3, 1, CV_64FC1);
			centerMatrix = cvCreateMat(3, 1, CV_64FC1);

			hedefp->data.db[0] = 0;
			hedefp->data.db[1] = 0;
			hedefp->data.db[2] = 0;

			mergedImage = cvCreateImage(cvSize(640, 480), 8, 1);

			sceneCorner.resize(4);
			sceneRate[0] = 0;
			sceneRate[1] = 0;
			
		#ifndef WIN32
			system("export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH");
		#endif
		}

		else
		{
			fprintf(stderr, "Scene Camera Not Found on %d\n", frontCamIndex);
		}
	}

	else
	{
		fprintf(stderr, "Eye Camera Not Found on %d\n", eyeCamIndex);
	}
}

EyeTracker::~EyeTracker()
{
	if(originalEyeImagePts != NULL)
		cvReleaseImage(&originalEyeImagePts);
	
	if(sceneImagePts != NULL)
		cvReleaseImage(&sceneImagePts);
	
	if(graySceneImagePts != NULL)
		cvReleaseImage(&graySceneImagePts);
	
	if(grayEyeImagePts != NULL)
		cvReleaseImage(&grayEyeImagePts);
	
	if(threshold_image != NULL)
		cvReleaseImage(&threshold_image);

	if(eyeCamera != NULL)
		cvReleaseCapture(&eyeCamera);
	
	if(sceneCamera != NULL)
		cvReleaseCapture(&sceneCamera);

	if(calibMatrix != NULL)
		cvReleaseMat(&calibMatrix);
	
	if(homography != NULL)
		cvReleaseMat(&homography);
	
	if(hedefp != NULL)
		cvReleaseMat(&hedefp);
	
	if(centerMatrix != NULL)
		cvReleaseMat(&centerMatrix);
}

Point2f EyeTracker::whereIsEyeNow()
{
	captureEyeFrame();

	captureSceneFrame();

	Point2f p = doTrack();

	//qDebug() << "x: " << p.x << " y: " << p.y;
	releaseGrayEyeImage();
	
	releaseGraySceneImage();

	//cvWaitKey(20);

	return p;
}

void EyeTracker::startTracker()
{
	while(true)
	{
		captureEyeFrame();
		captureSceneFrame();

		Point2f p = doTrack();

		//qDebug() << "x: " << p.x << " y: " << p.y;
		
		drawTrasholds();
		drawSquares(findSquares());
		
		cvShowImage(PUPIL_DETECTION_WINDOW_NAME, grayEyeImagePts);

		releaseGrayEyeImage();
		releaseGraySceneImage();

		int k = cvWaitKey(20);
	
		if( k == 27 )
			break;
	/*
		if( k == 'w' || k == 'W' )
			++highThreshold;
	
		else if ( k == 's' || k == 'S' )
			--highThreshold;
	
		else if( k == 'q' || k == 'Q' )
			++squareThreshold;
	
		else if ( k == 'a' || k == 'A' )
			--squareThreshold;*/
	}
}

Point2f EyeTracker::doTrack()
{
	/* Remove the reflection. */
	removeReflection();

	/* Detect the pupil */
	return detectPupil();
}

Point2f EyeTracker::detectPupil()
{
	/* 
	 * Uses cvHoughCircles to find circles on gray eye image. 
	 * Sets prev_center with last circle.
	 */
	doHoughTransform();

	/* Sets featurePoints */
	noktadanAcil();

	CvPoint2D32f p32[NPOINTS];
	CvBox2D box;

	for(size_t i = 0; i < featurePoints.size(); ++i)
	{
		p32[i] = cvPoint2D32f( featurePoints[i].x, featurePoints[i].y );
	}

	cvFitEllipse(p32, NPOINTS, &box);

	cvEllipse(grayEyeImagePts, 
			  cvPoint((int)box.center.x, (int)box.center.y),
			  cvSize((int)(box.size.width/2), (int)(box.size.height/2)),
			  box.angle, 
			  0, 
			  360, 
			  cvScalar(WHITE, 0, 0, 0), 
			  3);

	cout << "x=" << (int)box.center.x << "-y=" << (int) box.center.y << endl;
	
	if(box.size.width < 1)
	{
		firstDetect = false;
	}

	else
	{
		/* Adds point to centerList, sets aver_center to average of centerList */
		addToList(cvPoint( cvRound(box.center.x), cvRound(box.center.y) ) );
		prev_center.x = (int)box.center.x;
		prev_center.y = (int)box.center.y;
	}

	return box.center;
}

void EyeTracker::noktadanAcil()
{
	CvPoint tempPoint;
	double stepAngle = 2 * PI / NPOINTS;
	double angle = 0;
	int radius = 1;

	featurePoints.clear();

	for(int i = 0; i < NPOINTS; ++i)
	{
		while(true)
		{
			tempPoint.x = (int)(prev_center.x + sin( angle ) * radius);
			tempPoint.y = (int)(prev_center.y + cos( angle ) * radius);

			if( tempPoint.x <= 0 || tempPoint.x >= grayEyeImagePts->width ||
				tempPoint.y <= 0 || tempPoint.y >= grayEyeImagePts->height )
			{
				break;
			}

			int intensity = ((uchar *)(grayEyeImagePts->imageData + tempPoint.y * grayEyeImagePts->widthStep))[tempPoint.x];

			static int counter = 0;
			static CvPoint temp;

			if(!(intensity > lowThreshold && intensity < highThreshold))
			{
				++counter;
				
				if(counter == 1)
				{
					temp = tempPoint;
				}

				else if(counter >= 10)
				{
					featurePoints.push_back(temp);
					break;
				}
				
			}

			else
			{
				counter = 0;
			}

			++radius;
		}

		angle += stepAngle;
		radius = 1;
	}
}

void EyeTracker::doHoughTransform()
{
	if(!firstDetect)
	{
		CvMemStorage* storage = cvCreateMemStorage(0);
		
		while(!firstDetect)
		{
			float* p;

			CvSeq* circles;

			circles = cvHoughCircles(grayEyeImagePts, storage, CV_HOUGH_GRADIENT, 
									 3, grayEyeImagePts->width, 50, 100, 30, 60);
			int i;

			static int count = 0;

			for(i = 0; i < circles->total; i++)
			{
				++count;
				p = (float*)cvGetSeqElem(circles, i);
				prev_center.x = (int)p[0];
				prev_center.y = (int)p[1];
				//cout << "merkez bulundu hough " << count << endl;
			}

			firstDetect = true;
		}

		cvReleaseMemStorage(&storage);
	}
}

void EyeTracker::drawTrasholds()
{
	CvFont font;
	char s[20];
	sprintf(s, "HIGH THRESHOLD = %d", highThreshold);
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, 1, 1, 0, 1);
	cvPutText(grayEyeImagePts, s, cvPoint(10, 40), &font, cvScalar(255, 255, 0));

	sprintf(s, "SQUARE THRESHOLD = %d", squareThreshold);
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, 1, 1, 0, 1);
	cvPutText(grayEyeImagePts, s, cvPoint(10, 100), &font, cvScalar(255, 255, 0));
}

IplImage * EyeTracker::captureSceneFrame()
{
	sceneImagePts = cvQueryFrame(sceneCamera);
	graySceneImagePts = cvCreateImage(cvGetSize(sceneImagePts), 8, 1);
	cvCvtColor(sceneImagePts, graySceneImagePts, CV_BGR2GRAY);
	return sceneImagePts;
}

void EyeTracker::releaseGraySceneImage()
{
	cvReleaseImage(&graySceneImagePts);
	graySceneImagePts = NULL;
}

void EyeTracker::captureEyeFrame()
{
	originalEyeImagePts = cvQueryFrame(eyeCamera);
	cvFlip(originalEyeImagePts, originalEyeImagePts, 1);
	grayEyeImagePts = cvCreateImage(cvGetSize(originalEyeImagePts), 8, 1);
	cvCvtColor(originalEyeImagePts, grayEyeImagePts, CV_BGR2GRAY);
}

void EyeTracker::releaseGrayEyeImage()
{
	cvReleaseImage(&grayEyeImagePts);
	grayEyeImagePts = NULL;
}

IplImage *EyeTracker::getEyeImage()
{
	return grayEyeImagePts;
}

CvPoint EyeTracker::getFocusPoint()
{
	return scenePoint;
}

IplImage *EyeTracker::getSceneImage()
{
	return sceneImagePts;
}

CvPoint EyeTracker::getCenter() const
{
	return prev_center;
}

void EyeTracker::calculateScenePoint()
{
	centerMatrix->data.db[0] = aver_center.x;
	centerMatrix->data.db[1] = aver_center.y;
	centerMatrix->data.db[2] = 1;

	cvGEMM(homography, centerMatrix, 1, 0 , 0, hedefp);

	scenePoint = cvPoint(cvRound(hedefp->data.db[0] / hedefp->data.db[2]),
						 cvRound(hedefp->data.db[1] / hedefp->data.db[2]));
}

CvSeq* EyeTracker::findSquares()
{
	CvSeq* contours;
	int i, N = 5;
	CvSize sz = cvSize( sceneImagePts->width, sceneImagePts->height);
	IplImage* gray = cvCreateImage( sz, 8, 1 );
	IplImage* tgray = cvCreateImage( sz, 8, 1 );
	CvSeq* result;
	double s, t;

	CvSeq* squares = cvCreateSeq(0, sizeof(CvSeq), sizeof(CvPoint), squareStorage);

	cvCvtColor(sceneImagePts, tgray, CV_RGB2GRAY);

	// apply threshold if l!=0:
	//     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
	cvThreshold(tgray, gray, squareThreshold, 255, CV_THRESH_BINARY );

	// find contours and store them all as a list
	cvFindContours(gray, squareStorage, &contours, sizeof(CvContour),
				   CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

	// test each contour
	while(contours)
	{
		// approximate contour with accuracy proportional
		// to the contour perimeter
		result = cvApproxPoly(contours, 
							  sizeof(CvContour), 
							  squareStorage,
							  CV_POLY_APPROX_DP, 
							  cvContourPerimeter(contours) * 0.02, 
							  0);

		// square contours should have 4 vertices after approximation
		// relatively large area (to filter out noisy contours)
		// and be convex.
		// Note: absolute value of an area is used because
		// area may be positive or negative - in accordance with the
		// contour orientation
		if(result->total == 4 &&
		   fabs(cvContourArea(result, CV_WHOLE_SEQ)) > 1000 &&
		   cvCheckContourConvexity(result))
		{
			s = 0;

			for(i = 0; i < 5; ++i)
			{
				// find minimum angle between joint
				// edges (maximum of cosine)
				if(i >= 2)
				{
					t = fabs(angle((CvPoint*)cvGetSeqElem(result, i),
								   (CvPoint*)cvGetSeqElem(result, i-2),
								   (CvPoint*)cvGetSeqElem(result, i-1)));
					s = s > t ? s : t;
				}
			}

			// if cosines of all angles are small
			// (all angles are ~90 degree) then write quandrange
			// vertices to resultant sequence
			if(s < 0.2)
			{
				CvSeqReader reader;

				// initialize reader of the sequence
				cvStartReadSeq(result, &reader, 0);
				CvPoint pt[4];

				CV_READ_SEQ_ELEM( pt[0], reader );
				CV_READ_SEQ_ELEM( pt[1], reader );
				CV_READ_SEQ_ELEM( pt[2], reader );
				CV_READ_SEQ_ELEM( pt[3], reader );

				for(int i = 1; i < 4; ++i)
				{
					for(int j = 0; j < 4 - i; ++j)
					{
						if(pt[j].x > pt[j+1].x)
						{
							CvPoint temp = pt[j+1];
							pt[j+1] = pt[j];
							pt[j] = temp;
						}
					}
				}

				if(pt[0].y > pt[1].y)
				{
					CvPoint temp = pt[1];
					pt[1] = pt[0];
					pt[0] = temp;
				}

				if(pt[2].y > pt[3].y)
				{
					CvPoint temp = pt[3];
					pt[3] = pt[2];
					pt[2] = temp;
				}

				if(abs(pt[0].y - pt[1].y) > 240)
				{
					sceneCorner[0] = pt[0];
					sceneCorner[1] = pt[1];
					sceneCorner[2] = pt[2];
					sceneCorner[3] = pt[3];

					for(int i = 0; i < 4; ++i)
						cvSeqPush(squares, (CvPoint*) cvGetSeqElem(result, i));

					break;
				}
			}
		}

		// take the next contour
		contours = contours->h_next;
	}

	// release all the temporary images
	cvReleaseImage(&gray);
	cvReleaseImage(&tgray);
	
	return squares;
}

double EyeTracker::angle(CvPoint* pt1, CvPoint* pt2, CvPoint* pt0)
{
	double dx1 = pt1->x - pt0->x;
	double dy1 = pt1->y - pt0->y;
	double dx2 = pt2->x - pt0->x;
	double dy2 = pt2->y - pt0->y;

	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1) * (dx2*dx2 + dy2*dy2) + 1e-10);
}

void EyeTracker::drawSquares(CvSeq* squares)
{
	CvSeqReader reader;
	int i;

	// initialize reader of the sequence
	cvStartReadSeq(squares, &reader, 0);
	CvPoint pt[4];
	CvPoint* rect;

	// read 4 sequence elements at a time (all vertices of a square)
	for(i = 0; i < squares->total; i += 4)
	{
		rect = pt;
		int count = 4;

		// read 4 vertices
		CV_READ_SEQ_ELEM(pt[0], reader);
		CV_READ_SEQ_ELEM(pt[1], reader);
		CV_READ_SEQ_ELEM(pt[2], reader);
		CV_READ_SEQ_ELEM(pt[3], reader);

		cvPolyLine(graySceneImagePts, &rect, &count, 1, 1, CV_RGB(255, 255, 255), 3, CV_AA, 0);
	}

	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, 1.0, 1.0, 0, 1);

	char s[20];
	sprintf(s, "Threshold = %d", squareThreshold);

	cvPutText(graySceneImagePts, s, cvPoint(30, 30), &font, cvScalar(255, 255, 0));
}

void EyeTracker::mergeImage()
{
	IplImage* imgsmall = cvCreateImage(cvSize(128, 96), 8, 1);

	cvResize(grayEyeImagePts, imgsmall);

	cvCopyImage( graySceneImagePts, mergedImage );

	for(int i = 0; i < imgsmall->width; ++i)
	{
		for(int j = 0; j < imgsmall->height; ++j)
		{
			cvSet2D(mergedImage, j, i, cvGet2D(imgsmall, j, i));
		}
	}

	cvReleaseImage(&imgsmall);
}

void EyeTracker::showMergeImage()
{
	mergeImage();
	cvShowImage(MERGE_IMAGE_WINDOW_NAME, mergedImage );
}

double *EyeTracker::getSceneRate()
{
	int fark;

	if(scenePoint.x < sceneCorner[0].x || scenePoint.x > sceneCorner[2].x)
		sceneRate[0] = -1;

	else
	{
		fark = sceneCorner[2].x - sceneCorner[0].x;
		
		if(fark == 0)
			sceneRate[0] = 0;
	
		else
		{
			sceneRate[0] = 100 * (double)(scenePoint.x - sceneCorner[0].x) / fark;
		}
	}

	if(scenePoint.y < sceneCorner[0].y || scenePoint.y > sceneCorner[1].y)
		sceneRate[1] = -1;
	
	else
	{
		fark = sceneCorner[1].y - sceneCorner[0].y;

		if(fark == 0)
			sceneRate[1] = 0;
	
		else
		{
			sceneRate[1] = 100 * (double)(scenePoint.y - sceneCorner[0].y) / fark;
		}
	}

	return sceneRate;
}

void EyeTracker::addToList(const CvPoint &p)
{
	int size = centerList.size();
	
	if(size > CENTER_LIST_SIZE)
		centerList.pop_front();

	centerList.push_back(p);

	CvPoint sum = cvPoint(0, 0);
	
	for(list<CvPoint>::iterator itr = centerList.begin(); itr != centerList.end(); ++itr)
	{
		sum.x += (*itr).x;
		sum.y += (*itr).y;
	}

	aver_center.x = cvRound((double)sum.x/size);
	aver_center.y = cvRound((double)sum.y/size);
}

bool EyeTracker::isSetCameras()
{
	return eyeCamera != NULL && sceneCamera != NULL;
}

void EyeTracker::showWindow()
{
	cvNamedWindow(MERGE_IMAGE_WINDOW_NAME, 1);
}

void EyeTracker::showWindows()
{
	cvNamedWindow(PUPIL_DETECTION_WINDOW_NAME, 1);
}

void EyeTracker::hideWindow()
{
	cvDestroyAllWindows();
	
#ifndef WIN32
	
	cvShowImage(PUPIL_DETECTION_WINDOW_NAME, grayEyeImagePts);
	cvShowImage(SCENE_CAMERA_WINDOW_NAME, graySceneImagePts);
	cvShowImage(MERGE_IMAGE_WINDOW_NAME, mergedImage);
	
	cvDestroyAllWindows();
	
#endif
}

/* New added by by nsk. */
void EyeTracker::calibrateLeftTopCorner()
{
	calibrator->setEyeLeftTopCorner(whereIsEyeNow());
}

void EyeTracker::calibrateRightTopCorner()
{
	calibrator->setEyeRightTopCorner(whereIsEyeNow());
}

void EyeTracker::calibrateLeftDownCorner()
{
	calibrator->setEyeLeftDownCorner(whereIsEyeNow());
}

void EyeTracker::calibrateRightDownCorner()
{
	calibrator->setEyeRightDownCorner(whereIsEyeNow());
}

void EyeTracker::calibrateLeftTopCorner(Point2f& eyePoint)
{
	calibrator->setEyeLeftTopCorner(eyePoint);
}

void EyeTracker::calibrateRightTopCorner(Point2f& eyePoint)
{
	calibrator->setEyeRightTopCorner(eyePoint);
}

void EyeTracker::calibrateLeftDownCorner(Point2f& eyePoint)
{
	calibrator->setEyeLeftDownCorner(eyePoint);
}

void EyeTracker::calibrateRightDownCorner(Point2f& eyePoint)
{
	calibrator->setEyeRightDownCorner(eyePoint);
}

void EyeTracker::calibrate()
{
	calibrator->calibrate();
}

/*##############################################################################*/
/*						Corneal Reflection Remover Code							*/
/*##############################################################################*/
void EyeTracker::removeReflection()
{
	/* Apply noise reduction */
	cvSmooth(originalEyeImagePts, originalEyeImagePts);

	threshold_image = cvCloneImage(grayEyeImagePts);
	
	remove_corneal_reflection( 320, 160, cr_window_size, 
		(int)grayEyeImagePts->height/10, corneal_reflection.x, corneal_reflection.y );  

	remove_corneal_reflection( 320, 160, cr_window_size, 
		(int)grayEyeImagePts->height/10, corneal_reflection.x, corneal_reflection.y );

	cvReleaseImage(&threshold_image);
}

void EyeTracker::remove_corneal_reflection( int sx, int sy, int window_size, 
											int biggest_crr, int& crx, int& cry )
{
	int crar = -1;	//corneal reflection approximate radius
	crx = cry = crar = -1;

	float angle_delta = (float)(1 * PI / 180);
	int angle_num = (int)(2*PI/angle_delta);
	//printf("(corneal reflection) sx:%d; sy:%d\n", sx, sy);
	double *angle_array = (double*)malloc(angle_num*sizeof(double));
	double *sin_array = (double*)malloc(angle_num*sizeof(double));
	double *cos_array = (double*)malloc(angle_num*sizeof(double));
	for (int i = 0; i < angle_num; i++) {
		angle_array[i] = i*angle_delta;
		sin_array[i] = sin(angle_array[i]);
		cos_array[i] = cos(angle_array[i]);
	}

	locate_corneal_reflection( sx, sy, window_size, (int)(biggest_crr/2.5), crx, cry, crar);
	corneal_reflection_r = fit_circle_radius_to_corneal_reflection( crx, cry, crar, (int)(biggest_crr/2.5),  sin_array, cos_array, angle_num);
	corneal_reflection_r = (int)(2.5*corneal_reflection_r);
	interpolate_corneal_reflection( crx, cry , sin_array, cos_array, angle_num);

	free(angle_array);
	free(sin_array);
	free(cos_array);
}

void EyeTracker::locate_corneal_reflection( int sx, int sy, int window_size, int 
							   biggest_crar, int &crx, int &cry, int &crar)
{
	if(window_size % 2 == 0)
	{
		printf("Error! window_size should be odd!\n");
	}

	int r = (window_size-1)/2;
	int startx = MAX(sx-r, 0);
	int endx = MIN(sx+r, grayEyeImagePts->width-1);
	int starty = MAX(sy-r, 0);
	int endy = MIN(sy+r, grayEyeImagePts->height-1);
	cvSetImageROI(grayEyeImagePts, cvRect(startx, starty, endx-startx+1, endy-starty+1));
	cvSetImageROI(threshold_image, cvRect(startx, starty, endx-startx+1, endy-starty+1));

	double min_value, max_value;
	CvPoint min_loc, max_loc; //location


	cvMinMaxLoc(grayEyeImagePts, &min_value, &max_value, &min_loc, &max_loc);

	int threshold, i;
	CvSeq* contour=NULL;
	CvMemStorage* storage = cvCreateMemStorage(0);
	double *scores = (double*)malloc(sizeof(double)*((int)max_value+1));
	memset(scores, 0, sizeof(double)*((int)max_value+1));
	int area, max_area, sum_area;
	for (threshold = (int)max_value; threshold >= 1; threshold--) {
		cvThreshold(grayEyeImagePts, threshold_image, threshold, 1, CV_THRESH_BINARY);
		cvFindContours(threshold_image, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_NONE);    
		max_area = 0;
		sum_area = 0;
		CvSeq *max_contour = contour;
		for( ; contour != 0; contour = contour->h_next) {
			area = contour->total + (int)(fabs(cvContourArea(contour, CV_WHOLE_SEQ)));
			sum_area += area;
			if (area > max_area) {
				max_area = area;
				max_contour = contour;
			}
		}
		if (sum_area-max_area > 0) {
			scores[threshold-1] = max_area / (sum_area-max_area);
			//printf("max_area: %d, max_contour: %d, sum_area: %d; scores[%d]: %lf\n", 
			//        max_area, max_contour->total, sum_area, threshold-1, scores[threshold-1]);      
		}
		else
			continue;

		if (scores[threshold-1] - scores[threshold] < 0) {
			//found the corneal reflection
			crar = (int)sqrt(max_area / PI);
			int sum_x = 0;
			int sum_y = 0;
			CvPoint *point;
			for (i = 0; i < max_contour->total; i++) {
				point = CV_GET_SEQ_ELEM(CvPoint, max_contour, i);
				sum_x += point->x;
				sum_y += point->y;
			}
			crx = sum_x/max_contour->total;
			cry = sum_y/max_contour->total;
			break;
		}
	}

	free(scores);
	cvReleaseMemStorage(&storage);
	cvResetImageROI(grayEyeImagePts);
	cvResetImageROI(threshold_image);

	if (crar > biggest_crar) {
		//printf("(corneal) size wrong! crx:%d, cry:%d, crar:%d (should be less than %d)\n", crx, cry, crar, biggest_crar);
		cry = crx = -1;
		crar = -1;
	}

	if (crx != -1 && cry != -1) {
		//  printf("(corneal) startx:%d, starty:%d, crx:%d, cry:%d, crar:%d\n", startx, starty, crx, cry, crar);
		crx += startx;
		cry += starty;
	}

}

int EyeTracker::fit_circle_radius_to_corneal_reflection( int crx, int cry, int crar, int biggest_crar, double *sin_array, double *cos_array, int array_len)
{
	if (crx == -1 || cry == -1 || crar == -1)
		return -1;

	double *ratio = (double*)malloc((biggest_crar-crar+1)*sizeof(double));
	int i, r, r_delta=1; 
	int x, y, x2, y2;
	double sum, sum2;
	for (r = crar; r <= biggest_crar; r++) {
		sum = 0;
		sum2 = 0;
		for (i = 0; i < array_len; i++) {
			x = (int)(crx + (r+r_delta)*cos_array[i]);
			y = (int)(cry + (r+r_delta)*sin_array[i]);
			x2 = (int)(crx + (r-r_delta)*cos_array[i]);
			y2 = (int)(cry + (r+r_delta)*sin_array[i]);
			if ((x >= 0 && y >=0 && x < grayEyeImagePts->width && y < grayEyeImagePts->height) &&
				(x2 >= 0 && y2 >=0 && x2 < grayEyeImagePts->width && y2 < grayEyeImagePts->height)) {
					sum += *(grayEyeImagePts->imageData+y*grayEyeImagePts->width+x);
					sum2 += *(grayEyeImagePts->imageData+y2*grayEyeImagePts->width+x2);
			}
		}
		ratio[r-crar] = sum / sum2;
		if (r - crar >= 2) {
			if (ratio[r-crar-2] < ratio[r-crar-1] && ratio[r-crar] < ratio[r-crar-1]) {
				free(ratio);
				return r-1;
			}
		} 
	}

	free(ratio);
	// printf("ATTN! fit_circle_radius_to_corneal_reflection() do not change the radius\n");
	return crar;
}

void EyeTracker::interpolate_corneal_reflection( int crx, int cry, double *sin_array, double *cos_array, 
									int array_len)
{
	if (crx == -1 || cry == -1 || corneal_reflection_r == -1)
		return;

	if (crx-corneal_reflection_r < 0 || crx+corneal_reflection_r >= grayEyeImagePts->width || cry-corneal_reflection_r < 0 || cry+corneal_reflection_r >= grayEyeImagePts->height) {
		printf("Error! Corneal reflection is too near the image border\n");
		return;
	}

	int i, r, r2,  x, y;
	unsigned char *perimeter_pixel = (unsigned char*)malloc(array_len*sizeof(int));
	int sum=0;
	double avg;
	for (i = 0; i < array_len; i++) {
		x = (int)(crx + corneal_reflection_r*cos_array[i]);
		y = (int)(cry + corneal_reflection_r*sin_array[i]);
		perimeter_pixel[i] = (unsigned char)(*(grayEyeImagePts->imageData+y*grayEyeImagePts->width+x));
		sum += perimeter_pixel[i];
	}
	avg = sum*1.0/array_len;

	for (r = 1; r < corneal_reflection_r; r++) {
		r2 = corneal_reflection_r-r;
		for (i = 0; i < array_len; i++) {
			x = (int)(crx + r*cos_array[i]);
			y = (int)(cry + r*sin_array[i]);
			*(grayEyeImagePts->imageData+y*grayEyeImagePts->width+x) = (unsigned char)((r2*1.0/corneal_reflection_r)*avg + (r*1.0/corneal_reflection_r)*perimeter_pixel[i]);
		}
	}
	free(perimeter_pixel);
}