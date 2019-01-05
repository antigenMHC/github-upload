#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<mmsystem.h>
#include<conio.h>
#include<stdbool.h>
#include"背景和画蛇.h"//把占空间大的放在头文件中
#include"resource.h"
#pragma comment(lib,"winmm.lib")//手动添加库
void firstpage(void);//首页
void firstpage_music(void);//首页音乐
//void empty_cmd(void);//清空首页
void stopmusic(void);//停止音乐
void startgame(void);//开始游戏(按钮)
void ground(void);//游戏边框
void snake_pos(void);//蛇的随机产生
void draw_snake(void);//画蛇
void empty_snake(void);//去除旧蛇残留
void change_dir(void);//改变方向
bool snake_die(void);//死亡判断
void snake_food(void);//画食物
void snake_up(void);//蛇变长
void gotoxy();

//首页
void firstpage(void)
{

	printf("\n"); printf("\n"); printf("\n");
	printf("				************************************************\n");
	printf("\n"); printf("\n"); printf("\n");
	printf("				*           <来和程序张一起van♂游戏>          *\n");
	printf("				*          van♂心提示:			       *\n");
	printf("				*          1. W A S D 控制老蛇的方向           *\n");
	printf("				*          2. 按 开始游戏                      *\n");
	printf("\n"); printf("\n"); printf("\n");
	printf("				************************************************\n");
	printf("\n"); printf("\n"); printf("\n");

}

//播放音乐(必须是wav格式的)
//void firstpage_music(void)
//{
//	//绝对路径：文件的完整路径
//	//相对路径：和要执行的文件所在的位置一样
//	PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC);//加载资源在内部需要加头文件
//}
//
//void game_music(void)
//{
//	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
//}

void startgame(void)
{
	//按空格开始游戏
	char start;
	while (1)//无限循环
	{
		start = _getch();
		if (' ' == start)//输入空格时跳出循环开始游戏
		{
			break;
		}
	}
}

//音乐停止(或者更换播放音乐)
void stopmusic(void)
{

	PlaySound(NULL, 0, 0);
}

//void empty_cmd(void)
//{
//	//清空控制台界面，准备进入游戏界面
//	system("cls");
//}

//专心画背景emmmmm
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
	//产生随机数
	srand((unsigned int)time(NULL));//种种子
	//随机数的范围
	int x = (rand() % 19) + 1;//1~19
	int y = (rand() % 27) + 1;//1~27

	//初始化蛇的三个节点(身体)
	//头
	arr_snake[0][0] = y;//行
	arr_snake[0][1] = 2 * x;//列
	arr_snake[0][2] = to_west;//方向
	//身
	arr_snake[1][0] = y;//行
	arr_snake[1][1] = 2 * x + 2;//列
	arr_snake[0][2] = to_west;//方向
	//尾
	arr_snake[2][0] = y;//行
	arr_snake[2][1] = 2 * x + 4;//列
	arr_snake[2][2] = to_west;//方向


	draw_snake();
}

