// HW5_E24069020.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
using namespace std;
void Hanoi(int p,char A,char B, char C) //設計函數,p表示盤子數量,A表示塔1(from),B表示塔2(by),C表示塔3(to)
{
	if (p == 1)
	{
		cout << "Plates " << p << " move from tower " << A << " to tower " << C << endl;  
		return;
	}
	else
	{
		Hanoi(p - 1, A, C, B); //目的在把前p-1個的plates從A移到B,故to跟by對調
		cout << "Plates " << p << " move from tower " << A << " to tower " << C << endl;  
		Hanoi(p - 1, B, A, C);//目的在把前p-1個的plates從B移到C,故to跟by對調
		return;
	}
}
int main()
{
    cout << "Please input number of plates from 1 to 9:\n";
	int p;
    begin:cin >> p;
	if (p >= 1 && p <= 9)
	{
		Hanoi(p, 'A', 'B', 'C');
		cout << "win!" << endl;
	}
	else
	{
		cout << "Sorry, please enter the number of plates from 1 to 9:\n";
		goto begin;
	}
	return 0;
}


