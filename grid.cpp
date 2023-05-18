#include "grid.h"
#include "player.h"
#include "structs.h"

void Grid::setPlayerChar(char playerCharacter)
{
    playerChar = playerCharacter;
}

void Grid::generateObstacles()//uses the rand function to generate random numbers to be positions of obstacles
{
    for(int a = 0; a < ((row * column) / obstacleDiv); a++)
    {
        Place dummy;
        dummy.y = rand() % ((row - 2) - 5 + 1) + 5;
        dummy.x = rand() % ((column - 2) - 1 + 1) + 1;
        obstacles.push_back(dummy);
    }
}


const std::vector<Place> &Grid::getObstacles()
{
    return obstacles;
}

void Grid::findRowAndColumn()//gets the maximum number of rows and columns with an ncurses function
{
    getmaxyx(stdscr, row, column);//returns the max size of the screen
}

void Grid::print(const Place& player, const Place& erase, const std::vector<Opponent>& opponents, const std::vector<Place>& eraseOpps)//prints the player and puts a space where it used to be
{
    attron(COLOR_PAIR(2));

    mvaddch(erase.y, erase.x, ' ');//erases where the player was before they moved
    for(int i = 0; i < eraseOpps.size(); i++) {
        mvaddch(eraseOpps.at(i).y, eraseOpps.at(i).x, ' ');
    }


    for(int a = 0; a < ((row * column) / obstacleDiv); a++)
    {
        mvaddch(obstacles.at(a).y, obstacles.at(a).x, obstacleChar);
    }

    attron(COLOR_PAIR(4));

    for(int a = 0; a < opponents.size(); a++)//prints all of the opponents
    {
        Place oppPos = opponents.at(a).getPos();
        mvaddch(oppPos.y, oppPos.x, opponentChar);
    }

    refresh();

    attron(COLOR_PAIR(1));

    mvaddch(player.y, player.x, playerChar);//prints the player
    refresh();

}

void Grid::print(const Place& player)//used to initially print the player and obstacles
{
    attron(COLOR_PAIR(2));

    for(int a = 0; a < ((row * column) / obstacleDiv); a++)//prints the obstacles
    {
        mvaddch(obstacles.at(a).y, obstacles.at(a).x, obstacleChar);
    }

    refresh();

    for(int a = set; a < 4; a++)//prints the blank white of the top left screen
    {
        for(int b = set; b < 28 ; b++)
        {
            attron(COLOR_PAIR(5));
            mvaddch(a, b, ' ');
        }
     }

    attron(COLOR_PAIR(1));

    mvaddch(player.y, player.x, playerChar);//prints the player
    refresh();
}

void Grid::printInBox(std::string message)//used to print in the top left box
{
    attron(COLOR_PAIR(5));
    for(int a = set; a < 4; a++)//clears the box of any other messages
    {
        for(int b = set; b < 28 ; b++)
        {
            mvaddch(a, b, ' ');
        }
     }
    mvaddch(set, set, message.at(0));
    for(int a = 1; a < message.size(); a++)//prints the message
    {
        addch(message.at(a));
        refresh();
    }
}

void Grid::printStats(const int health, const int score, const int turns)//used to print the stats of the player
{

    for(int a = 1; a < 4; a++)//clears the menu at the top right
    {
        for(int b = menueset2; b < (column - 1); b++)
        {
            attron(COLOR_PAIR(5));
            mvaddch(a, b, ' ');
        }
    }

    attron(COLOR_PAIR(5));//sets the colour

    std::ostringstream healthOut;
    std::ostringstream scoreOut;
    std::ostringstream turnsOut;

    healthOut << health;//sets healthOut to the players health
    scoreOut << score;//sets scoreOut the the players score
    turnsOut << turns;//sets turnsOut to the number of turns elapsed

    std::string healthString = "Health (" + healthOut.str() + "):";//displays the health in a number form in brackets so that it can easily be seen even if the user does not want to count the health bar
    std::string scoreString = "Score: " + scoreOut.str();
    std::string turnsString = "Turns#: " + turnsOut.str();
    for (int a = 0;a < health; a++)//adds a star to the healthString to represent health, one star is equivalent to one health point
    {
        healthString += "*";
    }
    for (int a = 1; a < 4; a++)
    {
        if(a == 1)
        {
            move(1, (menueset2));
            for (int b = 0; b < healthString.size(); b++)//prints the health of the player
            {
                attron(COLOR_PAIR(6));
                addch(healthString.at(b));
            }
            refresh();
        }
        else if (a == 2)//prints the player's score
        {
            move(2, (menueset2));
            for (int b = 0; b < scoreString.size(); b++)
            {
                attron(COLOR_PAIR(7));
                addch(scoreString.at(b));
            }
            refresh();
        }
        else if (a == 3)//prints the number of turns
        {
            move(3, (menueset2));
            for (int b = 0; b < turnsString.size(); b++)
            {
                attron(COLOR_PAIR(8));
                addch(turnsString.at(b));
            }
            refresh();
        }
    }
}

