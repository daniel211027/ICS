
#include "mainwindow.h"
using namespace std;
//�ص��� 
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	setFixedSize(1000,600);
	this->setWindowTitle("DARK CHESS");
	QFont ft1;
    ft1.setPointSize(20);
	player_time=new QLabel("Player time:0",this);
	player_time->setGeometry(300,300,500,30);
	player_time->setFont(ft1);
	sum_time=new QLabel("Total time: 00:00:00",this);
	sum_time->setGeometry(300,340,500,30);
	sum_time->setFont(ft1);
	timeout=new QLabel("",this);
	timeout->setGeometry(300,400,300,150);
	
	help=new QPushButton("Rules",this);
    help->setGeometry(600,35,200,30);
    help->setFlat(1);
    help->setFont(ft1);
    
	setMouseTracking(true);
	setAcceptDrops(true);
	Timer =new QTimer(this);
	
	start=new QPushButton("Restart the game",this);
	start->setGeometry(600,5,300,30);
	start->setFont(ft1);
	start->setFlat(1);
	
	isdark=new QPushButton("Change to continuously eat",this);
	isdark->setGeometry(600,65,400,30);
	isdark->setFont(ft1);
	isdark->setFlat(1);
	
	connect(help,SIGNAL(clicked(bool)),this,SLOT(help_slots()));
    connect(Timer,SIGNAL(timeout()),this,SLOT(counting_slots()));
    connect(start,SIGNAL(clicked(bool)),this,SLOT(start_slots()));
    connect(isdark,SIGNAL(clicked(bool)),this,SLOT(isdark_slots()));
}
//���I���m,�ç����\�h���� 

