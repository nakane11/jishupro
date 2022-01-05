#ifndef __DRAW_FUNCTION_H__
#define __DRAW_FUNCTION_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
  double x, y, z;
}Vector;
extern Vector line_vector[];
extern int line_vec_num;
extern GLUquadricObj *bucket, *paint;


void init3d(void);
void drawCat(int i);
void drawMap(double x, double z, double range);
void drawPointer(double cx, double cy);
void drawColorPointer(double cx, double cy, int color, int pm);
void drawFloor(int r);
void drawCloud(void);
void makeCloud(void);
void drawBucket(double r);
void makeBucket();
  
#ifdef __cplusplus
}
#endif

#endif
