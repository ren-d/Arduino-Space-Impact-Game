#ifndef BULLET_H
#define BULLET_H
#include "Graphics.h"
#include "Vector2.h"
class Bullet
{
public:
    Vector2 position;
    bool isShot = false;
    Bullet();
    void Update(Graphics& OLED);
    void Draw(Graphics& OLED);
    void Destroy();
    void Initialize();
};
#endif /*BULLET_H*/