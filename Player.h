#ifndef PLAYER_H
#define PLAYER_H
#include <Streaming.h>
#include "Vector2.h"
#include "Graphics.h"
class Player
{
    public:
    Vector2 position;
    int health;
    const int scale = 2;
    Player();
    void Update();
    void Move(Vector2 position, Graphics& OLED);
    void Draw(Vector2 position, Graphics& OLED);
};
#endif