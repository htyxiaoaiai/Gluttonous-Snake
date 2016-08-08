#pragma once
#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>

#include <Windows.h>
#include <mmsystem.h>//PlaySound的头文件依赖于<Windows.h>
#pragma comment(lib,"winmm.lib")//引入winmm.lib库

#define DEF_SNAKE_LONG 100

//两个字节 站两个字符位
char g_strGameBack[20][48] = {
								"■■■■■■■■■■■■■■■■■■■■■■■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■■■■■■■■■■■■■■■■■■■■■■■\n" };

//存储蛇的数组
int g_arrSnake[DEF_SNAKE_LONG][3] = { 0 };

//记录蛇的长度
int g_nSnakeLen = 3;

//蛇的运动方向
enum
{
	UP = -1,
	DOWN = 1,
	LEFT = -2,
	RIGHT = 2
};
//蛇的方向
int g_nSnakeDir = LEFT;
//是否需要产生食物
bool g_bIsProductFood = true;
//食物的坐标
int g_xFood = 0;
int g_yFood = 0;

//记录蛇的长度
int g_Score = 0;

//主菜单
void Menu();
//显示首页
void FirstPage();
//播放音乐??如何让音乐一直响，直到按下某一个键
void MyPlaySound();
//停止播放音乐
void MyStopSound();
//检测空格
void TestSpace();
//ESC退出游戏
void Exit();
//画背景
void ShowBackgroud();
//把蛇画到背景上
void DrawSnake();
//为蛇产生一个随机的位置
//行x,y,方向
void SetSnakeRandPos();
//销毁蛇
void DropSnake();
//蛇的移动
void SnakeMove();
//蛇随着方向键移动
void ChangeDir();
//判断蛇是否死亡
bool IsSnakedDie();
//为蛇产生食物
void ProductFood();
//蛇吃到食物长大
void SnakeGrowUp();
//显示分数
void Score();
//销毁食物
void DropFood();