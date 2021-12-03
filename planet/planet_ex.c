#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#include "get_clock_now.h"
#include "draw_function.h"

//-----------------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------------
// 再生、停止フラグ
//static int flg_play = 1;

// 視点情報
static double distance = 5.0, pitch = 0.0, yaw = 0.0;

// マウス入力情報
GLint mouse_button = -1;
GLint mouse_x = 0, mouse_y = 0;

//位置情報
static int N=30;
int n=20; int m=8;
double *matrix;



// // クロック
// static double clock_now, clock_pre;

// // 日
// static double day = 0;

// static const GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
// static const GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
// static const GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};

// static const GLfloat mat_default_color[] = { 1.0, 1.0, 1.0, 1.0 };
// static const GLfloat mat_default_specular[] = { 0.0, 0.0, 0.0, 0.0 };
// static const GLfloat mat_default_shininess[] = { 100.0 };
// static const GLfloat mat_default_emission[] = {0.0, 0.0, 0.0, 0.0};


//-----------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------
void init(void)
{
  for (int i=0;i<=n;i++) {
    matrix[i * m + 0]=(rand()%40-20)/10.0;
    matrix[i * m + 1]= 0.0;
    matrix[i * m + 2]=(rand()%40-20)/10.0;
    matrix[i * m + 3]=rand()%360-180.0;
    matrix[i * m + 4]=0.2;
    matrix[i * m + 5]=(rand()%10)/10.0;
    matrix[i * m + 6]=(rand()%10)/10.0;
    matrix[i * m + 7]=(rand()%10)/10.0;

    printf("Value of d = %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, \n",matrix[i*m+0], matrix[i*m+1], matrix[i*m+2],
              matrix[i*m+3], matrix[i*m+ 4],
              matrix[i*m+5], matrix[i*m+6], matrix[i*m+7]);
  }
  

  

  // クリアの値の設定
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glClearDepth( 1.0 );

  // デプステストを行う
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LESS );

  glShadeModel (GL_SMOOTH);

  // デフォルトライト
  // glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  // glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  // glLightfv(GL_LIGHT0, GL_DIFFUSE, light_ambient);
  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);

  // // デフォルトマテリアル
  // glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_default_color);
  // glMaterialfv(GL_FRONT, GL_AMBIENT, mat_default_color);
  // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_default_specular);
  // glMaterialfv(GL_FRONT, GL_SHININESS, mat_default_shininess);

  // クロックの初期化
  //clock_now = clock_pre = get_clock_now();
}

//-----------------------------------------------------------------------------------
// レンダリング
//-----------------------------------------------------------------------------------
void display(void)
{
  // クロックの更新
    // clock_pre = clock_now;
    // clock_now = get_clock_now();

  // 1秒で1日分動くとする
  // if( flg_play )
  //   day += (clock_now - clock_pre);

  // フレームバッファのクリア
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // 視点の設定
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // マウス入力で視点を移動
  glTranslatef( -yaw, pitch, -distance );

  glPushMatrix();
  {
    for(int i=1;i<=n;i++){
      DrawCat(matrix[i * m + 0], matrix[i * m + 1], matrix[i * m + 2],
              matrix[i * m + 3], matrix[i * m + 4],
              matrix[i * m + 5], matrix[i * m + 6], matrix[i * m + 7]);
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
  // case 'z':
  //   if( flg_play == 1 ) flg_play = 0;
  //   else flg_play = 1;
  //   usleep(1000);
  //   break;
  case 27:
    free(matrix);
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
  matrix =(double *)malloc(sizeof(double) * N * 8);
  
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
