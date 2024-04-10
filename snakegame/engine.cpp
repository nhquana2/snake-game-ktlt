#include "snakegame.h"
#include <iostream>

using namespace std;

//the function 'PlaySound' in Windows API requires 'const wchar_t*' (pointer to a wide string)
void PlaySoundEffect(const string& soundFile) {
	if (SOUND == 1) {
		wstring wideSoundFile(soundFile.begin(), soundFile.end()); //convert regular string to wide string
		PlaySound(wideSoundFile.c_str(), NULL, SND_FILENAME | SND_ASYNC); //convert string to wchar_t*
	}
	else {
		PlaySound(NULL, NULL, 0);
	}
}

/*Standard: 
	mciSendString(L"open check.mp3 type mpegvideo alias music", nullptr, 0, nullptr);
    mciSendString(L"play music", NULL, 0, NULL);
*/

void PlayMusic(const string& musicFile, const string& alias) {
	if (MUSIC == 1) {
		wstring wSoundFile(musicFile.begin(), musicFile.end());
		wstring wAlias(alias.begin(), alias.end());

		wstring command = L"open " + wSoundFile + L".mp3 type mpegvideo alias " + wAlias;
		mciSendString(command.c_str(), NULL, 0, NULL);

		wstring playCommand = L"play " + wAlias + L" repeat";
		mciSendString(playCommand.c_str(), NULL, 0, NULL);
	}
}

void StopMusic(const string& alias) {
	wstring wAlias(alias.begin(), alias.end());

	wstring command = L"stop " + wAlias;
	mciSendString(command.c_str(), NULL, 0, NULL);

	wstring closeCommand = L"close " + wAlias;
	mciSendString(closeCommand.c_str(), NULL, 0, NULL);
}

void PauseMusic(const string& alias) {
	wstring wAlias(alias.begin(), alias.end());

	wstring command = L"pause " + wAlias;
	mciSendString(command.c_str(), NULL, 0, NULL);
}

void ResumeMusic(const string& alias) {
	wstring wAlias(alias.begin(), alias.end());

	wstring command = L"play " + wAlias + L" repeat";
	mciSendString(command.c_str(), NULL, 0, NULL);
}
 
void SetVolume(DWORD volume)
{
	DWORD leftVolume = volume & 0xFFFF;
	DWORD rightVolume = (volume & 0xFFFF) << 16;
	waveOutSetVolume(0, leftVolume | rightVolume);
}

void SetVolume_Pt2(int volume) {
	if (volume == 0) SetVolume(0x0000);
	else if (volume == 20) SetVolume(0x3333);
	else if (volume == 40) SetVolume(0x6666);
	else if (volume == 60) SetVolume(0x9999);
	else if (volume == 80) SetVolume(0xCCCC);
	else if (volume == 100) SetVolume(0xFFFF);
}


int RandomInRange(int a, int b) {
	return a + rand() % (b - a + 1);
}

void BoardInit(int x, int y, int width, int height) {
	int pos = 0;
	board[pos] = { x, y };
	for (int i = 0; i < width; ++i) {
		board[pos] = { x + i, y };
		++pos;
	}
	for (int i = 0; i < width; ++i) {
		board[pos] = { x + i, y + height - 1 };
		++pos;
	}
	for (int i = y + 1; i < y + height - 1; ++i) {
		board[pos] = { x , i }; ++pos;
		board[pos] = { x + width - 1, i };


		++pos;
	}
	SIZE_BOARD = pos;
}
bool IsValidFood(int x, int y) {
	for (int i = 0; i < SIZE_SNAKE; ++i) {
		if (snake[i].x == x && snake[i].y == y) return false;
	}
	for (int i = 0; i < NUMBER_OF_OBSTACLES; i++) {
		if ((obstacles[i].x == x && obstacles[i].y == y) || (obstacles[i].x + 1 == x && obstacles[i].y == y))//check if the food is near the obstacles
			return false;
	}
	/*for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (x == big_food[i][j].x && y == big_food[i][j].y) return false;
		}
	}*/
	return true;
}
void GenerateFood() {
	int x, y;
	srand(time(NULL));
	for (int i = 0; i < MAX_SIZE_FOOD; ++i) {
		if (LEVEL == 3) {
			do {
				x = RandomInRange(board[0].x + 1, board[0].x + WIDTH_BOARD / 2 - 2);
				y = RandomInRange(board[0].y + 1, board[0].y + HEIGHT_BOARD - 2);
			} while (!IsValidFood(x, y));
			food[i] = { x , y };
		}
		else {
			do {
				x = RandomInRange(board[0].x + 1, board[0].x + WIDTH_BOARD - 2);
				y = RandomInRange(board[0].y + 1, board[0].y + HEIGHT_BOARD - 2);
			} while (!IsValidFood(x, y));
			food[i] = { x , y };
		}
	}
}
void DeleteBigFood(int x, int y) {
	GoToXY(x, y);
	for (int i = 0; i < BIG_FOOD_SIZE; i++) {
		for (int j = 0; j < BIG_FOOD_SIZE; j++) {
			cout << " ";
			big_food[i][j] = { 0, HEIGHT_CONSOLE + 2 };
		}
		GoToXY(x, y + i + 1);
	}
}
bool CheckBigFood(int x, int y) {//check if the snake touches the big food
	for (int i = 0; i < BIG_FOOD_SIZE; i++) {
		for (int j = 0; j < BIG_FOOD_SIZE; j++) {
			//cout << " ";
			if (x == big_food[i][j].x && y == big_food[i][j].y) {
				//SIZE_SNAKE+=3;//
				//FOOD_INDEX++;
				//skillState = 1;
				return true;
			}
		}
		//GoToXY(x, y + i + 1);
		//break;
	}
	return false;
}

