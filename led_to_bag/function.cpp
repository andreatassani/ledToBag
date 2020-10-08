#include <arduino.h>
#include "function.h"
#define TS_PIN 2
#define TD_PIN 4
#define POT_PIN A0

int randLed = 0;
int difficulty = 0;
int startGame = 0;
int pushes = 0;
int score = 0;
int fadeAmount = 4;
int currIntensity = 0;
int timeToPlay = 0;
int pinLed[5] = {5, 9, 10, 11, 6};

void win(){
  Serial.print("\nAnother object in the bag! Count: ");
  Serial.print(++score);
  Serial.print(" objects\n");
  timeToPlay = (timeToPlay*7)/8;
  light(0,0);
  delay(200);
  for(int i=1; i>=-1; i-=2){
    for(int f = 0; f<50; f++){
      analogWrite(pinLed[0],currIntensity);
      currIntensity = currIntensity + (i*fadeAmount);
      delay(30);
    }
  }
  light(0,0);
}

void lose(){
  for(int i=0; i<=3;i++){
    light(i,0);
  }
  light(4,1);
  Serial.print("\nGAME OVER, SCORE: ");
  Serial.print(score);
  Serial.print("\n\n\n\n");
  delay(2000);
  light(4,0);
  setup();
}

void light(int led, int amount) {
  if(amount == 0) digitalWrite(pinLed[led] , 0);
  else  digitalWrite(pinLed[led] , 255);
}

void initialBlinking() {
  for(int i = 1; i <=3; i++) {
    light(i,1);
    delay(256);
    light(i,0);
  }
  light(2,1);
  delay(256);
  light(2,0);
}

void bringToWhite(int randLed) {
  light(randLed,1);
  for(int i = 0; i<(timeToPlay); i++){
    delay(100);
    if(digitalRead(TD_PIN) == 1) {
      pushes++;
      if(pushes == (randLed-2)){
        light(3,0);
        light(2,1);
      }
      if(pushes == (randLed-1)){
        light(2,0);
        light(1,1);
      }
      if (pushes == randLed) {
        light(1,0);
        light(0,1);
        i = timeToPlay*7/8;
      }
      if (pushes > randLed) {
        light(0,0);
        lose();
        pushes = 4;
      }
      delay(100);
      while (digitalRead(TD_PIN) == 1) {
        i++;
        if(i>=timeToPlay){
          lose();
          pushes = 4; //escape win() with pushes=0=randLed
        }
        delay(100);
      }
    }
  }
}
