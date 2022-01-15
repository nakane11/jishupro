#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "ball.h"
#include "matrix_function.h"

double ball_speed = 0.1; //0.1~0.6
int ball_phase = 0;
double ball_pos[3];
double ball_endpos[3]; 
double g = 10.0;
double Y0, v0, t, t1;
GLfloat start_position_matrix[16];

void ball_change_speed(){
    static int s = 1;
    ball_speed += s*0.1/12;
    if(ball_speed >= 0.6){
        s = -1;
    }else if (ball_speed <= 0.1){
        s = 1;
    }
}

void ball_pos_update(){
    if(ball_phase == 0 || ball_phase == 1){
        ball_pos[0] = 0.5*inv[4]+inv[12];
        ball_pos[1] = 0.5*inv[5]+inv[13];
        ball_pos[2] = 0.5*inv[6]+inv[14];
    }else if(ball_phase == 2){
        t += 0.02;
        double X = v0*t;
        double Y = Y0 + v0*t - g*t*t/2.0;
        //最初のカメラ座標で(0, Y, X)を世界座標に変換
        ball_pos[0] = Y*start_position_matrix[4] + X*start_position_matrix[8] + start_position_matrix[12];
        ball_pos[1] = Y*start_position_matrix[5] + X*start_position_matrix[9] + start_position_matrix[13];
        ball_pos[2] = Y*start_position_matrix[6] + X*start_position_matrix[10] + start_position_matrix[14];
        if(t>t1 && ball_pos[1]<=0.65){
            if(abs(ball_pos[0])>=61 || abs(ball_pos[2])>=61){
                ball_phase = 4;
            }else{
                ball_pos[1] = 0.65;
                ball_phase = 3;
            }
        } 
    }else if(ball_phase == 4){
        t += 0.02;
        double X = v0*t;
        double Y = Y0 + v0*t - g*t*t/2.0;
        //最初のカメラ座標で(0, Y, X)を世界座標に変換
        ball_pos[0] = Y*start_position_matrix[4] + X*start_position_matrix[8] + start_position_matrix[12];
        ball_pos[1] = Y*start_position_matrix[5] + X*start_position_matrix[9] + start_position_matrix[13];
        ball_pos[2] = Y*start_position_matrix[6] + X*start_position_matrix[10] + start_position_matrix[14];
        if(ball_pos[1]<-30){
            ball_phase =5;
        }
  
    }
}

void drawBall(){
    if(ball_phase != 3 && ball_phase != 5)
        ball_pos_update();
    if(ball_phase !=5){
        glPushMatrix();{
            GLfloat color[] = { 255.0/255, 25.0/255/ ball_speed, 10.0/255/ ball_speed, 1.0 }; //彩度変更
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
            glTranslated(ball_pos[0], ball_pos[1], ball_pos[2]);
            glutSolidSphere(1.3,32,32);
        }glPopMatrix();
    }
}

void ball_calc(){
    t = 0.0;
    Y0 = 0.5; 
    v0 = 9+50.0/5*(ball_speed-0.1);
    double X1 = (v0*v0/g + sqrt((v0*v0/g)*(v0*v0/g)+4*v0*v0*Y0/g))/2.0;
    t1 = sqrt(2)*X1/v0;
    copyMat(start_position_matrix, inv);
    
    ball_endpos[0] = X1*inv[8] + inv[12];
    ball_endpos[1] = 0.0;
    ball_endpos[2] = X1*inv[10] + inv[14];
}

