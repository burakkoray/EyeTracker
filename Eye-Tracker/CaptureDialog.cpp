#include "CaptureDialog.h"

namespace Nsk
{
	CaptureDialog::CaptureDialog(QWidget * parent, Qt::WindowFlags flags)
		: QDialog(parent, flags)
	{
		ui.setupUi(this);
		this->setWindowTitle("Captured Frame");
		enterOrEscPressed = false;
	}

	void CaptureDialog::setEyeFrame(QImage eyeFrame)
	{
		ui.lEyeFrame->setPixmap(QPixmap::fromImage(eyeFrame));
	}

	void CaptureDialog::setEyePoint(CvPoint2D32f eyePoint)
	{
		char xStr[50], yStr[50];

		sprintf(xStr, "%.1f", eyePoint.x);
		sprintf(yStr, "%.1f", eyePoint.y);

		ui.lEyeX->setText(xStr);
		ui.lEyeY->setText(yStr);
	}

	CaptureDialog::~CaptureDialog()
	{

	}

	void CaptureDialog::keyPressEvent(QKeyEvent *e)
	{
		switch(e->key())
		{
		case Qt::Key_Enter: case Qt::Key_Return:
			this->setReturnValue(RESULT_ACCEPTED);
			this->enterOrEscPressed = true;
			qDebug() << "Result is accepted";
			this->close();
			break;

		case Qt::Key_Escape:
			qDebug() << "Result is ignored";
			this->setReturnValue(RESULT_IGNORED);
			this->enterOrEscPressed = true;
			this->close();
			break;

		default:
			this->enterOrEscPressed = false;
			break;
		}
	}

	void CaptureDialog::closeEvent(QCloseEvent *event)
	{
		if(enterOrEscPressed)
		{
			this->enterOrEscPressed = false;
		}

		else
		{
			this->setReturnValue(RESULT_IGNORED);
		}

		event->accept();
	}
}