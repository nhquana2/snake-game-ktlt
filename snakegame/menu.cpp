#include "snakegame.h"

using namespace std;

void InitMainButtons() {
	main_button[0].st = { 15, 11 };
	main_button[0].file_path = "assets\\ascii\\playbutton.txt";

	main_button[1].st = { 15, 21 };
	main_button[1].file_path = "assets\\ascii\\loadbutton.txt";

	main_button[2].st = { 15, 31 };
	main_button[2].file_path = "assets\\ascii\\settingbutton.txt";

	main_button[3].st = { 65, 11 };
	main_button[3].file_path = "assets\\ascii\\aboutbutton.txt";

	main_button[4].st = { 65, 21 };
	main_button[4].file_path = "assets\\ascii\\rankbutton.txt";

	main_button[5].st = { 65, 31 };
	main_button[5].file_path = "assets\\ascii\\exitbutton.txt";
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

void ToggleNormalStateDecorButton(DECOR_BUTTON a) {
	DrawButton(a, 0);
}

void ToggleActiveStateDecorButton(DECOR_BUTTON a) {
	DrawButton(a, 1);
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
	//PrintTextFile((WIDTH_CONSOLE - title_width) / 2, 1, "title.txt");
	PrintTitle2File(30, 0, "assets\\ascii\\snakegamenew.txt");
	DrawKeyCap(0, 0, 'W');
	//Menu outside border
	DrawRectangle(3, 9, WIDTH_CONSOLE - 3 * 2, HEIGHT_CONSOLE - 9 - 1);


	for (int i = 0; i < 6; ++i) {
		ToggleNormalStateDecorButton(main_button[i]);
	}

	
	//PrintSnakeTextFile(116, 13, "assets\\ascii\\happysnake.txt");
	/*DrawPlayButton(1);
	DrawLoadButton(1);
	DrawAboutButton(1);
	DrawSettingButton(1);
	DrawLeaderButton(1);
	DrawExitButton(1);*/
	//DrawOcToPus(130, 10);
	//DrawOcToPusHidden(1, 1);

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
	PrintFile(75, 16, "assets\\ascii\\color.txt");
	
	if (SOUND == 1)	PrintFile(58, 14, "assets\\ascii\\soundon.txt");
	for (int i = 0; i < 2; ++i) {
		ToggleNormalStateButton(sound_button[i]);
	}
	for (int j = 0; j < 4; ++j) {
		ToggleNormalStateButton(color_button[j]);
	}
}

void DrawLeaderBoardScreen() {
	NUMBER_OF_PLAYERS = LeaderBoard(Player);
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	FillAreaColor(11,11, 56, 18+NUMBER_OF_PLAYERS, Red);
	SetConsoleColor(Yellow, Red);
	PrintFile(13, 12, "assets\\ascii\\leaderboard.txt");
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	PrintCup(82, 16);

	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	GoToXY(13, 16);
	SetConsoleColor(DefaultTextColor, Red);
	cout << "USERNAME     SCORE     TIME PLAYED";

	for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
		GoToXY(13, 17+i + 1);
		cout << Player[i].name; 
		GoToXY(26,17+ i + 1);
		cout << Player[i].SCORE;
		GoToXY(38, 17 + i + 1);
		cout << Player[i].TIME;

	}
	SetConsoleColor(DefaultTextColor, DefaultBgColor);

	SetConsoleColor(DefaultTextColor, DefaultBgColor);
}