int Grid::getRow()
{
    return row;
}

int Grid::getColumn()
{
    return column;
}
Grid::Grid()//uses the findRowAndColumn and generateObstacle functions and then prints the starting board
{

    //Below is declaration of all color pairs
    init_pair(1, COLOR_BLUE, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_RED, COLOR_GREEN);
    init_pair(5, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(6, COLOR_RED, COLOR_WHITE);
    init_pair(7, COLOR_YELLOW, COLOR_WHITE);
    init_pair(8, COLOR_CYAN, COLOR_WHITE);

    Place dummyLoc;//a holder for coordinates to put into the obstacle vector for player collision

    this->findRowAndColumn();

    this->generateObstacles();

    this->setPlayerChar('v');//sets the player character to v to start

    attron(COLOR_PAIR(2) | A_BOLD);

    for(int a = 0; a < row; a++)//prints the entire screen as blank green
    {
        for(int b = 0; b < column; b++)
        {
            mvaddch(a, b, ' ');
        }
    }

    attron(COLOR_PAIR(3));

    for(int a = 0; a < column; a++)//the border
    {
        mvaddch(0, a, borderChar);
        mvaddch(row - 1, a, borderChar);
        dummyLoc.x = a;
        dummyLoc.y = 0;
        obstacles.push_back(dummyLoc);
        dummyLoc.y = row - 1;
        obstacles.push_back(dummyLoc);
    }
    for(int a = 0; a < row; a++)//prints the border
    {
        mvaddch(a, 0, borderChar);
        mvaddch(a, column - 1, borderChar);
        dummyLoc.x = 0;
        dummyLoc.y = a;
        obstacles.push_back(dummyLoc);
        dummyLoc.x = column - 1;
        obstacles.push_back(dummyLoc);
    }

    attron(COLOR_PAIR(2));

    for(int a = 0; a < ((row * column) / obstacleDiv); a++)//prints the obstacles
    {
        mvaddch(obstacles.at(a).y, obstacles.at(a).x, obstacleChar);
    }

    for(int a = set; a < 5; a++)//prints the screen at the top right for displaying messages
    {
        for(int b = set; b < 29; b++)
        {
            if(b == 28)//prints the border
            {
                attron(COLOR_PAIR(3));
                mvaddch(a, b, 'X');
                dummyLoc.x = b;
                dummyLoc.y = a;
                obstacles.push_back(dummyLoc);
            }
            else if (a == 4)//prints a border
            {
                mvaddch(a, b, 'X');
                dummyLoc.x = b;
                dummyLoc.y = a;
                obstacles.push_back(dummyLoc);
            }
            else//prints blank spaces
            {
                attron(COLOR_PAIR(5));
                mvaddch(a, b, ' ');
            }
        }
    }
    for(int a = 1; a < 5; a++)//prints the top right menu that will display the players statistics such as health and score
    {
        for(int b = menueset2; b < (column - 1); b++)
        {
            if (a == 4)
            {
                attron(COLOR_PAIR(3));
                mvaddch(a, b, 'X');
                dummyLoc.x = b;
                dummyLoc.y = a;
                obstacles.push_back(dummyLoc);
            }
            else
            {
                attron(COLOR_PAIR(5));
                mvaddch(a, b, ' ');
            }
        }
    }
}
