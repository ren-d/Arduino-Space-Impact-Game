#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "Arduino.h"
#include "Streaming.h"
#include "Vector2.h"

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define OLED_RESET -1
#define OLED_SCREEN_I2C_ADDRESS 0x3C

class Graphics
{
    public:
    Graphics();
    void Render();
    void blah();
    void Clear();
    void Line(Vector2 point1, Vector2 point2);
    void Rectangle(Vector2 point1, Vector2 point2);
    void Circle(Vector2 pos, int size, bool fill);
    void PrintToScreen(String text);
    void PrintToScreen(String text, Vector2 pos);
    void endlg();
    private:
    Adafruit_SSD1306 display;
};
#endif