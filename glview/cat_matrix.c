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
GLfloat* makeMat(GLfloat* t,int i, double x, double y, double z, double theta) {
  double rad = theta * PI / 180.0;
  t[16*i+0] = cos(rad);
  t[16*i+1] = 0;
  t[16*i+2] = -sin(rad);
  t[16*i+3] = 0;

  t[16*i+4] = 0;
  t[16*i+5] = 1;
  t[16*i+6] = 0;
  t[16*i+7] = 0;

  t[16*i+8] = sin(rad);
  t[16*i+9] = 0;
  t[16*i+10] = cos(rad);
  t[16*i+11] = 0;

  t[16*i+12] = x*cos(rad)+z*sin(rad);
  t[16*i+13] = y;
  t[16*i+14] = -x*sin(rad)+z*cos(rad);
  t[16*i+15] = 1;

  return t;

}

//初期化
void initMat(int num)
{
    //srand((unsigned int)time(NULL));
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

        htm =makeMat(htm,i,trait[i * m + 0],trait[i * m + 1],trait[i * m + 2],trait[i * m + 3]);
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

