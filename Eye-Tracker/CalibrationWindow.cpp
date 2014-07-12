#include "CalibrationWindow.h"

namespace Nsk
{
	const int CALIBRATION_POINT_LEFT_TOP_CORNER = 0;
	const int CALIBRATION_POINT_RIGHT_TOP_CORNER = 1;
	const int CALIBRATION_POINT_LEFT_DOWN_CORNER = 2;
	const int CALIBRATION_POINT_RIGHT_DOWN_CORNER = 3;
	const int CALIBRATION_POINT_END = 4;
	
	CalibrationWindow::CalibrationWindow(EyeTrackerWindow *eyeTrackerWindow, QWidget *parent, Qt::WFlags flags)
				: QMainWindow(parent, flags), eyeTrackerWindow(eyeTrackerWindow)
	{
		this->ui.setupUi(this);
		this->setWindowTitle("Calibration");
		this->setWindowIcon(QIcon("Images/calibration_icon.png"));
		this->calibrationDone = false;
		
		this->eyeTracker = new EyeTracker();
		this->captureDialog = new CaptureDialog(this);
		this->captureDialog->setWindowIcon(QIcon("Images/select_icon.png"));
		this->calibrationStatus = CALIBRATION_POINT_LEFT_TOP_CORNER;
	}

	void CalibrationWindow::setEyeCamIndex(int newEyeCamIndex)
	{
		if(newEyeCamIndex < 0)
		{
			qDebug() << "Eye cam index cannot be negative!";
			throw -1;
		}

		this->eyeCamIndex = newEyeCamIndex;
		eyeTracker->setEyeCamIndex(newEyeCamIndex);
	}

	void CalibrationWindow::initializeEyeTracker()
	{
		leftTopCircle = QPoint(50, 50),
		rightTopCircle = QPoint(this->geometry().width() - this->geometry().width() % 50, 50),
		leftDownCircle = QPoint(50, this->geometry().height() - this->geometry().height() % 50),
		rightDownCircle = QPoint(this->geometry().width() - this->geometry().width() % 50, this->geometry().height() - this->geometry().height() % 50);

		/* Set calirator window points. */
		eyeTracker->getCalibrator()->setWindowLeftTopCorner(Point2f(0.0, 0.0));
		eyeTracker->getCalibrator()->setWindowRightTopCorner(Point2f((double) this->geometry().width(), 0.0));
		eyeTracker->getCalibrator()->setWindowLeftDownCorner(Point2f(0.0, (double)this->geometry().height()));
		eyeTracker->getCalibrator()->setWindowRightDownCorner(Point2f((double)this->geometry().width(), (double)this->geometry().height()));
		
		eyeTracker->initialize();
	}

	void CalibrationWindow::setFrontCamIndex(int newFrontCamIndex)
	{
		if(newFrontCamIndex < 0)
		{
			qDebug() << "Front cam index cannot be negative!";
			throw 1;
		}

		this->frontCamIndex = newFrontCamIndex;
		eyeTracker->setFrontCamIndex(frontCamIndex);
	}

