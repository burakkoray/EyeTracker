#include "HangmanWindow.h"
#include <stdlib.h>
#include <QPoint>
#include <iostream>
#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>
#include <QSplashScreen>
#include <QTimer>
#include "SelectCameraWindow.h"

using namespace std;

namespace Nsk
{
	MouseMoverThread::MouseMoverThread(QObject* parent)	: QThread(parent)
	{
		// Intentionally empty
	}

	MouseMoverThread::~MouseMoverThread()
	{
		// Intentionally empty
	}
 
	void MouseMoverThread::run(void)
	{
		for( ; ; )
		{
			Point2f p = eyeTracker->getEyePointOnWindow();

			QCursor::setPos(QPoint(p.x, p.y));
		}
	}

	HangmanWindow::HangmanWindow(QWidget *parent, Qt::WFlags flags) 
				: QMainWindow(parent, flags)
	{
		mouseMoverThread = new MouseMoverThread(this);

		valuef = 1;
		word = "AN";
		words[0]="AKYAKA";
		words[1]="SUSUZ";
		words[2]="ARPACAY";
		words[3]="SARIKAMIS";
		words[4]="SEVEN";
		words[5]="DIGOR";

		QCoor[0] = 120;  // X1, Y1, X2, Y2
		WCoor[0] = 230;
		ECoor[0] = 340;
		RCoor[0] = 450;
		TCoor[0] = 560;
		YCoor[0] = 670;
		UCoor[0] = 780;
		ICoor[0] = 890;
		OCoor[0] = 1000;
		PCoor[0] = 1110;
		ACoor[0] = 180;
		SCoor[0] = 290;
		DCoor[0] = 400;
		FCoor[0] = 510;
		GCoor[0] = 620;
		HCoor[0] = 730;
		JCoor[0] = 840;
		KCoor[0] = 950;
		LCoor[0] = 1060;
		ZCoor[0] = 290;
		XCoor[0] = 400;
		CCoor[0] = 510;
		VCoor[0] = 620;
		BCoor[0] = 730;
		NCoor[0] = 840;
		MCoor[0] = 950;
		startCoor[0] = 110; 
		exitCoor[0] = 210;

		QCoor[1] = 330;  // X1, Y1, X2, Y2
		WCoor[1] = 330;
		ECoor[1] = 330;
		RCoor[1] = 330;
		TCoor[1] = 330;
		YCoor[1] = 330;
		UCoor[1] = 330;
		ICoor[1] = 330;
		OCoor[1] = 330;
		PCoor[1] = 330;
		ACoor[1] = 395;
		SCoor[1] = 395;
		DCoor[1] = 395;
		FCoor[1] = 395;
		GCoor[1] = 395;
		HCoor[1] = 395;
		JCoor[1] = 395;
		KCoor[1] = 395;
		LCoor[1] = 395;
		ZCoor[1] = 460;
		XCoor[1] = 460;
		CCoor[1] = 460;
		VCoor[1] = 460;
		BCoor[1] = 460;
		NCoor[1] = 460;
		MCoor[1] = 460;
		startCoor[1] = 40;
		exitCoor[1] = 40;

		QCoor[2] = 230;  // X1, Y1, X2, Y2
		WCoor[2] = 340;
		ECoor[2] = 450;
		RCoor[2] = 560;
		TCoor[2] = 670;
		YCoor[2] = 780;
		UCoor[2] = 890;
		ICoor[2] = 1000;
		OCoor[2] = 1110;
		PCoor[2] = 1220;
		ACoor[2] = 290;
		SCoor[2] = 400;
		DCoor[2] = 510;
		FCoor[2] = 620;
		GCoor[2] = 730;
		HCoor[2] = 840;
		JCoor[2] = 950;
		KCoor[2] = 1060;
		LCoor[2] = 1170;
		ZCoor[2] = 400;
		XCoor[2] = 510;
		CCoor[2] = 620;
		VCoor[2] = 730;
		BCoor[2] = 840;
		NCoor[2] = 950;
		MCoor[2] = 1060;
		startCoor[2] = 210;
		exitCoor[2] = 310;


		QCoor[3] = 395;  // X1, Y1, X2, Y2
		WCoor[3] = 395;
		ECoor[3] = 395;
		RCoor[3] = 395;
		TCoor[3] = 395;
		YCoor[3] = 395;
		UCoor[3] = 395;
		ICoor[3] = 395;
		OCoor[3] = 395;
		PCoor[3] = 395;
		ACoor[3] = 460;
		SCoor[3] = 460;
		DCoor[3] = 460;
		FCoor[3] = 460;
		GCoor[3] = 460;
		HCoor[3] = 460;
		JCoor[3] = 460;
		KCoor[3] = 460;
		LCoor[3] = 460;
		ZCoor[3] = 525;
		XCoor[3] = 525;
		CCoor[3] = 525;
		VCoor[3] = 525;
		BCoor[3] = 525;
		NCoor[3] = 525;
		MCoor[3] = 525;
		startCoor[3] = 75;
		exitCoor[3] = 75;

		ui.setupUi(this);
		ui.groupBox->setStyleSheet("background-color:grey;");
		ui.pushButton->setStyleSheet("background-color:white;");
		ui.pushButton_2->setStyleSheet("background-color:white;");
		ui.pushButton_3->setStyleSheet("background-color:white;");
		ui.pushButton_4->setStyleSheet("background-color:white;");
		ui.pushButton_5->setStyleSheet("background-color:white;");
		ui.pushButton_6->setStyleSheet("background-color:white;");
		ui.pushButton_7->setStyleSheet("background-color:white;");
		ui.pushButton_8->setStyleSheet("background-color:white;");
		ui.pushButton_9->setStyleSheet("background-color:white;");
		ui.pushButton_10->setStyleSheet("background-color:white;");
		ui.pushButton_11->setStyleSheet("background-color:white;");
		ui.pushButton_12->setStyleSheet("background-color:white;");
		ui.pushButton_13->setStyleSheet("background-color:white;");
		ui.pushButton_14->setStyleSheet("background-color:white;");
		ui.pushButton_15->setStyleSheet("background-color:white;");
		ui.pushButton_16->setStyleSheet("background-color:white;");
		ui.pushButton_17->setStyleSheet("background-color:white;");
		ui.pushButton_18->setStyleSheet("background-color:white;");
		ui.pushButton_19->setStyleSheet("background-color:white;");
		ui.pushButton_20->setStyleSheet("background-color:white;");
		ui.pushButton_21->setStyleSheet("background-color:white;");
		ui.pushButton_22->setStyleSheet("background-color:white;");
		ui.pushButton_23->setStyleSheet("background-color:white;");
		ui.pushButton_24->setStyleSheet("background-color:white;");
		ui.pushButton_25->setStyleSheet("background-color:white;");
		ui.pushButton_26->setStyleSheet("background-color:white;");
		
		QPixmap pix("Images/77.png");
		ui.label_3->setPixmap(pix);
		on_action_triggered();
	}

