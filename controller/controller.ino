#include "Keyboard.h"
#include "Mouse.h"

//=================================================
//digital
#define ButtonJL 3
#define ButtonCG 4
#define ButtonCB 5
#define ButtonCR 6
#define ButtonX 7
#define ButtonN 8
#define ButtonZ 9
#define ButtonP 10

//analog
#define StickLX A0 
#define StickLY A1
#define StickRX A2
#define StickRY A3 

//=================================================
signed char get_mouse_amount(int val)
{
    signed char amount[16] = { -6, -4, -2, -2, -2, -1, -1,  0,
                                0,  1,  1,  2,  2,  2,  4,  6 };
    unsigned int range = ((unsigned int)val&0x03ff) / 64;
    return amount[range];
}

void setup() {
//  Serial.begin(9600);
  Keyboard.begin();
  Mouse.begin();
  
  pinMode(ButtonJL, INPUT_PULLUP);
  pinMode(ButtonCG, INPUT_PULLUP);
  pinMode(ButtonCB, INPUT_PULLUP);
  pinMode(ButtonCR, INPUT_PULLUP);
  pinMode(ButtonX, INPUT_PULLUP);
  pinMode(ButtonN, INPUT_PULLUP);
  pinMode(ButtonZ, INPUT_PULLUP);
  pinMode(ButtonP, INPUT_PULLUP);
  
  pinMode(StickLX, INPUT); 
  pinMode(StickLY, INPUT); 
  pinMode(StickRX, INPUT); 
  pinMode(StickRY, INPUT); 
}

void loop() {
  //右ジョイスティック
    int rx_reading = 0;        /* analogRead()の戻り値を格納する */
    int ry_reading = 0;        /* analogRead()の戻り値を格納する */
    signed char x_amount = 0; /* Mouse.move()の xの値を格納する */
    signed char y_amount = 0; /* Mouse.move()の yの値を格納する */

    rx_reading = analogRead(StickRX);
    ry_reading = analogRead(StickRY);
    x_amount =- 3*get_mouse_amount(rx_reading);
    y_amount = -3*get_mouse_amount(ry_reading);
    if( x_amount || y_amount )
    {
        Mouse.move(x_amount, y_amount, 0);
        delay(10);
    }

   //左ジョイスティック
   int lx_reading = 0;        /* analogRead()の戻り値を格納する */
   int ly_reading = 0; 
   lx_reading = analogRead(StickLX);
   ly_reading = analogRead(StickLY);
     
//   Serial.println(lx_reading);
//    delay(100);
//   
   if((ly_reading-524)>200){
    Keyboard.print("s");
    delay(10);
   }else if((ly_reading-524)<-200){
    Keyboard.print("w");
    delay(10);
   }

   if((lx_reading-501)>200){
    Keyboard.print("d");
    delay(10);
   }else if((lx_reading-501)<-200){
    Keyboard.print("a");
    delay(10);
   }
   
   
  
  if(digitalRead(ButtonJL) == LOW){
    //マウスクリック
    Mouse.click(MOUSE_LEFT);
    delay(80);
    while(digitalRead(ButtonJL) == LOW);
  }
  
  if(digitalRead(ButtonCR) == LOW){
    Keyboard.print("r");
    delay(80);
    while(digitalRead(ButtonCR) == LOW);
  }
    
  if(digitalRead(ButtonCG) == LOW){
    Keyboard.print("g");
    delay(80);
    while(digitalRead(ButtonCG) == LOW);
  }
  
  if(digitalRead(ButtonCB) == LOW){
    Keyboard.print("b");
    delay(80);
    while(digitalRead(ButtonCB) == LOW);
  }
  
  if(digitalRead(ButtonN) == LOW){
    Keyboard.print("n");
    delay(80);
    while(digitalRead(ButtonN) == LOW);
  }
  
  if(digitalRead(ButtonP) == LOW){
    Keyboard.print("p");
    delay(50);
    while(digitalRead(ButtonP) == LOW);
  }
  
  if(digitalRead(ButtonZ) == LOW){
    Keyboard.print("z");
    delay(30);
  }
  
  if(digitalRead(ButtonX) == LOW){
    Keyboard.print("x");
    delay(20);
  }

  delay(10);
}
