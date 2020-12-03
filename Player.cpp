#include "Player.h"
#include "Graphics.h"
Player::Player()
{
    health = 1;
}

void Player::Move(Vector2 position, Graphics& OLED)
{
    this->position = position;
    Draw(position, OLED);
}

void Player::Draw(Vector2 position, Graphics& OLED)
{
    if(health >= 1)
    {
        OLED.Circle(position, scale, true);
    }
}

void Player::Update()
{

}