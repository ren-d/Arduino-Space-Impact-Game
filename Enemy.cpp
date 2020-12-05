#include "Enemy.h"
#include "Streaming.h"
Enemy::Enemy()
{
    position = Vector2(120, 41);
    scale = 3;
    speed = 1;
    health = 1;
    canShoot = false;
}

Enemy::Enemy(Vector2 pos, int scale, int speed, int health, bool canShoot)
{
    this->position = pos;
    this->scale = scale;
    this->speed = speed;
    this->health = health;
    this->canShoot = canShoot;
}
void Enemy::Setup(Vector2 pos, int speed)
{
    this->position = pos;
    this->speed = speed;
}
void Enemy::Update(Graphics& OLED)
{
    Move();
    Draw(OLED);
    if(position.x <= 0)
    {
        position.x = 125;
    }
}

void Enemy::Draw(Graphics& OLED)
{
    OLED.Circle(position, scale, false);
}

void Enemy::Move()
{
    this->position.x -= speed;
}

bool Enemy::HasCollided(int yAxis)
{
    int dx = abs(5 - this->position.x);
    int dy = abs(yAxis - this->position.y);
    
    float distance = mathf.SQRT((dx * dx + dy * dy));
    if(distance < 2 + this->scale)
    {
        return true;
    }
    else 
    {
        return false;
    }
}
