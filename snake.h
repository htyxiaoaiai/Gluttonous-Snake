#pragma once
#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>

#include <Windows.h>
#include <mmsystem.h>//PlaySound��ͷ�ļ�������<Windows.h>
#pragma comment(lib,"winmm.lib")//����winmm.lib��

#define DEF_SNAKE_LONG 100

//�����ֽ� վ�����ַ�λ
char g_strGameBack[20][48] = {
								"����������������������������������������������\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"��                                          ��\n",
								"����������������������������������������������\n" };

//�洢�ߵ�����
int g_arrSnake[DEF_SNAKE_LONG][3] = { 0 };

//��¼�ߵĳ���
int g_nSnakeLen = 3;

//�ߵ��˶�����
enum
{
	UP = -1,
	DOWN = 1,
	LEFT = -2,
	RIGHT = 2
};
//�ߵķ���
int g_nSnakeDir = LEFT;
//�Ƿ���Ҫ����ʳ��
bool g_bIsProductFood = true;
//ʳ�������
int g_xFood = 0;
int g_yFood = 0;

//��¼�ߵĳ���
int g_Score = 0;

//���˵�
void Menu();
//��ʾ��ҳ
void FirstPage();
//��������??���������һֱ�죬ֱ������ĳһ����
void MyPlaySound();
//ֹͣ��������
void MyStopSound();
//���ո�
void TestSpace();
//ESC�˳���Ϸ
void Exit();
//������
void ShowBackgroud();
//���߻���������
void DrawSnake();
//Ϊ�߲���һ�������λ��
//��x,y,����
void SetSnakeRandPos();
//������
void DropSnake();
//�ߵ��ƶ�
void SnakeMove();
//�����ŷ�����ƶ�
void ChangeDir();
//�ж����Ƿ�����
bool IsSnakedDie();
//Ϊ�߲���ʳ��
void ProductFood();
//�߳Ե�ʳ�ﳤ��
void SnakeGrowUp();
//��ʾ����
void Score();
//����ʳ��
void DropFood();