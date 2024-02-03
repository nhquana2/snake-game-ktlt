#include "snakegame.h"
using namespace std;

bool SnakeGoThroughGate() {
		if (snake[0].x == WIN_POINT.x && snake[0].y == WIN_POINT.y)
		{
			--SIZE_SNAKE;

			return true;
		}
		else
		{
			//GoToXY(snake[SIZE_SNAKE -1].x, snake[SIZE_SNAKE - 1].y);
			//cout << " ";
			//snake[snake_pos - 1] = { 0, HEIGH_CONSOLE + 2 };
			--SIZE_SNAKE;
			return false;
		}
		
}
void BlinkingMap(){//blinking when the snake died
	BLINKING_MAP = 1;
	for(int i = 0; i < 5; i++) {
		for (int i = 0; i < SIZE_SNAKE; i++){
			GoToXY(snake[i].x, snake[i].y);
			cout << " ";
		}
		for (int i = 0; i < SIZE_BOARD; i++){
			GoToXY(board[i].x, board[i].y);
			cout << " ";
		}
		//for (int i = 0; i < NUMBER_OF_OBSTACLES; i++)
		//{
		//	GoToXY(obstacles[i].x, obstacles[i].y);
		//	cout << " ";
		//}
		Sleep(100);
		DrawRectangle(board[0].x, board[0].y, WIDTH_BOARD, HEIGHT_BOARD);
		DrawSnakeAndFood(MSSV);
		/*if (LEVEL == 1)
		{
			NUMBER_OF_OBSTACLES = MapLevel1();
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
		}*/
		Sleep(100);
	}
	BLINKING_MAP = 0;
}