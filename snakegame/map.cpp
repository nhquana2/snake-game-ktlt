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
void DeleteMap(){
	for (int i = 0; i < NUMBER_OF_OBSTACLES; i++) {
		GoToXY(obstacles[i].x, obstacles[i].y);
		cout << " ";
		obstacles[i] = { 0,HEIGHT_CONSOLE + 2 };
	}
	NUMBER_OF_OBSTACLES = 0;
}
int MapLevel1() {
	PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y + 2, "assets\\ascii\\level 2.txt");
	PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 10, "assets\\ascii\\battery.txt");

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
	PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y + 2, "assets\\ascii\\level 3.txt");
	PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 10, "assets\\ascii\\battery.txt");

	int pos = 0;
	GoToXY(board[0].x + 5, board[0].y + 5);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++){
		cout << '\xb2';
		obstacles[pos] = { board[0].x + 5 + i,board[0].y + 5 };
		pos++;
	}
	GoToXY(board[(WIDTH_BOARD) / 2].x-10, board[0].y  + 10);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++){
		cout << '\xb2';
		obstacles[pos] = { board[(WIDTH_BOARD) / 2].x-10+i,board[0].y + 10 };
		pos++;
	}
	GoToXY(board[0].x + 5, board[0].y + 15);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++){
		cout << '\xb2';
		obstacles[pos] = { board[0].x + 5 + i,board[0].y + 15};
		pos++;
	}
	GoToXY(board[(WIDTH_BOARD) / 2].x - 10, board[0].y + 20);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++){
		cout << '\xb2';
		obstacles[pos] = { board[(WIDTH_BOARD) / 2].x -10 + i,board[0].y + 20 };
		pos++;
	}
	GoToXY(board[0].x + 5, board[0].y + 25);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++){
		cout << '\xb2';
		obstacles[pos] = { board[0].x + 5 + i,board[0].y + 25 };
		pos++;
	}
	return pos;
}
int MapLevel3()
{
	PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y + 2, "assets\\ascii\\level 4.txt");
	PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 10, "assets\\ascii\\battery.txt");

	int pos;
	int x, y;
	for (pos=0;pos<20; pos++)
	{
		x = RandomInRange(board[0].x + 2, board[0].x + WIDTH_BOARD - 2);
		y = RandomInRange(board[0].y + 2, board[0].y + HEIGHT_BOARD - 2);
		GoToXY(x, y);
		cout << '\xb2';
		obstacles[pos] = { x,y };
	}
	return pos;
}
int MapLevel4() {

	PrintFile(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 10, "assets\\ascii\\battery.txt");

	bullet_down.x = board[0].x + 60;
	bullet_down.y = board[0].y + 1;

	bullet_up.x = board[0].x + 61;
	bullet_up.y = board[0].y + HEIGHT_BOARD - 2;
	
	int pos = 0;
	GoToXY(10, 20);
	for (int i = 0; i < 45; i++)
	{
		cout << '\xb2';
		obstacles[pos] = { 10+i,20};
		pos++;
	}
	GoToXY(72, 20);
	for (int i = 0; i < 45; i++)
	{
		cout << '\xb2';
		obstacles[pos] = { 72 + i,20 };
		pos++;
	}
	GoToXY(10, 26);
	for (int i = 0; i < 45; i++)
	{
		cout << '\xb2';
		obstacles[pos] = { 10 + i,26 };
		pos++;
	}
	GoToXY(72, 26);
	for (int i = 0; i < 45; i++)
	{
		cout << '\xb2';
		obstacles[pos] = { 72 + i,26 };
		pos++;
	}
	
	for (int i = 0; i < 8; i++)
	{
		GoToXY(54, 19 - i);
		cout << '\xb2';
		obstacles[pos] = { 54, 19-i };
		pos++; 
		GoToXY(53, 19 - i);
		cout << '\xb2';
		obstacles[pos] = { 53, 19 - i };
		pos++;
	}
	for (int i = 0; i < 8; i++)
	{
		GoToXY(72, 19 - i);
		cout << '\xb2';
		obstacles[pos] = { 54, 19 - i };
		pos++;
		GoToXY(73, 19 - i);
		cout << '\xb2';
		obstacles[pos] = { 53, 19 - i };
		pos++;
	}
	for (int i = 0; i < 8; i++)
	{
		GoToXY(54, 27 + i);
		cout << '\xb2';
		obstacles[pos] = { 54, 27 + i };
		pos++;
		GoToXY(53, 27 + i);
		cout << '\xb2';
		obstacles[pos] = { 53, 27 + i };
		pos++;
	}
	for (int i = 0; i < 8; i++)
	{
		GoToXY(72, 27 + i);
		cout << '\xb2';
		obstacles[pos] = { 54, 27 + i };
		pos++;
		GoToXY(73, 27 + i);
		cout << '\xb2';
		obstacles[pos] = { 53, 27 + i };
		pos++;
	}
	return pos;
}
void DrawTelePoint(int x1, int y1, int x2, int y2) {
	//delete old pixel
	//SetConsoleColor(Red, Black);
	GoToXY(TELE_POINT_1.x, TELE_POINT_1.y);
	cout << "\xba";
	GoToXY(TELE_POINT_2.x, TELE_POINT_2.y);
	cout << "\xba";
	
	//Create new coordinates
	TELE_POINT_1.x = x1;
	TELE_POINT_1.y = y1;
	TELE_POINT_2.x = x2;
	TELE_POINT_2.y = y2;
	GoToXY(TELE_POINT_1.x, TELE_POINT_1.y);
	cout << " ";
	GoToXY(TELE_POINT_2.x, TELE_POINT_2.y);
	cout << " ";
	//SetConsoleColor(White, Black);
}