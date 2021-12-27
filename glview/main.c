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
#include "font0.h"

#define PI 3.141592653589793

//-----------------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------------

// 視点情報
static double distance, pitch, yaw;
static int rx;

// マウス入力情報
GLint mouse_x, mouse_y;

int winW = 1280, winH = 960;

double px=0, py=0; //ポインタ位置

double objX, objY, objZ; //ピッキングした座標

double cz = 5.0; //カメラ高さ
double ry = 0.0; //カメラ角度

typedef enum{
  WATCH,
  BREED,
  CARRY
} Mode; 

Mode mode = WATCH;

extern int pick_obj;

//-----------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------
void init(void)
{
  srand((unsigned int)time(NULL));
  initCat(6); //ねこ生成
  texinit(); //テクスチャ作成
  unitMat(camera); //カメラ座標初期化
  makeCloud(); //雲生成
  pick_obj = -1;
  readfont0();
  
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

 
void liner_search (double x, double z) {
 for (int i=0;i < n;i++) {
   if (abs(cats[i].x - x)*abs(cats[i].z-z)<2.0)
   {
     switch(mode){
       case BREED:
        if(cats[i].task!=JUMP){
          cats[i].task = JUMP;
          cats[i].duration = 0;
        }
        break;

       case CARRY:
        pick_obj = i;
        cats[pick_obj].task = PICKED;
        //カメラ位置に拘束
        GLfloat t[16];
        copyMat(t, inv);
        dotMat(t, tlMat( 0, 4, 20).matrix);
        copyMat(cats[pick_obj].matrix, t);
        break;

      default:
        break;
     }
     return;
   }
 }
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
    //drawStr(mode);
    drawMap(-5, 5.2, 60);
    drawfont0();
    if(mode == BREED||mode == CARRY){
      glTranslated(0,0.0,-5);
      drawPointer(px, py);
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

    //モード切替
    case 32: 
      mode = (mode+1)%3;
      if(pick_obj>=0){
        cats[pick_obj].matrix[13] = 0.0;
        cats[pick_obj].task = STAY;
        pick_obj = -1;
      }
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
  mouse_x = x;	mouse_y = y;

  if(state == GLUT_UP && mode == BREED){
    getWorldCood(x+6, y+30);
    liner_search(objX, objZ);
    printf("%d\n",n);

  }else if(state == GLUT_DOWN && mode == CARRY){
    if(pick_obj>=0){
      cats[pick_obj].matrix[13] = 0.0;
      cats[pick_obj].task = STAY;
      pick_obj = -1;
    }else{
      getWorldCood(x+6, y+30);
      liner_search(objX, objZ);
    }
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
  glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowSize (winW, winH);
  glutInitWindowPosition (50, 50);
  glutCreateWindow ("planet");

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
