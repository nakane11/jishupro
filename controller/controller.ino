#include "Keyboard.h"

//=================================================
//digital
//#define ButtonJL 2
#define ButtonJR 3
#define ButtonCG 4
#define ButtonCR 5
#define ButtonCB 6
#define ButtonN 7
#define ButtonX 8
#define ButtonZ 9
#define ButtonS 10

//analog
#define StickLX A0 
#define StickLY A1
#define StickRX A2
#define StickRY A3 

//=================================================

void setup() {
  Keyboard.begin();
  
  //pinMode(ButtonJL, INPUT_PULLUP);
  pinMode(ButtonJR, INPUT_PULLUP);
  pinMode(ButtonCR, INPUT_PULLUP);
  pinMode(ButtonCG, INPUT_PULLUP);
  pinMode(ButtonCB, INPUT_PULLUP);
  pinMode(ButtonN, INPUT_PULLUP);
  pinMode(ButtonX, INPUT_PULLUP);
  pinMode(ButtonZ, INPUT_PULLUP);
  pinMode(ButtonS, INPUT_PULLUP);
  
  pinMode(StickLX, INPUT); 
  pinMode(StickLY, INPUT); 
  pinMode(StickRX, INPUT); 
  pinMode(StickRX, INPUT); 
}

void loop() {
  if(digitalRead(ButtonJL) == LOW){
    Keyboard.print("Arduino operating time ");
    Keyboard.write(','); //
    Keyboard.print(millis());
    Keyboard.write('\n');
    delay(100);

    while(digitalRead(ButtonJL) == LOW);
  }

  delay(100);
}
