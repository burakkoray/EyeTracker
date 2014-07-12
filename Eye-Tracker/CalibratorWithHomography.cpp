#include "CalibratorWithHomography.h"

namespace Nsk
{
	/* No-parameter constructor */
	CalibratorWithHomography::CalibratorWithHomography()
	{
		calibrated = false;
		
		eyeMat = cvCreateMat(CALIBRATE_POINT, 2, CV_64FC1 );
		sceneMat = cvCreateMat(CALIBRATE_POINT, 2, CV_64FC1 );
		homography = cvCreateMat( 3, 3, CV_64FC1);
		hedefp = cvCreateMat(3, 1, CV_64FC1);
		centerMatrix = cvCreateMat(3, 1, CV_64FC1);

		hedefp->data.db[0] = 0;
		hedefp->data.db[1] = 0;
		hedefp->data.db[2] = 0;
	}

	CalibratorWithHomography::CalibratorWithHomography(const CalibratorWithHomography& other)
	{
		this->calibrated = other.calibrated;
	}

	/* Sets the left top corner point of the window */
	void CalibratorWithHomography::setWindowLeftTopCorner(Point2f windowLeftTopCorner)
	{
		if(windowLeftTopCorner.x <= 0 || windowLeftTopCorner.y <= 0)
		{
			printf("Error: window left top corner should be non zero.\n");
			return;
		}

		sceneMat->data.db[2*0] = windowLeftTopCorner.x;
		sceneMat->data.db[2*1] = windowLeftTopCorner.y;
		
		qDebug() << "Window left top setted to " << "(" << windowLeftTopCorner.x << ", " << windowLeftTopCorner.y << ")";
	}

	/* Sets the left down corner point of the window */
	void CalibratorWithHomography::setWindowLeftDownCorner(Point2f windowLeftDownCorner)
	{
		if(windowLeftDownCorner.x <= 0 || windowLeftDownCorner.y <= 0)
		{
			printf("Error: window left down corner should be non zero.\n");
			return;
		}

		sceneMat->data.db[2*4] = windowLeftDownCorner.x;
		sceneMat->data.db[2*5] = windowLeftDownCorner.y;
		qDebug() << "Window left down setted to " << "(" << windowLeftDownCorner.x << ", " << windowLeftDownCorner.y << ")";
	}

	/* Sets the right top corner point of the window */
	void CalibratorWithHomography::setWindowRightTopCorner(Point2f windowRightTopCorner)
	{
		if(windowRightTopCorner.x <= 0 || windowRightTopCorner.y <= 0)
		{
			printf("Error: window right top corner should be non zero.\n");
			return;
		}

		sceneMat->data.db[2*2] = windowRightTopCorner.x;
		sceneMat->data.db[2*3] = windowRightTopCorner.y;
		qDebug() << "Window right top setted to " << "(" << windowRightTopCorner.x << ", " << windowRightTopCorner.y << ")";
	}

	/* Sets the right down corner point of the window */
	void CalibratorWithHomography::setWindowRightDownCorner(Point2f windowRightDownCorner)
	{
		if(windowRightDownCorner.x <= 0 || windowRightDownCorner.y <= 0)
		{
			printf("Error: window right down corner should be non zero.\n");
			return;
		}
	
		sceneMat->data.db[2*6] = windowRightDownCorner.x;
		sceneMat->data.db[2*7] = windowRightDownCorner.y;
		qDebug() << "Window right down setted to " << "(" << windowRightDownCorner.x << ", " << windowRightDownCorner.y << ")";
	}

	/* Sets the left top corner point of the eye */
	void CalibratorWithHomography::setEyeLeftTopCorner(Point2f eyeLeftTopCorner)
	{
		if(eyeLeftTopCorner.x <= 0 || eyeLeftTopCorner.y <= 0)
		{
			printf("Error: eye left top corner should be non zero.\n");
			return;
		}

		this->eyeLeftTopCorner = eyeLeftTopCorner;

		eyeMat->data.db[2*0] = eyeLeftTopCorner.x;
		eyeMat->data.db[2*1] = eyeLeftTopCorner.y;
		qDebug() << "Eye left top setted to " << "(" << eyeLeftTopCorner.x << ", " << eyeLeftTopCorner.y << ")";
	}

