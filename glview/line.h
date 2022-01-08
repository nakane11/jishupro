#ifndef __LINE_H__
#define __LINE_H__

typedef struct{
  double x, y, z;
}Vector;
extern Vector line_vector[];
extern int line_vec_num;

void line_init();
int line_isstar(int d);
void line_calc();
void fusion_clearColor();
int fusion_update();

#endif