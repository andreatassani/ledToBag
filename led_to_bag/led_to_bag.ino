//Authors: Tassani Andrea && Torroni Michele

#include <stdlib.h>
#include <arduino.h>
#include "function.h"

#define TS_PIN 2
#define TD_PIN 4
#define POT_PIN A0

extern int randLed;
extern int difficulty;
extern int startGame;
extern int pushes;
extern int score;
extern int fadeAmount;
extern int currIntensity;
extern int timeToPlay;
extern int pinLed[5];

void setup() {
  pinMode(pinLed[1], OUTPUT);
  pinMode(pinLed[2], OUTPUT); 
  pinMode(pinLed[3], OUTPUT);
  pinMode(pinLed[0], OUTPUT);
  pinMode(pinLed[4], OUTPUT);
  pinMode(TS_PIN, INPUT);
  pinMode(TD_PIN, INPUT);    
  pinMode(POT_PIN, INPUT);
  
  difficulty = 0;
  startGame = 0;
  pushes = 0;
  score = 0;
  currIntensity = 0;
  fadeAmount = 5;
  timeToPlay = 0;
  randLed = 0;

  Serial.begin(9600);
  Serial.println("Welcome to Led to Bag. Press Key TS to startGame");
}  

void loop() {
//DIFFICULTY FROM POTENTIOMETER && INITIAL BLINKING
  int potVal = analogRead(POT_PIN);
  difficulty = potVal/127;
  if(difficulty == 8) difficulty = 7;
  if(startGame == 0) initialBlinking();
//START OF THE GAME
  if (startGame != 1 && digitalRead(TS_PIN) == HIGH){
    startGame = 1;
    Serial.println("Go!");
    Serial.print("Difficulty: ");
    Serial.print(difficulty+1);
    Serial.print("\n");
    timeToPlay = (8-difficulty)*9;
  }
//LOGIC OF THE GAME
  if(startGame == 1){
    delay(1000);
    pushes = 0;
    randLed = (rand()/(RAND_MAX/3))+1;
    bringToWhite(randLed);
    if(pushes == randLed) win();
    else if(randLed != 0) lose();
  }  
}
