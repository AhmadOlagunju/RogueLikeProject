#ifndef STRUCTS_H
#define STRUCTS_H

struct Place
{
    int x;
    int y;
};
struct CanMove
{
    bool up;
    bool down;
    bool left;
    bool right;
};
struct playerLoc
{
    bool above;
    bool below;
    bool right;
    bool left;
};
#endif // STRUCTS_H
