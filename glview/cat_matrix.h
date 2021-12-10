#ifndef __CAT_MATRIX_H__
#define __CAT_MATRIX_H__

#ifdef __cplusplus
extern "C" {
#endif

extern GLfloat *htm;
extern int n;
void initMat(int num);
double getMat(int i, int j);
void setMat(int i, int j, double value);
void freeMat(void);
GLfloat* makeMat(GLfloat* t,int i, double x, double y, double z, double theta);

  
#ifdef __cplusplus
}
#endif

#endif
