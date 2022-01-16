#ifndef __BALL_H__
#define __BALL_H__

extern int ball_phase;
extern int chase_num;
void ball_change_speed();
void drawBall();
void ball_calc();
void relative_pos();
void ball_update_chase();
void ball_reset_chase();

#endif