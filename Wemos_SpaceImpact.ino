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
void MenuUI();
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

bool menuEnd = false;
void loop()
{
    OLED.Clear();

    switch(menuEnd)
    {
        case true:
            GameLoop();
            break;
        case false:
            MenuUI();
            break;
    }
    
    OLED.Render();
}

void GameLoop()
{
    
    int sensorValue = analogRead(A0) / 10.24;
    player.Update(digitalRead(buttonPin), OLED);
    
    for(int i = 0; i < 5; i++)
    {
        enemies[i].Update(OLED, player);
        if(damageCooldown == false)
        {
           if(enemies[i].HasCollided(player.position))
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
}

//shows input values, !-for debugging-!
void DebugUI(int sensor, int button)
{
 OLED.PrintToScreen(String(player.score), Vector2(0,5));
 OLED.endlg();
}

void GameScreenUI()
{
    switch(player.health)
    {
        case 3:
            OLED.Circle(Vector2(90,7), 3, true);
            OLED.Circle(Vector2(98,7), 3, true);
            OLED.Circle(Vector2(106,7), 3, true);
            break;
        case 2:
            OLED.Circle(Vector2(90,7), 3, true);
            OLED.Circle(Vector2(98,7), 3, true);
            break;
        case 1:
            OLED.Circle(Vector2(90,7), 3, true);
            break;
        default:
            break;
    }
    
    OLED.Line(Vector2(0,16), Vector2(122,16));
    OLED.Line(Vector2(0,14), Vector2(122,14));
    OLED.Line(Vector2(122,0), Vector2(122,14));
}


void MenuUI()
{
    int sensorValue = analogRead(A0) / 10.24;
    OLED.Circle(Vector2(40,35), 50, false);
    OLED.PrintToScreen("SPACE", Vector2(5,0));
    OLED.PrintToScreen("IMPACT", Vector2(20,8));
    OLED.Line(Vector2(0,15), Vector2(110,15));
    if(sensorValue > 50)
    {
        OLED.PrintToScreen("> Start Game", Vector2(37,21));
        OLED.PrintToScreen("  Credits", Vector2(32,35));
        if(digitalRead(buttonPin) == 0)
        {
            menuEnd = true;
        }
    }
    else
    {
        OLED.PrintToScreen("  Start Game", Vector2(32,21));
        OLED.PrintToScreen("> Credits", Vector2(37,35));
        menuEnd = false;
    }

    
    
    
}