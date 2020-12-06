#include "Bullet.h"
Bullet::Bullet()
{
    Initialize();
}

void Bullet::Update(Graphics& OLED)
{
    if(isShot)
    {
        position.x += 5;
    }

    Draw(OLED);

    if(position.x > 120)
    {
        isShot = false;
        position.x = 5;
    }
}

void Bullet::Draw(Graphics& OLED)
{
    if(isShot)
    {
        OLED.Circle(position, 1, true);
    }
}

void Bullet::Destroy()
{
    isShot = false;
}

void Bullet::Initialize()
{
    isShot = false;
}

