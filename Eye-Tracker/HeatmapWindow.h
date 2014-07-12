#ifndef HEATMAP_WINDOW
#define HEATMAP_WINDOW

#include "ui_HeatmapWindow.h"
#include "Commons.h"
#include "EyeTracker.h"
#include <QThread>
#include <QLabel>
#include <QImage>
#include <QDebug>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

namespace Nsk
{
	// Front camera stream reader thread class
	class HeatmapCameraReaderThread : public QThread
	{
		Q_OBJECT;

	public:
		explicit HeatmapCameraReaderThread(QObject* parent = 0);
		int getEyeCameraIndex() const { return eyeCameraIndex; }
		void setEyeCameraIndex(int eyeCameraIndex) { this->eyeCameraIndex = eyeCameraIndex; };
		int getFrontCameraIndex() const { return frontCameraIndex; }
		void setFrontCameraIndex(int frontCameraIndex) { this->frontCameraIndex = frontCameraIndex; };
		EyeTracker *getEyeTracker() const { return eyeTracker; }
		void setEyeTracker(EyeTracker *eyeTracker) { this->eyeTracker = eyeTracker; }
		~HeatmapCameraReaderThread();
 
	signals:
		void onFrontCameraPixmapChanged(const QPixmap&);
		void onFrontCameraTextChanged(const QString&);

	protected:
		void run(void);
 
	private:
		EyeTracker *eyeTracker;
		int eyeCameraIndex;
		int frontCameraIndex;
	};

	class HeatmapWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		HeatmapWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
		void setEyeCamIndex(int eyeCamIndex);
		void setFrontCamIndex(int frontCamIndex);
		void setEyeTracker(EyeTracker *eyeTracker) { this->eyeTracker = eyeTracker; }
		~HeatmapWindow();

	protected:
		void paintEvent(QPaintEvent *event);
		void keyPressEvent(QKeyEvent* event);
		void closeEvent(QCloseEvent *event);

	private:
		Ui::HeatmapWindowClass ui;
		HeatmapCameraReaderThread *heatmapCameraReaderThread;
		EyeTracker *eyeTracker;
		int eyeCamIndex;
		int frontCamIndex;
	};
}

#endif