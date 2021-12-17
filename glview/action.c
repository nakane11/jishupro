#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "matrix_function.h"


typedef enum {
    WALK,
    EAT,
    STAY,
    SLEEP,
    TURN
} task;

double param = 0;

double catsDistance (int a, int b){
    return (cats[a].x - cats[b].x)*(cats[a].x - cats[b].x) 
    + (cats[a].y - cats[b].y) * (cats[a].y - cats[b].y) 
    + (cats[a].z - cats[b].z) * (cats[a].z - cats[b].z);
}

void updateFunc(void){
    int i, j;
    MatArray array;
    for (i = 0; i<n; i++){
        switch (cats[i].task){
        case EAT:
            if (cats[i].duration == 0){
                cats[i].duration = 60*(rand()%4+1);
                param = 1;
                
            }else if(cats[i].duration %60 > 30){
                param = 1;
            }else{
                param = -1;
            }
            if (cats[i].duration == 1){
                cats[i].task = STAY;
            }
            array = tlMat(0, 0.1*param, 0);
            dotMat( array.matrix, cats[i].matrix);
            cats[i].duration --;
            break;

        case WALK:
            for (j = i+1; j<n; j++){
                if (catsDistance(i, j) < 4.0){
                    cats[i].task = STAY;
                    cats[i].duration = 0;
                    break;
                }
            }
            if (cats[i].duration == 0){
                cats[i].duration = 60*(rand()%15+2); //進む距離決める
                param = rand()%5+5;
            }else if (cats[i].duration == 1){
                cats[i].task = STAY; //次のtask
            }
            MatArray array = tlMat(0, 0, param/500.0);
            dotMat( cats[i].matrix, array.matrix);
            cats[i].duration --;
            break;
    //     case TURN:
    //         for (j = i+1; j<n; j++){
    //             if (catsDistance(i, j) < 4.0){
    //                 cats[i].task = STAY;//並進スピード小さくするかstay
    //                 duration = 0;
    //                 break;
    //             }
    //         }
    //         if (duration == 0){
    //             duration = rand(); //回転角決める
    //             cats[i].speed = 
    //         }else if (duration == 1){
    //             cats[i].task = ; //次のtask
    //         }
    //         //曲がりながら進む
    //         duration -= 1;
    //         break;
    //     }
           
    //     for (j = i+1; j<n; j++){
    //         if (catsDistance(i, j) < 4.0){
    //             MatArray array = y_rtMat(30*(rand()%2*2-1));
    //             dotMat(avoid, cats[i].matrix);
    //         }
    //     }
    // }
    // //ここでaction
    // for (i = 0; i<n; i++){
    //     //行列を更新した後に座標を更新
    //     cats[i].x = cats[i].matrix[12];
    //     cats[i].y = cats[i].matrix[13];
    //     cats[i].z = cats[i].matrix[14];
    // }
        }
        }
}