bool CheckValidBigFood() {
	for (int i = 0; i < BIG_FOOD_SIZE; i++) {
		for (int j = 0; j < BIG_FOOD_SIZE; j++) {
			if (!IsValidFood(big_food[i][j].x, big_food[i][j].y))
			{
				return false;
			}
		}
	}
	return true;
}
void GenerateBigFood() {
	int x, y;
	do {
		do {
			x = RandomInRange(board[0].x + 1, board[0].x + WIDTH_BOARD - 2 - BIG_FOOD_SIZE);
			y = RandomInRange(board[0].y + 1, board[0].y + HEIGHT_BOARD - 2 - BIG_FOOD_SIZE);
		} while (!IsValidFood(x, y));
		for (int i = 0; i < BIG_FOOD_SIZE; i++) {
			for (int j = 0; j < BIG_FOOD_SIZE; j++) {
				big_food[i][j] = { x + i, y + j };
			}
		}
	} while (!CheckValidBigFood());
}
bool CheckValidGate(int size) {
	for (int i = 0; i < size; i++) {
		if (!IsValidFood(gate[i].x, gate[i].y)) {
			return false;
		}
	}
	return true;
}



//Create gate[] array, use to store coordinates 
void InitGate() {//return size of gate
	int x, y;
	//pos: number of pixels in gate[]
	int pos = 0;
	while (1) {
		pos = 0;
		x = RandomInRange(board[0].x + 2, board[0].x + WIDTH_BOARD - 1 - WIDTH_GATE - 1); //random coordinates such that the gate is inside the playzone
		y = RandomInRange(board[0].y + 2, board[0].y + HEIGHT_BOARD - 1 - HEIGHT_GATE - 1);

		gate[pos] = { x, y };
		pos++;

		gate[pos] = { x + 1, y };
		pos++;

		gate[pos] = { x + 1, y + 1 };
		pos++;

		gate[pos] = { x + 1, y + 2 };
		pos++;

		gate[pos] = { x, y + 2 };
		pos++;

		//check if gate[] generated is valid, if it is valid break while loop (random until it is valid)
		if (CheckValidGate(pos)) {
			break;
		}
	}
	WIN_POINT = { x,y + 1 };
}
void DeleteGate() {
	for (int i = 0; i < WIDTH_GATE * HEIGHT_GATE - 1; i++) {
		GoToXY(gate[i].x, gate[i].y);
		cout << " ";
		gate[i] = { 0,HEIGHT_CONSOLE + 5 };
	}
	WIN_POINT = { 0, 0 }; //Reset win point
}
void RespawnSnake() {
	for (int i = 0; i < SIZE_SNAKE; i++) {
		snake[i] = { 10 + i, 10 };
	}
}
void ResetData() {

	CHAR_LOCK = 'A', MOVING = 'D', SPEED = 10; FOOD_INDEX = 0,
		WIDTH_CONSOLE = 180, HEIGHT_CONSOLE = 40, SIZE_SNAKE = 6; BLINKING_MAP = 1;
	TIME = 0;
	LEVEL = 0;
	SCORE = 0;
	CHECK_SNAKE = false;
	TEXTINCONSOLE = 0;
	DeleteMap();
	RespawnSnake();
	GenerateFood();
	skillState = 0;//0 is lock
	Flag_PoisonSpray = Spraying = false;
	DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
	TELE_POINT_1.x = TELE_POINT_1.y = TELE_POINT_2.x = TELE_POINT_2.y = 0;
	emotionstime = 5;
	PowerScore = 0;
	octopus_hidden_time = 1;
	octopus_time = 3;
	HP_OF_BOSS = 3;
	//con muc o giua
	bullet1_to_left.x = 100;
	bullet1_to_left.y = 22;

	//con muc o tren
	bullet2_to_left.x = 100;
	bullet2_to_left.y = 13;
	//con muc o duoi
	bullet3_to_left.x = 100;
	bullet3_to_left.y = 31;
}

