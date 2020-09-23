// ConsoleApplication2.cpp : 定義主控台應用程式的進入點。
//變色龍

#include<iostream>
#include<ctime>
#include<vector>
#include<string>
#include <iomanip>
#include <stdlib.h>
#include<algorithm>
#include <windows.h>
using namespace std;

//此函數為判斷某牌為甚麼顏色,自定義1~63之數字除7後，不同餘數對應不同顏色，64~66為加2卡，67~76為彩色卡
string kind_of_card(int num_of_card){
	string kind;
	if (num_of_card < 64 && num_of_card % 7 == 0){
		kind = "pink";
		return kind;
	}
	else if (num_of_card < 64 && num_of_card % 7 == 1){
		kind = "red";
		return kind;
	}
	else if (num_of_card < 64 && num_of_card % 7 == 2){
		kind = "blue";
		return kind;
	}
	else if (num_of_card < 64 && num_of_card % 7 == 3){
		kind = "yellow";
		return kind;
	}
	else if (num_of_card < 64 && num_of_card % 7 == 4){
		kind = "gray";
		return kind;
	}
	else if (num_of_card < 64 && num_of_card % 7 == 5){
		kind = "darkred";
		return kind;
	}
	else if (num_of_card < 64 && num_of_card % 7 == 6){
		kind = "green";
		return kind;
	}
	else if (num_of_card <= 66 && num_of_card >= 64){
		kind = "Allcolor";
		return kind;
	}
	else if (num_of_card <= 76 && num_of_card >= 67){
		kind = "bonus";
		return kind;
	}
	else if (num_of_card == 99){
		kind = "Caution";
		return kind;
	}
}

