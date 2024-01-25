#include "snakegame.h"

using namespace std;

int map0() {
	int pos = 0;
	GoToXY(board[0].x + 10, board[0].y + 4);
	for (int i = 0; i < WIDTH_BOARD-7 - (board[0].x+10); i++)
	{
		cout << '\xb2';
		obstacles[pos] = { board[0].x + 10 + i, board[0].y + 4 };
		pos++;
	}
	for (int i =1; i < HEIGHT_BOARD - 10; i++)
	{
		GoToXY(board[0].x+10, board[0].y+4+i);
		obstacles[pos] = { board[0].x + 10 , board[0].y + 4 +i};
		pos++;
		cout<< '\xb2';
		GoToXY(board[0].x + 11, board[0].y + 4 + i);
		obstacles[pos] = { board[0].x + 11 , board[0].y + 4 + i };
		pos++;
		cout << '\xb2';
		GoToXY(board[0].x + (WIDTH_BOARD-12), board[0].y + 4 + i);
		obstacles[pos] = { board[0].x + (WIDTH_BOARD - 12) , board[0].y + 4 + i };
		pos++;
		cout << '\xb2';
		GoToXY(board[0].x + (WIDTH_BOARD - 11), board[0].y + 4 + i);
		obstacles[pos] = { board[0].x + (WIDTH_BOARD - 11) , board[0].y + 4 + i };
		pos++;
		cout << '\xb2';
	}
	
	return pos;
}