void StartGame() {
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	PauseMusic("intro");
	PlaySoundEffect("assets\\sounds\\startGame");
	//BoardInit(5, 10);
	WIN_POINT.x = 0;
	WIN_POINT.y = 0;
	//set the coordinates of win point to {0,0} so that it lies outside of the board and the snake cannot touch it until the gate is drawed
	system("cls"); //Clear screen
	BoardInit(3, 9, WIDTH_BOARD, HEIGHT_BOARD);
	ResetData(); // Intialize original data
	ColorStatusBoard();
	DrawRectangle_Ver2(board[0].x, board[0].y, WIDTH_BOARD, HEIGHT_BOARD); // Draw board game

	//DrawRectangle(board[0].x + WIDTH_BOARD + board[0].x, board[0].y, WIDTH_CONSOLE - WIDTH_BOARD - 3 * board[0].x, HEIGHT_CONSOLE - board[0].y - (HEIGHT_CONSOLE - board[0].y - HEIGHT_BOARD)); // Draw status board

	//DrawRectangle(board[0].x + WIDTH_BOARD + board[0].x, board[0].y, WIDTH_CONSOLE - WIDTH_BOARD - 3 * board[0].x, HEIGHT_BOARD); // Draw status board

	SetConsoleColor(Black, DefaultStatusColor);
	DrawLineStatusBoard(board[0].x + WIDTH_BOARD + board[0].x, 1, WIDTH_CONSOLE - WIDTH_BOARD - 3 * board[0].x, HEIGHT_BOARD + 8);
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	//int title_width, title_height;
	//GetWidthAndHeightFile("title.txt", title_width, title_height);
	//SetConsoleColor(Green, Black);
	//PrintTextFile((WIDTH_CONSOLE - title_width) / 2, 1, "title.txt");
	//DrawLineStatusBoard(2, 0, 122, 9);
	PrintTitle2File(1, 0, "assets\\ascii\\snakegamenew.txt");
	//PrintTitleShadowFile(5, 2, "assets\\ascii\\snakegamenewshadow.txt");
	//PrintTitleFile(5, 2, "assets\\ascii\\snakegamenew.txt");

	//PrintTitleShadowFixedFile(5, 2, "assets\\ascii\\snakegametitleshadowfixed.txt");
	//PrintTitleShadowFixed_2File(5, 2, "assets\\ascii\\snaketitleshadow.txt");
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	//SetConsoleColor(White, Black);

	PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 12, board[0].y - 7, "assets\\ascii\\level 1.txt", DefaultStatusColor);
	PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 2, board[0].y + 1, "assets\\ascii\\battery.txt", DefaultStatusColor);
	PlayMusic("assets\\sounds\\map2", "map2");
	
	STATE = 1; //Start running Thread
}

void ExitGame(HANDLE t) {
	system("cls");
	TerminateThread(t, 0);//no ok
}

void PauseGame(HANDLE t) {
	PlaySoundEffect("assets\\sounds\\pauseGame");
	SuspendThread(t);
}

