#ifndef EYE_TRACKER_WINDOW_H
#define EYE_TRACKER_WINDOW_H

#include "ui_EyeTrackerWindow.h"
#include "ui_AboutDialog.h"
#include "HeatmapWindow.h"
#include "HangmanWindow.h"
#include "EyeTracker.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QtGui/QMainWindow>

using namespace cv;

namespace Nsk
{
	class EyeTrackerWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		EyeTrackerWindow(HeatmapWindow* heatmapWindow, HangmanWindow *hangmanWindow, QWidget *parent = 0, Qt::WFlags flags = 0);
		int getEyeCamIndex() const { return eyeCamIndex; }
		int getFrontCamIndex() const { return frontCamIndex; }
		void setEyeCamIndex(int eyeCamIndex);
		void setFrontCamIndex(int frontCamIndex);
		void setEyeTracker(EyeTracker *eyeTracker) { this->eyeTracker = eyeTracker; }
		~EyeTrackerWindow();

	protected:
		void keyPressEvent(QKeyEvent* event);
		void closeEvent(QCloseEvent *event);

	private:
		Ui::EyeTrackerWindowClass ui;
		HeatmapWindow *heatmapWindow;
		HangmanWindow *hangmanWindow;
		int eyeCamIndex;
		int frontCamIndex;
		EyeTracker *eyeTracker;
		bool mouseTrackingActive;
		Point2f previousEyePoint;
		bool previousEyePointExists;
	
	private slots:
		void onTestEyeTrackingClicked();
		void onAboutClicked();
		void onHelpClicked();
		void onStartHangmanGameClicked();
		void onStartHeatmapApplicationClicked();
	};
}

#endif // EYE_TRACKER_WINDOW_H