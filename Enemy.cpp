#include "Enemy.h"
#include "Streaming.h"

//Constructor for the Enemy class, with default valus
Enemy::Enemy()
{
    position = Vector2(120, 41);
    scale = 3;
    speed = 1;
    health = 1;
    isActive = false;
    type = 0;
}

Enemy::Enemy(Vector2 pos, int scale, int speed, int health) //secondary constructer with settable values
{
    this->position = pos;
    this->scale = scale;
    this->speed = speed;
    this->health = health;
}

//external function to setup the enemy
void Enemy::Setup(Vector2 pos, int speed, int type)
{
    this->position = pos;
    this->speed = speed;
    this->type = type;
    isActive = true;
    this->health = 1;
}

//runs every frame
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
        if(HasCollided(player.bullets[i].position)) //checks if the enemy has collided with a bullet
        {

            Destroy();
            player.bullets[i].Destroy(); //destroys the bullet
            player.score += 75; // adds score to the player

            
        }
        else if(HasCollided(player.position) && player.damageCooldown == 0)
        {
            Destroy();
        }
    }
}


//draws the enemy depending on the type
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

//moves the enemy by its speed
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

//uses a basic circle collision algorithm to check if anything has collided wtih the enemy
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

//destroys the enemy
void Enemy::Destroy()
{
    health--;
    isActive = false;
}


