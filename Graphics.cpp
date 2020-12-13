#include "Arduino.h"
#include "Streaming.h"
#include "Vector2.h"

//includes the OLED's graphics libraries
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#include "Graphics.h"


Graphics::Graphics()
{
    //starts the OLED display
    display.begin(SSD1306_SWITCHCAPVCC, OLED_SCREEN_I2C_ADDRESS);
}

//renders objects to the screen
void Graphics::Render()
{
    display.display();
}

//loads up the splashscreen
void Graphics::blah()
{
     display.display();
 delay(2000);
 display.clearDisplay();
 display.setCursor(0,0);
 display.setTextSize(1); // - a line is 21 chars in this size
 display.setTextColor(WHITE);
}

//clears the display
void Graphics::Clear()
{
    display.clearDisplay();
}

//displays a circle to the screen
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

//displays a line to the screen
void Graphics::Line(Vector2 point1, Vector2 point2)
{
    display.drawLine(point1.x, point1.y, point2.x, point2.y, WHITE);
}

//displays a rectangle to the screen
void Graphics::Rectangle(Vector2 pos, Vector2 scale)
{
    display.drawRect(pos.x, pos.y, scale.x, scale.y, WHITE);
}

//displays text to the screen
void Graphics::PrintToScreen(String text)
{
    display << text;
}

//displays text to the screen and changes cursor position
void Graphics::PrintToScreen(String text, Vector2 pos)
{
    display.setCursor(pos.x, pos.y);
    display << text;
}

//displays a new line to the screen
void Graphics::endlg()
{
    display << " " << endl;
}