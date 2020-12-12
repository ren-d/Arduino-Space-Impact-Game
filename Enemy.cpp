#include "Enemy.h"
#include "Streaming.h"
Enemy::Enemy()
{
    position = Vector2(120, 41);
    scale = 3;
    speed = 1;
    health = 1;
    isActive = false;
    type = 0;
}

Enemy::Enemy(Vector2 pos, int scale, int speed, int health)
{
    this->position = pos;
    this->scale = scale;
    this->speed = speed;
    this->health = health;
}
void Enemy::Setup(Vector2 pos, int speed, int type)
{
    this->position = pos;
    this->speed = speed;
    this->type = type;
    isActive = true;
    this->health = 1;
}

void Enemy::Update(Graphics& OLED, Player& player)
{
    Move();
    Draw(OLED);
    if(position.x <= 0)
    {
        isActive = false;
    }
    for(int i = 0; i < 17; i++)
    {
        if(HasCollided(player.bullets[i].position))
        {

            Destroy();
            player.bullets[i].Destroy();
            player.score += 75;

            
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
        switch(type)
        {
            case 0:
                OLED.Circle(position, scale, false);
                break;
            case 1:
                OLED.Rectangle(position, Vector2(scale + 4, scale + 4));
        }
        
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
    isActive = false;
}


