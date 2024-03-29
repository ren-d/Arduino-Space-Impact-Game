#ifndef PLAYER_H
#define PLAYER_H
#include <Streaming.h>
#include "Vector2.h"
#include "Graphics.h"
#include "Bullet.h"

class Player
{
public:
    Vector2 position;
    Bullet bullets[17];
    int score;
    int health;
    int damageCooldown;
    int bulletCooldown;
    bool buttonBuffer;
    const int scale = 2;
    Player();
    void Update(int buttonPin, Graphics& OLED);
    void Move(Vector2 position, Graphics& OLED);
    void Draw(Vector2 position, bool onCooldown, Graphics& OLED);
    void TakeDamage();
    void Shoot(Bullet& bullet);
    void ButtonPress(int pinButton);
};
#endif /*PLAYER_H*/