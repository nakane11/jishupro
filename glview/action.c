#include "cat_matrix.h"

enum state {
    ASLEEP,
    MOVE,
    STAY
}

enum action {
    SLEEP,
    WALK,
    RUN,
    SIT, 
}

//nextActionより周期長くする
void nextState(int i) {
    //stateに応じて次のstateを決める
    switch((int)getMat(i, 8)) {
        case ASLEEP:
        //確率0.15でSTAY
            // setMat(i, 8)=;
            // setMat(i, 9)=;

            break;
        case MOVE:
        //確率0.3でSTAY
            break;
        case STAY:
        //確率0.2でASLEEP 0.3で
            break;
        default:
            printf("nextAction %d default\n",i);
    }

}

void nextAction(int i) {
    

    //stateに応じて次のactionを決める
    switch((int)getMat(i, 8)) {
        case ASLEEP:
        //確率0.15でSTAY
            // setMat(i, 8)=;
            // setMat(i, 9)=;

            break;
        case MOVE:
        //確率0.3でSTAY
            break;
        case STAY:
        //確率0.2でASLEEP 0.3で
            break;
        default:
            printf("nextAction %d default\n",i);
    }
    //決まったactionに応じて次の位置を決める


    

}

