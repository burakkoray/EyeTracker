#include "HeatmapWindow.h"
#include "Heatmap.h"
#include "EyeTracker.h"

namespace Nsk
{
	HeatmapCameraReaderThread::HeatmapCameraReaderThread(QObject* parent) : QThread(parent)
	{
		this->eyeTracker = NULL;
		this->eyeCameraIndex = 2;
		this->frontCameraIndex = 1;
	}

	HeatmapCameraReaderThread::~HeatmapCameraReaderThread()
	{
		// Intentionally empty
	}

	void HeatmapCameraReaderThread::run(void)
	{
		emit onFrontCameraTextChanged("Loading...");

		Mat frame;

		VideoCapture videoCapture(frontCameraIndex);
		
		/* If camera could not be opened */
		if(!videoCapture.isOpened())
		{
			qDebug() << "Error: Cannot connect to camera.";
			emit onFrontCameraTextChanged("Cannot connect to camera");
			emit finished();
		}

		videoCapture.read(frame);

		//Point2f previousEyePoint(-1, -1);
		double fps = 59;
		heatmap_init(frame, fps);
		
		// Create heatmap kernel
		create_kernel();

		while (frame.data != NULL)
		{
			/* Capture images */
			Point2f eyePoint = eyeTracker->getEyePointOnWindow();

			eyePoint.x = (eyePoint.x / eyeTracker->getCalibrator()->getWindowWidth()) * 640.0;
			eyePoint.y = (eyePoint.y / eyeTracker->getCalibrator()->getWindowHeight()) * 480.0;

			int k = 1;

			heat_point(eyePoint.x, eyePoint.y);
			//heat_point(eyePoint.x-k, eyePoint.y+k);
			heat_point(eyePoint.x, eyePoint.y+k);
			//heat_point(eyePoint.x+k, eyePoint.y+k);
			heat_point(eyePoint.x-k, eyePoint.y);
			heat_point(eyePoint.x+k, eyePoint.y);
			//heat_point(eyePoint.x-k, eyePoint.y-k);
			heat_point(eyePoint.x, eyePoint.y-k);
			//heat_point(eyePoint.x+k, eyePoint.y-k);

			qDebug() << "x: " << eyePoint.x << " y: " << eyePoint.y;
			
			/*
			// This is first enterance in this code. 
			if(previousEyePoint.x == -1)
			{
				qDebug() << "First enterance!";

				heat_point(eyePoint.x, eyePoint.y);

				qDebug() << "x: " << eyePoint.x << " y: " << eyePoint.y;
			}
			
			else
			{
				int x1 = previousEyePoint.x, x2 = eyePoint.x,
					y1 = previousEyePoint.y, y2 = eyePoint.y;

				// Ths increment number for traversing the line between two points. 
				int incNum = x1 > x2 ? -1 : +1;

				// Traverse the line
				for(int i = x1; !approximatelyEquals(i, x2, 0); i += incNum)
				{
					int x, y;

					x = i;
					y = (y2 - y1) * (x - x2) / (x2 - x1) + y2;

					heat_point(x, y);
				}
			}

			previousEyePoint = eyePoint;
			*/

			// Draw the heatmap
			overlay_heatmap(frame);

			emit onFrontCameraPixmapChanged(QPixmap::fromImage(cvMatToQImage(frame)));

			decrease_heatmap();

			videoCapture.read(frame);
			
			waitKey(100);

		}
	}

	HeatmapWindow::HeatmapWindow(QWidget *parent, Qt::WFlags flags)
						: QMainWindow(parent, flags), frontCamIndex(-1)
	{
		this->ui.setupUi(this);
		this->setWindowTitle("Heatmap");

		// Set up heatmap camera reader thread, connect to slots
		heatmapCameraReaderThread = new HeatmapCameraReaderThread(this);

		connect(heatmapCameraReaderThread, SIGNAL(onFrontCameraPixmapChanged(const QPixmap&)), ui.lCameraStream, SLOT(setPixmap(const QPixmap&)));
		connect(heatmapCameraReaderThread, SIGNAL(onFrontCameraTextChanged(const QString&)), ui.lCameraStream, SLOT(setText(const QString&)));
	}

	HeatmapWindow::~HeatmapWindow()
	{
		if(heatmapCameraReaderThread->isRunning())
		{
			heatmapCameraReaderThread->terminate();
		}

		delete heatmapCameraReaderThread;
	}

	void HeatmapWindow::setEyeCamIndex(int eyeCamIndex)
	{
		if(eyeCamIndex < 0)
		{
			printf("Front cam index cannot be negative!");
			return;
		}

		this->eyeCamIndex = eyeCamIndex;
	}

	void HeatmapWindow::setFrontCamIndex(int frontCamIndex)
	{
		if(frontCamIndex < 0)
		{
			printf("Front cam index cannot be negative!");
			return;
		}

		this->frontCamIndex = frontCamIndex;
	}

