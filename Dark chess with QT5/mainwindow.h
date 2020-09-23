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
		QImage chess[15];   //0:back  1~7:�Ѥp��j�´� 8~14:�Ѥp��j���� 
		QImage circle_frame,To_Move;
		int dark=1;
		int num_can_eat=0;
		int x,a;
		int y,b;
		int tie=0;
		int end=0;
		int press_x=99,press_y=99;
		int turn=99;//turn%2=0:����  1:�¤�
		int warning=0;  //�Y���L�ĨB�ƥX�{,�������a 
		int AI_turn;
		int turn_dicision=0;    //�M�w�Ĥ@�ӤU�Ѫ̬�����C�� 
		int ID_ini[4][8];//�̪�Ѧ�,�H�C���i��|��
		int ID_status[4][8]={0};  //-1:�S��  0:back ,else��L�� 
		QVector<int> eaten[2];//�Q�Y�����Ѥl�O���b�o��, 0�s���誺,1�s�¤誺 
		MainWindow(QWidget *parent = 0);
		void ini_array(); 
		void can_move_eat_or_not(int i,int j,int kind);
		void update_to_move_array();
		void eat_or_move(int eat_x,int eat_y,int eat_ID,int eaten_x,int eaten_y,int eaten_ID);
		void AI();
		int time_turn=0; //�O���@��U�Ѯɶ� 
		int int_sum_time=0;
		QTimer *Timer;
		QLabel *player_time; //�O�����a1���ɶ� 
		QLabel *sum_time;   //��Ӯɶ�
		QLabel *timeout; 
		QPushButton *start;//���U�Y�}�l�C�� 
		QPushButton *help;//��ܹC���W�h 
		QPushButton *isdark;
		int movable[4][8]={0}; //to_move�ȭY��99 �Y�i���ʨ�i,j 
		
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
		void counting_slots();   //�@���p�ɨ�� 
		void start_slots();      //�C���}�l 
		void help_slots();  //�C���W�h 
		void isdark_slots();
		
		
		
};
#endif