void draw_snake(void)
{
	int i = 0;
	for (i = 0; arr_snake[i][0] != 0; i++)//打印3个节点
	{
		//字符串自带\0，所以"●"带了三个字符，当我们直接赋值给数组时会吧\0复制过去，会停止，所以要规定只复制两个字符过去
		//把放在蛇数组里的三个节点拿到界面中
		strncpy(&black_ground[arr_snake[i][0]][arr_snake[i][1]], "█", 2);
	}
}
//蛇动
void snake_move(void)
{
	int i = snake_max_long - 1;//100个元素，但是下标只有99

	empty_snake();//清除蛇残留

	for (i; i > 0; i--)//循环遍历蛇数组
	{
		//因为我们初始化的蛇数组都为0，所以遍历时若为0说明不是蛇身体上的任一部分，可以过滤掉0的部分
		if (0 == arr_snake[i][1])
		{
			continue;
		}
		//把前一个节点的x坐标给后一个节点，新的蛇的位置装在了数组中
		arr_snake[i][0] = arr_snake[i - 1][0];//就是x的坐标
		arr_snake[i][1] = arr_snake[i - 1][1];
		arr_snake[i][2] = arr_snake[i - 1][2];
	}
	//蛇头
	arr_snake[0][2] = snake_dir;//将上下左右的移动赋值给它以进行下一步的判断(南北时1和-1，东西时2和-2)
	if (to_east == arr_snake[0][2] || to_west == arr_snake[0][2])//当输入的键是左右时执行if，上下执行else
	{
		arr_snake[0][1] += arr_snake[0][2];//左右移动列动,当输入的是左右时就朝当前位置加输入方向大小 (-2和2)位移
	}
	else
	{
		arr_snake[0][0] += arr_snake[0][2];//上下移动行动，当输入的是上下时就朝当前位置加输入方向大小(-1和1)位移
	}
	draw_snake();
}
//去除旧蛇残留
void empty_snake(void)
{
	int i = 0;
	for (i = 0; arr_snake[i][0] != 0; i++)
	{
		strncpy(&black_ground[arr_snake[i][0]][arr_snake[i][1]], "  ", 2);
	}
}
//改变方向
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

//蛇死亡判断
bool snake_die(void)
{
	if (to_west == arr_snake[0][2] || to_east == arr_snake[0][2])
	{
		//老蛇左右移动的时候行不动列动，arr_snake[0][0](行),arr_snake[0][1] + arr_snake[0][2](列)
		//这里代表的是列坐标+输入的键位大小，即是下一个坐标，并对下一个坐标进行判断
		//strncmp若返回0则代表两个比较的字符串相等(需要的参数是字符串的首地址)
		if (0 == (strncmp(&black_ground[arr_snake[0][0]][arr_snake[0][1] + arr_snake[0][2]], "█", 2) /*||  0 == (strncmp(&black_ground[arr_snake[0][0]][arr_snake[0][1] + arr_snake[0][2]], "〇", 2))*/))//背景上蛇头的下一个点
		{
			return false;
		}
	}
	else
	{
		//列不动行动
		if (0 == (strncmp(&black_ground[arr_snake[0][0] + arr_snake[0][2]][arr_snake[0][1]], "█", 2) /*|| 0 == (strncmp(&black_ground[arr_snake[0][0] + arr_snake[0][2]][arr_snake[0][1]], "〇", 2))*/))
		{
			return false;
		}
	}
	return true;
}

//产生食物
void snake_food(void)
{
	//产生随机坐标

	//判断是否需要产生新的食物
	if (crea_food == 0)//不需要产生食物
	{
		return;
	}

	srand((unsigned int)time(NULL));
	while (1)
	{
		int mark = 1;
		//因为死亡判断原因，食物放在边框旁的话蛇会无法获得并转身(或转身后无法获取)，所以我们+2使其数组下标x=2，y=2开始
		food_x = (rand() % 18) + 2;//实际范围应该是1~21，随机范围低于21都行，(0~20)+1==1~21
		food_y = (rand() % 25) + 2;
		int i;//遍历蛇身

		for (i = 0; arr_snake[i][0] != 0; i++)
		{
			if (food_x * 2 == arr_snake[i][1] && food_y == arr_snake[i][0])//食物的横纵坐标和蛇的横纵坐标做对比,若重合，则重新产生一个随机数
			{
				mark = 0;//标记当前的不满足不重合的条件，不能跳出while循环
				break;//一有重合部分就跳出for循环，不用每个节点都判断是否重合，提高效率
			}
		}
		if (mark == 1)
		{
			break;//满足条件后跳出while循环
		}

	}

	//画食物
	strncpy(&black_ground[food_y][food_x * 2], "※", 2);//横坐标乘2，两字节，背景数组为[y][x]
	crea_food = 0;//产生食物后赋值一个0，防止又有食物产生
}

