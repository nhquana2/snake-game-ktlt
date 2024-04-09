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
		else if(c=='s'){

			SetConsoleColor(DefaultTextColor, DefaultBgColor);
			cout << " ";
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
			SetConsoleColor(DefaultTextColor, DefaultBgColor);
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
void PrintTitleFile(int x, int y, const char* FileName) {
	ifstream ifs;
	int st_x = x, st_y = y;
	ifs.open(FileName);
	if (!ifs.good()) return;
	char c;
	GoToXY(x, y);
	while (ifs.get(c)) {
		if (c != ' ') {
			SetConsoleColor(Red, DefaultBgColor);
			cout << c;
		}
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
}

void PrintTitle2File(int x, int y, const char* FileName) {
	ifstream ifs;
	int st_x = x, st_y = y;
	ifs.open(FileName);
	if (!ifs.good()) return;
	char c;
	GoToXY(x, y);
	while (ifs.get(c)) {
		if (c != ' ') {
			SetConsoleColor(SnakeColor, DefaultBgColor);
			cout << c;
		}
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
}




void PrintSnakeStatusTextFile(int x, int y, const char* FileName) {
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
		else if (c == 's') {

			SetConsoleColor(DefaultTextColor, DefaultStatusColor);
			cout << " ";
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
			SetConsoleColor(DefaultTextColor, DefaultBgColor);
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
void PrintTextFile(int x, int y, const char* FileName) {
	ifstream ifs;
	int st_x = x, st_y = y;
	ifs.open(FileName);
	if (!ifs.good()) return;
	char c;
	GoToXY(x, y);
	while (ifs.get(c)) {
		if (c == 'o') {
			SetConsoleColor(Red, Red);
			cout << '\xb2';
			SetConsoleColor(DefaultTextColor, Red);
		}
		else if (c == '/') {
			SetConsoleColor(Yellow, Red);
			cout << '\xb2';
			SetConsoleColor(DefaultTextColor, DefaultBgColor);
		}
		else if (c == ' ') {
			SetConsoleColor(Yellow, Red);
			cout << c;
			SetConsoleColor(DefaultTextColor, DefaultBgColor);
		}
		else {
			SetConsoleColor(Yellow, Red);
			cout << c;
			SetConsoleColor(DefaultTextColor, DefaultBgColor);
		}
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
}

void PrintColorFile(int x, int y, const char* FileName, int background) {
	ifstream ifs;
	int st_x = x, st_y = y;
	ifs.open(FileName);
	if (!ifs.good()) return;
	char c;
	GoToXY(x, y);
	while (ifs.get(c)) {
		if (c == ' ') {
			SetConsoleColor(Black, background);
			cout << c;
		}
		else {
		SetConsoleColor(Black, background);
		cout << c;
		SetConsoleColor(DefaultTextColor, DefaultBgColor);
		}
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
}
void PrintColorFile_Ver2(int x, int y, const char* FileName,int colortext, int background) {
	ifstream ifs;
	int st_x = x, st_y = y;
	ifs.open(FileName);
	if (!ifs.good()) return;
	char c;
	GoToXY(x, y);
	while (ifs.get(c)) {
		if (c != '-') {
			SetConsoleColor(colortext, background);
			cout << c;
		}
		SetConsoleColor(DefaultTextColor, DefaultBgColor);
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
}

void PrintAuCup(int x, int y) {
	ifstream ifs;
	int st_x = x, st_y = y, cnst_x = x, cnst_y = y;
	ifs.open("assets/ascii/rankAu.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	char c;
	SetConsoleColor(Black, DefaultBgColor);
	while (ifs.get(c)) {
		if (c != ' ' && c != 'v') {
			SetConsoleColor(Black, LightYellow);
			cout << c;
		}
		else if (c == 'v') {
			SetConsoleColor(LightYellow, LightYellow);
			cout << '\xb2';
		}
		
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank5.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(BrightWhite, LightYellow);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank2.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(Yellow, LightYellow);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank4.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(DefaultBgColor, Black);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank6.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(Yellow, Black);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank7.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(Black, DefaultBgColor);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}

	GoToXY(cnst_x + 12, cnst_y + 14);
	SetConsoleColor(Red, LightYellow);
	cout << Player[0].name;
	SetConsoleColor(DefaultTextColor, DefaultBgColor);

	
}

void PrintAgCup(int x, int y) {
	ifstream ifs;
	int st_x = x, st_y = y, cnst_x = x, cnst_y = y;
	ifs.open("assets/ascii/rankAg.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	char c;
	SetConsoleColor(Black, DefaultBgColor);
	while (ifs.get(c)) {
		if (c != ' ' && c != 'b') {
			SetConsoleColor(Black, BrightWhite);
			cout << c;
		}
		else if (c == 'b') {
			SetConsoleColor(BrightWhite,BrightWhite);
			cout << '\xb2';
		}

		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank5.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(White, BrightWhite);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank2.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(White, BrightWhite);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank4.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(DefaultBgColor, Black);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank6.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(White, Black);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank7.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(Black, DefaultBgColor);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	GoToXY(cnst_x + 12, cnst_y + 14);
	SetConsoleColor(Red, BrightWhite);
	cout << Player[1].name;
	SetConsoleColor(DefaultTextColor, DefaultBgColor);


}
void PrintCuCup(int x, int y) {
	ifstream ifs;
	int st_x = x, st_y = y, cnst_x = x, cnst_y = y;
	ifs.open("assets/ascii/rankCu.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	char c;
	
	SetConsoleColor(Black, DefaultBgColor);
	while (ifs.get(c)) {
		if (c != ' ' && c != 'd') {
			SetConsoleColor(Black, LightRed);
			cout << c;
		}
		else if (c == 'd') {
			SetConsoleColor(LightRed, LightRed);
			cout << '\xb2';
		}

		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank5.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(BrightWhite, LightRed);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank2.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(Red, LightRed);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();
	
	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank4.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(DefaultBgColor, Black);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank6.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(Red, Black);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	ifs.close();

	x = cnst_x;
	y = cnst_y;
	ifs.open("assets/ascii/rank7.txt");
	if (!ifs.good()) return;
	GoToXY(x, y);
	SetConsoleColor(Black, DefaultBgColor);
	while (ifs.get(c)) {
		if (c != ' ') cout << c;
		if (c != '\n') ++x; else ++y, x = st_x;
		GoToXY(x, y);
	}
	GoToXY(cnst_x + 12, cnst_y + 14);
	SetConsoleColor(BrightWhite, LightRed);
	cout << Player[2].name;
	SetConsoleColor(DefaultTextColor, DefaultBgColor);


}
void PrintCup(int x, int y) {
	PrintAgCup(x, y);
	PrintCuCup(x+60, y);
	PrintAuCup(x+30, y);
}

void ChangeSnakeColor(int snake, int id) {
	SnakeColor = snake;
	IDColor = id;
}