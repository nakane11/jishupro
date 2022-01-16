#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "ball.h"
#include "matrix_function.h"
#include "action.h"

double ball_speed = 0.1; //0.1~0.6
int ball_phase = 0;
double ball_pos[3];
double ball_endpos[3]; 
double g = 10.0;
double Y0, v0, t, t1;
GLfloat start_position_matrix[16];
int chase_num = 0;


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
        if(t>t1 && ball_pos[1]<=0.5){
            if(abs(ball_pos[0])>=61 || abs(ball_pos[2])>=61){
                ball_phase = 4;
            }else{
                ball_pos[1] = 0.5;
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
  
    }else if(ball_phase == 6){
        ball_pos[0] = cats[chase_num].x;
        ball_pos[1] = cats[chase_num].y;
        ball_pos[2] = cats[chase_num].z;
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
            glutSolidSphere(1.0,32,32);
        }glPopMatrix();
    }
}

void ball_calc(){
    t = 0.0;
    Y0 = 0.5; 
    v0 = 12+50.0/5*(ball_speed-0.1);
    double X1 = (v0*v0/g + sqrt((v0*v0/g)*(v0*v0/g)+4*v0*v0*Y0/g))/2.0;
    t1 = sqrt(2)*X1/v0;
    copyMat(start_position_matrix, inv);
    
    ball_endpos[0] = X1*inv[8] + inv[12];
    ball_endpos[1] = 0.0;
    ball_endpos[2] = X1*inv[10] + inv[14];
}

void ball_reset_chase(){
    if(cats[chase_num].task == CHASE)
        cats[chase_num].task = STAY;
}

double my_min(double x, double y){
    if(abs(x)>=abs(y))
        return y;
    else
        return x;
}
void  ball_update_cat(){
    int i = chase_num;
    GLfloat m[16];
    gluInvertMatrix(cats[i].matrix, m);
    

    if(ball_phase == 1){
        //体をボールの方へ向ける
        double x = 0*inv[8]+inv[12]-cats[i].x;
        double z = 0*inv[10]+inv[14]-cats[i].z;
        double camerarel_x = m[0]*x+m[8]*z+m[12];
        //printf("%f\n",rel_x);
        MatArray rtarray;
        if(camerarel_x>0.1){
            //右回転
            rtarray = y_rtMat(0.7);
            dotMat( cats[i].matrix, rtarray.matrix);
        }else if(camerarel_x<-0.1){
            //左回転
            rtarray = y_rtMat(-0.7);
            dotMat( cats[i].matrix, rtarray.matrix);
        }
    }else if(ball_phase == 2 || ball_phase == 3){
        //ボールを取りに行く
        double x = ball_pos[0]-cats[i].x; //世界座標
        double z = ball_pos[2]-cats[i].z;
        double ballrel_x = m[0]*x+m[8]*z+m[12];
        double ballrel_z = m[2]*x+m[10]*z+m[14]; //ねこ座標
        
        MatArray tlarray, rtarray;
        double d = (ball_pos[0]-cats[i].x)*(ball_pos[0]-cats[i].x)+(ball_pos[2]-cats[i].z)*(ball_pos[2]-cats[i].z);
        if(ballrel_x>0.1){
            //右回転
            rtarray = y_rtMat(my_min((ballrel_x-0.1)*10, 0.4));
            dotMat( cats[i].matrix, rtarray.matrix);
        }else if(ballrel_x<-0.1){
            //左回転
            rtarray = y_rtMat(my_min((-0.1-ballrel_x)*10,-0.4));
            dotMat( cats[i].matrix, rtarray.matrix);
        }else if(ballrel_z<-0.06){
            rtarray = y_rtMat(6.0);
            dotMat( cats[i].matrix, rtarray.matrix);
        }else if(ballrel_z>0){
            tlarray = tlMat(0, 0, 0.08);
            dotMat( cats[i].matrix, tlarray.matrix);
            
        }else{
            // tlarray = tlMat(0, 0, 5.0);
            // dotMat( cats[i].matrix, tlarray.matrix);
            ball_phase = 6;
        }
        //printf("(%f, %f),(%f, %f)\n", ball_pos[0],ball_pos[2], ball_endpos[0], ball_endpos[2]);
        //printf("%d, %f\n",ball_phase, ballrel_x);
    }else if(ball_phase == 6){
        double x = inv[12]-cats[i].x; //世界座標
        double z = inv[14]-cats[i].z;
        double camerarel_x = m[0]*x+m[8]*z+m[12];
        double camerarel_z = m[2]*x+m[10]*z+m[14]; //ねこ座標

        MatArray tlarray, rtarray;
        if(camerarel_x>0.1){
            //右回転
            rtarray = y_rtMat(0.6);
            dotMat( cats[i].matrix, rtarray.matrix);
        }else if(camerarel_x<-0.1){
            //左回転
            rtarray = y_rtMat(-0.6);
            dotMat( cats[i].matrix, rtarray.matrix);
        }else if(camerarel_z<-0.1){
            rtarray = y_rtMat(6.0);
            dotMat( cats[i].matrix, rtarray.matrix);
        }else if(camerarel_z>0.5){
            tlarray = tlMat(0, 0, 0.08);
            dotMat( cats[i].matrix, tlarray.matrix);
        }else{
            // tlarray = tlMat(0, 0, 5.0);
            // dotMat( cats[i].matrix, tlarray.matrix);
            
            ball_reset_chase();
            ball_phase = 0;
        }
    }
    
    
    
}

void ball_update_chase(){
    double min = 60*60*2;
    for(int i = 0; i<n; i++){
        double d = (cats[i].x-inv[12])*(cats[i].x-inv[12])+(cats[i].z-inv[14])*(cats[i].z-inv[14]);
        if(d<min){
          min = d;
          chase_num = i;
        }
      }
    cats[chase_num].task = CHASE;
    cats[chase_num].neck_angle = -30.0;
}



