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
//��ʳ�� ������
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
void startlevel(int level,int mark);//��һ��ˢ�£���Ҫ�жϹؿ���
void everystep();
void makefood();//����ʳ��жϳ��ȣ����������Ž���һ�أ�




int main()
{
	title();
	while(1){}
	system("pause");
	return 0;
}

void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//�ҵ�����̨����
	COORD coord;//���ṹ��
	coord.X = x;
	coord.Y = y;//���ù��
	SetConsoleCursorPosition(handle, coord);//ͬ��������̨
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
		cout << "��";
		gotoxy(i, hei);
		cout << "��";
	}
	for (int i = 1; i <= hei; i++)
	{
		gotoxy(1, i);
		cout << "��";
		gotoxy(wid-1,i );
		cout << "��";
	}
	gotoxy(46,20);
	cout << "̰  ��  ��";
	gotoxy(44, 22);
	cout << "����Ӣ�����뷨";
	gotoxy(42, 30);
	load();
	cout << "�� �� Ϸ �� �� 1";
	if (levelnumber != 1)
	{
		gotoxy(42, 32);
		cout << "�� �� �� Ϸ �� �� 2";
	}
	gotoxy(42, 34);
	cout << "�� �� �� �� �� ��";
	while (key==0)
	{
		if (_kbhit())//���հ���
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
	//��ʳ�� ������(ռ�����ַ���
	srand((unsigned int)time(NULL));//�����������

	for (int i = 1; i <= wid; i += 2)
	{
		gotoxy(i, 1);
		cout << "��";
		gotoxy(i, hei);
		cout << "��";
	}
	for (int i = 1; i <= hei; i++)
	{
		gotoxy(1, i);
		cout << "��";
		gotoxy(wid - 1, i);
		cout << "��";
	}
	//��
	snake.len = 3;
	snake.speed = 300/level;
	snake.head.x = wid/ 2;
	snake.head.y = hei/ 2;
	gotoxy(snake.head.x, snake.head.y);
	printf("��");
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
		printf("��");
		*now.next = fuck;///��BUG
		cout << "4";
		now = fuck;
		cout << "5";

	}

	//ʳ��
	food.x = rand() % (wid- 4) + 2;
	food.y = rand() % (hei - 2) + 1;
	gotoxy(food.x, food.y);
	printf("��");
	while(1){}
}//��һ��ˢ�£���Ҫ�жϹؿ���
void everystep()
{
	
}
void makefood()
{

}//����ʳ��жϳ��ȣ����������Ž���һ�أ