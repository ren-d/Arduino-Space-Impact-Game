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
void Enemy::Update(Graphics& OLED, Player& player)
{
    Move();
    Draw(OLED);
    if(position.x <= 0)
    {
        position.x = 125;
    }
    for(int i = 0; i < 17; i++)
    {
        if(HasCollided(player.bullets[i].position))
        {
            Destroy();
            player.bullets[i].Destroy();
            player.score += 200;
        }
        else if(HasCollided(player.position) && player.damageCooldown == 0)
        {
            Destroy();
        }
    }
}

void Enemy::Draw(Graphics& OLED)
{
    if(health >= 1)
    {
        OLED.Circle(position, scale, false);
    }
    
}

void Enemy::Move()
{
    if(health >= 1)
    {
        this->position.x -= speed;
    }
    else
    {
        this->position =  Vector2(0,0);
    }
    
    
}

bool Enemy::HasCollided(Vector2 position)
{
    int dx = abs(position.x - this->position.x);
    int dy = abs(position.y - this->position.y);
    
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

void Enemy::Destroy()
{
    health--;
}
