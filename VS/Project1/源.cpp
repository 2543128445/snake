#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<fstream>
#define wid 100
#define hei 50
#define snakesize 1000
//⊙食物 ■蛇身
using namespace std;
struct { int x, y; } food;
 typedef struct Node
{
	int x, y;
	struct Node*next;
};
struct 
{
	Node head;
	Node tail;
	int len;
}snake;
int levelnumber=1, mark=0,move,longer;
void title();
void gotoxy(int x, int y);
void load();
void save();
void stepone();//第一步刷新，需要判断关卡数
void everystep();
void makefood();//产生食物，判断长度，产生传送门进下一关；




int main()
{
	title();
	while(1){}
	system("pause");
	return 0;
}

void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//找到控制台窗口
	COORD coord;//光标结构体
	coord.X = x;
	coord.Y = y;//设置光标
	SetConsoleCursorPosition(handle, coord);//同步到控制台
}
void load()
{
	ifstream input;
	input.open("save.txt");
	input >> levelnumber >> mark;
	input.close();
}
void save()
{
	ofstream output;
	output.open("save.txt");
	output << levelnumber << mark;
	output.close();
}
void title()
{
	for (int i = 1; i <= wid; i += 2)
	{
		gotoxy(i, 1);
		cout << "■";
		gotoxy(i, hei);
		cout << "■";
	}
	for (int i = 1; i <= hei; i++)
	{
		gotoxy(1, i);
		cout << "■";
		gotoxy(wid-1,i );
		cout << "■";
	}
	gotoxy(46,20);
	cout << "贪  吃  蛇";
	gotoxy(44, 22);
	cout << "请用英文输入法";
	gotoxy(42, 30);
	load();
	cout << "新 游 戏 请 按 1";
	if (levelnumber != 1)
	{
		gotoxy(42, 32);
		cout << "继 续 游 戏 请 按 2";
	}
	gotoxy(42, 34);
	cout << "退 出 请 按 3";
}
void stepone()
{

}//第一步刷新，需要判断关卡数
void everystep()
{

}
void makefood()
{

}//产生食物，判断长度，产生传送门进下一关；