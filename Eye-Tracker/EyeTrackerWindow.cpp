#include "EyeTrackerWindow.h"
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QMessageBox>
#include <QThread>
#include <QInputDialog>
#include <QDebug>
#include <QMouseEvent>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>

namespace Nsk
{
	EyeTrackerWindow::EyeTrackerWindow(HeatmapWindow *heatmapWindow, HangmanWindow *hangmanWindow, QWidget *parent, Qt::WFlags flags)
		: QMainWindow(parent, flags), heatmapWindow(heatmapWindow), hangmanWindow(hangmanWindow), previousEyePoint(0, 0)
	{
		this->ui.setupUi(this);
		this->setWindowIcon(QIcon("Images/eyetracker_icon.png"));
		this->mouseTrackingActive = false;
		this->previousEyePointExists = false;

		/* Connect buttons onclick listeners */
		this->connect(ui.bTestTracking, SIGNAL(clicked()), this, SLOT(onTestEyeTrackingClicked()));
		this->connect(ui.bAbout, SIGNAL(clicked()), this, SLOT(onAboutClicked()));
		this->connect(ui.bHelp, SIGNAL(clicked()), this, SLOT(onHelpClicked()));
		this->connect(ui.bStartHangmanGame, SIGNAL(clicked()), this, SLOT(onStartHangmanGameClicked()));
		this->connect(ui.bStartHeatmapApplication, SIGNAL(clicked()), this, SLOT(onStartHeatmapApplicationClicked()));
	}

	void EyeTrackerWindow::setEyeCamIndex(int eyeCamIndex)
	{
		if(eyeCamIndex < 0)
		{
			qDebug() << "Eye cam index cannot be negative!";
			throw -1;
		}

		this->eyeCamIndex = eyeCamIndex;
	}
	
	void EyeTrackerWindow::setFrontCamIndex(int frontCamIndex)
	{
		if(frontCamIndex < 0)
		{
			qDebug() << "Front cam index cannot be negative!";
			throw -1;
		}

		this->frontCamIndex = frontCamIndex;
	}

	void EyeTrackerWindow::onTestEyeTrackingClicked()
	{
		/*
		bool isSetCameras = true;
		
		qDebug() << "Eye cam index: " << eyeCamIndex << " Front cam index: " << frontCamIndex;
		EyeTracker *eyeTracker = new EyeTracker(eyeCamIndex, frontCamIndex);
	
		eyeTracker->showWindows();
		eyeTracker->startTracker();
		eyeTracker->hideWindow();

		delete eyeTracker;*/

		mouseTrackingActive = true;

		while(mouseTrackingActive)
		{
			Point2f eyePoint = eyeTracker->getEyePointOnWindow();

			/* This is first enterance in this code. */
			if(!previousEyePointExists)
			{
				qDebug() << "First enterance!";

				this->cursor().setPos(QPoint(eyePoint.x, eyePoint.y));

				previousEyePointExists = true;

				qDebug() << "x: " << eyePoint.x << " y: " << eyePoint.y;
			}
			
			else
			{
				double x1 = previousEyePoint.x, x2 = eyePoint.x,
						y1 = previousEyePoint.y, y2 = eyePoint.y;

				/* Ths increment number for traversing the line between two points. */
				int incNum = x1 > x2 ? -1 : +1;

				this->cursor().setPos(QPoint(eyePoint.x, eyePoint.y));

				/* Traverse the line */
				for(int i = x1; !approximatelyEquals(i, x2, 0); i += incNum)
				{
					double x, y;

					x = i;
					y = (y2 - y1) * (x - x2) / (x2 - x1) + y2;

					this->cursor().setPos(QPoint(x, y));
					
					qDebug() << "x: " << x << " y: " << y;
				}
			}

			previousEyePoint = eyePoint;
		}

		//qDebug() << "x: " << eyePoint.x << " y: " << eyePoint.y;
	}

	void EyeTrackerWindow::onAboutClicked()
	{
		QDialog *dialog = new QDialog(this);
		
		Ui::AboudDialogClass aboutDialogUi;

		aboutDialogUi.setupUi(dialog);

		dialog->exec();
	}

	void EyeTrackerWindow::onHelpClicked()
	{
		
	}

	void EyeTrackerWindow::onStartHangmanGameClicked()
	{
		hangmanWindow->setEyeTracker(eyeTracker);
		hangmanWindow->showMaximized();
	}

	void EyeTrackerWindow::onStartHeatmapApplicationClicked()
	{
		heatmapWindow->setEyeTracker(eyeTracker);
		heatmapWindow->setEyeCamIndex(eyeCamIndex);
		heatmapWindow->setFrontCamIndex(frontCamIndex);
		heatmapWindow->showFullScreen();
	}

	EyeTrackerWindow::~EyeTrackerWindow()
	{
		
	}

	void EyeTrackerWindow::keyPressEvent(QKeyEvent* event)
	{
		switch(event->key())
		{
		case Qt::Key_Escape:
			mouseTrackingActive = false;
			
			this->close();
			break;
		}
	}

	void EyeTrackerWindow::closeEvent (QCloseEvent *event)
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