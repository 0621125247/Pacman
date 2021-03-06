// mySecondProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL/glut.h>      // (or others, depending on the system in use)
#include <stdio.h>
#include <cmath>

#define RED 1.0,0.0,0.0		// RGB code for red color
#define WHITE_A 1.0,1.0,1.0,1.0 //REG code for white and alpha
#define BLACK_A 0.0,0.0,0.0,1.0 //REG code for white and alpha


int colorMode = 0;
float phi = 0;
float deltaPhi = 0;
// WCS volume limit
float left = -3.0;
float right = 3.0;
float bottom = -3.0;
float top = 3.0;
float znear = 0;
float zfar = -10.0;

// RCS for window  limit
int win_width = 640;
int win_height = 480;
float win_position_x = 100;
float win_position_y = 100;
//for rotate mouth
float rotateOn = -45;

//for delete point

float movew ;
float moves ;
float deltaMoveW = 0.05;
float deltaMoveS = 0.05;
float rotateP = 0;


float scalePX = 0.1;
float scalePY = 0.1;

float r, g, b, r2, g2, b2, r3, g3, b3 = 0;

int eat = 0;
//change rotate
int role = 3;
// mouse position start
float xstart = 347;
float ystart = 258;
//locate
float ptx_1 = -10; float pty_1 = 0;
float ptx_2 = -20; float pty_2 = 0;
float ptx_3 = -30; float pty_3 = 0;
//blind point
int mana = 0;

void mouse(int button, int state, int x, int y) {
	float xUnitRatio = (right - left) / (float)win_width;
	float yUnitRatio = (top - bottom) / (float)win_height;
	int xMovePixel;
	int yMovePixel;
	float xMoveUnit;
	float yMoveUnit;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		xMovePixel = x - xstart;
		yMovePixel = win_height - y - ystart;
		xMoveUnit = xMovePixel * xUnitRatio;
		yMoveUnit = yMovePixel * yUnitRatio;
		glTranslatef(xMoveUnit, yMoveUnit, 0);
		xstart = x;
		ystart = win_height - y;
		printf("mouse x=%3.3f, y=%3.3f\n", xstart, ystart);
	}
	glutPostRedisplay();
}



void motion(int x, int y) {
	glTranslatef((x - xstart)*right / (float)win_width, (win_height - y - ystart)*top / (float)win_height, 0);
	xstart = x;
	ystart = win_height - y;
	printf("motion x=%3.3f, y=%3.3f\n", xstart, ystart);
	glutPostRedisplay();
}


void init(void) {
	glClearColor(WHITE_A);                 // Set display-window color to white.

	glMatrixMode(GL_PROJECTION);           // Set projection parameters.
	glLoadIdentity();
	glOrtho(left, right, bottom, top, znear, zfar);
}

int nside = 100;

