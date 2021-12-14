#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "tex.h"
//#include "cat_matrix.h"
//#include "action.h"
#include "matrix_function.h"

//const float DEG2RAD = 3.14159/180;

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

// double nextActionHoge(int i) {
//   int p = rand()%100;
//   return 0.0;
// }


void drawCat(int i)
{
  // double e = 1.0;
  // double f=1.0;
  //nextAction0(i, &e, &f);

  // static int count = 0;
  // double a = 0;
  // a = nextAction(1);
  // double a2 = 0.1;
  // nextAction2(i, &a2);
  //printf("%d action:%lf hoge:%lf\n", count, nextAction(1), nextActionHoge(1));
  //double a = 0.01;
  // if(count % 100 == 0 && i == 0){
  //   printf("%d a:%lf b:%lf func:%lf  action:%lf hoge:%lf\n", count, a, a2, nextAction(1), nextAction(1), nextActionHoge(1));
  // }
  //printf("%d %d %lf\n", count, i, a);
  // ++count;
  //////////////////////GLfloat *m = htm+16*i;
  //printf("%f %f %f %f\n",m[0],m[1],m[2],m[3]);
 
  // if(e!=0.0){
  //   htm_dot(m, htm_makeMat(0,0,e,f));
  //   //htm_setMat(htm, m,i);
  // }
  /////////////////////htm_dot(m, htm_makeMat(0,0,e,f));

  // double x = getMat(i, 0); double y= getMat(i, 1); double z = getMat(i, 2);
  // double theta = getMat(i, 3); 
  // double size = getMat(i, 4);
  // double r = getMat(i, 5);  double g = getMat(i, 6); double b = getMat(i, 7);
  double size = cats[i].scale;
  //printf("%lf\n",size);
 
  //printf("%f %f %f %f\n",cats[i].matrix[0],cats[i].matrix[1],cats[i].matrix[2],cats[i].matrix[3]);
  GLfloat *m = cats[i].matrix;

  glPushMatrix();
  {
    //色の設定
    GLfloat color[] = {cats[i].r, cats[i].g, cats[i].b, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

    glMultMatrixf( m );

    drowCuboid(2.0*size, 1.0*size, 3.0*size); //胴体
    
    glPushMatrix();
      glTranslated(0*size, 1.3*size, 1.4*size); //頭
      //glRotated(cats[i].neck_angle, 1 , 0, 0);

      //テクスチャマッピング
      texinit();
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

  glFlush();
}