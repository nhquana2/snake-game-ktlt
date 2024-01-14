#include "snakegame.h"

bool IsValidFood(int x, int y) {
	for (int i = 0; i < SIZE_SNAKE; ++i) {
		if (snake[i].x == x && snake[i].y == y) return false;
	}
	return true;
}
void GenerateFood() {
	int x, y;
	srand(time(NULL));
	for (int i = 0; i < MAX_SIZE_FOOD; ++i) {
		do {
			x = rand() % (WIDTH_CONSOLE - 1) + 1;
			y = rand() % (HEIGH_CONSOLE - 1) + 1;
		} while (!IsValidFood(x, y));
		food[i] = { x , y };
	}
}
void ResetData() {
	CHAR_LOCK = 'A', MOVING = 'D', SPEED = 1; FOOD_INDEX = 0, 
	WIDTH_CONSOLE = 120, HEIGH_CONSOLE = 30, SIZE_SNAKE = 6;

	snake[0] = { 10, 5 }; snake[1] = { 11, 5 };
	snake[2] = { 12, 5 }; snake[3] = { 13, 5 };
	snake[4] = { 14, 5 }; snake[5] = { 15, 5 };

	GenerateFood();
}
void luaquandumdi{

};
void StartGame() {
	system("cls");
	ResetData(); // Intialize original data
	DrawBoard(3, 7, 70, 20); // Draw game
	STATE = 1;//Start running Thread
}

void PauseGame(HANDLE t) {
	system("color 70");
	TerminateThread(t, 0);
	
}

void ExitGame(HANDLE t) {
	SuspendThread(t);
}