	HangmanWindow::~HangmanWindow()
	{
		// Intentionally left blank
	}

	void HangmanWindow::keyPressEvent(QKeyEvent* event)
	{
		switch(event->key())
		{
		case Qt::Key_Escape:
			this->close();
			break;
		}
	}

	void HangmanWindow::closeEvent(QCloseEvent *event)
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
			if(mouseMoverThread->isRunning())
			{
				mouseMoverThread->terminate();
			}

			event->accept();
		}

		else
		{
			event->ignore();
		}
	}

	void HangmanWindow::on_pushButton_28_clicked() ///start
	{
		valuef=1;
		wrongLetter="  ";
		ui.label_4->setText(wrongLetter);
		on_action_triggered();
		checkFinish();

		if(!mouseMoverThread->isRunning())
		{
			mouseMoverThread->setEyeTracker(eyeTracker);
			mouseMoverThread->start();
		}
	}

	void HangmanWindow::on_pushButton_29_clicked()  ////exit
	{
		this->close();
	}

	void HangmanWindow::paintEvent(QPaintEvent *event)
	{
		int desktopHeight = this->geometry().height();
		int desktopWidth = this->geometry().width();

		//ui.groupBox->setGeometry(0, 0, desktopWidth, desktopHeight);
		ui.groupBox_2->setGeometry(desktopWidth*0.02, desktopHeight/2.25, (desktopWidth-desktopWidth*0.04), desktopHeight/2.25);

		ui.groupBox_4->setGeometry(desktopWidth/4, 10, (desktopWidth/3.40), desktopHeight/4.85);
		ui.groupBox_3->setGeometry(desktopWidth/4, 50+desktopHeight/4.85, (desktopWidth/3.40), desktopHeight/7.55);
		ui.label->setGeometry(20 , 15, (desktopWidth/4), desktopHeight/7.55);
		ui.label_2->setGeometry(2, 15, (desktopWidth/3.5), desktopHeight/11.14);


		ui.label_3->setGeometry(3*desktopWidth/4, 10, (desktopWidth/5.2), desktopHeight/2.35);
		ui.label_4->setGeometry(desktopWidth/4+(desktopWidth/3.1), desktopHeight/4.85, (desktopWidth/7.5), desktopHeight/13.6);

		ui.pushButton->setGeometry(50, 40 , desktopWidth/11 , desktopHeight/8);
		ui.pushButton_2->setGeometry(50 + (desktopWidth/11), 40 , desktopWidth/11 , desktopHeight/8);
		ui.pushButton_3->setGeometry(50 + 2*(desktopWidth/11), 40 , desktopWidth/11 , desktopHeight/8);
		ui.pushButton_4->setGeometry(50 + 3*(desktopWidth/11), 40 , desktopWidth/11 , desktopHeight/8);
		ui.pushButton_5->setGeometry(50 + 4*(desktopWidth/11), 40 , desktopWidth/11 , desktopHeight/8);
		ui.pushButton_6->setGeometry(50 + 5*(desktopWidth/11), 40 , desktopWidth/11 , desktopHeight/8);
		ui.pushButton_7->setGeometry(50 + 6*(desktopWidth/11), 40 , desktopWidth/11 , desktopHeight/8);
		ui.pushButton_8->setGeometry(50 + 7*(desktopWidth/11), 40 , desktopWidth/11 , desktopHeight/8);
		ui.pushButton_9->setGeometry(50 + 8*(desktopWidth/11), 40 , desktopWidth/11 , desktopHeight/8);
		ui.pushButton_10->setGeometry(50 + 9*(desktopWidth/11), 40 , desktopWidth/11 , desktopHeight/8);


		ui.pushButton_11->setGeometry(50                       , 40 + desktopHeight/8 , desktopWidth/10 , desktopHeight/8);
		ui.pushButton_12->setGeometry(50 + (desktopWidth/10)   , 40 + desktopHeight/8 , desktopWidth/10 , desktopHeight/8);
		ui.pushButton_13->setGeometry(50 + 2 *(desktopWidth/10), 40 + desktopHeight/8 , desktopWidth/10 , desktopHeight/8);
		ui.pushButton_14->setGeometry(50 + 3 *(desktopWidth/10), 40 + desktopHeight/8 , desktopWidth/10 , desktopHeight/8);
		ui.pushButton_15->setGeometry(50 + 4 *(desktopWidth/10), 40 + desktopHeight/8 , desktopWidth/10 , desktopHeight/8);
		ui.pushButton_16->setGeometry(50 + 5 *(desktopWidth/10), 40 + desktopHeight/8 , desktopWidth/10 , desktopHeight/8);
		ui.pushButton_17->setGeometry(50 + 6 *(desktopWidth/10), 40 + desktopHeight/8 , desktopWidth/10 , desktopHeight/8);
		ui.pushButton_18->setGeometry(50 + 7 *(desktopWidth/10), 40 + desktopHeight/8 , desktopWidth/10 , desktopHeight/8);
		ui.pushButton_19->setGeometry(50 + 8 *(desktopWidth/10), 40 + desktopHeight/8 , desktopWidth/9.4 , desktopHeight/8);



		ui.pushButton_20->setGeometry(50                       , 40 +  2 * desktopHeight/8 , desktopWidth/7.8 , desktopHeight/8);
		ui.pushButton_21->setGeometry(50 + (desktopWidth/7.8)   , 40 +  2 * desktopHeight/8 , desktopWidth/7.8 , desktopHeight/8);
		ui.pushButton_22->setGeometry(50 + 2 *(desktopWidth/7.8), 40 +  2 * desktopHeight/8 , desktopWidth/7.8 , desktopHeight/8);
		ui.pushButton_23->setGeometry(50 + 3 *(desktopWidth/7.8), 40 +  2 * desktopHeight/8 , desktopWidth/7.8 , desktopHeight/8);
		ui.pushButton_24->setGeometry(50 + 4 *(desktopWidth/7.8), 40 +  2 * desktopHeight/8 , desktopWidth/7.8 , desktopHeight/8);
		ui.pushButton_25->setGeometry(50 + 5 *(desktopWidth/7.8), 40 +  2 * desktopHeight/8 , desktopWidth/7.8 , desktopHeight/8);
		ui.pushButton_26->setGeometry(50 + 6 *(desktopWidth/7.8), 40 +  2 * desktopHeight/8 , desktopWidth/7.3 , desktopHeight/8);


		ui.pushButton_28->setGeometry(50 , 40  , desktopWidth/7 , desktopHeight/7);
		ui.pushButton_29->setGeometry(50 , 40 +   desktopHeight/7 , desktopWidth/7 , desktopHeight/7);
		startCoor[0]=50;    startCoor[1]=40;    startCoor[2]=startCoor[0]+desktopWidth/7;   startCoor[3]=startCoor[1]+ desktopHeight/7;
		exitCoor[0]=50;    exitCoor[1]=40 +  desktopHeight/7;    exitCoor[2]=exitCoor[0]+desktopWidth/7 ;    exitCoor[3]=exitCoor[1]+desktopHeight/7;


		QCoor[0]=desktopWidth*0.02+50;                        QCoor[1]=desktopHeight/2.25+40 ;  QCoor[2]=QCoor[0]+desktopWidth/11 ;  QCoor[3]= QCoor[1]+desktopHeight/8;
		WCoor[0]=desktopWidth*0.02+50 + (desktopWidth/11);    WCoor[1]=desktopHeight/2.25+40 ;  WCoor[2]=WCoor[0]+desktopWidth/11 ;  WCoor[3]= WCoor[1]+desktopHeight/8;
		ECoor[0]=desktopWidth*0.02+50 + 2*(desktopWidth/11);  ECoor[1]=desktopHeight/2.25+40 ;  ECoor[2]=ECoor[0]+desktopWidth/11 ;  ECoor[3]= ECoor[1]+desktopHeight/8;
		RCoor[0]=desktopWidth*0.02+50 + 3*(desktopWidth/11);  RCoor[1]=desktopHeight/2.25+40 ;  RCoor[2]=RCoor[0]+desktopWidth/11 ;  RCoor[3]= RCoor[1]+desktopHeight/8;
		TCoor[0]=desktopWidth*0.02+50 + 4*(desktopWidth/11);  TCoor[1]=desktopHeight/2.25+40 ;  TCoor[2]=TCoor[0]+desktopWidth/11 ;  TCoor[3]= TCoor[1]+desktopHeight/8;
		YCoor[0]=desktopWidth*0.02+50 + 5*(desktopWidth/11);  YCoor[1]=desktopHeight/2.25+40 ;  YCoor[2]=YCoor[0]+desktopWidth/11 ;  YCoor[3]= YCoor[1]+desktopHeight/8;
		UCoor[0]=desktopWidth*0.02+50 + 6*(desktopWidth/11);  UCoor[1]=desktopHeight/2.25+40 ;  UCoor[2]=UCoor[0]+desktopWidth/11 ;  UCoor[3]= UCoor[1]+desktopHeight/8;
		ICoor[0]=desktopWidth*0.02+50 + 7*(desktopWidth/11);  ICoor[1]=desktopHeight/2.25+40 ;  ICoor[2]=ICoor[0]+desktopWidth/11 ;  ICoor[3]= ICoor[1]+desktopHeight/8;
		OCoor[0]=desktopWidth*0.02+50 + 8*(desktopWidth/11);  OCoor[1]=desktopHeight/2.25+40 ;  OCoor[2]=OCoor[0]+desktopWidth/11 ;  OCoor[3]= OCoor[1]+desktopHeight/8;
		PCoor[0]=desktopWidth*0.02+50 + 9*(desktopWidth/11);  PCoor[1]=desktopHeight/2.25+40 ;  PCoor[2]=PCoor[0]+desktopWidth/11 ;  PCoor[3]= PCoor[1]+desktopHeight/8;


		ACoor[0]=desktopWidth*0.02+50                      ;    ACoor[1]=desktopHeight/2.25+40 + desktopHeight/8;  ACoor[2]=ACoor[0]+desktopWidth/10 ;  ACoor[3]= ACoor[1]+desktopHeight/8;
		SCoor[0]=desktopWidth*0.02+50 +   (desktopWidth/10);  SCoor[1]=desktopHeight/2.25+40+ desktopHeight/8 ;  SCoor[2]=SCoor[0]+desktopWidth/10 ;  SCoor[3]= SCoor[1]+desktopHeight/8;
		DCoor[0]=desktopWidth*0.02+50 + 2*(desktopWidth/10);  DCoor[1]=desktopHeight/2.25+40+ desktopHeight/8 ;  DCoor[2]=DCoor[0]+desktopWidth/10 ;  DCoor[3]= DCoor[1]+desktopHeight/8;
		FCoor[0]=desktopWidth*0.02+50 + 3*(desktopWidth/10);  FCoor[1]=desktopHeight/2.25+40 + desktopHeight/8;  FCoor[2]=FCoor[0]+desktopWidth/10 ;  FCoor[3]= FCoor[1]+desktopHeight/8;
		GCoor[0]=desktopWidth*0.02+50 + 4*(desktopWidth/10);  GCoor[1]=desktopHeight/2.25+40 + desktopHeight/8;  GCoor[2]=GCoor[0]+desktopWidth/10 ;  GCoor[3]= GCoor[1]+desktopHeight/8;
		HCoor[0]=desktopWidth*0.02+50 + 5*(desktopWidth/10);  HCoor[1]=desktopHeight/2.25+40+ desktopHeight/8 ;  HCoor[2]=HCoor[0]+desktopWidth/10 ;  HCoor[3]= HCoor[1]+desktopHeight/8;
		JCoor[0]=desktopWidth*0.02+50 + 6*(desktopWidth/10);  JCoor[1]=desktopHeight/2.25+40 + desktopHeight/8;  JCoor[2]=JCoor[0]+desktopWidth/10 ;  JCoor[3]= JCoor[1]+desktopHeight/8;
		KCoor[0]=desktopWidth*0.02+50 + 7*(desktopWidth/10);  KCoor[1]=desktopHeight/2.25+40 + desktopHeight/8;  KCoor[2]=KCoor[0]+desktopWidth/10 ;  KCoor[3]= KCoor[1]+desktopHeight/8;
		LCoor[0]=desktopWidth*0.02+50 + 8*(desktopWidth/10);  LCoor[1]=desktopHeight/2.25+40 + desktopHeight/8;  LCoor[2]=LCoor[0]+desktopWidth/10 ;  LCoor[3]= LCoor[1]+desktopHeight/8;


		ZCoor[0]=desktopWidth*0.02+50                      ;  ZCoor[1]=desktopHeight/2.25+40+ 2*desktopHeight/8 ;  ZCoor[2]=ZCoor[0]+desktopWidth/7.8 ;  ZCoor[3]= ZCoor[1]+desktopHeight/8;
		XCoor[0]=desktopWidth*0.02+50 +   (desktopWidth/7.8);  XCoor[1]=desktopHeight/2.25+40 + 2* desktopHeight/8;  XCoor[2]=XCoor[0]+desktopWidth/7.8 ;  XCoor[3]= XCoor[1]+desktopHeight/8;
		CCoor[0]=desktopWidth*0.02+50 + 2*(desktopWidth/7.8);  CCoor[1]=desktopHeight/2.25+40 + 2*desktopHeight/8;  CCoor[2]=CCoor[0]+desktopWidth/7.8 ;  CCoor[3]= CCoor[1]+desktopHeight/8;
		VCoor[0]=desktopWidth*0.02+50 + 3*(desktopWidth/7.8);  VCoor[1]=desktopHeight/2.25+40+ 2*desktopHeight/8 ;  VCoor[2]=VCoor[0]+desktopWidth/7.8 ;  VCoor[3]= VCoor[1]+desktopHeight/8;
		BCoor[0]=desktopWidth*0.02+50 + 4*(desktopWidth/7.8);  BCoor[1]=desktopHeight/2.25+40 +2* desktopHeight/8;  BCoor[2]=BCoor[0]+desktopWidth/7.8 ;  BCoor[3]= BCoor[1]+desktopHeight/8;
		NCoor[0]=desktopWidth*0.02+50 + 5*(desktopWidth/7.8);  NCoor[1]=desktopHeight/2.25+40 + 2*desktopHeight/8;  NCoor[2]=NCoor[0]+desktopWidth/7.8 ;  NCoor[3]= NCoor[1]+desktopHeight/8;
		MCoor[0]=desktopWidth*0.02+50 + 6*(desktopWidth/7.8);  MCoor[1]=desktopHeight/2.25+40 +2* desktopHeight/8;  MCoor[2]=MCoor[0]+desktopWidth/7.8 ;  MCoor[3]= MCoor[1]+desktopHeight/8;
	}

	void HangmanWindow::findButton(int x, int y){

		//cout<<x<<" "<<y;
		ui.pushButton_32->setGeometry( x , y , 10, 10);//
		update();//
		repaint();//
		if(  (QCoor[0]<x && QCoor[2]>x)    &&    (QCoor[1]<y && QCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 1 )
				on_pushButton_clicked();

		} else if(  (WCoor[0]<x && WCoor[2]>x)    &&    (WCoor[1]<y && WCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 2 )
				on_pushButton_2_clicked();

		} else if(  (ECoor[0]<x && ECoor[2]>x)    &&    (ECoor[1]<y && ECoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 3 )
				on_pushButton_3_clicked();

		} else if(  (RCoor[0]<x && RCoor[2]>x)    &&    (RCoor[1]<y && RCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 4 )
				on_pushButton_4_clicked();

		} else if(  (TCoor[0]<x && TCoor[2]>x)    &&    (TCoor[1]<y && TCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 5 )
				on_pushButton_5_clicked();

		} else if(  (YCoor[0]<x && YCoor[2]>x)    &&    (YCoor[1]<y && YCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 6 )
				on_pushButton_6_clicked();

		} else if(  (UCoor[0]<x && UCoor[2]>x)    &&    (UCoor[1]<y && UCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 7 )
				on_pushButton_7_clicked();

		} else if(  (ICoor[0]<x && ICoor[2]>x)    &&    (ICoor[1]<y && ICoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 8 )
				on_pushButton_8_clicked();

		} else if(  (OCoor[0]<x && OCoor[2]>x)    &&    (OCoor[1]<y && OCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 9 )
				on_pushButton_9_clicked();

		} else if(  (PCoor[0]<x && PCoor[2]>x)    &&    (PCoor[1]<y && PCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 10 )
				on_pushButton_10_clicked();

		} else if(  (ACoor[0]<x && ACoor[2]>x)    &&    (ACoor[1]<y && ACoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 11 )
				on_pushButton_11_clicked();

		} else if(  (SCoor[0]<x && SCoor[2]>x)    &&    (SCoor[1]<y && SCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 12 )
				on_pushButton_12_clicked();

		} else if(  (DCoor[0]<x && DCoor[2]>x)    &&    (DCoor[1]<y && DCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 13 )
				on_pushButton_13_clicked();

		} else if(  (FCoor[0]<x && FCoor[2]>x)    &&    (FCoor[1]<y && FCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 14 )
				on_pushButton_14_clicked();

		} else if(  (GCoor[0]<x && GCoor[2]>x)    &&    (GCoor[1]<y && GCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 15 )
				on_pushButton_15_clicked();

		} else if(  (HCoor[0]<x && HCoor[2]>x)    &&    (HCoor[1]<y && HCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 16 )
				on_pushButton_16_clicked();

		} else if(  (JCoor[0]<x && JCoor[2]>x)    &&    (JCoor[1]<y && JCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 17 )
				on_pushButton_17_clicked();

		} else if(  (KCoor[0]<x && KCoor[2]>x)    &&    (KCoor[1]<y && KCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 18 )
				on_pushButton_18_clicked();

		} else if(  (LCoor[0]<x && LCoor[2]>x)    &&    (LCoor[1]<y && LCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 19 )
				on_pushButton_19_clicked();

		} else if(  (ZCoor[0]<x && ZCoor[2]>x)    &&    (ZCoor[1]<y && ZCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 20 )
				on_pushButton_20_clicked();

		} else if(  (XCoor[0]<x && XCoor[2]>x)    &&    (XCoor[1]<y && XCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 21 )
				on_pushButton_21_clicked();

		} else if(  (CCoor[0]<x && CCoor[2]>x)    &&    (CCoor[1]<y && CCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 22 )
				on_pushButton_22_clicked();

		} else if(  (VCoor[0]<x && VCoor[2]>x)    &&    (VCoor[1]<y && VCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 23 )
				on_pushButton_23_clicked();

		} else if(  (BCoor[0]<x && BCoor[2]>x)    &&    (BCoor[1]<y && BCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 24 )
				on_pushButton_24_clicked();

		} else if(  (NCoor[0]<x && NCoor[2]>x)    &&    (NCoor[1]<y && NCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 25 )
				on_pushButton_25_clicked();

		} else if(  (MCoor[0]<x && MCoor[2]>x)    &&    (MCoor[1]<y && MCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 26 )
				on_pushButton_26_clicked();

		} else if(  (exitCoor[0]<x && exitCoor[2]>x)    &&    (exitCoor[1]<y && exitCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 27 )
				on_pushButton_29_clicked();

		} else if(  (startCoor[0]<x && startCoor[2]>x)    &&    (startCoor[1]<y && startCoor[3]>y)  ){
			Sleeper::sleep(4);
			if(  findButton2(x ,y) == 28 )
				on_pushButton_28_clicked();

		}
	}

	int HangmanWindow::findButton2(int x, int y){

		ui.pushButton_32->setGeometry( x , y , 10, 10);//
		update();//
		repaint();//
		if(  (QCoor[0]<x && QCoor[2]>x)    &&    (QCoor[1]<y && QCoor[3]>y)  ){
			return 1;

		}  else if(  (WCoor[0]<x && WCoor[2]>x)    &&    (WCoor[1]<y && WCoor[3]>y)  ){
			return 2;

		} else if(  (ECoor[0]<x && ECoor[2]>x)    &&    (ECoor[1]<y && ECoor[3]>y)  ){
			return 3;

		} else if(  (RCoor[0]<x && RCoor[2]>x)    &&    (RCoor[1]<y && RCoor[3]>y)  ){
			return 4;

		} else if(  (TCoor[0]<x && TCoor[2]>x)    &&    (TCoor[1]<y && TCoor[3]>y)  ){
			return 5;

		} else if(  (YCoor[0]<x && YCoor[2]>x)    &&    (YCoor[1]<y && YCoor[3]>y)  ){
			return 6;

		} else if(  (UCoor[0]<x && UCoor[2]>x)    &&    (UCoor[1]<y && UCoor[3]>y)  ){
			return 7;

		} else if(  (ICoor[0]<x && ICoor[2]>x)    &&    (ICoor[1]<y && ICoor[3]>y)  ){
			return 8;

		} else if(  (OCoor[0]<x && OCoor[2]>x)    &&    (OCoor[1]<y && OCoor[3]>y)  ){
			return 9;

		} else if(  (PCoor[0]<x && PCoor[2]>x)    &&    (PCoor[1]<y && PCoor[3]>y)  ){
			return 10;

		} else if(  (ACoor[0]<x && ACoor[2]>x)    &&    (ACoor[1]<y && ACoor[3]>y)  ){
			return 11;

		} else if(  (SCoor[0]<x && SCoor[2]>x)    &&    (SCoor[1]<y && SCoor[3]>y)  ){
			return 12;

		} else if(  (DCoor[0]<x && DCoor[2]>x)    &&    (DCoor[1]<y && DCoor[3]>y)  ){
			return 13;

		} else if(  (FCoor[0]<x && FCoor[2]>x)    &&    (FCoor[1]<y && FCoor[3]>y)  ){
			return 14;

		} else if(  (GCoor[0]<x && GCoor[2]>x)    &&    (GCoor[1]<y && GCoor[3]>y)  ){
			return 15;

		} else if(  (HCoor[0]<x && HCoor[2]>x)    &&    (HCoor[1]<y && HCoor[3]>y)  ){
			return 16;

		} else if(  (JCoor[0]<x && JCoor[2]>x)    &&    (JCoor[1]<y && JCoor[3]>y)  ){
			return 17;

		} else if(  (KCoor[0]<x && KCoor[2]>x)    &&    (KCoor[1]<y && KCoor[3]>y)  ){
			return 18;

		} else if(  (LCoor[0]<x && LCoor[2]>x)    &&    (LCoor[1]<y && LCoor[3]>y)  ){
			return 19;

		} else if(  (ZCoor[0]<x && ZCoor[2]>x)    &&    (ZCoor[1]<y && ZCoor[3]>y)  ){
			return 20;

		} else if(  (XCoor[0]<x && XCoor[2]>x)    &&    (XCoor[1]<y && XCoor[3]>y)  ){
			return 21;

		} else if(  (CCoor[0]<x && CCoor[2]>x)    &&    (CCoor[1]<y && CCoor[3]>y)  ){
			return 22;

		} else if(  (VCoor[0]<x && VCoor[2]>x)    &&    (VCoor[1]<y && VCoor[3]>y)  ){
			return 23;

		} else if(  (BCoor[0]<x && BCoor[2]>x)    &&    (BCoor[1]<y && BCoor[3]>y)  ){
			return 24;

		} else if(  (NCoor[0]<x && NCoor[2]>x)    &&    (NCoor[1]<y && NCoor[3]>y)  ){
			return 25;

		} else if(  (MCoor[0]<x && MCoor[2]>x)    &&    (MCoor[1]<y && MCoor[3]>y)  ){
			return 26;

		} else if(  (exitCoor[0]<x && exitCoor[2]>x)    &&    (exitCoor[1]<y && exitCoor[3]>y)  ){
			return 27;

		} else if(  (startCoor[0]<x && startCoor[2]>x)    &&    (startCoor[1]<y && startCoor[3]>y)  ){
			return 28;

		}
		return 0;

	}

	void HangmanWindow::on_action_triggered()  //// HangMan
	{
		ansWord="";
		QString answer = " ";
		word=words[rand()%6];
		for(int i = 0; i < word.length() ; ++i){
			ansWord+="-";
			answer+="  __";
		}

		ui.label_2->setText(answer);
		ui.label->setText("One of the beautiful \ncounty of KARS");
	}


	void HangmanWindow::on_action_2_triggered()
	{
		on_pushButton_28_clicked();
		newGame();
	}

	void HangmanWindow::newGame(){

		QPoint oldPosition;
		for(;true;){
			oldPosition = ui.groupBox->mapFromGlobal(QCursor::pos());
			findButton(oldPosition.x(), oldPosition.y());
			ui.pushButton_32->setGeometry( oldPosition.x() , oldPosition.y() , 10, 10);  //
			update();///
			repaint();///
			Sleeper::sleep(4);
		}
	}

	void HangmanWindow::on_pushButton_clicked()    ////Q
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='Q'){
				check = true;
				ansWord[i] = 'Q';
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  Q";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='Q')
				answer+="  Q";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_2_clicked()     ////W
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='W'){
				ansWord[i] = 'W';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  W";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='W')
				answer+="  W";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_3_clicked()    ////E
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='E'){
				ansWord[i] = 'E';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  E";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='E')
				answer+="  E";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_4_clicked()    ////R
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='R'){
				ansWord[i] = 'R';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  R";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='R')
				answer+="  R";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_5_clicked()    ////T
	{
		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='T'){
				ansWord[i] = 'T';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  T";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='T')
				answer+="  T";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();


	}

	void HangmanWindow::on_pushButton_6_clicked()    ////Y
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='Y'){
				ansWord[i] = 'Y';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  Y";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='Y')
				answer+="  Y";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_7_clicked()    ////U
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='U'){
				ansWord[i] = 'U';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  U";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='U')
				answer+="  U";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_8_clicked()    ////I
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='I'){
				ansWord[i] = 'I';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  I";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='I')
				answer+="  I";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_9_clicked()    ////O
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='O'){
				ansWord[i] = 'O';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  O";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='O')
				answer+="  O";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_10_clicked()    ////P
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='P'){
				ansWord[i] = 'P';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  P";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='P')
				answer+="  P";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_11_clicked()    ////A
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='A'){
				ansWord[i] = 'A';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  A";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='A')
				answer+="  A";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_12_clicked()    ////S
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='S'){
				ansWord[i] = 'S';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  S";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='S')
				answer+="  S";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_13_clicked()    ////D
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='D'){
				ansWord[i] = 'D';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  D";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='D')
				answer+="  D";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_14_clicked()    ////F
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='F'){
				ansWord[i] = 'F';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  F";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='F')
				answer+="  F";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_15_clicked()    ////G
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='G'){
				ansWord[i] = 'G';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  G";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='G')
				answer+="  G";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_16_clicked()    ////H
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='H'){
				ansWord[i] = 'H';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  H";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='H')
				answer+="  H";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_17_clicked()    ////J
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='J'){
				ansWord[i] = 'J';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  J";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='J')
				answer+="  J";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_18_clicked()    ////K
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='K'){
				ansWord[i] = 'K';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  K";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='K')
				answer+="  K";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_19_clicked()    ////L
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='L'){
				ansWord[i] = 'L';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  L";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='L')
				answer+="  L";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_20_clicked()    ////Z
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='Z'){
				ansWord[i] = 'Z';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  Z";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='Z')
				answer+="  Z";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_21_clicked()    ////X
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='X'){
				ansWord[i] = 'X';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  X";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='X')
				answer+="  X";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_22_clicked()    ////C
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='C'){
				ansWord[i] = 'C';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  C";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='C')
				answer+="  C";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_23_clicked()    ////V
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='V'){
				ansWord[i] = 'V';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  V";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='V')
				answer+="  V";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_24_clicked()    ////B
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='B'){
				ansWord[i] = 'B';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  B";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='B')
				answer+="  B";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_25_clicked()    ////N
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='N'){
				ansWord[i] = 'N';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  N";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='N')
				answer+="  N";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::on_pushButton_26_clicked()    ////M
	{

		QString answer = " ";
		bool check = false;
		for(int i = 0; i < word.length() ; ++i){
			if(word[i]=='M'){
				ansWord[i] = 'M';
				check = true;
			}
		}

		if(!check){
			++valuef;
			wrongLetter+="  M";
			ui.label_4->setText(wrongLetter);
		}

		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]=='-')
				answer+="  __";
			else if(ansWord[i]=='M')
				answer+="  M";
			else
				answer+="  "+ansWord[i];
		}

		ui.label_2->setText(answer);
		checkFinish();
		update();
		repaint();

	}

	void HangmanWindow::setWord(QString x)
	{
		word=x;
	}

	void HangmanWindow::checkFinish()
	{
		QPixmap pix("Images/77.png");
		QPixmap pix2("Images/76.png");
		QPixmap pix3("Images/75.png");
		QPixmap pix4("Images/74.png");
		QPixmap pix5("Images73.png");
		QPixmap pix6("Images/72.png");
		QPixmap pix7("Images/7.png");

		if(valuef==1)
			ui.label_3->setPixmap(pix);
		else if(valuef==2)
			ui.label_3->setPixmap(pix2);
		else if(valuef==3)
			ui.label_3->setPixmap(pix3);
		else if(valuef==4)
			ui.label_3->setPixmap(pix4);
		else if(valuef==5)
			ui.label_3->setPixmap(pix5);
		else if(valuef==6)
			ui.label_3->setPixmap(pix6);
		else if(valuef==7){
			ui.label_3->setPixmap(pix7);
			//valuef = 1;
			ui.label_4->setText("GAME OVER");
		}


		int counter = 0;
		for(int i = 0; i < word.length() ; ++i){
			if(ansWord[i]!='-'){
				++counter;
			}
		}
		if(counter == ansWord.length()){


			/*QSplashScreen *splash = new QSplashScreen;
			splash->setPixmap(QPixmap("C:/Users/YvZ/Desktop/Proje2Son/Proje/77.png"));
			splash->show();
			QTimer::singleShot(2500, splash , SLOT(close()));*/
			ui.label_4->setText("WIN");
			valuef = 1;
			for(int i = 0; i < word.length() ; ++i){
				if(ansWord[i]!='-'){
					ansWord[i]='-';
				}
			}
		}

	}
}