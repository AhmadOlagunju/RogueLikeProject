#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <curses.h>
#include <sstream>
#include "structs.h"
#include "opponent.h"

class Grid
{
private:

    int set = 1;
    int menueset2 = 29;
    //Place coordinates;
    char obstacleChar = 'X';
    char borderChar = 'X';
    char playerChar;
    char opponentChar = '@';
    int row, column;
    int obstacleDiv = 40;
    std::vector<Place> obstacles;
    

public:
    Grid();
    const std::vector<Place>& getObstacles();
    
    void setPlayerChar(char playerCharacter);
    void print(const Place& player, const Place& erase, const std::vector<Opponent>&, const std::vector<Place>&);
    void print(const Place& player);
    void printInBox(std::string message);
    void printStats(int health, int score, int turns);
    int getRow();
    int getColumn();
    void findRowAndColumn();
    void generateObstacles();
};

#endif // GRID_H
