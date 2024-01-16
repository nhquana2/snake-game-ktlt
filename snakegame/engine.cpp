#include "snakegame.h"
#include <iostream>

using namespace std;

void BoardInit(int x, int y, int width, int height) {
	int pos = 0;
	board[pos] = { x, y };
	for (int i = 0; i < width; ++i) {
		board[pos] = { x + i, y };
		++pos;
	}
	for (int i = 0; i < width; ++i) {
		board[pos] = { x + i, y + height - 1 };
		++pos;
	}
	for (int i = y + 1; i < y + height - 1; ++i) {
		board[pos] = { x , i }; ++pos;
		board[pos] = { x + width - 1, i };
		++pos;
	}
	SIZE_BOARD = pos;
}
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

void StartGame() {
	//BoardInit(5, 10);
	system("cls"); //Clear screen
	ResetData(); // Intialize original data
	BoardInit(3, 7, WIDTH_BOARD, HEIGHT_BOARD);
	DrawBoard(board[0].x, board[0].y, WIDTH_BOARD, HEIGHT_BOARD); // Draw board game
	STATE = 1; //Start running Thread
}

void ExitGame(HANDLE t) {
	system("cls");
	TerminateThread(t, 0);//no ok
}

void PauseGame(HANDLE t) {
	SuspendThread(t);
}

void ProcessDead() {
	STATE = 0;
	GoToXY(0, HEIGH_CONSOLE + 2);
	printf("Dead, press anykey to continue!");
}

void Eat() {
	snake[SIZE_SNAKE] = food[FOOD_INDEX];
	if (FOOD_INDEX == MAX_SIZE_FOOD - 1)
	{
		FOOD_INDEX = 0;
		SIZE_SNAKE = 6;
		SPEED++;
		GenerateFood();
	}
	else
	{
		FOOD_INDEX++;
		SIZE_SNAKE++;
	}
}
//Move functions

void MoveRight()
{
	if (snake[SIZE_SNAKE - 1].x + 1 == WIDTH_CONSOLE)//if snake hit the wall
	{
		ProcessDead();
	}
	else {
		if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
			Eat();
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
			
		}
		snake[SIZE_SNAKE - 1].x++;
	}
}

void MoveLeft()
{
	if (snake[SIZE_SNAKE - 1].x -1 == WIDTH_CONSOLE)
	{
		ProcessDead();
	}
	else {
		if (snake[SIZE_SNAKE - 1].x -1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
			Eat();
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;

		}
		snake[SIZE_SNAKE - 1].x--;
	}
}

void MoveUp()
{
	if (snake[SIZE_SNAKE - 1].y - 1 == HEIGH_CONSOLE)
	{
		ProcessDead();
	}
	else {
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y -1== food[FOOD_INDEX].y) {
			Eat();
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;

		}
		snake[SIZE_SNAKE - 1].y--;
	}
}

void MoveDown()
{
	if (snake[SIZE_SNAKE - 1].y + 1 == HEIGH_CONSOLE)
	{
		ProcessDead();
	}
	else {
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y) {
			Eat();
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i+1].x;
			snake[i].y = snake[i + 1].y;

		}
		snake[SIZE_SNAKE - 1].y++;
	}
}
void ThreadFunc() {
	while (1) {
		if (STATE == 1) {
			DrawSnakeAndFood(" ");
			switch (MOVING) {
				case 'A':
				MoveLeft();
				break;
				case 'D':
				MoveRight();
				break;
				case 'W':
				MoveUp();
				break;
				case 'S':
				MoveDown();
				break;
				}
			DrawSnakeAndFood("*");
			Sleep(1000 / SPEED);
		}
	}
}