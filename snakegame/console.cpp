#include "snakegame.h"

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
void DrawBigFood()
{
	GenerateBigFood();
	//GoToXY(x, y);
	for (int i = 0; i < BIG_FOOD_SIZE; i++)
	{
		for (int j = 0; j < BIG_FOOD_SIZE; j++)
		{
			//cout << "?";
			//big_food[i][j] = { x + i,y + j };
			GoToXY(big_food[i][j].x, big_food[i][j].y);
			cout << "?";
		}
		GoToXY(big_food[i][0].x, big_food[i][0].y + 1);
	}
}


void DrawRectangle(int x, int y, int width, int height) {
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

void DrawGate()
{
	int size = InitGate();
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
	GoToXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y); //Go to current food pos
	printf("F"); //Draw food
	int len = strlen(str);
	for (int i = 0; i < SIZE_SNAKE; i++)
	{
		GoToXY(snake[i].x, snake[i].y);
		cout << str[(i % len)];
	}
	GoToXY(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 1);
	cout << "Time: " << TIME << endl;
	GoToXY(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 2);
	cout << "Total score: " << SCORE << endl;
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


