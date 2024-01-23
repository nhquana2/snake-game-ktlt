//Snake game 23CLC01

#include <iostream>
#include "snakegame.h"

//Global variables
POINT gate[WIDTH_GATE * HEIGHT_GATE - 1];
POINT big_food[BIG_FOOD_SIZE][BIG_FOOD_SIZE];
POINT snake[40];
POINT board[400];
POINT food[6];
const char* MSSV = "23127106231274582312723123127332";
int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is one direction my snake cannot move to)
int MOVING;//used to determine the direction my snake moves (At a moment, there  are three directions my snake can move)
int SPEED;// Standing for level, the higher the level, the quicker the speed
int HEIGH_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
int FOOD_INDEX; // current food-index
int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size may be 10
int STATE; // State of snake: dead or alive
int SCREEN = 2;
int MENU_OPTION = 0;
int SIZE_BOARD;
int TIME;
POINT WIN_POINT;
int LEVEL;
using namespace std;

int main()
{
    system("color 70");
    FixConsoleWindow();
    ResetData();
    DrawMenu();
    STATE = 0;
    //StartGame();
    //GenerateBigFood();

    thread t1(ThreadFunc);
    HANDLE handle_t1 = t1.native_handle();

    char temp;
    while (1) {
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
                    if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S')) {
                        if (temp == 'D') CHAR_LOCK = 'A';
                        else if (temp == 'W') CHAR_LOCK = 'S';
                        else if (temp == 'S') CHAR_LOCK = 'W';
                        else CHAR_LOCK = 'D';
                        MOVING = temp;
                    }
                }
            }
            else {
                if (temp == 'Y') StartGame();
                if (temp == 27) {
                    //ExitGame(handle_t1);
                    STATE = 2;
                    t1.join();
                    return 0;
                }
                if (temp == 'M') {
                    SCREEN = 2;
                    DrawMenu();
                }
            }
        }
        if (SCREEN == 2) {
            temp = toupper(_getch());

            if (temp == char(-32)) {
                temp = toupper(_getch()); continue;
            }
            if (temp == 'W') {
                MENU_OPTION = (MENU_OPTION - 1 + 5) % 5; // 5 options in total
                DrawMenu();
            }
            if (temp == 'S') {
                MENU_OPTION = (MENU_OPTION + 1) % 5; // 5 options in total
                DrawMenu();
            }
            if (temp == 'N' || (temp == 13 && MENU_OPTION == 0)) {
                SCREEN = 1;
                StartGame();
            }
            if (temp == 'Q' || (temp == 13 && MENU_OPTION == 4)) {
                STATE = 2;
                t1.join();
                return 0;
            }
        }
    }


    return 0;
}