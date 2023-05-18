#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <curses.h>
#include "grid.h"
#include "player.h"
#include "opponent.h"

using namespace std;

int main()
{
    srand(time(NULL));

    cout << "Size screen (At least 80x24) then enter y." << endl;//asks user to resize screen

    char init;//a character to get value for if the user wants to start game
    int ch;//will hold user input throughout game for movement

    cin >> init;

    while(init != 'y')//will keep asking until user enters y
    cin >> init;

    initscr();//Starts ncurses

    noecho();//turns off echoing so what the user enters does not show on the screen

    cbreak();//alsows the imediate use of the users entered data withut the need for an endline character
    curs_set(0);//makes the cursor invisable
    start_color();//turns on the ability touse colour
    keypad(stdscr, TRUE);//lets the program accept the function and arrow keys as valid input

    int row, column;

    getmaxyx(stdscr, row, column);//gets the max screen size

    init_pair(9, COLOR_MAGENTA, COLOR_WHITE);

    attron(COLOR_PAIR(9));//changes the colour to be printed in

    const std::string intro = "Hello! This is a basic Rogue Like style game developed in C++ with Ncurses. You can use the arrow keys to move up, down, left, and right. You have five health and will lose it occasionally when fighting an opponent. Running into an opponent will start combat, killing the opponent and occasionally harming you the player. You can not move through obstacles, opponents, or the border. Have fun! hit 'q' anytime to quit immediately"; // the intro message

    for(int a = 0; a < row; a++)//prints a blank screen so the intro can be printed clearly
    {
        for(int b = 0; b < column; b++)
        {
            mvaddch(a, b, ' ');
        }
    }

    int middleUpDown = (row / 4);//sets it to 1/4 of the screen
    int middleLeftRight = (column / 4);//sets it to 1/4 of the screen
    int x, y;
    int count = 1;

    move(middleUpDown, middleLeftRight);//moves to 1/4 down the screen and 1/4 across the screen

    for (int a = 0; a < intro.size(); a++)//prints the intro
    {
        getyx(stdscr, y, x);//gets the max values for the x and y coordinates on the screen
        if(x == (column - middleLeftRight))//stops at 3/4 the way across the screen
        {
            move((middleUpDown + count), middleLeftRight);
            count++;//adds one to count so that the same line wont be printed on more than once
        }
        addch(intro.at(a));
    }

    getch();

    attroff(COLOR_PAIR(9));

    Player player;//creates the player
    Grid game;//creates a grid object
    Opponent enemy;//creates an opponent object to handle opponent generation and movement

    //generates opponents
    
    game.print(player.getPosition());//prints the playing field
    game.printInBox("Hit q to exit.");//tels he user the key they need to hit to end the game

    do
    {

        ch = getch();

        game.printInBox(player.move(ch, game.getObstacles()));//moves the player and then outputs any message such as "Can't go right" with print in box

        game.setPlayerChar(player.getPlayerChar());//sets the player char so that the player character changes for the last direction that was moved in

        game.print(player.getPosition(), player.getErase(), player.getOpponents(), player.getEraseOpps());//prints the play area and erases behind the player while moving the player to its new location

        refresh();

        game.printStats(player.getHealth(), player.getScore(), player.getTurns());//prints the players score, health, and the number of turns elapsed

        refresh();

        player.increaseTurns();//increases the number of turns

        enemy.moveOpp(player.getPosition(), game.getObstacles());//causes the enemies to move

       
        if(player.getOpponents().size() == 0)//when there are no more opponents
        {
            break;
        }

    }while(ch != 'q' && player.getHealth() > 0);//while the user has not entered 'q' to quit

    game.printInBox("Goodbye!");

    game.print(player.getPosition(), player.getErase(), player.getOpponents(), player.getEraseOpps());//prints the game one more time so that it does not end so abruptly after the last opponent is killed

    getch();
    refresh();

    attron(COLOR_PAIR(9));

    for(int a = 0; a < row; a++)//prints a blank white screen so that the end message can be displayed nicely
    {
        for(int b = 0; b < column; b++)
        {
            mvaddch(a, b, ' ');
        }
    }

    refresh();

    std::ostringstream outScore;
    std::ostringstream outTurns;

    outScore << player.getScore();//sets outScore to the players score
    outTurns << player.getTurns();//sets outTurns to the number of turns played

    std::string end1 = "Your final score was: " + outScore.str() + ", ";//makes the users final score into a string
    std::string end2 = "and you survived " + outTurns.str() + " turns!";//makes the total number of turns the player played the game into a string

    move( y / 2, x / 2);//moves the cursor to the middle of the screen
    for (int a = 0; a < end1.size(); a++)//prints the first line of the end massage
        addch(end1.at(a));
    move(((y / 2) + 1), (x / 2));//moves the cursor to the middle of the screen and one line down
    for (int a = 0; a < end2.size(); a ++)//prints the second line of the end message
        addch(end2.at(a));

    refresh();//refreshes after printing something
    getch();//gets a character to give a puse before ncurses ends
    endwin();//ends ncurses

    return 0;
}
