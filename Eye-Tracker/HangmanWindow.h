#ifndef HANGMAN_WINDOW_H
#define HANGMAN_WINDOW_H

#include "ui_HangmanWindow.h"
#include "Commons.h"
#include <QMainWindow>
#include <QThread>

namespace Nsk
{
	class MouseMoverThread : public QThread
	{
		Q_OBJECT;

	public:
		explicit MouseMoverThread(QObject* parent = 0);
		EyeTracker* getEyeTracker() const { return eyeTracker; }
		void setEyeTracker(EyeTracker *eyeTracker) { this->eyeTracker = eyeTracker; };
		~MouseMoverThread();
 
	protected:
		void run(void);
 
	private:
		EyeTracker *eyeTracker;
	};

	class HangmanWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		HangmanWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
		~HangmanWindow();
		void findButton(int x, int y);
		int findButton2(int x, int y);
		void setEyeTracker(EyeTracker *eyeTracker) { this->eyeTracker = eyeTracker; }
		EyeTracker *getEyeTracker() const { return eyeTracker; }
		void newGame();

		int valuef;
		QString word;
		QString words[6];
		QString ansWord ;
		QString wrongLetter;
		void setWord(QString x);
		void checkFinish();

	private slots:

		void on_pushButton_28_clicked();

		void on_pushButton_clicked();

		void on_pushButton_2_clicked();

		void on_pushButton_3_clicked();

		void on_pushButton_4_clicked();

		void on_pushButton_5_clicked();

		void on_pushButton_6_clicked();

		void on_pushButton_7_clicked();

		void on_pushButton_8_clicked();

		void on_pushButton_9_clicked();

		void on_pushButton_10_clicked();

		void on_pushButton_11_clicked();

		void on_pushButton_12_clicked();

		void on_pushButton_13_clicked();

		void on_pushButton_14_clicked();

		void on_pushButton_15_clicked();

		void on_pushButton_16_clicked();

		void on_pushButton_17_clicked();

		void on_pushButton_18_clicked();

		void on_pushButton_19_clicked();

		void on_pushButton_20_clicked();

		void on_pushButton_21_clicked();

		void on_pushButton_22_clicked();

		void on_pushButton_23_clicked();

		void on_pushButton_24_clicked();

		void on_pushButton_25_clicked();

		void on_pushButton_26_clicked();

		void on_pushButton_29_clicked();

		void on_action_triggered();

		void on_action_2_triggered();
	
	protected:
		void paintEvent(QPaintEvent *event);
		void keyPressEvent(QKeyEvent* event);
		void closeEvent(QCloseEvent *event);

	private:
		Ui::HangmanWindowClass ui;
		EyeTracker *eyeTracker;
		MouseMoverThread *mouseMoverThread;
		int QCoor[4]; // X1, Y1, X2, Y2
		int WCoor[4];
		int ECoor[4];
		int RCoor[4];
		int TCoor[4];
		int YCoor[4];
		int UCoor[4];
		int ICoor[4];
		int OCoor[4];
		int PCoor[4];
		int ACoor[4];
		int SCoor[4];
		int DCoor[4];
		int FCoor[4];
		int GCoor[4];
		int HCoor[4];
		int JCoor[4];
		int KCoor[4];
		int LCoor[4];
		int ZCoor[4];
		int XCoor[4];
		int CCoor[4];
		int VCoor[4];
		int BCoor[4];
		int NCoor[4];
		int MCoor[4];
		int startCoor[4];
		int exitCoor[4];

	};
}
#endif // HANGMAN_WINDOW_H
