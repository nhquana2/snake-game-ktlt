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
	main_button[3].file_path = "assets\\ascii\\aboutusbutton.txt";

	main_button[4].st = { 65, 21 };
	main_button[4].file_path = "assets\\ascii\\rankbutton.txt";

	main_button[5].st = { 65, 31 };
	main_button[5].file_path = "assets\\ascii\\exitbutton.txt";
}

void InitColorButtons() {
	color_button[0].st = { 7, 25 };
	color_button[0].file_path = "assets\\ascii\\redbutton.txt";

	color_button[1].st = { 39, 25 };
	color_button[1].file_path = "assets\\ascii\\bluebutton.txt";

	color_button[2].st = { 71, 25 };
	color_button[2].file_path = "assets\\ascii\\greenbutton.txt";

	color_button[3].st = { 104, 25 };
	color_button[3].file_path = "assets\\ascii\\yellowbutton.txt";
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
	//Menu outside border
	DrawRectangle(3, 9, WIDTH_CONSOLE - 3 * 2, HEIGHT_CONSOLE - 9 - 1);


	for (int i = 0; i < 6; ++i) {
		ToggleNormalStateDecorButton(main_button[i]);
	}

	
	PrintSnakeTextFile(120, 11, "assets\\ascii\\happysnake.txt");
	
	//DrawOcToPus(130, 10);
	//DrawOcToPusHidden(1, 1);
	//DrawSettingButton(0);
}

void DrawAboutScreen() {
	//playSound("assets\\sounds\\aboutus");
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	PrintFile(8, 13, "assets\\ascii\\nhquan.txt");
	PrintFile(8, 18, "assets\\ascii\\ttcuong.txt");
	PrintFile(8, 23, "assets\\ascii\\ttmy.txt");
	PrintFile(8, 28, "assets\\ascii\\thphuc.txt");

	PrintFile(92, 34, "assets\\ascii\\presstogoback.txt");
	DrawKeyCap(110, 31, "B");
}

void DrawLoadGameScreen() {
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	//GoToXY(10, 12);
	PrintColorFile_Ver2(65,11,"assets\\ascii\\loadbutton.txt", Black, LightRed);
	PrintColorFile_Ver2(65, 11, "assets\\ascii\\fixbutton.txt", DefaultBgColor, Black);
	PrintColorFile_Ver2(65, 11, "assets\\ascii\\shadowbutton.txt", Red, Black);
	PrintColorFile_Ver2(65, 11, "assets\\ascii\\fix2button.txt", LightRed, Red);
	GoToXY(55, 16);
	for (int i = 0; i < save_entries.size(); ++i) {
		GoToXY(save_entries[i].st.x, save_entries[i].st.y);
		cout << i+1 << ". ";
		GoToXY(save_entries[i].st.x + 5, save_entries[i].st.y);
		cout << save_entries[i].text_value;
	}

	PrintFile(92, 34, "assets\\ascii\\presstogoback.txt");
	DrawKeyCap(110, 31, "B");
}

void DrawSettingsScreen() {
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	PrintFile(8, 13, "assets\\ascii\\presstoplaysound.txt");
	PrintFile(8, 20, "assets\\ascii\\presstoplaymusic.txt");
	PrintFile(123, 12, "assets\\ascii\\sounds.txt");
	PrintFile(122, 18, "assets\\ascii\\music.txt");
	DrawKeyCap(25, 10, "N");
	DrawKeyCap(25, 17, "M");
	FillAreaColor(171, 22, 174, 26, Green);
	FillAreaColor(171, 27, 174, 31, Blue);
	FillAreaColor(171, 32, 174, 36, Black);
	GoToXY(165, 10); cout << "100%__";
	GoToXY(166, 16); cout << "80%__";
	GoToXY(166, 21); cout << "60%__";
	GoToXY(166, 26); cout << "40%__";
	GoToXY(166, 31); cout << "20%__";
	GoToXY(167, 36); cout << "0%__";

	if (SOUND == 1)	PrintFile(130, 12, "assets\\ascii\\soundon.txt");
	for (int j = 0; j < 4; ++j) {
		DrawSettingsButton(color_button[j], 0);
	}
	PrintFile(92, 34, "assets\\ascii\\presstogoback.txt");
	DrawKeyCap(110, 31, "B");
}

