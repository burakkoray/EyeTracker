#ifndef INITIAL_SCREEN_H
#define INITIAL_SCREEN_H

#include "ui_InitialWindow.h"
#include "SelectCameraWindow.h"
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
#include <QDebug>

namespace Nsk
{
	class InitialWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		InitialWindow(SelectCameraWindow *selectCameraWindow, QWidget *parent = 0, Qt::WFlags flags = 0);
		~InitialWindow();

	private:
		Ui::InitialWindowClass ui;
		SelectCameraWindow *selectCameraWindow;
		//EyeTracker *selectCameraDialog;

	private slots:
		void onCalibrateButtonClicked();
	};
}

#endif