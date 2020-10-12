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
struct Node
{
	int x, y;
	struct Node *next;
};
Node now;
struct 
{
	Node head;
	Node tail;
	int len,speed;
}snake;
int levelnumber=1, mark=0,move,longer,key=0;
void title();
void gotoxy(int x, int y);
void load();
void save();
void startlevel(int level,int mark);//第一步刷新，需要判断关卡数
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
	cout << "退 出 请 随 便 按";
	while (key==0)
	{
		if (_kbhit())//接收按键
		{
			fflush(stdin);
			key = _getch();
		}
	}
	if (key == '1')
	{
		startlevel(1, 0);
		
		return;
	}
	if (key == '2')
	{
		startlevel(levelnumber, mark);
		return;
	}
	exit(0);
}
void startlevel(int level, int mark)
{
	//⊙食物 ■蛇身(占两个字符）
	srand((unsigned int)time(NULL));//随机函数种子

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
		gotoxy(wid - 1, i);
		cout << "■";
	}
	//蛇
	snake.len = 3;
	snake.speed = 300/level;
	snake.head.x = wid/ 2;
	snake.head.y = hei/ 2;
	gotoxy(snake.head.x, snake.head.y);
	printf("■");
	now = snake.head;
	for (int i = 1; i <= snake.len; i++)
	{
		Node fuck;
		cout << "1";
		fuck.x = now.x - 2;
		cout << "2";
		fuck.y = now.y;
		cout << "3";
		gotoxy(fuck.x, fuck.y);
		printf("■");
		*now.next = fuck;///有BUG
		cout << "4";
		now = fuck;
		cout << "5";

	}

	//食物
	food.x = rand() % (wid- 4) + 2;
	food.y = rand() % (hei - 2) + 1;
	gotoxy(food.x, food.y);
	printf("⊙");
	while(1){}
}//第一步刷新，需要判断关卡数
void everystep()
{
	
}
void makefood()
{

}//产生食物，判断长度，产生传送门进下一关；