#include "snakegame.h"

using namespace std;

void ToggleNormalStateButton(BUTTON a) {
	SetConsoleColor(DefaultBgColor, DefaultBgColor);
	FillRectangle(a.st.x, a.st.y, a.width, a.height);
	SetConsoleColor(DefaultTextColor, DefaultBgColor); //default colors
	DrawRectangle(a.st.x, a.st.y, a.width, a.height);
	GoToXY(a.text_st.x, a.text_st.y);
	cout << a.text_value;
}

void ToggleActiveStateButton(BUTTON a) {
	FillRectangle(a.st.x, a.st.y, a.width, a.height);
	SetConsoleColor(DefaultBgColor, DefaultTextColor);
	GoToXY(a.text_st.x, a.text_st.y);
	cout << a.text_value;
	SetConsoleColor(DefaultTextColor, DefaultBgColor);  //default colors
}


void DrawMenu() {
	system("cls");
	//ASCII art title
	int title_width, title_height;
	GetWidthAndHeightFile("title.txt", title_width, title_height);
	PrintTextFile((WIDTH_CONSOLE - title_width) / 2, 1, "title.txt");

	//Menu outside border
	DrawRectangle(3, 9, WIDTH_CONSOLE - 3 * 2, HEIGHT_CONSOLE - 9 - 1);


	for (int i = 0; i < 5; ++i) {
		ToggleNormalStateButton(main_button[i]);
	}

	/*GoToXY(116, 13); cout << "           /^\\/^\\";
	GoToXY(116, 14); cout << "         _|__|  O|";
	GoToXY(116, 15); cout << "\\/     /~     \\_/ \\";
	GoToXY(116, 16); cout << "\\____|__________/  \\";
	GoToXY(116, 17); cout << "        \\_______      \\";
	GoToXY(116, 18); cout << "                `\\     \\                 \\";
	GoToXY(116, 19); cout << "                 |     |                  \\";
	GoToXY(116, 20); cout << "                /      /                    \\";
	GoToXY(116, 21); cout << "                /     /                       \\\\";
	GoToXY(116, 22); cout << "              /      /                         \\ \\";
	GoToXY(116, 23); cout << "             /     /                            \\  \\";
	GoToXY(116, 24); cout << "           /     /             _----_            \\   \\";
	GoToXY(116, 25); cout << "          /     /           _-~      ~-_         |   |";
	GoToXY(116, 26); cout << "         (      (        _-~    _--_    ~-_     _/   |";
	GoToXY(116, 27); cout << "          \\      ~-____-~    _-~    ~-_    ~-_-~    /";
	GoToXY(116, 28); cout << "            ~-_           _-~          ~-_       _-~";
	GoToXY(116, 29); cout << "               ~--______-~                ~-___-~";
	*/
	PrintSnakeTextFile(116, 13, "assets\\ascii\\happysnake.txt");
	//PrintTextFile(70, 10, "assets\\ascii\\paused.txt");
}

void DrawAboutScreen() {
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	GoToXY(10, 12);
	cout << "About us";

}

void DrawLoadGameScreen() {
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	GoToXY(10, 12);
	cout << "Load game";
}

void DrawSettingsScreen() {
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	PrintFile(23, 14, "assets\\ascii\\sounds.txt");
	for (int i = 0; i < 2; ++i) {
		ToggleNormalStateButton(sound_button[i]);
	}
}
