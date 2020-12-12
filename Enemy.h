#ifndef ENEMY_H
#define ENEMY_H
#include "Graphics.h"
#include "Math.h"
#include "Vector2.h"
#include "Player.h"
class Enemy
{
public:
    Vector2 position;
    int scale;
    int health;
    int speed;
    bool isActive;
    int type;

    Enemy();
    Enemy(Vector2 pos, int scale, int speed, int health);
    void Setup(Vector2 pos, int speed, int type);
    void Update(Graphics& OLED, Player& player);
    void Draw(Graphics& OLED);
    void Move();
    bool HasCollided(Vector2 position);
    void Destroy();
private:
    Math mathf;
};
#endif /*ENEMY_H*/