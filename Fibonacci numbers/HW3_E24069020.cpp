// HW3_E24069020.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
using namespace std;

int main()
{
	
	int Fn; //宣告一變數 代表Fibonacci 的第n項之值
	int n; //項數
	int counter=1; //計算時計次數
	int box1=1, box2=1, box3; //計算時用來暫存數值的小箱子

	cout  << "Please enter a n, and I will show you the nth number of the Fibonacci sequence  " << endl;
	cin  >> n;

	if (n == 0) 
		Fn = 0;
	else if (n == 1 || n== 2)
		Fn = 1;
	else {
		while (counter <= n-2) {  //n要減2，因為前兩項已被定義為0,1

			
			Fn = box1+box2; //Fn為前兩項之積
			cout << "the " << counter+2 << "th number of the Fibonacci sequence is " << Fn << endl; //counter要加
			box1 = box2; // 
			box2 = Fn;


			counter++;
		}

	}

	system("pause");
	return 0;
}

