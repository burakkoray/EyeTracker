#ifndef COMMONS_H
#define COMMONS_H

#include "EyeTracker.h"
#include <QObject>
#include <QThread>
#include <QPixmap>
#include <opencv2/opencv.hpp>

using namespace cv;

namespace Nsk
{
	// Front camera stream reader thread class
	class FrontCameraFrameReaderThread : public QThread
	{
		Q_OBJECT;

	public:
		explicit FrontCameraFrameReaderThread(QObject* parent = 0);
		int getCameraIndex() const { return cameraIndex; }
		void setCameraIndex(int cameraIndex) { this->cameraIndex = cameraIndex; };
		~FrontCameraFrameReaderThread();
 
	signals:
		void onCameraPixmapChanged(const QPixmap&);
		void onCameraTextChanged(const QString&);

	protected:
		void run(void);
 
	private:
		int cameraIndex;
	};

	// Eye camera stream reader thread class
	class EyeCameraFrameReaderThread : public QThread
	{
		Q_OBJECT;

	public:
		explicit EyeCameraFrameReaderThread(QObject* parent = 0);
		int getCameraIndex() const { return cameraIndex; }
		void setCameraIndex(int cameraIndex) { this->cameraIndex = cameraIndex; }
		~EyeCameraFrameReaderThread();
 
	signals:
		void onCameraPixmapChanged(const QPixmap&);
		void onCameraTextChanged(const QString&);
		void onEyeXChanged(const QString&);
		void onEyeYChanged(const QString&);

	protected:
		void run(void);
 
	private:
		int cameraIndex;
	};

	QImage cvMatToQImage(const Mat &inMat);
	bool approximatelyEquals(double x1, double x2, double tolerance);

	class Sleeper : public QThread
	{
	public:
		/* Sleeps for given seconds */
		static void sleep(unsigned long secs) {
			QThread::sleep(secs);
		}

		/* Sleeps for given milliseconds */
		static void msleep(unsigned long msecs) {
			QThread::msleep(msecs);
		}

		/* Sleeps for given microseconds */
		static void usleep(unsigned long usecs) {
			QThread::usleep(usecs);
		}
	};
}

#endif