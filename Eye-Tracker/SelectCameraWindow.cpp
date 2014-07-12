#include "SelectCameraWindow.h"

namespace Nsk
{
	SelectCameraWindow::SelectCameraWindow(CalibrationWindow *calibrationWindow, QWidget *parent, Qt::WFlags flags)
			: QMainWindow(parent, flags), calibrationWindow(calibrationWindow)
	{
		this->ui.setupUi(this);
		this->setWindowTitle("Select camera");
		this->setWindowIcon(QIcon("Images/select_icon.png"));

		this->setAndContinueClicked = false;

		// Set up eye camera thread, connect to slots
		eyeCamFrameReaderThread = new EyeCameraFrameReaderThread(this);

		connect(eyeCamFrameReaderThread, SIGNAL(onCameraPixmapChanged(const QPixmap&)), ui.lEyeCam, SLOT(setPixmap(const QPixmap&)));
		connect(eyeCamFrameReaderThread, SIGNAL(onCameraTextChanged(const QString&)), ui.lEyeCam, SLOT(setText(const QString&)));
		connect(eyeCamFrameReaderThread, SIGNAL(onEyeXChanged(const QString&)), ui.lEyeX, SLOT(setText(const QString&)));
		connect(eyeCamFrameReaderThread, SIGNAL(onEyeYChanged(const QString&)), ui.lEyeY, SLOT(setText(const QString&)));

		// Set up front camera thread, connect to slots
		frontCamFrameReaderThread = new FrontCameraFrameReaderThread(this);

		connect(frontCamFrameReaderThread, SIGNAL(onCameraPixmapChanged(const QPixmap&)), ui.lFrontCam, SLOT(setPixmap(const QPixmap&)));
		connect(frontCamFrameReaderThread, SIGNAL(onCameraTextChanged(const QString&)), ui.lFrontCam, SLOT(setText(const QString&)));
		
		// Connect buttons to listeners
		connect(ui.bSetAndContinue, SIGNAL(clicked()), this, SLOT(onSetAndContinueClicked()));
		connect(ui.bTestEyeCam, SIGNAL(clicked()), this, SLOT(onTestEyeCamClicked()));
		connect(ui.bTestFrontCam, SIGNAL(clicked()), this, SLOT(onTestFrontCamClicked()));
	}

	void SelectCameraWindow::onSetAndContinueClicked()
	{
		/* Check for the different cameras to be selected */
		if(ui.cbEyeCamIndex->currentIndex() == ui.cbFrontCamIndex->currentIndex())
		{
			QMessageBox::warning(this, "Error", "Eye camera and front camera cannot be same!", QMessageBox::Ok);
		
			return;
		}
		
		setAndContinueClicked = true;

		this->close();

		//qDebug() << "Eye cam index: " << ui.cbEyeCamIndex->currentIndex() << " Front cam index: " << ui.cbFrontCamIndex->currentIndex();

		calibrationWindow->setEyeCamIndex(ui.cbEyeCamIndex->currentIndex());
		calibrationWindow->setFrontCamIndex(ui.cbFrontCamIndex->currentIndex());
		calibrationWindow->showFullScreen();
		calibrationWindow->initializeEyeTracker();
	}

	void SelectCameraWindow::onTestEyeCamClicked()
	{
		#ifndef _WIN32
			ui.lEyeCam->setText("Loading...");

			VideoCapture videoCapture(ui.cbEyeCamIndex->currentIndex());
			videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
			videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

			Mat frame;
			
			/* If camera could not be opened */
			if(!videoCapture.isOpened())
			{
				ui.lEyeCam->setText("Cannot open camera");
				qDebug() << "Capture not opened";
				return;
			}

			for( ; ; )
			{
				videoCapture.read(frame);
				ui.lEyeCam->setPixmap(QPixmap::fromImage(cvMatToQImage(frame)));
				waitKey();
			}
		#else

			// If thread is running
			if(eyeCamFrameReaderThread->isRunning())
			{
				qDebug() << "Eye Camera Thread is already running";

				// If we are already sreaming this cam, go out of there!
				if(eyeCamFrameReaderThread->getCameraIndex() == ui.cbEyeCamIndex->currentIndex())
				{
					qDebug() << "Same camera selected!";
					return;
				}

				// If a cam selected to be tested while streaming from another cam
				else
				{
					qDebug() << "Starting stream with diferent camera";
					eyeCamFrameReaderThread->terminate();
					eyeCamFrameReaderThread->setCameraIndex(ui.cbEyeCamIndex->currentIndex());
					eyeCamFrameReaderThread->start();
				}
			}

			// If thread is not started yet
			else
			{
				qDebug() << "Eye Camera Thread starting first time";
				eyeCamFrameReaderThread->setCameraIndex(ui.cbEyeCamIndex->currentIndex());
				eyeCamFrameReaderThread->start();
			}

		#endif
		return;
	}

	void SelectCameraWindow::onTestFrontCamClicked()
	{
		#ifndef _WIN32
			ui.lFrontCam->setText("Loading...");

			VideoCapture videoCapture(ui.cbFrontCamIndex->currentIndex());
			videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
			videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
			Mat frame;
			
			/* If camera could not be opened */
			if(!videoCapture.isOpened())
			{
				ui.lFrontCam->setText("Cannot open camera");
				qDebug() << "Capture not opened";
				return;
			}

			for( ; ; )
			{
				videoCapture.read(frame);
				ui.lFrontCam->setPixmap(QPixmap::fromImage(cvMatToQImage(frame)));
				waitKey();
			}
		#else
			// If thread is running
			if(frontCamFrameReaderThread->isRunning())
			{
				qDebug() << "Front Camera Thread is already running";

				// If we are already sreaming this cam, go out of there!
				if(frontCamFrameReaderThread->getCameraIndex() == ui.cbFrontCamIndex->currentIndex())
				{
					qDebug() << "Same camera selected!";
					return;
				}

				// If a cam selected to be tested while streaming from another cam
				else
				{
					qDebug() << "Starting stream with diferent camera";
					frontCamFrameReaderThread->terminate();
					frontCamFrameReaderThread->setCameraIndex(ui.cbFrontCamIndex->currentIndex());
					frontCamFrameReaderThread->start();
				}
			}

			// If thread is not started yet
			else
			{
				qDebug() << "Front Camera Thread starting first time";
				frontCamFrameReaderThread->setCameraIndex(ui.cbFrontCamIndex->currentIndex());
				frontCamFrameReaderThread->start();
			}
		#endif
		return;
	}

	void SelectCameraWindow::keyPressEvent(QKeyEvent* event)
	{
		switch(event->key())
		{
		case Qt::Key_Escape:
			this->close();
			break;
		}
	}
	
	void SelectCameraWindow::closeEvent(QCloseEvent *event)
	{
		if(setAndContinueClicked)
		{
			event->accept();
		}

		else
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

	SelectCameraWindow::~SelectCameraWindow()
	{
		// Delete eye camera reader thread
		if(eyeCamFrameReaderThread->isRunning())
		{
			eyeCamFrameReaderThread->terminate();
		}

		delete eyeCamFrameReaderThread;

		// Delete front camera reader thread
		if(frontCamFrameReaderThread->isRunning())
		{
			frontCamFrameReaderThread->terminate();
		}

		delete frontCamFrameReaderThread;
	}
}