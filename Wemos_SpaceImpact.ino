
#include <Streaming.h>
#include <iostream> 

#include "Vector2.h" //custom vector 2 class include

//button and led port definitions
int buttonPin = D4;
int ledPin = D3;

// includes the graphics class created to make using the OLED easier for the programmer to use
#include "Graphics.h"
Graphics OLED;

// includes the custom player class which deals with all player functions
#include "Player.h"
Player player;

// includes the custom enemy class which deals with all the enemies on the screen
#include "Enemy.h"
Enemy enemies[50]; //array defining the max amount of enemies on the screen at once
 
//custom math class
#include "Math.h"
Math mathf;

// Extension board includes and pre-requisites

#include <TM1638.h>

// port definitions for the extension board
#define TM1638_STB D5
#define TM1638_CLK D6
#define TM1638_DIO D7
// Extension board definition
TM1638 module(TM1638_DIO, TM1638_CLK, TM1638_STB);
byte buttons; 

//Servo include and definition
#include <Servo.h>

Servo myservo;

//function prototypes
void DisplayScore();
void GameScreenUI();
void MenuUI();
void extBoardLEDsForward();
void extBoardLEDsBackward();
void spawnEnemies();


bool damageCooldown = false;

void setup()
{
//sets up the Serial port
 Serial.begin(115200);

 //loads up the default splashscreen
 OLED.blah();

//resets and sets up the extension board for usage
 module.clearDisplay();
 module.setupDisplay(true, 7); //sets brightness of seven seg to max

 //attatches the servo to the D0 port and setting it to 20 as the default start
 myservo.attach(D0);
 myservo.write(20);

//sets up the led and button for usage
 pinMode(buttonPin, INPUT_PULLUP);
 pinMode(ledPin, OUTPUT);

}


//changes the servo's position depending on the current health of the player
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

//switches on the LED when the button is pressed
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

bool menuEnd = false; //sets the state of if the player is in the menu or not

//displays the endscreen when the player dies
void EndScreen()
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
    if(buttons == 0x0001)   //if S1 on the extension board is pressed the game is reset
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

//arduino loop function
void loop()
{
    servoHealth();
    
    OLED.Clear();
    ledSwitch();

    //switches if the gameloop should be used or the main menu
    switch(menuEnd)
    {
        case true:
            if(player.health > 0)
            {
                GameLoop();
            }
            else
            {
                EndScreen();
            }
            break;
        case false:
            MenuUI();
            break;
    }
    
    OLED.Render();
}


//main Game Loop
void GameLoop()
{
    
    module.setDisplayToDecNumber(player.score, 0, false); //sets the 7seg display to display the player's current score

    //stores the potentiometer's value into a variable.
    int sensorValue = analogRead(A0) / 10.24;

    player.Update(digitalRead(buttonPin), OLED); //updates the player for this frame
    spawnEnemies();
    //updates the enemies on the screen
    for(int i = 0; i < 50; i++)
    {
        switch(enemies[i].isActive)
        {
            case true:

                enemies[i].Update(OLED, player); //updates all the enemies for this frame

                //checks for collisions
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
    
    //deals with the player's damage cooldown
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
    
    Serial << mathf.Clamp(sensorValue, 19, 60) << endl; //outputs the current value of the potentiometer for debuging purposes

    DisplayScore();
    GameScreenUI();
    
    player.Draw(Vector2(5, mathf.Clamp(sensorValue, 19, 60)), damageCooldown, OLED); //draws the player to the screen parsing through the potentiometer's value
}

//displays the current score onto the OLED
void DisplayScore()
{
 OLED.PrintToScreen(String(player.score), Vector2(0,5));
 OLED.endlg();
}

//display's the game UI
void GameScreenUI()
{

    //displays circles based on the player's current health
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

//displays the main menu UI
void MenuUI()
{
    int sensorValue = analogRead(A0) / 10.24;

    OLED.Circle(Vector2(40,35), 50, false);
    OLED.PrintToScreen("SPACE", Vector2(5,0));
    OLED.PrintToScreen("IMPACT", Vector2(20,8));
    OLED.Line(Vector2(0,15), Vector2(110,15));

    // depending on the value of the potentiometer a menu option is selected
    if(sensorValue > 50)
    {
        OLED.PrintToScreen("> Start Game", Vector2(37,21));
        OLED.PrintToScreen("  Credits", Vector2(32,35));

        // when the main button is pressed the option is selected
        if(digitalRead(buttonPin) == 0)
        {
            //quits the menu
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

//waterfall effect with extension board leds
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


//spawns enemies depending on the player's score (infinitely until the player dies)
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
                enemies[i].Setup(Vector2(128,random(19,60)), random(lowerend,difficulty), random(0, 2)); //spawns enemies
                i++;
                break;
            }
        }     
    }
}