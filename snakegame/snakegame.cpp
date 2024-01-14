//Snake game 23CLC01

#include <iostream>
#include "snakegame.h"

//Global variables
POINT snake[40];
POINT food[6];
int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is one direction my snake cannot move to)
int MOVING;//used to determine the direction my snake moves (At a moment, there  are three directions my snake can move)
int SPEED;// Standing for level, the higher the level, the quicker the speed
int HEIGH_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
int FOOD_INDEX; // current food-index
int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size may be 10
int STATE; // State of snake: dead or alive

using namespace std;

void ThreadFunc() {
    cout << "Khong bao gio ngu quen";
}

int main()
{
    system("color 70");
    FixConsoleWindow();
    StartGame();
 
    PrintFile(10, 4, "title.txt");

    //======= test thread handle
    /*thread t1(ThreadFunc);
    HANDLE handle_t1 = t1.native_handle();

    SuspendThread(t1.native_handle());
    Sleep(1000);
    ResumeThread(t1.native_handle());

    t1.join();*/
    //======= end test thread handle


    return 0;
}