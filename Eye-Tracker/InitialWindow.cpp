#include "InitialWindow.h"
#include "EyeTrackerWindow.h"
#include <QPainter>
#include <QDialog>
#include <QImage>
#include <QScrollArea>
#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
#include <QMenuBar>
#include <QtWebKit/QWebView>
#include <QDesktopServices>
#include <cstring>

namespace Nsk
{
	InitialWindow::InitialWindow(SelectCameraWindow *selectCameraWindow, QWidget *parent, Qt::WFlags flags) 
					: QMainWindow(parent, flags), selectCameraWindow(selectCameraWindow)
	{
		this->ui.setupUi(this);
		this->setWindowTitle("Warning");

		this->setWindowIcon(QIcon("Images/warning.png"));
		this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
		//this->selectCameraDialog = selectCameraDialog;

		/*
		ui.webView->load(QUrl(tr("index.html")));
		
		QDialog d(this);

		QWebView wv(&d);
		/*
		QWebPage *wp = wv.page();
		QWebSettings *settings = wp->settings();
		settings->setAttribute(QWebSettings::JavascriptEnabled, true);
		settings->setAttribute(QWebSettings::PluginsEnabled, false);
		settings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, false);
		settings->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, false);
		settings->setAttribute(QWebSettings::LocalStorageEnabled, false);
		settings->setAttribute(QWebSettings::AutoLoadImages, false);
		settings->setAttribute(QWebSettings::JavascriptCanAccessClipboard, false);
		settings->setAttribute(QWebSettings::JavascriptCanOpenWindows, false);
		settings->setAttribute(QWebSettings::JavaEnabled, false);
		settings->setAttribute(QWebSettings::AcceleratedCompositingEnabled, false);
		settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, false);
		settings->setAttribute(QWebSettings::FrameFlatteningEnabled, false);
		settings->setAttribute(QWebSettings::XSSAuditingEnabled, false);
		settings->setAttribute(QWebSettings::TiledBackingStoreEnabled, false);
		wv.load(QUrl(tr("index.html")));
		*/
		//QDesktopServices::openUrl ( QUrl(tr("index.html")));
		
		//d.exec();

		connect(ui.bCalibrate, SIGNAL(clicked()), this, SLOT(onCalibrateButtonClicked()));
	}
	
	InitialWindow::~InitialWindow()
	{
		
	}

	void InitialWindow::onCalibrateButtonClicked()
	{
		//WindowContainer::selectCameraDialog->show();
		this->close();
		selectCameraWindow->show();


		/*

		int dialogWidth = 400, dialogHeight = 300;

		QRect dialogGeo;

		dialogGeo.setX(this->geometry().x() + (this->geometry().width() - dialogWidth) / 2);
		dialogGeo.setY(this->geometry().y() + (this->geometry().height() - dialogHeight) / 2);
		dialogGeo.setWidth(dialogWidth);
		dialogGeo.setHeight(dialogHeight);
		
		
		dialog.setGeometry(dialogGeo);

		QGroupBox groupBox(&dialog);
		groupBox.setTitle("Choose camera");
		
		groupBox.setGeometry(5, 5, 
							dialog.geometry().width() - 10,
							dialog.geometry().height() - 10);

		QHBoxLayout layout(&groupBox);

		QComboBox comboBox;
		
		comboBox.addItem("0");
		comboBox.addItem("1");
		comboBox.addItem("2");
		//comboBox.setGeometry(40, 50, comboBox.geometry().width() - 10, comboBox.geometry().height() - 10);
		
		QPushButton save;

		save.setText("Save and continue");
		save.setGeometry(groupBox.geometry().x() + 20,  groupBox.geometry().y() + 200, 
						groupBox.geometry().width() - 40, groupBox.geometry().height() - 220);
		
		QLabel l;
		l.setText("Hello");

		layout.addWidget(&l);
		layout.addWidget(&comboBox);
		
		QVBoxLayout v(&groupBox);

		v.addLayout(&layout);
		v.addWidget(&save);

		dialog.exec();

		/* Calibration window..
		dialog.showFullScreen();
		dialog.setWindowTitle("Choose camera");
		
		QLabel label(&dialog);
		label.setVisible(true);
		label.setGeometry(dialog.geometry());
		label.setPixmap(QPixmap(dialog.geometry().width(), dialog.geometry().height()));

		QImage tmp(label.pixmap()->toImage());

		QPen paintpen(Qt::black);
        paintpen.setWidth(10);

		QPainter painter(&tmp);
		painter.setPen(paintpen);
		painter.drawEllipse(QPoint(10, 10), 50, 50); 
		painter.drawLine(QPoint(0, 200), QPoint(dialog.geometry().width(), 200));
		

		label.setPixmap(QPixmap::fromImage(tmp));
		
		
		/*
		QGraphicsView v(&dialog);

		v.setGeometry(200, 200, 700, 700);
		
		QGraphicsScene s(0,0, 400, 400, &dialog);

		v.setScene(&s);

		s.addEllipse(0, 0, 200, 200);
		
		QPropertyAnimation animation(&v, "geometry");
		
		animation.setDuration(1000);
		

		animation.setStartValue(QRect(200, 200, 200, 200));
		animation.setEndValue(QRect(300, 300, 0, 0));

		animation.start();
		
		dialog.exec();
		*/
	}
}