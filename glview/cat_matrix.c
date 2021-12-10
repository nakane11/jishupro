#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>

#define PI 3.141592653589793

static int N=50; //出現数の上限
int n=0; //現在のねこの出現数
const int m=10;
static double *trait;
GLfloat *htm;
//m列の情報
// 0: X    1: Y    2: Z
// 3: THETA    4: SIZE     
// 5: R    6: G    7: B  
// 8: STATE    9: ACTION

//i番目のネコを(x,y,z)平行移動後にy軸周りにrad回転
// GLfloat* makeMat(GLfloat* t,int i, double x, double y, double z, double theta) {
//   double rad = theta * PI / 180.0;
//   t[16*i+0] = cos(rad);
//   t[16*i+1] = 0;
//   t[16*i+2] = -sin(rad);
//   t[16*i+3] = 0;

//   t[16*i+4] = 0;
//   t[16*i+5] = 1;
//   t[16*i+6] = 0;
//   t[16*i+7] = 0;

//   t[16*i+8] = sin(rad);
//   t[16*i+9] = 0;
//   t[16*i+10] = cos(rad);
//   t[16*i+11] = 0;

//   t[16*i+12] = x*cos(rad)+z*sin(rad);
//   t[16*i+13] = y;
//   t[16*i+14] = -x*sin(rad)+z*cos(rad);
//   t[16*i+15] = 1;

//   return t;

// }

//ネコを(x,y,z)平行移動後にy軸周りにrad回転する行列を返す
GLfloat* htm_makeMat(double x, double y, double z, double theta) {
  double rad = theta * PI / 180.0;
  GLfloat *t;
  t=(float *)malloc(sizeof(float) * 16);
  t[0] = cos(rad);
  t[1] = 0;
  t[2] = -sin(rad);
  t[3] = 0;

  t[4] = 0;
  t[5] = 1;
  t[6] = 0;
  t[7] = 0;

  t[8] = sin(rad);
  t[9] = 0;
  t[10] = cos(rad);
  t[11] = 0;

  t[12] = x*cos(rad)+z*sin(rad);
  t[13] = y;
  t[14] = -x*sin(rad)+z*cos(rad);
  t[15] = 1;

  return t;

}

//作った行列をi番目に保存
void htm_setMat(GLfloat* s, GLfloat* t, int i){
  s[16*i+0] = t[0];
  s[16*i+1] = t[1];
  s[16*i+2] = t[2];
  s[16*i+3] = t[3];

  s[16*i+4] = t[4];
  s[16*i+5] = t[5];
  s[16*i+6] = t[6];
  s[16*i+7] = t[7];

  s[16*i+8] = t[8];
  s[16*i+9] = t[9];
  s[16*i+10] = t[10];
  s[16*i+11] = t[11];

  s[16*i+12] = t[12];
  s[16*i+13] = t[13];
  s[16*i+14] = t[14];
  s[16*i+15] = t[15];
}

void htm_dot(GLfloat* s, GLfloat* b){
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

    free(b);

}

//初期化
void initMat(int num)
{
    srand((unsigned int)time(NULL));
    trait =(double *)malloc(sizeof(double) * N * m);
    htm =(float *)malloc(sizeof(float) * N * 16);
    for (int i=0; i<=num; i++) {
        trait[i * m + 0]=(rand()%40-20); 
        trait[i * m + 1]= 0.0;
        trait[i * m + 2]=(rand()%20); 
        trait[i * m + 3]=rand()%360-180.0;
        trait[i * m + 4]=1.0;
        trait[i * m + 5]=(rand()%10)/10.0;
        trait[i * m + 6]=(rand()%10)/10.0;
        trait[i * m + 7]=(rand()%10)/10.0;

        htm_setMat(htm,htm_makeMat(trait[i * m + 0],trait[i * m + 1],trait[i * m + 2],trait[i * m + 3]),i);

        //htm =makeMat(htm,i,trait[i * m + 0],trait[i * m + 1],trait[i * m + 2],trait[i * m + 3]);
        // printf("i=%d\n",i);
        // printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",htm[16*i],htm[16*i+1],htm[16*i+2],htm[16*i+3],htm[16*i+4],htm[16*i+5], htm[16*i+6], htm[16*i+7], htm[16*i+8], htm[16*i+9],htm[16*i+10],htm[16*i+11],htm[16*i+12],htm[16*i+13],htm[16*i+14],htm[16*i+15]);
    }
    n = num;
}

//値を参照
double getMat(int i, int j)
{
    return trait[i * m + j];
}

//値を代入
void setMat(int i, int j, double value)
{
    trait[i * m + j]= value;
}

void freeMat(void)
{
    free(trait);
}

