#ifndef __TEX_H__
#define __TEX_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
    HAPPY,
    SLEEPY,
    ANGRY,
    NORMAL
}face;

void texinit(void);
void facedisplay(face t, float a, float b, float c);
  
#ifdef __cplusplus
}
#endif

#endif
