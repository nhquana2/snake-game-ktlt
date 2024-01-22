#include "snakegame.h"

using namespace std;

void DrawMenu() {
	system("cls");
	//ASCII art title
	int title_width, title_height;
	GetWidthAndHeightFile("title.txt", title_width, title_height);
	PrintFile((WIDTH_CONSOLE - title_width) / 2, 1, "title.txt");

	//Menu outside border
	DrawRectangle(3, 9, WIDTH_CONSOLE - 3 * 2, HEIGH_CONSOLE - 9 - 1);

	//Button: NEW GAME
	DrawRectangle(80, 12, 20, 3);
	GoToXY(86, 13);
	cout << "NEW GAME";
	if (MENU_OPTION == 0) cout << "  \xDB";

	//Button: LOAD GAME
	DrawRectangle(80, 16, 20, 3);
	GoToXY(86, 17);
	cout << "LOAD GAME";
	if (MENU_OPTION == 1) cout << "  \xDB";

	//Button: SETTINGS
	DrawRectangle(80, 20, 20, 3);
	GoToXY(86, 21);
	cout << "SETTINGS";
	if (MENU_OPTION == 2) cout << "  \xDB";

	//Button: ABOUT
	DrawRectangle(80, 24, 20, 3);
	GoToXY(86, 25);
	cout << "ABOUT";
	if (MENU_OPTION == 3) cout << "  \xDB";

	//Button: EXIT
	DrawRectangle(80, 28, 20, 3);
	GoToXY(86, 29);
	cout << "EXIT";
	if (MENU_OPTION == 4) cout << "  \xDB";
}