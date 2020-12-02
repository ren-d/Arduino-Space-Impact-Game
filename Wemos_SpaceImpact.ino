#include <Streaming.h>
#include <iomanip>
#include <iostream>
#include "Vector2.h"
int buttonPin = D5;

#include "Graphics.h"
Graphics OLED;

void DebugUI(int sensor, int button);

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




