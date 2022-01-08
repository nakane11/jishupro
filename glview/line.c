#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

#include "matrix_function.h"
#include "line.h"

#define PI 3.141592653589793

Vector line_vector[30];
int line_vec_num;

int fusion_list[50];
int fusion_num;

static double line_cx, line_cz; //図形重心
static double line_r; //半径

void Circle3D(double radius, double theta, double x, double y, double z)
{
 for (double th1 = 0.0;  th1 <= theta;  th1 = th1 + 1.0)
 {             
  double th2 = th1 + 10.0;
  double th1_rad = th1 / 180.0 * PI; 
  double th2_rad = th2 / 180.0 * PI;

  double x1 = radius * cos(th1_rad);
  double y1 = radius * sin(th1_rad);
  double x2 = radius * cos(th2_rad);
  double y2 = radius * sin(th2_rad);

  glBegin(GL_LINES);   
   glVertex3d( x1+x, y, y1+z );     
   glVertex3d( x2+x, y, y2+z );
  glEnd();
 }
}

double line_distance(int i, int j){
  return (line_vector[i].x-line_vector[j].x)*(line_vector[i].x-line_vector[j].x) 
        +(line_vector[i].z-line_vector[j].z)*(line_vector[i].z-line_vector[j].z);
}

double line_radius(double cx, double cz){
  double sum = 0.0;
  for (int i=0; i<line_vec_num-1; i++){
    sum += (line_vector[i].x-cx)*(line_vector[i].x-cx) 
        +(line_vector[i].z-cz)*(line_vector[i].z-cz);
  }
  
  sum /= (double)line_vec_num;
  return sqrt(sum);
}

void line_init(){
    for (size_t i = 0; i < line_vec_num; ++i) {
        line_vector[i] = (Vector){0, 0, 0};
    }
    line_vec_num=0;
}


int line_isstar(int d){
    // if(line_distance(0,5)<d && line_distance(5,10)<d && line_distance(3,6)<d && line_distance(1,7)<d && line_distance(4,8)<d && line_distance(2,9)<d){
    if(line_distance(0,5)<d){
        return 1;
    }else{
        return 0;
    }
}

void line_calc(){
    //重心を計算
    for(int k = 0; k < line_vec_num; k++){
        line_cx += line_vector[k].x;
        line_cz += line_vector[k].z;
    }
    line_cx /= line_vec_num;  line_cz /= line_vec_num;
    //半径を計算
    line_r = line_radius(line_cx, line_cz);
    
    fusion_num = 0;
   
    for(int i=0; i<n; i++){
        if((cats[i].x - line_cx)*(cats[i].x - line_cx) + (cats[i].z - line_cz)*(cats[i].z - line_cz) <line_r*line_r){
            fusion_list[fusion_num] = i;
            fusion_num ++;
        }
    }
    printf("fu->%d\n", fusion_num);
    
}

void fusionCat(int num){
    cats[n].x = line_cx;
    cats[n].y = 0.0;
    cats[n].z = line_cz;
    cats[n].scale = num;
    cats[n].r = 0.0;
    cats[n].g =0.0;
    cats[n].b =  0.0;
    cats[n].neck_angle = 0.0;
    cats[n].task = 2;
    cats[n].duration = 0;
    cats[n].flg = 0;
    
    unitMat(cats[n].matrix);
    MatArray array = y_rtMat(rand()%360-180.0);
    dotMat(array.matrix, tlMat(cats[n].x, cats[n].y, cats[n].z).matrix);
    dotMat( cats[n].matrix, array.matrix);
    n+=1;
}

int fusion_counter(int update){
    static int count = 0;
    if(update == 1){
        count++;
    }
    if(count==60*7 && fusion_num == 0){
        count = 60*7+600 + 60*2 + 1;
    }
    if(count>60*7+60*10 + 60*2 + 60*2){
        count = 0;
    }
    return count;
}

void fusion_clearColor(){
    int count = fusion_counter(0);
    if(count < 60*7){
        glClearColor (36.0/255*count/60/7, 37.0/255*count/60/7, 1-(1-80.0/255)*count/60/7, 0.0);
    }else if(count < 60*7 + 60*10 + 60*2){
        glClearColor (36.0/255, 37.0/255, 80.0/255, 0.0);
    }else if(count < 60*7 + 60*10 + 60*2 + 60*2){
        double t = (double)(count-(60*7+60*10 + 60*2))/(60*2);
        glClearColor (36.0/255*(1-t), 37.0/255*(1-t), 1.0-(1-t)*(1-80.0/255), 0.0);
    }
}

int fusion_update(){
    int count = fusion_counter(1);
    if(count == 0)
        return 1;

    int d = 600 / (fusion_num + 3);
    if(count < 60*7){
    }
    else if(count < 60*7+600){
        Circle3D(line_r, (double)(count-60*7)*360/600, line_cx, -0.5, line_cz);
        if((count-60*7 + 1) % d == 0){ //ねこを黒くする
            cats[fusion_list[(count-60*7+1)/d -1]].r = 0.0;
            cats[fusion_list[(count-60*7+1)/d -1]].g = 0.0;
            cats[fusion_list[(count-60*7+1)/d -1]].b = 0.0;
        }
    }else if(count == 60*7+600){ 
        Circle3D(line_r, 360, line_cx, -0.5, line_cz);
        for(int i=0; i<fusion_num; i++){
            for(int j=fusion_list[i]-i;j<n;j++){
                    cats[j]=cats[j+1];
                }
                n--; 
        }
        fusionCat(fusion_num);
        cats[n-1].y -= 1.6*cats[n-1].scale;
        dotMat( cats[n-1].matrix, tlMat(0, - 1.6*cats[n-1].scale, 0.0).matrix);
    }else if(count <=60*7+600 + 60*2){
        Circle3D(line_r, 360, line_cx, -0.5, line_cz);
        cats[n-1].y += 1.6*cats[n-1].scale/120; //ねこがせりあがる
        dotMat( cats[n-1].matrix, tlMat(0, 1.6*cats[n-1].scale/120, 0.0).matrix);
    }

    if(count < 60*7+600 && fusion_num>0){ //ねこを上昇させる
        for(int i=0; i<fmin((count-60*7)/d, fusion_num+1); i++){
            cats[fusion_list[i]].y += 0.3;
            dotMat( cats[fusion_list[i]].matrix, tlMat(0, 0.3, 0.0).matrix);
        }
    }
    return 0;
    
}

