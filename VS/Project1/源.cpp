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

struct eat{ int x, y; }shit[1000],boom,food;
struct Node
{
	int x, y;
	struct Node *next;
};
Node now,really,all[2000];
struct 
{
	Node head;
	Node tail;
	int len,speed;
}snake;
struct someone { string name; int goal; }NB[100];
int levelnumber=1, mark=0,longer=0,key=0,num=0,harder=1,people,shitnum=0;
void title();
void gotoxy(int x, int y);
void load();
void save();
void startlevel(int level,int mar);//��һ��ˢ�£���Ҫ�жϹؿ���
void everystep();
void makefood();
void makeshit();
void makeboom();
bool dieorlive();
void die();
bool cmp(someone a, someone b)
{
	return a.goal > b.goal;
}
int main()
{
	title();
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
	output << levelnumber <<' '<< mark;
	output.close();
}
void title()
{
	key = 0;
	ifstream input;
	input.open("rank.txt");
	input >> people;
	for (int i = 1; i <= people; i++)
	{
		input >> NB[i].name >> NB[i].goal;
	}
	sort(NB + 1, NB + people+1, cmp);
	input.close();
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
	gotoxy(46,16);
	cout << "̰  ��  ��";
	gotoxy(10, 22);
	cout << "��Ϸ˵��������Ӣ�����뷨����Ϊ�X�mLZY��д����bug�����������⾴���½�,����WASD�ƶ�";
	gotoxy(6, 24);
	cout << "���Ժ����ӳ��ȣ������Ե������ȡ�����һ�����Ⱥ���֡ѣ��Ժ������һ��,��Ϸ�����а�E�˳�";
	gotoxy(30, 26);
	cout << "�߳���Ϊ2ʱ�����˻������Ͼ�Ҫ��ͷ��������";
	gotoxy(42, 32);
	load();
	cout << "�� �� Ϸ �� �� 2";
	if (levelnumber != 1)
	{
		gotoxy(42, 30);
		cout << "�� �� �� Ϸ �� �� 1";
	}
	gotoxy(42, 34);
	cout << "�� ѡ �� �� �� �� �� �� �� 3";
	gotoxy(42, 36);
	cout << "�� �� �� �� �� �� �� 4";
	gotoxy(42, 38);
	cout << "�� �� �� �� �� �� �� �� ��";
	while (key==0)
	{
		if (_kbhit())//���հ���
		{
			fflush(stdin);
			key = _getch();
		}
	}
	system("cls");
	if (key == '2')
	{
		levelnumber = 1,mark=0;
		startlevel(1, 0);
		return;
	}
	if (key == '1')
	{
		startlevel(levelnumber, mark);
		return;
	}
	if (key == '3')
	{
		
		gotoxy(36, 20); cout << "�� �� �� �� �� �� �� ��";
		gotoxy(42, 30); cout << "�ؿ���"; cin >> levelnumber;
		gotoxy(42, 32); cout << "�Ѷȣ� "; cin >> harder;
		system("cls");
		startlevel(levelnumber, 0);
	}
	if (key == '4')
	{
		key = 0;
		ifstream input;
		input.open("rank.txt");
		input >> people;
		for (int i = 1; i <=people; i++)
		{
			input >> NB[i].name >> NB[i].goal;
		}
		sort(NB + 1, NB + people, cmp);
		input.close();
		gotoxy(36, 10); cout << "name                    mark";
		for (int i = 1; i <= min(people, 10); i++)
		{
			gotoxy(34, 10 + 2 * i); cout << i << ',' << NB[i].name;
			gotoxy(60, 10 + 2 * i); cout << NB[i].goal;
		}
		gotoxy(36, 12 + 2 * min(people, 10));
		cout << "�� �� �� �� �� �� ��  ";
		while (key == 0)
		{
			if (_kbhit())//���հ���
			{
				fflush(stdin);
				key = _getch();
			}
		}
		system("cls");
		title();
	}
	exit(0);
}
void startlevel(int level, int mar)
{
	gotoxy(40, 18); printf("�� %d ��   �� ����%d  �� �ȣ�%d", level, mar, harder);
	Sleep(3000);
	system("cls");
	levelnumber = level;
	mark = mar;
	save();
	//��ӡ��ͼ
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
	snake.speed = 500/(level+1);
	snake.head.x = (wid/ 2)-1;
	snake.head.y = hei/ 2;
	gotoxy(snake.head.x, snake.head.y);
	printf("��");
	now.x = snake.head.x - 2;
	now.y = snake.head.y;
	gotoxy(now.x, now.y);
	printf("��");
	snake.head.next = &now;
	for (int i = 1; i <= snake.len-2; i++)
	{
		Node temp;
		temp.x = now.x - 2;
		temp.y = now.y;
		gotoxy(temp.x, temp.y);
		printf("��");
		now.next = &temp;
	}
	//ʳ��
	
	while (1)
	{
		int flag = 1;
		food.x = rand() % (wid - 4) + 2;
		food.y = rand() % (hei - 2) + 1;
		if (food.x % 2 == 0||food.x==1||food.y==1||food.x==99||food.y==50) continue;
		Node q = snake.head;
		for (int k = 1; k <= snake.len; k++)
		{
			Node temp;
			temp = q;
			if (temp.x == food.x && temp.y == food.y)
			{
				flag = 0;
				break;
			}
			if (k != snake.len) q = *temp.next;
		}
		if (flag)break;
	}
	gotoxy(food.x, food.y);
	printf("��");

	//��ը��
	while (1)
	{
		int flag = 1;
		boom.x = rand() % (wid - 4) + 2;
		boom.y = rand() % (hei - 2) + 1;
		if (boom.x % 2 == 0 || boom.x == 1 || boom.y == 1 || boom.x == 99 || boom.y == 50||(boom.x==food.x&&boom.y==food.y)) continue;
		Node q = snake.head;
		for (int k = 1; k <= snake.len; k++)
		{
			Node temp;
			temp = q;
			if (temp.x == boom.x && temp.y == boom.y)
			{
				flag = 0;
				break;
			}
			if (k != snake.len) q = *temp.next;
		}
		if (flag)break;
	}
	gotoxy(boom.x, boom.y);
	printf("��");

	//�춾��
	shitnum = harder * levelnumber;
	while (1)
	{
		int flag = 1;
		shit[1].x = rand() % (wid - 4) + 2;
		shit[1].y = rand() % (hei - 2) + 1;
		if (shit[1].x % 2 == 0 || (shit[1].x == food.x && shit[1].y == food.y) || (shit[1].x == boom.x && shit[1].y == boom.y)|| shit[1].x == 1 || shit[1].y == 1 || shit[1].x == 99 || shit[1].y == 50) continue;
		Node q = snake.head;
		for (int k = 1; k <= snake.len; k++)
		{
			Node temp;
			temp = q;
			if (temp.x == shit[1].x && temp.y == shit[1].y)
			{
				flag = 0;
				break;
			}

			if (k != snake.len) q = *temp.next;
		}
		if (flag)break;
		
	}
	gotoxy(shit[1].x, shit[1].y);
	cout << "��";
	if (shitnum > 1)
	{
		for (int i = 2; i <= shitnum; i++)
		{
			while (1)
			{
				int flag = 1;
				shit[i].x = rand() % (wid - 4) + 2;
				shit[i].y = rand() % (hei - 2) + 1;
				if (shit[i].x % 2 == 0 || (shit[i].x == food.x && shit[i].y == food.y) || (shit[i].x == boom.x && shit[i].y == boom.y) || shit[i].x == 1 || shit[i].y == 1 || shit[i].x == 99 || shit[i].y == 50) continue;
				Node q = snake.head;
				for (int k = 1; k <= snake.len; k++)
				{
					Node temp;
					temp = q;
					if (temp.x == shit[i].x && temp.y == shit[i].y)
					{
						flag = 0;
						break;
					}
					if (k != snake.len) q = *temp.next;
				}
				for (int j = 1; j < i; j++)
				{
					if (shit[j].x == shit[i].x && shit[j].y == shit[i].y)
					{
						flag = 0;
						break;
					}
				}
				if (flag)break;
				
			}
			gotoxy(shit[i].x, shit[i].y);
			cout << "��";
		}
	}
	key = 'd';
	while (1)
	{
		//makeboom();
		makeshit();
		makefood();
		makeboom();
		Sleep(snake.speed);
		everystep();
	}
}//��һ��ˢ�£���Ҫ�жϹؿ���
void makefood()
{
	if (snake.head.x == food.x && snake.head.y == food.y)
	{
		if (snake.len < 20+10*levelnumber*harder ) 
		{
			srand((unsigned int)time(NULL));
			while (1)
			{
				int flag=1;
				food.x = rand() % (wid - 4) + 2;
				food.y = rand() % (hei - 2) + 2;
				if (food.x % 2 == 0 || food.x == 1 || food.y == 1 || food.x == 99 || food.y == 50 || (boom.x == food.x && boom.y == food.y)) continue;
				for (int i = 1; i <= shitnum; i++)
				{
					if (shit[i].x == food.x && shit[i].y == food.y) flag = 0;
				}
				if (flag == 0) continue;
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
				if (flag)break;
			}
			gotoxy(food.x, food.y);
			printf("��");
			longer++;
		}
		else
		{
			if (snake.len ==20+ 10 * levelnumber * harder)
			{
				srand((unsigned int)time(NULL));
				while (1)
				{
					int flag = 1;
					food.x = rand() % (wid - 4) + 2;
					food.y = rand() % (hei - 2) + 2;
					if (food.x % 2 == 0 || food.x == 1 || food.y == 1 || food.x == 99 || food.y == 50 || (boom.x == food.x && boom.y == food.y)) continue;
					for (int i = 1; i <= shitnum; i++)
					{
						if (shit[i].x == food.x && shit[i].y == food.y) flag = 0;
					}
					if (flag == 0) continue;
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
					if (flag)break;
					
				}
				gotoxy(food.x, food.y);
				printf("��");
				longer++;			
			}
			else
			{
				mark += snake.len;
				system("cls");
				startlevel(++levelnumber, mark);				
			}			
		}		
	}

}//����ʳ����������ţ�
void everystep()
{
	int xx=key;
	if (_kbhit())
	{
		//�а����ͽ���
		fflush(stdin);
		int temp= _getch();
		if (temp == 'w' || temp == 'W' || temp == 's' || temp == 'S' || temp == 'a' || temp == 'A' || temp == 'd' || temp == 'D' || temp == 32 || temp == 'E' || temp == 'e')
			xx = temp;
	}
	Node ready, temp,wuqwww=snake.head;
	temp = *wuqwww.next;
	switch (xx)
	{
		
	case'w':
	case'W':
		if (snake.head.x != temp.x||(snake.head.x == temp.x&&snake.head.y== temp.y-1))
		{
			key = xx;
			ready = snake.head;
			snake.head.y--;
			snake.head.next = &ready;
			gotoxy(wid + 2, 1);
		}
		else
		{
			ready = snake.head;
			snake.head.y++;
			snake.head.next = &ready;
			gotoxy(wid + 2,1);
		}
		break;
	case's':
	case'S':
		if (snake.head.x != temp.x || (snake.head.x == temp.x && snake.head.y == temp.y+1))
		{
			key = xx;
			ready = snake.head;
			snake.head.y++;
			snake.head.next = &ready;
			gotoxy(wid + 2, 1);
		}
		else
		{
			ready = snake.head;
			snake.head.y--;
			snake.head.next = &ready;
			gotoxy(wid + 2, 1);
		}
		break;
	case'a':
	case'A':	
		if (snake.head.y != temp.y || (snake.head.y == temp.y && snake.head.x == temp.x - 2))
		{
			key = xx;
			ready = snake.head;
			snake.head.x-=2;
			snake.head.next = &ready;
			gotoxy(wid + 2, 1);
		}
		else
		{
			ready = snake.head;
			snake.head.x += 2;
			snake.head.next = &ready;
			gotoxy(wid + 2, 1);
		}
		break;
	case'd':
	case'D':
 		if (snake.head.y != temp.y || (snake.head.y == temp.y && snake.head.x == temp.x + 2))
		{
			key = xx;
			ready = snake.head;
			snake.head.x+=2;
			snake.head.next = &ready;
			gotoxy(wid + 2, 1);
		}
		else
		{
			ready = snake.head;
			snake.head.x -= 2;
			snake.head.next = &ready;
			gotoxy(wid + 2, 1);
		}
		break;
	case'e':
	case'E':
		system("cls");
		title();
	}
	//ֻ��Ҫ��ʱά����������
	if (dieorlive()) die();
	if (longer > 0)
	{
		Node q;
		++snake.len;
		q = snake.head;
		gotoxy(q.x, q.y);
		cout << "��";
		longer--;
		all[(++num) % 1000] = *snake.head.next;
		num = num % 1000;
		snake.head.next = &all[num];
		for (int i = 2; i <= snake.len; i++)
		{
			if (i != snake.len)
			{
				Node q;
				q = *all[num].next;
				all[++num] = q;
				all[num - 1].next = &all[num];
			}

		}
		
	}
	else
	{
		if (longer == 0)
		{
			if (snake.len == 1)
			{
				gotoxy(snake.head.x, snake.head.y);
				cout<< "��";
				Node e = *snake.head.next;
				gotoxy(e.x, e.y);
				cout << "  ";
			}
			else
			{
				gotoxy(snake.head.x, snake.head.y);
				cout << "��";
				all[(++num) % 1000] = *snake.head.next;
				num = num % 1000;
				snake.head.next = &all[num];
				for (int i = 2; i <= snake.len; i++)
				{
					gotoxy(all[num].x, all[num].y);
					cout << "��";
					if (i != snake.len)
					{
						Node q;
						q = *all[num].next;
						all[++num] = q;
						all[num - 1].next = &all[num];
					}
				}
				Node e;
				e = *all[num].next;
				gotoxy(e.x, e.y);
				cout << "  ";
			}
		}
		if (longer == -1)
		{
			gotoxy(snake.head.x, snake.head.y);
			cout << "��";
			if (snake.len  == 2)
			{
				all[(++num) % 1000] = *snake.head.next;
				num = num % 1000;
				snake.head.next = &all[num];
				gotoxy(all[num].x, all[num].y);
				cout << " ";
				--snake.len;
				longer = 0;
			}
			else
			{
				all[(++num) % 1000] = *snake.head.next;
				num = num % 1000;
				snake.head.next = &all[num];
				for (int i = 2; i < snake.len; i++)
				{
					gotoxy(all[num].x, all[num].y);
					cout << "��";
					if (i != snake.len - 1)
					{
						Node q;
						q = *all[num].next;
						all[++num] = q;
						all[num - 1].next = &all[num];
					}
				}
				Node e;
				e = *all[num].next;
				gotoxy(e.x, e.y);
				cout << " ";
				e = *e.next;
				gotoxy(e.x, e.y);
				cout << " ";
				--snake.len;
				longer = 0;
			}
			
		}
		if (longer == -2)
		{
			gotoxy(snake.head.x, snake.head.y);
			cout << "��";
			int f = 1;
			if (snake.len % 2 == 0) f = 0; 
			snake.head.next = &all[num];
			if (f == 0)
			{
				for (int i = 2; i <= snake.len; i++)
				{
					gotoxy(all[num].x, all[num].y);
					if (i <= snake.len / 2)
						cout << "��";
					else
						cout << "  ";
					if (i != snake.len)
					{
						Node q;
						q = *all[num].next;
						all[++num] = q;
						all[num - 1].next = &all[num];
					}
				}
				snake.len = snake.len / 2;
			}
			if (f == 1)
			{
				for (int i = 2; i <= snake.len; i++)
				{
					gotoxy(all[num].x, all[num].y);
					if (i <= (snake.len +1)/2)
						cout << "��";
					else
						cout << "  ";
					if (i != snake.len)
					{
						Node q;
						q = *all[num].next;
						all[++num] = q;
						all[num - 1].next = &all[num];
					}
				}
				snake.len = (snake.len + 1) / 2;
			}
			Node e;
			e = *all[num].next;
			gotoxy(e.x, e.y);
			cout << "  ";
			longer = 0;
		}	
	}
	gotoxy(wid + 2, 0);
}
bool dieorlive()
{
	if (snake.head.x == 1 || snake.head.x == 99 || snake.head.y == 1 || snake.head.y == 50) return 1;
	Node s=*snake.head.next;
	for (int i = 1; i <= snake.len - 1; i++)
	{
		if (snake.head.x == s.x && snake.head.y == s.y) return 1;
		s = *s.next;
	}
	return 0;
}
void die()
{
	system("cls");
	for (int i = 1; i <= 10; i++)
	{
		gotoxy(45, 20 + i);
		cout << "Game Over!!";
	}
	Sleep(2000);
	system("cls");
	gotoxy(40, 20);
	cout << "�� 1 �� �� �� �� ��";
	gotoxy(40, 22);
	cout << "�� 2 �� �� �� �� �� ��";
	gotoxy(40, 24);
	cout << "�� 3 �� �� �� �� �� �� �� �� ��";
	gotoxy(40, 26);
	cout << "�� �� �� �� ��";
		key = 0;
	while (key == 0)
	{
		if (_kbhit())//���հ���
		{
			fflush(stdin);
			key = _getch();
		}
	}
	system("cls");
	switch (key)
	{
	case '1': startlevel(levelnumber, mark);
	case '2': title();
	case '3': 
		mark += snake.len;
		gotoxy(40, 22); cout << "����������:";
		cin >> NB[++people].name;
		NB[people].goal = mark;
		ofstream output;
		output.open("rank.txt");
		output << people<<' ';
		for (int i = 1; i <= people; i++)
			output << NB[i].name << ' ' << NB[i].goal;
		output.close();
		title();
	}
	exit(0);
}
void makeshit()
{
	for (int i = 1; i <= shitnum; i++)
	{
		if (shit[i].x == snake.head.x && shit[i].y == snake.head.y)
		{
			if (snake.len == 2) { die(); }
			else
			{

				srand((unsigned int)time(NULL));
				while (1)
				{
					int flag = 1;
					shit[i].x = rand() % (wid - 4) + 2;
					shit[i].y = rand() % (hei - 2) + 2;
					if (shit[i].x % 2 == 0||(shit[i].x==food.x&&shit[i].y==food.y) || (shit[i].x == boom.x && shit[i].y == boom.y) || shit[i].x == 1 || shit[i].y == 1 || shit[i].x == 99 || shit[i].y == 50) continue;
					for (int j = 1; j <= shitnum; j++)
					{
						if (shit[j].x == shit[i].x && shit[j].y == shit[i].y&&i!=j)
						{
							flag = 0;
							break;
						}
					}
					if (flag == 0) continue;
					Node now = snake.head;
					for (int k = 1; k <= snake.len; k++)
					{
						Node temp;
						temp = now;
						if (temp.x == shit[i].x && temp.y == shit[i].y)
						{
							flag = 0;
							break;
						}
						now = *temp.next;
					}
					if (flag)break;
				}
				gotoxy(shit[i].x, shit[i].y);
				printf("��");
				longer = -1;
			}
		}
	}
}
void makeboom()
{
	if (snake.head.x == boom.x && snake.head.y == boom.y)
	{
		if (snake.len == 2) { die(); }
		else
		{
			srand((unsigned int)time(NULL));
			while (1)
			{
				int flag = 1;
				boom.x = rand() % (wid - 4) + 2;
				boom.y = rand() % (hei - 2) + 2;
				if (boom.x % 2 == 0 || boom.x == 1 || boom.y == 1 || boom.x == 99 || boom.y == 50 || (boom.x == food.x && boom.y == food.y)) continue;
				for (int i = 1; i <= shitnum; i++)
				{
					if (shit[i].x == boom.x && shit[i].y == boom.y) flag = 0;
				}
				if (flag == 0) continue;
				Node now = snake.head;
				for (int k = 1; k <= snake.len; k++)
				{
					Node temp;
					temp = now;
					if (temp.x == boom.x && temp.y == boom.y)
					{
						flag = 0;
						break;
					}
					now = *temp.next;
				}
				if (flag)break;
			}
			gotoxy(boom.x, boom.y);
			printf("��");
			longer=-2;
		}	
	}

}
