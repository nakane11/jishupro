#include <stdlib.h>

static int N=30; //出現数の上限
int n=0; //現在の出現数
const int m=8;
static double *matrix;

//初期化
void initMat(int num)
{
    matrix =(double *)malloc(sizeof(double) * N * m);
    for (int i=0; i<=num; i++) {
        matrix[i * m + 0]=(rand()%40-20)/10.0;
        matrix[i * m + 1]= 0.0;
        matrix[i * m + 2]=(rand()%40-20)/10.0;
        matrix[i * m + 3]=rand()%360-180.0;
        matrix[i * m + 4]=0.2;
        matrix[i * m + 5]=(rand()%10)/10.0;
        matrix[i * m + 6]=(rand()%10)/10.0;
        matrix[i * m + 7]=(rand()%10)/10.0;

        // printf("Value of d = %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, \n",matrix[i*m+0], matrix[i*m+1], matrix[i*m+2],
        //           matrix[i*m+3], matrix[i*m+ 4],
        //           matrix[i*m+5], matrix[i*m+6], matrix[i*m+7]);
    }
    n = num;
}

//値を参照
double getMat(int i, int j)
{
    return matrix[i * m + j];
}

//値を代入
void setMat(int i, int j, double value)
{
    matrix[i * m + j]= value;
}

void freeMat(void)
{
    free(matrix);
}