void MainWindow::mousePressEvent(QMouseEvent *ev) {
    if (ev->button() == Qt::LeftButton) {
		a=ev->x();
     	b=ev->y();
 	    if(101<=a&&501>=a&&1<=b&&201>=b){         //�I��b�ѽL������m 
   		 	for(int i=0;i<4;i++){             //i,j�Y���y�Фƫ᪺�� 
				for(int j=0;j<8;j++){
					if ((((101+50*j)<a)&&(a<(151+50*j))&&((1+50*i)<b)&&(b<(51+50*i)))){       //i,j����U�Q�諸�y��,press�h���e�@���Q�諸 
						if(press_x==i&&press_y==j){         //�Y�I�F�P�@���Ѥl�⦸,�N�٭� 
							update_to_move_array();
							press_x=99;
							press_y=99;
							this->repaint();
							return;
						} 
						if(movable[i][j]==99){  
							if(dark==1){//�Y���i�Y,�Υi����,�N�ʧ@,�æb���禡�̭�update 
								eat_or_move(press_x,press_y,ID_status[press_x][press_y],i,j,ID_status[i][j]);
								press_x=99;
								press_y=99;
								time_turn=0;
								this->repaint();
								AI();	
								return;  
							}	
							if(dark==0){
							 
								int num_can_eat=0;
								for(int m=0;m<4;m++){
									for(int n=0;n<8;n++){
										if(movable[m][n]==99&&ID_status[m][n]>0)
											num_can_eat++;
									}
								}
								if(num_can_eat==0){
									press_x=99;
									press_y=99;
									time_turn=0;
									turn++;
									this->repaint();
									AI();	
									return;  
								}
								else{
									if(ID_status[i][j]>0){
										eat_or_move(press_x,press_y,ID_status[press_x][press_y],i,j,ID_status[i][j]);
										//update_to_move_array();
										turn--;
										time_turn=0;
										can_move_eat_or_not(i,j,ID_status[i][j]);
										press_x=i;
										press_y=j;
										this->repaint();
									}
									else{
										turn++;
										AI();
										return;
									}
								}
							
							}
						}		
						else if(ID_status[i][j]==0){            //�Y�O�I������½��,�ä�����press_x,press_y 
							ID_status[i][j]=ID_ini[i][j];
							update_to_move_array();
							if(turn_dicision==0){                             //����ƥu�b�̤@�}�l��Ѥl���� 
								if (ID_status[i][j]>7&&ID_status[i][j]<15){    //�Y�Ĥ@�ӤH½�X�Ӫ��Ѥl������,���N�O����
									turn=0;
									AI_turn=!turn;               //AI���¦�,AI_turn=1 
									}                            //turn�O�H,!turn�N�Ocomputer 
								else{                                          //�Y�Ĥ@�ӤH½�X�Ӫ��Ѥl���¤�,���N�O�¤�  (AI�û��O)
									turn=1;
									AI_turn=!turn; 				//AI������,AI_turn=0 
								}
								turn_dicision++;                              //������Ƥ��A�i�� 
								Timer->start(1000);
							}
							turn++;
							time_turn=0;
							press_x=99;
							press_y=99;
							this->repaint();
							AI();	
							return;
						}			
						else if(ID_status[i][j]==-1){        //�Y�Q�襤���a��S��,�Bmovable!=99,�N���L,�q�^�W�@��
							update_to_move_array();         //�q�^�W�@�� 
							press_x=99;
							press_y=99;
							warning=1;
							this->repaint();
							return ;
						}
						else if(turn%2==0&&(ID_status[i][j]>7&&ID_status[i][j]<15)) {//�������,�B��w���Ѥl 
							update_to_move_array();                
							can_move_eat_or_not(i,j,ID_status[i][j]);
							press_x=i;
							press_y=j;
							this->repaint();
						} 
						else if (turn%2==1&&(ID_status[i][j]>0&&ID_status[i][j]<8)) {//����¤�,�B��w�´Ѥl 
							update_to_move_array();                
							can_move_eat_or_not(i,j,ID_status[i][j]);
							press_x=i;
							press_y=j;
							this->repaint();
						} 
						else if((turn%2==1&&(ID_status[i][j]>7&&ID_status[i][j]<15))||(turn%2==0&&(ID_status[i][j]>0&&ID_status[i][j]<8))){
							warning=1;
							this->repaint();
						}
					}
				}
			}
		}
	} 		
}
void MainWindow::AI(){
	if(end==1) return;
	int asd=1;
   	while(asd){
   		srand( time(NULL) );
		int com = rand()%32;
		int i=com/8;
		int j=com%8;
		if(AI_turn==0&&eaten[0].size()>8){    //AI�O���� �B�����8���H�� (�Y���H���],�|�]�ܤ[�~���ѤU��) 
   			for(int m=0;m<4;m++){
				for(int n=0;n<8;n++){
					if(ID_status[m][n]>7&&ID_status[m][n]<15){      //���y�����,�N��Q���˨쪺 
						i=m;
						j=n;
					}
				}
			} 
   		} 
   		if(AI_turn==1&&eaten[1].size()>8){    //AI�O�¦� �B�¦��8���H�� (�Y���H���],�|�]�ܤ[�~���ѤU��) 
   			for(int m=0;m<4;m++){
				for(int n=0;n<8;n++){
					if(ID_status[m][n]>0&&ID_status[m][n]<8){      //���y��¦�,�N��Q���˨쪺 
						i=m;
						j=n;
					}
				}
			} 
   		} 
		for(int m=0;m<4;m++){
			for(int n=0;n<8;n++){
				if(movable[m][n]==99){                 //�Y���i�Y,�Υi����,�N�ʧ@,�æb���禡�̭�update 
					eat_or_move(press_x,press_y,ID_status[press_x][press_y],m,n,ID_status[m][n]);
					press_x=99;
					press_y=99;
					time_turn=0;
					this->repaint();
					asd=0;  
				} 
			}
		}
		if(!asd) break;                     //�Y�������Y�β��ʪ��ʧ@,�{���N���ΦA���U�]�F 
		if(ID_status[i][j]==0){            //�Y�O�I������½��,�ä�����press_x,press_y 
			ID_status[i][j]=ID_ini[i][j];
			update_to_move_array();
			turn++;
			time_turn=0;
			press_x=99;
			press_y=99;
			this->repaint();
			asd=0;  
		}			
		else if(ID_status[i][j]==-1){        //�Y�Q�襤���a��S��,�Bmovable!=99,�N���L,�q�^�W�@��
			update_to_move_array();         //�q�^�W�@�� 
			press_x=99;
			press_y=99;
			warning=1;
			this->repaint();
		}
		else if(turn%2==0&&(ID_status[i][j]>7&&ID_status[i][j]<15)) {//�������,�B��w���Ѥl 
			update_to_move_array();                
			can_move_eat_or_not(i,j,ID_status[i][j]);
			press_x=i;
			press_y=j;
			this->repaint();
		} 
		else if (turn%2==1&&(ID_status[i][j]>0&&ID_status[i][j]<8)) {//����¤�,�B��w�´Ѥl 
			update_to_move_array();                
			can_move_eat_or_not(i,j,ID_status[i][j]);
			press_x=i;
			press_y=j;
			this->repaint();
		} 
		else if((turn%2==1&&(ID_status[i][j]>7&&ID_status[i][j]<15))||(turn%2==0&&(ID_status[i][j]>0&&ID_status[i][j]<8))){
			warning=1;
			this->repaint();
		}
	}
}

