#include "snake.h"

int main(void)
{
	FirstPage();
	//��������
	MyPlaySound();
	//���ո�
	TestSpace();
	//ֹͣ����
	MyStopSound();
	//��ʼ��Ϸ
	system("cls");
	//�������һ����
	SetSnakeRandPos();
	//�����ߵı���
	ShowBackgroud();

	//��ʼ��Ϸ
	while (1)
	{
		system("cls");
		//����ʳ��
		ProductFood();
		//�����ŷ�����ƶ�
		ChangeDir();
		//�ж���Ϸ�Ƿ����
		if (false == IsSnakedDie())
		{
			printf("��Ϸ������...\n");
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

//��ʾ��ҳ
void FirstPage()
{
	printf("\n\n");
	printf("\t\t\t\t\t<<��ӭ�����ҵ�̰����С��Ϸ>>\n\n\n");
	printf("\t\t\t\t\t    <<���ո�ʼ��Ϸ>>\n");
	printf("\t\t\t\t\t   <<w a s d ���Ʒ���>>\n");
}
//��������??���������һֱ�죬ֱ������ĳһ����
void MyPlaySound()
{
	PlaySound("background.wav", NULL, SND_FILENAME | SND_ASYNC);
}

//ֹͣ��������
void MyStopSound()
{
	PlaySound(NULL, 0, 0);
}

//���ո�
void TestSpace()
{

	char chrInput;
	while (1)
	{
		chrInput = _getch();
		//����Ҫ���س�,ֱ�Ӷ�ȡ,Ҳ����ʾ�ڿ���̨,��vc++2005֮��ʹ��_getchar������
		if (' ' == chrInput)
		{
			break;
		}
	}
}
////ESC�˳���Ϸ
//void Exit()
//{
//	if (GetAsyncKeyState(VK_ESCAPE))
//		;
//}

//������
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

//���߻���������
void DrawSnake()
{
	int i = 0;
	for (; i < g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]], "��", 2);//���ܽ�'\0'������ȥ
	}
}

//Ϊ�߲���һ�������λ��
//��x,y,����
void SetSnakeRandPos()
{
	int x = -1;
	int y = -1;
	srand((unsigned int)time(NULL));

	//�����ߵĳ�ʼ����Ϊ3�������Ǻ������
	x = rand() % 19 + 1;
	y = rand() % 18 + 1;

	g_arrSnake[0][0] = y;
	g_arrSnake[0][1] = 2 * x;//ע���к��У�x�����У�����һ������ռ�����ֽ�
	g_arrSnake[0][2] = LEFT;

	g_arrSnake[1][0] = y;
	g_arrSnake[1][1] = 2 * x + 2;//ע���к��У�x�����У�����һ������ռ�����ֽ�
	g_arrSnake[1][2] = LEFT;

	g_arrSnake[2][0] = y;
	g_arrSnake[2][1] = 2 * x + 4;//ע���к��У�x�����У�����һ������ռ�����ֽ�
	g_arrSnake[2][2] = LEFT;

	DrawSnake();
}

//������
void DropSnake()
{
	int i = 0;
	for (; i < g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]], "  ", 2);//���ܽ�'\0'������ȥ
	}

}
//�ߵ��ƶ�
void SnakeMove()
{
	DropSnake();

	//ǰ�߽ڵ�����ߵĽڵ㣬��ͷ��������,�ߵ�����û��Ҫ�������ƣ�ֻ������Ч��λ��
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

	//������ͷ
	g_arrSnake[0][2] = g_nSnakeDir;
	if (LEFT == g_arrSnake[0][2] || RIGHT == g_arrSnake[0][2])
	{
		g_arrSnake[0][1] += g_arrSnake[0][2];
	}
	else
	{
		g_arrSnake[0][0] += g_arrSnake[0][2];
	}
	//���߻���������
	DrawSnake();
}

//�����ŷ�����ƶ�
void ChangeDir()
{
	//ֻ�ܼ���д��Ԫ�أ�����ֵΪshort,���ֽڣ����ֵһֱ���£���0�ĸ��������ֽڣ��ڵ���֮ǰ���¹���ֵ
	if (GetAsyncKeyState('W'))//�첽����ֵ�������������������г��򣬶�_getch()ֻ������֮������С�
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
	//�߲��ܲ����Լ��������ƶ�
}

//�ж����Ƿ�����
bool IsSnakedDie()
{
	if (LEFT == g_arrSnake[0][2] || RIGHT == g_arrSnake[0][2])
	{
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0]][g_arrSnake[0][1] + g_arrSnake[0][2]], "��", 2))
		{
			return false;//dead
		}
	}
	else
	{
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0] + g_arrSnake[0][2]][g_arrSnake[0][1]], "��", 2))
			return false;//dead
	}

	return true;

}

//Ϊ�߲���ʳ��
void ProductFood()
{
	if (!g_bIsProductFood)
	{
		return;
	}

	//���������
	srand((unsigned int)time(NULL));
	bool flag = false;
	while (1)
	{
		flag = true;
		g_yFood = rand() % 17 + 1;
		g_xFood = rand() % 20 + 1;

		for (int i = 0; g_arrSnake[i][0] != 0; i++)
		{
			//�ж��߲�����λ���Ƿ���ߵ������غ�
			if (g_yFood == g_arrSnake[i][0] && g_xFood == g_arrSnake[i][1])
			{
				flag = false;
				break;
			}
		}

		if (flag)
			break;
	}

	//��ʾʳ��
	strncpy(&g_strGameBack[g_yFood][g_xFood * 2], "��", 2);
	g_bIsProductFood = false;
}

//�߳Ե�ʳ�ﳤ��
void SnakeGrowUp()
{
	//�߳Ե�ʳ�ﳤ��
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
//��ʾ����
void Score()
{
	//������ʾ������λ��
	COORD rd;
	rd.X = 90;
	rd.Y = 11;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);

	printf("�� ��");
	rd.X = 91;
	rd.Y = 12;
	printf("%d", g_Score);
}

//����ʳ��
void DropFood()
{
	strncpy(&g_strGameBack[g_yFood][g_xFood * 2], "  ", 2);
	g_bIsProductFood = true;
}
