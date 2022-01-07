#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "draw_function.h"
#include "tex.h"
#include "matrix_function.h"
#include "action.h"
#include "line.h"

#define PI 3.141592653589793

//-----------------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------------

int winW = 1280, winH = 960;

double pointer_x=0, pointer_y=0; //ポインタ位置

double objX, objY, objZ; //ピッキングした座標

double cam_height = 5.0; //カメラ高さ
double cam_angle = 0.0; //カメラ角度

typedef enum{
  WATCH,
  BREED,
  CARRY,
  COLOR,
  LINE,
  FUSION
} Mode; 
const char* mode_name[] = {"WATCH", "BREED", "CARRY", "COLOR", "LINE"}; 
Mode mode = WATCH;

int rgb_flg = 0; //r=0, g=1, b=2
int rgb_pm = 1; 

extern int pick_obj;

int line_flg;


//-----------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------
void init(void)
{
  srand((unsigned int)time(NULL));
  initCat(10); //ねこ生成
  texinit(); //テクスチャ作成
  unitMat(camera); 
  makeCloud(); //雲生成
  makeBucket();
  pick_obj = -1;
}

void shaking(){ //地震
  static int count = 0;
  MatArray array1;
  double y = 0.07;
  if(count<6)
    y *= -1;
  array1 = tlMat( y, 0, 0);
  dotMat(array1.matrix, camera);
  copyMat(camera, array1.matrix);
  gluInvertMatrix(camera, inv);
  count+=1;
  if(count==12)
    count = 0;
}

void getWorldCood(int TargetX, int TargetY)
{
	double modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	double projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	float z;

	glReadPixels(TargetX,winH - TargetY,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&z);
	gluUnProject(TargetX,winH - TargetY,z,modelview,projection,viewport,&objX,&objY,&objZ);	
}

 
int liner_search (double x, double z) {
  //(x,y)との距離が2.0より小さい猫
 for (int i=0;i < n;i++) {
   if (abs(cats[i].x - x)*abs(cats[i].z-z)<2.0)
     return i;
 }
 return -1;
}
 



//-----------------------------------------------------------------------------------
// レンダリング
//-----------------------------------------------------------------------------------
//60Hz

