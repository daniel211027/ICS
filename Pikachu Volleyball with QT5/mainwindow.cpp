#include "mainwindow.h"
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	setFixedSize(1800,900);
	this->setWindowTitle("Pikachu volleyball");
	ball.load("./dataset/pokeball.png");
	pikachuL.load("./dataset/daidai.png");
	pikachuRfly.load("./dataset/chochonifly.png");
	pikachuR.load("./dataset/chochoni.png");
	bg.load("./dataset/bg.png"); 
	score.load("./dataset/win");
}
void MainWindow::mode(QPainter &B){
	B.drawText(1200,30,QString("Enter 'backspace' to change mode"));
	if(keycode==10)
		doubleAI_mode=!doubleAI_mode;
	if(doubleAI_mode)
		B.drawText(1200,55,QString("Current mode:\n 2 computers"));
	else
		B.drawText(1200,55,QString("Current mode:\n U fight with the computer"));
}
void MainWindow::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
		case Qt::Key_Up:
			keycode = 0;
			break;
		case Qt::Key_Down:
			keycode = 1;
			break;
		case Qt::Key_Left:
			keycode = 2;
			break;
		case Qt::Key_Right:
			keycode = 3;
			break;
		case Qt::Key_Backspace:
			keycode = 10;
			break;
		case Qt::Key_Space:
			keycode = 11;
			break;
		default:
			keycode = -1;
			break;
		}
		update();
}
void MainWindow::keyReleaseEvent(QKeyEvent *event){
	switch (event->key()) {
		case Qt::Key_Space:
			keycode = 11;
			break;
		default:
			keycode = -1;
			break;
	}
	keycode_first=keycode;
}
void MainWindow::draw_pikachu(QPainter &B){
	//For left pikachu x axis
	if(l_x>ball_x-100)
		l_x-=15;
	else
		l_x+=15;
	if(l_x<0){
		l_x=1;
	}
	if (l_x>650) l_x=650-1;
	//For right pikachu on y axis
	if(r_y>690){
		if(keycode==0){
			r_vy=-25;
			t_r=0;
		}
		else{
			r_vy=0;
			r_y=700;
		}
	}
	else{
		if(fly==1)
			t_r+=1;
		else
			t_r+=0.15;
		r_vy=r_vy+0.5*g*t_r;
	}
	//For right pikachu on x axis
	if((r_x_before_fly-r_x>350||r_x_before_fly-r_x<-350)&&fly){
		r_vx=0;
		fly=0;
	}
	if(r_x>1580||r_x<940){
		fly=0;
		r_vx=0;
	}
	if(doubleAI_mode){
		if(r_x>930&&r_x<=1600){
			if(ball_x>0){
				if(r_x>ball_x+50)
					r_x-=50;
				else
					r_x+=50;
			}	
		}
		 if(r_x<931){
			r_x=931;
		}
		if (r_x>1600 )r_x=1600-1;
	}
	else{
		if(r_x>930&&r_x<=1600){
			if(keycode_first==11&&r_y>680&&(keycode==2||keycode==3)){
				r_vy=-10;
				r_x_before_fly=r_x;
				keycode_first=-1;
				fly=1;
				t_r=0;
				if(keycode==2)
					r_vx-=35;
				if(keycode==3)
					r_vx+=35;
			}
			else{
				if(keycode==2)
					r_x-=20;
				if(keycode==3)
					r_x+=20;
			}
		}
		if(r_x<931){
			r_x=932;
		}
		if (r_x>1600) r_x=1599;
	}
	l_y+=l_vy;
	r_y+=r_vy;
	r_x+=r_vx;
	if(fly==1)
		B.drawImage(QRect(r_x,r_y,200,200),pikachuRfly);
	else
		B.drawImage(QRect(r_x,r_y,200,200),pikachuR);
	B.drawImage(QRect(l_x,l_y,200,200),pikachuL);
}
void MainWindow::draw_ball(QPainter &B){
	B.drawImage(QRect(ball_x,ball_y,150,150),ball);
	//ball collides with window side
	if(ball_x>1800-150){
		ball_x=1650;
		ball_vx=-ball_vx;
	}
	if(ball_x<0){
		ball_x=0;
		ball_vx=-ball_vx;
	}
	if(ball_y>900-150){
		ball_vy=-ball_vy;
		ball_y=900-150;
	}
	if(ball_y<0){
		ball_vy=-ball_vy;
	}
	//ball collides with net from one side
	if(ball_vx<0&&ball_x>920-100&&ball_x<920&&ball_y>=565-150&&ball_y<=900-150){
		ball_vx=-ball_vx;
	}
	if(ball_vx>0&&ball_x>880-150&&ball_x<880-50&&ball_y>=565-150&&ball_y<=900-150){
		ball_vx=-ball_vx;
	}
	//ball collides with net from top
	if(ball_vy>0&&ball_x<=920&&ball_x>=880-150&&ball_y>=540-150&&ball_y<565-150){
		ball_vy=-ball_vy;
		t_ball=0;
	}
	if(ball_vy>20&&ball_x<=920&&ball_x>=880-150&&ball_y>=535-150&&ball_y<565-150){
		ball_vy=-ball_vy;
		t_ball=0;
	}
	if(keycode==11)     //if wanna Smash!
		ball_vabs=40*sqrt(2);
	else
		ball_vabs=20*sqrt(2);
	dis_ball_left=sqrt(pow(ball_x+75-l_x-100,2)+pow(ball_y+75-l_y-100,2));
	dis_ball_right=sqrt(pow(ball_x+75-r_x-100,2)+pow(ball_y+75-r_y-100,2));
	if(dis_ball_left<150){
		ball_vx=ball_vabs*(ball_x+75-l_x-100)/dis_ball_left;	//Normalize
		ball_vy=ball_vabs*(ball_y+75-l_y-100)/dis_ball_left;
		t_ball=0;
		keycode=-1;
		pika->play();
	}
	if(dis_ball_right<150){
		ball_vx=ball_vabs*(ball_x+75-r_x-100)/dis_ball_right;	//Normalize
		ball_vy=ball_vabs*(ball_y+75-r_y-100)/dis_ball_right;
		t_ball=0;
		keycode=-1;
		ball_vabs=20*sqrt(2);
		pika->play();
	}
	t_ball+=0.03;
	ball_vy=ball_vy+g*t_ball;
	ball_x+=ball_vx;
	ball_y+=ball_vy;
}
void MainWindow::ball_gnd(QPainter &C){
	if(ball_y>900-150){
		if(ball_x<880){
			score_r++;
			ball_x=1500,ball_y=0;
			ball_vx=0,ball_vy=0;
			l_x=100,l_y=700;
			r_x=1500,r_y=700;
		}
		else{
			score_l++;
			ball_x=150,ball_y=0;
			ball_vx=0,ball_vy=0;
			l_x=100,l_y=700;
			r_x=1500,r_y=700;
		}
		t_ball=0;
	}
	C.drawText(150,100,QString("%1").arg(score_l));
	C.drawText(1600,100,QString("%1").arg(score_r));
	if(score_l>=4&&score_r>=4){
		C.drawText(800,100,QString("DEUCE"));
		if(score_r-score_l>1){
			C.drawText(1600,100,QString("%1").arg(score_r));
			C.drawImage(QRect(1350,100,300,300),score);
			ball_x=-200,ball_y=-200;
			g=0;
		}	
		if(score_l-score_r>1){
			C.drawText(150,100,QString("%1").arg(score_l));
			C.drawImage(QRect(150,100,300,300),score);
			ball_x=-200,ball_y=-200;
			g=0;
		}
	}
	else{
		if(score_l==5){
			C.drawText(150,100,QString("%1").arg(score_l));
			C.drawImage(QRect(150,100,300,300),score);
			ball_x=-200,ball_y=-200;
			g=0;
		}
		if(score_r==5){
			C.drawText(1600,100,QString("%1").arg(score_r));
			C.drawImage(QRect(1350,100,300,300),score);
			ball_x=-200,ball_y=-200;
			g=0;
		}
	}
}

void MainWindow::paintEvent(QPaintEvent *event) {
	QPainter B(this);
	QPainter C(this);
	B.setRenderHint(QPainter::Antialiasing, true);
	//////////////////////////////////////////////
	QFont ft,ft1;
	ft.setPointSize(20);
	ft1.setPointSize(50);
	C.setFont(ft1);
	B.setFont(ft);
	//////////////////////////////////////////////
	draw_bg(B);
	draw_ball(B);
	draw_pikachu(B);
	ball_gnd(C);
	mode(B);
	this->update();
}

void MainWindow::draw_bg(QPainter &B){
	B.drawImage(0,0,bg);
}






