//此函為印出當前的各種狀況 (牌庫剩餘牌數 & 玩家有哪些牌 & 檯面上的牌堆有哪些)
void Status_in_time(vector<int>cards_in_depot, vector<int>cards_on_hand[5], vector<int>cards_in_stack[5], int num_of_player, int round){
	system("cls");
	cout << "Round:" << round << endl << endl;
	//以下計算牌庫剩餘牌數
	cout << "The Rest of cards : " << cards_in_depot.size() << endl << endl;
	int num_of_pink = 0, num_of_blue = 0, num_of_red = 0, num_of_green = 0, num_of_yellow = 0; //這些變數為每個顏色出現的次數
	int num_of_darkred = 0, num_of_gray = 0, num_of_bonus = 0, num_of_Allcolor = 0, caution = 0;
	for (int i = 0; i < num_of_player; i++){ //開始計算每個玩家每個顏色出現的次數
		cout << "Player " << i + 1 << " : ";
       num_of_pink = 0, num_of_blue = 0, num_of_red = 0, num_of_green = 0, num_of_yellow = 0;
	   num_of_darkred = 0, num_of_gray = 0, num_of_bonus = 0, num_of_Allcolor = 0;
		for (int j = 0; j < cards_on_hand[i].size(); j++){
			if (kind_of_card(cards_on_hand[i][j]) == "pink")
				num_of_pink++;
			if (kind_of_card(cards_on_hand[i][j]) == "blue")
				num_of_blue++;
			if (kind_of_card(cards_on_hand[i][j]) == "red")
				num_of_red++;
			if (kind_of_card(cards_on_hand[i][j]) == "green")
				num_of_green++;
			if (kind_of_card(cards_on_hand[i][j]) == "yellow")
				num_of_yellow++;
			if (kind_of_card(cards_on_hand[i][j]) == "darkred")
				num_of_darkred++;
			if (kind_of_card(cards_on_hand[i][j]) == "gray")
				num_of_gray++;
			if (kind_of_card(cards_on_hand[i][j]) == "bonus")
				num_of_bonus++;
			if (kind_of_card(cards_on_hand[i][j]) == "Allcolor")
				num_of_Allcolor++;
		}
		//有被拿回手裡的牌才印出來
		if (num_of_pink > 0)
			cout << setw(10) << "pink*" << num_of_pink << " ";
		if (num_of_red > 0)
			cout << setw(10) << "red*" << num_of_red << " ";
		if (num_of_blue > 0)
			cout << setw(10) << "blue*" << num_of_blue << " ";
		if (num_of_green > 0)
			cout << setw(10) << "green*" << num_of_green << " ";
		if (num_of_yellow > 0)
			cout << setw(10) << "yellow*" << num_of_yellow << " ";
		if (num_of_darkred > 0)
			cout << setw(10) << "darkred*" << num_of_darkred << " ";
		if (num_of_gray > 0)
			cout << setw(10) << "gray*" << num_of_gray << " ";
		if (num_of_bonus > 0)
			cout << setw(10) << "bonus*" << num_of_bonus << " ";
		if (num_of_Allcolor > 0)
			cout << setw(10) << "Allcolor*" << num_of_Allcolor << " ";
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < num_of_player; i++){
		cout << "Stack " << i + 1 << " : ";
		num_of_pink = 0, num_of_blue = 0, num_of_red = 0, num_of_green = 0, num_of_yellow = 0;//這些變數為每個顏色出現的次數
		num_of_darkred = 0, num_of_gray = 0, num_of_bonus = 0, num_of_Allcolor = 0, caution = 0;
		//開始計算每個顏色出現的次數
		for (int j = 0; j < cards_in_stack[i].size(); j++){
			if (kind_of_card(cards_in_stack[i][j]) == "pink")
				num_of_pink++;
			if (kind_of_card(cards_in_stack[i][j]) == "blue")
				num_of_blue++;
			if (kind_of_card(cards_in_stack[i][j]) == "red")
				num_of_red++;
			if (kind_of_card(cards_in_stack[i][j]) == "green")
				num_of_green++;
			if (kind_of_card(cards_in_stack[i][j]) == "yellow")
				num_of_yellow++;
			if (kind_of_card(cards_in_stack[i][j]) == "darkred")
				num_of_darkred++;
			if (kind_of_card(cards_in_stack[i][j]) == "gray")
				num_of_gray++;
			if (kind_of_card(cards_in_stack[i][j]) == "bonus")
				num_of_bonus++;
			if (kind_of_card(cards_in_stack[i][j]) == "Allcolor")
				num_of_Allcolor++;
			if (kind_of_card(cards_in_stack[i][j]) == "Caution")
				caution++;
		}
		//有被放進牌堆的牌才印出來
		if (num_of_pink > 0)
			cout << setw(10) << "pink*" << num_of_pink << " ";
		if (num_of_red > 0)
			cout << setw(10) << "red*" << num_of_red << " ";
		if (num_of_blue > 0)
			cout << setw(10) << "blue*" << num_of_blue << " ";
		if (num_of_green > 0)
			cout << setw(10) << "green*" << num_of_green << " ";
		if (num_of_yellow > 0)
			cout << setw(10) << "yellow*" << num_of_yellow << " ";
		if (num_of_darkred > 0)
			cout << setw(10) << "darkred*" << num_of_darkred << " ";
		if (num_of_gray > 0)
			cout << setw(10) << "gray*" << num_of_gray << " ";
		if (num_of_bonus > 0)
			cout << setw(10) << "bonus*" << num_of_bonus << " ";
		if (num_of_Allcolor > 0)
			cout << setw(10) << "Allcolor*" << num_of_Allcolor << " ";
		if (caution > 0)
			cout << setw(10) << "Do not put the card you draw here until the next round starts! ";
		cout << endl;
	}
	cout << endl;
}

