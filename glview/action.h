#ifndef __ACTION_H__
#define __ACTION_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WALK,
    EAT,
    STAY,
    SLEEP,
    TURN
} task;

void updateFunc(void);
  
#ifdef __cplusplus
}
#endif

#endif