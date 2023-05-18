#ifndef PLAYER_H
#define PLAYER_H

#include "grid.h"
#include "structs.h"
#include <vector>
#include <string>

class Player
{
private:
    char playerChar;
    int health;
    int score;
    int turns;
    bool isInjured;
    CanMove canMove;
    std::vector<Opponent> opponents;
    std::vector<Place> eraseOpps;
    Place position;
    Place erase;
public:
    void scan(const std::vector<Place>&);
    char getPlayerChar();
    void generateOpponents();
    const std::vector<Opponent>& getOpponents() const;
    const std::vector<Place>& getEraseOpps() const;
    std::string move(int ch, const std::vector<Place>& );
    void combat(int);

    void injured();
    void increaseScore();
    void increaseTurns();
    int getScore();
    int getTurns();
    int getHealth();
    const Place& getPosition();
    const Place& getErase();
    Player();

};

#endif // PLAYER_H
