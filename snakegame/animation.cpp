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
		Sleep(100);
		int x=RandomInRange(0, 15);
		SetConsoleColor(x, DefaultBgColor);
		DrawRectangle_Ver2(board[0].x, board[0].y, WIDTH_BOARD, HEIGHT_BOARD);
		DrawSnakeAndFood(MSSV);
		SetConsoleColor(DefaultTextColor, DefaultBgColor);
		Sleep(100);

	}
	DrawRectangle_Ver2(board[0].x, board[0].y, WIDTH_BOARD, HEIGHT_BOARD);

}