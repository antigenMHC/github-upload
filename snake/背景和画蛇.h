#define	snake_max_long 100
#define	M 3//3代表每个数组里面要装三个元素，y，x，方向
//实际上横坐标只有x=48/2=24
//有23个两字节的符号，所以下标范围是0~22，除开边框就是1~21，减去蛇初始长度就是横坐标随机数的产生范围

//实际纵坐标有y=29，所以下标范围0~28
char black_ground[29][48] = { "███████████████████████\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "█                                          █\n",
					  "███████████████████████\n" };
//枚举方向
enum { to_east = 2, to_west = -2, to_north = -1, to_south = 1 };//东西北南

//蛇数组
//行的位置写多少，蛇就最长是多少
int arr_snake[snake_max_long][3] = { 0 };

//蛇的方向
int snake_dir = to_west;

int crea_food = 1;//初始化为1，代表需要产生食物
//定义食物坐标为全局变量方便在蛇变长函数中使用
int food_x;
int food_y;

//记录蛇长
int snake_long = 2;//3个，下标0~2，所以长度为2

//分数
int g_score = 0;