int main()
{
	vector<int >depot; //使用vector(stock)存取牌庫的卡牌
	vector<int>cards_on_hand[5]; //一列存取一玩家手上的牌，最多為5個玩家，直接設有5個row的二維矩陣
	vector<int>stack[5];//暫存被放在桌上牌堆的牌
	int num_of_player = 0,round = 1; //玩家數
	//洗牌動作：隨機產生76個1~76的不重複的值存入stock，自定義1~63之數字除7後，不同餘數對應不同顏色，64~66為加2卡，67~76為彩色卡
	srand((unsigned)time(NULL));
	for (int m = 0; m < 76; m++){
		int a;
		a = rand() % 76 + 1;
		depot.push_back(a);
		for (int n = 0; n < m; n++){
			if (depot[m] == depot[n]) {
				m--;
				depot.pop_back();
			}
		}
	}

	string who_to_play_with;
	cout << "Who do you want to player with? Computer or Friends? [c,f]\n";
	while (1)
	{
		cin >> who_to_play_with; //玩家輸入要跟誰玩
		if (who_to_play_with == "c" || who_to_play_with == "C" || who_to_play_with == "F" || who_to_play_with == "f") {
			cout << "Please enter the # of players (3~5 players includes you)\n";   //決定玩家數
			while (1) {
				cin >> num_of_player;
				if (num_of_player > 5 || num_of_player < 3)
					cout << "Sorry, the # of players can only be 3~5\n";
				else
					break;
			}

			//遊戲一開始先發牌給大家
			for (int i = 0; i < num_of_player; i++){
				cards_on_hand[i].push_back(depot.back());
				depot.pop_back();
			}
			Status_in_time(depot, cards_on_hand, stack, num_of_player, round);

			while (depot.size() > 15) {
				int num_of_stacks_be_taken_in_a_round = 0;   //紀錄一回合有幾次牌堆被收走，全收走即開始另一回合
				vector<int>has_taken[5];            //紀錄此玩家已拿走牌堆,在下一輪開始前,不會輪到他玩

				//新的一輪先清空
				for (int i = 0; i < 5; i++) {
					has_taken[i].clear();
					stack[i].clear();
				}

				while (1) {
					if (depot.size() < 15)
						break;
					//遊戲主要運作區,為了可以保留前一輪結束玩家是誰,此處終止條件設到不可能到達的次數,用i=i% num_of_player表示輪到的玩家
					for (int i = 1; i <= 999999; i++) {
						int j = 0;
						//計算一輪是否已結束(當有一玩家拿走牌堆,num_of_stacks_be_taken_in_a_round就+1,加到與玩家數相同時,及代表牌堆都被拿走,並重開下一輪)
						if (num_of_stacks_be_taken_in_a_round == num_of_player) {
							if (depot.size() < 15)
								break;
							round++;    //回合數+1
							for (int p = 0; p < 5; p++) {   //每輪開始前先清空
								has_taken[p].clear();
								stack[p].clear();
								Status_in_time(depot, cards_on_hand, stack, num_of_player, round);
							}
							num_of_stacks_be_taken_in_a_round = 0;
							i--;
						}
						i = i % num_of_player;
						if (i == 0)
							i = num_of_player;
						for (int m = 0; m < num_of_player; m++) {
							if (stack[m].size() >= 3)
								j++;
						}
						while (has_taken[i - 1].size() != 0)
							i++;
						if (i > num_of_player)
							i = 1;
						int k = 0;
						if (j == num_of_player)
							k = 1;

					LLL:cout << "It's player" << i << "'s turn." << endl;
						if (k == 1) {
							cout << "Now you only can choose to take away a stack, which stack do you want to take?\n";
							int take; //欲拿走的牌堆
							if (i == 1 || who_to_play_with == "f" || who_to_play_with == "F") {    //輪到自己,只能選擇拿走排堆
								cin >> take;
								if (take<1 || take>num_of_player)
									cout << "Sorry, please choose stack1~stack" << num_of_player << endl;
								else if (stack[take - 1].size() == 4)
									cout << "Sorry, the stack you choose has be taken, please choose again\n";
								else {
									int size_of_stack = stack[take - 1].size();   //將stack的牌拿走
									for (int j = 0; j < size_of_stack; j++) {
										cards_on_hand[i - 1].push_back(stack[take - 1].back());
										stack[take - 1].pop_back();
									}
									has_taken[i - 1].push_back(1);     //此玩家i-1已拿走牌堆,在他專屬的vector做一個記號, 在下一輪開始前, 不會輪到他玩
									for (int j = 0; j < 4; j++) {      //將收走的牌堆的vector塞99 99 99 99
										stack[take - 1].push_back(99);
										num_of_stacks_be_taken_in_a_round++;
										Status_in_time(depot, cards_on_hand, stack, num_of_player, round);
									}
									if (num_of_stacks_be_taken_in_a_round == num_of_player)
										break;
									i++;
									if (i > num_of_player)
										i = 1;
									goto LLL;
								}
							}
							else if (i != 1 && (who_to_play_with == "c" || who_to_play_with == "C"))   //輪到電腦,有牌堆就拿
							{
							MMM:
								take = rand() % num_of_player + 1;
								cout << take << endl;
								system("pause");
								if (take<1 || take>num_of_player)
									cout << "Sorry, please choose stack1~stack" << num_of_player << endl;
								else if (stack[take - 1].size() == 4)
									cout << "Sorry, the stack you choose has be taken, please choose again\n";
								else {
									int size_of_stack = stack[take - 1].size();//將stack的牌拿走
									for (int j = 0; j < size_of_stack; j++) {
										cards_on_hand[i - 1].push_back(stack[take - 1].back());
										stack[take - 1].pop_back();
									}
									has_taken[i - 1].push_back(1);//此玩家已拿走牌堆,在他專屬的vector做一個記號, 在下一輪開始前, 不會輪到他玩
									for (int j = 0; j < 4; j++)
										stack[take - 1].push_back(99);//將收走的牌堆的vector塞99 99 99 99
									num_of_stacks_be_taken_in_a_round++;
									Status_in_time(depot, cards_on_hand, stack, num_of_player, round);
								}
							}
							if (num_of_stacks_be_taken_in_a_round == num_of_player)
								break;
							i++;
							if (i > num_of_player)
								i = 1;
							goto MMM;
							}
							if ((stack[0].size() == 0 || stack[0].size() > 3) && (stack[1].size() == 0 || stack[1].size() > 3) && (stack[2].size() == 0 || stack[2].size() > 3) && (stack[3].size() == 0 || stack[3].size() > 3) && (stack[4].size() == 0 || stack[4].size() > 3))
							{
								if (i == 1 || who_to_play_with == "f" || who_to_play_with == "F") {   //因檯面無牌可以收，此時只能抽牌
									while (1) {
										cout << "Please draw a card" << endl;
										cout << "Draw or not? [y/n]" << endl;//詢問玩家是否要抽卡
										char draw[40];
										cin >> draw;
										if (draw[0] == 'n' || draw[0] == 'N')
											cout << "Sorry, You should draw a card" << endl;
										else if (draw[0] == 'y' || draw[0] == 'Y') {
											cout << "The card is " << kind_of_card(depot.back()) << endl;//用函數判斷這張牌是甚麼
											cout << "Which stack do you want to put it? (stack1~stack" << num_of_player << ")" << endl;//抽完牌放牌堆
											while (1) {
												int stack_to_put;
												cin >> stack_to_put;
												if (stack_to_put > 0 && stack_to_put <= num_of_player) {
													if (stack[stack_to_put - 1].size() < 3) {
														stack[stack_to_put - 1].push_back(depot.back());
														depot.pop_back();
														Status_in_time(depot, cards_on_hand, stack, num_of_player, round);
														break;
													}
													else
														cout << "Sorry, the stack you choose has been taken, please choose again\n";
												}
												else
													cout << "Sorry, Please enter 1~" << num_of_player << endl;
											}
											break;
										}
										else
											cout << "Sorry, Please enter y or n" << endl;
									}
								}
								else if (i != 1 && (who_to_play_with == "c" || who_to_play_with == "C")) {
									cout << "Please draw a card" << endl;
									cout << "Draw or not? [y/n]" << endl;//詢問玩家是否要抽卡
									system("pause");
									char draw[40] = { "y" };
									cout << "y\n";
									system("pause");
									cout << "The card is " << kind_of_card(depot.back()) << endl;//用函數判斷這張牌是甚麼
									cout << "Which stack do you want to put it? (stack1~stack" << num_of_player << ")" << endl;//抽完牌放牌堆
									system("pause");
									while (1) {
										int stack_to_put;
										stack_to_put = rand() % num_of_player + 1;
										cout << stack_to_put << endl;
										if (stack_to_put > 0 && stack_to_put <= num_of_player) {
											if (stack[stack_to_put - 1].size() < 3) {
												stack[stack_to_put - 1].push_back(depot.back());
												depot.pop_back();
												Status_in_time(depot, cards_on_hand, stack, num_of_player, round);
												break;
											}
											else
												cout << "Sorry, the stack you choose has been taken, please choose again\n";
										}
										else
											cout << "Sorry, Please enter 1~" << num_of_player << endl;
									}
									break;
								}
							}
							else {
								cout << "What do you wanna do next? Take a stack away or draw a card?[take/draw]\n";//檯面上有牌,可選擇抽排或拿牌堆
								if (i == 1 || who_to_play_with == "f" || who_to_play_with == "F") {
									while (1) {
										string choose;
										cin >> choose;
										if (choose == "take") {
											while (1) {
												cout << "Which stack do you want to take?(stack1~stack" << num_of_player << ")" << endl;
												int take; //欲拿走的牌堆
												cin >> take;
												if (take<1 || take>num_of_player)
													cout << "Sorry, please choose stack1~stack" << num_of_player << endl;
												else if (stack[take - 1].size() < 1)
													cout << "Sorry, the stack you choose is empty, please choose again\n";
												else if (stack[take - 1].size() == 4)
													cout << "Sorry, the stack you choose has be taken, please choose again\n";
												else {
													int size_of_stack = stack[take - 1].size();//將stack的牌拿走
													for (int j = 0; j < size_of_stack; j++) {
														cards_on_hand[i - 1].push_back(stack[take - 1].back());
														stack[take - 1].pop_back();
													}
													has_taken[i - 1].push_back(1);      //此玩家已拿走牌堆,在他專屬的vector做一個記號, 在下一輪開始前, 不會輪到他玩
													for (int j = 0; j < 4; j++)
														stack[take - 1].push_back(99);  //將收走的牌堆的vector塞99 99 99 99
													num_of_stacks_be_taken_in_a_round++;
													Status_in_time(depot, cards_on_hand, stack, num_of_player, round);
													break;
												}
											}
											break;
										}
										else if (choose == "draw") {
											cout << "The card is " << kind_of_card(depot.back()) << endl;  //用函數判斷這張牌是甚麼
											cout << "Which stack do you want to put it? (stack1~stack" << num_of_player << ")" << endl;//抽完牌只能放牌堆
											while (1) {
												int stack_to_put;
												cin >> stack_to_put;
												if (stack_to_put > 0 && stack_to_put <= num_of_player) {
													if (stack[stack_to_put - 1].size() < 3) {
														stack[stack_to_put - 1].push_back(depot.back());
														depot.pop_back();
														Status_in_time(depot, cards_on_hand, stack, num_of_player, round);
														break;
													}
													else if (stack[stack_to_put - 1].size() == 3)
														cout << "Sorry, the stack you choose is full, please choose again\n";
													else if (stack[stack_to_put - 1].size() == 4)
														cout << "Sorry, the stack you choose has been taken, please choose again\n";
												}
												else
													cout << "Sorry, Please enter 1~" << num_of_player << endl;
											}
											break;
										}
										else
											cout << "Sorry, please enter take or not [take/draw]\n";
									}
								}
								else if (i != 1 && (who_to_play_with == "c" || who_to_play_with == "C")) {
									while (1) {
										string choose;
										int a = rand() % 2;
										system("pause");
										if (a == 0) {
											choose = "take";
											cout << "take\n";
											system("pause");
										}
										else {
											choose = "draw";
											cout << "draw\n";
											system("pause");
										}
										if (choose == "take") {
											while (1) {
												cout << "Which stack do you want to take?(stack1~stack" << num_of_player << ")" << endl;
												int take; //欲拿走的牌堆
												take = rand() % num_of_player + 1;
												cout << take << endl;
												system("pause");
												if (take<1 || take>num_of_player)
													cout << "Sorry, please choose stack1~stack" << num_of_player << endl;
												else if (stack[take - 1].size() < 1)
													cout << "Sorry, the stack you choose is empty, please choose again\n";
												else if (stack[take - 1].size() == 4)
													cout << "Sorry, the stack you choose has be taken, please choose again\n";
												else {
													int size_of_stack = stack[take - 1].size();//將stack的牌拿走
													for (int j = 0; j < size_of_stack; j++) {
														cards_on_hand[i - 1].push_back(stack[take - 1].back());
														stack[take - 1].pop_back();
													}
													has_taken[i - 1].push_back(1);//此玩家已拿走牌堆,在他專屬的vector做一個記號, 在下一輪開始前, 不會輪到他玩
													for (int j = 0; j < 4; j++)
														stack[take - 1].push_back(99);//將收走的牌堆的vector塞99 99 99 99
													num_of_stacks_be_taken_in_a_round++;
													Status_in_time(depot, cards_on_hand, stack, num_of_player, round);
													break;
												}
											}
											break;
										}
										else if (choose == "draw") {
											//用函數判斷這張牌是甚麼
											cout << "The card is " << kind_of_card(depot.back()) << endl;
											//抽完牌放牌堆
											cout << "Which stack do you want to put it? (stack1~stack" << num_of_player << ")" << endl;
											while (1) {
												int stack_to_put;
												stack_to_put = rand() % num_of_player + 1;
												cout << stack_to_put << endl;
												system("pause");
												if (stack_to_put > 0 && stack_to_put <= num_of_player) {
													if (stack[stack_to_put - 1].size() < 3) {
														stack[stack_to_put - 1].push_back(depot.back());
														depot.pop_back();
														Status_in_time(depot, cards_on_hand, stack, num_of_player, round);
														break;
													}
													else if (stack[stack_to_put - 1].size() == 3)
														cout << "Sorry, the stack you choose is full, please choose again\n";
													else if (stack[stack_to_put - 1].size() == 4)
														cout << "Sorry, the stack you choose has been taken, please choose again\n";
												}
												else
													cout << "Sorry, Please enter 1~" << num_of_player << endl;
											}
											break;
										}
									}
								}
							}
						}
					}
				}
				break;
			}
		else
			cout << "Sorry, please enter c or f\n";
	}
	//開始算分數
	Status_in_time(depot, cards_on_hand, stack, num_of_player, round);
	int num_of_pink = 0, num_of_blue = 0, num_of_red = 0, num_of_green = 0, num_of_yellow = 0; //這些變數為每個玩家每個顏色出現的次數
	int num_of_darkred = 0, num_of_gray = 0, num_of_bonus = 0, num_of_Allcolor = 0, caution = 0;
	int score[5];//紀錄每個玩家分數
	int score_compare[5];//亦為記錄玩家分數,但裡面數字會拿來排序
	for (int i = 0; i < num_of_player; i++) {//開始計算每個顏色出現的次數
		num_of_pink = 0, num_of_blue = 0, num_of_red = 0, num_of_green = 0, num_of_yellow = 0;
		num_of_darkred = 0, num_of_gray = 0, num_of_bonus = 0, num_of_Allcolor = 0;
		for (int j = 0; j < cards_on_hand[i].size(); j++){
			if (kind_of_card(cards_on_hand[i][j]) == "pink")
				num_of_pink++;
			if (kind_of_card(cards_on_hand[i][j]) == "blue")
				num_of_blue++;
			if (kind_of_card(cards_on_hand[i][j]) == "red")
				num_of_red++;
			if (kind_of_card(cards_on_hand[i][j]) == "green")
				num_of_green++;
			if (kind_of_card(cards_on_hand[i][j]) == "yellow")
				num_of_yellow++;
			if (kind_of_card(cards_on_hand[i][j]) == "darkred")
				num_of_darkred++;
			if (kind_of_card(cards_on_hand[i][j]) == "gray")
				num_of_gray++;
			if (kind_of_card(cards_on_hand[i][j]) == "bonus")
				num_of_bonus++;
			if (kind_of_card(cards_on_hand[i][j]) == "Allcolor")
				num_of_Allcolor++;
		}
		//使用C++內建函數做排序
		int color_cards[7] = { num_of_pink, num_of_blue, num_of_red, num_of_green, num_of_yellow,num_of_darkred, num_of_gray };
		sort(color_cards, color_cards + 7);     //升冪排序
		reverse(color_cards, color_cards + 7);    //轉成降冪
		//把彩色卡加進去
		int m = 0;
		for (int i = 0; i < 3; i++){
			while (m < num_of_Allcolor){
				if (color_cards[i] < 6){
					color_cards[i]++;
					m++;
				}
				else
					break;
			}
		}
		for (int i = 0; i < 7; i++)
			cout << color_cards[i] << " ";
		//加分部分
		int score_plus = 0;
		for (int i = 0; i < 3; i++)
			score_plus = score_plus + ((color_cards[i] * (color_cards[i] + 1)) / 2);
		//減分部分
		int score_minus = 0;
		for (int i = 3; i < 7; i++)	{
			if (color_cards[i] != 0)
				score_minus = score_minus + ((color_cards[i] + (color_cards[i] + 1)) / 2);
			else
				break;
		}
		int Total_score;  //Total score of each player
		Total_score = score_plus - score_minus + (2 * num_of_bonus);
		//cout << score_plus << " " << score_minus << " " << 2 * num_of_bonus;
		score[i] = Total_score;
		score_compare[i] = Total_score;
		cout << "The score of player " << i + 1 << " is " << Total_score << endl;
	}
	sort(score_compare, score_compare + 7);     //升冪排序
	reverse(score_compare, score_compare + 7);    //轉成降冪
    //此時score[0]為最高分
	for (int i = 0; i < num_of_player; i++)
	{
		if (score_compare[0] == score[i])
			cout << "The winner is player " << i + 1 << endl;
	}

    system("pause");
	return 0;

}