#ifndef OPPONENT_H
#define OPPONENT_H
#include "structs.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>


class Opponent
{
private:
    int health;
    Place position;
    Place oppErase;

    void findUser(const Place&, const Place&, playerLoc&);//finds which direction user is in eg. up,down,left right
    bool wasCombat;
    bool doesInjure;
    void combat(const Place& position);
    int opponentDiv;


public:
    Opponent();

    Opponent(int, Place);
    const Place& getPos() const;
    void isKilled();
    void genOpp();
    void moveOpp(const Place& userPos, const std::vector<Place>& obstacles);//moves opponent based on findUser
    int scan(const std::vector<Place>& walls, const Place& position, CanMove& canMove, const Place& userPos, int opponentNum);
    bool getWasCombat();
    bool getDoesInjure();

};

#endif // OPPONENT_H
