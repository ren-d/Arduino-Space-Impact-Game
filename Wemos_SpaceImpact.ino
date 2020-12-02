#include <Streaming.h>
#include <iomanip>
#include <iostream>
#include "Vector2.h"
int buttonPin = D5;

#include "Graphics.h"
Graphics OLED;

#include "Player.h"
Player player;

void DebugUI(int sensor, int button);
void GameScreenUI();

void setup()
{
 Serial.begin(115200);
 OLED.blah();
 pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
 OLED.Clear();
 int sensorValue = analogRead(A0) / 10.24;

 DebugUI(sensorValue, buttonPin);
 GameScreenUI();
 player.Draw(Vector2(5, sensorValue), OLED);

 
 OLED.Render();
}

//shows input values, !-for debugging-!
void DebugUI(int sensor, int button)
{
 OLED.PrintToScreen(String(sensor), Vector2(0,0));
 OLED.PrintToScreen(" ");
 OLED.PrintToScreen(String(digitalRead(button)));
 OLED.endlg();
}

void GameScreenUI()
{
    OLED.Line(Vector2(0,16), Vector2(122,16));
    OLED.Line(Vector2(0,14), Vector2(122,14));
    OLED.Line(Vector2(122,0), Vector2(122,14));
}




