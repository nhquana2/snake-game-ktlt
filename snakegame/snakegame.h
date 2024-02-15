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
#include <mmsystem.h>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <filesystem>

namespace fs = std::filesystem;


//Color
#define Black 0
#define Blue 1
#define Green 2
#define Aqua 3
#define Red 4
#define Purple 5
#define Yellow 6
#define White 7
#define Gray 8
#define LightBlue 9
#define LightGreen 10
#define LightAqua 11
#define LightRed 12
#define LightPurple 13
#define LightYellow 14
#define BrightWhite 15


//Global constant
#define WIDTH_GATE 2
#define HEIGHT_GATE 3
#define BIG_FOOD_SIZE 3
#define MAX_SIZE_SNAKE 40
#define MAX_SIZE_FOOD 3
#define MAX_BOARD_SIZE 400
#define MAX_SPEED 20
#define HEIGHT_BOARD 30
#define WIDTH_BOARD 120

using namespace std;


struct PLAYER {
	string name;
	long long TIME;
	int SCORE;
};

extern mutex mtx;
extern condition_variable cvThread;
extern condition_variable cvMain;
extern atomic<bool> threadPaused;

//Global variables (definition using extern keyword)
extern int NUMBER_OF_OBSTACLES; //number of obstacles is updated every time the map function is called
extern const char* MSSV;
extern POINT obstacles[500];
extern POINT gate[WIDTH_GATE * HEIGHT_GATE-1];//-1 because of the win point
extern POINT big_food[BIG_FOOD_SIZE][BIG_FOOD_SIZE];
extern POINT snake[MAX_SIZE_SNAKE];
extern POINT food[MAX_SIZE_FOOD];
extern POINT board[MAX_BOARD_SIZE];
extern POINT WIN_POINT;
extern POINT bullet_up, bullet_down;
extern POINT spray;
extern POINT TELE_POINT_1, TELE_POINT_2;
extern PLAYER Player[100];
extern vector<string> save_entries;

//Menu button struct
struct BUTTON {
	POINT st; //top left point
	int width, height;
	POINT text_st; //coords for write text
	string text_value;
};

extern BUTTON main_button[6];
extern BUTTON sound_button[2];


extern int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is one direction my snake cannot move to)
extern int MOVING;//used to determine the direction my snake moves (At a moment, there  are three directions my snake can move)
extern int SPEED;// Standing for level, the higher the level, the quicker the speed
extern int HEIGHT_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
extern int FOOD_INDEX; // current food-index
extern int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size may be 10
extern int STATE; // State of snake: dead or alive
extern int PAUSE;
extern int SCREEN;
extern int MENU_OPTION;
extern int SOUND_OPTION;
extern int SIZE_BOARD;
extern int LEVEL;
extern int TIME;
extern int SCORE;
extern int SOUND;
extern int OLD_SIZE_SNAKE;
extern bool CHECK_SNAKE; 
extern bool Flag_PoisonSpray;
extern bool Spraying;
extern int previousAction;
extern int BLINKING_MAP;
extern int DefaultTextColor;
extern int DefaultBgColor;
extern int PowerScore;
extern int TEXTINCONSOLE;//1 if text is in console (game over, ...)

//Utility
int RandomInRange(int a, int b);
void SetConsoleColor(int text, int background);
void SetCursor(bool visible, DWORD size);
bool IsValidPoint(int x, int y);

//Console and Graphic functions
void FixConsoleWindow();
void GoToXY(int x, int y);
void ClearScreen(int x1, int y1, int x2, int y2);
void FillRectangle(int x1, int y1, int width, int height);
void DrawRectangle(int x, int y, int width, int height);
void PrintFile(int x, int y, const char* FileName);
void DrawGate();
void DrawSnakeAndFood(const char* str);
void PrintStatusBoard();
void GenerateBigFood();
void DrawBigFood();
void DrawBulletUp();
void DrawBulletDown();
void DrawTelePoint(int x1, int y1, int x2, int y2);
void Pause();
void PostPauseDraw();

//Menu-related functions
void DrawMenu();
void DrawAboutScreen();
void DrawSettingsScreen();
void DrawLoadGameScreen();
void DrawLeaderBoardScreen();
void GetWidthAndHeightFile(const char* FileName, int& width, int& height);
void ToggleNormalStateButton(BUTTON a);
void ToggleActiveStateButton(BUTTON a);
void InitMainButtons();
void InitSoundButtons();

//Logic and game engine functions
void playSound(const std::string& soundFile);
bool IsValidFood(int x, int y);
void GenerateFood();
void ResetData();
void StartGame();
void ExitGame(HANDLE t);
void PauseGame(HANDLE t);
void BoardInit(int x, int y, int width, int height);
void ThreadFunc();
void Eat();
void ProcessDead();
void InitGate();//return size of gate

//map
bool CheckTouchObstacles(int x, int y);//parameters is the coordinate of the head of the snake
void DeleteMap();
int MapLevel1();
int MapLevel2();
int MapLevel3();
int MapLevel4();
void DrawMap();

void MapLevel5();
//animations
bool SnakeGoThroughGate();
void BlinkingMap();

//Save/Load game processing
void SaveGame(string FileName);
void LoadGame(string FileName);
void LoadSaveEntries();

//graphics
void PrintTextFile(int x, int y, const char* FileName);
void PrintSnakeTextFile(int x, int y, const char* FileName);

//highscore
int LeaderBoard(PLAYER Player[]);