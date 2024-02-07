#include "snakegame.h"

void SaveGame(string FileName) {
	ofstream ofs;
	ofs.open(FileName);

	ofs << SIZE_SNAKE << "\n";
	for (int i = 0; i < SIZE_SNAKE; ++i) {
		ofs << snake[i].x << " " << snake[i].y << "\n";
	}
	ofs << "\n";
	ofs << CHAR_LOCK << " " << MOVING << " " << SPEED << " " << FOOD_INDEX << "\n";
	ofs << TIME << " " << LEVEL << " " << SCORE << "\n";
	ofs << WIN_POINT.x << " " << WIN_POINT.y << "\n";

	for (int i = 0; i < BIG_FOOD_SIZE; ++i) {
		for (int j = 0; j < BIG_FOOD_SIZE; ++j) {
			ofs << big_food[i][j].x << " " << big_food[i][j].y << "\n";
		}
	}

	for (int i = 0; i <= 4; ++i) {
		ofs << gate[i].x << " " << gate[i].y << "\n";
	}

	ofs << PowerScore;

	ofs.close();
}

void LoadGame(string FileName) {
	playSound("assets\\sounds\\startGame");
	system("cls"); //Clear screen
	BoardInit(3, 9, WIDTH_BOARD, HEIGHT_BOARD);

	//=== Begin init data
	ifstream ifs;
	ifs.open(FileName);

	ifs >> SIZE_SNAKE;
	for (int i = 0; i < SIZE_SNAKE; ++i) {
		ifs >> snake[i].x >> snake[i].y;
	}
	ifs >> CHAR_LOCK >> MOVING >> SPEED >> FOOD_INDEX;
	ifs >> TIME >> LEVEL >> SCORE;
	ifs >> WIN_POINT.x >> WIN_POINT.y;

	for (int i = 0; i < BIG_FOOD_SIZE; ++i) {
		for (int j = 0; j < BIG_FOOD_SIZE; ++j) {
			ifs >> big_food[i][j].x >> big_food[i][j].y;
		}
	}

	for (int i = 0; i <= 4; ++i) {
		ifs >> gate[i].x >> gate[i].y;
	}

	ifs >> PowerScore;

	ifs.close();
	//=== End init data

	CHECK_SNAKE = false;
	DeleteMap();
	GenerateFood();
	DrawBigFood();

	DrawRectangle(board[0].x, board[0].y, WIDTH_BOARD, HEIGHT_BOARD); 
	DrawRectangle(board[0].x + WIDTH_BOARD + board[0].x, board[0].y, WIDTH_CONSOLE - WIDTH_BOARD - 3 * board[0].x, HEIGHT_BOARD); // Draw status board

	int title_width, title_height;
	GetWidthAndHeightFile("title.txt", title_width, title_height);
	PrintFile((WIDTH_CONSOLE - title_width) / 2, 1, "title.txt");

	PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 10, "assets\\ascii\\battery.txt");
	if (LEVEL == 0) PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y + 2, "assets\\ascii\\level 1.txt");

	if (FOOD_INDEX == 1) PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 4, board[0].y + 11, "assets\\ascii\\food1.txt");
	if (FOOD_INDEX == 2) {
		PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 4, board[0].y + 11, "assets\\ascii\\food1.txt");
		PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 17, board[0].y + 11, "assets\\ascii\\food2.txt");
	}

	if (!(WIN_POINT.x == 0 && WIN_POINT.y == 0)) {
		DrawGate();
		PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 32, board[0].y + 11, "assets\\ascii\\food3.txt");
	}

	if (LEVEL == 1) {
		DrawTelePoint(board[0].x, board[0].y + 10, board[0].x + WIDTH_BOARD - 1, board[0].y + 5);
		NUMBER_OF_OBSTACLES = MapLevel1();
	}
	if (LEVEL == 2) {
		DrawTelePoint(board[0].x, board[0].y + 10, board[0].x + WIDTH_BOARD - 1, board[0].y + 8);
		DeleteMap();
		NUMBER_OF_OBSTACLES = MapLevel2();
	}
	if (LEVEL == 3) {
		DeleteMap();
		NUMBER_OF_OBSTACLES = MapLevel3();
	}
	if (LEVEL == 4) {
		DeleteMap();
		NUMBER_OF_OBSTACLES = MapLevel4();
	}

	STATE = 1; //Start running Thread

}