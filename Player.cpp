#include "Player.h"
#include "Graphics.h"
Player::Player()
{

}

void Player::Move(Vector2 position, Graphics& OLED)
{
    this->position = position;
    Draw(position, OLED);
}

void Player::Draw(Vector2 position, Graphics& OLED)
{
    OLED.Circle(position, 2, true);
}