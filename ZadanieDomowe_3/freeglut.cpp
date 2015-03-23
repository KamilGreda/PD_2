#include <iostream>
#include <GL/freeglut.h>


const int glutWindowWidth = 800;
const int glutWindowHeight = 600;

class C_FIGURA
{
public:

	enum e_ksztalt
	{
		circle = 0, square = 4, heksagon = 6
	};

	float x, y;
	float r, g, b;

	e_ksztalt shape;

	C_FIGURA *next;
	C_FIGURA *prev;
	

	void Draw(C_FIGURA::e_ksztalt ksztalt);

	C_FIGURA(float _x, float _y)//WSZYSCY SA NIEBIESKIMI KWADRATAMI
	{

		x = _x;
		y = _y;
		shape = square;
		this->zmien_kolor();
	}

	void zmien_kolor() //zmienia kolor na niebieski
	{
		r = 0;
		g = 0;
		b = 1;
	}

};

C_FIGURA lewa(-2.0, 0);
C_FIGURA srodkowa(0.0, 0);
C_FIGURA prawa(2.0, 0);

C_FIGURA *aktualna = &lewa;//wskaznik na aktualnego bohatera



bool byl_pierwszy_obieg = 0;


using namespace std;

void utworz_powiazania()
{
	

	lewa.next = &srodkowa;
	lewa.prev = &prawa;

	srodkowa.next = &prawa;
	srodkowa.prev = &lewa;

	prawa.next = &lewa;
	prawa.prev = &srodkowa;

}



float proportion = (float)glutWindowWidth / (float)glutWindowHeight;

/* GLUT callback Handlers */
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


void C_FIGURA:: Draw(C_FIGURA::e_ksztalt ksztalt)
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
		glRotated(0, 1.0, 0.0, 0.0);
		glRotated(0, 0.0, 1.0, 0.0);
		glRotated(0, 0.0, 0.0, 1.0);

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
		glRotated(0, 1.0, 0.0, 0.0);
		glRotated(0, 0.0, 1.0, 0.0);
		glRotated(0, 0.0, 0.0, 1.0);

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
		glRotated(0, 1.0, 0.0, 0.0);
		glRotated(0, 0.0, 1.0, 0.0);
		glRotated(0, 0.0, 0.0, 1.0);


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
	
	aktualna->r = 0.1; //zmiana koloru aktualnego bohatera
	aktualna->g = 0.05;
	aktualna->b = 0.0;

	lewa.Draw(lewa.shape);
	srodkowa.Draw(srodkowa.shape);
	prawa.Draw(prawa.shape);


	glutKeyboardFunc(keyboard);
	
	glPopMatrix();

	glutSwapBuffers();
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




	glutMainLoop();

	return 0;
}