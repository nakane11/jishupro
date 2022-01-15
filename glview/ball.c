#include <GL/glut.h>
#include <stdio.h>

#include "ball.h"

double ball_speed = 0.1; //0.1~1.0

void drawBall(){
    static int s = 1;
    glPushMatrix();
  {
    GLfloat color[] = { 255.0/255, 25.0/255/ ball_speed, 10.0/255/ ball_speed, 1.0 }; //彩度変更
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    glTranslated(0, 0.5, 0);
    glutSolidSphere(1.3,32,32);
    ball_speed += s*0.1/12;
    if(ball_speed >= 0.6){
        s = -1;
    }else if (ball_speed <= 0.1){
        s = 1;
    }
  }glPopMatrix();
}