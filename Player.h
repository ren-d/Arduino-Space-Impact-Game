#include <Streaming.h>
#include "Vector2.h"
#include "Graphics.h"
class Player
{
    public:
    Vector2 position;
    Player();
    void Move(Vector2 position, Graphics& OLED);
    void Draw(Vector2 position, Graphics& OLED);
};