void ProcessDead() {
	STATE = 0;
	PrintSnakeStatusTextFile(board[0].x + WIDTH_BOARD + board[0].x + 5, board[0].y + 12, "assets\\ascii\\angrysnake.txt");
	PlaySoundEffect("assets\\sounds\\deathSound");

	BlinkingMap();
	GoToXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2);
	ClearScreen(board[0].x + 1, board[0].y + 1, board[0].x + WIDTH_BOARD - 2, board[0].y + HEIGHT_BOARD - 2);
	TEXTINCONSOLE = 1;
	//PrintSnakeStatusTextFile(board[0].x + WIDTH_BOARD + board[0].x + 5, board[0].y + 13, "assets\\ascii\\angrysnake.txt");
	//FillAreaColor(34, 14, 91, 20,Red);
	SetConsoleColor(Yellow, Red);
	//DrawRectangle(35, 14, 90 - 34, 20 - 13);

	//FillAreaColor(15, 16, 110, 20, Red);
	SetConsoleColor(Yellow, Red);
	//DrawRectangle(45, 14, 70 - 34, 20 - 13);

	PrintTextFile(23, 12, "assets\\ascii\\gameover.txt");
	
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	SetConsoleColor(DefaultTextColor, DefaultBgColor);
	BLINKING_MAP = 0;
	//GoToXY(18, 34);
	//cout << "Dead! Press O to save highscore";
	FillAreaColor(128, 2,175,17, DefaultStatusColor);
	
	PrintColorFile_Ver2(board[0].x + WIDTH_BOARD + board[0].x +4, board[0].y - 5, "assets\\ascii\\deadtext.txt", Red, DefaultStatusColor);
	//SetConsoleColor(Yellow, Black);
	//cout<<"Dead, press Y to continue!";
	//SetConsoleColor(White, Black);
}

void LevelUp() {
	//process when the snake eat enough food and open the gate
	//when the head of the snake hit the win point
	PlaySoundEffect("assets\\sounds\\levelup");
	DeleteGate();
	FOOD_INDEX = 0;
	LEVEL += 1;
	SPEED += 3;

	if (LEVEL == 1){
		NUMBER_OF_OBSTACLES = MapLevel1();
	}
	/*if (LEVEL == 4) {
		//DrawTelePoint(board[0].x, board[0].y + 10, board[0].x + WIDTH_BOARD - 1, board[0].y + 8);
		DeleteMap();//delete old map before switch to next map
		NUMBER_OF_OBSTACLES = FinalMap();
	}*/
	if (LEVEL == 2) {
		DeleteMap();
		NUMBER_OF_OBSTACLES = MapLevel3();

	}
	if (LEVEL == 3) {
		DeleteMap();
		SPEED = 15;
		NUMBER_OF_OBSTACLES = FinalMap();
		MAX_SIZE_FOOD = 20;
		GenerateFood();
		//	DrawTelePoint(board[0].x, board[0].y + 23, board[0].x + WIDTH_BOARD - 1, board[0].y + 5);
		
	}
	/*if (LEVEL == 5) {

		DeleteMap();
		DrawTelePoint(board[0].x, board[0].y + 23, board[0].x + WIDTH_BOARD - 1, board[0].y + 5);
		NUMBER_OF_OBSTACLES = FinalMap();
	}
	if (LEVEL == 6) {
		DeleteMap();
		NUMBER_OF_OBSTACLES = FinalMap();
	}*/
	RespawnSnake();
	//GenerateBigFood();
}
void Eat() {
	PlaySoundEffect("assets\\sounds\\button");
	PrintSnakeStatusTextFile(board[0].x + WIDTH_BOARD + board[0].x + 5, board[0].y + 12, "assets\\ascii\\happysnake.txt");
	emotionstime = 10;
	if (!Spraying) snake[SIZE_SNAKE] = food[FOOD_INDEX];
	else {
		if (spray.x == food[FOOD_INDEX].x && spray.y == food[FOOD_INDEX].y)
			snake[SIZE_SNAKE] = snake[SIZE_SNAKE - 1];
		else snake[SIZE_SNAKE] = food[FOOD_INDEX];
	};
	SCORE += 10;
	if (PowerScore < 3) PowerScore++;
	++SIZE_SNAKE;
	if (FOOD_INDEX == MAX_SIZE_FOOD - 1)//if the player met the requirement of food
	{

		PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 32, board[0].y + 2, "assets\\ascii\\food3.txt", DefaultStatusColor);
		//If gate is not inside board, max number of food spawned -> DrawGate
		if (WIN_POINT.x == 0 && WIN_POINT.y == 0) {
			if (LEVEL >= 1) {
				if (big_food[0][0].x != 0 && big_food[0][0].y != HEIGHT_CONSOLE + 2)
					DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
			}
			InitGate();
			DrawGate();
		}
	}
	else
	{
		FOOD_INDEX++;
		if (FOOD_INDEX == 1) PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 4, board[0].y + 2, "assets\\ascii\\food1.txt", DefaultStatusColor);
		if (FOOD_INDEX == 2) PrintColorFile(board[0].x + WIDTH_BOARD + board[0].x + 17, board[0].y + 2, "assets\\ascii\\food2.txt", DefaultStatusColor);
	}
}
bool Suicide(int x, int y)//return true if the snake touch its body
{
	for (int i = 0; i < SIZE_SNAKE; i++) {
		if (x == snake[i].x && y == snake[i].y)
			return true;
	}
	return false;
}

