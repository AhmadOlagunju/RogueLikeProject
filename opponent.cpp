#include "opponent.h"

Opponent::Opponent() {
    
}
Opponent::Opponent(int oppHealth, Place pos)
{
    health = oppHealth;
    position = pos;
    /*
    int y, x;
    getmaxyx(stdscr, y, x);
    wasCombat = false;
    doesInjure = false;

    genOpp();*/
}

void Opponent::isKilled()
{   
    health = 0;
    
}

void Opponent::genOpp()
{/*
    srand(time(NULL));
    //Making opponents
    int row, column;

    getmaxyx(stdscr, row, column);

    Place dummy;

    for(int a = 0; a < ((row * column) / opponentDiv); a++)
    {
        dummy.y = rand() % ((row - 2) - 5 + 1) + 5;
        dummy.x = rand() % ((column - 2) - 1 + 1) + 1;
        opponents.push_back(dummy);
    }
    */

}

void Opponent::findUser(const Place& userPos, const Place& oppPos, playerLoc& userLoc)
{/*

    //conditions for whether player is above, below, to the right or the left of the opponents
    if(userPos.y > oppPos.y)
        userLoc.below = true;
    if(userPos.y < oppPos.y)
        userLoc.above = true;
    if(userPos.x > oppPos.x)
        userLoc.right = true;
    if(userPos.x < oppPos.x)
        userLoc.left = true;
    */
}

void Opponent::combat(const Place& position)
{/*
    wasCombat = true;

    int chance = rand() % ((3) - 1 + 1) + 1;

    if(chance == 3)
        doesInjure = true;
    else {
        doesInjure = false;
    }

    killedOpponent(position);*/
}
const Place& Opponent::getPos() const{
    return position;
}
void Opponent::moveOpp(const Place& userPos, const std::vector<Place>& obstacles)
{
    /*
    wasCombat = false;
    doesInjure = false;

    CanMove canMove;


    for(size_t i = 0; i < opponents.size(); i++)
    {
        canMove.up = true;
        canMove.down = true;
        canMove.right = true;
        canMove.left = true;
        playerLoc userLoc{false, false, false, false};
        findUser(userPos, opponents.at(i), userLoc);

        scan(obstacles, opponents.at(i), canMove, userPos, i);

        //adjusts opponent Place struct based on findUser
        if(userLoc.above == true && canMove.up == true)
            opponents.at(i).y--;
        else if(userLoc.below == true && canMove.down == true)
            opponents.at(i).y++;
        else if(userLoc.right == true && canMove.right == true)
            opponents.at(i).x++;
        else if(userLoc.left == true && canMove.left == true)
            opponents.at(i).x--;
    }
*/
}

bool Opponent::getWasCombat()
{
    return wasCombat;
}

bool Opponent::getDoesInjure()
{
    return doesInjure;
}
int Opponent::scan(const std::vector<Place>& walls, const Place& position, CanMove& canMove, const Place& userPos, int opponentNum)
{/*
    int opponentX, opponentY, wallsX, wallsY;
        for(size_t count{0}; count < opponents.size(); count++)
            {

                if(count == opponentNum)
                {
                    continue;
                }

                opponentX = opponents.at(count).x;
                opponentY = opponents.at(count).y;

                if(position.x == opponentX )
                {
                    if(position.y - 1 == opponentY)
                    {
                        canMove.up =false;
                    }
                    if(position.y + 1 == opponentY)
                    {
                        canMove.down =false;
                    }
                }

                if(position.y == opponentY)
                {
                    if(position.x + 1 == opponentX)
                    {
                        canMove.right =false;
                    }
                    if(position.x - 1 == opponentX)
                    {
                        canMove.left = false;
                    }
                }

            }
        if(position.x == userPos.x )
        {
            if(position.y - 1 == userPos.y)
            {
                canMove.up = false;
                combat(position);
                return 0;
            }
            if(position.y + 1 == userPos.x)
            {
                canMove.down = false;
                combat(position);
                return 0;
            }
        }

        if(position.y == userPos.y)
        {
            if(position.x + 1 == userPos.y)
            {
                canMove.right = false;
                combat(position);
                return 0;
            }
            if(position.x - 1 == userPos.x)
            {
                canMove.left = false;
                combat(position);
                return 0;
            }
        }

        for(size_t count{0}; count < walls.size(); count++)
            {
                wallsX = walls.at(count).x;
                wallsY = walls.at(count).y;
                if(position.x == wallsX)
                {
                    if(position.y - 1 == wallsY)
                    {
                        canMove.up = false;
                    }
                    if(position.y + 1 == wallsY)
                    {
                        canMove.down =false;
                    }
                }
                if(position.y == wallsY)
                {

                    if(position.x - 1 == wallsX)
                    {
                        canMove.left  = false;
                    }
                    if(position.x + 1 == wallsX)
                    {
                        canMove.right  = false;
                    }
                }


            }*/
}


