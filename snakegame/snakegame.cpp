//Snake game 23CLC01

#include <iostream>
#include "snakegame.h"

//Global variables
POINT obstacles[500];
POINT gate[WIDTH_GATE * HEIGHT_GATE - 1];
POINT big_food[BIG_FOOD_SIZE][BIG_FOOD_SIZE];
POINT snake[40];
POINT board[400];
POINT food[MAX_SIZE_FOOD];
POINT bullet;
POINT spray;
POINT WIN_POINT;
POINT TELE_POINT_1, TELE_POINT_2;

BUTTON main_button[5];

const char* MSSV = "23127106231274582312723123127332";
int NUMBER_OF_OBSTACLES;
int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is one direction my snake cannot move to)
int MOVING;//used to determine the direction my snake moves (At a moment, there  are three directions my snake can move)
int SPEED;// Standing for level, the higher the level, the quicker the speed
int HEIGHT_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
int FOOD_INDEX; // current food-index
int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size may be 10
int STATE; // State of snake: dead or alive
int SCREEN = 2;
//SCREEN 1: PLAY
//SCREEN 2: MAIN MENU
//SCREEN 3: LOAD GAME
//SCREEN 4: SETTINGS
//SCREEN 5: ABOUT
int MENU_OPTION = 0; //current option, change with W and S key
int SIZE_BOARD;
int TIME;
int SCORE;
int OLD_SIZE_SNAKE;
bool CHECK_SNAKE;
int LEVEL;
int SOUND = 1;
bool Flag_PoisonSpray, Spraying;
int previousAction;//1 is move right, 2 is move left, 3 is move up, 4 is move down
int previousAction_tmp;
int BLINKING_MAP;

int DefaultTextColor = Black;
int DefaultBgColor = LightAqua;

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    SetCursor(0, 0); //No cursor
    SetConsoleColor(DefaultTextColor, DefaultBgColor);
    playSound("assets\\sounds\\intro");
    FixConsoleWindow();
    ResetData();
    //First draw menu
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
    main_button[4].text_st = { 86, 29 };
    main_button[4].text_value = "EXIT";

    DrawMenu();
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
                if (temp == 'P') {
                    PauseGame(handle_t1);
                }
                else if (temp == 27) {
                    //ExitGame(handle_t1);
                    STATE = 2;
                    t1.join();
                    return 0;
                }
                else {
                    ResumeThread(handle_t1);
                    if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S' || temp == 'L')) {
                        if (temp == 'D') CHAR_LOCK = 'A';
                        else if (temp == 'W') CHAR_LOCK = 'S';
                        else if (temp == 'S') CHAR_LOCK = 'W';
                        else if (temp == 'A') CHAR_LOCK = 'D';
                        if (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S') MOVING = temp;
                        if (temp == 'L' && !Spraying) {
                            playSound("assets\\sounds\\shooting");
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
                if (temp == 'M') {
                    SCREEN = 2; //SCREEN: MAIN MENU
                    DrawMenu();
                }
            }
        }

        //SCREEN: MAIN MENU
        if (SCREEN == 2) {
            temp = toupper(_getch());

            if (temp == char(-32)) {
                temp = toupper(_getch()); continue;
            }
            if (temp == 'W') {
                ToggleNormalStateButton(main_button[MENU_OPTION]);
                MENU_OPTION = (MENU_OPTION - 1 + 5) % 5; // 5 options in total
                ToggleActiveStateButton(main_button[MENU_OPTION]);
                //DrawMenu();
            }
            if (temp == 'S') {
                ToggleNormalStateButton(main_button[MENU_OPTION]);
                MENU_OPTION = (MENU_OPTION + 1) % 5; // 5 options in total
                ToggleActiveStateButton(main_button[MENU_OPTION]);
                //DrawMenu();
            }
            //temp == 13 -> Enter key
            if (temp == 'N' || (temp == 13 && MENU_OPTION == 0)) {
                SCREEN = 1; //SCREEN: PLAY
                StartGame();
            }
            if (temp == 'Q' || (temp == 13 && MENU_OPTION == 4)) {
                STATE = 2; //break ThreadFunc
                t1.join();
                return 0;
            }
            if (temp == 13 && MENU_OPTION == 3) {
                SCREEN = 3;
                DrawAboutScreen();
            }
        }
        if (SCREEN == 3) {

            temp = toupper(_getch());

            if (temp == char(-32)) {
                temp = toupper(_getch()); continue;
            }
            
            //Back
            if (temp == 'B') {
                SCREEN = 2;
                DrawMenu();
            }
        }
    }


    return 0;
}