//Move functions
void MoveRight()
{
	POINT nextpoint = { snake[SIZE_SNAKE - 1].x + 1 , snake[SIZE_SNAKE - 1].y };
	//snake touch deadline in final map
	if (LEVEL == 3) {
		if (nextpoint.x > 80) ProcessDead();
	}
	//Snake touch telepoint in final map
	if (nextpoint.x == TELE_POINT_2.x + 2 && nextpoint.y == TELE_POINT_2.y) {
		if (LEVEL == 3) {
			GoToXY(TELE_POINT_2.x + 1, TELE_POINT_2.y);
			cout << '\xb2';
		}
		snake[SIZE_SNAKE - 1] = TELE_POINT_1;
		nextpoint.x = snake[SIZE_SNAKE - 1].x + 1;
		nextpoint.y = snake[SIZE_SNAKE - 1].y;

	}

	//Snake touch Win point
	if (nextpoint.x == WIN_POINT.x && nextpoint.y == WIN_POINT.y)
	{
		//check if the player ate the big food (big food only be drawn if level up function is called)
		if (!CHECK_SNAKE) OLD_SIZE_SNAKE = SIZE_SNAKE;
		CHECK_SNAKE = true;
	}
	//Snake touch Gate
	if (nextpoint.x == WIN_POINT.x && (nextpoint.y == WIN_POINT.y + 1 || nextpoint.y == WIN_POINT.y - 1))
	{
		ProcessDead();
	}

	//check if the snake touch the big food
	if (CheckBigFood(nextpoint.x, nextpoint.y))
	{
		PlaySoundEffect("assets\\sounds\\bigfood");
		//delete big food, parameters are its coordinates
		DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
		PowerScore = 3;
		SCORE += 100;
	}

	// If snake hit wall or snake suicide
	if (nextpoint.x == WIDTH_BOARD + board[0].x - 1 || Suicide(nextpoint.x, nextpoint.y) || CheckTouchObstacles(nextpoint.x, nextpoint.y))
	{
		ProcessDead();
	}
	else {
		if ((WIN_POINT.x == 0 && WIN_POINT.y == 0) && nextpoint.x == food[FOOD_INDEX].x && nextpoint.y == food[FOOD_INDEX].y) {
			Eat();
		}
		else {
			for (int i = 0; i < SIZE_SNAKE - 1; i++) {
				snake[i].x = snake[i + 1].x;
				snake[i].y = snake[i + 1].y;

			}
			snake[SIZE_SNAKE - 1].x++;
		}
	}
}

void MoveLeft()
{
	POINT nextpoint = { snake[SIZE_SNAKE - 1].x - 1 , snake[SIZE_SNAKE - 1].y };
	//Snake touch telepoint
	if (nextpoint.x == TELE_POINT_1.x - 2 && nextpoint.y == TELE_POINT_1.y) {
		if (LEVEL == 3) {
			GoToXY(TELE_POINT_1.x - 1, TELE_POINT_1.y);
			cout << '\xb2';
		}
		snake[SIZE_SNAKE - 1] = TELE_POINT_2;
		nextpoint.x = snake[SIZE_SNAKE - 1].x - 1;
		nextpoint.y = snake[SIZE_SNAKE - 1].y;
	}
	//Snake Touch Gate
	if (nextpoint.x == WIN_POINT.x + 1 && (nextpoint.y == WIN_POINT.y + 1 || nextpoint.y == WIN_POINT.y - 1 || nextpoint.y == WIN_POINT.y))
	{
		ProcessDead();
	}

	if (CheckBigFood(nextpoint.x, nextpoint.y))
	{
		PlaySoundEffect("assets\\sounds\\bigfood");
		DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
		PowerScore = 3;
		SCORE += 100;
	}

	if (nextpoint.x == board[0].x || Suicide(nextpoint.x, nextpoint.y) || CheckTouchObstacles(nextpoint.x, nextpoint.y))
	{
		ProcessDead();
	}
	else {
		if ((WIN_POINT.x == 0 && WIN_POINT.y == 0) && nextpoint.x == food[FOOD_INDEX].x && nextpoint.y == food[FOOD_INDEX].y) {
			Eat();
		}
		else {
			for (int i = 0; i < SIZE_SNAKE - 1; i++) {
				snake[i].x = snake[i + 1].x;
				snake[i].y = snake[i + 1].y;

			}
			snake[SIZE_SNAKE - 1].x--;
		}
	}
}

