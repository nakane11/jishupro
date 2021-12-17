#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define faceImageWidth 32
#define faceImageHeight 32

typedef enum{
    HAPPY,
    SLEEPY,
    ANGRY,
    NORMAL
}face;

GLubyte faceImage[faceImageWidth][faceImageHeight][3];

void makeFaceImage(void){
    int i, j;
    int b = 0; int w = 255;
    //base
    for (i = 0; i < faceImageWidth; i++) {
        for (j = 0; j < faceImageHeight; j++) {
            faceImage[i][j][0] = (GLubyte) b;
            faceImage[i][j][1] = (GLubyte) b;
            faceImage[i][j][2] = (GLubyte) b;
        }
    }

    //nose
    for (i = 9; i < 11; i++) {
        for (j = 7; j < 9; j++) {
            faceImage[i][j][0] = (GLubyte) 120;
            faceImage[i][j][1] = (GLubyte) 0;
            faceImage[i][j][2] = (GLubyte) 255;
        }
    }
    for (i = 25; i < 27; i++) {
        for (j = 7; j < 9; j++) {
            faceImage[i][j][0] = (GLubyte) 120;
            faceImage[i][j][1] = (GLubyte) 0;
            faceImage[i][j][2] = (GLubyte) 255;
        }
    }
    for (i = 9; i < 11; i++) {
        for (j = 23; j < 25; j++) {
            faceImage[i][j][0] = (GLubyte) 120;
            faceImage[i][j][1] = (GLubyte) 0;
            faceImage[i][j][2] = (GLubyte) 255;
        }
    }
    for (i = 25; i < 27; i++) {
        for (j = 23; j < 25; j++) {
            faceImage[i][j][0] = (GLubyte) 120;
            faceImage[i][j][1] = (GLubyte) 0;
            faceImage[i][j][2] = (GLubyte) 255;
        }
    }

    //happy eyes
    faceImage[5][1][0] = (GLubyte) w; faceImage[5][1][1] = (GLubyte) w; faceImage[5][1][2] = (GLubyte) w;
    faceImage[5][2][0] = (GLubyte) w; faceImage[5][2][1] = (GLubyte) w; faceImage[5][2][2] = (GLubyte) w;
    faceImage[5][3][0] = (GLubyte) w; faceImage[5][3][1] = (GLubyte) w; faceImage[5][3][2] = (GLubyte) w;

    faceImage[5][12][0] = (GLubyte) w; faceImage[5][12][1] = (GLubyte) w; faceImage[5][12][2] = (GLubyte) w;
    faceImage[5][13][0] = (GLubyte) w; faceImage[5][13][1] = (GLubyte) w; faceImage[5][13][2] = (GLubyte) w;
    faceImage[5][14][0] = (GLubyte) w; faceImage[5][14][1] = (GLubyte) w; faceImage[5][14][2] = (GLubyte) w;

    faceImage[6][0][0] = (GLubyte) w; faceImage[6][0][1] = (GLubyte) w; faceImage[6][0][2] = (GLubyte) w;
    faceImage[6][4][0] = (GLubyte) w; faceImage[6][4][1] = (GLubyte) w; faceImage[6][4][2] = (GLubyte) w;
    faceImage[6][11][0] = (GLubyte) w; faceImage[6][11][1] = (GLubyte) w; faceImage[6][11][2] = (GLubyte) w;
    faceImage[6][15][0] = (GLubyte) w; faceImage[6][15][1] = (GLubyte) w; faceImage[6][15][2] = (GLubyte) w;

    //sleepy eyes
    faceImage[7][17][0] = (GLubyte) w; faceImage[7][17][1] = (GLubyte) w; faceImage[7][17][2] = (GLubyte) w;
    faceImage[7][18][0] = (GLubyte) w; faceImage[7][18][1] = (GLubyte) w; faceImage[7][18][2] = (GLubyte) w;
    faceImage[7][19][0] = (GLubyte) w; faceImage[7][19][1] = (GLubyte) w; faceImage[7][19][2] = (GLubyte) w;

    faceImage[7][28][0] = (GLubyte) w; faceImage[7][28][1] = (GLubyte) w; faceImage[7][28][2] = (GLubyte) w;
    faceImage[7][29][0] = (GLubyte) w; faceImage[7][29][1] = (GLubyte) w; faceImage[7][29][2] = (GLubyte) w;
    faceImage[7][30][0] = (GLubyte) w; faceImage[7][30][1] = (GLubyte) w; faceImage[7][30][2] = (GLubyte) w;

    faceImage[6][16][0] = (GLubyte) w; faceImage[6][16][1] = (GLubyte) w; faceImage[6][16][2] = (GLubyte) w;
    faceImage[6][20][0] = (GLubyte) w; faceImage[6][20][1] = (GLubyte) w; faceImage[6][20][2] = (GLubyte) w;
    faceImage[6][27][0] = (GLubyte) w; faceImage[6][27][1] = (GLubyte) w; faceImage[6][27][2] = (GLubyte) w;
    faceImage[6][31][0] = (GLubyte) w; faceImage[6][31][1] = (GLubyte) w; faceImage[6][31][2] = (GLubyte) w;

    //angry eyes
    faceImage[21][1][0] = (GLubyte) w; faceImage[21][1][1] = (GLubyte) w; faceImage[21][1][2] = (GLubyte) w;
    faceImage[21][14][0] = (GLubyte) w; faceImage[21][14][1] = (GLubyte) w; faceImage[21][14][2] = (GLubyte) w;

    faceImage[22][2][0] = (GLubyte) w; faceImage[22][2][1] = (GLubyte) w; faceImage[22][2][2] = (GLubyte) w;
    faceImage[22][3][0] = (GLubyte) w; faceImage[22][3][1] = (GLubyte) w; faceImage[22][3][2] = (GLubyte) w;
    faceImage[22][12][0] = (GLubyte) w; faceImage[22][12][1] = (GLubyte) w; faceImage[22][12][2] = (GLubyte) w;
    faceImage[22][13][0] = (GLubyte) w; faceImage[22][13][1] = (GLubyte) w; faceImage[22][13][2] = (GLubyte) w;

    faceImage[23][4][0] = (GLubyte) w; faceImage[23][4][1] = (GLubyte) w; faceImage[23][4][2] = (GLubyte) w;
    faceImage[23][11][0] = (GLubyte) w; faceImage[23][11][1] = (GLubyte) w; faceImage[23][11][2] = (GLubyte) w;

    //normal eyes
    faceImage[21][17][0] = (GLubyte) w; faceImage[21][17][1] = (GLubyte) w; faceImage[21][17][2] = (GLubyte) w;
    faceImage[21][18][0] = (GLubyte) w; faceImage[21][18][1] = (GLubyte) w; faceImage[21][18][2] = (GLubyte) w;
    faceImage[21][29][0] = (GLubyte) w; faceImage[21][29][1] = (GLubyte) w; faceImage[21][29][2] = (GLubyte) w;
    faceImage[21][30][0] = (GLubyte) w; faceImage[21][30][1] = (GLubyte) w; faceImage[21][30][2] = (GLubyte) w;

    faceImage[22][17][0] = (GLubyte) w; faceImage[22][17][1] = (GLubyte) w; faceImage[22][17][2] = (GLubyte) w;
    faceImage[22][18][0] = (GLubyte) w; faceImage[22][18][1] = (GLubyte) w; faceImage[22][18][2] = (GLubyte) w;
    faceImage[22][29][0] = (GLubyte) w; faceImage[22][29][1] = (GLubyte) w; faceImage[22][29][2] = (GLubyte) w;
    faceImage[22][30][0] = (GLubyte) w; faceImage[22][30][1] = (GLubyte) w; faceImage[22][30][2] = (GLubyte) w;

}


