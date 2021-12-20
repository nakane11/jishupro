#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "draw_function.h"
#include "tex.h"
#include "matrix_function.h"
#include "action.h"

#define PI 3.141592653589793

//-----------------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------------

// 視点情報
static double distance = 5.0, pitch = 0.0, yaw = 0.0, rx = 1.0;


// マウス入力情報
GLint mouse_button = -1;
GLint mouse_x = 0, mouse_y = 0;

static const GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
static const GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat light_specular[]={1.0,1.0,1.0,1.0};

//-----------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------
void init(void)
{
  initCat(10); //ねこの生成
  texinit();
}
void init3d(void){
  // クリアの値の設定
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glClearDepth( 1.0 );

  // デプステストを行う
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LESS );
  glShadeModel (GL_SMOOTH);

  // デフォルトライト
  
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

}

//-----------------------------------------------------------------------------------
// レンダリング
//-----------------------------------------------------------------------------------
//60Hz

void Square2D(int x1,int y1,int x2, int y2,float size){
 glLineWidth(size);
 glBegin(GL_LINE_LOOP);
 glVertex2i(x1,y1);
 glVertex2i(x2,y1);
 glVertex2i(x2,y2);
 glVertex2i(x1,y2);
 glEnd();
}
void display(void)
{
  // フレームバッファのクリア
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gluLookAt(0, 8, -10, 0, 1, 2, 0, 1, 0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glPushMatrix();{
    glDisable( GL_LIGHTING ); //光源処理無効
    glRotated(atan2(7,12)*360.0/(2*PI), 1.0, 0.0, 0.0);

    Square2D(4,5,6.9,6.9,1.0f); //四角形

    glPointSize(5.0f); //点
    glBegin(GL_POINTS);
      glVertex2f(4.5,5.5);
    glEnd();

    glLineWidth(20);   
    glBegin(GL_LINES);                                    //      線分の描画
      glVertex2f(-0.5, 0);
      glVertex2f(0.5, 0);
    glEnd();
    glBegin(GL_LINES);                                    //      線分の描画
      glVertex2f(0, -0.5);
      glVertex2f(0, 0.5);
    glEnd();

    }
  glPopMatrix();

  init3d();
  // 視点を移動
  glTranslatef( -yaw, pitch, -distance );
  rx=rx-(int)(rx/360)*360;
  glRotated(rx, 0.0, 1.0, 0.0);

  
  updateFunc();
 
  for(int i=0;i<n;i++){
    drawCat(i);
  }

  glutSwapBuffers();
}

// void timer(int value){
//   for(int i=0;i<n;i++){
//       nextState(i);
//       //printf("%d",(int)getMat(i,8));
//   }
//   printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
//   glutTimerFunc(1000,timer,0);
// }


//-----------------------------------------------------------------------------------
// ウィンドウリサイズのコールバック関数
//-----------------------------------------------------------------------------------
void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1.0*4, 20.0*4);
}

//-----------------------------------------------------------------------------------
// キーボード入力のコールバック関数
//-----------------------------------------------------------------------------------
void keyboard (unsigned char key, int x, int y)
{
  switch (key) {
    //視点高さ
    case 'z':
      pitch -= (GLfloat) 0.4;
      break;
    case 'x':
      pitch += (GLfloat) 0.4;
      break;
    //前後方向
    case 's':
       distance -= (GLfloat) 0.4;
      break;
    case 'w':
      distance += (GLfloat) 0.4;
      break;
    //左右回転
    case 'a':
      rx -= (GLfloat) 1;
      break;
    case 'd':
      rx += (GLfloat) 1;
      break;

    case 27:
      exit(0);
      break;
  }
}

// -----------------------------------------------------------------------------------
// マウスクリックのコールバック関数
// -----------------------------------------------------------------------------------
// void mouse(int button, int state, int x, int y)
// {
//   mouse_button = button;
//   mouse_x = x;	mouse_y = y;

//   if(state == GLUT_UP){
//     mouse_button = -1;
//   }

//   glutPostRedisplay();
// }

// -----------------------------------------------------------------------------------
// マウス移動のコールバック関数
// -----------------------------------------------------------------------------------
// void motion(int x, int y)
// {
//   switch(mouse_button){
//   case GLUT_LEFT_BUTTON:

//     if( x == mouse_x && y == mouse_y )
//       return;

//     yaw -= (GLfloat) (x - mouse_x) / 100.0;
//     pitch -= (GLfloat) (y - mouse_y) / 100.0;

//     break;

//   case GLUT_RIGHT_BUTTON:

//     if( y == mouse_y )
//       return;

//     if( y < mouse_y )
//       distance += (GLfloat) (mouse_y - y)/50.0;
//     else
//       distance -= (GLfloat) (y-mouse_y)/50.0;

//     if( distance < 1.0 ) distance = 1.0;
//     if( distance > 10.0 ) distance = 10.0;

//     break;
//   }

//   mouse_x = x;
//   mouse_y = y;

//   glutPostRedisplay();
// }

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
  glutInitWindowSize (1280, 960);
  glutInitWindowPosition (50, 50);
  glutCreateWindow ("planet");

  init();
  
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  //glutTimerFunc(1000,timer,0);
  // glutMouseFunc(mouse);
  // glutMotionFunc(motion);

  glutMainLoop();

  return 0;
}
