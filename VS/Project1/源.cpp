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
void stepone();//��һ��ˢ�£���Ҫ�жϹؿ���
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
	cout << "�� �� �� �� 3";
}
void stepone()
{

}//��һ��ˢ�£���Ҫ�жϹؿ���
void everystep()
{

}
void makefood()
{

}//����ʳ��жϳ��ȣ����������Ž���һ�أ