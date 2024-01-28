#include "snakegame.h"

using namespace std;
bool CheckTouchObstacles(int x, int y)//parameters is the coordinate of the head of the snake
{
	for (int i = 0; i < NUMBER_OF_OBSTACLES; i++)
	{
		if (x == obstacles[i].x && y == obstacles[i].y)
		{
			return true;//return true if the snake hit the obstacles
		}
	}
	return false;
}
void DeleteMap()
{
	for (int i = 0; i < NUMBER_OF_OBSTACLES; i++) {
		GoToXY(obstacles[i].x, obstacles[i].y);
		cout << " ";
		obstacles[i] = { 0,HEIGH_CONSOLE + 2 };
	}
	NUMBER_OF_OBSTACLES = 0;
}
int MapLevel1() {
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
int MapLevel2()
{
	int pos = 0;
	GoToXY(board[0].x + 5, board[0].y + 5);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++)
	{
		cout << '\xb2';
		obstacles[pos] = { board[0].x + 5 + i,board[0].y + 5 };
		pos++;
	}
	GoToXY(board[(WIDTH_BOARD) / 2].x-10, board[0].y  + 10);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++)
	{
		cout << '\xb2';
		obstacles[pos] = { board[(WIDTH_BOARD) / 2].x-10+i,board[0].y + 10 };
		pos++;
	}
	GoToXY(board[0].x + 5, board[0].y + 15);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++)
	{
		cout << '\xb2';
		obstacles[pos] = { board[0].x + 5 + i,board[0].y + 15};
		pos++;
	}
	GoToXY(board[(WIDTH_BOARD) / 2].x - 10, board[0].y + 20);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++)
	{
		cout << '\xb2';
		obstacles[pos] = { board[(WIDTH_BOARD) / 2].x -10 + i,board[0].y + 20 };
		pos++;
	}
	GoToXY(board[0].x + 5, board[0].y + 25);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++)
	{
		cout << '\xb2';
		obstacles[pos] = { board[0].x + 5 + i,board[0].y + 25 };
		pos++;
	}
	return pos;
}
int MapLevel3()
{
	int pos;
	int x, y;
	for (pos=0;pos<20; pos++)
	{
		x = RandomInRange(board[0].x + 2, board[0].x + WIDTH_BOARD - 2);
		y = RandomInRange(board[0].y + 2, board[0].y + HEIGHT_BOARD - 2);
		GoToXY(x, y);
		cout << '\xb2';
		obstacles[pos] = { x,y };
		pos++;
	}
	return pos;
}