#include "snakegame.h"
#include <iostream>

using namespace std;

int RandomInRange(int a, int b) {
	//srand(time(NULL));
	return a + rand() % (b - a + 1);
}

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
			x = RandomInRange(board[0].x + 1, board[0].x + WIDTH_BOARD - 2 );
			y = RandomInRange(board[0].y + 1, board[0].y + HEIGHT_BOARD - 2 );
		} while (!IsValidFood(x, y));
		food[i] = { x , y };
	}
}
void ResetData() {
	CHAR_LOCK = 'A', MOVING = 'D', SPEED = 20; FOOD_INDEX = 0, 
	WIDTH_CONSOLE = 180, HEIGH_CONSOLE = 40, SIZE_SNAKE = 6;
	LEVEL = 1;
	snake[0] = { 10, 10 }; snake[1] = { 11, 10 };
	snake[2] = { 12, 10 }; snake[3] = { 13, 10 };
	snake[4] = { 14, 10 }; snake[5] = { 15, 10 };

	GenerateFood();
}

void StartGame() {
	//BoardInit(5, 10);
	WIN_POINT.x = 0;
	WIN_POINT.y = 0;
	//set the coordinates of win point to {0,0} so that it lies outside of the board and the snake cannot touch it until the gate is drawed
	system("cls"); //Clear screen
	BoardInit(3, 9, WIDTH_BOARD, HEIGHT_BOARD);
	ResetData(); // Intialize original data
	DrawRectangle(board[0].x, board[0].y, WIDTH_BOARD, HEIGHT_BOARD); // Draw board game

	DrawRectangle(board[0].x + WIDTH_BOARD + board[0].x, board[0].y, WIDTH_CONSOLE - WIDTH_BOARD - 3 * board[0].x, HEIGH_CONSOLE - board[0].y - (HEIGH_CONSOLE - board[0].y - HEIGHT_BOARD)); // Draw status board

	int title_width, title_height;
	GetWidthAndHeightFile("title.txt", title_width, title_height);
	PrintFile((WIDTH_CONSOLE - title_width) / 2, 1, "title.txt");
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
	printf("Dead, press Y to continue!");
}

void LevelUp() {//need fix
	//process when the snkae eat enough food and open the gate
	//when the head � the snake hit the win point
	FOOD_INDEX = 0;
	LEVEL += 1;
	SPEED += 5;
}
void Eat() {
	snake[SIZE_SNAKE] = food[FOOD_INDEX];
	if (FOOD_INDEX == MAX_SIZE_FOOD - 1)
	{
		//FOOD_INDEX = 0;
		//SIZE_SNAKE = 6;
		//SPEED++;
		//LevelUp();
		if (WIN_POINT.x==0 && WIN_POINT.y==0) DrawGate(2, 3);//Neu da co gate inside area board roi thi khong DrawGate nua
		GenerateFood();
	}
	else
	{
		FOOD_INDEX++;
		SIZE_SNAKE++;
	}
}
//Move functions
bool Suicide(int x,int y)
{
	for (int i = 0; i < SIZE_SNAKE; i++) {
		if (x == snake[i].x && y == snake[i].y)
			return true;
	}
	return false;
}
void MoveRight()
{
	//Snake touch Win point
	if (snake[SIZE_SNAKE - 1].x + 1 == WIN_POINT.x && snake[SIZE_SNAKE - 1].y == WIN_POINT.y)
	{
		LevelUp();
		printf("LevelUP");
		ProcessDead();//thay the bang next round
	}
	//Snake touch Gate
	if (snake[SIZE_SNAKE - 1].x + 1 == WIN_POINT.x && (snake[SIZE_SNAKE - 1].y == WIN_POINT.y + 1 || snake[SIZE_SNAKE - 1].y == WIN_POINT.y - 1))
	{
		ProcessDead();
	}
	///////
	if (snake[SIZE_SNAKE - 1].x + 1 == WIDTH_BOARD+board[0].x - 1 || Suicide(snake[SIZE_SNAKE - 1].x + 1, snake[SIZE_SNAKE - 1].y))//if snake hit the wall
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
	//Snake Touch Gate
	if (snake[SIZE_SNAKE - 1].x - 1 == WIN_POINT.x + 1 && (snake[SIZE_SNAKE - 1].y == WIN_POINT.y + 1 || snake[SIZE_SNAKE - 1].y == WIN_POINT.y - 1 || snake[SIZE_SNAKE - 1].y == WIN_POINT.y))
	{
		ProcessDead();
	}
	///////////
	if (snake[SIZE_SNAKE - 1].x -1 == board[0].x || Suicide(snake[SIZE_SNAKE - 1].x-1, snake[SIZE_SNAKE - 1].y))
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
	//Snake touch Gate
	if (snake[SIZE_SNAKE - 1].y - 1==WIN_POINT.y+1&&(snake[SIZE_SNAKE-1].x==WIN_POINT.x|| snake[SIZE_SNAKE - 1].x== WIN_POINT.x+1)) {
		ProcessDead();
	}
	//////
	if (snake[SIZE_SNAKE - 1].y - 1 == board[0].y || Suicide(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y - 1))
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
	//Snake touch gate
	if (snake[SIZE_SNAKE - 1].y + 1 == WIN_POINT.y - 1 && (snake[SIZE_SNAKE - 1].x == WIN_POINT.x || snake[SIZE_SNAKE - 1].x == WIN_POINT.x + 1)) {
		ProcessDead();
	}
	////
	if (snake[SIZE_SNAKE - 1].y + 1 == HEIGHT_BOARD+board[0].y - 1 || Suicide(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y + 1))
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
			
			DrawSnakeAndFood(MSSV);
			Sleep(1000 / SPEED);
		}
		if (STATE == 2) {
			break;
		}
	}
}