#include <Streaming.h>
#include <iomanip>
#include <iostream>
#include "Vector2.h"
int buttonPin = D4;
int ledPin = D3;
#include "Graphics.h"
Graphics OLED;

#include "Player.h"
Player player;

#include "Enemy.h"
Enemy enemies[50];

#include "Math.h"
Math mathf;
#include <InvertedTM1638.h>
#include <TM1638.h>
#include <TM1638QYF.h>
#include <TM1640.h>
#include <TM16XX.h>
#include <TM16XXFonts.h>
#define TM1638_STB D5
#define TM1638_CLK D6
#define TM1638_DIO D7
TM1638 module(TM1638_DIO, TM1638_CLK, TM1638_STB);
byte buttons;


#include <Servo.h>

Servo myservo;

void DebugUI(int sensor, int button);
void GameScreenUI();
void MenuUI();
void extBoardLEDsForward();
void extBoardLEDsBackward();
void spawnEnemies();
bool damageCooldown = false;

void setup()
{
 Serial.begin(115200);
 OLED.blah();
 module.clearDisplay();
 module.setupDisplay(true, 2);

 
 myservo.attach(D0);
 myservo.write(20);
 pinMode(buttonPin, INPUT_PULLUP);
 pinMode(ledPin, OUTPUT);
}

void servoHealth()
{
    switch(player.health)
    {
        case 3:
            myservo.write(20);
            break;
        case 2:
            myservo.write(60);
            break;
        case 1:
            myservo.write(120);
            break;
        case 0:
            myservo.write(190);
            break;
    }

}

void ledSwitch()
{
    if(digitalRead(buttonPin) == 0)
    {
        digitalWrite(ledPin, HIGH);
    } 
    else
    {
        digitalWrite(ledPin, LOW);
    }
    
}
bool menuEnd = false;
void loop()
{
    servoHealth();
    
    OLED.Clear();
    ledSwitch();
    switch(menuEnd)
    {
        case true:
            if(player.health > 0)
            {
                GameLoop();
            }
            else
            {
                myservo.write(190);
                buttons = module.getButtons();
                OLED.PrintToScreen("Your score was: ", Vector2(0, 8));
                OLED.PrintToScreen(String(player.score));
                OLED.endlg();
                OLED.endlg();
                OLED.PrintToScreen("Press S1 on the");
                OLED.endlg();
                OLED.PrintToScreen("expansion board to");
                OLED.endlg();
                OLED.PrintToScreen("play again");
                if(buttons == 0x0001)
                {
                    menuEnd = false;
                    player.health = 3;
                    player.score = 0;
                    for(int i = 0; i < 50; i++)
                    {
                        enemies[i].Destroy();
                    }
                    module.setDisplayToDecNumber(player.score, 0, false);
                }
            }
            
            
            break;
        case false:
            MenuUI();
            break;
    }
    
    OLED.Render();
}

void GameLoop()
{
    
    module.setDisplayToDecNumber(player.score, 0, false);
    int sensorValue = analogRead(A0) / 10.24;
    player.Update(digitalRead(buttonPin), OLED);
    spawnEnemies();
    for(int i = 0; i < 50; i++)
    {
        switch(enemies[i].isActive)
        {
            case true:

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
                break;
            case false:
                break;
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
        extBoardLEDsForward();
    }
    else
    {
        OLED.PrintToScreen("  Start Game", Vector2(32,21));
        OLED.PrintToScreen("> Credits", Vector2(37,35));
        menuEnd = false;
        extBoardLEDsBackward();
    }

}

int ledPos = 0;

void extBoardLEDsForward()
{
    if(ledPos > 0)
        module.setLED(TM1638_COLOR_NONE, ledPos - 1);
        
        if(ledPos == 8)
        ledPos = 0;

        module.setLED(TM1638_COLOR_RED, ledPos);
        ledPos++;
}

void extBoardLEDsBackward()
{
    if(ledPos < 7)
         module.setLED(TM1638_COLOR_NONE, ledPos + 1);
        
        if(ledPos == -1)
            ledPos = 7;

        module.setLED(TM1638_COLOR_RED, ledPos);
        ledPos--;
}


int difficulty = 2;
int lowerend = 1;
void spawnEnemies()
{
    int randNum = random(0, 101);

    if(player.score > 100)
    {
        lowerend = 1;
        difficulty = 3;
    }
    else if (player.score > 1000)
    {
        lowerend = 2;
        difficulty = 4;
    }
    else if (player.score > 2500)
    {
        lowerend = 3;
        difficulty = 5;
    }
    else if (player.score > 5000)
    {
        lowerend = 4;
        difficulty = 5;
    }
    else if (player.score > 7500)
    {
        lowerend = 4;
        difficulty = 6;
    }
    else if (player.score > 10000)
    {
        lowerend = 5;
        difficulty = 6;
    }
    else if (player.score > 15000)
    {
        lowerend = 8;
        difficulty = 15;
    }

    if(randNum > 75)
    {
        for(int i = 0; i < 50; i++)
        {
            if(!enemies[i].isActive)
            {
                enemies[i].Setup(Vector2(128,random(16,64)), random(lowerend,difficulty), random(0, 2));
                i++;
                break;
            }
        }     
    }
}