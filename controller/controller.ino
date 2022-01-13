#include "Keyboard.h"
#include "Mouse.h"

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
signed char get_mouse_amount(int val)
{
    signed char amount[16] = { -8, -4, -2, -2, -2, -1, -1,  0,
                                0,  1,  1,  2,  2,  2,  4,  8 };
    unsigned int range = ((unsigned int)val&0x03ff) / 64;
    return amount[range];
}

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  Mouse.begin();
  
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
  pinMode(StickRY, INPUT); 
}

void loop() {
  //右ジョイスティック
    int rx_reading = 0;        /* analogRead()の戻り値を格納する */
    int ry_reading = 0;        /* analogRead()の戻り値を格納する */
    signed char x_amount = 0; /* Mouse.move()の xの値を格納する */
    signed char y_amount = 0; /* Mouse.move()の yの値を格納する */

    rx_reading = - (analogRead(StickRX)+12);
    ry_reading = - analogRead(StickRY);
    x_amount = 5*get_mouse_amount(rx_reading);
    y_amount = 5*get_mouse_amount(ry_reading);
//    Serial.println(ry_reading);
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
   
   if((ly_reading-521)>200){
    Keyboard.print("s");
    delay(50);
   }else if((ly_reading-521)<-200){
    Keyboard.print("w");
    delay(50);
   }

   if((lx_reading-507)>200){
    Keyboard.print("d");
    delay(50);
   }else if((lx_reading-507)<-200){
    Keyboard.print("a");
    delay(50);
   }
   
   
  
  if(digitalRead(ButtonJR) == LOW){
    //マウスクリック
    Mouse.click(MOUSE_LEFT);
    delay(100);
    while(digitalRead(ButtonJR) == LOW);
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
    Keyboard.print("s");
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

  delay(10);
}
