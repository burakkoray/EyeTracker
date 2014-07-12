#ifndef CAPTURE_DIALOG_H
#define CAPTURE_DIALOG_H

#include "ui_CaptureDialog.h"
#include <QDialog>
#include <QWidget>
#include <QKeyEvent>
#include <QDebug>
#include <opencv/cv.h>

#define RESULT_ACCEPTED 0
#define RESULT_IGNORED 1

using namespace cv;

namespace Nsk
{
	class CaptureDialog : public QDialog
	{
		Q_OBJECT

	public:
		CaptureDialog(QWidget * parent = 0, Qt::WindowFlags flags = 0);
		void setEyeFrame(QImage image);
		void setEyePoint(CvPoint2D32f eyePoint);
		void setReturnValue(int returnValue) { this->returnValue = returnValue; }
		int getReturnValue() { return returnValue; }
		~CaptureDialog();

	protected:
		void keyPressEvent(QKeyEvent *e);
		void closeEvent(QCloseEvent *event);

	private:
		Ui::CaptureDialogClass ui;
		int returnValue;
		bool enterOrEscPressed;
	};
}

#endif
