#include <iostream>
#include<GL/freeglut.h>
#include <ctime>
#include <cstdlib>
#include <GL/glext.h>
#include <cmath>
using namespace std;
int gameSpeed = 10;
int _width = 400, _height = 400;
GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
GLfloat light_ambient[] = {0.1, 0.5, 0.5, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {1.0, 0.0, -5.0, 0.0};
GLdouble angle=0.0; //�ngulo da c�mera
GLdouble lx=0.0f,lz=-1.0f; //dire��o da c�mera
GLdouble x=0.0f,z=5.0f; //posi��o da c�mera

void drawWalls(){
	glColor3f(1.0f, 1.0f, 1.0f);
    // Desenhar corpo
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidCube(3.0f);
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();glLoadIdentity();
	gluLookAt(x, 1.0f, z,
              x+lx, 1.0f,  z+lz,
			  0.0f, 1.0f,  0.0f);
    // Desenhar solo
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-50.0f, 0.0f, -50.0f);
		glVertex3f(-50.0f, 0.0f,  50.0f);
		glVertex3f( 50.0f, 0.0f,  50.0f);
		glVertex3f( 50.0f, 0.0f, -50.0f);
	glEnd();

    //Muro trás
	glPushMatrix();
	glTranslated(0, 0, 50);
	glRotated(90, -1, 0, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-50.0f, 0.0f, 0);
		glVertex3f(-50.0f, 0.0f, 10.0f);
		glVertex3f( 50.0f, 0.0f, 10.0f);
		glVertex3f( 50.0f, 0.0f, 0);
	glEnd();
	glPopMatrix();

	//Muro frente
	glPushMatrix();
	glTranslated(0, 0, -50);
	glRotated(90, -1, 0, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-50.0f, 0.0f, 0);
		glVertex3f(-50.0f, 0.0f, 10.0f);
		glVertex3f( 50.0f, 0.0f, 10.0f);
		glVertex3f( 50.0f, 0.0f, 0);
	glEnd();
	glPopMatrix();

    // Muro lado esquerdo
	glPushMatrix();
	glTranslated(-50, 0, 0);
	glRotated(90, 0, 1, 0);
	glRotated(90, -1, 0, 0);
    glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(50.0f, 0.0f, 0);
		glVertex3f(50.0f, 0.0f, 10.0f);
		glVertex3f(-50.0f, 0.0f, 10.0f);
		glVertex3f(-50.0f, 0.0f, 0);
	glEnd();
	glPopMatrix();

	// Muro lado direito
	glPushMatrix();
	glTranslated(50, 0, 0);
	glRotated(90, 0, 1, 0);
	glRotated(90, -1, 0, 0);
    glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(50.0f, 0.0f, 0);
		glVertex3f(50.0f, 0.0f, 10.0f);
		glVertex3f(-50.0f, 0.0f, 10.0f);
		glVertex3f(-50.0f, 0.0f, 0);
	glEnd();
	glPopMatrix();


	glDisable(GL_TEXTURE_2D);

    //Desenhar as paredes
	for(int i = -3; i < 3; i++){
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0,0,j * 10.0);
			drawWalls();
			glPopMatrix();
		}
	}
	glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy) {
	float amount = 0.5f;
	cout << "X " << lx << " Y " << lz << endl;
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

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("MY GAME");
	glutDisplayFunc(draw);
	glutTimerFunc(10,timerFunc,0);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	configureCam();
	glutMainLoop();
	return 0;
}
