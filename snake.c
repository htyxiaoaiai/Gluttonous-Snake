#include "snake.h"

int main(void)
{
	FirstPage();
	//播放音乐
	MyPlaySound();
	//检测空格
	TestSpace();
	//停止播放
	MyStopSound();
	//开始游戏
	system("cls");
	//随机产生一条蛇
	SetSnakeRandPos();
	//画出蛇的背景
	ShowBackgroud();

	//开始游戏
	while (1)
	{
		system("cls");
		//产生食物
		ProductFood();
		//蛇随着方向键移动
		ChangeDir();
		//判断游戏是否结束
		if (false == IsSnakedDie())
		{
			printf("游戏结束了...\n");
			break;
		}

		SnakeMove();
		SnakeGrowUp();
		ShowBackgroud();
		Score();
		Sleep(500);
	}

	system("pause");
	return 0;
}

//显示首页
void FirstPage()
{
	printf("\n\n");
	printf("\t\t\t\t\t<<欢迎进入我的贪吃蛇小游戏>>\n\n\n");
	printf("\t\t\t\t\t    <<按空格开始游戏>>\n");
	printf("\t\t\t\t\t   <<w a s d 控制方向>>\n");
}
//播放音乐??如何让音乐一直响，直到按下某一个键
void MyPlaySound()
{
	PlaySound("background.wav", NULL, SND_FILENAME | SND_ASYNC);
}

//停止播放音乐
void MyStopSound()
{
	PlaySound(NULL, 0, 0);
}

//检测空格
void TestSpace()
{

	char chrInput;
	while (1)
	{
		chrInput = _getch();
		//不需要按回车,直接读取,也不显示在控制台,在vc++2005之后使用_getchar来代替
		if (' ' == chrInput)
		{
			break;
		}
	}
}
////ESC退出游戏
//void Exit()
//{
//	if (GetAsyncKeyState(VK_ESCAPE))
//		;
//}

//画背景
void ShowBackgroud()
{
	int i = 0;
	printf("\n\n");
	for (i = 0; i < 20; i++)
	{
		printf("\t\t\t\t\t");
		printf(g_strGameBack[i]);
	}
}

//把蛇画到背景上
void DrawSnake()
{
	int i = 0;
	for (; i < g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]], "■", 2);//不能将'\0'拷贝过去
	}
}

//为蛇产生一个随机的位置
//行x,y,方向
void SetSnakeRandPos()
{
	int x = -1;
	int y = -1;
	srand((unsigned int)time(NULL));

	//假设蛇的初始长度为3，并且是横向放置
	x = rand() % 19 + 1;
	y = rand() % 18 + 1;

	g_arrSnake[0][0] = y;
	g_arrSnake[0][1] = 2 * x;//注意行和列，x代表列，并且一个方块占两个字节
	g_arrSnake[0][2] = LEFT;

	g_arrSnake[1][0] = y;
	g_arrSnake[1][1] = 2 * x + 2;//注意行和列，x代表列，并且一个方块占两个字节
	g_arrSnake[1][2] = LEFT;

	g_arrSnake[2][0] = y;
	g_arrSnake[2][1] = 2 * x + 4;//注意行和列，x代表列，并且一个方块占两个字节
	g_arrSnake[2][2] = LEFT;

	DrawSnake();
}

//销毁蛇
void DropSnake()
{
	int i = 0;
	for (; i < g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]], "  ", 2);//不能将'\0'拷贝过去
	}

}
//蛇的移动
void SnakeMove()
{
	DropSnake();

	//前边节点代替后边的节点，蛇头单独处理,蛇的身体没必要整个复制，只拷贝有效的位置
	for (int i = DEF_SNAKE_LONG - 1; i > 0; i--)
	{
		if (g_arrSnake[i][0] == 0)
		{
			continue;
		}
		g_arrSnake[i][0] = g_arrSnake[i - 1][0];
		g_arrSnake[i][1] = g_arrSnake[i - 1][1];
		g_arrSnake[i][2] = g_arrSnake[i - 1][2];
	}

	//处理蛇头
	g_arrSnake[0][2] = g_nSnakeDir;
	if (LEFT == g_arrSnake[0][2] || RIGHT == g_arrSnake[0][2])
	{
		g_arrSnake[0][1] += g_arrSnake[0][2];
	}
	else
	{
		g_arrSnake[0][0] += g_arrSnake[0][2];
	}
	//将蛇画到背景上
	DrawSnake();
}

