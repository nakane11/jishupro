#ifndef __ACTION_H__
#define __ACTION_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WALK,
    JUMP,
    STAY,
    SLEEP,
    TURN,
    DIE,
    PICKED,
    CHASE
} task;

double catsDistance (int a, int b);
void updateFunc(void);
  
#ifdef __cplusplus
}
#endif

#endif