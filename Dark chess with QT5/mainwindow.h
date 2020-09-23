#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QPaintEvent>
#include<QPainter>
#include <QMouseEvent>
#include <QDebug>
#include<QLabel>
#include<QPushButton>
#include <Qimage>
#include<QMessageBox>
#include <QString>
#include<string>
#include<QPalette>
#include<QTimer>
#include<QVector> 
#include<ctime>
#include <QMovie>
class MainWindow : public QMainWindow {
	Q_OBJECT
	//ui (new Ui::MainWindow)
	public:
		QImage chess[15];   //0:back  1~7:由小到大黑棋 8~14:由小到大紅棋 
		QImage circle_frame,To_Move;
		int dark=1;
		int num_can_eat=0;
		int x,a;
		int y,b;
		int tie=0;
		int end=0;
		int press_x=99,press_y=99;
		int turn=99;//turn%2=0:紅方  1:黑方
		int warning=0;  //若有無效步數出現,提醒玩家 
		int AI_turn;
		int turn_dicision=0;    //決定第一個下棋者為何種顏色 
		int ID_ini[4][8];//最初棋位,隨遊戲進行會變
		int ID_status[4][8]={0};  //-1:沒棋  0:back ,else其他棋 
		QVector<int> eaten[2];//被吃掉的棋子記錄在這裡, 0存紅方的,1存黑方的 
		MainWindow(QWidget *parent = 0);
		void ini_array(); 
		void can_move_eat_or_not(int i,int j,int kind);
		void update_to_move_array();
		void eat_or_move(int eat_x,int eat_y,int eat_ID,int eaten_x,int eaten_y,int eaten_ID);
		void AI();
		int time_turn=0; //記錄一方下棋時間 
		int int_sum_time=0;
		QTimer *Timer;
		QLabel *player_time; //記錄玩家1的時間 
		QLabel *sum_time;   //整個時間
		QLabel *timeout; 
		QPushButton *start;//按下即開始遊戲 
		QPushButton *help;//顯示遊戲規則 
		QPushButton *isdark;
		int movable[4][8]={0}; //to_move值若為99 即可移動到i,j 
		
	protected:
		void draw_plate(QPainter &B);
		void draw_chess(QPainter &B);
		void paintEvent(QPaintEvent *event);
		void show_warning(QPainter &C);
		void show_gameover(QPainter &C);
		void mousePressEvent(QMouseEvent *ev);
		void whose_turn(QPainter &B);
		void show_tie(QPainter &C);
	public slots:
		void counting_slots();   //作為計時函數 
		void start_slots();      //遊戲開始 
		void help_slots();  //遊戲規則 
		void isdark_slots();
		
		
		
};
#endif