void MainWindow::whose_turn(QPainter &B){
	if (turn==99){
		B.drawText(300,500,QString("Time start. Please choose a chess!!!"));
	}
	else{
		if(turn%2==AI_turn){
			B.drawText(600,180,QString("Computer's turn"));
		}
		else{
			B.drawText(600,180,QString("Your turn"));
		}
	}
}
//��l�ƦU�ӺX�l�ݪ���m 
void MainWindow::ini_array(){
	ID_ini[0][0]=6;
	ID_ini[0][1]=8;
	ID_ini[0][2]=2;
	ID_ini[0][3]=13;
	ID_ini[0][4]=4;
	ID_ini[0][5]=9;
	ID_ini[0][6]=1;
	ID_ini[0][7]=7;
	ID_ini[1][0]=8;
	ID_ini[1][1]=1;
	ID_ini[1][2]=12;
	ID_ini[1][3]=8;
	ID_ini[1][4]=2;
	ID_ini[1][5]=1;
	ID_ini[1][6]=5;
	ID_ini[1][7]=9;
	ID_ini[2][0]=3;
	ID_ini[2][1]=10;
	ID_ini[2][2]=13;
	ID_ini[2][3]=5;
	ID_ini[2][4]=12;
	ID_ini[2][5]=10;
	ID_ini[2][6]=4;
	ID_ini[2][7]=8;
	ID_ini[3][0]=1;
	ID_ini[3][1]=8;
	ID_ini[3][2]=14;
	ID_ini[3][3]=6;
	ID_ini[3][4]=11;
	ID_ini[3][5]=1;
	ID_ini[3][6]=3;
	ID_ini[3][7]=11;
	update_to_move_array();
}
//��Ĥ@�ӴѤl�Q���,�L�N���� 
void MainWindow::update_to_move_array(){
	for(int i=0;i<4;i++){
		for(int j=0;j<8;j++){
			movable[i][j]=ID_status[i][j];
		}
	}
}
void MainWindow::show_warning(QPainter &C){
	if(warning==1){
		C.drawText(0,450,QString("Warning!!!!It's an illegal step!!!!!!!!!"));
		warning=0;
	}
} 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::can_move_eat_or_not(int i,int j,int kind){         //�N���U�ӯ�Q��ܧ@�����ʩγQ�Y����l�ᤩmovable�Ȭ�99
	if(kind==1){  //��>>>>>>>�L��ӳ��i�H�Y�A�W�U���k���Ŧ�]�i�H��������W�X�ѽL  
	   if(i-1>=0&&(ID_status[i-1][j]==8||ID_status[i-1][j]==14||ID_status[i-1][j]==-1) )  movable[i-1][j]=99;
	   if(j-1>=0&&(ID_status[i][j-1]==8||ID_status[i][j-1]==14||ID_status[i][j-1]==-1) )  movable[i][j-1]=99; 
	   if(i+1<4&&(ID_status[i+1][j]==8||ID_status[i+1][j]==14||ID_status[i+1][j]==-1) )  movable[i+1][j]=99;
	   if(j+1<8&&(ID_status[i][j+1]==8||ID_status[i][j+1]==14||ID_status[i][j+1]==-1) )  movable[i][j+1]=99;
	}
	
	if(kind==2){  //��>>>>>>>�I�줣�O�Ů�Nexist++,��exist==2�B�����Ѯ�,�Y�z
	    int exist=0;
	    if(i-1>=0&&ID_status[i-1][j]==-1)  movable[i-1][j]=99;
	    if(j-1>=0&&ID_status[i][j-1]==-1) movable[i][j-1]=99; 
	    if(i+1<4&&ID_status[i+1][j]==-1)  movable[i+1][j]=99;
	    if(j+1<8&&ID_status[i][j+1]==-1) movable[i][j+1]=99;
		for(int m=1;m<4;m++){
			if(i-m>=0){
				if(ID_status[i-m][j]!=-1)	exist++;
				if(exist==2&&ID_status[i-m][j]<15&&ID_status[i-m][j]>7)   movable[i-m][j]=99;
			}
		}
		exist=0;
		for(int m=1;m<4;m++){
			if(i+m<4){
				if(ID_status[i+m][j]!=-1)	exist++;
				if(exist==2&&ID_status[i+m][j]<15&&ID_status[i+m][j]>7)   movable[i+m][j]=99;
			}
		}
		exist=0;
		for(int m=1;m<8;m++){
			if(j+m<8){
				if(ID_status[i][j+m]!=-1)	exist++;
				if(exist==2&&ID_status[i][j+m]<15&&ID_status[i][j+m]>7)   movable[i][j+m]=99;
			}
		}
		exist=0;
		for(int m=1;m<8;m++){
			if(j-m>=0){
				if(ID_status[i][j-m]!=-1)	exist++;
				if(exist==2&&ID_status[i][j-m]<15&&ID_status[i][j-m]>7)   movable[i][j-m]=99;				
			}
		}
	}
	if(kind==3){  //�� 
		if(i-1>=0&&( (ID_status[i-1][j]<11&&ID_status[i-1][j]>7) || ID_status[i-1][j]==-1) )  movable[i-1][j]=99;
		if(j-1>=0&&( (ID_status[i][j-1]<11&&ID_status[i][j-1]>7) || ID_status[i][j-1]==-1) )  movable[i][j-1]=99; 
		if(i+1<4&&( (ID_status[i+1][j]<11&&ID_status[i+1][j]>7) || ID_status[i+1][j]==-1) )  movable[i+1][j]=99;
		if(j+1<8&&( (ID_status[i][j+1]<11&&ID_status[i][j+1]>7) || ID_status[i][j+1]==-1) )  movable[i][j+1]=99;
	}
	if(kind==4){  //�� 
		if(i-1>=0&&( (ID_status[i-1][j]<12&&ID_status[i-1][j]>7) || ID_status[i-1][j]==-1) )  movable[i-1][j]=99;
		if(j-1>=0&&( (ID_status[i][j-1]<12&&ID_status[i][j-1]>7) || ID_status[i][j-1]==-1) )  movable[i][j-1]=99;
		if(i+1<4&&( (ID_status[i+1][j]<12&&ID_status[i+1][j]>7) || ID_status[i+1][j]==-1) )  movable[i+1][j]=99;
		if(j+1<8&&( (ID_status[i][j+1]<12&&ID_status[i][j+1]>7) || ID_status[i][j+1]==-1) )  movable[i][j+1]=99;	
	}
	if(kind==5){  //�H 
		if(i-1>=0&&( (ID_status[i-1][j]<13&&ID_status[i-1][j]>7) || ID_status[i-1][j]==-1) )  movable[i-1][j]=99;
		if(j-1>=0&&( (ID_status[i][j-1]<13&&ID_status[i][j-1]>7) || ID_status[i][j-1]==-1) )  movable[i][j-1]=99;
		if(i+1<4&&( (ID_status[i+1][j]<13&&ID_status[i+1][j]>7) || ID_status[i+1][j]==-1) )  movable[i+1][j]=99;
		if(j+1<8&&( (ID_status[i][j+1]<13&&ID_status[i][j+1]>7) || ID_status[i][j+1]==-1) )  movable[i][j+1]=99;	
	}
	if(kind==6){  //�h 
		if(i-1>=0&&( (ID_status[i-1][j]<14&&ID_status[i-1][j]>7) || ID_status[i-1][j]==-1) )  movable[i-1][j]=99;
		if(j-1>=0&&( (ID_status[i][j-1]<14&&ID_status[i][j-1]>7) || ID_status[i][j-1]==-1) )  movable[i][j-1]=99;
		if(i+1<4&&( (ID_status[i+1][j]<14&&ID_status[i+1][j]>7) || ID_status[i+1][j]==-1) )  movable[i+1][j]=99;
		if(j+1<8&&( (ID_status[i][j+1]<14&&ID_status[i][j+1]>7) || ID_status[i][j+1]==-1) )  movable[i][j+1]=99;
	}
	if(kind==7){  //�N 
		if(i-1>=0&&( (ID_status[i-1][j]<15&&ID_status[i-1][j]>8) || ID_status[i-1][j]==-1) )  movable[i-1][j]=99;   //���F�L���i�H�Y 
		if(j-1>=0&&( (ID_status[i][j-1]<15&&ID_status[i][j-1]>8) || ID_status[i][j-1]==-1) )  movable[i][j-1]=99;
		if(i+1<4&&( (ID_status[i+1][j]<15&&ID_status[i+1][j]>8) || ID_status[i+1][j]==-1) )  movable[i+1][j]=99;
		if(j+1<8&&( (ID_status[i][j+1]<15&&ID_status[i][j+1]>8) || ID_status[i][j+1]==-1) )  movable[i][j+1]=99;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(kind==8){  //���L 
		if(i-1>=0&&(ID_status[i-1][j]==1||ID_status[i-1][j]==7||ID_status[i-1][j]==-1) )  movable[i-1][j]=99;
		if(j-1>=0&&(ID_status[i][j-1]==1||ID_status[i][j-1]==7||ID_status[i][j-1]==-1) )  movable[i][j-1]=99; 
		if(i+1<4&&(ID_status[i+1][j]==1||ID_status[i+1][j]==7||ID_status[i+1][j]==-1) )  movable[i+1][j]=99;
		if(j+1<8&&(ID_status[i][j+1]==1||ID_status[i][j+1]==7||ID_status[i][j+1]==-1) )  movable[i][j+1]=99;	
	}
	if(kind==9){  //���� 
		int exist=0;
		if(i-1>=0&&ID_status[i-1][j]==-1)  movable[i-1][j]=99;
	    if(j-1>=0&&ID_status[i][j-1]==-1) movable[i][j-1]=99; 
	    if(i+1<4&&ID_status[i+1][j]==-1)  movable[i+1][j]=99;
	    if(j+1<8&&ID_status[i][j+1]==-1) movable[i][j+1]=99;
		for(int m=1;m<4;m++){
			if(i-m>=0){
				if(ID_status[i-m][j]!=-1)exist++;
				if(exist==2&&ID_status[i-m][j]<8&&ID_status[i-m][j]>0)   movable[i-m][j]=99;
			}
		}
		exist=0;
		for(int m=1;m<4;m++){
			if(i+m<4){
				if(ID_status[i+m][j]!=-1)	exist++;
				if(exist==2&&ID_status[i+m][j]<8&&ID_status[i+m][j]>0)   movable[i+m][j]=99;
			}
		}
		exist=0;
		for(int m=1;m<8;m++){
			if(j+m<8){
				if(ID_status[i][j+m]!=-1)	exist++;
				if(exist==2&&ID_status[i][j+m]<8&&ID_status[i][j+m]>0)   movable[i][j+m]=99;
			}
		}
		exist=0;
		for(int m=1;m<8;m++){
			if(j-m>=0){
				if(ID_status[i][j-m]!=-1)	exist++;
				if(exist==2&&ID_status[i][j-m]<8&&ID_status[i][j-m]>0)   movable[i][j-m]=99;				
			}
		}
	}
	if(kind==10){  //���� 
		if(i-1>=0&&( (ID_status[i-1][j]<4&&ID_status[i-1][j]>0) || ID_status[i-1][j]==-1) )  movable[i-1][j]=99;
		if(j-1>=0&&( (ID_status[i][j-1]<4&&ID_status[i][j-1]>0) || ID_status[i][j-1]==-1) )  movable[i][j-1]=99; 
		if(i+1<4&&( (ID_status[i+1][j]<4&&ID_status[i+1][j]>0) || ID_status[i+1][j]==-1) )  movable[i+1][j]=99;
		if(j+1<8&&( (ID_status[i][j+1]<4&&ID_status[i][j+1]>0) || ID_status[i][j+1]==-1) )  movable[i][j+1]=99;
	}
	if(kind==11){  //���� 
		if(i-1>=0&&( (ID_status[i-1][j]<5&&ID_status[i-1][j]>0) || ID_status[i-1][j]==-1) )  movable[i-1][j]=99;
		if(j-1>=0&&( (ID_status[i][j-1]<5&&ID_status[i][j-1]>0) || ID_status[i][j-1]==-1) )  movable[i][j-1]=99; 
		if(i+1<4&&( (ID_status[i+1][j]<5&&ID_status[i+1][j]>0) || ID_status[i+1][j]==-1) )  movable[i+1][j]=99;
		if(j+1<8&&( (ID_status[i][j+1]<5&&ID_status[i][j+1]>0) || ID_status[i][j+1]==-1) )  movable[i][j+1]=99;
	}
	if(kind==12){  //���� 
		if(i-1>=0&&( (ID_status[i-1][j]<6&&ID_status[i-1][j]>0) || ID_status[i-1][j]==-1) )  movable[i-1][j]=99;
		if(j-1>=0&&( (ID_status[i][j-1]<6&&ID_status[i][j-1]>0) || ID_status[i][j-1]==-1) )  movable[i][j-1]=99; 
		if(i+1<4&&( (ID_status[i+1][j]<6&&ID_status[i+1][j]>0) || ID_status[i+1][j]==-1) )  movable[i+1][j]=99;
		if(j+1<8&&( (ID_status[i][j+1]<6&&ID_status[i][j+1]>0) || ID_status[i][j+1]==-1) )  movable[i][j+1]=99;
	}
	if(kind==13){  //���h  
		if(i-1>=0&&( (ID_status[i-1][j]<7&&ID_status[i-1][j]>0) || ID_status[i-1][j]==-1) )  movable[i-1][j]=99;
		if(j-1>=0&&( (ID_status[i][j-1]<7&&ID_status[i][j-1]>0) || ID_status[i][j-1]==-1) )  movable[i][j-1]=99; 
		if(i+1<4&&( (ID_status[i+1][j]<7&&ID_status[i+1][j]>0) || ID_status[i+1][j]==-1) )  movable[i+1][j]=99;
		if(j+1<8&&( (ID_status[i][j+1]<7&&ID_status[i][j+1]>0) || ID_status[i][j+1]==-1) )  movable[i][j+1]=99;
	}
	if(kind==14){  //�� 
		if(i-1>=0&&( (ID_status[i-1][j]<8&&ID_status[i-1][j]>1) || ID_status[i-1][j]==-1) )  movable[i-1][j]=99;
		if(j-1>=0&&( (ID_status[i][j-1]<8&&ID_status[i][j-1]>1) || ID_status[i][j-1]==-1) )  movable[i][j-1]=99; 
		if(i+1<4&&( (ID_status[i+1][j]<8&&ID_status[i+1][j]>1) || ID_status[i+1][j]==-1) )  movable[i+1][j]=99;
		if(j+1<8&&( (ID_status[i][j+1]<8&&ID_status[i][j+1]>1) || ID_status[i][j+1]==-1) )  movable[i][j+1]=99;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void MainWindow::eat_or_move(int eat_x,int eat_y,int eat_ID,int eaten_x,int eaten_y,int eaten_ID){
	QLabel *label=new QLabel();
	QMovie *movie = new QMovie("dataset/eat.gif");
	label->setMovie(movie);
	turn++;
	time_turn++;
	if(eaten_ID!=-1){
		if(eaten_ID>7&&eaten_ID<15) eaten[0].push_back(eaten_ID);
		else eaten[1].push_back(eaten_ID);
	}
	
	if(eaten_ID==-1) tie++;
	else tie=0;
	
	if(eaten_ID>0){                             //�Y�l�ʵe
		label->show();
		label->setGeometry(-100,230,300,300);
		movie->start();
	}
	
	ID_status[eat_x][eat_y]=-1;
	ID_status[eaten_x][eaten_y]=eat_ID;
	update_to_move_array();
}
void MainWindow::isdark_slots(){
	if (dark==1){
		isdark->setText("Change to invisibly eat ");
		this->repaint();
		dark=0;
	}
	else{
		isdark->setText("Change to continuously eat ");
		this->repaint();
		dark=1;
	}
}
void MainWindow::counting_slots(){
	time_turn++;
	int_sum_time++;
	QString print_turn_time;
	print_turn_time=QString("time pass by:%2 s").arg(time_turn);
	player_time->setText(print_turn_time);
	QString print_total_time;
	print_total_time=QString("Total time:%1 s").arg(int_sum_time);
	sum_time->setText(print_total_time);
	
	
	if(time_turn==15){
		QLabel *label=new QLabel();
		QMovie *timeup = new QMovie("dataset/timeup.gif");
		label->setMovie(timeup); 
		label->show();
		label->setGeometry(100,230,480,270);
		timeup->start();
		Timer->stop();
	}
	else return;
	
}
//���URestart��A���U�ت�l�� 
void MainWindow::start_slots(){
	start->setText("Restart the game");
	press_x=99;
	press_y=99;
	turn=99;
	warning=0;
	turn_dicision=0;
	eaten[0].clear();
	eaten[1].clear();
	//��Ҧ��Ѥl½�^�I�� 
	for(int i=0;i<4;i++){
		for(int j=0;j<8;j++){
			ID_status[i][j]=0;
		}
	}
	time_turn=0;
	int_sum_time=0;
	this->repaint();
	Timer->start(1000);
}
void MainWindow::help_slots(){
	QLabel *label=new QLabel();
	QMovie *Help = new QMovie("dataset/help.gif");
	label->setMovie(Help); 
	label->show();
	label->setGeometry(100,230,1138,273);
	Help->start();
}
//�L��j���� 
void MainWindow::paintEvent(QPaintEvent *event) {
	QFont ft;
	ft.setPointSize(20);
	QPainter B(this); // Create a painter on this widget
	QPainter C(this);
	QPen pen,pen1; // Initialize a pen
	B.setRenderHint(QPainter::Antialiasing, true); // Set antialiasing
	pen.setColor(Qt::red);
	pen1.setColor(Qt::blue);
	B.setFont(ft);
	C.setFont(ft);
	C.setPen(pen);
	B.setPen(pen1);
	draw_plate(B);
	draw_chess(B);
	whose_turn(B);
	show_warning(C);
	show_gameover(C);
	show_tie(C);
}
	
//�L�X�ѽL 
void MainWindow::draw_plate(QPainter &B) {
	QImage image;
	image.load("./dataset/plate.png");
	B.drawImage(100,0,image);
}

void MainWindow::show_gameover(QPainter &C){   //�Y�䤤�@��Q�Y�o�Ѥl��16�ӡA�h�t�@����� 
	QLabel *label=new QLabel();
	QMovie *redwin = new QMovie("dataset/redwin.gif");
	QMovie *blackwin = new QMovie("dataset/blackwin.gif");
	
	
	if(eaten[0].size()==16){
		label->setMovie(blackwin); 
		label->show();
		label->setGeometry(100,230,400,400);
		blackwin->start();
		C.drawText(300,400,QString("Black WIN!!!!!!"));
		eaten[0].clear();
		end=1;
	} 
	if(eaten[1].size()==16){
		label->setMovie(redwin); 
		label->show();
		label->setGeometry(100,230,400,400);
		redwin->start();
		C.drawText(300,400,QString("RED WIN!!!!!!"));
		eaten[1].clear();
		end=1;
	}
	
}
void MainWindow::show_tie(QPainter &C){
	if(tie==15){
		C.drawText(300,400,QString("TIE!!!!!!"));
		Timer->stop();
	}
}
//0:back  1~7:�Ѥp��j�´� 8~14:�Ѥp��j���� 
void MainWindow::draw_chess(QPainter &B){
	To_Move.load("./dataset/ToMove");
	circle_frame.load("./dataset/frame");
	chess[0].load("./dataset/back");         //back
 	chess[1].load("./dataset/black7");       //�� 
 	chess[2].load("./dataset/black6");       //�� 
 	chess[3].load("./dataset/black5");       //�°� 
 	chess[4].load("./dataset/black4");       //�¨� 
 	chess[5].load("./dataset/black3");       //�H 
 	chess[6].load("./dataset/black2");       //�h 
 	chess[7].load("./dataset/black1");       //�N 
 	chess[8].load("./dataset/red7");         //�L 
 	chess[9].load("./dataset/red6");         //�� 
 	chess[10].load("./dataset/red5");        //�°� 
 	chess[11].load("./dataset/red4");        //���� 
 	chess[12].load("./dataset/red3");        //�� 
 	chess[13].load("./dataset/red2");        //�K 
 	chess[14].load("./dataset/red1");        //�� 
 	for(int m=0;m<4;m++){
 		for(int n=0;n<8;n++){      //�襤����l��m 
 			if(ID_status[m][n]!=-1)         //�u�n���O�S�� �N���L! 
 				B.drawImage(101+50*n,1+50*m,chess[ID_status[m][n]]); //�L�X�C�Ӧ�l�����p 
 			if(movable[m][n]==99){
 				B.drawImage(101+50*n,1+50*m,To_Move);
			}
    	}
 	}
 	//�L�X�Q�Y�o�Ѥl 
 	for(int i=0;i<2;i++){
 		for(int j=0;j<eaten[i].size();j++){
 			if(i==0) B.drawImage(QRect(70,1+26*j,25,25),chess[eaten[i][j]]);
 			else B.drawImage(QRect(505,1+26*j,25,25),chess[eaten[i][j]]);
		 }
	 }
 	B.drawImage(101+50*press_y,1+50*press_x,circle_frame);
}