	void CalibrationWindow::paintEvent(QPaintEvent *event)
	{
		//qDebug() << this->geometry().width() << " " << this->geometry().height();
		
		QFont font;
		int left, top, width, height;

		/* Set up calibration status position */
		width = this->geometry().width() * 0.7;
		height = this->geometry().height() * 0.3;
		left = (this->geometry().width() - width) / 2;
		top = (this->geometry().height() - height) / 2;

		ui.lCalibrationStatus->setGeometry(left, top, width, height);
		font.setFamily(ui.lCalibrationStatus->font().family());
		font.setPointSize(width * 0.028);
		ui.lCalibrationStatus->setFont(font);

		/* Set up marker position */
		width = this->geometry().width() * 0.15;
		height = this->geometry().width() * 0.15;
		left = (this->geometry().width() - width) / 2;
		top = this->geometry().height() - height;
	
		ui.lMarker->setGeometry(QRect(left, top, width, height));

		QPainter *painter = new QPainter(this);
		int radious = 25;

		painter->setPen(QPen(QColor(170, 170, 170)));
		painter->setBrush(QBrush(Qt::red));

		width = this->geometry().width() * this->geometry().height() * 0.00012;
		height = this->geometry().width() * this->geometry().height() * 0.00007;
		font.setFamily(ui.lEyeLeftTop->font().family());
		font.setPointSize(width * 0.15);

		/* Set up left top eye corner coordinate text position */
		left = 0;
		top = leftTopCircle.y() + radious;
		ui.lEyeLeftTop->setGeometry(left, top, width, height);
		ui.lEyeLeftTop->setFont(font);
		
		/* Set up right top eye corner coordinate text position */
		left = this->geometry().width() - width;
		top = rightTopCircle.y() + radious;
		ui.lEyeRightTop->setGeometry(left, top, width, height);
		ui.lEyeRightTop->setFont(font);

		/* Set up left down eye corner coordinate text position */
		left = 0;
		top = this->geometry().height() - 2 * radious - height;
		ui.lEyeLeftDown->setGeometry(left, top, width, height);
		ui.lEyeLeftDown->setFont(font);

		/* Set up right down eye corner coordinate text position */
		left = this->geometry().width() - width;
		top = this->geometry().height() - 2 * radious - height;
		ui.lEyeRightDown->setGeometry(left, top, width, height);
		ui.lEyeRightDown->setFont(font);

		char text[50];
		Point2f eyePoint;

		/* Draw circles */
		leftTopCircle = QPoint(50, 50),
		rightTopCircle = QPoint(this->geometry().width() - this->geometry().width() % 50, 50),
		leftDownCircle = QPoint(50, this->geometry().height() - this->geometry().height() % 50),
		rightDownCircle = QPoint(this->geometry().width() - this->geometry().width() % 50, this->geometry().height() - this->geometry().height() % 50);

		switch(calibrationStatus)
		{
		case CALIBRATION_POINT_LEFT_TOP_CORNER:
			ui.lCalibrationStatus->setText("Please look at left top circle and then press enter...");
			painter->drawEllipse(leftTopCircle, radious, radious);
			painter->drawEllipse(rightTopCircle, radious, radious);
			painter->drawEllipse(leftDownCircle, radious, radious);
			painter->drawEllipse(rightDownCircle, radious, radious);
			//eyeTracker.calibrateLeftTopCorner();
			break;

		case CALIBRATION_POINT_RIGHT_TOP_CORNER:
			ui.lCalibrationStatus->setText("Please look at right top circle and then press enter...");
			painter->drawEllipse(rightTopCircle, radious, radious);
			painter->drawEllipse(leftDownCircle, radious, radious);
			painter->drawEllipse(rightDownCircle, radious, radious);
			painter->setBrush(QBrush(Qt::green));
			painter->drawEllipse(leftTopCircle, radious, radious);

			eyePoint = eyeTracker->getCalibrator()->getEyeLeftTopCorner();
			sprintf(text, "x: %.1f \ny: %.1f", eyePoint.x, eyePoint.y);

			ui.lEyeLeftTop->setText(text);
			ui.lEyeLeftTop->setStyleSheet("color: rgb(0, 255, 0)");
			//eyeTracker.calibrateRightTopCorner();
			break;

		case CALIBRATION_POINT_LEFT_DOWN_CORNER:
			ui.lCalibrationStatus->setText("Please look at left down circle and then press enter...");
			painter->drawEllipse(rightDownCircle, radious, radious);
			painter->drawEllipse(leftDownCircle, radious, radious);
			painter->setBrush(QBrush(Qt::green));
			painter->drawEllipse(leftTopCircle, radious, radious);
			painter->drawEllipse(rightTopCircle, radious, radious);

			eyePoint = eyeTracker->getCalibrator()->getEyeRightTopCorner();
			sprintf(text, "x: %.1f \ny: %.1f", eyePoint.x, eyePoint.y);

			ui.lEyeRightTop->setText(text);
			ui.lEyeRightTop->setStyleSheet("color: rgb(0, 255, 0)");
			//eyeTracker.calibrateLeftDownCorner();
			break;
			
		case CALIBRATION_POINT_RIGHT_DOWN_CORNER:
			ui.lCalibrationStatus->setText("Please look at right down circle and then press enter...");
			painter->drawEllipse(rightDownCircle, radious, radious);
			painter->setBrush(QBrush(Qt::green));
			painter->drawEllipse(leftTopCircle, radious, radious);
			painter->drawEllipse(rightTopCircle, radious, radious);
			painter->drawEllipse(leftDownCircle, radious, radious);

			eyePoint = eyeTracker->getCalibrator()->getEyeLeftDownCorner();
			sprintf(text, "x: %.1f \ny: %.1f", eyePoint.x, eyePoint.y);

			ui.lEyeLeftDown->setText(text);
			ui.lEyeLeftDown->setStyleSheet("color: rgb(0, 255, 0)");
			//eyeTracker.calibrateRightDownCorner();
			break;

		case CALIBRATION_POINT_END:
			ui.lCalibrationStatus->setText("Calibration completed successfully. \nPress enter to start eye tracker...");
			painter->setBrush(QBrush(Qt::green));
			painter->drawEllipse(leftTopCircle, radious, radious);
			painter->drawEllipse(rightTopCircle, radious, radious);
			painter->drawEllipse(leftDownCircle, radious, radious);
			painter->drawEllipse(rightDownCircle, radious, radious);

			eyePoint = eyeTracker->getCalibrator()->getEyeRightDownCorner();
			sprintf(text, "x: %.1f \ny: %.1f", eyePoint.x, eyePoint.y);

			ui.lEyeRightDown->setText(text);
			ui.lEyeRightDown->setStyleSheet("color: rgb(0, 255, 0)");
			//eyeTracker.calibrate();
			break;
		}

		/* Draw vertical lines. */
		for(int i = 50; i < this->geometry().width(); i = i + 50)
		{
			painter->drawLine(i, 0, i, this->geometry().height());
		}

		/* Draw horizontal lines. */
		for(int i = 50; i < this->geometry().height(); i = i + 50)
		{
			painter->drawLine(0, i, this->geometry().width(), i);
		}

		delete painter;
	}

