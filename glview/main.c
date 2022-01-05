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

#define PI 3.141592653589793

//-----------------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------------

// 視点情報
static double distance, pitch, yaw;
static int rx;

// マウス入力情報
//GLint mouse_x, mouse_y;

int winW = 1280, winH = 960;

double px=0, py=0; //ポインタ位置

double objX, objY, objZ; //ピッキングした座標

double cz = 5.0; //カメラ高さ
double ry = 0.0; //カメラ角度

int rgb_flg = 0; //rgb
int color_pm = 1;

typedef enum{
  WATCH,
  BREED,
  CARRY,
  COLOR
} Mode; 
const char* mode_name[] = {"WATCH", "BREED", "CARRY", "COLOR"}; 
Mode mode = WATCH;

extern int pick_obj;

//-----------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------
void init(void)
{
  srand((unsigned int)time(NULL));
  initCat(10); //ねこ生成
  texinit(); //テクスチャ作成
  unitMat(camera); //カメラ座標初期化
  makeCloud(); //雲生成
  pick_obj = -1;
  
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
  
  // フレームバッファのクリア
  glClearColor (0.0, 0.0, 1.0, 0.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  gluLookAt(0, 5, -10, 0, 1-600*tan(ry), 2, 0, 1, 0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glPushMatrix();{
    glDisable( GL_LIGHTING ); //光源処理無効
    glRotated(atan2(4,12)*360.0/(2*PI), 1.0, 0.0, 0.0);
    drawMap(-5, 5.2, 60);
    if(mode == BREED||mode == CARRY){
      glTranslated(0,0.0,-5);
      drawPointer(px, py);
    }else if(mode == COLOR){
      glTranslated(0,0.0,-5);
      drawColorPointer(px, py, rgb_flg, color_pm);
    }
  }
  glPopMatrix();

  init3d();
  
  // 視点を移動
  glMultMatrixf(camera);

  drawFloor(60); //地面  
  drawCloud(); //雲
  
  updateFunc(); 
  for(int i=0;i<n;i++){
    drawCat(i);
  }

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
  yaw=0; pitch=0; distance=0; rx=0;
  switch (key) {
    //視点高さ
    case 'z':
      if(ry<1.57){
        ry = ry+0.4/20;
      }
      if(cz<60){
        pitch = - 0.4;
        cz += 0.4;
      }
      break;
    case 'x':
      if(cz>5){
        pitch =  0.4;
        cz -= 0.4;
        if(cz<60){
          ry = ry-0.4/20;
        }
      }
      break;

    //前後方向
    case 's':
       distance = - 0.4;
      break;
    case 'w':
      distance =  0.4;
      break;

    //左右回転
    case 'a':
      rx = - 2;
      break;
    case 'd':
      rx =  2;
      break;

    //色変更
    case 'r':
      rgb_flg = 0;
      color_pm *= -1;
      break;
    case 'g':
      rgb_flg = 1;
      color_pm *= -1;
      break;
    case 'b':
      rgb_flg = 2;
      color_pm *= -1;
      break;

    //モード切替
    case 32: 
      mode = (mode+1)%4;
      if(pick_obj>=0){
        cats[pick_obj].matrix[13] = 0.0;
        cats[pick_obj].task = STAY;
        pick_obj = -1;
      }
      glutSetWindowTitle(mode_name[mode]);
      break;


    case 27:
      exit(0);
      break;
  }

  //カメラの行列を更新
  MatArray array1, array2;
  array1 = tlMat( -yaw, pitch, -distance);
  array2 = y_rtMat(rx);
  dotMat(array1.matrix, camera);
  dotMat(array2.matrix, array1.matrix);
  copyMat(camera, array2.matrix);
  gluInvertMatrix(camera, inv);

  if(pick_obj>=0){
    GLfloat t[16];
    copyMat(t, inv);
    dotMat(t, tlMat( 0, 4, 20).matrix);
    copyMat(cats[pick_obj].matrix, t);
  }

}

// -----------------------------------------------------------------------------------
// マウスクリックのコールバック関数
// -----------------------------------------------------------------------------------
void mouse(int button, int state, int x, int y)
{
  int i=-1;
  //mouse_x = x;	mouse_y = y;
  if(state == GLUT_UP) 
    return;
  else{
    getWorldCood(x+6, y+30);
    i = liner_search(objX, objZ);
  }

  switch(mode){
    case BREED:
      if(i>-1){
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
            cats[i].r += color_pm*0.2;
            if(cats[i].r>1.0)
              cats[i].r=1.0;
            if(cats[i].r<0.0)
              cats[i].r=0.0;
            break;
          case 1:
            cats[i].g += color_pm*0.2;
            if(cats[i].g>1.0)
              cats[i].g=1.0;
            if(cats[i].g<0.0)
              cats[i].g=0.0;
            break;
          case 2:
            cats[i].b += color_pm*0.2;
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
  px = (640 - x-40)/191.0;
  py = (770 - y-40)/191.0;

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
