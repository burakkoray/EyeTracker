#ifndef CALIBRATION_WINDOW_H
#define CALIBRATION_WINDOW_H

#include "EyeTrackerWindow.h"
#include "EyeTracker.h"
#include "ui_CalibrationWindow.h"
#include "CaptureDialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include <QLine>
#include <QPainter>
#include <QPaintEvent>
#include <QFrame>
#include <QKeyEvent>
#include <QFont>
#include <QPen>
#include <QColor>
#include <QPropertyAnimation>
#include <QGraphicsItemAnimation>
#include <QGraphicsScene>
#include <QPaintEngine>
#include <QApplication>
#include <QVBoxLayout>

namespace Nsk
{
	class CalibrationWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		CalibrationWindow(EyeTrackerWindow *eyeTrackerWindow, QWidget *parent = 0, Qt::WFlags flags = 0);
		int getEyeCamIndex() const { return eyeCamIndex; }
		void setEyeCamIndex(int eyeCamIndex);
		int getFrontCamIndex() const { return frontCamIndex; }
		void setFrontCamIndex(int frontCamIndex);
		void startEyeTracker();
		void initializeEyeTracker();
		~CalibrationWindow();

	protected:
		void paintEvent(QPaintEvent *event);
		void keyPressEvent(QKeyEvent* event);
		void closeEvent(QCloseEvent *event);
	
	private:
		Ui::CalibrationWindowClass ui;
		EyeTrackerWindow *eyeTrackerWindow;
		int calibrationStatus;
		int eyeCamIndex;
		int frontCamIndex;
		EyeTracker *eyeTracker;
		QPoint leftTopCircle;
		QPoint rightTopCircle;
		QPoint leftDownCircle;
		QPoint rightDownCircle;
		CaptureDialog *captureDialog;
		bool calibrationDone;
	};
}
#endif