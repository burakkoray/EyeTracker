#ifndef SELECT_CAMERA_DIALOG_H
#define SELECT_CAMERA_DIALOG_H

#include "ui_SelectCameraWindow.h"
#include "CalibrationWindow.h"
#include "Commons.h"
#include <QMainWindow>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <QDialog>
#include <QDebug>
#include <QThread>
#include <QComboBox>

namespace Nsk
{
	class SelectCameraWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		SelectCameraWindow(CalibrationWindow *calibrationWindow, QWidget *parent = 0, Qt::WFlags flags = 0);
		~SelectCameraWindow();

	protected:
		void keyPressEvent(QKeyEvent* event);
		void closeEvent(QCloseEvent *event);

	private:
		Ui::SelectCameraWindowClass ui;
		CalibrationWindow *calibrationWindow;
		EyeCameraFrameReaderThread *eyeCamFrameReaderThread;
		FrontCameraFrameReaderThread *frontCamFrameReaderThread;
		bool setAndContinueClicked;

	private slots:
		void onSetAndContinueClicked();
		void onTestEyeCamClicked();
		void onTestFrontCamClicked();
	};
}

#endif