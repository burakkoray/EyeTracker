#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <opencv/cv.h>
#include <QDebug>

using namespace cv;

namespace Nsk
{
	class Calibrator
	{
	public:
		Calibrator();
		Calibrator(const Calibrator& other);
		void setWindowLeftTopCorner(Point2f windowLeftTopCorner);
		void setWindowLeftDownCorner(Point2f windowLeftDownCorner);
		void setWindowRightTopCorner(Point2f windowRightTopCorner);
		void setWindowRightDownCorner(Point2f windowRightDownCorner);
		void setEyeLeftTopCorner(Point2f eyeLeftTopCorner);
		void setEyeLeftDownCorner(Point2f eyeLeftDownCorner);
		void setEyeRightTopCorner(Point2f eyeRightTopCorner);
		void setEyeRightDownCorner(Point2f eyeRightDownCorner);
		void calibrate();
		Point2f convertToWindowPoint(Point2f eyePoint) const;
		bool cornersSetUpDone() const;
		Point2f getEyeLeftTopCorner() { return eyeLeftTopCorner; }
		Point2f getEyeLeftDownCorner() { return eyeLeftDownCorner; }
		Point2f getEyeRightTopCorner() { return eyeRightTopCorner; }
		Point2f getEyeRightDownCorner() { return eyeRightDownCorner; }
		double getEyeFrameWidth() const { return maxEyeX - minEyeX; }
		double getEyeFrameHeight() const { return maxEyeY - minEyeY; }
		double getWindowWidth() const { qDebug() << "Window right top corner x: " <<  windowRightTopCorner.x << " Window left top corner x: " << windowLeftTopCorner.x; return (windowRightTopCorner.x - windowLeftTopCorner.x); }
		double getWindowHeight() const { qDebug() << "Window left down corner x: " <<  windowLeftDownCorner.x << " Window left top corner x: " << windowLeftTopCorner.x; return (windowLeftDownCorner.y - windowLeftTopCorner.y); }
		virtual ~Calibrator() { }

	private:
		Point2f eyeLeftTopCorner;
		Point2f eyeLeftDownCorner;
		Point2f eyeRightTopCorner;
		Point2f eyeRightDownCorner;
		Point2f windowLeftTopCorner;
		Point2f windowLeftDownCorner;
		Point2f windowRightTopCorner;
		Point2f windowRightDownCorner;

		double minEyeX;
		double minEyeY;
		double maxEyeX;
		double maxEyeY;

		double windowToEyeWidthRatio;
		double windowToEyeHeightRatio;
	
		bool calibrated;
	};
}

#endif