﻿#include "snakegame.h"

using namespace std;


void SetCursor(bool visible, DWORD size) { //set bool visible = 0 - invisible, bool visible = 1 - visible
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (size == 0) size = 20;
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

void SetConsoleColor(int text, int background)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, text+background*16);
}

bool IsValidPoint(int x, int y) {
	if (x < 0 || x >= WIDTH_CONSOLE) return false;
	if (y < 0 || y >= HEIGHT_CONSOLE) return false;
	return true;
}

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

	COORD bufferSize = { 180, 40 }; //120x30: default size
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

void ClearScreen(int x1, int y1, int x2, int y2) {
	GoToXY(x1, y1);
	for (int j = y1; j <= y2; ++j) {
		GoToXY(x1, j);
		for (int i = x1; i <= x2; ++i) {
			cout << " ";
		}
	}
}

void FillRectangle(int x1, int y1, int width, int height) {
	GoToXY(x1, y1);
	int x2 = x1 + width - 1;
	int y2 = y1 + height - 1;
	for (int j = y1; j <= y2; ++j) {
		GoToXY(x1, j);
		for (int i = x1; i <= x2; ++i) {
			cout << "\xDB";
		}
	}
}

void DrawBigFood()
{
	//GenerateBigFood();
	//GoToXY(x, y);
	for (int i = 0; i < BIG_FOOD_SIZE; i++)
	{
		for (int j = 0; j < BIG_FOOD_SIZE; j++)
		{
			//cout << "?";
			//big_food[i][j] = { x + i,y + j };
			GoToXY(big_food[i][j].x, big_food[i][j].y);
			if (IsValidPoint(big_food[i][j].x, big_food[i][j].y)) cout << "?";
		}
		GoToXY(big_food[i][0].x, big_food[i][0].y + 1);
	}
}

void DrawBulletDown() {
	if (bullet_down.y == board[0].y + HEIGHT_BOARD-1) bullet_down.y = board[0].y+1;
	GoToXY(bullet_down.x, bullet_down.y);
	cout << " ";
	++bullet_down.y;
	GoToXY(bullet_down.x, bullet_down.y);
	cout << "\x1F";
	for (int i = 0; i < SIZE_SNAKE; ++i)
		if (bullet_down.x == snake[i].x && bullet_down.y == snake[i].y)
			ProcessDead();
}

void DrawBulletUp() {
	if (bullet_up.y == board[0].y) bullet_up.y = board[0].y + HEIGHT_BOARD - 2;
	GoToXY(bullet_up.x, bullet_up.y);
	cout << " ";
	--bullet_up.y;
	GoToXY(bullet_up.x, bullet_up.y);
	cout << "\x1E";
	for (int i = 0; i < SIZE_SNAKE; ++i)
		if (bullet_up.x == snake[i].x && bullet_up.y == snake[i].y)
			ProcessDead();
}

void DrawRectangle(int x, int y, int width, int height) {
	//nhquan: print characters using code page 437
	//SetConsoleColor(Red, Black);
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
	//SetConsoleColor(White, Black);
}

void DrawGate(){
	//InitGate();
	GoToXY(gate[0].x, gate[0].y);
	cout << '\xc4';

	GoToXY(gate[1].x, gate[1].y);
	cout << '\xb7';

	GoToXY(gate[2].x, gate[2].y);
	cout << '\xb3';

	GoToXY(gate[3].x, gate[3].y);
	cout << '\xbd';

	GoToXY(gate[4].x, gate[4].y);
	cout << '\xc4';
}

void DrawSnakeAndFood(const char* str) {
	if (!(TEXTINCONSOLE))
	{
		GoToXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y); //Go to current food pos
		if (WIN_POINT.x == 0 && WIN_POINT.y == 0) printf("F"); //Draw food only if gate has not been spawned
		int len = strlen(str);
		if (str == " ") SetConsoleColor(DefaultTextColor, DefaultBgColor);
		else SetConsoleColor(Black, SnakeColor);
		for (int i = 0; i < SIZE_SNAKE; i++)
		{
			GoToXY(snake[i].x, snake[i].y);
			cout << str[(i % len)];
			SetConsoleColor(Black, SnakeColor);
		}
		SetConsoleColor(DefaultTextColor, DefaultBgColor);
		GoToXY(0, 0);
		cout << WIN_POINT.x << " " << WIN_POINT.y << " " << FOOD_INDEX << " " << SIZE_SNAKE << " ";
	}
}

void PrintStatusBoard() {
	SetConsoleColor(Black, DefaultStatusColor);
	GoToXY(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 6);
	cout << "Time: " << TIME << endl;
	GoToXY(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 7);
	cout << "Total score: " << SCORE << "  " << endl;
	GoToXY(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 8);
	if (PowerScore == 3) cout << "Skill: Available    ";
	else cout << "Skill: Unavailable";
	GoToXY(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 15);
	if (PowerScore == 0) cout << "Power:[\xFA\xFA\xFA\xFA\xFA\xFA]";
	else if (PowerScore == 1) cout << "Power:[\xFE\xFE\xFA\xFA\xFA\xFA]";
	else if (PowerScore == 2) cout << "Power:[\xFE\xFE\xFE\xFE\xFA\xFA]";
	else if (PowerScore == 3) cout << "Power:[\xFE\xFE\xFE\xFE\xFE\xFE]";
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
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

void GetWidthAndHeightFile(const char* FileName, int &width, int &height) {
	ifstream ifs;
	ifs.open(FileName);
	if (!ifs.good()) return;
	width = 0; height = 1;
	char c;
	while (ifs.get(c))
	{
		if (c == '\n') height++;
	}
	ifs.close();
	ifs.open(FileName);
	int h = height;
	while (h != 0) {
		int width_tmp = 0;
		while (ifs.get(c)) {
			width_tmp++;
			if (c == '\n') break;
		}
		if (width_tmp > width) width = width_tmp;
		h--;
	}

}

void Pause()
{
	PAUSE = 1;
	//PauseGame(handle_t1);
	threadPaused = true;
	cvThread.notify_one();
	unique_lock<mutex> lock(mtx);
	cvMain.wait(lock, [] { return threadPaused.load();  });
	lock.unlock();
	ClearScreen(board[0].x + 1, board[0].y + 1, board[0].x + WIDTH_BOARD - 2, board[0].y + HEIGHT_BOARD - 2);
	PrintTextFile(18, 16, "assets\\ascii\\paused.txt");
	GoToXY(18, 29);
	cout << "Press any key to continue, or press L to save game";
}

void PostPauseDraw() {
	for (int i = 0; i < NUMBER_OF_OBSTACLES; ++i) {
		GoToXY(obstacles[i].x, obstacles[i].y);
		cout << '\xb2';
	}
	if (!(WIN_POINT.x == 0 && WIN_POINT.y == 0)) DrawGate();
	DrawBigFood();
}

//DrawRectangle(board[0].x + WIDTH_BOARD + board[0].x, board[0].y, WIDTH_CONSOLE - WIDTH_BOARD - 3 * board[0].x, HEIGHT_BOARD); // Draw status board
void ColorStatusBoard() {
	for (int i = 126; i < 126+ WIDTH_CONSOLE - WIDTH_BOARD - 3 * board[0].x; i++) {
		for (int j = 9; j < 9 + HEIGHT_BOARD; j++) {
			GoToXY(i, j);
			SetConsoleColor(DefaultStatusTextColor, DefaultStatusColor);
			cout << " ";
		}
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
}
