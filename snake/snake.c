#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<mmsystem.h>
#include<conio.h>
#include<stdbool.h>
#include"�����ͻ���.h"//��ռ�ռ��ķ���ͷ�ļ���
#include"resource.h"
#pragma comment(lib,"winmm.lib")//�ֶ���ӿ�
void firstpage(void);//��ҳ
void firstpage_music(void);//��ҳ����
//void empty_cmd(void);//�����ҳ
void stopmusic(void);//ֹͣ����
void startgame(void);//��ʼ��Ϸ(��ť)
void ground(void);//��Ϸ�߿�
void snake_pos(void);//�ߵ��������
void draw_snake(void);//����
void empty_snake(void);//ȥ�����߲���
void change_dir(void);//�ı䷽��
bool snake_die(void);//�����ж�
void snake_food(void);//��ʳ��
void snake_up(void);//�߱䳤
void gotoxy();

//��ҳ
void firstpage(void)
{

	printf("\n"); printf("\n"); printf("\n");
	printf("				************************************************\n");
	printf("\n"); printf("\n"); printf("\n");
	printf("				*           <���ͳ�����һ��van����Ϸ>          *\n");
	printf("				*          van������ʾ:			       *\n");
	printf("				*          1. W A S D �������ߵķ���           *\n");
	printf("				*          2. �� ��ʼ��Ϸ                      *\n");
	printf("\n"); printf("\n"); printf("\n");
	printf("				************************************************\n");
	printf("\n"); printf("\n"); printf("\n");

}

//��������(������wav��ʽ��)
//void firstpage_music(void)
//{
//	//����·�����ļ�������·��
//	//���·������Ҫִ�е��ļ����ڵ�λ��һ��
//	PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC);//������Դ���ڲ���Ҫ��ͷ�ļ�
//}
//
//void game_music(void)
//{
//	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
//}

void startgame(void)
{
	//���ո�ʼ��Ϸ
	char start;
	while (1)//����ѭ��
	{
		start = _getch();
		if (' ' == start)//����ո�ʱ����ѭ����ʼ��Ϸ
		{
			break;
		}
	}
}

//����ֹͣ(���߸�����������)
void stopmusic(void)
{

	PlaySound(NULL, 0, 0);
}

//void empty_cmd(void)
//{
//	//��տ���̨���棬׼��������Ϸ����
//	system("cls");
//}

//ר�Ļ�����emmmmm
void background(void)
{
	int i = 0;
	for (i = 0; i < 29; i++)
	{
		printf(black_ground[i]);
	}
}

void snake_pos(void)
{
	//���������
	srand((unsigned int)time(NULL));//������
	//������ķ�Χ
	int x = (rand() % 19) + 1;//1~19
	int y = (rand() % 27) + 1;//1~27

	//��ʼ���ߵ������ڵ�(����)
	//ͷ
	arr_snake[0][0] = y;//��
	arr_snake[0][1] = 2 * x;//��
	arr_snake[0][2] = to_west;//����
	//��
	arr_snake[1][0] = y;//��
	arr_snake[1][1] = 2 * x + 2;//��
	arr_snake[0][2] = to_west;//����
	//β
	arr_snake[2][0] = y;//��
	arr_snake[2][1] = 2 * x + 4;//��
	arr_snake[2][2] = to_west;//����


	draw_snake();
}

