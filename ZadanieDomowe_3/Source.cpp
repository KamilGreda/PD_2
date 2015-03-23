/*#include <iostream>
#include <math.h>

#include <GL/freeglut.h>

const int glutWindowWidth = 640;
const int glutWindowHeight = 480;

float proportion = (float)glutWindowWidth / (float)glutWindowHeight;

 GLUT callback Handlers 
static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;
	proportion = ar;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void idle(void)
{
	glutPostRedisplay();
}

void DrawRectangle(void)
{
	double height = 0.5;
	double width = 1.0;

	glPushMatrix();
	// TODO
	// test functions below (glTranslated, glRotated, glColor3d) - what
//	happen when you change their arguments ?
		// does their order change the result?
		glTranslated(0, 0, 0);
	glRotated(0, 1.0, 0.0, 0.0);
	glRotated(0, 0.0, 1.0, 0.0);
	glRotated(0, 0.0, 0.0, 1.0);

	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	{
		glVertex3d(-width / 2, height / 2, 0);
		glVertex3d(width / 2, height / 2, 0);
		glVertex3d(width / 2, -height / 2, 0);
		glVertex3d(-width / 2, -height / 2, 0);
	}
	glEnd();
	glPopMatrix();
}

void DrawCircle(void)
{
	double height = 0.5;
	double width = 1.0;

	glPushMatrix();
	// TODO
	// test functions below (glTranslated, glRotated, glColor3d) - what
	//happen when you change their arguments ?
		// does their order change the result?
		glTranslated(0, 0, 0);
	glRotated(0, 1.0, 0.0, 0.0);
	glRotated(0, 0.0, 1.0, 0.0);
	glRotated(0, 0.0, 0.0, 1.0);


	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	int r = 2;
	float rad_alpha = 0;
	float PI = 3.1415;
	{
		//glVertex3d(0, 0, 0);
		for (int i = 0; i <360; i = 360 / 5 + i)
		{
			rad_alpha = (i* PI) / 180;
			glVertex3d(r*cos(rad_alpha), r* sin(rad_alpha), 0);
		}
	}
	glEnd();
	glPopMatrix();
}

void DrawOsie(void)
{
	double height = 0.5;
	double width = 1.0;

	glPushMatrix();
	// TODO
	// test functions below (glTranslated, glRotated, glColor3d) - what
	//happen when you change their arguments ?
		// does their order change the result?
		glTranslated(0, 0, 0);
	glRotated(0, 1.0, 0.0, 0.0);
	glRotated(0, 0.0, 1.0, 0.0);
	glRotated(0, 0.0, 0.0, 1.0);


	glColor3d(1.0, 0.0, 0.0);

	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);

	glVertex3d(0, -0.1, 0);
	glVertex3d(5, -0.1, 0);
	glVertex3d(5, 0.1, 0);
	glVertex3d(0, 0.1, 0);

	glEnd();


	glEnd();

	glColor3d(0, 0.0, 1.0);
	glBegin(GL_LINE);

	glVertex3d(0, 0, 5);

	glEnd();
	glPopMatrix();
}

static void display(void)
{
	// wyczyszenie sceny
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	DrawOsie();
	glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	// it's still possible to use console to print messages
	printf("Hello openGL world!");
	// the same can be done with cout / cin

	glutInitWindowSize(glutWindowWidth, glutWindowHeight);
	glutInitWindowPosition(40, 40);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("OpenGLUT Shapes");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// set white as clear colour
	glClearColor(1, 1, 1, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glutMainLoop();

	return 0;


	void C_FIGURA:: DrawHeksagon(void)
	{
	double radius = 0.5;
	float rad_alpha = 0;
	float PI = 3.1415;
	glPushMatrix();

	glTranslated(x, y, 0);
	glRotated(0, 1.0, 0.0, 0.0);
	glRotated(0, 0.0, 1.0, 0.0);
	glRotated(0, 0.0, 0.0, 1.0);


	glColor3d(0.0, 0.0, 1.0);

	glBegin(GL_POLYGON);
	{
	//glVertex3d(0, 0, 0);
	for (int i = 0; i <360; i = 360 / 6 + i)
	{
	rad_alpha = (i* PI) / 180;
	glVertex3d(radius*cos(rad_alpha), radius* sin(rad_alpha), 0);
	}
	}
	glEnd();
	glPopMatrix();
	}

	void C_FIGURA:: DrawSquare(void)
	{
	double side= 0.5;

	glPushMatrix();
	glTranslated(x, y, 0);
	glRotated(0, 1.0, 0.0, 0.0);
	glRotated(0, 0.0, 1.0, 0.0);
	glRotated(0, 0.0, 0.0, 1.0);

	glColor3d(1.0, 0.0, 0.0);

	glBegin(GL_POLYGON);
	{
	glVertex3d(-side / 2, side / 2, 0);
	glVertex3d(side / 2, side / 2, 0);
	glVertex3d(side / 2, -side / 2, 0);
	glVertex3d(-side / 2, -side / 2, 0);
	}
	glEnd();
	glPopMatrix();
	}

}*/