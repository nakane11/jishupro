#ifndef __MATRIX_FUNCTION_H__
#define __MATRIX_FUNCTION_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double x, y, z, scale, r, g, b;
    int neck_angle, task, duration, face;
    GLfloat matrix[16];
    float p_speed;
    int flg;
} Cat;
typedef struct { GLfloat matrix[16]; } MatArray;

extern int n; //現在のねこの出現数
extern Cat cats[];
extern GLfloat camera[];
extern GLfloat inv[];

int gluInvertMatrix(const GLfloat m[16], GLfloat invOut[16]);
void copyMat (GLfloat *a, GLfloat *b);
void dotMat (GLfloat *a, GLfloat *b);
MatArray y_rtMat(double angle);
MatArray tlMat(double x, double y, double z);
void unitMat(GLfloat *a);
void initCat (int num);
void addCat(int i, int j);
void myUnProject(GLfloat winX, GLfloat winY, GLfloat winZ,
	            GLfloat *model, GLfloat *proj, GLint *view,
	            GLfloat* objX, GLfloat* objY, GLfloat* objZ);
  
#ifdef __cplusplus
}
#endif

#endif