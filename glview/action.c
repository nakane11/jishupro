#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "cat_matrix.h"

#include "action.h"

enum state {
    ASLEEP,
    MOVE,
    STAY,
    LTURN,
    RTURN
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
    if(p<5){
        setMat(i,10,rand()%45-15);
    }
    switch((int)getMat(i, 8)) {
        case ASLEEP: //確率0.15でSTAY
            if (p<15){
                setMat(i, 8,(double)STAY);
            }
            break;
        case MOVE:
        //確率0.3でSTAY
            if (p<35){
                setMat(i, 8,(double)STAY);
            }else if(p<41){
                setMat(i, 8,(double)LTURN);
            }else if(p<47){
                setMat(i, 8,(double)RTURN);
            }
            break;
        case STAY:
        //確率0.2でASLEEP 0.3でMOVE
            if (p<20){
                setMat(i, 8,(double)ASLEEP);
            }else if(p<70){
                setMat(i, 8,(double)MOVE);
            }
            break;
        case LTURN:
            if (p<50){
                setMat(i, 8,(double)STAY);
            }else if(p<60){
                setMat(i, 8,(double)MOVE);
            }
            break;
        case RTURN:
            if (p<50){
                setMat(i, 8,(double)STAY);
            }else if(p<60){
                setMat(i, 8,(double)MOVE);
            }
            break;
        default:
            printf("nextState %d default\n",i);
    }
}

// double nextAction(int i) {
//     int p = rand()%100;
//     //printf("%d",p);
//     // switch((int)getMat(i, 8)){
//     //     case ASLEEP: 
//     //         break;
//     //     case MOVE:
//     //         if (p<40){
//     //             //直進
//     //             //setMat(i, 2, getMat(i, 2)+0.1);
//     //             //printf("a");
//     //             return 0.00000000000000000005;
//     //         }else if(p<80){
//     //             //printf("b");
//     //             //return -0.005;
            
//     //         }else if(p<87){
//     //             //左折
//     //         }else if(p<95){
//     //             //右折
//     //         }else{
//     //             //後退
//     //         }
//     //         break;
//     //     case STAY:
//     //         break;
//     //     default:
//     //         printf("nextAction %d default\n",i);
//     // }
//     return 0.0;
// }

// void nextAction2(int i, double* a) {
//     *a = 0.01;
// }

void nextAction0(int i, double* a,double* b) {
    int p = rand()%100;
    switch((int)getMat(i, 8)){
        case ASLEEP: 
            break;
        case MOVE:
            if (p<90){
                //直進
                *a = 0.02;
            }else{
                //後退
                *a = -0.01;
            }
            break;
        case STAY:
            break;
        case LTURN:
            *b = -1.0;
        case RTURN:
            *b = 1.0;
        default:
            printf("nextAction %d default\n",i);
    }
}


// double catsDistance (int a, int b){
//     return (cats[a].x - cats[b].x)*(cats[a].x - cats[b].x) 
//     + (cats[a].y - cats[b].y) * (cats[a].y - cats[b].y) 
//     + (cats[a].z - cats[b].z) * (cats[a].z - cats[b].z);
// }

// void updateFunc(void){
//     int i, j;
//     for (i = 0; i<n; i++){
//         switch (cats[i].task){
//         case EAT:
//             break:
//         case WALK:
//             for (j = i+1; j<n; j++){
//                 if (catsDistance(i, j) < 4.0){
//                     cats[i].task = TURN, STAY;
//                     duration = 0;
//                     break;
//                 }
//             }
//             if (duration == 0){
//                 duration = rand(); //進む距離決める
//                 cats[i].speed = 
//             }else if (duration == 1){
//                 cats[i].task = ; //次のtask
//             }
//             //z方向に進む
//             duration -= 1;
//             break;
//         case TURN:
//             for (j = i+1; j<n; j++){
//                 if (catsDistance(i, j) < 4.0){
//                     cats[i].task = STAY;//並進スピード小さくするかstay
//                     duration = 0;
//                     break;
//                 }
//             }
//             if (duration == 0){
//                 duration = rand(); //回転角決める
//                 cats[i].speed = 
//             }else if (duration == 1){
//                 cats[i].task = ; //次のtask
//             }
//             //曲がりながら進む
//             duration -= 1;
//             break;
//         }
           
//         for (j = i+1; j<n; j++){
//             if (catsDistance(i, j) < 4.0){
//                 MatArray array = y_rtMat(30*(rand()%2*2-1));
//                 dotMat(avoid, cats[i].matrix);
//             }
//         }
//     }
//     //ここでaction
//     for (i = 0; i<n; i++){
//         //行列を更新した後に座標を更新
//         cats[i].x = cats[i].matrix[12];
//         cats[i].y = cats[i].matrix[13];
//         cats[i].z = cats[i].matrix[14];
//     }
// }