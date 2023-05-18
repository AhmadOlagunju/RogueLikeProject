#include "player.h"

Player::Player()
{
    position.x = 5;
    position.y = 5;
    health = 5;
    score = 0;
    playerChar = 'v';
    isInjured = false;
    generateOpponents();
}
void Player::generateOpponents()//uses the rand function to generate random numbers to be positions of opponents
{
    
    opponents.push_back(Opponent(3, Place{25,5}));
    opponents.push_back(Opponent(3, Place{50,5}));
    opponents.push_back(Opponent(3, Place{75,5}));
}

void Player::scan(const std::vector<Place>& walls)
{   
    eraseOpps.clear(); //clear erase vector
    int opponentX, opponentY, wallsX, wallsY;
    for(size_t count{0}; count < opponents.size(); count++)
        {
            opponentX = opponents.at(count).getPos().x;
            opponentY = opponents.at(count).getPos().y;

            if((position.x == opponentX && (position.y - 1 == opponentY || position.y + 1 == opponentY)) || (position.y == opponentY && (position.x + 1 == opponentX || position.x - 1 == opponentX)))
            {
                combat(count);
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
                canMove.up =false;
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


    }
}

char Player::getPlayerChar()
{
    return playerChar;
}
const std::vector<Opponent>& Player::getOpponents() const {
    return opponents;
}
const std::vector<Place>& Player::getEraseOpps() const {
    return eraseOpps;
}
void Player::combat(int index) {
    int playerHit = rand() % 2;
    if(playerHit == 0) {
        injured();
        score += 1;
    }
    else{
        score += 2;
    }
    opponents.at(index).isKilled();
    eraseOpps.push_back(opponents.at(index).getPos());
    opponents.erase(opponents.begin() + index);
}
std::string Player::move(int ch, const std::vector<Place>& walls)
{
    erase.x = position.x;//sets erase to the location of player to fill it with a space later
    erase.y = position.y;//sets erase to the position of player will be filled with ' ' later

    this->scan(walls);

    std::string message = " ";

    switch(ch)
    {
    case KEY_LEFT:
        if(canMove.left != false)
        {
            position.x--;
            playerChar = '>';//sets player char to show directional movement
        }
        else
            message += "Can't move left!";
        break;
    case KEY_RIGHT:
        if(canMove.right != false)
        {
            position.x++;
            playerChar = '<';//sets player char to show directional movement
        }
        else
            message += "Can't move right!";
        break;
    case KEY_UP:
        if(canMove.up != false)
        {
            position.y--;
            playerChar = 'v';//sets player char to show directional movement
        }
        else
            message += "Can't move up!";
        break;
    case KEY_DOWN:
        if(canMove.down != false)
        {
            position.y++;
            playerChar = '^';//sets player char to show directional movement
        }
        else
            message += "Can't move down!";
        break;
    case 'q':
        break;
    case KEY_MOUSE:
        break;
    default:
        message = "NO! Use the proper keys!";
        refresh();
    }

    canMove.up = true;
    canMove.down = true;
    canMove.left = true;
    canMove.right = true;
    if(isInjured){
        message+= "Ouch!";
        isInjured = false;
    }
    return message;
}

void Player::injured()
{
    health -= 2;
    isInjured = true;
}

void Player::increaseScore()
{
    score++;
}

void Player::increaseTurns()
{
    turns++;
}

int Player::getScore()
{
    return score;
}

int Player::getTurns()
{
    return turns;
}

int Player::getHealth()
{
    return health;
}

const Place& Player::getPosition()
{
    return position;
}

const Place &Player::getErase()
{
    return erase;
}
