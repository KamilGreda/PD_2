#include <iostream>
#include <GL/freeglut.h>


const int glutWindowWidth = 800;
const int glutWindowHeight = 600;

class C_FIGURA
{
public:

	enum e_ksztalt //potrzebne do przekazania funkcji draw, co ma rysowac
	{
		circle = 0, square = 4, heksagon = 6
	};

	float x, y;
	float r, g, b;

	e_ksztalt shape; //przechowuje informacje o ksztalcie

	C_FIGURA *next; //wskazniki na nastepnego i poprzedniego bohatera, umozliwiaja przelaczanie
	C_FIGURA *prev;
	

	void Draw(C_FIGURA::e_ksztalt ksztalt);

	C_FIGURA(float _x, float _y)//WSZYSCY SA ZIELONYMI KWADRATAMI
	{

		x = _x;
		y = _y;
		shape = square;
		this->zmien_kolor();
	}

	void zmien_kolor() //zmienia kolor na zielony
	{
		r = 0;
		g = 1;
		b = 0;
	}

};

C_FIGURA lewa(-2.0, 0); //globalna definicja figur
C_FIGURA srodkowa(0.0, 0);
C_FIGURA prawa(2.0, 0);

C_FIGURA *aktualna = &lewa;//wskaznik na aktualnego bohatera

using namespace std;

//tworzy zapetlona strukture danych
void utworz_powiazania() 
{
	lewa.next = &srodkowa;
	lewa.prev = &prawa;

	srodkowa.next = &prawa;
	srodkowa.prev = &lewa;

	prawa.next = &lewa;
	prawa.prev = &srodkowa;

}


//rysuje rozne figury zaleznie od parametru, umozliwia to zapamietanie ksztaltow bohaterow
void C_FIGURA::Draw(C_FIGURA::e_ksztalt ksztalt)
{

	switch (ksztalt)
	{

	case circle:
	{
		double radius = 0.5;
		float rad_alpha = 0;
		float PI = 3.1415;
		glPushMatrix();



		glTranslated(x, y, 0);

		glColor3d(r, g, b);

		glBegin(GL_POLYGON);
		{
			for (int i = 0; i <360; i++)
			{
				rad_alpha = (i* PI) / 180;
				glVertex3d(radius*cos(rad_alpha), radius* sin(rad_alpha), 0);
			}
		}
		glEnd();
		glPopMatrix();
		break;
	}

	case square:
	{
		double side = 0.5;

		glPushMatrix();
		glTranslated(x, y, 0);


		glColor3d(r, g, b);

		glBegin(GL_POLYGON);
		{
			glVertex3d(-side / 2, side / 2, 0);
			glVertex3d(side / 2, side / 2, 0);
			glVertex3d(side / 2, -side / 2, 0);
			glVertex3d(-side / 2, -side / 2, 0);
		}
		glEnd();
		glPopMatrix();

		break;
	}

	case heksagon:
	{
		double radius = 0.5;
		float rad_alpha = 0;
		float PI = 3.1415;
		glPushMatrix();

		glTranslated(x, y, 0);

		glColor3d(r, g, b);

		glBegin(GL_POLYGON);
		{
			for (int i = 0; i <360; i = 360 / 6 + i)
			{
				rad_alpha = (i* PI) / 180;
				glVertex3d(radius*cos(rad_alpha), radius* sin(rad_alpha), 0);
			}
		}
		glEnd();
		glPopMatrix();

		break;
	}
	}

}

float proportion = (float)glutWindowWidth / (float)glutWindowHeight;

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

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		aktualna->y += 0.15;

		break;

	case 's':
		aktualna->y -= 0.15;;

		break;

	case 'a':
		aktualna->x -= 0.15;
		break;

	case 'd':
		aktualna->x += 0.15;
		break;



	case 'q':
		aktualna->zmien_kolor();
		aktualna = aktualna->prev;
		break;

	case 'e':
		aktualna->zmien_kolor();
		aktualna = aktualna->next;
		break;



	case 'i':
		aktualna->shape = C_FIGURA::e_ksztalt::square;
		break;

	case 'o':
		aktualna->shape = C_FIGURA::e_ksztalt::circle;
		break;

	case 'p':
		aktualna->shape = C_FIGURA::e_ksztalt::heksagon;
		break;

	default:
		break;
	}
}

static void display(void)
{
	// wyczyszenie sceny
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	

	lewa.Draw(lewa.shape);
	srodkowa.Draw(srodkowa.shape);
	prawa.Draw(prawa.shape);

	glutKeyboardFunc(keyboard);
	
	
	glPopMatrix();

	glutSwapBuffers();
}

void Timer(int value)
{
	value++;

	if (value % 2)
	{
	aktualna->r = 0;
	aktualna->g = 0;
	aktualna->b = 1;
	}
	else
	{
		aktualna->b = 0;
		aktualna->r = 1;
	}
	// wyœwietlenie sceny
	glutPostRedisplay();

	// nastêpne wywo³anie funkcji timera
	glutTimerFunc(432, Timer, value);
}

int main(int argc, char *argv[])
{

	utworz_powiazania(); //nadaje wartosci wskaznikom w obiektach klasy C_FIGURA 
	
	glutInitWindowSize(glutWindowWidth, glutWindowHeight);
	glutInitWindowPosition(40, 40);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("OpenGLUT Shapes"); //tworzy okno, jak nazwa mowi

	glutPostRedisplay();
	glutReshapeFunc(resize);
	glutDisplayFunc(display);

	glutIdleFunc(idle);

	glutKeyboardFunc(keyboard);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// set white as clear colour
	glClearColor(1, 1, 1, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glutTimerFunc(432, Timer, 0);

	glutMainLoop();

	return 0;
}