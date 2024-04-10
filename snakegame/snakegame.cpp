//Snake game 23CLC01

#include <iostream>
#include "snakegame.h"

//Global variables
POINT obstacles[1000];
POINT gate[WIDTH_GATE * HEIGHT_GATE - 1];
POINT big_food[BIG_FOOD_SIZE][BIG_FOOD_SIZE];
POINT snake[MAX_SIZE_SNAKE];
POINT board[MAX_BOARD_SIZE];
POINT food[50];
POINT bullet_up,bullet_down,bullet1_to_left, bullet2_to_left, bullet3_to_left;
POINT spray;
POINT WIN_POINT;
POINT TELE_POINT_1, TELE_POINT_2;
POINT MINI_Snake;
PLAYER Player[100];
DECOR_BUTTON main_button[6];
BUTTON sound_button[2];
DECOR_BUTTON color_button[4];
vector<SAVE_ENTRY> save_entries;

mutex mtx;
condition_variable cvThread;
condition_variable cvMain;
atomic<bool> threadPaused(false);

const char* MSSV = "23127106231274582312723123127332";
int NUMBER_OF_OBSTACLES;
int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is one direction my snake cannot move to)
int MOVING;//used to determine the direction my snake moves (At a moment, there  are three directions my snake can move)
int SPEED;// Standing for level, the higher the level, the quicker the speed
int HEIGHT_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
int FOOD_INDEX; // current food-index
int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size may be 10
int STATE; // State of snake: dead or alive
int PAUSE = 0;
int SCREEN = 2;
//SCREEN 1: PLAY
//SCREEN 2: MAIN MENU
//SCREEN 3: ABOUT
//SCREEN 4: SETTINGS
//SCREEN 5: LOAD GAME
//SCREEN 6: LEADERBOARD
//SCREEN 7: GUIDE
int MENU_OPTION = 0; //current option, change with W and S key
int LOADGAME_OPTION = 0;
int SOUND_OPTION = 0;
int COLOR_OPTION = 0;
int SIZE_BOARD;
int TIME;
int SCORE;
int OLD_SIZE_SNAKE;
bool CHECK_SNAKE;
int LEVEL;
int SOUND = 1;
int MUSIC = 1;
int VOLUME = 60;
bool Flag_PoisonSpray, Spraying, Flag_emotions;
int previousAction;//1 is move right, 2 is move left, 3 is move up, 4 is move down
int previousAction_tmp;
int BLINKING_MAP;
int TEXTINCONSOLE; //1 if text is in console (game over, ...)
int DefaultTextColor = Black;
int DefaultBgColor = 7;
int DefaultStatusColor = LightRed;
int DefaultStatusTextColor = BrightWhite;
int SnakeColor = Red;
int IDColor = White;

int NUMBER_OF_PLAYERS;
int emotionstime;
int PowerScore;
int skillState = 0;//0 is lock, 1 is unlock, eat big food to unlock
int minisnake = 1;
int MINI_SNAKE_COLOR;
int octopus_time = 0;
int octopus_hidden_time = 0;
int HP_OF_BOSS = 3;
int MAX_SIZE_FOOD = 3;
using namespace std;