void MoveUp()
{
	POINT nextpoint = { snake[SIZE_SNAKE - 1].x , snake[SIZE_SNAKE - 1].y - 1 };
	//Snake touch Gate
	if (nextpoint.y == WIN_POINT.y + 1 && (nextpoint.x == WIN_POINT.x || nextpoint.x == WIN_POINT.x + 1)) {
		ProcessDead();
	}

	if (CheckBigFood(nextpoint.x, nextpoint.y))
	{
		PlaySoundEffect("assets\\sounds\\bigfood");
		DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
		PowerScore = 3;
		SCORE += 100;
	}
	if (nextpoint.y == board[0].y || Suicide(nextpoint.x, nextpoint.y) || CheckTouchObstacles(nextpoint.x, nextpoint.y))
	{
		ProcessDead();
	}
	else {
		if ((WIN_POINT.x == 0 && WIN_POINT.y == 0) && nextpoint.x == food[FOOD_INDEX].x && nextpoint.y == food[FOOD_INDEX].y) {
			Eat();
		}
		else {
			for (int i = 0; i < SIZE_SNAKE - 1; i++) {
				snake[i].x = snake[i + 1].x;
				snake[i].y = snake[i + 1].y;

			}
			snake[SIZE_SNAKE - 1].y--;
		}
	}
}

