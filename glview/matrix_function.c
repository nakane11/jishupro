#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "action.h"
#include "tex.h"
#include "matrix_function.h"
#define PI 3.141592653589793

const int N=50; //出現数の上限
int n=0;
Cat cats[50];
GLfloat camera[16];
GLfloat inv[16];

int gluInvertMatrix(const GLfloat m[16], GLfloat invOut[16]) //逆行列
{
    GLfloat inv[16];
    double det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return 0;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return 1;
}

void copyMat(GLfloat *a, GLfloat *b){
    for(int i = 0; i < 16; i++) {
            a[i] = b[i];
    }
}

//内積
void dotMat (GLfloat *a, GLfloat *b){
    GLfloat s[16];
    
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

    copyMat(a, s);
}

void dotMat41 (GLfloat *a, GLfloat *b, GLfloat *ret){
    
    ret[0]=a[0]*b[0]+a[4]*b[1]+a[8]*b[2]+a[12]*b[3];
    ret[1]=a[1]*b[0]+a[5]*b[1]+a[9]*b[2]+a[13]*b[3];
    ret[2]=a[2]*b[0]+a[6]*b[1]+a[10]*b[2]+a[14]*b[3];
    ret[3]=a[3]*b[0]+a[7]*b[1]+a[11]*b[2]+a[15]*b[3];

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

//単位行列
void unitMat(GLfloat *a){
    for (int k = 0; k<16; k++){
        a[k] = 0;
    }
    a[0] = 1;
    a[5] = 1;
    a[10] = 1;
    a[15] = 1;
}

 
void initCat (int num){
   for (int i=0; i<num; i++){
       // double s = 0;
       // while(s<3*i){
           cats[i].x = rand()%40-20;
           cats[i].y = 0.0;
           cats[i].z = -rand()%20;
           // s = 0;
           // for (int j = i-1; j>=0; j--){
           //     s+=fmin(catsDistance(i, j),3);
           // }
       // }
      
       // for (int j = i-1; j>=0; j--){
       //     while (catsDistance(i, j) < 4.0){
       //             cats[i].y+=1;
       //     }
       // }
       cats[i].scale = 1.0;
       cats[i].r = (rand()%100)/100.0;
       cats[i].g = (rand()%100)/100.0;
       cats[i].b = (rand()%100)/100.0;
       cats[i].neck_angle = 0.0;
       cats[i].task = STAY;
       cats[i].duration = 0;
       cats[i].flg = 0;
      
       unitMat(cats[i].matrix);
 
       MatArray array1, array2;
       array1 = tlMat(cats[i].x, cats[i].y, cats[i].z);
       array2 = y_rtMat(rand()%360-180.0);
       dotMat(array2.matrix, array1.matrix);
       dotMat( cats[i].matrix,array2.matrix);
      
   }
   n = num;
  
}

void addCat(int i, int j){
   if(n<N){
       cats[n].x = (cats[i].x+cats[j].x)/2.0;
       cats[n].y = 0.0;
       cats[n].z = (cats[i].z+cats[j].z)/2.0;
       cats[n].scale = 0.6;
       cats[n].r = (cats[i].r+cats[j].r)/2.0;
       cats[n].g = (cats[i].g+cats[j].g)/2.0;
       cats[n].b = (cats[i].b+cats[j].b)/2.0;
       cats[n].neck_angle = 0.0;
       cats[n].task = STAY;
       cats[n].duration = 0;
       cats[i].flg = 0;
       
       unitMat(cats[n].matrix);
 
       MatArray array1, array2;
       array1 = tlMat(cats[n].x, cats[n].y, cats[n].z);
       array2 = y_rtMat(rand()%360-180.0);
       dotMat(array2.matrix, array1.matrix);
       dotMat( cats[n].matrix,array2.matrix);

       cats[i].flg=0;
       cats[j].flg=0;
       //printf("%d -> (%lf, %lf, %lf)\n",n, cats[n].x,cats[n].y,cats[n].z);
       n+=1;
   }
}
 

 
void myUnProject(GLfloat winX, GLfloat winY, GLfloat winZ,
	            GLfloat *model, GLfloat *proj, GLint *view,
	            GLfloat* objX, GLfloat* objY, GLfloat* objZ)
{
    dotMat(model, proj);
    GLfloat invPM[16];
    gluInvertMatrix(model, invPM);

    GLfloat invVp[4] = {2 * (winX - view[0]) / view[2] - 1.0 ,
                        2 * (winY - view[1]) / view[3] - 1.0 ,
                        2 * winZ - 1.0,
                        1};
    GLfloat V[4];
    dotMat41(invPM, invVp, V);

    *objX = V[0] / V[3];
    *objY = V[1] / V[3];
    *objZ = V[2] / V[3];

}
