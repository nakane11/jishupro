#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "cat_matrix.h"

enum state {
    ASLEEP,
    MOVE,
    STAY
};

enum action {
    SLEEP,
    WALK,
    RUN,
    SIT, 
};


void nextState(int i) {
    //stateに応じて次のstateを決める
    int p = rand()%100;
    switch((int)getMat(i, 8)) {
        case ASLEEP: //確率0.15でSTAY
            if (p<15){
                setMat(i, 8,(double)STAY);
            }
            break;
        case MOVE:
        //確率0.3でSTAY
            if (p<30){
                setMat(i, 8,(double)STAY);
            }
            break;
        case STAY:
        //確率0.2でASLEEP 0.3でMOVE
            if (p<20){
                setMat(i, 8,(double)ASLEEP);
            }else if(p<50){
                setMat(i, 8,(double)MOVE);
            }
            break;
        default:
            printf("nextState %d default\n",i);
    }
}

double nextAction(int i) {
    int p = rand()%100;
    //printf("%d",p);
    switch((int)getMat(i, 8)){
        case ASLEEP: 
            break;
        case MOVE:
            if (p<10){
                //直進
                //setMat(i, 2, getMat(i, 2)+0.1);
                return -0.005;
            }else if(p<80){
                return -0.005;
            
            }else if(p<87){
                //左折
            }else if(p<95){
                //右折
            }else{
                //後退
            }
            break;
        case STAY:
            break;
        default:
            printf("nextAction %d default\n",i);
    }
    return 0.0;
}

