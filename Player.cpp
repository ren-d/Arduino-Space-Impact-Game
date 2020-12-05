#include "Player.h"
Player::Player()
{
    health = 3;
    damageCooldown = 25;
    for (int i = 0; i < 30; i++)
    {
        bullets[i].Initialize();
    }

}

void Player::Move(Vector2 position, Graphics& OLED)
{
    this->position = position;
    Draw(position, false, OLED);
}

void Player::Draw(Vector2 position, bool onCooldown, Graphics& OLED)
{
    if(health >= 1)
    {
        if(!onCooldown)
        {
            OLED.Circle(position, scale, true);
        }
        else
        {
            if(damageCooldown % 4 == 0)
            {
                OLED.Circle(position, scale, false);
                
                
            }
            else
            {
                OLED.Circle(position, scale, true);
            }
            
            
        }
        
    }
}

void Player::Update(int buttonPin, Graphics& OLED)
{
    if(buttonPin == 0)
    {
        for(int i = 0; i < 30; i++)
        {
            if(bullets[i].isShot == false)
            {
                Shoot(bullets[i]);
                break;
            }
        }
    }
    for(int i = 0; i < 30; i++)
    {
        bullets[i].Update(OLED);
    }
}

void Player::TakeDamage()
{
    if(health > 0)
    {
        health--;
    }
    
}

void Player::Shoot(Bullet& bullet)
{
    bullet.position = this->position;
    bullet.isShot = true;
}