void MoveDown()
{
	POINT nextpoint = { snake[SIZE_SNAKE - 1].x , snake[SIZE_SNAKE - 1].y + 1 };
	//Snake touch gate
	if (nextpoint.y == WIN_POINT.y - 1 && (snake[SIZE_SNAKE - 1].x == WIN_POINT.x || snake[SIZE_SNAKE - 1].x == WIN_POINT.x + 1)) {
		ProcessDead();
	}

	if (CheckBigFood(nextpoint.x, nextpoint.y))
	{
		PlaySoundEffect("assets\\sounds\\bigfood");
		DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
		PowerScore = 3;
		SCORE += 100;
	}
	if (nextpoint.y == HEIGHT_BOARD + board[0].y - 1 || Suicide(nextpoint.x, nextpoint.y) || CheckTouchObstacles(nextpoint.x, nextpoint.y))
	{
		ProcessDead();
	}
	else {
		if ((WIN_POINT.x == 0 && WIN_POINT.y == 0) && nextpoint.x == food[FOOD_INDEX].x && nextpoint.y == food[FOOD_INDEX].y) {
			Eat();
		}
		else {
			for (int i = 0; i < SIZE_SNAKE - 1; i++) {
				snake[i].x = snake[i + 1].x;
				snake[i].y = snake[i + 1].y;

			}
			snake[SIZE_SNAKE - 1].y++;
		}
	}
}
bool checkTouchBoss(int x, int y) {
	return (x >= 105 && y >= 12 && y <= 15) || (x >= 100 && y >= 19 && y <= 28) || (x >= 105 && y >= 32 && y <= 35);
}
bool checkBullet(int x, int y) {
	return (x == bullet1_to_left.x && y == bullet1_to_left.y) || (x == bullet2_to_left.x && y == bullet2_to_left.y) || (x == bullet3_to_left.x && y == bullet3_to_left.y);
}
void PoisonSpray() {
	GoToXY(spray.x, spray.y);
	cout << " ";
	if (previousAction == 1) {//move right
		spray.x++;
		if (LEVEL == 3 && checkTouchBoss(spray.x, spray.y)) {//win game neu HP == 0
			HP_OF_BOSS--;
			PlaySoundEffect("assets\\sounds\\explosion");
			Spraying = false;

		}
		else if (LEVEL == 3 && checkBullet(spray.x, spray.y)) {
			PlaySoundEffect("assets\\sounds\\explosion");
			Spraying = false;
		}
			
	 
			//check touch obstacles
			for (int i = 0; i < NUMBER_OF_OBSTACLES; ++i)
				if (spray.x == obstacles[i].x && spray.y == obstacles[i].y) {
					obstacles[i].x = obstacles[i].y = 3;
					PlaySoundEffect("assets\\sounds\\explosion");
					Spraying = false;
					break;
				}
			//check touch gate
			for (int i = 0; i < WIDTH_GATE * HEIGHT_GATE - 1; ++i)
				if (spray.x == gate[i].x && spray.y == gate[i].y) {
					spray.x = spray.y = 5;
					PlaySoundEffect("assets\\sounds\\explosion");
					Spraying = false;
					break;
				}
			//check touch tele point
			if (spray.x == TELE_POINT_2.x - 1 && spray.y == TELE_POINT_2.y) {
				spray.x = TELE_POINT_1.x + 1;
				spray.y = TELE_POINT_1.y;
			}
			//check touch big food
			if (CheckBigFood(spray.x, spray.y)) {
				PlaySoundEffect("assets\\sounds\\bigfood");
				DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
				SCORE += 100;
				PowerScore = 3;
				Spraying = false;
			}
			else {
				if ((spray.x == food[FOOD_INDEX].x && spray.y == food[FOOD_INDEX].y)) { //check touch big food
					Eat();
					Spraying = false;
				}
				else if (spray.x == board[0].x + WIDTH_BOARD - 2) {
					PlaySoundEffect("assets\\sounds\\explosion");
					Spraying = false;
				}
			}
		
	}
	else if (previousAction == 2) {//move left
		spray.x--;
		//check touch obstacles
		for (int i = 0; i < NUMBER_OF_OBSTACLES; ++i)
			if (spray.x == obstacles[i].x && spray.y == obstacles[i].y){
				obstacles[i].x = obstacles[i].y = 3;
				PlaySoundEffect("assets\\sounds\\explosion");
				Spraying = false;
				break;
			}
		//check touch gate
		if (Spraying) {
			for (int i = 0; i < WIDTH_GATE * HEIGHT_GATE - 1; ++i)
				if (spray.x == gate[i].x && spray.y == gate[i].y) {
					spray.x = spray.y = 5;
					PlaySoundEffect("assets\\sounds\\explosion");
					Spraying = false;
					break;
				}
		}
		//check touch tele point

		if (spray.x == TELE_POINT_1.x + 1 && spray.y == TELE_POINT_1.y) {
			spray.x = TELE_POINT_2.x - 1;
			spray.y = TELE_POINT_2.y;
		}
		if (spray.x == TELE_POINT_1.x && spray.y == TELE_POINT_1.y) {
			spray = TELE_POINT_2;
		}
		//check touch big food
		if (Spraying) {
			if (CheckBigFood(spray.x, spray.y))
			{
				PlaySoundEffect("assets\\sounds\\bigfood");
				DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
				SCORE += 100;
				PowerScore = 3;
				Spraying = false;
			}
			else {
				if ((spray.x == food[FOOD_INDEX].x && spray.y == food[FOOD_INDEX].y)) { //check touch big food
					Eat();
					Spraying = false;
				}
				else if (spray.x == board[0].x + 1) {
					PlaySoundEffect("assets\\sounds\\explosion");
					Spraying = false;
				}
			}
		}
	}
	else if (previousAction == 3) {//move up
		spray.y--;
		//check touch obstacles
		for (int i = 0; i < NUMBER_OF_OBSTACLES; ++i)
			if (spray.x == obstacles[i].x && spray.y == obstacles[i].y) {
				obstacles[i].x = obstacles[i].y = 3;
				PlaySoundEffect("assets\\sounds\\explosion");
				Spraying = false;
				break;
			}
		//check touch gate
		if (Spraying) {
			for (int i = 0; i < WIDTH_GATE * HEIGHT_GATE - 1; ++i)
				if (spray.x == gate[i].x && spray.y == gate[i].y) {
					spray.x = spray.y = 5;
					PlaySoundEffect("assets\\sounds\\explosion");
					Spraying = false;
					break;
				}
		}
		//check touch big food
		if (CheckBigFood(spray.x, spray.y)){
			//playSound("assets\\sounds\\bigfood");
			DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
			SCORE += 100;
			PowerScore = 3;
			Spraying = false;
		}
		else {
			if ((spray.x == food[FOOD_INDEX].x && spray.y == food[FOOD_INDEX].y)) { //check touch food
				Eat();
				Spraying = false;
			}
			else if (spray.y == board[0].y + 1) {
				PlaySoundEffect("assets\\sounds\\explosion");
				Spraying = false;
			}
		}
	}
	else if (previousAction == 4) {//move down
		spray.y++;
		//check touch obstacles
		for (int i = 0; i < NUMBER_OF_OBSTACLES; ++i)
			if (spray.x == obstacles[i].x && spray.y == obstacles[i].y) {
				obstacles[i].x = obstacles[i].y = 3;
				PlaySoundEffect("assets\\sounds\\explosion");
				Spraying = false;
				break;
			}

		//check touch gate
		if (Spraying) {
			for (int i = 0; i < WIDTH_GATE * HEIGHT_GATE - 1; ++i)
				if (spray.x == gate[i].x && spray.y == gate[i].y) {
					spray.x = spray.y = 5;
					PlaySoundEffect("assets\\sounds\\explosion");
					Spraying = false;
					break;
				}
		}
		//check touch food
		if (CheckBigFood(spray.x, spray.y)){
			PlaySoundEffect("assets\\sounds\\bigfood");
			DeleteBigFood(big_food[0][0].x, big_food[0][0].y);
			SCORE += 100;
			PowerScore = 3;
			Spraying = false;
		}
		else {
			if ((spray.x == food[FOOD_INDEX].x && spray.y == food[FOOD_INDEX].y)) {//check touch food
				Eat();
				Spraying = false;
			}
			else if (spray.y == board[0].y + HEIGHT_BOARD - 2) {
				PlaySoundEffect("assets\\sounds\\explosion");
				Spraying = false;
			}
		}
	}
	GoToXY(spray.x, spray.y);
	if (Spraying)
		cout << "\xFE";
	else cout << " ";
}

