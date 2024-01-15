#include "snakegame.h"
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <dos.h>
#include <thread>

using namespace std;

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);

	//Set console title for snake game which appears on top
	SetConsoleTitle(L"Snake Game - 23CLC01");

	//Console code page: 437 OEM - US
	SetConsoleOutputCP(437);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//cout << GetLargestConsoleWindowSize(hConsole).X; //max based on system

	COORD bufferSize = { 120, 30 }; //120x30: default size
	SMALL_RECT windowSize = { 0, 0, bufferSize.X - 1, bufferSize.Y - 1 };

	//nhquan: make the console screen buffer size and console window size equal to hide scrollbar
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

//Go to specific location in console
void GoToXY(int x, int y) {
	COORD coord;
	coord.X = x, coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawBoard(int x, int y, int width, int height) {
	//nhquan: print characters using code page 437
	GoToXY(x, y); cout << '\xc9';
	for (int i = 1; i < width-1; i++) cout << '\xcd';
	cout << '\xbb';
	GoToXY(x, y + height - 1);
	for (int i = 0; i < width; i++) cout << '\xcd';
	for (int i = y + 1; i < y + height; ++i) {
		GoToXY(x, i); 
		if (i != y + height - 1) cout << '\xba'; else cout << '\xc8';
		GoToXY(x + width - 1, i); 
		if (i != y + height - 1) cout << '\xba'; else cout << '\xbc';
	}
}
void DrawGate(int GateHeight,int GateWidth)
{
	int x, y;
	srand(time(NULL));
	do
	{
		x = rand() % (board[0].x) + HEIGHT_BOARD;//random coordinates such that the gate is inside the playzone
		y = rand() % (board[0].y) + WIDTH_BOARD;
	} while (x <= board[0].x+ GateHeight || y <= board[0].y+GateWidth);// continue the loop if they out of the playzone
	GoToXY(x, y);
	for (int i = 0; i < GateHeight; i++)
	{
		for (int j = 0; j < GateWidth; j++)
		{
			if (i == GateHeight - 1 && j== GateWidth/2)//chừa 1 lỗ trong 1 khối vd 3x3 để làm cái cổng
				continue;
			cout << "*";
		}
		cout << endl;
	}
}
void PrintFile(int x, int y, const char* FileName) {
	ifstream ifs;
	int st_x = x, st_y = y;
	ifs.open(FileName);
	if (!ifs.good()) return;
	char c;
	GoToXY(x, y);
	while (ifs.get(c)) {
		cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
}

int getWeightAsciiArt(const char* FileName) {
	//cuong: this func return max_weight of ascii art
	ifstream ifs;
	ifs.open(FileName);
	if (!ifs.good()) return 0;
	char c;
	int weight = 0;
	int h = getHeightAsciiArt(FileName);
	while (h != 0) {
		int weight_tmp = 0;
		while (ifs.get(c)) {
			weight_tmp++;
			if (c == '\n') break;
		}
		if (weight_tmp > weight) weight = weight_tmp;
		h--;
	}
	return --weight;
}

int getHeightAsciiArt(const char* FileName) {
	//cuong: this func return height of ascii art
	ifstream ifs;
	ifs.open(FileName);
	if (!ifs.good()) return 0;
	char c;
	int height = 0; 
	while (ifs.get(c)) {
		if (c == '\n') height++;
	}
	return ++height;
}