void texinit(void){
    makeFaceImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, faceImageWidth,
    faceImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
    &faceImage[0][0][0]);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
}

void facedisplay(int t, float a, float b, float c){
    switch (t){
        case HAPPY:
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.4); glVertex3f(-a, -b, c);
                glTexCoord2f(0.0, 0.0); glVertex3f(-a, b, c);
                glTexCoord2f(0.5, 0.0); glVertex3f(a, b, c);
                glTexCoord2f(0.5, 0.4); glVertex3f(a, -b, c);
            glEnd();
            break;
        case SLEEPY:
            glBegin(GL_QUADS);
                glTexCoord2f(0.5, 0.4); glVertex3f(-a, -b, c);
                glTexCoord2f(0.5, 0.0); glVertex3f(-a, b, c);
                glTexCoord2f(1.0, 0.0); glVertex3f(a, b, c);
                glTexCoord2f(1.0, 0.4); glVertex3f(a, -b, c);
            glEnd();
            break;
        case ANGRY:
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.9); glVertex3f(-a, -b, c);
                glTexCoord2f(0.0, 0.5); glVertex3f(-a, b, c);
                glTexCoord2f(0.5, 0.5); glVertex3f(a, b, c);
                glTexCoord2f(0.5, 0.9); glVertex3f(a, -b, c);
            glEnd();
            break;
        case NORMAL:
            glBegin(GL_QUADS);
                glTexCoord2f(0.5, 0.9); glVertex3f(-a, -b, c);
                glTexCoord2f(0.5, 0.5); glVertex3f(-a, b, c);
                glTexCoord2f(1.0, 0.5); glVertex3f(a, b, c);
                glTexCoord2f(1.0, 0.9); glVertex3f(a, -b, c);
            glEnd();
            break;
        default:
            printf("facedisplay default");
        
    }
}