void DrawGuideScreen() {
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	PrintFile(19, 11, "assets\\ascii\\navigation.txt");
	PrintFile(108, 11, "assets\\ascii\\howtoplay.txt");
	DrawKeyCap(30, 16, "W");
	DrawKeyCap(15, 23, "A");
	DrawKeyCap(30, 23, "S");
	DrawKeyCap(45, 23, "D");
	GoToXY(93, 15);
	cout << "Navigate the snake to eat food \xfe (and big food after each level) and gain points";
	GoToXY(93, 17);
	cout << "For each piece of food eaten, you will gain +10 points, +1 power";
	GoToXY(93, 19);
	cout << "Power is used to shoot poison and destroy obstacles";
	GoToXY(93, 21);
	cout << "Press L to shoot poison";
	GoToXY(93, 23);
	cout << "After eating enough amount of food, move to next levx`el by going through the gate";
	GoToXY(93, 25);
	cout << "You will lose if your snake hit the board and obstacles, or be shot by bullets";
	GoToXY(93, 27);
	cout << "You can save game when you play";
	GoToXY(93, 29);
	cout << "You can enter your name to save results to leaderboard when you lose";
	PrintFile(92, 34, "assets\\ascii\\presstogoback.txt");
	DrawKeyCap(110, 31, "B");
}

void DrawLeaderBoardScreen() {
	NUMBER_OF_PLAYERS = LeaderBoard(Player);
	ClearScreen(4, 10, 4 + WIDTH_CONSOLE - 3 * 2 - 3, 10 + HEIGHT_CONSOLE - 9 - 1 - 3);
	//FillAreaColor(11,11, 56, 18+NUMBER_OF_PLAYERS, Red);
	PrintColorFile_Ver2(13, 12,"assets\\ascii\\leaderboard1.txt" , Black, LightGreen);
	PrintColorFile_Ver2(13, 12, "assets\\ascii\\leaderboard2.txt", DefaultBgColor, Black);
	PrintColorFile_Ver2(13, 12, "assets\\ascii\\leaderboard3.txt", Green, Black);
	PrintColorFile_Ver2(13, 12, "assets\\ascii\\leaderboard4.txt", LightGreen, Green);
	//SetConsoleColor(Yellow, Red);
	//PrintFile(13, 12, "assets\\ascii\\leaderboard.txt");
	//SetConsoleColor(DefaultTextColor, DefaultBgColor);
	PrintCup(82, 12);

	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	GoToXY(15, 18);
	//SetConsoleColor(DefaultTextColor, Red);
	cout << "USERNAME     SCORE     TIME PLAYED";

	for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
		GoToXY(15, 19+i + 1);
		cout << Player[i].name; 
		GoToXY(28,19+ i + 1);
		cout << Player[i].SCORE;
		GoToXY(40, 19 + i + 1);
		cout << Player[i].TIME;

	}

	

	PrintFile(92, 34, "assets\\ascii\\presstogoback.txt");
	DrawKeyCap(110, 31, "B");
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

