#include "Bullet.h"
Bullet::Bullet()
{
    Initialize();
}

void Bullet::Update(Graphics& OLED)
{
    if(isShot)
    {
        position.x += 2;
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

}

void Bullet::Initialize()
{
    isShot = false;
}

