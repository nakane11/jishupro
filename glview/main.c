#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "draw_function.h"
#include "cat_matrix.h"

//-----------------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------------

// 視点情報
static double distance = 5.0, pitch = 0.0, yaw = 0.0;

// マウス入力情報
GLint mouse_button = -1;
GLint mouse_x = 0, mouse_y = 0;

//-----------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------
void init(void)
{
  initMat(6);
  
  // クリアの値の設定
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glClearDepth( 1.0 );

  // デプステストを行う
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LESS );
  glShadeModel (GL_SMOOTH);

}

//-----------------------------------------------------------------------------------
// レンダリング
//-----------------------------------------------------------------------------------
void display(void)
{

  // フレームバッファのクリア
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // 視点の設定
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // マウス入力で視点を移動
  glTranslatef( -yaw, pitch, -distance );
  //初期位置
  glPushMatrix();
  {
    for(int i=1;i<=n;i++){
      DrawCat(getMat(i, 0), getMat(i, 1), getMat(i, 2),
              getMat(i, 3), getMat(i, 4),
              getMat(i, 5), getMat(i, 6), getMat(i, 7));
    }
  }
  glPopMatrix();
  
  glutSwapBuffers();
}


//-----------------------------------------------------------------------------------
// ウィンドウリサイズのコールバック関数
//-----------------------------------------------------------------------------------
void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
}

//-----------------------------------------------------------------------------------
// キーボード入力のコールバック関数
//-----------------------------------------------------------------------------------
void keyboard (unsigned char key, int x, int y)
{
  switch (key) {
  case 27:
    freeMat();
    exit(0);
    break;
  }
}

//-----------------------------------------------------------------------------------
// マウスクリックのコールバック関数
//-----------------------------------------------------------------------------------
void mouse(int button, int state, int x, int y)
{
  mouse_button = button;
  mouse_x = x;	mouse_y = y;

  if(state == GLUT_UP){
    mouse_button = -1;
  }

  glutPostRedisplay();
}

//-----------------------------------------------------------------------------------
// マウス移動のコールバック関数
//-----------------------------------------------------------------------------------
void motion(int x, int y)
{
  switch(mouse_button){
  case GLUT_LEFT_BUTTON:

    if( x == mouse_x && y == mouse_y )
      return;

    yaw -= (GLfloat) (x - mouse_x) / 100.0;
    pitch -= (GLfloat) (y - mouse_y) / 100.0;

    break;

  case GLUT_RIGHT_BUTTON:

    if( y == mouse_y )
      return;

    if( y < mouse_y )
      distance += (GLfloat) (mouse_y - y)/50.0;
    else
      distance -= (GLfloat) (y-mouse_y)/50.0;

    if( distance < 1.0 ) distance = 1.0;
    if( distance > 10.0 ) distance = 10.0;

    break;
  }

  mouse_x = x;
  mouse_y = y;

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
  glutInitWindowSize (1280, 960);
  glutInitWindowPosition (50, 50);
  glutCreateWindow ("planet");

  init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);

  glutMainLoop();

  return 0;
}
