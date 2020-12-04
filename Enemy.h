#include "Graphics.h"
#include "Math.h"
#include "Vector2.h"
#include "Player.h"
class Enemy
{
public:
    Vector2 position;
    int scale;
    int health;
    int speed;
    bool canShoot;

    Enemy();
    Enemy(Vector2 pos, int scale, int speed, int health, bool canShoot);
    void Setup(Vector2 pos, int speed);
    void Update(Graphics& OLED, int yAxis);
    void Draw(Graphics& OLED);
    void Move();
    bool HasCollided(int yAxis);
private:
    Math mathf;
};
