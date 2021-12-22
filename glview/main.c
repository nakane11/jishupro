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

MatArray array1, array2;

//-----------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------
void init(void)
{
  initCat(10); //ねこ生成
  texinit(); //テクスチャ作成
  unitMat(camera.matrix); //カメラ座標初期化
}



//-----------------------------------------------------------------------------------
// レンダリング
//-----------------------------------------------------------------------------------
//60Hz

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
    
    drawMap(-5.4, 6.3);
    drawPointer(0.0, 0.0);

    // glBegin(GL_TRIANGLES);

    //   glVertex2f(-1.0f, -1.0f);
    //   glVertex2f(-1.0f, 1.0f);
    //   glVertex2f(1.0f, -1.0f);
    // glEnd();
    

    }
  glPopMatrix();

  init3d();
  // 視点を移動
  glMultMatrixf( camera.matrix );
  
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
  yaw=0; pitch=0; distance=0; rx=0;
  switch (key) {
    //視点高さ
    case 'z':
      pitch = -(GLfloat) 0.4;
      break;
    case 'x':
      pitch = (GLfloat) 0.4;
      break;
    //前後方向
    case 's':
       distance = -(GLfloat) 0.4;
      break;
    case 'w':
      distance = (GLfloat) 0.4;
      break;
    //左右回転
    case 'a':
      rx = -(GLfloat) 1;
      break;
    case 'd':
      rx = (GLfloat) 1;
      break;

    case 27:
      exit(0);
      break;
  }
  //カメラの行列を更新
  array1 = tlMat( -yaw, pitch, -distance);
  //printf("1:%f %f %f %f\n",array1.matrix[12],array1.matrix[13],array1.matrix[14],array1.matrix[15]);
  array2 = y_rtMat(rx);
  //printf("%f %f %f %f\n",array2.matrix[12],array2.matrix[13],array2.matrix[14],array2.matrix[15]);
  // printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n\n",
  //       array2.matrix[0],array2.matrix[1],array2.matrix[2],array2.matrix[3],
  //       array2.matrix[4],array2.matrix[5],array2.matrix[6],array2.matrix[7],
  //       array2.matrix[8],array2.matrix[9],array2.matrix[10],array2.matrix[11],
  //       array2.matrix[12],array2.matrix[13],array2.matrix[14],array2.matrix[15]);
  dotMat(array1.matrix, camera.matrix);
  printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n\n",
        array1.matrix[0],array1.matrix[1],array1.matrix[2],array1.matrix[3],
        array1.matrix[4],array1.matrix[5],array1.matrix[6],array1.matrix[7],
        array1.matrix[8],array1.matrix[9],array1.matrix[10],array1.matrix[11],
        array1.matrix[12],array1.matrix[13],array1.matrix[14],array1.matrix[15]);
  //printf("2:%f %f %f %f\n",array1.matrix[12],array1.matrix[13],array1.matrix[14],array1.matrix[15]);

  dotMat(array2.matrix, array1.matrix);
  //printf("%f %f %f %f\n",array2.matrix[12],array2.matrix[13],array2.matrix[14],array2.matrix[15]);
  copyMat(camera.matrix, array2.matrix);

  //printf("3:%f %f %f %f\n",camera.matrix[12],camera.matrix[13],camera.matrix[14],camera.matrix[15]);
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
