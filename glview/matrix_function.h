#ifndef __MATRIX_FUNCTION_H__
#define __MATRIX_FUNCTION_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double x, y, z, scale, r, g, b;
    int neck_angle, state, task, duration, face;
    GLfloat matrix[16];
} Cat;
typedef struct { GLfloat matrix[16]; } MatArray;

extern int n; //現在のねこの出現数
extern Cat cats[];

void dotMat (GLfloat *a, GLfloat *b);
MatArray y_rtMat(double angle);
MatArray tlMat(double x, double y, double z);
void initCat (int num);
  
#ifdef __cplusplus
}
#endif

#endif