	void HeatmapWindow::paintEvent(QPaintEvent *event)
	{
		qDebug() << "Window width: " << this->geometry().width() << " height: " << this->geometry().height();
		int left, top, width, height;

		/* Set up front cam frame position */
		height = this->geometry().height();
		width = (height / 480.0) * 640.0;
		left = (this->geometry().width() - width) / 2;
		top = (this->geometry().height() - height) / 2;

		qDebug() << "Label left: " << left << " top: " << top << " width " << width << " height: " << height;
		ui.lCameraStream->setGeometry(left, top, width, height);
	}	
	
	void HeatmapWindow::keyPressEvent(QKeyEvent* event)
	{
		switch(event->key())
		{
		case Qt::Key_Escape:
			this->close();
			break;

		case Qt::Key_Enter: case Qt::Key_Return:
			#ifdef _WIN32
			if(!heatmapCameraReaderThread->isRunning())
			{
				heatmapCameraReaderThread->setEyeTracker(eyeTracker);
				heatmapCameraReaderThread->setEyeCameraIndex(eyeCamIndex);
				heatmapCameraReaderThread->setFrontCameraIndex(frontCamIndex);
				heatmapCameraReaderThread->start();
			}
			#else
			ui.lCameraStream->setText("Loading...");

			Mat frame;

			frame = cvarrToMat(eyeTracker->captureSceneFrame());

			// For video writer
			int askFileTypeBox=0;
			int color = 1;  
			Size size = Size(320, 240); 

			VideoWriter outVideo;  

			outVideo.open("Heatmap.avi", askFileTypeBox, 6, size, color);

			//Point2f previousEyePoint(-1, -1);
			double fps = 59;
			heatmap_init(frame, fps);
			
			// Create heatmap kernel
			create_kernel();

			while (frame.data != NULL)
			{
				/* Capture images */
				Point2f eyePoint = eyeTracker->getEyePointOnWindow();

				eyePoint.x = (eyePoint.x / eyeTracker->getCalibrator()->getWindowWidth()) * 640.0;
				eyePoint.y = (eyePoint.y / eyeTracker->getCalibrator()->getWindowHeight()) * 480.0;

				qDebug() << "x: " << eyePoint.x << " y: " << eyePoint.y;

				int k = 1;

				heat_point(eyePoint.x, eyePoint.y);
				//heat_point(eyePoint.x-k, eyePoint.y+k);
				heat_point(eyePoint.x, eyePoint.y+k);
				//heat_point(eyePoint.x+k, eyePoint.y+k);
				heat_point(eyePoint.x-k, eyePoint.y);
				heat_point(eyePoint.x+k, eyePoint.y);
				//heat_point(eyePoint.x-k, eyePoint.y-k);
				heat_point(eyePoint.x, eyePoint.y-k);
				//heat_point(eyePoint.x+k, eyePoint.y-k);


				/*
				// This is first enterance in this code. 
				if(previousEyePoint.x == -1)
				{
					qDebug() << "First enterance!";

					heat_point(eyePoint.x, eyePoint.y);

					qDebug() << "x: " << eyePoint.x << " y: " << eyePoint.y;
				}
				
				else
				{
					int x1 = previousEyePoint.x, x2 = eyePoint.x,
						y1 = previousEyePoint.y, y2 = eyePoint.y;

					// Ths increment number for traversing the line between two points. 
					int incNum = x1 > x2 ? -1 : +1;

					// Traverse the line
					for(int i = x1; i != x2; i += incNum)
					{
						int x, y;

						x = i;
						y = (y2 - y1) * (x - x2) / (x2 - x1) + y2;

						heat_point(x, y);
						
						qDebug() << "x: " << x << " y: " << y;
						
						// Set up x and y coordinates 
						char str[50];
						sprintf(str, "%.1f", eyePoint.x);
						eyeX->setText(str);
			
						sprintf(str, "%.1f", eyePoint.y);
						eyeY->setText(str);
					}
				}

				previousEyePoint = eyePoint;*/


				// Draw the heatmap
				overlay_heatmap(frame);

				ui.lCameraStream->setPixmap(QPixmap::fromImage(cvMatToQImage(frame)));
				outVideo << frame;

				decrease_heatmap();

				frame = cvarrToMat(eyeTracker->captureSceneFrame());
				waitKey();

			}
			#endif
			break;
		}
	}

	void HeatmapWindow::closeEvent(QCloseEvent *event)
	{
		QMessageBox exitDialog(this);
		int reply;

		exitDialog.setWindowTitle("Exit");
		exitDialog.setText("Are you sure you want to exit?");
		exitDialog.setWindowIcon(QPixmap("Images/exit.png"));
		exitDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		exitDialog.setIcon(QMessageBox::Question);
		
		reply = exitDialog.exec();
		
		if(reply == QMessageBox::Yes) 
		{
			event->accept();
		}

		else
		{
			event->ignore();
		}
	}
}