//蛇随着方向键移动
void ChangeDir()
{
	//只能检测大写的元素，返回值为short,高字节：检测值一直按下，非0的负数，低字节：在调用之前按下过键值
	if (GetAsyncKeyState('W'))//异步检测键值，如果不输入则继续运行程序，而_getch()只有输入之后才运行。
	{
		if (DOWN != g_arrSnake[0][2])
			g_nSnakeDir = UP;
	}
	else if (GetAsyncKeyState('S'))
	{
		if (UP != g_arrSnake[0][2])
			g_nSnakeDir = DOWN;
	}
	else if (GetAsyncKeyState('A'))
	{
		if (RIGHT != g_arrSnake[0][2])
			g_nSnakeDir = LEFT;
	}
	else if (GetAsyncKeyState('D'))
	{
		if (LEFT != g_arrSnake[0][2])
			g_nSnakeDir = RIGHT;
	}
	//蛇不能踩着自己的身体移动
}

//判断蛇是否死亡
bool IsSnakedDie()
{
	if (LEFT == g_arrSnake[0][2] || RIGHT == g_arrSnake[0][2])
	{
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0]][g_arrSnake[0][1] + g_arrSnake[0][2]], "■", 2))
		{
			return false;//dead
		}
	}
	else
	{
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0] + g_arrSnake[0][2]][g_arrSnake[0][1]], "■", 2))
			return false;//dead
	}

	return true;

}

//为蛇产生食物
void ProductFood()
{
	if (!g_bIsProductFood)
	{
		return;
	}

	//产生随机数
	srand((unsigned int)time(NULL));
	bool flag = false;
	while (1)
	{
		flag = true;
		g_yFood = rand() % 17 + 1;
		g_xFood = rand() % 20 + 1;

		for (int i = 0; g_arrSnake[i][0] != 0; i++)
		{
			//判断蛇产生的位置是否和蛇的身体重合
			if (g_yFood == g_arrSnake[i][0] && g_xFood == g_arrSnake[i][1])
			{
				flag = false;
				break;
			}
		}

		if (flag)
			break;
	}

	//显示食物
	strncpy(&g_strGameBack[g_yFood][g_xFood * 2], "★", 2);
	g_bIsProductFood = false;
}

//蛇吃到食物长大
void SnakeGrowUp()
{
	//蛇吃到食物长大
	if (g_yFood == g_arrSnake[0][0] && g_xFood * 2 == g_arrSnake[0][1])
	{
		if (LEFT == g_arrSnake[0][2])
		{
			g_arrSnake[g_nSnakeLen][0] = g_arrSnake[g_nSnakeLen - 1][0];
			g_arrSnake[g_nSnakeLen][1] = g_arrSnake[g_nSnakeLen - 1][1] + 2;
			g_arrSnake[g_nSnakeLen][2] = g_arrSnake[g_nSnakeLen - 1][2];
		}
		else if (RIGHT == g_arrSnake[0][2])
		{
			g_arrSnake[g_nSnakeLen][0] = g_arrSnake[g_nSnakeLen - 1][0];
			g_arrSnake[g_nSnakeLen][1] = g_arrSnake[g_nSnakeLen - 1][1] - 2;
			g_arrSnake[g_nSnakeLen][2] = g_arrSnake[g_nSnakeLen - 1][2];
		}
		else if (UP == g_arrSnake[0][2])
		{
			g_arrSnake[g_nSnakeLen][0] = g_arrSnake[g_nSnakeLen - 1][0] + 1;
			g_arrSnake[g_nSnakeLen][1] = g_arrSnake[g_nSnakeLen - 1][1];
			g_arrSnake[g_nSnakeLen][2] = g_arrSnake[g_nSnakeLen - 1][2];
		}
		else if (DOWN == g_arrSnake[0][2])
		{
			g_arrSnake[g_nSnakeLen][0] = g_arrSnake[g_nSnakeLen - 1][0] - 1;
			g_arrSnake[g_nSnakeLen][1] = g_arrSnake[g_nSnakeLen - 1][1];
			g_arrSnake[g_nSnakeLen][2] = g_arrSnake[g_nSnakeLen - 1][2];
		}
		g_nSnakeLen++;
		g_Score++;
		g_bIsProductFood = true;
	}
}
//显示分数
void Score()
{
	//设置显示分数的位置
	COORD rd;
	rd.X = 90;
	rd.Y = 11;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);

	printf("分 数");
	rd.X = 91;
	rd.Y = 12;
	printf("%d", g_Score);
}

//销毁食物
void DropFood()
{
	strncpy(&g_strGameBack[g_yFood][g_xFood * 2], "  ", 2);
	g_bIsProductFood = true;
}
