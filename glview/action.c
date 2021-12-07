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

void nextAction(int i) {
    //stateに応じて次のstate, actionを決める
    switch((int)getMat(i, 8)) {
        case ASLEEP:
            // setMat(i, 8)=;
            // setMat(i, 9)=;

            break;
        case MOVE:
            break;
        case STAY:
            break;
        default:
            printf("nextAction %d default\n",i);
    }

    //actionに応じて次の位置を決める
    switch((int)getMat(i, 9)) {
        case SLEEP:
            

            break;
        case WALK:
            break;
        case RUN:
            break;
        case SIT:
            break;
        case EAT:
            break;

        default:
            printf("nextAction %d default\n",i);
    }

    

}