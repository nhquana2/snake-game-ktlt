//Snake game 23CLC01

#include <iostream>
#include "snakegame.h"

//Global variables
POINT snake[40];
POINT board[400];
POINT food[6];
int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is one direction my snake cannot move to)
int MOVING;//used to determine the direction my snake moves (At a moment, there  are three directions my snake can move)
int SPEED;// Standing for level, the higher the level, the quicker the speed
int HEIGH_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
int FOOD_INDEX; // current food-index
int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size may be 10
int STATE; // State of snake: dead or alive
int SIZE_BOARD;
POINT WIN_POINT;
int LEVEL;
using namespace std;


int main()
{
   system("color 70");
   FixConsoleWindow();
   StartGame();

   int w, h;
   GetWidthnHeighAsciiArt("title.txt", w, h);
   cout << w <<" "<< h;

    //thread t1(ThreadFunc);
    //HANDLE handle_t1 = t1.native_handle();

    //PrintFile((120 - GetWidthtAsciiArt("title.txt")) / 2, 3, "title.txt");
    //GoToXY(0, 0);
    //cout << SIZE_BOARD << "\n";
    /*for (int i = 0; i < SIZE_BOARD; ++i) {
        cout << board[i].x << " " << board[i].y << "\n";
    }*/
    DrawGate(2,3);
    
    while (1);
    int temp;
    /*while (1) {
        temp = toupper(_getch());
        if (STATE == 1) {
            if (temp == 'P') {
                PauseGame(handle_t1);
            }
            else if (temp == 27) {
                ExitGame(handle_t1);
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
            else {
                ExitGame(handle_t1);
                return 0;
            }
        }
    }*/

    //======= test thread handle
    /*

    SuspendThread(t1.native_handle());
    Sleep(1000);
    ResumeThread(t1.native_handle());

    t1.join();*/
    //======= end test thread handle

    return 0;
}