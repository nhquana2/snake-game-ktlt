#include "snakegame.h"
using namespace std;

bool SnackGoThroughGate() {
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