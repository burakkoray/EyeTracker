#include "Commons.h"

namespace Nsk
{
	FrontCameraFrameReaderThread::FrontCameraFrameReaderThread(QObject* parent) : QThread(parent)
	{
		this->cameraIndex = 0;
	}

	FrontCameraFrameReaderThread::~FrontCameraFrameReaderThread()
	{
		// Intentionally empty
	}
 
	void FrontCameraFrameReaderThread::run(void)
	{
		emit onCameraTextChanged("Loading...");

		VideoCapture videoCapture(cameraIndex);
		Mat frame;
		
		/* If camera could not be opened */
		if(!videoCapture.isOpened())
		{
			emit onCameraTextChanged("Cannot open camera");
			qDebug() << "Capture not opened";
			return;
		}

		for( ; ; )
		{
			videoCapture.read(frame);
			emit onCameraPixmapChanged(QPixmap::fromImage(cvMatToQImage(frame)));
			waitKey();
		}
	}

	EyeCameraFrameReaderThread::EyeCameraFrameReaderThread(QObject* parent) : QThread(parent)
	{
		this->cameraIndex = 0;
	}

	EyeCameraFrameReaderThread::~EyeCameraFrameReaderThread()
	{
		// Intentionally empty
	}
 
	void EyeCameraFrameReaderThread::run(void)
	{
		emit onCameraTextChanged("Loading...");
		int frontCamIndex = cameraIndex == 1 ? 2 : 1;
		EyeTracker *eyeTracker = new EyeTracker(cameraIndex, frontCamIndex);

		// If camera could not be opened 
		if(!eyeTracker->isOpened())
		{
			qDebug() << "Error: Cannot connect to camera.";
			emit onCameraTextChanged("Cannot connect to camera");
			emit finished();
		}

		for( ; ; )
		{
			// Capture images 
			eyeTracker->captureEyeFrame();
			eyeTracker->captureSceneFrame();

			Point2f p = eyeTracker->doTrack();

			// Set up x and y coordinates 
			char str[50];
			sprintf(str, "%.1f", p.x);
			emit onEyeXChanged(str);
		
			sprintf(str, "%.1f", p.y);
			emit onEyeYChanged(str);

			// Draw squares to eye image 
			eyeTracker->drawSquares(eyeTracker->findSquares());
			
			// Set eye pixmap 
			emit onCameraPixmapChanged(QPixmap::fromImage(cvMatToQImage(cvarrToMat(eyeTracker->getEyeImage()))));
				
			// Release images 
			eyeTracker->releaseGrayEyeImage();
			eyeTracker->releaseGraySceneImage();

			cvWaitKey(20);
		}
	}

	QImage cvMatToQImage(const Mat &inMat)
	{
		switch ( inMat.type() )
		{
			// 8-bit, 4 channel
			case CV_8UC4:
			{
				QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

				return image;
			}

			// 8-bit, 3 channel
			case CV_8UC3:
			{
				QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

				return image.rgbSwapped();
			}

			// 8-bit, 1 channel
			case CV_8UC1:
			{
				QVector<QRgb>  sColorTable;

				// only create our color table once
				if ( sColorTable.isEmpty() )
				{
					for ( int i = 0; i < 256; ++i )
					sColorTable.push_back( qRgb( i, i, i ) );
				}

				QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

				image.setColorTable( sColorTable );

				return image;
			}

			default:
			qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
			break;
		}

		return QImage();
	}

	bool approximatelyEquals(double x1, double x2, double tolerance)
	{
		return (x1 - x2) < 0.0001 || (x2 - x1) < 0.001;
	}
}