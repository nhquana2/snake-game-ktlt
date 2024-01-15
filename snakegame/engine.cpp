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

void StartGame() {
	system("cls");
	ResetData(); // Intialize original data
	DrawBoard(3, 7, 70, 20); // Draw game
	STATE = 1;//Start running Thread
}

void ExitGame(HANDLE t) {
	system("cls");
	TerminateThread(t, 0);
}

void PauseGame(HANDLE t) {
	SuspendThread(t);
}

void ProcessDead() {
	STATE = 0;
	GoToXY(0, HEIGH_CONSOLE + 2);
	printf("Dead, press anykey to continue!");
}

void DrawSnakeAndFood(char* str) {
	GoToXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);//Cho con tro nhap nhay
	printf(".");//Draw food
	for (int i = 0; i < SIZE_SNAKE; i++)
	{
		GoToXY(snake[i].x, snake[i].y);
		printf(str);
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