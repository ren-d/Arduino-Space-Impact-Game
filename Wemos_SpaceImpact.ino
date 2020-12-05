#include <Streaming.h>
#include <iomanip>
#include <iostream>
#include "Vector2.h"
int buttonPin = D5;

#include "Graphics.h"
Graphics OLED;

#include "Player.h"
Player player;

#include "Enemy.h"
Enemy enemies[5];

#include "Math.h"
Math mathf;

void DebugUI(int sensor, int button);
void GameScreenUI();

bool damageCooldown = false;
void setup()
{
 Serial.begin(115200);
 OLED.blah();

 enemies[0].Setup(Vector2(120, 55), 2);
 enemies[1].Setup(Vector2(126, 41), 1);
 enemies[2].Setup(Vector2(150, 27), 7);
 enemies[3].Setup(Vector2(144, 37), 3);
 enemies[4].Setup(Vector2(140, 29), 3);
 
 pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
    GameLoop();
}

void GameLoop()
{
    OLED.Clear();
    int sensorValue = analogRead(A0) / 10.24;
    player.Update(digitalRead(buttonPin), OLED);
    
    for(int i = 0; i < 5; i++)
    {
        enemies[i].Update(OLED);
        if(damageCooldown == false)
        {
           if(enemies[i].HasCollided(mathf.Clamp(sensorValue, 19, 60)))
           {
               player.TakeDamage();
               damageCooldown = true;
               player.damageCooldown = 20;

           }
        }
    }
    
    if(damageCooldown == true)
    {
       if(player.damageCooldown != 0)
       {
           player.damageCooldown--;
       }
       else
       {
           damageCooldown = false;
       }  
    }
    
    Serial << mathf.Clamp(sensorValue, 19, 60) << endl;
    DebugUI(sensorValue, buttonPin);
    GameScreenUI();
    player.Draw(Vector2(5, mathf.Clamp(sensorValue, 19, 60)), damageCooldown, OLED);

    OLED.Render();
}

//shows input values, !-for debugging-!
void DebugUI(int sensor, int button)
{
 OLED.PrintToScreen(String(mathf.Clamp(sensor, 19, 60)), Vector2(0,0));
 OLED.PrintToScreen(" ");
 OLED.PrintToScreen(String(digitalRead(button)));
 OLED.PrintToScreen(" ");
 OLED.PrintToScreen(String(player.health));
 OLED.PrintToScreen(" ");
 OLED.PrintToScreen(String(player.damageCooldown));
 OLED.endlg();
}

void GameScreenUI()
{
    OLED.Line(Vector2(0,16), Vector2(122,16));
    OLED.Line(Vector2(0,14), Vector2(122,14));
    OLED.Line(Vector2(122,0), Vector2(122,14));
}
