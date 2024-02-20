#include "snakegame.h"

using namespace std;

void InitMainButtons() {
	main_button[0].st = { 80, 12 };
	main_button[0].width = 20;
	main_button[0].height = 3;
	main_button[0].text_st = { 86, 13 };
	main_button[0].text_value = "NEW GAME";

	main_button[1].st = { 80, 16 };
	main_button[1].width = 20;
	main_button[1].height = 3;
	main_button[1].text_st = { 86, 17 };
	main_button[1].text_value = "LOAD GAME";

	main_button[2].st = { 80, 20 };
	main_button[2].width = 20;
	main_button[2].height = 3;
	main_button[2].text_st = { 86, 21 };
	main_button[2].text_value = "SETTINGS";

	main_button[3].st = { 80, 24 };
	main_button[3].width = 20;
	main_button[3].height = 3;
	main_button[3].text_st = { 86, 25 };
	main_button[3].text_value = "ABOUT";

	main_button[4].st = { 80, 28 };
	main_button[4].width = 20;
	main_button[4].height = 3;
	main_button[4].text_st = { 85, 29 };
	main_button[4].text_value = "LEADERBOARD";

	main_button[5].st = { 80, 32 };
	main_button[5].width = 20;
	main_button[5].height = 3;
	main_button[5].text_st = { 86, 33 };
	main_button[5].text_value = "EXIT";
}

void InitSoundButtons() {
	sound_button[0].st = { 30, 21 };
	sound_button[0].width = 20;
	sound_button[0].height = 3;
	sound_button[0].text_st = { 30+10-1, 22 };
	sound_button[0].text_value = "ON";

	sound_button[1].st = { 30, 25 };
	sound_button[1].width = 20;
	sound_button[1].height = 3;
	sound_button[1].text_st = { 30+10-2, 26 };
	sound_button[1].text_value = "OFF";
}

void InitColorButtons() {
	color_button[0].st = { 75, 25 };
	color_button[0].width = 20;
	color_button[0].height = 3;
	color_button[0].text_st = { 75+10-2, 26};
	color_button[0].text_value = "BLUE";

	color_button[1].st = { 100, 25 };
	color_button[1].width = 20;
	color_button[1].height = 3;
	color_button[1].text_st = { 100+10-3, 26 };
	color_button[1].text_value = "GREEN";

	color_button[2].st = { 125, 25 };
	color_button[2].width = 20;
	color_button[2].height = 3;
	color_button[2].text_st = { 125+10-3, 26 };
	color_button[2].text_value = "YELLOW";

	color_button[3].st = { 150, 25 };
	color_button[3].width = 20;
	color_button[3].height = 3;
	color_button[3].text_st = { 150+10-2, 26 };
	color_button[3].text_value = "PINK";
}

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

void ToggleNormalStateSaveEntry(SAVE_ENTRY a, int pos) {
	SetConsoleColor(DefaultBgColor, DefaultBgColor);
	FillRectangle(a.st.x, a.st.y, 20, 1);
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	GoToXY(a.st.x, a.st.y);
	cout << pos + 1 << ". ";
	GoToXY(a.st.x + 5, a.st.y);
	cout << a.text_value;
	SetConsoleColor(DefaultTextColor, DefaultBgColor); //default colors
}

void ToggleActiveStateSaveEntry(SAVE_ENTRY a, int pos) {
	//SetConsoleColor(DefaultBgColor, DefaultBgColor);
	FillRectangle(a.st.x, a.st.y, 20, 1);
	SetConsoleColor(DefaultBgColor, DefaultTextColor);
	GoToXY(a.st.x, a.st.y);
	cout << pos + 1 << ". ";
	GoToXY(a.st.x + 5, a.st.y);
	cout << a.text_value;
	SetConsoleColor(DefaultTextColor, DefaultBgColor); //default colors
}


void DrawMenu() {
	system("cls");
	//ASCII art title
	int title_width, title_height;
	GetWidthAndHeightFile("title.txt", title_width, title_height);
	PrintTextFile((WIDTH_CONSOLE - title_width) / 2, 1, "title.txt");

	//Menu outside border
	DrawRectangle(3, 9, WIDTH_CONSOLE - 3 * 2, HEIGHT_CONSOLE - 9 - 1);


	for (int i = 0; i < 6; ++i) {
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
	//int nsize=LeaderBoard(Player);
	//GoToXY(0, 0);
	//for (int i = 0; i < nsize; i++) {
		//cout << Player[i].name << " ";
	//}
	//PrintTextFile(70, 10, "assets\\ascii\\paused.txt");
	
}

void DrawAboutScreen() {
	//playSound("assets\\sounds\\aboutus");
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	PrintFile(8, 13, "assets\\ascii\\nhquan.txt");
	PrintFile(8, 18, "assets\\ascii\\ttcuong.txt");
	PrintFile(8, 23, "assets\\ascii\\ttmy.txt");
	PrintFile(8, 28, "assets\\ascii\\thphuc.txt");
}

void DrawLoadGameScreen() {
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	GoToXY(10, 12);
	cout << "Load game";
	GoToXY(10, 13);
	for (int i = 0; i < save_entries.size(); ++i) {
		GoToXY(save_entries[i].st.x, save_entries[i].st.y);
		cout << i+1 << ". ";
		GoToXY(save_entries[i].st.x + 5, save_entries[i].st.y);
		cout << save_entries[i].text_value;
	}
}

void DrawSettingsScreen() {
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	PrintFile(22, 14, "assets\\ascii\\sounds.txt");
	if (SOUND == 1)	PrintFile(58, 14, "assets\\ascii\\soundon.txt");
	for (int i = 0; i < 2; ++i) {
		ToggleNormalStateButton(sound_button[i]);
	}
	for (int j = 0; j < 4; ++j) {
		ToggleNormalStateButton(color_button[j]);
	}
}

void DrawLeaderBoardScreen() {
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	GoToXY(10, 12);
	cout << "USERNAME     SCORE     TIME PLAYED";
	NUMBER_OF_PLAYERS = LeaderBoard(Player);
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
		GoToXY(10, 12+i + 1);
		cout << Player[i].name; 
		GoToXY(23,12+ i + 1);
		cout << Player[i].SCORE;
		GoToXY(33, 12 + i + 1);
		cout << Player[i].TIME;

	}
	
	PrintCup(82, 15);

	SetConsoleColor(DefaultTextColor, DefaultBgColor);
}