	void CalibrationWindow::keyPressEvent(QKeyEvent* event)
	{
		switch(event->key())
		{
		/* Pressing Escape key */
		case Qt::Key_Escape:
			this->close();
			break;

		/* Pressing Enter key */
		case Qt::Key_Enter: case Qt::Key_Return:
			/* If calibration is not finished */
			if(calibrationStatus != CALIBRATION_POINT_END)
			{
				/* Capture images */
				eyeTracker->captureEyeFrame();
				eyeTracker->captureSceneFrame();

				Point2f eyePoint = eyeTracker->doTrack();

				/* Set eye point */
				captureDialog->setEyePoint(eyePoint);

				/* Draw squares to eye image */
				//eyeTracker->drawTrasholds();
				eyeTracker->drawSquares(eyeTracker->findSquares());
			
				/* Set eye pixmap */
				captureDialog->setEyeFrame(cvMatToQImage(cvarrToMat(eyeTracker->getEyeImage())));
				
				/* Release images */
				eyeTracker->releaseGrayEyeImage();
				eyeTracker->releaseGraySceneImage();

				captureDialog->exec();
			
				qDebug() << captureDialog->getReturnValue();

				if(captureDialog->getReturnValue() == RESULT_IGNORED)
				{
					qDebug() << "Result is ignored in calibration window";
					return;
				}

				qDebug() << "Result is accepted in calibration window";

				switch(calibrationStatus)
				{
				case CALIBRATION_POINT_LEFT_TOP_CORNER:
					eyeTracker->calibrateLeftTopCorner(eyePoint);
					break;

				case CALIBRATION_POINT_RIGHT_TOP_CORNER:
					eyeTracker->calibrateRightTopCorner(eyePoint);
					break;

				case CALIBRATION_POINT_LEFT_DOWN_CORNER:
					eyeTracker->calibrateLeftDownCorner(eyePoint);
					break;
			
				case CALIBRATION_POINT_RIGHT_DOWN_CORNER:
					eyeTracker->calibrateRightDownCorner(eyePoint);
					break;
				}
				++calibrationStatus;
				update();
			}

			/* If calibration is finished */
			else
			{
				eyeTracker->calibrate();
				startEyeTracker();
			}

			break;
		}

		event->ignore();
	}

	void CalibrationWindow::closeEvent(QCloseEvent *event)
	{
		if(calibrationDone)
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

	void CalibrationWindow::startEyeTracker()
	{
		calibrationDone = true;

		this->close();

		qDebug() << "Eye cam index: " << eyeCamIndex << " Front cam index: " << frontCamIndex;

		eyeTrackerWindow->setEyeTracker(eyeTracker);
		eyeTrackerWindow->setEyeCamIndex(eyeCamIndex);
		eyeTrackerWindow->setFrontCamIndex(frontCamIndex);
		eyeTrackerWindow->show();
	}

	CalibrationWindow::~CalibrationWindow()
	{
	
	}
}    