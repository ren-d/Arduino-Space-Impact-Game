#include "Player.h"

//default player constructor
Player::Player()
{
    score = 0;
    health = 3;
    damageCooldown = 0;
    bulletCooldown = 7;
    buttonBuffer = false;
    //initialises all the bullets
    for (int i = 0; i < 17; i++)
    {
        bullets[i].Initialize();
    }

}

//moves the player
void Player::Move(Vector2 position, Graphics& OLED)
{
    this->position = position;
    Draw(position, false, OLED);
}

//draws the player depending on the position
void Player::Draw(Vector2 position, bool onCooldown, Graphics& OLED)
{
    this->position = position;
    //plays animation for when the player is on cooldown
    if(health >= 1)
    {
        if(!onCooldown)
        {
            OLED.Circle(position, scale, true);
        }
        else
        {
            if(damageCooldown >= 15)
            {
                OLED.Circle(position, scale, false);
                
                
            }
            else if(damageCooldown >= 9)
            {
                OLED.Circle(position, scale, true);
            }
            else if(damageCooldown >= 1)
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

//main update loop played every frame for the player
void Player::Update(int buttonPin, Graphics& OLED)
{

    if(health > 0)
    {
        //checks if the button is pressed and  shoots a bullet
        if(buttonPin == 0 && buttonBuffer == false)
        {
            for(int i = 0; i < 17; i++)
            {
                if(bullets[i].isShot == false)
                {
                    if(bulletCooldown < 0)
                    {
                        Shoot(bullets[i]);
                        bulletCooldown = 12;
                        buttonBuffer = false;
                        break;
                    }
                
                }
            }
        }
        for(int i = 0; i < 17; i++)
        {
            //updates all the bullets
            bullets[i].Update(OLED);
        }
        bulletCooldown--;
        ButtonPress(buttonPin);

    }
    
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

//makes the player take damage
void Player::TakeDamage()
{
    if(health > 0)
    {
        health--;
    }
    
}

//shoots a bullet
void Player::Shoot(Bullet& bullet)
{
    bullet.isShot = true;
    bullet.position.y = position.y;
    bullet.position.x = position.x;
}