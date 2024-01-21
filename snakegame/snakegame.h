#pragma once
#include <windows.h>
#include <thread>
#include <string>
#include <conio.h>
#include <thread>
#include <dos.h>
#include <fstream>
#include <iostream>
#include <ctime>

//Global constant
#define BIG_FOOD_SIZE 3
#define MAX_SIZE_SNAKE 40
#define MAX_SIZE_FOOD 6
#define MAX_BOARD_SIZE 400
#define MAX_SPEED 20
#define HEIGHT_BOARD 30
#define WIDTH_BOARD 120
//Global variables (definition using extern keyword)
extern const char* MSSV;
extern POINT big_food[BIG_FOOD_SIZE][BIG_FOOD_SIZE];
extern POINT snake[MAX_SIZE_SNAKE];
extern POINT food[MAX_SIZE_FOOD];
extern POINT board[MAX_BOARD_SIZE];
extern int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is one direction my snake cannot move to)
extern int MOVING;//used to determine the direction my snake moves (At a moment, there  are three directions my snake can move)
extern int SPEED;// Standing for level, the higher the level, the quicker the speed
extern int HEIGH_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
extern int FOOD_INDEX; // current food-index
extern int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size may be 10
extern int STATE; // State of snake: dead or alive
extern int SCREEN;
extern int SIZE_BOARD;
extern POINT WIN_POINT;
extern int LEVEL;
//Utility
int RandomInRange(int a, int b);

//Console and Graphic functions
void FixConsoleWindow();
void GoToXY(int x, int y);
void ClearScreen(int x1, int y1, int x2, int y2);
void DrawRectangle(int x, int y, int width, int height);
void PrintFile(int x, int y, const char* FileName);
void DrawGate(int GateHeight, int GateWidth);
void DrawSnakeAndFood(const char* str);
void GenerateBigFood();
void DrawMenu();

void GetWidthAndHeightFile(const char* FileName, int& width, int& height);

//Logic and game engine functions
bool IsValidFood(int x, int y);
void GenerateFood();
void ResetData();
void StartGame();
void ExitGame(HANDLE t);
void PauseGame(HANDLE t);
void BoardInit(int x, int y, int width, int height);
void ThreadFunc();
void Eat();