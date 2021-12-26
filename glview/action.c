#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "matrix_function.h"
#include "tex.h"
#include "action.h"

double param = 0;
int pick_obj;

double catsDistance (int a, int b){
    return (cats[a].x - cats[b].x)*(cats[a].x - cats[b].x) 
    + (cats[a].y - cats[b].y) * (cats[a].y - cats[b].y) 
    + (cats[a].z - cats[b].z) * (cats[a].z - cats[b].z);
}

void updateFunc(void){
    int i, j;
    MatArray tlarray, rtarray;
    // for(i=0;i<n;i++){
    //     for (j = i+1; j<n; j++){
    //         if (catsDistance(i, j) < 9.0){
    //             if(cats[i].task==TURN){
    //                 cats[j].task = STAY;
    //                 cats[j].duration = 200;
    //             }else{
    //                 cats[i].task = STAY;
    //                 cats[i].duration = 200;
    //                 cats[j].task = TURN;
    //                 cats[j].duration = 100;
    //             }
    //         }
    //     }
    // }
    
    for (i = 0; i<n; i++){
        if(rand()%4000<2){cats[i].neck_angle = rand()%60-30;}
        
        switch (cats[i].task){
        case JUMP:
            if (cats[i].duration == 0){
                cats[i].duration = 60*(rand()%4+4);
                param = 1;
                cats[i].face = HAPPY;
                cats[i].flg = 1;
                
            }else if(cats[i].duration %60 >= 30){
                param = 1;
            }else{
                param = -1;
            }
            if (cats[i].duration == 1){
                cats[i].task = STAY;
                cats[i].flg = 0;
            }
            tlarray = tlMat(0, 0.1*param, 0);
            dotMat( cats[i].matrix, tlarray.matrix);
            cats[i].duration --;
            break;

        case WALK:
            // for (j = i+1; j<n; j++){
            //     if (catsDistance(i, j) < 6.0){
            //         cats[i].task = STAY;
            //         cats[i].duration = 0;
            //         break;
            //     }
            // }
            if (cats[i].duration == 0){
                cats[i].duration = 40*(rand()%20+4); //進む距離決める
                cats[i].p_speed = rand()%10+5;
                cats[i].face = NORMAL;
            }else if (cats[i].duration == 1){
                
                if(rand()%100<40){
                    cats[i].task = TURN;
                }else{
                    cats[i].task = STAY; //次のtask
                }
                
            }
            tlarray = tlMat(0, 0, cats[i].p_speed/400.0);
            dotMat( cats[i].matrix, tlarray.matrix);
            cats[i].duration --;
            break;

        case TURN:
            // for (j = i+1; j<n; j++){
            //     if (catsDistance(i, j) < 6.0){
            //         cats[i].task = STAY;//並進スピード小さくするかstay
            //         cats[i].duration = 0;
            //         break;
            //     }
            // }
            if (cats[i].duration == 0){
                cats[i].duration = 60*(rand()%4/3+2); //回転角決める
                cats[i].p_speed = (rand()%2*2-1)*(rand()%10+5);
                cats[i].face = ANGRY;
            }else if (cats[i].duration == 1){
                cats[i].task = WALK; //次のtask
            }
            //曲がりながら進む
            tlarray = tlMat(0, 0, abs(cats[i].p_speed)/500.0);
            if(cats[i].p_speed>0){rtarray = y_rtMat(0.5);}else{rtarray = y_rtMat(-0.5);}
            dotMat(tlarray.matrix , rtarray.matrix);
            dotMat( cats[i].matrix, tlarray.matrix);
            cats[i].duration --;
            break;

        case STAY:
            if (cats[i].duration == 0){
                cats[i].duration = 5*(rand()%20+4);
                cats[i].face = NORMAL;
            }else if(cats[i].duration == 1){
                if(rand()%100<50){
                    cats[i].task = WALK;
                }else{
                    cats[i].task = SLEEP;
                }
            }
            cats[i].duration--;
            break;

        case SLEEP:
            if (cats[i].duration == 0){
                cats[i].duration = 20*(rand()%20+4);
                cats[i].face = SLEEPY;
            }else if(cats[i].duration == 1){
                cats[i].task = STAY;
            }
            cats[i].duration--;
            break;

        case DIE:
            if (cats[i].duration == 1){
                for(j=i;j<n;j++){
                    cats[j]=cats[j+1];
                }
                i--; n--; 
                if(i<pick_obj){pick_obj --;}
                //printf("%d\n",n);
            }else{
                tlarray = tlMat(0, -0.6, 0);
                dotMat( cats[i].matrix, tlarray.matrix);
                cats[i].duration --;
            }
            break;

        case PICKED:
            break;

        }
           
    //     for (j = i+1; j<n; j++){
    //         if (catsDistance(i, j) < 4.0){
    //             MatArray array = y_rtMat(30*(rand()%2*2-1));
    //             dotMat(avoid, cats[i].matrix);
    //         }
    //     }
    // }
    }
    for (i = 0; i<n; i++){
        //行列を更新した後に座標を更新
        cats[i].x = cats[i].matrix[12];
        cats[i].y = cats[i].matrix[13];
        cats[i].z = cats[i].matrix[14];

        if((abs(cats[i].x)>64||abs(cats[i].z)>64)&&cats[i].task!=DIE){
            cats[i].task = DIE;
            cats[i].duration = 60;
            cats[i].r = 1.0;
            cats[i].g = 0.0;
            cats[i].b = 0.0;
            
        }
    }

    for (i = 0; i<n; i++){
       if(cats[i].flg){
           for (j = i+1; j<n; j++){
               if(cats[j].flg && catsDistance(i, j)<250){
                   //printf("%lf\n",catsDistance(i,j));
                   addCat(i, j);
               }
           }
       }
    }


    
    
}