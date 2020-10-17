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
Node now,really;
struct 
{
	Node head;
	Node tail;
	int len,speed;
}snake;
int levelnumber=1, mark=0,longer=0,key=0;
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
		system("cls");
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
		startlevel(1, 0);
		
		return;
	}
	if (key == '2')
	{
		system("cls");
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
		startlevel(levelnumber, mark);
		return;
	}
	exit(0);
}
void startlevel(int level, int mark)
{
	//⊙食物 ■蛇身(占两个字符）
	srand((unsigned int)time(NULL));//随机函数种子

	//记得清除标题

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
	snake.head.x = (wid/ 2)-1;
	snake.head.y = hei/ 2;
	gotoxy(snake.head.x, snake.head.y);
	printf("■");
	now.x = snake.head.x - 2;
	now.y = snake.head.y;
	gotoxy(now.x, now.y);
	printf("■");
	snake.head.next = &now;
	for (int i = 1; i <= snake.len-2; i++)
	{
		Node temp;
		temp.x = now.x - 2;
		temp.y = now.y;
		gotoxy(temp.x, temp.y);
		printf("■");
		now.next = &temp;
	}
	//食物
	
	while (1)
	{
		int flag = 1;
		food.x = rand() % (wid - 4) + 2;
		food.y = rand() % (hei - 2) + 1;		
		Node q = snake.head;
		for (int k = 1; k <= snake.len; k++)
		{
			Node temp;
			temp = q;
			//cout << temp.x << " ";
			if (temp.x == food.x && temp.y == food.y)
			{
				flag = 0;
				break;
			}
			
			if(k!=snake.len) q = *temp.next;
		}
		
		if (flag && (food.x % 2)-1 == 0)break;
	}
	gotoxy(food.x, food.y);
	printf("⊙");
	key = 'd';
	while (1)
	{
		makefood();
		
		Sleep(snake.speed);
		everystep();
		//if ()//死没死，过关没过关，吃没吃屎
	}
}//第一步刷新，需要判断关卡数
void makefood()
{
	if (snake.head.x == food.x && snake.head.y == food.y)
	{
		srand((unsigned int)time(NULL));
		while (1)
		{
			int flag=1;
			food.x = rand() % (wid - 4) + 2;
			food.y = rand() % (hei - 2) + 1;
			Node now = snake.head;
			for (int k = 1; k <= snake.len; k++)
			{
				Node temp;
				temp = now;
				if (temp.x == food.x && temp.y == food.y)
				{
					flag = 0; 
					break;
				}
				now = *temp.next;
			}
			if (flag && food.x % 2 == 0)break;
		}
		gotoxy(food.x, food.y);
		printf("⊙");
		longer++;//在思考什么时候加长度，和什么时候产生传送门。。。
	}

}//产生食物产生传送门；
void everystep()
{
	if (_kbhit())
	{
		//有按键就接受
		fflush(stdin);
		int temp= _getch();
		if (temp == 'w' || temp == 'W' || temp == 's' || temp == 'S' || temp == 'a' || temp == 'A' || temp == 'd' || temp == 'D' || temp == 32 || temp == 'E')
			key = temp;
	}
	Node ready, temp,wuqwww=snake.head;
	temp = *wuqwww.next;

	//gotoxy(4, 4);
	//cout << temp.x << temp.y<<snake.head.x<<snake.head.y;

	switch (key)
	{
		
	case'w':
	case'W':
		if (snake.head.x != temp.x||(snake.head.x == temp.x&&snake.head.y== temp.y-1))
		{
			ready = snake.head;
			snake.head.y--;
			snake.head.next = &ready;

		}
		break;
	case's':
	case'S':
		if (snake.head.x != temp.x || (snake.head.x == temp.x && snake.head.y == temp.y+1))
		{
			ready = snake.head;
			snake.head.y++;
			snake.head.next = &ready;
		}
		break;
	case'a':
	case'A':
		
		if (snake.head.y != temp.y || (snake.head.y == temp.y && snake.head.x == temp.x - 2))
		{
			ready = snake.head;
			snake.head.x-=2;
			snake.head.next = &ready;
		}
		break;
	case'd':
	case'D':
 		if (snake.head.y != temp.y || (snake.head.y == temp.y && snake.head.x == temp.x + 2))
		{
			ready = snake.head;
			snake.head.x+=2;
			snake.head.next = &ready;
			gotoxy(wid + 2, hei - 2);
		}
		break;
	}
	//还差功能按键判断
	if (longer != 0)
	{
		Node q;
		snake.len++;
		q = snake.head;
		gotoxy(q.x, q.y);
		cout << "■";
		longer--;
		
	}
	else
	{
		Node q=snake.head;
		for (int i = 1; i <= snake.len; i++)
		{
			gotoxy(q.x, q.y);
			cout << "■";
			if (i != snake.len)  q = *q.next;
			else snake.tail = q;
		}
		Node e;
		e = *q.next;
		gotoxy(e.x, e.y);
		cout << "  ";
	}
	gotoxy(wid + 2, 0);

}

