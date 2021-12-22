#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "tex.h"
#include "matrix_function.h"

//-----------------------------------------------------------------------------------

static const GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
static const GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat light_specular[]={1.0,1.0,1.0,1.0};

//-----------------------------------------------------------------------------------

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

//直方体
void drowCuboid(double a, double b, double c){
  GLdouble vertex[][3] = {
      { -a/2.0, -b/2.0, -c/2.0 },
      {  a/2.0, -b/2.0, -c/2.0 },
      {  a/2.0,  b/2.0, -c/2.0 },
      { -a/2.0,  b/2.0, -c/2.0 },
      { -a/2.0, -b/2.0,  c/2.0 },
      {  a/2.0, -b/2.0,  c/2.0 },
      {  a/2.0,  b/2.0,  c/2.0 },
      { -a/2.0,  b/2.0,  c/2.0 }
    };
  int face[][4] = {//面の定義
      { 3, 2, 1, 0 },
      { 1, 2, 6, 5 },
      { 4, 5, 6, 7 },
      { 0, 4, 7, 3 },
      { 0, 1, 5, 4 },
      { 2, 3, 7, 6 }
    };
  GLdouble normal[][3] = {//面の法線ベクトル
    { 0.0, 0.0, -1.0 },
    { 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    {-1.0, 0.0, 0.0 },
    { 0.0,-1.0, 0.0 },
    { 0.0, 1.0, 0.0 }
  };
    glPushMatrix();
      
      glBegin(GL_QUADS);
      for (int j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]); //法線ベクトルの指定
        for (int i = 0; i < 4; ++i) {
          glVertex3dv(vertex[face[j][i]]);
        }
      }
      glEnd();
    glPopMatrix();
}

//2D四角形
void Square2D(int x1,int y1,int x2, int y2,float size){
 glLineWidth(size);
 glBegin(GL_LINE_LOOP);
 glVertex2f(x1,y1);
 glVertex2f(x2,y1);
 glVertex2f(x2,y2);
 glVertex2f(x1,y2);
 glEnd();
}

void drawCat(int i)
{
 
  double size = cats[i].scale;

  glPushMatrix();
  {
    //色の設定
    GLfloat color[] = {cats[i].r, cats[i].g, cats[i].b, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

    glMultMatrixf( cats[i].matrix );

    drowCuboid(2.0*size, 1.0*size, 3.0*size); //胴体
    
    glPushMatrix();
      glTranslated(0*size, 1.3*size, 1.4*size); //頭
      glRotated(cats[i].neck_angle, 1 , 0, 0);

      //テクスチャマッピング
      facedisplay(cats[i].face, 1.0*size, 0.8*size,0.7*size);

      drowCuboid(2.0*size,  1.6*size,1.4*size);
      


      glPushMatrix();
        glTranslated(-0.7*size, 0.8*size, 0.0); //左耳
        glRotated(-90, 1 , 0, 0);
        glutSolidCone(0.3*size, 0.6*size, 20, 20);
      glPopMatrix();

      glPushMatrix();
        glTranslated(0.7*size, 0.8*size, 0.0); //左耳
        glRotated(-90, 1 , 0, 0);
        glutSolidCone(0.3*size, 0.6*size, 20, 20);
      glPopMatrix();
      
    glPopMatrix();
    
  }
  glPopMatrix();

  glFlush();
}

void drawMap(double x, double z){
  GLfloat inv[16];
  gluInvertMatrix(camera.matrix, inv);
  glColor3d(1.0, 1.0, 1.0);

  Square2D(x+1.3, z-1.3, x-1.3, z+1.3,1.0f); //四角形

  glPointSize(5.0f); //点
  glBegin(GL_POINTS);
    glVertex2f(x+inv[12]/70, z+inv[14]/70);

    for(int i=0;i<n;i++){
      glPushMatrix();
        glColor3d(cats[i].r, cats[i].g, cats[i].b);
        glVertex2f(x+cats[i].x/70, z+cats[i].z/70);
      glPopMatrix();
    }

  glEnd();
}

void drawPointer(double cx, double cy){
  glColor3d(1.0, 1.0, 1.0);
  glLineWidth(20);   

  glBegin(GL_LINES);                                    // 横線
    glVertex2f(-0.5, cy);
    glVertex2f(0.5, cy);
  glEnd();

  glBegin(GL_LINES);                                    // 縦線
    glVertex2f(cx, -0.5);
    glVertex2f(cx, 0.5);
  glEnd();
}