int main()
{
    
    CONSOLE_SCREEN_BUFFER_INFOEX info;
    info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfoEx(hConsole, &info);

   
    //info.ColorTable[Red] = RGB(26, 16, 8);
    //info.ColorTable[3] = RGB(135, 206, 235);

    //info.ColorTable[15] = RGB(25, 25, 25);

    SetConsoleScreenBufferInfoEx(hConsole, &info);

    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    SetCursor(0, 0); //No cursor
    SetConsoleColor(DefaultTextColor, DefaultBgColor);
    PlayMusic("assets\\sounds\\intro2", "intro");

    //playSound("assets\\sounds\\intro");
    FixConsoleWindow();
    ResetData();
    //Flag_emotions = true;
    emotionstime = 5;
    ///Initiate buttons
    InitMainButtons();
    InitColorButtons();

    //First draw menu
    DrawMenu();
    ToggleActiveStateDecorButton(main_button[MENU_OPTION]);

    //State when the game has not been started
    STATE = 0;
   
    thread t1(ThreadFunc);

    HANDLE handle_t1 = t1.native_handle();

    char temp;
    while (1) {
        //SCREEN: PLAY
        
        if (SCREEN == 1) {
            temp = toupper(_getch());
            if (temp == char(-32)) {
                temp = toupper(_getch()); continue;
            }
            if (STATE == 1) {
                if (PAUSE && temp == 'M') {
                    PAUSE = 0;
                    threadPaused = false;
                    cvThread.notify_one();
                    STATE = 0;
                    StopMusic("map2");
                    ResumeMusic("intro");
                    SCREEN = 2; //SCREEN: MAIN MENU
                    DrawMenu();
                    ToggleActiveStateDecorButton(main_button[MENU_OPTION]);
                }
                if (PAUSE && temp == 'L') {
                    string fileName;
                    
                    //while to handle valid input file name (<= 15 chars)
                    while (1) {
                        GoToXY(18, 30);
                        cout << "File name to save (without extension): ";
                        GoToXY(18, 31);
                        for (int i = 0; i < fileName.length(); ++i) cout << " "; //clear input buffer
                        GoToXY(18, 31); 
                        cin >> fileName;
                        if (fileName.length() <= 15) break; else {
                            GoToXY(18, 32);
                            cout << "File name should be less than 15 characters, try again.";
                        }
                    }

                    fileName = "./data/" + fileName + ".txt";
                    SaveGame(fileName);
                    GoToXY(18, 32);
                    cout << "File save successful, press any key to continue playing";
                    continue;
                }
                if (!PAUSE && temp == 'P') {
                    Pause();
                }
                else if (temp == 27) {
                    //ResumeThread(handle_t1);
                    STATE = 2;
                    threadPaused = false;
                    cvThread.notify_one();
                    t1.join();
                    return 0;
                }
                else if (PAUSE == 1) {
                    PAUSE = 0;
                    ClearScreen(board[0].x + 1, board[0].y + 1, board[0].x + WIDTH_BOARD - 2, board[0].y + HEIGHT_BOARD - 2);
                    PostPauseDraw();
                    threadPaused = false;
                    cvThread.notify_one();
                    //ResumeThread(handle_t1);
                }
                else  {
                    if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S' || temp == 'L')) {
                        if (temp == 'D') CHAR_LOCK = 'A';
                        else if (temp == 'W') CHAR_LOCK = 'S';
                        else if (temp == 'S') CHAR_LOCK = 'W';
                        else if (temp == 'A') CHAR_LOCK = 'D';
                        if (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S') MOVING = temp;
                        if (temp == 'L' && !Spraying) {
                            Flag_PoisonSpray = true;
                        }
                    }
                }
            }
            else {
                if ( !BLINKING_MAP && temp == 'Y') StartGame();
                if (temp == 27) {
                    //ExitGame(handle_t1);
                    STATE = 2;
                    t1.join();
                    return 0;
                }
                if (!BLINKING_MAP && temp == 'O')
                {
                   
                    string username;

                    //while to handle valid input user name (<= 15 chars)
                    while (1) {
                        GoToXY(18, 35);
                        cout << "Username to save high score: ";
                        GoToXY(18, 36);
                        for (int i = 0; i < username.length(); ++i) cout << " "; //clear input buffer
                        GoToXY(18, 36);
                        cin >> username;
                        if (username.length() <= 15) break; else {
                            GoToXY(18, 37);
                            cout << "Username should be less than 15 characters, try again.";
                        }
                    }

                    ofstream output;
                    output.open("highscore.txt",ios::app);
                    output << username << ',' << TIME << ',' << SCORE << '\n';
                    GoToXY(18, 36);
                    cout << "High score saved! Press M to go back to menu, Y to play again";
                    continue;

                }
                if (!BLINKING_MAP && temp == 'M') {
                    StopMusic("map2");
                    ResumeMusic("intro");
                    SCREEN = 2; //SCREEN: MAIN MENU
                    DrawMenu();
                    ToggleActiveStateDecorButton(main_button[MENU_OPTION]);
                }
            }
        }

        //SCREEN: MAIN MENU
        if (SCREEN == 2) {
            //Mini snake moving
            
            //PrintColorFile_Ver2(30, 20, "assets\\ascii\\minisnake2.txt", Red, DefaultBgColor);
            temp = toupper(_getch());
            if (temp == char(-32)) {
                temp = toupper(_getch()); continue;
            }

            if (temp == 'G') {
                SCREEN = 7;
                DrawGuideScreen();
            }

            if (temp == 'W') {
                PlaySoundEffect("assets\\sounds\\button");
                ToggleNormalStateDecorButton(main_button[MENU_OPTION]);
                MENU_OPTION = (MENU_OPTION - 1 + 6) % 6; // 6 options in total
                ToggleActiveStateDecorButton(main_button[MENU_OPTION]);
            }
            if (temp == 'S') {
                PlaySoundEffect("assets\\sounds\\button");
                ToggleNormalStateDecorButton(main_button[MENU_OPTION]);
                MENU_OPTION = (MENU_OPTION + 1) % 6; 
                ToggleActiveStateDecorButton(main_button[MENU_OPTION]);
            }

            if (temp == 'A') {
                PlaySoundEffect("assets\\sounds\\button");
                ToggleNormalStateDecorButton(main_button[MENU_OPTION]);
                MENU_OPTION = (MENU_OPTION - 3 + 6) % 6; // 6 options in total
                ToggleActiveStateDecorButton(main_button[MENU_OPTION]);
            }

            if (temp == 'D') {
                PlaySoundEffect("assets\\sounds\\button");
                ToggleNormalStateDecorButton(main_button[MENU_OPTION]);
                MENU_OPTION = (MENU_OPTION + 3 + 6) % 6; // 6 options in total
                ToggleActiveStateDecorButton(main_button[MENU_OPTION]);
            }

            //temp == 13 -> Enter key
            if (temp == 'N' || (temp == 13 && MENU_OPTION == 0)) {
                SCREEN = 1; //SCREEN: PLAY
                StartGame();
            }
            if (temp == 'Q' || (temp == 13 && MENU_OPTION == 5)) {
                STATE = 2; //used to break ThreadFunc
                t1.join();
                return 0;
            }
            if (temp == 13 && MENU_OPTION == 3) {
                SCREEN = 3;
                DrawAboutScreen();
             //   playSound("assets\\sounds\\startGame");

            }
            if (temp == 13 && MENU_OPTION == 2) {
                SCREEN = 4;
                DrawSettingsScreen();
            }
            if (temp == 13 && MENU_OPTION == 1) {
                LoadSaveEntries(); //prepare save entries data
                SCREEN = 5;
                DrawLoadGameScreen();
            }
            if (temp == 13 && MENU_OPTION == 4) {
                SCREEN = 6;
                DrawLeaderBoardScreen();
            }
        }

        //SCREEN: LOAD GAME
        if (SCREEN == 5) { 

            ToggleActiveStateSaveEntry(save_entries[LOADGAME_OPTION], LOADGAME_OPTION);

            temp = toupper(_getch());

            if (temp == char(-32)) {
                temp = toupper(_getch()); continue;
            }

            LoadSaveEntries(); //prepare save entries data
            int num_se = save_entries.size();

            if (temp == 'W') {
                ToggleNormalStateSaveEntry(save_entries[LOADGAME_OPTION], LOADGAME_OPTION);
                LOADGAME_OPTION = (LOADGAME_OPTION - 1 + num_se) % num_se; // num_se options in total
                ToggleActiveStateSaveEntry(save_entries[LOADGAME_OPTION], LOADGAME_OPTION);
            }
            if (temp == 'S') {
                ToggleNormalStateSaveEntry(save_entries[LOADGAME_OPTION], LOADGAME_OPTION);
                LOADGAME_OPTION = (LOADGAME_OPTION + 1) % num_se;
                ToggleActiveStateSaveEntry(save_entries[LOADGAME_OPTION], LOADGAME_OPTION);
            }
            //temp == 13 -> Enter key
            if (temp == 13) {
                string fileName;
                fileName = "./data/" + save_entries[LOADGAME_OPTION].text_value;
                SCREEN = 1;
                LoadGame(fileName);
            } 

            //Back
            if (temp == 'B') {
                PlaySoundEffect("assets\\sounds\\button");
                SCREEN = 2;
                DrawMenu();
                ToggleActiveStateDecorButton(main_button[MENU_OPTION]);
            }

        }

        if (SCREEN == 4) {//Screen: Settings
            //int MINI_SNAKE_COLOR;
           
            
            DrawMiniSnake();
            DrawSettingsButton(color_button[COLOR_OPTION], 1);
            temp = toupper(_getch());

            if (temp == char(-32)) {
                temp = toupper(_getch()); continue;
            }

            //Options for sounds
            if (temp == 'W') {
                if (VOLUME < 100) {
                    VOLUME += 20;
                    SetVolume_Pt2(VOLUME);
                    if (VOLUME == 100) FillAreaColor(171, 11, 174, 16, Red);
                    if (VOLUME == 80) FillAreaColor(171, 17, 174, 21, Yellow);
                    if (VOLUME == 60) FillAreaColor(171, 22, 174, 26, Green);
                    if (VOLUME == 40) FillAreaColor(171, 27, 174, 31, Blue);
                    if (VOLUME == 20) FillAreaColor(171, 32, 174, 36, Black);
                }
            }
            if (temp == 'S') {
                if (VOLUME > 0) {
                    VOLUME -= 20;
                    SetVolume_Pt2(VOLUME);
                    if (VOLUME == 80) FillAreaColor(171, 11, 174, 16, DefaultBgColor);
                    if (VOLUME == 60) FillAreaColor(171, 17, 174, 21, DefaultBgColor);
                    if (VOLUME == 40) FillAreaColor(171, 22, 174, 26, DefaultBgColor);
                    if (VOLUME == 20) FillAreaColor(171, 27, 174, 31, DefaultBgColor);
                    if (VOLUME == 0) FillAreaColor(171, 32, 174, 36, DefaultBgColor);
                }
            }

            ////Options for snake's colors
            if (temp == 'A') {
                PlaySoundEffect("assets\\sounds\\button");
                DrawSettingsButton(color_button[COLOR_OPTION], 0);
                COLOR_OPTION = (COLOR_OPTION - 1 + 4) % 4;
                DrawSettingsButton(color_button[COLOR_OPTION], 1);
            }
            if (temp == 'D') {
                PlaySoundEffect("assets\\sounds\\button");
                DrawSettingsButton(color_button[COLOR_OPTION], 0);
                COLOR_OPTION = (COLOR_OPTION + 1) % 4;
                DrawSettingsButton(color_button[COLOR_OPTION], 1);
            }

            //Turn on/off sounds
            if (temp == 'N') {
                SOUND = (SOUND - 1 + 2) % 2;
                if (SOUND == 1) {
                    PlaySoundEffect("assets\\sounds\\button");
                    PrintFile(130, 12, "assets\\ascii\\soundon.txt");
                }
                else PrintFile(130, 12, "assets\\ascii\\soundoff.txt");
            }
            //Turn on/off music
            if (temp == 'M') {
                PlaySoundEffect("assets\\sounds\\button");
                if (MUSIC == 1) {
                    MUSIC = 0;
                    PrintFile(122, 18, "assets\\ascii\\musicoff.txt");
                    PauseMusic("intro");
                }
                else {
                    MUSIC = 1;
                    PrintFile(122, 18, "assets\\ascii\\music.txt");
                    ResumeMusic("intro");
                }
            }
            if (temp == 13) {
                if (COLOR_OPTION == 0) ChangeSnakeColor(Red, White);
                else if (COLOR_OPTION == 1) ChangeSnakeColor(Blue, White);
                else if (COLOR_OPTION == 2) ChangeSnakeColor(Green, Black);
                else if (COLOR_OPTION == 3) ChangeSnakeColor(Yellow, Black);
            }

            if (temp == 'B') {
                PlaySoundEffect("assets\\sounds\\button");
                SCREEN = 2;
                DrawMenu();
                ToggleActiveStateDecorButton(main_button[MENU_OPTION]);
            }
        }

        //SCREEN: ABOUT
        if (SCREEN == 3) {

            temp = toupper(_getch());

            if (temp == char(-32)) {
                temp = toupper(_getch()); continue;
            }
            
            //Back
            if (temp == 'B') {
                SCREEN = 2;
                DrawMenu();
                ToggleActiveStateDecorButton(main_button[MENU_OPTION]);
            }
        }

        //SCREEN: LEADERBOARD
        if (SCREEN == 6) {

            temp = toupper(_getch());

            if (temp == char(-32)) {
                temp = toupper(_getch()); continue;
            }

            //Back
            if (temp == 'B') {
                PlaySoundEffect("assets\\sounds\\button");
                SCREEN = 2;
                DrawMenu();
                ToggleActiveStateDecorButton(main_button[MENU_OPTION]);
            }
        }

        //SCREEN: GUIDE
        if (SCREEN == 7) {

            temp = toupper(_getch());

            if (temp == char(-32)) {
                temp = toupper(_getch()); continue;
            }

            //Back
            if (temp == 'B') {
                PlaySoundEffect("assets\\sounds\\button");
                SCREEN = 2;
                DrawMenu();
                ToggleActiveStateDecorButton(main_button[MENU_OPTION]);
            }
        }

    }


    return 0;
}