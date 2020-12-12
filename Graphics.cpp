#include "Arduino.h"
#include "Streaming.h"
#include "Vector2.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#include "Graphics.h"


Graphics::Graphics()
{
    display.begin(SSD1306_SWITCHCAPVCC, OLED_SCREEN_I2C_ADDRESS);
}

void Graphics::Render()
{
    display.display();
}
void Graphics::blah()
{
     display.display();
 delay(2000);
 display.clearDisplay();
 display.setCursor(0,0);
 display.setTextSize(1); // - a line is 21 chars in this size
 display.setTextColor(WHITE);
}
void Graphics::Clear()
{
    display.clearDisplay();
}

void Graphics::Circle(Vector2 pos, int size, bool fill)
{
    switch(fill)
    {
        case false:
            display.drawCircle(pos.x, pos.y, size, WHITE);
            break;
        case true:
            display.fillCircle(pos.x, pos.y, size, WHITE);
            break;
    }
}

void Graphics::Line(Vector2 point1, Vector2 point2)
{
    display.drawLine(point1.x, point1.y, point2.x, point2.y, WHITE);
}

void Graphics::Rectangle(Vector2 pos, Vector2 scale)
{
    display.drawRect(pos.x, pos.y, scale.x, scale.y, WHITE);
}

void Graphics::PrintToScreen(String text)
{
    display << text;
}

void Graphics::PrintToScreen(String text, Vector2 pos)
{
    display.setCursor(pos.x, pos.y);
    display << text;
}
void Graphics::endlg()
{
    display << " " << endl;
}