void ThreadFunc() {
	while (1) {

		unique_lock<mutex> lock(mtx);
		cvThread.wait(lock, [] { return !threadPaused;  });
		if (STATE == 1) {

			DrawSnakeAndFood(" ");

			switch (MOVING) {
			case 'A':
				MoveLeft();
				break;
			case 'D':
				MoveRight();
				break;
			case 'W':
				MoveUp();
				break;
			case 'S':
				MoveDown();
				break;
			}
			//Snake moving through gate animation
			if (CHECK_SNAKE) {
				if (SnakeGoThroughGate()) {
					//cout << "ok";
					CHECK_SNAKE = false;
					SIZE_SNAKE = OLD_SIZE_SNAKE;
					LevelUp();
					DeleteBigFood(big_food[0][0].x, big_food[0][0].y);

					GenerateBigFood();
					
					DrawBigFood();
					GenerateFood();
				}
			}
			//End snake animation

			if (Flag_PoisonSpray && PowerScore > 0) {
				spray.x = snake[SIZE_SNAKE - 1].x;
				spray.y = snake[SIZE_SNAKE - 1].y;
				if (MOVING == 'A') previousAction = 2;//move left
				else if (MOVING == 'D') previousAction = 1;//move right
				else if (MOVING == 'W') previousAction = 3;//move up
				else if (MOVING == 'S') previousAction = 4;//move down
				Spraying = true;
				PowerScore--;
				PlaySoundEffect("assets\\sounds\\shooting");
				Flag_PoisonSpray = false;
			}
			else Flag_PoisonSpray = false;

			if (Spraying) PoisonSpray();

			/*if (LEVEL == 4) {
				DrawBulletDown();
				DrawBulletUp();
			}*/
			DrawSnakeAndFood(MSSV);
			PrintStatusBoard();



			if (LEVEL == 3) {
				if (STATE != 0) DrawOcToPus(100, 19);
				if (STATE != 0) DrawBulletToLeft(bullet1_to_left);
				if (STATE != 0) DrawBulletToLeft(bullet2_to_left);
				if (STATE != 0) DrawBulletToLeft(bullet3_to_left);

				if (HP_OF_BOSS <= 2) {
					if (STATE != 0) DrawBulletToLeft(bullet1_to_left);
					if (STATE != 0) DrawBulletToLeft(bullet2_to_left);
					if (STATE != 0) DrawBulletToLeft(bullet3_to_left);
				}
				
				if (STATE != 0) DrawOcToPusHidden1(100, 12);
				if (STATE != 0) DrawOcToPusHidden2(100, 32);

			}

			if (HP_OF_BOSS <= 0) {
				ClearScreen(board[0].x + 1, board[0].y + 1, board[0].x + WIDTH_BOARD - 2, board[0].y + HEIGHT_BOARD - 2);
				PrintTextFile(4, 16, "assets\\ascii\\youwin.txt");
				STATE = 0;
			}
			



			Sleep(1000 / SPEED);
			if (STATE != 0 && Spraying) PoisonSpray();
			TIME += 1000 / SPEED;
		}
		if (STATE == 2) {
			break;
		}

		if (threadPaused) {
			cvMain.notify_one();
			continue;
		}

		lock.unlock();
	}
}