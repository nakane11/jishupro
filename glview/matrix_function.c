#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>

#include "action.h"
#include "tex.h"

#define PI 3.141592653589793

typedef struct {
    double x, y, z, scale, r, g, b;
    int neck_angle, state, task, duration, face;
    GLfloat matrix[16];
} Cat;

typedef struct { GLfloat matrix[16]; } MatArray;

const int N=50; //出現数の上限
int n=0; //現在のねこの出現数
Cat cats[50];

//内積
void dotMat (GLfloat *s, GLfloat *b){
    GLfloat a[16];
    for(int i = 0; i < 16; i++) {
        a[i] = s[i];
    }
    
    s[0]=a[0]*b[0]+a[4]*b[1]+a[8]*b[2]+a[12]*b[3];
    s[1]=a[1]*b[0]+a[5]*b[1]+a[9]*b[2]+a[13]*b[3];
    s[2]=a[2]*b[0]+a[6]*b[1]+a[10]*b[2]+a[14]*b[3];
    s[3]=a[3]*b[0]+a[7]*b[1]+a[11]*b[2]+a[15]*b[3];

    s[4]=a[0]*b[4]+a[4]*b[5]+a[8]*b[6]+a[12]*b[7];
    s[5]=a[1]*b[4]+a[5]*b[5]+a[9]*b[6]+a[13]*b[7];
    s[6]=a[2]*b[4]+a[6]*b[5]+a[10]*b[6]+a[14]*b[7];
    s[7]=a[3]*b[4]+a[7]*b[5]+a[11]*b[6]+a[15]*b[7];

    s[8]=a[0]*b[8]+a[4]*b[9]+a[8]*b[10]+a[12]*b[11];
    s[9]=a[1]*b[8]+a[5]*b[9]+a[9]*b[10]+a[13]*b[11];
    s[10]=a[2]*b[8]+a[6]*b[9]+a[10]*b[10]+a[14]*b[11];
    s[11]=a[3]*b[8]+a[7]*b[9]+a[11]*b[10]+a[15]*b[11];

    s[12]=a[0]*b[12]+a[4]*b[13]+a[8]*b[14]+a[12]*b[15];
    s[13]=a[1]*b[12]+a[5]*b[13]+a[9]*b[14]+a[13]*b[15];
    s[14]=a[2]*b[12]+a[6]*b[13]+a[10]*b[14]+a[14]*b[15];
    s[15]=a[3]*b[12]+a[7]*b[13]+a[11]*b[14]+a[15]*b[15];


}

//y軸回転
MatArray y_rtMat(double angle){
    double rad = angle * PI / 180.0;
    MatArray m = {{cos(rad), 0, -sin(rad), 0,
                    0, 1, 0, 0,
                    sin(rad), 0, cos(rad), 0,
                    0, 0, 0, 1}};
    return m;
}

//平行移動
MatArray tlMat(double x, double y, double z){
    MatArray m = {{1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    x, y, z, 1}};
    return m;
}

void initCat (int num){
    srand((unsigned int)time(NULL));
    for (int i=0; i<num; i++){
        double s = 0;
        while(s<3*i){
            cats[i].x = rand()%40-20;
            cats[i].y = 0.0;
            cats[i].z = -rand()%20;
            s = 0;
            for (int j = i-1; j>=0; j--){
                s+=fmin(catsDistance(i, j),3);
            }
        }
        
        for (int j = i-1; j>=0; j--){
            while (catsDistance(i, j) < 4.0){
                    cats[i].y+=1;
            }
        }
        cats[i].scale = 1.0;
        cats[i].r = (rand()%100)/100.0;
        cats[i].g = (rand()%100)/100.0;
        cats[i].b = (rand()%100)/100.0;
        cats[i].neck_angle = 0.0;
        cats[i].face = NORMAL;
        cats[i].task = EAT;
        cats[i].duration = 0;
        
    
        for (int k = 0; k<16; k++){
            cats[i].matrix[k] = 0;
        }
        cats[i].matrix[0] = 1;
        cats[i].matrix[5] = 1;
        cats[i].matrix[10] = 1;
        cats[i].matrix[15] = 1;



        MatArray array1, array2;
        array1 = tlMat(cats[i].x, cats[i].y, cats[i].z);
        //printf("%f %f %f %f\n",array1.matrix[12],array1.matrix[13],array1.matrix[14],array1.matrix[15]);
        array2 = y_rtMat(rand()%360-180.0);
        dotMat(array2.matrix, array1.matrix);
        //printf("%f %f %f %f\n",array1.matrix[12],array1.matrix[13],array1.matrix[14],array1.matrix[15]);
        dotMat( cats[i].matrix,array2.matrix);
        // printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n\n",
        // cats[i].matrix[0],cats[i].matrix[1],cats[i].matrix[2],cats[i].matrix[3],
        // cats[i].matrix[4],cats[i].matrix[5],cats[i].matrix[6],cats[i].matrix[7],
        // cats[i].matrix[8],cats[i].matrix[9],cats[i].matrix[10],cats[i].matrix[11],
        // cats[i].matrix[12],cats[i].matrix[13],cats[i].matrix[14],cats[i].matrix[15]);
        
    }
    n = num;
    
    
    //関数のテスト用
    // MatArray tarray1, tarray2;
    // tarray1 = tlMat(cats[0].x, cats[0].y, cats[0].z);
    // tarray2 = y_rtMat(90);
    // printf("x=%lf, y=%lf, z=%lf, angle=%lf\n",cats[0].x,cats[0].y,cats[0].z,angle);
    // for(int i=0;i<16;i++){
    //     printf("%lf, \n",tarray1.matrix[i]);
    // }
    // dotMat(tarray2.matrix, tarray1.matrix);
    // for(int i=0;i<16;i++){
    //     printf("%lf, \n",tarray2.matrix[i]);
    // }
    
}