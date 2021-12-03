#ifndef __CAT_MATRIX_H__
#define __CAT_MATRIX_H__

#ifdef __cplusplus
extern "C" {
#endif

extern int n;
void initMat(int num);
double getMat(int i, int j);
void setMat(int i, int j, double value);
void freeMat(void);
  
#ifdef __cplusplus
}
#endif

#endif