void DrawSettingsButton(DECOR_BUTTON a, int mode) {
	char s[100];
	strcpy(s, a.file_path.c_str());
	if (mode == 0) {//normal
		PrintColorFile_Ver2(a.st.x, a.st.y, s, Black, LightRed);
		PrintColorFile_Ver2(a.st.x, a.st.y, "assets\\ascii\\fixsettingbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(a.st.x, a.st.y, "assets\\ascii\\shadowsettingbutton.txt", Red, Black);
		PrintColorFile_Ver2(a.st.x, a.st.y, "assets\\ascii\\fix2settingbutton.txt", LightRed, Red);
	}
	else {//active
		PrintColorFile_Ver2(a.st.x, a.st.y, s, Black, LightYellow);
		PrintColorFile_Ver2(a.st.x, a.st.y, "assets\\ascii\\fixsettingbutton.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(a.st.x, a.st.y, "assets\\ascii\\shadowsettingbutton.txt", Yellow, Black);
		PrintColorFile_Ver2(a.st.x, a.st.y, "assets\\ascii\\fix2settingbutton.txt", LightYellow, Yellow);
	}
}

void DrawKeyCap(int x, int y, const char *c) {

	PrintColorFile_Ver2(x, y, "assets\\ascii\\keycap1.txt", LightPurple, DefaultBgColor);
	PrintColorFile_Ver2(x, y, "assets\\ascii\\keycap2.txt", Red, LightPurple);
	PrintColorFile_Ver2(x, y, "assets\\ascii\\keycap3.txt", Purple, Red);
	PrintColorFile_Ver2(x, y, "assets\\ascii\\keycap4.txt", DefaultBgColor, LightPurple);
	PrintColorFile_Ver2(x, y, "assets\\ascii\\fix1keycap.txt", DefaultBgColor, Red);
	PrintColorFile_Ver2(x, y, "assets\\ascii\\fix2keycap.txt", Purple, DefaultBgColor);

	char path[1000] = {};
	strcat(path, "assets\\ascii\\");
	strcat(path, c);
	strcat(path, ".txt");

	PrintColorFile_Ver2(x, y, path, White, LightPurple);
}

void DrawOcToPus(int x, int y) {
	//int x = 100, y = 15;

	if (octopus_time == 3) {
		//pic1
		FillAreaColor(x - 3, y - 2, x + 12, y + 11, DefaultBgColor);
		PrintColorFile_Ver2(x, y, "assets\\ascii\\octopus3.txt", Black, LightPurple);
		PrintColorFile_Ver2(x, y, "assets\\ascii\\fixotp3.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y, "assets\\ascii\\eyesotp.txt", White, Black);
		SetConsoleColor(Red, DefaultBgColor);
		GoToXY(x + 2, y + 10);
		if (HP_OF_BOSS == 0) cout << "[\xFA\xFA\xFA\xFA\xFA\xFA]";
		else if (HP_OF_BOSS == 1) cout << "[\xFE\xFE\xFA\xFA\xFA\xFA]";
		else if (HP_OF_BOSS == 2) cout << "[\xFE\xFE\xFE\xFE\xFA\xFA]";
		else if (HP_OF_BOSS == 3) cout << "[\xFE\xFE\xFE\xFE\xFE\xFE]";
		SetConsoleColor(DefaultTextColor, DefaultBgColor);

	}
	else if (octopus_time == 4) {
		//pic2
		FillAreaColor(x - 2, y -2, x + 12, y + 11, DefaultBgColor);
		PrintColorFile_Ver2(x, y +1, "assets\\ascii\\octopus1.txt", Black, LightPurple);
		PrintColorFile_Ver2(x, y +1, "assets\\ascii\\fixotp1.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y +1, "assets\\ascii\\eyesotp.txt", White, Black);
		SetConsoleColor(Red, DefaultBgColor);
		GoToXY(x + 2, y + 10);
		if (HP_OF_BOSS == 0) cout << "[\xFA\xFA\xFA\xFA\xFA\xFA]";
		else if (HP_OF_BOSS == 1) cout << "[\xFE\xFE\xFA\xFA\xFA\xFA]";
		else if (HP_OF_BOSS == 2) cout << "[\xFE\xFE\xFE\xFE\xFA\xFA]";
		else if (HP_OF_BOSS == 3) cout << "[\xFE\xFE\xFE\xFE\xFE\xFE]";
		SetConsoleColor(DefaultTextColor, DefaultBgColor);
	}
	else if (octopus_time == 5) {
		//pic3
		FillAreaColor(x - 2, y -2, x + 12, y + 11, DefaultBgColor);
		PrintColorFile_Ver2(x, y +2, "assets\\ascii\\octopus2.txt", Black, LightPurple);
		PrintColorFile_Ver2(x, y +2, "assets\\ascii\\fixotp2.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y +2, "assets\\ascii\\eyesotp.txt", White, Black);
		SetConsoleColor(Red, DefaultBgColor);
		GoToXY(x + 2, y + 9);
		if (HP_OF_BOSS == 0) cout << "[\xFA\xFA\xFA\xFA\xFA\xFA]";
		else if (HP_OF_BOSS == 1) cout << "[\xFE\xFE\xFA\xFA\xFA\xFA]";
		else if (HP_OF_BOSS == 2) cout << "[\xFE\xFE\xFE\xFE\xFA\xFA]";
		else if (HP_OF_BOSS == 3) cout << "[\xFE\xFE\xFE\xFE\xFE\xFE]";
		SetConsoleColor(DefaultTextColor, DefaultBgColor);
	}
	else if (octopus_time == 6) {
		//pic4
		FillAreaColor(x - 2, y - 2, x + 12, y + 11, DefaultBgColor);
		PrintColorFile_Ver2(x, y -1, "assets\\ascii\\octopus4.txt", Black, LightPurple);
		PrintColorFile_Ver2(x, y -1, "assets\\ascii\\fixotp4.txt", DefaultBgColor, Black);
		PrintColorFile_Ver2(x, y -1, "assets\\ascii\\eyesotp.txt", White, Black);
		SetConsoleColor(Red, DefaultBgColor);
		GoToXY(x + 2, y + 9);
		if (HP_OF_BOSS == 0) cout << "[\xFA\xFA\xFA\xFA\xFA\xFA]";
		else if (HP_OF_BOSS == 1) cout << "[\xFE\xFE\xFA\xFA\xFA\xFA]";
		else if (HP_OF_BOSS == 2) cout << "[\xFE\xFE\xFE\xFE\xFA\xFA]";
		else if (HP_OF_BOSS == 3) cout << "[\xFE\xFE\xFE\xFE\xFE\xFE]";
		SetConsoleColor(DefaultTextColor, DefaultBgColor);
		octopus_time = 2;
	}

	octopus_time++;

	
}

void DrawOcToPusHidden1(int x, int y) {
	
	if (octopus_hidden_time == 1) {
		//pic1
		FillAreaColor(x - 1, y - 1, x + 20, y + 5, DefaultBgColor);
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
		FillAreaColor(x - 2, y - 2, x + 20, y + 3, DefaultBgColor);
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
	//octopus_hidden_time++;
	
}

void DrawOcToPusHidden2(int x, int y) {

	if (octopus_hidden_time == 1) {
		//pic1
		FillAreaColor(x - 1, y - 1, x + 20, y + 3, DefaultBgColor);
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
		FillAreaColor(x - 2, y - 2, x + 20, y + 3, DefaultBgColor);
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