void draw_snake(void)
{
	int i = 0;
	for (i = 0; arr_snake[i][0] != 0; i++)//��ӡ3���ڵ�
	{
		//�ַ����Դ�\0������"��"���������ַ���������ֱ�Ӹ�ֵ������ʱ���\0���ƹ�ȥ����ֹͣ������Ҫ�涨ֻ���������ַ���ȥ
		//�ѷ�����������������ڵ��õ�������
		strncpy(&black_ground[arr_snake[i][0]][arr_snake[i][1]], "��", 2);
	}
}
//�߶�
void snake_move(void)
{
	int i = snake_max_long - 1;//100��Ԫ�أ������±�ֻ��99

	empty_snake();//����߲���

	for (i; i > 0; i--)//ѭ������������
	{
		//��Ϊ���ǳ�ʼ���������鶼Ϊ0�����Ա���ʱ��Ϊ0˵�������������ϵ���һ���֣����Թ��˵�0�Ĳ���
		if (0 == arr_snake[i][1])
		{
			continue;
		}
		//��ǰһ���ڵ��x�������һ���ڵ㣬�µ��ߵ�λ��װ����������
		arr_snake[i][0] = arr_snake[i - 1][0];//����x������
		arr_snake[i][1] = arr_snake[i - 1][1];
		arr_snake[i][2] = arr_snake[i - 1][2];
	}
	//��ͷ
	arr_snake[0][2] = snake_dir;//���������ҵ��ƶ���ֵ�����Խ�����һ�����ж�(�ϱ�ʱ1��-1������ʱ2��-2)
	if (to_east == arr_snake[0][2] || to_west == arr_snake[0][2])//������ļ�������ʱִ��if������ִ��else
	{
		arr_snake[0][1] += arr_snake[0][2];//�����ƶ��ж�,�������������ʱ�ͳ���ǰλ�ü����뷽���С (-2��2)λ��
	}
	else
	{
		arr_snake[0][0] += arr_snake[0][2];//�����ƶ��ж����������������ʱ�ͳ���ǰλ�ü����뷽���С(-1��1)λ��
	}
	draw_snake();
}
//ȥ�����߲���
void empty_snake(void)
{
	int i = 0;
	for (i = 0; arr_snake[i][0] != 0; i++)
	{
		strncpy(&black_ground[arr_snake[i][0]][arr_snake[i][1]], "  ", 2);
	}
}
//�ı䷽��
void change_dir(void)
{
	if (GetAsyncKeyState('W'))
	{
		if (arr_snake[0][2] != to_south)
		{
			snake_dir = to_north;
		}
	}
	else if (GetAsyncKeyState('S'))
	{
		if (arr_snake[0][2] != to_north)
		{
			snake_dir = to_south;
		}
	}
	else if (GetAsyncKeyState('A'))
	{
		if (arr_snake[0][2] != to_east)
		{
			snake_dir = to_west;
		}
	}
	else if (GetAsyncKeyState('D'))
	{
		if (arr_snake[0][2] != to_west)
		{
			snake_dir = to_east;
		}
	}
}

//�������ж�
bool snake_die(void)
{
	if (to_west == arr_snake[0][2] || to_east == arr_snake[0][2])
	{
		//���������ƶ���ʱ���в����ж���arr_snake[0][0](��),arr_snake[0][1] + arr_snake[0][2](��)
		//����������������+����ļ�λ��С��������һ�����꣬������һ����������ж�
		//strncmp������0����������Ƚϵ��ַ������(��Ҫ�Ĳ������ַ������׵�ַ)
		if (0 == (strncmp(&black_ground[arr_snake[0][0]][arr_snake[0][1] + arr_snake[0][2]], "��", 2) /*||  0 == (strncmp(&black_ground[arr_snake[0][0]][arr_snake[0][1] + arr_snake[0][2]], "��", 2))*/))//��������ͷ����һ����
		{
			return false;
		}
	}
	else
	{
		//�в����ж�
		if (0 == (strncmp(&black_ground[arr_snake[0][0] + arr_snake[0][2]][arr_snake[0][1]], "��", 2) /*|| 0 == (strncmp(&black_ground[arr_snake[0][0] + arr_snake[0][2]][arr_snake[0][1]], "��", 2))*/))
		{
			return false;
		}
	}
	return true;
}

//����ʳ��
void snake_food(void)
{
	//�����������

	//�ж��Ƿ���Ҫ�����µ�ʳ��
	if (crea_food == 0)//����Ҫ����ʳ��
	{
		return;
	}

	srand((unsigned int)time(NULL));
	while (1)
	{
		int mark = 1;
		//��Ϊ�����ж�ԭ��ʳ����ڱ߿��ԵĻ��߻��޷���ò�ת��(��ת����޷���ȡ)����������+2ʹ�������±�x=2��y=2��ʼ
		food_x = (rand() % 18) + 2;//ʵ�ʷ�ΧӦ����1~21�������Χ����21���У�(0~20)+1==1~21
		food_y = (rand() % 25) + 2;
		int i;//��������

		for (i = 0; arr_snake[i][0] != 0; i++)
		{
			if (food_x * 2 == arr_snake[i][1] && food_y == arr_snake[i][0])//ʳ��ĺ���������ߵĺ����������Ա�,���غϣ������²���һ�������
			{
				mark = 0;//��ǵ�ǰ�Ĳ����㲻�غϵ���������������whileѭ��
				break;//һ���غϲ��־�����forѭ��������ÿ���ڵ㶼�ж��Ƿ��غϣ����Ч��
			}
		}
		if (mark == 1)
		{
			break;//��������������whileѭ��
		}

	}

	//��ʳ��
	strncpy(&black_ground[food_y][food_x * 2], "��", 2);//�������2�����ֽڣ���������Ϊ[y][x]
	crea_food = 0;//����ʳ���ֵһ��0����ֹ����ʳ�����
}

