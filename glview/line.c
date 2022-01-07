#include <math.h>

#include "line.h"

Vector line_vector[30];
int line_vec_num;


double line_distance(int i, int j){
  return (line_vector[i].x-line_vector[j].x)*(line_vector[i].x-line_vector[j].x) 
        +(line_vector[i].z-line_vector[j].z)*(line_vector[i].z-line_vector[j].z);
}

double line_radius(double cx, double cz){
  double sum;
  for (int i; i<line_vec_num-1; i++){
    sum += (line_vector[i].x-cx)*(line_vector[i].x-cx) 
        +(line_vector[i].z-cz)*(line_vector[i].z-cz);
  }
  sum /= line_vec_num;
  return sqrt(sum);
}

int line_isstar(int d){
    if(line_distance(0,5)<d && line_distance(5,10)<d && line_distance(3,6)<d && line_distance(1,7)<d && line_distance(4,8)<d && line_distance(2,9)<d){
        return 1;
    }else{
        return 0;
    }
}

void line_culc(){
    double line_cx, line_cz; //図形重心
    double line_r; //半径

    //重心を計算
    for(int k = 0; k < line_vec_num; k++){
    line_cx += line_vector[k].x;
    line_cz += line_vector[k].z;
    }
    line_cx /= line_vec_num;  line_cz /= line_vec_num;
    //半径を計算
    line_r = line_radius(line_cx, line_cz);
    
}
