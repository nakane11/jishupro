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
  if(digitalRead(ButtonJR) == LOW){
    //マウスクリック
//     Keyboard.print(32);
    delay(100);
    while(digitalRead(ButtonS) == LOW);
  }
  
  if(digitalRead(ButtonCR) == LOW){
    Keyboard.print("r");
    delay(100);
    while(digitalRead(ButtonCR) == LOW);
  }
    
  if(digitalRead(ButtonCG) == LOW){
    Keyboard.print("g");
    delay(100);
    while(digitalRead(ButtonCG) == LOW);
  }
  
  if(digitalRead(ButtonCB) == LOW){
    Keyboard.print("b");
    delay(100);
    while(digitalRead(ButtonCB) == LOW);
  }
  
  if(digitalRead(ButtonN) == LOW){
    Keyboard.print("n");
    delay(100);
    while(digitalRead(ButtonN) == LOW);
  }
  
  if(digitalRead(ButtonS) == LOW){
    Keyboard.print(32);
    delay(100);
    while(digitalRead(ButtonS) == LOW);
  }
  
  if(digitalRead(ButtonZ) == LOW){
    Keyboard.print("z");
    delay(100);
  }
  
  if(digitalRead(ButtonX) == LOW){
    Keyboard.print("x");
    delay(100);
  }

  delay(100);
}
