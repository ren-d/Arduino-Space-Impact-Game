#include "Player.h"
Player::Player()
{
    health = 3;
    damageCooldown = 25;
    bulletCooldown = 7;
    buttonBuffer = false;
    for (int i = 0; i < 17; i++)
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
    this->position = position;
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

    if(buttonPin == 0 && buttonBuffer == false)
    {
        for(int i = 0; i < 17; i++)
        {
            if(bullets[i].isShot == false)
            {
                if(bulletCooldown < 0)
                {
                    Shoot(bullets[i]);
                    bulletCooldown = 7;
                    buttonBuffer = false;
                    break;
                }
                
            }
        }
    }
    for(int i = 0; i < 17; i++)
    {
        bullets[i].Update(OLED);
    }
    bulletCooldown--;
    ButtonPress(buttonPin);

}

void Player::ButtonPress(int buttonPin) // Only activates the bullet when button is pressed and not held, if held it will not shoot more than once
{
    switch(buttonPin)
    {
        case 1:
            buttonBuffer = false;
            bulletCooldown = -1;
            break;
        case 0: 
            buttonBuffer = true;
            break;
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
    bullet.isShot = true;
    bullet.position.y = position.y;
    bullet.position.x = position.x;
}