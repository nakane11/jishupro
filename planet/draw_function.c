#include <GL/glut.h>
#include <math.h>

const float DEG2RAD = 3.14159/180;

// GLubyte faceImage[16][checkImageHeight][3];
// void makeCheckImage(void){
//   int i, j, c;
//   for (i = 0; i < checkImageWidth; i++) {
//   for (j = 0; j < checkImageHeight; j++) {
//   c = ((((i&0x8)==0)^((j&0x8)==0)))*255;
//   checkImage[i][j][0] = (GLubyte) c;
//   checkImage[i][j][1] = (GLubyte) c;
//   checkImage[i][j][2] = (GLubyte) c;
//   }
//   }
// }

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

void DrawCat(double x, double y, double z, double theta, double size, double r, double g, double b)//中心(x,y,z)
{
  glColor3d(r, g, b);
  
  glPushMatrix();
  {
    glTranslated( x, y, z);
    glRotated (theta, 0.0, 1.0, 0.0);
    drowCuboid(2.0*size, 1.0*size, 3.0*size); //胴体
    

    glPushMatrix();
      glTranslated(0*size, 1.3*size, 1.4*size); //頭
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