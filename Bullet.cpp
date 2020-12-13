#include "Bullet.h"
Bullet::Bullet()
{
    Initialize();
}

//updates the bullet's position every frame if the bullet has been shot
void Bullet::Update(Graphics& OLED)
{
    if(isShot)
    {
        position.x += 4;
    }

    Draw(OLED);

    if(position.x > 120)
    {
        isShot = false;
        position.x = 5;
    }
}


//renders the bullet
void Bullet::Draw(Graphics& OLED)
{
    if(isShot)
    {
        OLED.Circle(position, 1, true);
    }
}

//destroys the bullet
void Bullet::Destroy()
{
    isShot = false;
    position = Vector2(0,0);
}

void Bullet::Initialize()
{
    isShot = false;
}

