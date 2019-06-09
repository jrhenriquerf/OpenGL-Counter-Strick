#include <iostream>
#include<GL/freeglut.h>
#include <ctime>
#include <cstdlib>
#include <GL/glext.h>
#include <cmath>
#include "leitorBMP.h"

using namespace std;
int gameSpeed = 10;
int _width = 600, _height = 600;
GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
GLfloat light_ambient[] = {0.1, 0.5, 0.5, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {1.0, 0.0, -5.0, 0.0};
GLdouble angle=0.0; //�ngulo da c�mera
GLdouble lx=0.0f,lz=-1.0f; //dire��o da c�mera
GLdouble x=0.0f,z=5.0f; //posi��o da c�mera
GLuint textureID[2];

static void drawBox(GLfloat size, GLenum type, int idTexture)
{
    glBindTexture(GL_TEXTURE_2D, textureID[idTexture]);

    static GLfloat n[6][3] =
    {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
    };

    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--) {
        glBegin(type);
        glNormal3fv(&n[i][0]);
        glTexCoord2f(0.0, 1.0);
        glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2f(0.0, 0.0);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2f(1.0, 0.0);
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2f(1.0, 1.0);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

void drawWallMap() {
	glColor3d(0.8, 0.8, 0.9);
	glEnable(GL_TEXTURE_2D);
	drawBox(20, GL_QUADS, 1);
	glDisable(GL_TEXTURE_2D);
}

void drawSmallWallMap() {
    glColor3d(0.5, 0.26, 0.26);
    glEnable(GL_TEXTURE_2D);
    glScaled(1, 1, .3);
	drawBox(5, GL_QUADS, 0);
	glDisable(GL_TEXTURE_2D);
}

void drawAroundWalls() {
    glColor3d(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[1]);

    //Muro trás
	glPushMatrix();
	glTranslated(0, 0, 50);
	glRotated(90, -1, 0, 0);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
		glVertex3f(-50.0f, 0.0f, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-50.0f, 0.0f, 10.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f( 50.0f, 0.0f, 10.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f( 50.0f, 0.0f, 0);
	glEnd();
	glPopMatrix();

	//Muro frente
	glPushMatrix();
	glTranslated(0, 0, -50);
	glRotated(90, -1, 0, 0);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
		glVertex3f(-50.0f, 0.0f, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-50.0f, 0.0f, 10.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f( 50.0f, 0.0f, 10.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f( 50.0f, 0.0f, 0);
	glEnd();
	glPopMatrix();

    // Muro lado esquerdo
	glPushMatrix();
	glTranslated(-50, 0, 0);
	glRotated(90, 0, 1, 0);
	glRotated(90, -1, 0, 0);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
		glVertex3f(50.0f, 0.0f, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(50.0f, 0.0f, 10.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-50.0f, 0.0f, 10.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(-50.0f, 0.0f, 0);
	glEnd();
	glPopMatrix();

	// Muro lado direito
	glPushMatrix();
	glTranslated(50, 0, 0);
	glRotated(90, 0, 1, 0);
	glRotated(90, -1, 0, 0);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
		glVertex3f(50.0f, 0.0f, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(50.0f, 0.0f, 10.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-50.0f, 0.0f, 10.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(-50.0f, 0.0f, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawFloor() {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    // Desenhar solo
	glColor3d(1, 1, 1);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
		glVertex3f(-50.0f, 0.0f, -50.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-50.0f, 0.0f,  50.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f( 50.0f, 0.0f,  50.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f( 50.0f, 0.0f, -50.0f);
	glEnd();
	glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawBigBlocks() {
    //Desenhar blocos grandes
    glPushMatrix();
    glTranslatef(-20.0,0,-20.0);
    drawWallMap();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20.0,0,20.0);
    drawWallMap();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20.0,0,20.0);
    drawWallMap();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20.0,0,-20.0);
    drawWallMap();
    glPopMatrix();
}

void drawSmallBlocks() {
    //Desenhar bloquinhos
    glPushMatrix();
    glTranslatef(-32.0,0,-29.2);
    drawSmallWallMap();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(32.0,0,29.2);
    drawSmallWallMap();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-32.0,0,29.2);
    drawSmallWallMap();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(32.0,0,-29.2);
    drawSmallWallMap();
    glPopMatrix();
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(x, 3.0f, z,
              x+lx, 3.0f,  z+lz,
			  0.0f, 1.0f,  0.0f);

    drawFloor();
    drawAroundWalls();
    drawBigBlocks();
    drawSmallBlocks();

	glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy) {
	float amount = 0.5f;

	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.1f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.1f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * amount;
			z += lz * amount;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * amount;
			z -= lz * amount;
			break;
	}
}

void timerFunc(int x){
    glutPostRedisplay();
    glutTimerFunc(gameSpeed,timerFunc,0);
}

void configureCam(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}

void loadTexture()
{
    loadBMP("bricks.bmp");
    glEnable(GL_TEXTURE_2D);

    glGenTextures(2, textureID);
    glBindTexture(GL_TEXTURE_2D, textureID[0]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    loadBMP("gelo.bmp");
    glBindTexture(GL_TEXTURE_2D, textureID[1]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300,50);
	glutInitWindowSize(_width,_height);
	glutCreateWindow("MY GAME");
	glutDisplayFunc(draw);
	glutTimerFunc(10,timerFunc,0);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	configureCam();
	loadTexture();
	glutMainLoop();
	return 0;
}
