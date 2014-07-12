#include "Calibrator.h"

namespace Nsk
{
	/* No-parameter constructor */
	Calibrator::Calibrator()
	{
		calibrated = false;
		
		eyeLeftTopCorner = Point2f(-1, -1);
		eyeLeftDownCorner = Point2f(-1, -1);
		eyeRightTopCorner = Point2f(-1, -1);
		eyeRightDownCorner = Point2f(-1, -1);
		windowLeftTopCorner = Point2f(-1, -1);
		windowLeftDownCorner = Point2f(-1, -1);
		windowRightTopCorner = Point2f(-1, -1);
		windowRightDownCorner = Point2f(-1, -1);
	}

	Calibrator::Calibrator(const Calibrator& other)
	{
		this->calibrated = other.calibrated;
		this->windowToEyeWidthRatio = other.windowToEyeWidthRatio;
		this->windowToEyeHeightRatio = other.windowToEyeHeightRatio;
		
		this->eyeLeftTopCorner = other.eyeLeftTopCorner;
		this->eyeLeftDownCorner = other.eyeLeftDownCorner;
		this->eyeRightTopCorner = other.eyeRightTopCorner;
		this->eyeRightDownCorner = other.eyeRightDownCorner;
		
		this->windowLeftTopCorner = Point2f(0, 0);
		this->windowLeftDownCorner = Point2f(0, 0);
		this->windowRightTopCorner = Point2f(0, 0);
		this->windowRightDownCorner = other.windowRightDownCorner;
	}

	/* Sets the left top corner point of the window */
	void Calibrator::setWindowLeftTopCorner(Point2f windowLeftTopCorner)
	{
		if(windowLeftTopCorner.x < 0 || windowLeftTopCorner.y < 0)
		{
			printf("Error: window left top corner should be non zero.\n");
			return;
		}

		this->windowLeftTopCorner = windowLeftTopCorner;
		qDebug() << "Window left top setted to " << "(" << windowLeftTopCorner.x << ", " << windowLeftTopCorner.y << ")";
	}

	/* Sets the left down corner point of the window */
	void Calibrator::setWindowLeftDownCorner(Point2f windowLeftDownCorner)
	{
		if(windowLeftDownCorner.x < 0 || windowLeftDownCorner.y < 0)
		{
			printf("Error: window left down corner should be non zero.\n");
			return;
		}

		this->windowLeftDownCorner = windowLeftDownCorner;
		qDebug() << "Window left down setted to " << "(" << windowLeftDownCorner.x << ", " << windowLeftDownCorner.y << ")";
	}

	/* Sets the right top corner point of the window */
	void Calibrator::setWindowRightTopCorner(Point2f windowRightTopCorner)
	{
		if(windowRightTopCorner.x < 0 || windowRightTopCorner.y < 0)
		{
			printf("Error: window right top corner should be non zero.\n");
			return;
		}

		this->windowRightTopCorner = windowRightTopCorner;
		qDebug() << "Window right top setted to " << "(" << windowRightTopCorner.x << ", " << windowRightTopCorner.y << ")";
	}

	/* Sets the right down corner point of the window */
	void Calibrator::setWindowRightDownCorner(Point2f windowRightDownCorner)
	{
		if(windowRightDownCorner.x < 0 || windowRightDownCorner.y < 0)
		{
			printf("Error: window right down corner should be non zero.\n");
			return;
		}
	
		this->windowRightDownCorner = windowRightDownCorner;
		qDebug() << "Window right down setted to " << "(" << windowRightDownCorner.x << ", " << windowRightDownCorner.y << ")";
	}

	/* Sets the left top corner point of the eye */
	void Calibrator::setEyeLeftTopCorner(Point2f eyeLeftTopCorner)
	{
		if(eyeLeftTopCorner.x <= 0 || eyeLeftTopCorner.y <= 0)
		{
			printf("Error: eye left top corner should be non zero.\n");
			return;
		}

		this->eyeLeftTopCorner = eyeLeftTopCorner;
		qDebug() << "Eye left top setted to " << "(" << eyeLeftTopCorner.x << ", " << eyeLeftTopCorner.y << ")";
	}

	/* Sets the left down corner point of the eye */
	void Calibrator::setEyeLeftDownCorner(Point2f eyeLeftDownCorner)
	{
		if(eyeLeftDownCorner.x <= 0 || eyeLeftDownCorner.y <= 0)
		{
			printf("Error: eye left down corner should be non zero.\n");
			return;
		}

		this->eyeLeftDownCorner = eyeLeftDownCorner;
		qDebug() << "Eye left down setted to " << "(" << eyeLeftDownCorner.x << ", " << eyeLeftDownCorner.y << ")";
	}

