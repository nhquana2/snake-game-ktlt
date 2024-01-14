#pragma once
#include <windows.h>
#include <thread>
#include <string>

//Global constant
#define MAX_SIZE_SNAKE 40
#define MAX_SIZE_FOOD 6
#define MAX_SPEED 20

//Global variables (definition using extern keyword)
extern POINT snake[40];
extern POINT food[6];
extern int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is one direction my snake cannot move to)
extern int MOVING;//used to determine the direction my snake moves (At a moment, there  are three directions my snake can move)
extern int SPEED;// Standing for level, the higher the level, the quicker the speed
extern int HEIGH_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
extern int FOOD_INDEX; // current food-index
extern int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size may be 10
extern int STATE; // State of snake: dead or alive

//Console and Graphic functions
void FixConsoleWindow();
void GoToXY(int x, int y);
void DrawBoard(int x, int y, int width, int height);
void PrintFile(int x, int y, const char* FileName);

//Logic and game engine functions
bool IsValidFood(int x, int y);
void GenerateFood();
void ResetData();
void StartGame();