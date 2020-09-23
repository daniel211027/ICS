// HW4_E24069020.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <ctime>

int main()
{
	int ans[4];   //預設答案
	int guess; //使用者猜測的數字
    begin:     //使用者想再玩一次遊戲時,程式跑來這裡開始
	int A=0, B=0;     //# of A & B
	
	srand((unsigned)time(NULL));  //隨時間變的變數
	int m = 0, n = 0;
	for (m = 0; m < 4; m++) //此區為隨機產生四字不重複亂數並存進矩陣ans[]
	{    
		ans[m] =rand()%9+1;      //隨機亂數存入矩陣ans
		for (n = 0; n < m; n++)
		{
			if (ans[m] == ans[n]) {
				m--;
				break;
			}
		}
	}
	/*for (m = 0; m < 4; m++) {
		cout << ans[m];
	}*/


	cout << "Please enter 4-digit number, each from 1~9. These 4 numbers cannot be the same.\n"<<endl ;
	start:cin >> guess;
	int guessArray[4]; //將輸入數字之各位數放入矩陣存著

	guessArray[0] = guess / 1000; //千位數
	guessArray[1] = (guess - guessArray[0] * 1000) / 100;  //百位數
	guessArray[2] = (guess - guessArray[0] * 1000 - guessArray[1] * 100) / 10;  //十位數
	guessArray[3] = (guess - guessArray[0] * 1000 - guessArray[1] * 100 - guessArray[2] * 10);  //個位數


	for (m = 0; m < 4; m++)   //檢查輸入數字是否重複
	{ 
		for (n = 0; n < m; n++)
			if (guessArray[m] == guessArray[n])
			{
				cout << "Sorry, the number cannot be the same to each other, Please enter again!" << endl;
				goto start;
			}
	} 
		
	
	for (int i = 0; i < 4; i++)  //計算幾A幾B
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j && ans[i] == guessArray[j])
			{
				A++;
			}
			else if (i != j && ans[i] == guessArray[j])
			{
				B++;
			}
		}
	}

	cout << "The result is " << A << "A" << B << "B";

	if (A == 4)
	{
		cout << "\nYOU WIN!!!" << endl;
		cout << "\nDo U want to play again? If yes, enter 1. If not, enter 0." << endl;   
		int game;
		cin >> game;
		if (game == 1) {
			goto begin;
		}
		else
			return 0;
	}

	else {
		cout << "\nPlease enter the number again\n" << endl;
		A = 0; //A跟B皆要初始化
		B = 0;
		goto start;
	}
	
	system("pause");

	return 0;
}