void pacmanOn() {
	//on
	glPopMatrix();
	glColor3f(1, 1.5, 0);
	glRotatef(rotateOn, 0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < nside; i++) {
		float pi = 3.14159265;
		float theta = i * pi / nside;
		float x = cos(theta + phi);
		float y = sin(theta + phi);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}

void pacman() {

	//head
	glRotatef(rotateP, 0, 0, 1);
	glPushMatrix();
	glColor3f(5, 1.5, 0);
	glRotatef(-20, 0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < nside; i++) {
		float pi = 3.14159265;
		float theta = i * pi / nside;
		float x = cos(theta + phi);
		float y = sin(theta + phi);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1.5, 0);
	glRotatef(-150, 0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < nside; i++) {
		float pi = 3.14159265;
		float theta = i * pi / nside;
		float x = cos(theta + phi);
		float y = sin(theta + phi);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}
void point() {
	glBegin(GL_POLYGON);
	glScalef(scalePX,scalePY, 1);
	glColor3f(0, 0, 0);
	for (int i = 0; i < nside; i++) {
		float pi = 3.14159265;
		float theta = i * 2*pi / nside;
		float x = cos(theta + phi);
		float y = sin(theta + phi);
		glVertex2f(x, y);
	}
	glEnd();

}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);            // Clear display window.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	//blind point
	if (mana == 0) {
		glPushMatrix();
		glColor3f(r3, g3, b3);
		glScalef(scalePX, scalePY, 0.1);
		glTranslatef(ptx_3, pty_3, 0);
		point();
		glPopMatrix();
		glPushMatrix();
		glColor3f(r, g, b);
		glScalef(scalePX, scalePY, 1);
		glTranslatef(ptx_1, pty_1, 0);
		point();
		glPopMatrix();
		glPushMatrix();
		glColor3f(r2, g2, b2);
		glScalef(scalePX, scalePY, 0.1);
		glTranslatef(ptx_2, pty_2, 0);
		point();
		glPopMatrix();
	}
	if (mana == 1) {
		glPushMatrix();
		glColor3f(1, 1, 1);
		glScalef(scalePX, scalePY, 0.1);
		glTranslatef(ptx_3, pty_3, 0);
		point();
		glPopMatrix();
	}
	if (mana == 2) {
		glPushMatrix();
		glColor3f(1, 1, 1);
		glScalef(scalePX, scalePY, 1);
		glTranslatef(ptx_1, pty_1, 0);
		point();
		glPopMatrix();
	}
	if (mana == 3) {
		glPushMatrix();
		glColor3f(r2, g2, b2);
		glScalef(scalePX, scalePY, 0.1);
		glTranslatef(ptx_2, pty_2, 0);
		point();
		glPopMatrix();
	}
	
	//pacman
	glTranslatef(moves, movew, 0);
	if (role==1) {
		glRotated(-90,0,0,1);
		glScalef(0.5, 0.5, 0);
		pacman();
		pacmanOn();
	}
	if (role == 2) {
		glRotatef(90, 0, 0, 1);
		glScalef(0.5, 0.5, 0);
		pacman();
		pacmanOn();
	}
	if (role == 3) {
		glRotatef(-360,0,0,1);
		glScalef(0.5, 0.5, 0);
		pacman();
		pacmanOn();
	}
	if (role == 4) {
		glRotatef(180,0,0,1);
		glScalef(0.5, 0.5, 0);
		pacman();
		pacmanOn();
	}

	//screen
	/*if (moves > right) {
		moves = -moves;
	}
	else if (moves < left) {
		moves = -moves;
	}
	if (movew > top) {
		movew = movew;
	}
	else if (movew < bottom +0.10) {
		movew = -movew;
	}
	*/


	glFlush();     // Process all OpenGL routines as quickly as possible.
	glMatrixMode(GL_PROJECTION);
}

void blind() {

	float movex = moves * 10;
	float movey = movew * 10;
	//function
	if (movex > ptx_1) {
		mana = 1;
	}
	if (movex > ptx_1) {
		if (movex > ptx_2) {
			mana = 2;
		}
	}
	if (movex > ptx_1) {
		if (movex > ptx_2) {
		}if (movex > ptx_3) {
			mana = 3;
		}
	}
	printf("pacman x=%3.3f, y=%3.3f\n", movex, movew);
	printf("point1 x=%3.3f, y=%3.3f\n", ptx_1, pty_1);
	printf("point2 x=%3.3f, y=%3.3f\n", ptx_2, pty_2);
	printf("point3 x=%3.3f, y=%3.3f\n", ptx_3, pty_3);
	
	glutPostRedisplay();
}

void idle()
{
	if (moves < left)
	{
		moves = -moves;
	}

	if (movew > top)
	{
		movew =- moves ;
	}
	if (movew < bottom)
	{
		movew =- movew;
	}

	if (eat == 0) {

		rotateOn -= 2;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int w, int h) {
	switch (key)
	{
	case 'w':
		movew += 0.1;
		role = 1;
		break;
		glutPostRedisplay();
	case 's':
		movew -= 0.1;
		role = 2;
		break;
		glutPostRedisplay();
	case 'a':
		moves -= 0.1;
		role = 3;
		break;
		glutPostRedisplay();
	case 'd':
		moves += 0.1;
		role = 4;
		break;
		glutPostRedisplay();
	}
}

void reshape(int w, int h) {
	float aspect = (float)w / h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (aspect >= 1.0)
	{
		glOrtho(left*aspect, right*aspect, bottom, top, znear, zfar);
	}
	else {
		glutPostRedisplay();
	}
}

void main(int argc, char** argv) {
	// initializing routine
	glutInit(&argc, argv);                              // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);        // Set display mode./GLUT_SINGLE-->ใช้1 frameBuffer/GLUT_RGB-->ใช้สี RGB
	glutInitWindowPosition(win_position_x, win_position_y); //Set top-left display-window position./กำหนดจุดแรก บนหน้าจอ
	glutInitWindowSize(win_width, win_height); // Set display-window width and height./
	glutCreateWindow("Pacman");     // Create display window.

													   //user initialization routine
	init();															// user initializing routine

	glutReshapeFunc(reshape);																//callback register function
	glutDisplayFunc(display);					// Send graphics to display window.
	//glutMouseFunc(mouse);								// callback for mouse button and position
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);							// callback for mouse motion
	
	glutMainLoop();										// Loop over registered function
														// Display everything and wait.
}