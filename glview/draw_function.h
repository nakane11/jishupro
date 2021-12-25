#ifndef __DRAW_FUNCTION_H__
#define __DRAW_FUNCTION_H__

#ifdef __cplusplus
extern "C" {
#endif


void init3d(void);
void drawCat(int i);
void drawMap(double x, double z, double range);
void drawPointer(double cx, double cy);
void drawFloor(int r);
void drawCloud(void);

  
#ifdef __cplusplus
}
#endif

#endif
