#ifndef __LINE_H__
#define __LINE_H__

typedef struct{
  double x, y, z;
}Vector;
extern Vector line_vector[];
extern int line_vec_num;


int line_isstar(int d);
void line_culc();

#endif