void display(void)
{
  if(mode == FUSION)
    shaking(); //地面が揺れる

  glClearColor (0.0, 0.0, 1.0, 0.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gluLookAt(0, 5, -10, 0, 1-600*tan(cam_angle), 2, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

 //視点と一緒に移動するもの
  glDisable( GL_LIGHTING ); //光源処理無効
  glPushMatrix();{ 
    glRotated(atan2(4,12)*360.0/(2*PI), 1.0, 0.0, 0.0);

    drawMap(-5, 5.2, 60);
    //ポインタ描画
    if(mode == BREED||mode == CARRY){
      glTranslated(0,0.0,-5);
      drawPointer(pointer_x, pointer_y);
    }else if(mode == COLOR){
      glTranslated(0,0.0,-5);
      drawColorPointer(pointer_x, pointer_y, rgb_flg, rgb_pm);
    }
  }
  glPopMatrix();

  init3d();
  if(mode == LINE)
    drawBucket(line_vec_num/30.0);
  
  // ここから視点と逆に動くもの
  glMultMatrixf(camera);

  drawFloor(60); //地面  
  drawCloud(); //雲
  
  if(mode != FUSION)
    updateFunc(); //ねこ更新

  for(int i=0;i<n;i++){
    drawCat(i);
  }

  //if(line_vec_num>1){ //mode = LINEで線を描画
    glPushMatrix();{
      glDisable( GL_LIGHTING ); 
      glColor3d(1.0, 1.0, 1.0);
      glLineWidth(5.0f);
      for(int k = 0; k<(line_vec_num-1); k++){
        glBegin( GL_LINES );
        glVertex3f( line_vector[k].x, line_vector[k].y, line_vector[k].z);
        glVertex3f( line_vector[k+1].x, line_vector[k+1].y, line_vector[k+1].z);
        glEnd();
      }

      if(mode == FUSION){ //fusion_Circleで描画, 1を返すと終了処理
        if(fusion_Circle()){
          mode = LINE;
          line_init();
          line_flg = 0;
        }
      }

    }glPopMatrix();
  //}

  glutSwapBuffers();
}

// void timer(int value){
  
//   glutTimerFunc(1000,timer,0);
// }

//-----------------------------------------------------------------------------------
// ウィンドウリサイズのコールバック関数
//-----------------------------------------------------------------------------------
void reshape (int w, int h)
{
  winH = h;
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1.0*6, 20.0*10);
}

//-----------------------------------------------------------------------------------
// キーボード入力のコールバック関数
//-----------------------------------------------------------------------------------
void keyboard (unsigned char key, int x, int y)
{
  static unsigned char pre_key;
  // 視点移動変位
  double dx = 0.0, dy = 0.0, dz = 0.0;
  int rdx = 0;
  //printf("1->%d\n",rdx);
  switch (key) {
    //視点高さ変更
    case 'z':
      if(cam_angle<1.57){
        cam_angle = cam_angle+0.4/20;
      }
      if(cam_height<60){
        dy = - 0.4;
        cam_height += 0.4;
      }
      break;
    case 'x':
      if(cam_height>5){
        dy =  0.4;
        cam_height -= 0.4;
        if(cam_height<60){
          cam_angle = cam_angle-0.4/20;
        }
      }
      break;

    //前後方向
    case 's':
      dz = - 0.4;
      break;
    case 'w':
      dz =  0.4;
      break;

    //左右回転
    case 'a':
      rdx = - 2;
      break;
    case 'd':
      rdx =  2;
      break;

    //mode=COLOR 色変更
    case 'r':
      rgb_flg = 0;
      rgb_pm *= -1;
      break;
    case 'g':
      rgb_flg = 1;
      rgb_pm *= -1;
      break;
    case 'b':
      rgb_flg = 2;
      rgb_pm *= -1;
      break;

    case 'n':
      //描画終了後, 保存した頂点を破棄する(modeに依らない)
      if(line_flg == 0 && line_vec_num>0){ 
        // for (size_t i = 0; i < line_vec_num; ++i) {
        //     line_vector[i] = (Vector){0, 0, 0};
        // }
        // line_vec_num=0;
        line_init();
        break;
      }
    
      if(mode == LINE){
        //描画中 描画を終了する
        if(line_flg == 1){
          line_flg = 0;
          if(line_vec_num == 6 && line_isstar(20)){
            line_calc(); //錬成開始
            mode = FUSION;
          }
        //描画開始
        }else if(line_vec_num == 0){
          line_init();
          line_vector[0].x = inv[12];
          line_vector[0].y = -0.5;
          line_vector[0].z = inv[14];
          line_vec_num = 1;
          line_flg = 1; 
        }
      }
      break;

    case 32: 
      mode = (mode+1)%5; //モード切替

      if(pick_obj>=0){ //mode = CARRYのときねこを持っていたら解放
        cats[pick_obj].matrix[13] = 0.0;
        cats[pick_obj].task = STAY;
        pick_obj = -1;
      }

      if(line_flg == 1) //mode = LINEのとき描画終了
        line_flg = 0;

      glutSetWindowTitle(mode_name[mode]); //ウィンドウ名変更
      break;

    case 27:
      exit(0);
      break;
  }
  //printf("2->%d\n",rdx);
  if(mode == LINE){ //mode = LINEのとき移動速度増加
    dx*=3.0;
    dz*=3.0;
  }

  //キー入力した差分に応じてカメラの行列を更新
  MatArray array1, array2;
  array1 = tlMat( -dx, dy, -dz);
  array2 = y_rtMat(rdx);
  dotMat(array1.matrix, camera);
  dotMat(array2.matrix, array1.matrix);
  copyMat(camera, array2.matrix);
  gluInvertMatrix(camera, inv);

  //mode = CARRY カメラの動きを運んでいるねこに反映
  if(pick_obj>=0){
    GLfloat t[16];
    copyMat(t, inv);
    dotMat(t, tlMat( 0, 4, 20).matrix);
    copyMat(cats[pick_obj].matrix, t);
  }

  //mode = LINE 描画する頂点の更新
  if(line_flg && (key == 'w' || key == 's')){
    if(pre_key == 'w' || pre_key == 's'){
      line_vector[line_vec_num-1].x = inv[12];
      line_vector[line_vec_num-1].y = -0.5;
      line_vector[line_vec_num-1].z = inv[14];
    }else if(line_vec_num == 1){
      line_vector[line_vec_num].x = inv[12];
      line_vector[line_vec_num].y = -0.5;
      line_vector[line_vec_num].z = inv[14];
      line_vec_num ++;
    }
  }
  if(line_flg && (key == 'a' || key == 'd') && line_vec_num<30){
    if(pre_key == 'w' || pre_key == 's'){
      line_vector[line_vec_num].x = inv[12];
      line_vector[line_vec_num].y = -0.5;
      line_vector[line_vec_num].z = inv[14];
      line_vec_num ++;
    }
  }
  pre_key = key;

}

// -----------------------------------------------------------------------------------
// マウスクリックのコールバック関数
// -----------------------------------------------------------------------------------
void mouse(int button, int state, int x, int y)
{
  int i=-1;

  if(state == GLUT_UP) 
    return;
  else{
    getWorldCood(x+6, y+30);
    i = liner_search(objX, objZ);
  }

  switch(mode){
    case BREED:
      if(i>-1){

        if(cats[i].scale==0.6){
          cats[i].scale = 0.8;
          break;
        }else if(cats[i].scale==0.8){
          cats[i].scale = 1.0;
          break;
        }

        if(cats[i].task!=JUMP){
          cats[i].task = JUMP;
          cats[i].duration = 0;
        }
      }
      break;
    
    case CARRY:
      if(pick_obj>=0){ //離す
        cats[pick_obj].matrix[13] = 0.0;
        cats[pick_obj].task = STAY;
        pick_obj = -1;
      }else{
        if(i>-1){
          pick_obj = i;
          cats[pick_obj].task = PICKED;
          //カメラ位置に拘束
          GLfloat t[16];
          copyMat(t, inv);
          dotMat(t, tlMat( 0, 4, 20).matrix);
          copyMat(cats[pick_obj].matrix, t);
        }
      }
      break;

    case COLOR:
      if(i>-1){
        switch(rgb_flg){
          case 0:
            cats[i].r += rgb_pm*0.2;
            if(cats[i].r>1.0)
              cats[i].r=1.0;
            if(cats[i].r<0.0)
              cats[i].r=0.0;
            break;
          case 1:
            cats[i].g += rgb_pm*0.2;
            if(cats[i].g>1.0)
              cats[i].g=1.0;
            if(cats[i].g<0.0)
              cats[i].g=0.0;
            break;
          case 2:
            cats[i].b += rgb_pm*0.2;
            if(cats[i].b>1.0)
              cats[i].b=1.0;
            if(cats[i].b<0.0)
              cats[i].b=0.0;
            break;
        }
      }
      break;

    default:
      break;
  }

  glutPostRedisplay();
}

// -----------------------------------------------------------------------------------
// マウス移動のコールバック関数
// -----------------------------------------------------------------------------------
void motion(int x, int y){
  //マウス位置をポインタ位置に変換
  pointer_x = (640 - x-40)/191.0;
  pointer_y = (770 - y-40)/191.0;

  glutPostRedisplay();
}

//-----------------------------------------------------------------------------------
// アイドル時のコールバック関数
//-----------------------------------------------------------------------------------
void idle()
{
  glutPostRedisplay();
}

//-----------------------------------------------------------------------------------
// メイン関数
//-----------------------------------------------------------------------------------
int main(int argc, char** argv)
{
  
  glutInit(&argc, argv);
  glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize (winW, winH);
  glutInitWindowPosition (50, 50);
  glutCreateWindow (mode_name[mode]);

  init();
  
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  //glutTimerFunc(1000,timer,0);
  glutMouseFunc(mouse);
  //glutMotionFunc(motion);
  glutSetCursor(GLUT_CURSOR_NONE);
  glutPassiveMotionFunc(motion);

  glutMainLoop();

  return 0;
}
