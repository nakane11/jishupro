#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "draw_function.h"
#include "cat_matrix.h"
#include "tex.h"

//-----------------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------------

// 視点情報
static double dz = 5.0, dx = 0.0, dy = 0.0, rx = 0.0;

// マウス入力情報
GLint mouse_button = -1;
GLint mouse_x = 0, mouse_y = 0;

static const GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
static const GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};

//-----------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------
void init(void)
{
  initMat(20);
  //texinit();
  
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
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_ambient);
  //glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

}

//-----------------------------------------------------------------------------------
// レンダリング
//-----------------------------------------------------------------------------------
void display(void)
{

  // フレームバッファのクリア
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gluLookAt(0, 8, -10, 0, 1, 2, 0, 1, 0);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // マウス入力で視点を移動
  glTranslatef( -dx, dy, -dz );
  rx=rx-(int)(rx/360)*360;
  glRotated(rx, 0.0, 1.0, 0.0);
  
  //初期位置
  glPushMatrix();
  {
    //mydisplay(0.5, 0.4);
    for(int i=0;i<n;i++){
      drawCat(i);
    }
  }
  glPopMatrix();
  
  glutSwapBuffers();
}

void timer(int value){
  for(int i=0;i<n;i++){
      nextState(i);
      //printf("%d",(int)getMat(i,8));
  }
  //printf("\n");
  glutTimerFunc(1000,timer,0);
}


//-----------------------------------------------------------------------------------
// ウィンドウリサイズのコールバック関数
//-----------------------------------------------------------------------------------
void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1.0*2, 20.0*2);
}

//-----------------------------------------------------------------------------------
// キーボード入力のコールバック関数
//-----------------------------------------------------------------------------------
void keyboard (unsigned char key, int x, int y)
{
  switch (key) {
    case 'a':
      dx += (GLfloat) 0.2;
      break;
    case 'd':
      dx -= (GLfloat) 0.2;
      break;
    case 's':
      dz -= 0.2;
      break;
    case 'w':
      dz += 0.2;
      break;
    case 'z':
      rx -= (GLfloat) 1;
      break;
    case 'x':
      rx += (GLfloat) 1;
      break;
    case 27:
      freeMat();
      exit(0);
      break;
  }
}

//-----------------------------------------------------------------------------------
// マウスクリックのコールバック関数
//-----------------------------------------------------------------------------------
// void mouse(int button, int state, int x, int y)
// {
//   mouse_button = button;
//   mouse_x = x;	mouse_y = y;

//   if(state == GLUT_UP){
//     mouse_button = -1;
//   }

//   glutPostRedisplay();
// }

//-----------------------------------------------------------------------------------
// マウス移動のコールバック関数
//-----------------------------------------------------------------------------------
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
  glutTimerFunc(1000,timer,0);
  // glutMouseFunc(mouse);
  // glutMotionFunc(motion);

  glutMainLoop();

  return 0;
}
