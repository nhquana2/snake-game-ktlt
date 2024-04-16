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

void DrawMap() {
	for (int i = 0; i < NUMBER_OF_OBSTACLES; ++i) {
		GoToXY(obstacles[i].x, obstacles[i].y);
		cout << '\xb2';
	}
}

void DeleteMap() {
	for (int i = 0; i < NUMBER_OF_OBSTACLES; i++) {
		GoToXY(obstacles[i].x, obstacles[i].y);
		cout << " ";
		obstacles[i] = { 0,HEIGHT_CONSOLE + 2 };
	}
	NUMBER_OF_OBSTACLES = 0;
}
int MapLevel1() {
	PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y - 7, "assets\\ascii\\level 2.txt", DefaultStatusColor);
	PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 1, "assets\\ascii\\battery.txt", DefaultStatusColor);

	int pos = 0;
	GoToXY(board[0].x + 10, board[0].y + 4);
	for (int i = 0; i < WIDTH_BOARD - 7 - (board[0].x + 10); i++)
	{
		cout << '\xb2';
		obstacles[pos] = { board[0].x + 10 + i, board[0].y + 4 };
		pos++;
	}
	for (int i = 1; i < HEIGHT_BOARD - 10; i++)
	{
		GoToXY(board[0].x + 10, board[0].y + 4 + i);
		obstacles[pos] = { board[0].x + 10 , board[0].y + 4 + i };
		pos++;
		cout << '\xb2';
		GoToXY(board[0].x + 11, board[0].y + 4 + i);
		obstacles[pos] = { board[0].x + 11 , board[0].y + 4 + i };
		pos++;
		cout << '\xb2';
		GoToXY(board[0].x + (WIDTH_BOARD - 12), board[0].y + 4 + i);
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
	PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y - 7, "assets\\ascii\\level 3.txt", DefaultStatusColor);
	PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 1, "assets\\ascii\\battery.txt", DefaultStatusColor);

	int pos = 0;
	GoToXY(board[0].x + 5, board[0].y + 5);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++) {
		cout << '\xb2';
		obstacles[pos] = { board[0].x + 5 + i,board[0].y + 5 };
		pos++;
	}
	GoToXY(board[(WIDTH_BOARD) / 2].x - 10, board[0].y + 10);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++) {
		cout << '\xb2';
		obstacles[pos] = { board[(WIDTH_BOARD) / 2].x - 10 + i,board[0].y + 10 };
		pos++;
	}
	GoToXY(board[0].x + 5, board[0].y + 15);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++) {
		cout << '\xb2';
		obstacles[pos] = { board[0].x + 5 + i,board[0].y + 15 };
		pos++;
	}
	GoToXY(board[(WIDTH_BOARD) / 2].x - 10, board[0].y + 20);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++) {
		cout << '\xb2';
		obstacles[pos] = { board[(WIDTH_BOARD) / 2].x - 10 + i,board[0].y + 20 };
		pos++;
	}
	GoToXY(board[0].x + 5, board[0].y + 25);
	for (int i = 0; i < (WIDTH_BOARD) / 2 + 5; i++) {
		cout << '\xb2';
		obstacles[pos] = { board[0].x + 5 + i,board[0].y + 25 };
		pos++;
	}
	return pos;
}
int MapLevel3() {
	PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y - 7, "assets\\ascii\\level 4.txt", DefaultStatusColor);
	PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 1, "assets\\ascii\\battery.txt", DefaultStatusColor);

	bullet_down.x = board[0].x + 60;
	bullet_down.y = board[0].y + 1;

	bullet_up.x = board[0].x + 61;
	bullet_up.y = board[0].y + HEIGHT_BOARD - 2;

	int pos = 0;
	GoToXY(10, 20);
	for (int i = 0; i < 45; i++)
	{
		cout << '\xb2';
		obstacles[pos] = { 10 + i,20 };
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
		obstacles[pos] = { 54, 19 - i };
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
		obstacles[pos] = { 72, 19 - i };
		pos++;
		GoToXY(73, 19 - i);
		cout << '\xb2';
		obstacles[pos] = { 73, 19 - i };
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
		obstacles[pos] = { 72, 27 + i };
		pos++;
		GoToXY(73, 27 + i);
		cout << '\xb2';
		obstacles[pos] = { 73, 27 + i };
		pos++;
	}
	return pos;
}
int FinalMap() {
	PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y - 7, "assets\\ascii\\level 5.txt", DefaultStatusColor);

	int pos = 0;
	obstacles[pos++] = { 86,10 };
	GoToXY(86, 10);
	cout << '\xb2';
	obstacles[pos++] = { 87,10 };
	GoToXY(87, 10);
	cout << '\xb2';
	GoToXY(87, 11);
	cout << '\xb2';
	obstacles[pos++] = { 86,12 };
	GoToXY(86, 12);
	cout << '\xb2';
	obstacles[pos++] = { 87,12 };
	GoToXY(87, 12);
	cout << '\xb2';
	TELE_POINT_2.x = 86;
	TELE_POINT_2.y = 11;

	obstacles[pos++] = { 4,35 };
	GoToXY(4, 35);
	cout << '\xb2';
	GoToXY(4, 36);
	cout << '\xb2';
	obstacles[pos++] = { 4,37 };
	GoToXY(4, 37);
	cout << '\xb2';
	obstacles[pos++] = { 5,35 };
	GoToXY(5, 35);
	cout << '\xb2';
	obstacles[pos++] = { 5,37 };
	GoToXY(5, 37);
	cout << '\xb2';
	TELE_POINT_1.x = 5;
	TELE_POINT_1.y = 36;

	for (int i = board[0].y + 1; i < board[0].y + HEIGHT_BOARD - 1; i++) {
		if (i == board[0].y + 4 || i == board[0].y + 13 || i == board[0].y + 22) continue;
		SetConsoleColor(Red, DefaultBgColor);
		obstacles[pos++] = { 89,i };
		GoToXY(89, i); cout << '\xb2';
		obstacles[pos++] = { 88,i };
		GoToXY(88, i); cout << '\xb2';
		SetConsoleColor(DefaultTextColor, DefaultBgColor);
	}
	for (int i = board[0].y + 1; i < board[0].y + HEIGHT_BOARD - 1; i++) {
		if (i == board[0].y + 4 || i == board[0].y + 13 || i == board[0].y + 22) {
			continue;
		}
		obstacles[pos++] = { 40,i };
		GoToXY(40, i); cout << '\xb2';
	}
	return pos;
}
void DrawTelePoint(int x1, int y1, int x2, int y2) {
	//delete old pixel
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
}