void DrawButton(DECOR_BUTTON a, int mode) {
	char s[100];
	strcpy(s, a.file_path.c_str());
	if (mode == 0) {//normal
		PrintColorFile_Ver2(a.st.x, a.st.y, s , Black, LightRed);
		PrintColorFile_Ver2(a.st.x, a.st.y, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(a.st.x, a.st.y, "assets\\ascii\\shadowbutton.txt", Red, Black);
		PrintColorFile_Ver2(a.st.x, a.st.y, "assets\\ascii\\fix2button.txt", LightRed, Red);
	}
	else {//active
		PrintColorFile_Ver2(a.st.x, a.st.y, s , Black, LightYellow);
		PrintColorFile_Ver2(a.st.x, a.st.y, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(a.st.x, a.st.y, "assets\\ascii\\shadowbutton.txt", Yellow, Black);
		PrintColorFile_Ver2(a.st.x, a.st.y, "assets\\ascii\\fix2button.txt", LightYellow, Yellow);
	}
}

/*void DrawPlayButton(int mode) {
	
	if (mode == 0) {//normal
		PrintColorFile_Ver2(15, 10, "assets\\ascii\\playbutton.txt", Black, LightRed);
		PrintColorFile_Ver2(15, 10, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(15, 10, "assets\\ascii\\shadowbutton.txt", Red, Black);
		PrintColorFile_Ver2(15, 10, "assets\\ascii\\fix2button.txt", LightRed, Red);
	}
	else {//active
		PrintColorFile_Ver2(15, 10, "assets\\ascii\\playbutton.txt", Black, LightYellow);
		PrintColorFile_Ver2(15, 10, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(15, 10, "assets\\ascii\\shadowbutton.txt", Yellow, Black);
		PrintColorFile_Ver2(15, 10, "assets\\ascii\\fix2button.txt", LightYellow, Yellow);
	}
	
	
}
void DrawLoadButton(int mode) {
	if (mode ==0) {//normal
		PrintColorFile_Ver2(15, 20, "assets\\ascii\\loadbutton.txt", Black, LightRed);
		PrintColorFile_Ver2(15, 20, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(15, 20, "assets\\ascii\\shadowbutton.txt", Red, Black);
		PrintColorFile_Ver2(15, 20, "assets\\ascii\\fix2button.txt", LightRed, Red);
	}
	else {//active
		PrintColorFile_Ver2(15, 20, "assets\\ascii\\loadbutton.txt", Black, LightYellow);
		PrintColorFile_Ver2(15, 20, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(15, 20, "assets\\ascii\\shadowbutton.txt", Yellow, Black);
		PrintColorFile_Ver2(15, 20, "assets\\ascii\\fix2button.txt", LightYellow, Yellow);
	}
}
void DrawSettingButton(int mode) {
	if (mode == 0) {//normal
		PrintColorFile_Ver2(15, 30, "assets\\ascii\\settingbutton.txt", Black, LightRed);
		PrintColorFile_Ver2(15, 30, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(15, 30, "assets\\ascii\\shadowbutton.txt", Red, Black);
		PrintColorFile_Ver2(15, 30, "assets\\ascii\\fix2button.txt", LightRed, Red);
	}
	else {//active
		PrintColorFile_Ver2(15, 30, "assets\\ascii\\settingbutton.txt", Black, LightYellow);
		PrintColorFile_Ver2(15, 30, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(15, 30, "assets\\ascii\\shadowbutton.txt", Yellow, Black);
		PrintColorFile_Ver2(15, 30, "assets\\ascii\\fix2button.txt", LightYellow, Yellow);
	}
}
void DrawAboutButton(int mode) {
	if (mode == 0) {//normal
		PrintColorFile_Ver2(65, 10, "assets\\ascii\\aboutbutton.txt", Black, LightRed);
		PrintColorFile_Ver2(65, 10, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(65, 10, "assets\\ascii\\shadowbutton.txt", Red, Black);
		PrintColorFile_Ver2(65, 10, "assets\\ascii\\fix2button.txt", LightRed, Red);
	}
	else {//active
		PrintColorFile_Ver2(65, 10, "assets\\ascii\\aboutbutton.txt", Black, LightYellow);
		PrintColorFile_Ver2(65, 10, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(65, 10, "assets\\ascii\\shadowbutton.txt", Yellow, Black);
		PrintColorFile_Ver2(65, 10, "assets\\ascii\\fix2button.txt", LightYellow, Yellow);
	}
}
void DrawLeaderButton(int mode) {
	if (mode == 0) {//normal
		PrintColorFile_Ver2(65, 20, "assets\\ascii\\rankbutton.txt", Black, LightRed);
		PrintColorFile_Ver2(65, 20, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(65, 20, "assets\\ascii\\shadowbutton.txt", Red, Black);
		PrintColorFile_Ver2(65, 20, "assets\\ascii\\fix2button.txt", LightRed, Red);
	}
	else {//active
		PrintColorFile_Ver2(65, 20, "assets\\ascii\\rankbutton.txt", Black, LightYellow);
		PrintColorFile_Ver2(65, 20, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(65, 20, "assets\\ascii\\shadowbutton.txt", Yellow, Black);
		PrintColorFile_Ver2(65, 20, "assets\\ascii\\fix2button.txt", LightYellow, Yellow);
	}
}
void DrawExitButton(int mode) {
	if (mode == 0) {//normal
		PrintColorFile_Ver2(65, 30, "assets\\ascii\\exitbutton.txt", Black, LightRed);
		PrintColorFile_Ver2(65, 30, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(65, 30, "assets\\ascii\\shadowbutton.txt", Red, Black);
		PrintColorFile_Ver2(65, 30, "assets\\ascii\\fix2button.txt", LightRed, Red);
	}
	else {//active
		PrintColorFile_Ver2(65, 30, "assets\\ascii\\exitbutton.txt", Black, LightYellow);
		PrintColorFile_Ver2(65, 30, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(65, 30, "assets\\ascii\\shadowbutton.txt", Yellow, Black);
		PrintColorFile_Ver2(65, 30, "assets\\ascii\\fix2button.txt", LightYellow, Yellow);
	}
}*/

void DrawOcToPus(int x, int y) {
	//int x = 100, y = 15;

	if (octopus_time == 3) {
		//pic1
		FillAreaColor(x - 3, y - 2, x + 12, y + 8, DefaultBgColor);
		PrintColorFile_Ver2(x, y, "assets\\ascii\\octopus3.txt", Black, LightPurple);
		PrintColorFile_Ver2(x, y, "assets\\ascii\\fixotp3.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y, "assets\\ascii\\eyesotp.txt", White, Black);
	}
	else if (octopus_time == 5) {
		//pic2
		FillAreaColor(x - 2, y -2, x + 12, y + 8, DefaultBgColor);
		PrintColorFile_Ver2(x, y +1, "assets\\ascii\\octopus1.txt", Black, LightPurple);
		PrintColorFile_Ver2(x, y +1, "assets\\ascii\\fixotp1.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y +1, "assets\\ascii\\eyesotp.txt", White, Black);
	}
	else if (octopus_time == 7) {
		//pic3
		FillAreaColor(x - 2, y -2, x + 12, y + 8, DefaultBgColor);
		PrintColorFile_Ver2(x, y +2, "assets\\ascii\\octopus2.txt", Black, LightPurple);
		PrintColorFile_Ver2(x, y +2, "assets\\ascii\\fixotp2.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y +2, "assets\\ascii\\eyesotp.txt", White, Black);

	}
	else if (octopus_time == 9) {
		//pic4
		FillAreaColor(x - 2, y - 2, x + 12, y + 8, DefaultBgColor);
		PrintColorFile_Ver2(x, y -1, "assets\\ascii\\octopus4.txt", Black, LightPurple);
		PrintColorFile_Ver2(x, y -1, "assets\\ascii\\fixotp4.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y -1, "assets\\ascii\\eyesotp.txt", White, Black);
		octopus_time = 1;
	}

	octopus_time++;

	
}

void DrawOcToPusHidden1(int x, int y) {
	
	if (octopus_hidden_time == 1) {
		//pic1
		FillAreaColor(x - 1, y - 1, x + 16, y + 5, DefaultBgColor);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\otphidden2.txt", Black, LightPurple);
		PrintColorFile_Ver2(x + 4, y - 1, "assets\\ascii\\eyesotp.txt", LightPurple, White);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water2.txt", BrightWhite, LightPurple);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix1hidden2.txt", BrightWhite, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix2hidden2.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix3hidden2.txt", DefaultBgColor, BrightWhite);

	}
	else if (octopus_hidden_time == 15) {
		//pic2
		FillAreaColor(x - 2, y - 2, x + 20, y + 3, DefaultBgColor);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\otphidden1.txt", Black, LightPurple);
		PrintColorFile_Ver2(x + 4, y - 1, "assets\\ascii\\eyesotp.txt", White, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water1.txt", BrightWhite, LightPurple);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix1hidden1.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix2hidden1.txt", DefaultBgColor, BrightWhite);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix3hidden1.txt", BrightWhite, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water3.txt", BrightWhite, DefaultBgColor);
	}
	else if (octopus_hidden_time ==30 ) {
		//pic3
		//FillAreaColor(x - 2, y - 2, x + 20, y + 3, DefaultBgColor);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\otphidden1.txt", Black, LightPurple);
		PrintColorFile_Ver2(x + 4, y - 1, "assets\\ascii\\eyesotp.txt", White, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water1.txt", BrightWhite, LightPurple);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix1hidden1.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix2hidden1.txt", DefaultBgColor, BrightWhite);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix3hidden1.txt", BrightWhite, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water4.txt", BrightWhite, DefaultBgColor);

	}
	else if (octopus_hidden_time == 45) {
		//pic4
		FillAreaColor(x - 2, y - 2, x + 16, y + 3, DefaultBgColor);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\otphidden2.txt", Black, LightPurple);
		PrintColorFile_Ver2(x + 4, y - 1, "assets\\ascii\\eyesotp.txt", LightPurple, White);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water2.txt", BrightWhite, LightPurple);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix1hidden2.txt", BrightWhite, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix2hidden2.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix3hidden2.txt", DefaultBgColor, BrightWhite);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water5.txt", BrightWhite, DefaultBgColor);
		octopus_hidden_time = -15;
	}
	//octopus_hidden_time++;
	
}

void DrawOcToPusHidden2(int x, int y) {

	if (octopus_hidden_time == 1) {
		//pic1
		FillAreaColor(x - 1, y - 1, x + 15, y + 3, DefaultBgColor);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\otphidden2.txt", Black, LightPurple);
		PrintColorFile_Ver2(x + 4, y - 1, "assets\\ascii\\eyesotp.txt", LightPurple, White);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water2.txt", BrightWhite, LightPurple);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix1hidden2.txt", BrightWhite, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix2hidden2.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix3hidden2.txt", DefaultBgColor, BrightWhite);

	}
	else if (octopus_hidden_time == 15) {
		//pic2
		FillAreaColor(x - 2, y - 2, x + 20, y + 3, DefaultBgColor);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\otphidden1.txt", Black, LightPurple);
		PrintColorFile_Ver2(x + 4, y - 1, "assets\\ascii\\eyesotp.txt", White, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water1.txt", BrightWhite, LightPurple);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix1hidden1.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix2hidden1.txt", DefaultBgColor, BrightWhite);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix3hidden1.txt", BrightWhite, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water3.txt", BrightWhite, DefaultBgColor);
	}
	else if (octopus_hidden_time == 30) {
		//pic3
		//FillAreaColor(x - 2, y - 2, x + 20, y + 3, DefaultBgColor);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\otphidden1.txt", Black, LightPurple);
		PrintColorFile_Ver2(x + 4, y - 1, "assets\\ascii\\eyesotp.txt", White, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water1.txt", BrightWhite, LightPurple);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix1hidden1.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix2hidden1.txt", DefaultBgColor, BrightWhite);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix3hidden1.txt", BrightWhite, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water4.txt", BrightWhite, DefaultBgColor);

	}
	else if (octopus_hidden_time == 45) {
		//pic4
		FillAreaColor(x - 2, y - 2, x + 20, y + 3, DefaultBgColor);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\otphidden2.txt", Black, LightPurple);
		PrintColorFile_Ver2(x + 4, y - 1, "assets\\ascii\\eyesotp.txt", LightPurple, White);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water2.txt", BrightWhite, LightPurple);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix1hidden2.txt", BrightWhite, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix2hidden2.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\fix3hidden2.txt", DefaultBgColor, BrightWhite);
		PrintColorFile_Ver2(x, y - 1, "assets\\ascii\\water5.txt", BrightWhite, DefaultBgColor);
		octopus_hidden_time = -15;
	}
	octopus_hidden_time++;

}