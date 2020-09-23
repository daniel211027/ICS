#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMainWindow>
#include<QPaintEvent>
#include<QPainter>
#include<QTimer>
#include<math.h>
#include<QLabel>
#include<QPushButton>
#include <QImage>
#include <QSound>
using namespace std;
class MainWindow : public QMainWindow {
Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
	float g=0.98;
	int keycode_first=-1;
	int keycode=-1;
	double ball_x=1500,ball_y=0;
	double ball_vx=0,ball_vy=50;
	double ball_vabs=20*sqrt(2);
	double l_x=100,l_y=700;
	double r_x=1500,r_y=700;
	double r_x_before_fly=0;
	double r_vx=0;
	int fly;
	double l_vy=0;
	double r_vy=0;
	double t_ball=0;
	double t_l=0,t_r=0;
	bool doubleAI_mode=1; //if doubleAI_mode=0 means 1 player and 1 AI, else means 2AI
	double dis_ball_right=900;
	double dis_ball_left=900;
	int score_r=0;
	int score_l=0;
	//////////////////////////////////////////////
	void paintEvent(QPaintEvent *event);
	void draw_bg(QPainter &B);
	void draw_ball(QPainter &B);
	void draw_pikachu(QPainter &B);
	void ball_gnd(QPainter &B);
	void mode(QPainter &B);
	/////////////////////////////////////////////
	QImage ball;
	QImage pikachuL; 
	QImage pikachuR;
	QImage pikachuRfly;
	QImage bg;
	QImage score;
	QSound *pika=new QSound("./dataset/pika.wav");;
protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
};
#endif

