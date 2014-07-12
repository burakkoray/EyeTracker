#include <QtGui/QApplication>
#include <QDesktopWidget>
#include "SelectCameraWindow.h"
#include "InitialWindow.h"
#include "EyeTrackerWindow.h"
#include "CalibrationWindow.h"
#include "HeatmapWindow.h"
#include "HangmanWindow.h"

using namespace Nsk;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	HeatmapWindow heatmapWindow;
	heatmapWindow.move(QApplication::desktop()->screen()->rect().center() - heatmapWindow.geometry().center());

	HangmanWindow hangmanWindow;
	hangmanWindow.move(QApplication::desktop()->screen()->rect().center() - hangmanWindow.geometry().center());
	
	EyeTrackerWindow eyeTrackerWindow(&heatmapWindow, &hangmanWindow);
	eyeTrackerWindow.move(QApplication::desktop()->screen()->rect().center() - eyeTrackerWindow.geometry().center());
	
	CalibrationWindow calibrationWindow(&eyeTrackerWindow);
	calibrationWindow.move(QApplication::desktop()->screen()->rect().center() - calibrationWindow.geometry().center());
	
	SelectCameraWindow selectCameraWindow(&calibrationWindow);
	selectCameraWindow.move(QApplication::desktop()->screen()->rect().center() - selectCameraWindow.geometry().center());

	InitialWindow initialWindow(&selectCameraWindow);
	initialWindow.move(QApplication::desktop()->screen()->rect().center() - initialWindow.geometry().center());

	initialWindow.show();
	//selectCameraWindow.show();
	/*
	calibrationWindow.showFullScreen();
	calibrationWindow.setEyeCamIndex(2);
	calibrationWindow.setFrontCamIndex(1);
	calibrationWindow.initializeEyeTracker();
	*/
	//eyeTrackerWindow.show();

	/*
	heatmapWindow.setEyeCamIndex(2);
	heatmapWindow.setFrontCamIndex(1);
	heatmapWindow.showFullScreen();

	EyeTracker *eyeTracker = new EyeTracker();
	eyeTracker->setEyeCamIndex(2);
	eyeTracker->setFrontCamIndex(1);
	eyeTracker->getCalibrator()->setWindowLeftTopCorner(Point2f(0, 0));
	eyeTracker->getCalibrator()->setWindowRightTopCorner(Point2f(640, 0));
	eyeTracker->getCalibrator()->setWindowLeftDownCorner(Point2f(0, 480));
	eyeTracker->getCalibrator()->setWindowRightDownCorner(Point2f(640, 480));
	eyeTracker->initialize();

	heatmapWindow.setEyeTracker(eyeTracker);
	*/

	//hangmanWindow.showMaximized();
	
	return a.exec();
}