	/* Sets the left down corner point of the eye */
	void CalibratorWithHomography::setEyeLeftDownCorner(Point2f eyeLeftDownCorner)
	{
		if(eyeLeftDownCorner.x <= 0 || eyeLeftDownCorner.y <= 0)
		{
			printf("Error: eye left down corner should be non zero.\n");
			return;
		}

		this->eyeLeftDownCorner = eyeLeftDownCorner;

		eyeMat->data.db[2*4] = eyeLeftDownCorner.x;
		eyeMat->data.db[2*5] = eyeLeftDownCorner.y;
		qDebug() << "Eye left down setted to " << "(" << eyeLeftDownCorner.x << ", " << eyeLeftDownCorner.y << ")";
	}

	/* Sets the right top corner point of the eye */
	void CalibratorWithHomography::setEyeRightTopCorner(Point2f eyeRightTopCorner)
	{
		if(eyeRightTopCorner.x <= 0 || eyeRightTopCorner.y <= 0)
		{
			printf("Error: eye right top corner should be non zero.\n");
			return;
		}

		this->eyeRightTopCorner = eyeRightTopCorner;

		eyeMat->data.db[2*2] = eyeRightTopCorner.x;
		eyeMat->data.db[2*3] = eyeRightTopCorner.y;
		qDebug() << "Eye right top setted to " << "(" << eyeRightTopCorner.x << ", " << eyeRightTopCorner.y << ")";
	}

	/* Sets the right down corner point of the eye */
	void CalibratorWithHomography::setEyeRightDownCorner(Point2f eyeRightDownCorner)
	{
		if(eyeRightDownCorner.x <= 0 || eyeRightDownCorner.y <= 0)
		{
			printf("Error: eye right down corner should be non zero.\n");
			return;
		}

		this->eyeRightDownCorner = eyeRightDownCorner;
	
		eyeMat->data.db[2*6] = eyeRightDownCorner.x;
		eyeMat->data.db[2*7] = eyeRightDownCorner.y;
		qDebug() << "Eye right down setted to " << "(" << eyeRightDownCorner.x << ", " << eyeRightDownCorner.y << ")";
	}

	/* Computes ratios, this function should be called to make user sure that calibration done. */
	void CalibratorWithHomography::calibrate()
	{
		cvFindHomography(eyeMat, sceneMat, homography);
/*
		cvReleaseMat(&eyeMat);
		cvReleaseMat(&sceneMat);
		*/
		calibrated = true;
	}

	/* Converts eye point to window point. Returns with a point that user looks at on window. */
	Point2f CalibratorWithHomography::convertToWindowPoint(Point2f eyePoint) const
	{
		if(!this->cornersSetUpDone())
		{
			qDebug() << "Error: Corners setup not done!";
			return Point2f(-1, -1);
		}

		Point2f windowPoint;

		centerMatrix->data.db[0] = eyePoint.x;
		centerMatrix->data.db[1] = eyePoint.y;
		centerMatrix->data.db[2] = 1;

		cvGEMM( homography, centerMatrix, 1, 0 ,0, hedefp );

		windowPoint = cvPoint( cvRound(hedefp->data.db[0] / hedefp->data.db[2]),
								cvRound(hedefp->data.db[1] / hedefp->data.db[2]) );

		/* If we are in out of range, set window point to bounds *//*
		if(windowPoint.x < windowLeftTopCorner.x)
			windowPoint.x = windowLeftTopCorner.x;

		if(windowPoint.x > windowRightTopCorner.x)
			windowPoint.x = windowRightTopCorner.x;

		if(windowPoint.y < windowLeftTopCorner.y)
			windowPoint.y = windowLeftTopCorner.y;

		if(windowPoint.y > windowLeftDownCorner.y)
			windowPoint.y = windowLeftDownCorner.y;
		*/
		
		qDebug() << "Incoming eye point: " << eyePoint.x << ", " << eyePoint.y;
		qDebug() << "Outgoing window point: " << windowPoint.x << ", " << windowPoint.y;
		
		
		
		return windowPoint;
	}

	bool CalibratorWithHomography::cornersSetUpDone() const
	{
		return true;
		/*
		return eyeLeftTopCorner.x != -1 &&
				eyeLeftDownCorner.x != -1 &&
				eyeRightTopCorner.x != -1 &&
				eyeRightDownCorner.x != -1 &&
				windowLeftTopCorner.x != -1 &&
				windowLeftDownCorner.x != -1 &&
				windowRightTopCorner.x != -1 &&
				windowRightDownCorner.x != -1;
		*/
	}
}