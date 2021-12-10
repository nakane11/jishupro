#include <GL/glut.h>
#include <math.h>

#include "tex.h"
#include "cat_matrix.h"
#include "action.h"

const float DEG2RAD = 3.14159/180;

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

void drawCat(int i)
{
  int a = nextAction(i);
  
  double x = getMat(i, 0); double y= getMat(i, 1); double z = getMat(i, 2);
  double theta = getMat(i, 3); double size = getMat(i, 4);
  double r = getMat(i, 5);  double g = getMat(i, 6); double b = getMat(i, 7);

  glColor3d(r, g, b);

  glPushMatrix();
  {
    glTranslated( x, y, z);
    glRotated (theta, 0.0, 1.0, 0.0);
    drowCuboid(2.0*size, 1.0*size, 3.0*size); //胴体
    

    glPushMatrix();
      glTranslated(0*size, 1.3*size, 1.4*size); //頭
      facedisplay(1.0*size, 0.8*size,0.7*size);
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
}