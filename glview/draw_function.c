#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "tex.h"
#include "matrix_function.h"
#include "draw_function.h"

#define PI 3.141592653589793


//-----------------------------------------------------------------------------------

static const GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
static const GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat light_specular[]={1.0,1.0,1.0,1.0};

char str0[] = "MODE =  ";
char strs[3][6] = { "WATCH" , "BREED" , "CARRY" };

typedef struct {
    int r, x, y, z,
        ax, az, bx, bz, cx, cz;
} Cloud;

static Cloud clouds[30];

Vector line_vector[100];
int line_vec_num;
//-----------------------------------------------------------------------------------

void init3d(void){
  // クリアの値の設定
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

//長方形
void Square2D(float x1,float y1,float x2, float y2,float size){
 glLineWidth(size);
 glBegin(GL_LINE_LOOP);
 glVertex2f(x1,y1);
 glVertex2f(x2,y1);
 glVertex2f(x2,y2);
 glVertex2f(x1,y2);
 glEnd();
}

void SquareFill2D(float x1,float y1,float x2, float y2){
  glBegin(GL_QUADS);
  glVertex2f(x1,y1);
  glVertex2f(x2,y1);
  glVertex2f(x2,y2);
  glVertex2f(x1,y2);
  glEnd();
}

//雲
void makeCloud(void){
  for(int s=0; s<30; s++){;
    clouds[s].r = rand()%180;
    clouds[s].x = rand()%300-150;
    clouds[s].y = rand()%40+5;
    clouds[s].z = (rand()%2*2-1)*sqrt((rand()%10/10+1)*25000-clouds[s].x*clouds[s].x-clouds[s].y*clouds[s].y);

    clouds[s].ax = rand()%16+16;
    clouds[s].az = rand()%16+16;

    clouds[s].bx = clouds[s].ax-rand()%10;
    clouds[s].bz = clouds[s].az-rand()%10;

    clouds[s].cx = clouds[s].ax-rand()%10;
    clouds[s].cz = clouds[s].az-rand()%10;
  }
}

void drawCloud(void){
  GLfloat color[] = {1.0, 1.0, 1.0, 1.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
 
  for(int s=0;s<30;s++){
    glPushMatrix();{
      glRotated(clouds[s].r, 0 , 1, 0);
      glTranslated(clouds[s].x, clouds[s].y, clouds[s].z);
    
      int h = 4;
      drowCuboid(clouds[s].ax, h, clouds[s].az);

      glPushMatrix();{
        glTranslated(0,-h/2,0);
        drowCuboid(clouds[s].bx, h, clouds[s].bz);
      }glPopMatrix();

      glPushMatrix();{
        glTranslated(0,h/2,0);
        drowCuboid(clouds[s].cx, h, clouds[s].cz);
      }glPopMatrix();
    }
    glPopMatrix();
  }   
}

//猫
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

void drawMap(double x, double z, double range){
  
  //サーチライト
  glColor3d(1.0, 241.0/255, 0.0);
  glLineWidth(1.0f);
  glBegin(GL_LINE_LOOP);
    glVertex2f(x+inv[12]/70, z+inv[14]/70);
    glVertex2f(x+(-5*inv[0]+15*inv[8]+inv[12])/70, z+(-5*inv[2]+15*inv[10]+inv[14])/70);
    glVertex2f(x+(5*inv[0]+15*inv[8]+inv[12])/70, z+(5*inv[2]+15*inv[10]+inv[14])/70);
  glEnd();

  glPointSize(5.0f);
  glBegin(GL_POINTS);
    glVertex2f(x+inv[12]/70, z+inv[14]/70); //カメラ位置

    for(int i=0;i<n;i++){
      glPushMatrix();
        glColor3d(cats[i].r, cats[i].g, cats[i].b);
        glVertex2f(x+cats[i].x/70, z+cats[i].z/70); //猫位置
      glPopMatrix();
    }
  glEnd();
  
  glLineWidth(0.8f);
  glColor3d(1.0, 1.0, 1.0);
  for(int k = 0; k<(line_vec_num-1); k++){ //線
      glBegin( GL_LINES );
      glVertex2f(x+line_vector[k].x/70, z+line_vector[k].z/70);
      glVertex2f(x+line_vector[k+1].x/70, z+line_vector[k+1].z/70);
      glEnd();
  }
  
  glColor3d(0.0, 0.0, 0.0);
  SquareFill2D(x-range/70, z-range/70, x+range/70, z+range/70); //マップ
  glColor3d(255/255, 140/255.0, 0.0);
  Square2D(x-range/70, z-range/70, x+range/70, z+range/70, 1.5f); //マップ枠
  
  Square2D(x-range/70-0.21, z-range/70, x-range/70-0.05, z+range/70, 1.0f); //高度計
  SquareFill2D(x-range/70-0.21, z-range/70, x-range/70-0.05, z-range/70+inv[13]/70*2.18);
}


void drawPointer(double cx, double cy){

  glColor3d(1.0, 1.0, 1.0);
  glLineWidth(20);   

  glBegin(GL_LINES);                                    // 横線
    glVertex2f(cx-0.3, cy);
    glVertex2f(cx+0.3, cy);
  glEnd();

  glBegin(GL_LINES);                                    // 縦線
    glVertex2f(cx, cy-0.3);
    glVertex2f(cx, cy+0.3);
  glEnd();
}

void drawColorPointer(double cx, double cy, int color, int pm){
  if(color==0)
    glColor3d(1.0, 0.0, 0.0);
  else if(color==1)
    glColor3d(0.0, 1.0, 0.0);
  else if(color==2)
    glColor3d(0.0, 0.0, 1.0);
  else
    glColor3d(1.0, 1.0, 1.0);
    
  glLineWidth(20);   

  glBegin(GL_LINES);                                    // 横線
    glVertex2f(cx-0.2, cy);
    glVertex2f(cx+0.2, cy);
  glEnd();
  if(pm==1){
    glBegin(GL_LINES);                                    // 縦線
    glVertex2f(cx, cy-0.2);
    glVertex2f(cx, cy+0.2);
    glEnd();
  }
}

void drawFloor(int r){
  glPushMatrix();
  {
    GLfloat color[] = {0.0/255, 84.0/255, 58.0/255, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
 
    glRotated(-90, 1 , 0, 0);
    glTranslated(0, 0, -0.5);
    SquareFill2D(-r, -r, r, r);
  }
  glPopMatrix();
}


