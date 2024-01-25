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
	for (int i = 0; i < NUMBER_OF_OBSTACLES; i++)
	{
		if ((obstacles[i].x == x && obstacles[i].y == y)|| (obstacles[i].x + 1 == x && obstacles[i].y == y))//check if the food is near the obstacles
			return false;
	}
	return true;
}
void GenerateFood() {
	int x, y;
	srand(time(NULL));
	for (int i = 0; i < MAX_SIZE_FOOD; ++i) {
		do {
			x = RandomInRange(board[0].x + 1, board[0].x + WIDTH_BOARD - 2 );
			y = RandomInRange(board[0].y + 1, board[0].y + HEIGHT_BOARD - 2);
		} while (!IsValidFood(x, y));
		food[i] = { x , y };
	}
}
void DeleteBigFood(int x, int y)
{
	GoToXY(x, y);

	for (int i = 0; i < BIG_FOOD_SIZE; i++)
	{
		for (int j = 0; j < BIG_FOOD_SIZE; j++)
		{
			cout << " ";
			big_food[i][j] = { 0, HEIGH_CONSOLE + 2 };

		}
		GoToXY(x, y + i + 1);
		//break;
	}

}
bool CheckBigFood(int x,int y)//check if the snake touches the big food
{
	for (int i = 0; i < BIG_FOOD_SIZE; i++)
	{
		for (int j = 0; j < BIG_FOOD_SIZE; j++)
		{
			//cout << " ";
			if (x == big_food[i][j].x && y == big_food[i][j].y)
			{
				//SIZE_SNAKE+=3;//
				//FOOD_INDEX++;
				return true;
			}
		}
		//GoToXY(x, y + i + 1);
		//break;
	}
	return false;
}
bool CheckValidBigFood()
{
	for (int i = 0; i < BIG_FOOD_SIZE; i++)
	{
		for (int j = 0; j < BIG_FOOD_SIZE; j++)
		{
			if (!IsValidFood(big_food[i][j].x, big_food[i][j].y))
			{
				return false;
			}
		}
	}
	return true;
}
void GenerateBigFood() {
	int x, y;//need to be write with thread because the while loop paused the thread
	//srand(time(NULL));
	//for (int i = 0; i < MAX_SIZE_FOOD; ++i) {
	do {
		do {
			x = RandomInRange(board[0].x + 1, board[0].x + WIDTH_BOARD - 2 - BIG_FOOD_SIZE);
			y = RandomInRange(board[0].y + 1, board[0].y + HEIGHT_BOARD - 2 - BIG_FOOD_SIZE);
		} while (!IsValidFood(x, y));
		//}
		for (int i = 0; i < BIG_FOOD_SIZE; i++)
		{
			for (int j = 0; j < BIG_FOOD_SIZE; j++)
			{
				big_food[i][j] = { x + i, y + j };
			}
		}
	}
		while (!CheckValidBigFood());
}
bool CheckValidGate(int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!IsValidFood(gate[i].x, gate[i].y))
		{
			return false;
		}
	}
	return true;
}