	/* Sets the right top corner point of the eye */
	void Calibrator::setEyeRightTopCorner(Point2f eyeRightTopCorner)
	{
		if(eyeRightTopCorner.x <= 0 || eyeRightTopCorner.y <= 0)
		{
			printf("Error: eye right top corner should be non zero.\n");
			return;
		}

		this->eyeRightTopCorner = eyeRightTopCorner;
		qDebug() << "Eye right top setted to " << "(" << eyeRightTopCorner.x << ", " << eyeRightTopCorner.y << ")";
	}

	/* Sets the right down corner point of the eye */
	void Calibrator::setEyeRightDownCorner(Point2f eyeRightDownCorner)
	{
		if(eyeRightDownCorner.x <= 0 || eyeRightDownCorner.y <= 0)
		{
			printf("Error: eye right down corner should be non zero.\n");
			return;
		}
	
		this->eyeRightDownCorner = eyeRightDownCorner;
		qDebug() << "Eye right down setted to " << "(" << eyeRightDownCorner.x << ", " << eyeRightDownCorner.y << ")";
	}

	/* Computes ratios, this function should be called to make user sure that calibration done. */
	void Calibrator::calibrate()
	{
		minEyeX = eyeLeftTopCorner.x < eyeLeftDownCorner.x ? eyeLeftTopCorner.x : eyeLeftDownCorner.x;
		maxEyeX = eyeRightTopCorner.x > eyeRightDownCorner.x ? eyeRightTopCorner.x : eyeRightDownCorner.x;
		minEyeY = eyeLeftTopCorner.y < eyeRightTopCorner.y ? eyeLeftTopCorner.y : eyeRightTopCorner.y;
		maxEyeY = eyeLeftDownCorner.y > eyeRightDownCorner.y ? eyeLeftDownCorner.y : eyeRightDownCorner.y;

		windowToEyeWidthRatio = (double) getWindowWidth() / (double) getEyeFrameWidth();
		windowToEyeHeightRatio = (double) getWindowHeight() / (double) getEyeFrameHeight();
		calibrated = true;

		qDebug() << "Eye Frame height: " <<  getEyeFrameHeight() << " Eye Frame width: " << getEyeFrameWidth();
		qDebug() << "Window height: " <<  getWindowHeight() << " Window width: " << getWindowWidth();
		qDebug() << "Window eye height ratio: " << windowToEyeHeightRatio << " Window eye width ratio: " << windowToEyeWidthRatio;
	}

	/* Converts eye point to window point. Returns with a point that user looks at on window. */
	Point2f Calibrator::convertToWindowPoint(Point2f eyePoint) const
	{
		if(!this->cornersSetUpDone())
		{
			qDebug() << "Error: Corners setup not done!";
			return Point2f(-1, -1);
		}

		Point2f windowPoint;
		/*
		windowPoint.x = eyePoint.x * windowToEyeWidthRatio;
		windowPoint.y = eyePoint.y * windowToEyeHeightRatio;
		*/

		double widthPercent = (eyePoint.x - minEyeX) / (double) getEyeFrameWidth(),
			   heightPercent = (eyePoint.y - minEyeY) / (double) getEyeFrameHeight();

		qDebug() << "Width percent: " << widthPercent << " Height percent: " << heightPercent;


		windowPoint.x = widthPercent * getWindowWidth() + windowLeftTopCorner.x;
		windowPoint.y = heightPercent * getWindowHeight() + windowLeftTopCorner.y;

		/* If we are in out of range, set window point to bounds */
		if(windowPoint.x < windowLeftTopCorner.x)
			windowPoint.x = windowLeftTopCorner.x;

		if(windowPoint.x > windowRightTopCorner.x)
			windowPoint.x = windowRightTopCorner.x;

		if(windowPoint.y < windowLeftTopCorner.y)
			windowPoint.y = windowLeftTopCorner.y;

		if(windowPoint.y > windowLeftDownCorner.y)
			windowPoint.y = windowLeftDownCorner.y;
			
		
		qDebug() << "Incoming eye point: " << eyePoint.x << ", " << eyePoint.y;
		qDebug() << "Outgoing window point: " << windowPoint.x << ", " << windowPoint.y;
		
		
		
		return windowPoint;
	}

	bool Calibrator::cornersSetUpDone() const
	{
		return eyeLeftTopCorner.x != -1 &&
				eyeLeftDownCorner.x != -1 &&
				eyeRightTopCorner.x != -1 &&
				eyeRightDownCorner.x != -1 &&
				windowLeftTopCorner.x != -1 &&
				windowLeftDownCorner.x != -1 &&
				windowRightTopCorner.x != -1 &&
				windowRightDownCorner.x != -1;
	}
}