//�߱䳤
void snake_up(void)
{
	//��ͷ�����ʳ�������غ�ʱβ������1
	if (arr_snake[0][0] == food_y && arr_snake[0][1] == food_x * 2)
	{
		//����
		if (arr_snake[0][2] == to_east)
		{
			arr_snake[snake_long + 1][0] = arr_snake[snake_long][0];//�����ƶ�ʱ�����겻��
			arr_snake[snake_long + 1][1] = arr_snake[snake_long][1] + to_west;//���ƶ�ʱ��β����������һ��
			arr_snake[snake_long + 1][2] = arr_snake[snake_long][2];//���򲻱�
		}
		else if (arr_snake[0][2] == to_west)
		{
			arr_snake[snake_long + 1][0] = arr_snake[snake_long][0];//�����ƶ�ʱ�����겻��
			arr_snake[snake_long + 1][1] = arr_snake[snake_long][1] + to_east;
			arr_snake[snake_long + 1][2] = arr_snake[snake_long][2];//���򲻱�
		}
		else if (arr_snake[0][2] == to_north)
		{
			arr_snake[snake_long + 1][0] = arr_snake[snake_long][0] + to_south;
			arr_snake[snake_long + 1][1] = arr_snake[snake_long][1];//�������ƶ�ʱ�����겻��
			arr_snake[snake_long + 1][2] = arr_snake[snake_long][2];//���򲻱�
		}
		else if (arr_snake[0][2] == to_south)
		{
			arr_snake[snake_long + 1][0] = arr_snake[snake_long][0] + to_north;
			arr_snake[snake_long + 1][1] = arr_snake[snake_long][1];//�����ƶ�ʱ�����겻��
			arr_snake[snake_long + 1][2] = arr_snake[snake_long][2];//���򲻱�
		}

		snake_long++;
		crea_food = 1;//����ʳ����Ϊtrue
		g_score += 10;//��һ��ʳ���10��

	}
}

//�Ƿ�
void score(void)
{
	COORD rd;
	rd.X = 55;
	rd.Y = 15;
	//���ù��λ������Ϸ�����Ҳ�
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("������%d", g_score);
	COORD sd;
	sd.X = 55;
	sd.Y = 16;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), sd);
	if (to_east == arr_snake[0][2])
	{
		printf("�ԶԶԣ�����");
	}
	if (to_west == arr_snake[0][2])
	{
		printf("�ԶԶԣ�����");
	}
	if (to_north == arr_snake[0][2])
	{
		printf("�ԶԶԣ�����");
	}
	if (to_south == arr_snake[0][2])
	{
		printf("�ԶԶԣ�����");
	}

}

int main(void)
{
	//��ҳ����
	/*firstpage_music();*/
	//��ʾ��ҳ
	firstpage();
	//�ո������Ϸ����
	startgame();
	//ֹͣ����
	stopmusic();
	/*game_music();*/
	//��տ���̨��������ʾ����
	system("cls");
	//���λ����ʾ�ߣ���Ϊֻ��Ҫ��ʾһ��ʼ��һ�Σ������Ҫ������Ϸ��
	snake_pos();
	background();

	//����,�ظ����ú��������Ի�����
	while (1)
	{
		gotoxy(0, 0);//����˿���̨���������˸
		snake_food();//����ʳ��
		snake_up();//�߱䳤
		change_dir();//�ı䷽��
		
		//�������߲���д���⣬��Ϊ�ڻ������Ժ�ֱ������Ļ��൱��ÿ�ζ����»���һ���ߣ����޷��ж���һ��λ���Ƿ����Լ���
		if (false == snake_die())
		{
			system("cls");
			printf("��ϲ�㣬������\n");
			printf("������������: %d\n", g_score);
			break;
		}
		snake_move();//�߶�	
		background();//����
		score();//����
		Sleep(100);

	}
	system("pause");
	return 0;
}
//�������˸���⣬���Ǿ���ʵ�ַ������ǲ���ô��
void gotoxy(unsigned char x, unsigned char y)
{
	COORD cor;
	HANDLE hout;
	cor.X = x;
	cor.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, cor);
}