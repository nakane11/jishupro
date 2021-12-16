#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#define checkImageWidth 16
#define checkImageHeight 16

#define faceImageWidth 16
#define faceImageHeight 16
GLubyte checkImage[checkImageWidth][checkImageHeight][3];

GLubyte image[faceImageWidth][faceImageHeight][3];

void makeSmileImage(void){
    int i, j;
    int w = 255;
    for (i = 0; i < faceImageWidth; i++) {
        for (j = 0; j < faceImageHeight; j++) {
            image[i][j][0] = (GLubyte) 0;
            image[i][j][1] = (GLubyte) 0;
            image[i][j][2] = (GLubyte) 0;
        }
    }

    for (i = 9; i < 11; i++) {
        for (j = 7; j < 9; j++) {
            image[i][j][0] = (GLubyte) 0;
            image[i][j][1] = (GLubyte) 0;
            image[i][j][2] = (GLubyte) 255;
        }
    }
    image[5][1][0] = (GLubyte) w; image[5][1][1] = (GLubyte) w; image[5][1][2] = (GLubyte) w;
    image[5][2][0] = (GLubyte) w; image[5][2][1] = (GLubyte) w; image[5][2][2] = (GLubyte) w;
    image[5][3][0] = (GLubyte) w; image[5][3][1] = (GLubyte) w; image[5][3][2] = (GLubyte) w;

    image[5][12][0] = (GLubyte) w; image[5][12][1] = (GLubyte) w; image[5][12][2] = (GLubyte) w;
    image[5][13][0] = (GLubyte) w; image[5][13][1] = (GLubyte) w; image[5][13][2] = (GLubyte) w;
    image[5][14][0] = (GLubyte) w; image[5][14][1] = (GLubyte) w; image[5][14][2] = (GLubyte) w;

    image[6][0][0] = (GLubyte) w; image[6][0][1] = (GLubyte) w; image[6][0][2] = (GLubyte) w;
    image[6][4][0] = (GLubyte) w; image[6][4][1] = (GLubyte) w; image[6][4][2] = (GLubyte) w;
    image[6][11][0] = (GLubyte) w; image[6][11][1] = (GLubyte) w; image[6][11][2] = (GLubyte) w;
    image[6][15][0] = (GLubyte) w; image[6][15][1] = (GLubyte) w; image[6][15][2] = (GLubyte) w;

}

// void makeCheckImage(void){
//     int i, j, c;
//     for (i = 0; i < checkImageWidth; i++) {
//         for (j = 0; j < checkImageHeight; j++) {
//             // c = ((((i&0x8)==0)^((j&0x8)==0)))*255;
//             c = ((i%4)<2)*255;
//             checkImage[i][j][0] = (GLubyte) c;
//             checkImage[i][j][1] = (GLubyte) c;
//             checkImage[i][j][2] = (GLubyte) c;
//         }
//     }
//     // checkImage[32][32][0] = (GLubyte) 1;
//     // checkImage[32][32][1] = (GLubyte) 1;
//     // checkImage[32][32][2] = (GLubyte) 1;
// }

void texinit(void){
    makeSmileImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, faceImageWidth,
    faceImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
    &image[0][0][0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
}

void facedisplay(float a, float b, float c){
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.8); glVertex3f(-a, -b, c);
        glTexCoord2f(0.0, 0.0); glVertex3f(-a, b, c);
        glTexCoord2f(1.0, 0.0); glVertex3f(a, b, c);
        glTexCoord2f(1.0, 0.8); glVertex3f(a, -b, c);
    glEnd();
}