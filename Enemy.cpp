#include "Enemy.h"
#include "Streaming.h"
Enemy::Enemy()
{
    position = Vector2(120, 41);
    scale = 3;
    speed = 1;
    health = 1;
    canShoot = false;
}

Enemy::Enemy(Vector2 pos, int scale, int speed, int health, bool canShoot)
{
    this->position = pos;
    this->scale = scale;
    this->speed = speed;
    this->health = health;
    this->canShoot = canShoot;
}
void Enemy::Setup(Vector2 pos, int speed)
{
    this->position = pos;
    this->speed = speed;
}
void Enemy::Update(Graphics& OLED, Player& player)
{
    Move();
    if(HasCollided(player))
    {
        player.health--;
    }
    Draw(OLED);
    if(position.x <= 0)
    {
        position.x = 125;
    }
}

void Enemy::Draw(Graphics& OLED)
{
    OLED.Circle(position, scale, false);
}

void Enemy::Move()
{
    this->position.x -= speed;
}

bool Enemy::HasCollided(Player& player)
{
    int dx = abs(player.position.x - this->position.x);
    Serial << dx << endl;
    int dy = abs(player.position.y - this->position.y);
    Serial << dy << endl;
    Serial << dx * dx + dy * dy << endl;
    float distance = mathf.SQRT((float(dx * dx + dy * dy)));
    Serial << mathf.SQRT((dx * dx + dy * dy)) << endl;
    if(distance < player.scale + this->scale)
    {
        return true;
    }
    else 
    {
        return false;
    }
}