//Create gate[] array, use to store coordinates 
int InitGate()//return size of gate
{
	int x, y;
	//pos: number of pixels in gate[]
	int pos = 0;
	while (1) {
		pos = 0;
		x = RandomInRange(board[0].x + 2, board[0].x + WIDTH_BOARD - 1 - WIDTH_GATE - 1); //random coordinates such that the gate is inside the playzone
		y = RandomInRange(board[0].y + 2, board[0].y + HEIGHT_BOARD - 1 - HEIGHT_GATE - 1);

		gate[pos] = { x, y };
		pos++;

		gate[pos] = { x + 1, y };
		pos++;

		gate[pos] = { x + 1, y + 1 };
		pos++;

		gate[pos] = { x + 1, y + 2 };
		pos++;

		gate[pos] = { x, y + 2 };
		pos++;

		//check if gate[] generated is valid, if it is valid break while loop (random until it is valid)
		if (CheckValidGate(pos)) {
			break;
		}
	}
	WIN_POINT = { x,y + 1 };
	return pos;
}
void DeleteGate()
{
	for (int i = 0; i < WIDTH_GATE * HEIGHT_GATE - 1; i++)
	{
		GoToXY(gate[i].x, gate[i].y);
		cout << " ";
		gate[i] = { 0,HEIGH_CONSOLE + 5 };
	}
	WIN_POINT = { 0, 0 }; //Reset win point
}
void RespawnSnake()
{
	for (int i = 0; i < SIZE_SNAKE; i++)
	{
		snake[i] = { 10 + i, 10 };
	}
}
void ResetData() {
	CHAR_LOCK = 'A', MOVING = 'D', SPEED = 20; FOOD_INDEX = 0, 
	WIDTH_CONSOLE = 180, HEIGH_CONSOLE = 40, SIZE_SNAKE = 6;
	TIME = 0;
	LEVEL = 0;
	SCORE = 0;
	NUMBER_OF_OBSTACLES = 0;
	DeleteMap();
	RespawnSnake();
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

	//DrawRectangle(board[0].x + WIDTH_BOARD + board[0].x, board[0].y, WIDTH_CONSOLE - WIDTH_BOARD - 3 * board[0].x, HEIGH_CONSOLE - board[0].y - (HEIGH_CONSOLE - board[0].y - HEIGHT_BOARD)); // Draw status board
	DrawRectangle(board[0].x + WIDTH_BOARD + board[0].x, board[0].y, WIDTH_CONSOLE - WIDTH_BOARD - 3 * board[0].x, HEIGHT_BOARD); // Draw status board

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

void LevelUp() {
	//process when the snake eat enough food and open the gate
	//when the head of the snake hit the win point
	DeleteGate();
	FOOD_INDEX = 0;
	LEVEL += 1;
	SPEED += 5;
	if (LEVEL == 1)
	{
		NUMBER_OF_OBSTACLES = MapLevel3();
	}
	if (LEVEL == 2)
	{
		DeleteMap();//delete old map before switch to next map
		NUMBER_OF_OBSTACLES = MapLevel2();
	}
	if (LEVEL == 3)
	{
		DeleteMap();
		NUMBER_OF_OBSTACLES = MapLevel3();
	}
	RespawnSnake();
	//GenerateBigFood();
}
void Eat() {
	snake[SIZE_SNAKE] = food[FOOD_INDEX];
	SCORE += 10;
	if (FOOD_INDEX == MAX_SIZE_FOOD - 1)//if the player met the requirement of food
	{
		//FOOD_INDEX = 0;
		//SIZE_SNAKE = 6;
		//SPEED++;
		//If gate is not inside board, max number of food spawned -> DrawGate
		if (WIN_POINT.x==0 && WIN_POINT.y==0) DrawGate(); 
		//GenerateFood();
	}
	else
	{
		FOOD_INDEX++;
		SIZE_SNAKE++;
	}
}
bool Suicide(int x,int y)//return true if the snake touch its body
{
	for (int i = 0; i < SIZE_SNAKE; i++) {
		if (x == snake[i].x && y == snake[i].y)
			return true;
	}
	return false;
}

//Move functions

void MoveRight()
{
	//Snake touch Win point
	if (snake[SIZE_SNAKE - 1].x + 1 == WIN_POINT.x && snake[SIZE_SNAKE - 1].y == WIN_POINT.y)
	{
		//check if the player ate the big food (big food only be drawn if level up function is called)
		LevelUp();
		DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
		

		GenerateBigFood();
		DrawBigFood();
		GenerateFood(); //generate new food for next level
	}
	//Snake touch Gate
	if (snake[SIZE_SNAKE - 1].x + 1 == WIN_POINT.x && (snake[SIZE_SNAKE - 1].y == WIN_POINT.y + 1 || snake[SIZE_SNAKE - 1].y == WIN_POINT.y - 1))
	{
		ProcessDead();
	}

	//check if the snake touch the big food
	if (CheckBigFood(snake[SIZE_SNAKE - 1].x + 1, snake[SIZE_SNAKE - 1].y))
	{
		//delete big food, parameters is its coordinates
		DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
		SCORE += 100;
	}

	// If snake hit wall or snake suicide
	if (snake[SIZE_SNAKE - 1].x + 1 == WIDTH_BOARD+board[0].x - 1 || Suicide(snake[SIZE_SNAKE - 1].x + 1, snake[SIZE_SNAKE - 1].y)|| CheckTouchObstacles(snake[SIZE_SNAKE - 1].x + 1, snake[SIZE_SNAKE - 1].y))
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

	if (CheckBigFood(snake[SIZE_SNAKE - 1].x - 1, snake[SIZE_SNAKE - 1].y))
	{
		DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
		SCORE += 100;
	}

	if (snake[SIZE_SNAKE - 1].x -1 == board[0].x || Suicide(snake[SIZE_SNAKE - 1].x-1, snake[SIZE_SNAKE - 1].y)|| CheckTouchObstacles(snake[SIZE_SNAKE - 1].x - 1, snake[SIZE_SNAKE - 1].y))
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
	
	if (CheckBigFood(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y-1))
	{
		DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
		SCORE += 100;
	}
	if (snake[SIZE_SNAKE - 1].y - 1 == board[0].y || Suicide(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y - 1)|| CheckTouchObstacles(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y-1))
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
	
	if (CheckBigFood(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y+1))
	{
		DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
		SCORE += 100;
	}
	if (snake[SIZE_SNAKE - 1].y + 1 == HEIGHT_BOARD+board[0].y - 1 || Suicide(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y + 1)|| CheckTouchObstacles(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y + 1))
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
			TIME += 1000 / SPEED;
		}
		if (STATE == 2) {
			break;
		}
	}
}