//蛇变长
void snake_up(void)
{
	//蛇头坐标跟食物坐标重合时尾巴增长1
	if (arr_snake[0][0] == food_y && arr_snake[0][1] == food_x * 2)
	{
		//增长
		if (arr_snake[0][2] == to_east)
		{
			arr_snake[snake_long + 1][0] = arr_snake[snake_long][0];//向东西移动时纵坐标不变
			arr_snake[snake_long + 1][1] = arr_snake[snake_long][1] + to_west;//向东移动时蛇尾坐标往西加一格
			arr_snake[snake_long + 1][2] = arr_snake[snake_long][2];//方向不变
		}
		else if (arr_snake[0][2] == to_west)
		{
			arr_snake[snake_long + 1][0] = arr_snake[snake_long][0];//向东西移动时纵坐标不变
			arr_snake[snake_long + 1][1] = arr_snake[snake_long][1] + to_east;
			arr_snake[snake_long + 1][2] = arr_snake[snake_long][2];//方向不变
		}
		else if (arr_snake[0][2] == to_north)
		{
			arr_snake[snake_long + 1][0] = arr_snake[snake_long][0] + to_south;
			arr_snake[snake_long + 1][1] = arr_snake[snake_long][1];//向上下移动时横坐标不变
			arr_snake[snake_long + 1][2] = arr_snake[snake_long][2];//方向不变
		}
		else if (arr_snake[0][2] == to_south)
		{
			arr_snake[snake_long + 1][0] = arr_snake[snake_long][0] + to_north;
			arr_snake[snake_long + 1][1] = arr_snake[snake_long][1];//向东西移动时纵坐标不变
			arr_snake[snake_long + 1][2] = arr_snake[snake_long][2];//方向不变
		}

		snake_long++;
		crea_food = 1;//重置食物标记为true
		g_score += 10;//吃一次食物加10分

	}
}

//记分
void score(void)
{
	COORD rd;
	rd.X = 55;
	rd.Y = 15;
	//设置光标位置在游戏界面右侧
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("分数：%d", g_score);
	COORD sd;
	sd.X = 55;
	sd.Y = 16;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), sd);
	if (to_east == arr_snake[0][2])
	{
		printf("对对对，向左");
	}
	if (to_west == arr_snake[0][2])
	{
		printf("对对对，向右");
	}
	if (to_north == arr_snake[0][2])
	{
		printf("对对对，向下");
	}
	if (to_south == arr_snake[0][2])
	{
		printf("对对对，向上");
	}

}

int main(void)
{
	//首页音乐
	/*firstpage_music();*/
	//显示首页
	firstpage();
	//空格进入游戏界面
	startgame();
	//停止音乐
	stopmusic();
	/*game_music();*/
	//清空控制台界面以显示背景
	system("cls");
	//随机位置显示蛇，因为只需要显示一开始的一次，因此需要放在游戏外
	snake_pos();
	background();

	//背景,重复调用函数内容以画背景
	while (1)
	{
		gotoxy(0, 0);//清空了控制台并解决了闪烁
		snake_food();//产生食物
		snake_up();//蛇变长
		change_dir();//改变方向
		
		//别把清除蛇残留写在这，因为在画完蛇以后直接清除的画相当于每次都重新画了一条蛇，是无法判断下一个位点是否是自己的
		if (false == snake_die())
		{
			system("cls");
			printf("恭喜你，你死了\n");
			printf("辣鸡，分数才: %d\n", g_score);
			break;
		}
		snake_move();//蛇动	
		background();//背景
		score();//分数
		Sleep(100);

	}
	system("pause");
	return 0;
}
//解决了闪烁问题，但是具体实现方法还是不怎么懂
void gotoxy(unsigned char x, unsigned char y)
{
	COORD cor;
	HANDLE hout;
	cor.X = x;
	cor.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, cor);
}