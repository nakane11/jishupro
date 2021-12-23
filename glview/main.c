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

int winW = 1280, winH = 960;

float px=0, py=0;

MatArray array1, array2;

double objX, objY, objZ;

//-----------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------
void init(void)
{
  initCat(10); //ねこ生成
  texinit(); //テクスチャ作成
  unitMat(camera.matrix); //カメラ座標初期化
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
  printf("(%d, %d) -> (%lf, %lf, %lf)\n",TargetX,TargetY,-objX,objY,-objZ);
	
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
    
    drawMap(-5.8, 6.1, 60);
    drawPointer(px, py);

    }
  glPopMatrix();

  init3d();
  
  // 視点を移動
  glMultMatrixf( camera.matrix );

  drawFloor(60); //地面  
  
  updateFunc();
  for(int i=0;i<n;i++){
    drawCat(i);
  }

  glutSwapBuffers();
}

// void timer(int value){
//   for(int i=0;i<n;i++){
//       printf("%lf\t", cats[i].x);
//   }
//   printf("\n");
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
      rx = -(GLfloat) 2;
      break;
    case 'd':
      rx = (GLfloat) 2;
      break;
    case 'j':
      px += 0.4;
      break;
    case 'l':
      px -= 0.4;
      break;
    case 'i':
      py += 0.4;
      break;
    case 'k':
      py -= 0.4;
      break;


    case 27:
      exit(0);
      break;
  }
  //カメラの行列を更新
  array1 = tlMat( -yaw, pitch, -distance);
  array2 = y_rtMat(rx);
  dotMat(array1.matrix, camera.matrix);
  dotMat(array2.matrix, array1.matrix);
  copyMat(camera.matrix, array2.matrix);

}

// -----------------------------------------------------------------------------------
// マウスクリックのコールバック関数
// -----------------------------------------------------------------------------------
void mouse(int button, int state, int x, int y)
{
  mouse_button = button;
  mouse_x = x;	mouse_y = y;

  if(state == GLUT_UP){
    mouse_button = -1;
  }else{
    getWorldCood(x, y);
    printf("%f, %f\n",px,py);
  }
  
  glutPostRedisplay();
}

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
  glutInitWindowSize (winW, winH);
  glutInitWindowPosition (50, 50);
  glutCreateWindow ("planet");

  init();
  
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  // glutTimerFunc(1000,timer,0);
  glutMouseFunc(mouse);
  // glutMotionFunc(motion);

  glutMainLoop();

  return 0;
}
