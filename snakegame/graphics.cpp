#include "snakegame.h"

using namespace std;


void PrintSnakeTextFile(int x, int y, const char* FileName) {
	ifstream ifs;
	int st_x = x, st_y = y;
	ifs.open(FileName);
	if (!ifs.good()) return;
	char c;
	GoToXY(x, y);
	while (ifs.get(c)) {
		if (c == '~') {
			SetConsoleColor(LightGreen, LightGreen);
			cout << '\xb2';

			SetConsoleColor(DefaultTextColor, DefaultBgColor);
		}
		else if (c == '?') {
			SetConsoleColor(White, White);
			cout << '\xb2';
			SetConsoleColor(DefaultTextColor, DefaultBgColor);
		}
		else if (c == 'l') {
			SetConsoleColor(LightRed, LightRed);
			cout << '\xb2';
			SetConsoleColor(DefaultTextColor, DefaultBgColor);
		}
		else if (c == '-') {
			SetConsoleColor(LightPurple, LightPurple);
			cout << '\xb2';
			SetConsoleColor(DefaultTextColor, DefaultBgColor);
		}
		else if (c == '/') {
			SetConsoleColor(Green, Green);
			cout << '\xb2';
			SetConsoleColor(DefaultTextColor, DefaultBgColor);
		}
		else if (c == 'o') {
			SetConsoleColor(Red, Red);
			cout << '\xb2';
			SetConsoleColor(DefaultTextColor, DefaultBgColor);
		}
		else if (c == ' ') {
			cout << c;
		}
		else {
			SetConsoleColor(DefaultTextColor, LightGreen);
			cout << c;
			SetConsoleColor(DefaultTextColor, DefaultBgColor);
		}
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
}