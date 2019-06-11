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
int baseX = 0, baseY = 0;
GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
GLfloat light_ambient[] = {0.1, 0.5, 0.5, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {1.0, 0.0, -5.0, 0.0};
GLdouble angle=0.0; //�ngulo da c�mera
GLdouble lx=0.0f,lz=-1.0f, ly = 0.0f; //dire��o da c�mera
GLdouble x=0.0f,z=5.0f, y = 3.0f; //posi��o da c�mera
GLuint textureID[4];
GLfloat v[8][3];

void setBoxSize(GLfloat size) {
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;
}

static void drawBox(GLenum type, int idTexture, GLfloat v[8][3]) {
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

    GLint i;
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
	setBoxSize(20);
	drawBox(GL_QUADS, 1, v);
	glDisable(GL_TEXTURE_2D);
}

void drawSmallWallMap() {
    glColor3d(0.5, 0.26, 0.26);
    glEnable(GL_TEXTURE_2D);
    glScaled(1, 1, .3);
    setBoxSize(5);
	drawBox(GL_QUADS, 0, v);
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

void drawSky()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[3]);
	glColor3d(1, 1, 1);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
		glVertex3f(-50.0f, 15.0f, -50.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-50.0f, 15.0f,  50.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f( 50.0f, 15.0f,  50.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f( 50.0f, 15.0f, -50.0f);
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


    GLfloat size = 6;
    setBoxSize(size);
    glPushMatrix();
        glTranslatef(48.0,0,0);
        glColor3d(0.5, 0.26, 0.26);
        glEnable(GL_TEXTURE_2D);
        glScaled(1, 1, .3);
        setBoxSize(6);

        v[1][0] = v[0][0] = -size / 2 - 3;
        v[2][0] = v[3][0] = -size / 2 - 3;

        v[6][1] = v[7][1] = size / 2 + 3;
        drawBox(GL_QUADS, 0, v);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-48.0,0,0);
        glColor3d(0.5, 0.26, 0.26);
        glEnable(GL_TEXTURE_2D);
        glScaled(1, 1, .3);
        setBoxSize(6);
        v[1][0] = v[0][0] = -size / 2;
        v[2][0] = v[3][0] = -size / 2;

        v[6][1] = v[7][1] = size / 2;

        v[2][1] = v[3][1] = size / 2 + 3;

        v[4][0] = v[5][0] = size / 2 + 3;
        v[6][0] = v[7][0] = size / 2 + 3;
        drawBox(GL_QUADS, 0, v);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(x, y, z,
              x+lx, y+ly,  z+lz,
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
		    x -= lx + amount;
			break;
		case GLUT_KEY_RIGHT :
		    x += lx + amount;
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

void processNormalKeys(unsigned char key, int xx, int yy) {
    float amount = 0.5f;

	switch (key) {
		case 'a':
		    //x += lx - amount;
			break;
		case 'd':
		    //x += lx + amount;
			break;
		case 'w':
			x += lx * amount;
			z += lz * amount;
			break;
		case 's':
			x -= lx * amount;
			z -= lz * amount;
			break;
	}

	if (key == 27)
		exit(0);
}

void loadTexture()
{
    loadBMP("bricks.bmp");
    glEnable(GL_TEXTURE_2D);

    glGenTextures(4, textureID);
    glBindTexture(GL_TEXTURE_2D, textureID[0]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    loadBMP("floor_fods.bmp");
    glBindTexture(GL_TEXTURE_2D, textureID[1]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    loadBMP("gelo.bmp");
    glBindTexture(GL_TEXTURE_2D, textureID[2]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    loadBMP("ceu.bmp");
    glBindTexture(GL_TEXTURE_2D, textureID[3]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void mouseMoviment(int x, int y) {
    if(x < baseX) {
        angle -= 0.03f;
        lx = sin(angle);
        lz = -cos(angle);
    }else if(x > baseX){
        angle += 0.03f;
        lx = sin(angle);
        lz = -cos(angle);
    }
    baseX = x;

    if(y < baseY) {
        ly += 0.03f;
    }else if(y > baseY){
        ly -= 0.03f;
    }
    baseY = y;

    if(x >= 580 || x <= 20)
        glutWarpPointer(_width / 2, y);

    if(y >= 580 || y <= 20)
        glutWarpPointer(x, _height / 2);
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
	glutPassiveMotionFunc(mouseMoviment);
	configureCam();
	loadTexture();
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(_width / 2, _height / 2);
	glutMainLoop();
	return 0;
}
