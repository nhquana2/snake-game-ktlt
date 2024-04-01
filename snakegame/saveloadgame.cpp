#include "snakegame.h"

void SaveGame(string FileName) {
	ofstream ofs;
	ofs.open(FileName);

	ofs << SIZE_SNAKE << "\n";
	for (int i = 0; i < SIZE_SNAKE; ++i) {
		ofs << snake[i].x << " " << snake[i].y << "\n";
	}
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

	ofs << PowerScore << "\n";

	ofs << NUMBER_OF_OBSTACLES << "\n";
	for (int i = 0; i < NUMBER_OF_OBSTACLES; ++i) {
		ofs << obstacles[i].x << " " << obstacles[i].y << "\n";
	}

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

	ifs >> NUMBER_OF_OBSTACLES;
	for (int i = 0; i < NUMBER_OF_OBSTACLES; ++i) {
		ifs >> obstacles[i].x >> obstacles[i].y;
	}

	ifs.close();
	//=== End init data
	//GoToXY(0, 0);
	//cout << SIZE_SNAKE << " " << FOOD_INDEX;

	CHECK_SNAKE = false;
	GenerateFood();
	DrawBigFood();

	DrawRectangle(board[0].x, board[0].y, WIDTH_BOARD, HEIGHT_BOARD); 
	DrawRectangle(board[0].x + WIDTH_BOARD + board[0].x, board[0].y, WIDTH_CONSOLE - WIDTH_BOARD - 3 * board[0].x, HEIGHT_BOARD); // Draw status board

	int title_width, title_height;
	GetWidthAndHeightFile("title.txt", title_width, title_height);
	PrintTitle2File(1, 0, "assets\\ascii\\snakegamenew.txt");

	ColorStatusBoard();

	SetConsoleColor(Black, DefaultStatusColor);
	DrawLineStatusBoard(board[0].x + WIDTH_BOARD + board[0].x, 1, WIDTH_CONSOLE - WIDTH_BOARD - 3 * board[0].x, HEIGHT_BOARD + 8);
	SetConsoleColor(DefaultTextColor, DefaultBgColor);

	PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 1, "assets\\ascii\\battery.txt", DefaultStatusColor);

	if (LEVEL == 0) PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y - 7, "assets\\ascii\\level 1.txt", DefaultStatusColor);
	if (LEVEL == 1) PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y - 7, "assets\\ascii\\level 2.txt", DefaultStatusColor);
	if (LEVEL == 2) PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y - 7, "assets\\ascii\\level 3.txt", DefaultStatusColor);
	if (LEVEL == 3) PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y - 7, "assets\\ascii\\level 4.txt", DefaultStatusColor);
	if (LEVEL == 4) PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y - 7, "assets\\ascii\\level 5.txt", DefaultStatusColor);

	if (FOOD_INDEX == 1) PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 4, board[0].y + 2, "assets\\ascii\\food1.txt", DefaultStatusColor);
	if (FOOD_INDEX == 2) {
		PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 4, board[0].y + 2, "assets\\ascii\\food1.txt", DefaultStatusColor);
		PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 17, board[0].y + 2, "assets\\ascii\\food2.txt", DefaultStatusColor);
	}

	if (!(WIN_POINT.x == 0 && WIN_POINT.y == 0)) {
		DrawGate();
		PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 32, board[0].y + 2, "assets\\ascii\\food3.txt", DefaultStatusColor);
	}

	if (LEVEL == 1) {
		DrawTelePoint(board[0].x, board[0].y + 10, board[0].x + WIDTH_BOARD - 1, board[0].y + 5);
	}
	if (LEVEL == 2) {
		DrawTelePoint(board[0].x, board[0].y + 10, board[0].x + WIDTH_BOARD - 1, board[0].y + 8);

	}
	if (LEVEL == 3) {

	}
	if (LEVEL == 4) {
		bullet_down.x = board[0].x + 60;
		bullet_down.y = board[0].y + 1;
		bullet_up.x = board[0].x + 61;
		bullet_up.y = board[0].y + HEIGHT_BOARD - 2;
	}

	TEXTINCONSOLE = 0;
	emotionstime = 5;

	DrawMap();
	STATE = 1; //Start running Thread

}

void LoadSaveEntries() {
	save_entries.resize(0);
	string directory_path = "data";
	try {
		int pos = 0;
		// Iterate over the files in the directory
		for (const auto& entry : fs::directory_iterator(directory_path)) {
			if (entry.is_regular_file()) {
				SAVE_ENTRY se;
				se.text_value = entry.path().filename().string();
				se.st = { 10, 13 + pos };
				save_entries.push_back(se);
				++pos;
			}
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Error accessing directory: " << e.what() << std::endl;
	}
}