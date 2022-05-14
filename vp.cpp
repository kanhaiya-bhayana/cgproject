#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
// #include <GL/gl.h>
#include <time.h>
#include <sys/timeb.h>
#include <string.h>
#include <iostream>

using namespace std;
// global
static int window;
static int value = 0;

/************************************/

//CONSTANTS

#define HOUR_HAND_LENGTH 50.0
#define MINUTE_HAND_LENGTH 70.7106781187
#define SECOND_HAND_LENGTH 78.1024967591
#define CLOCK_RADIUS 80.0
#define PI 3.14159
#define CLOCK_VOL 100.00
#define ANGLE_ONE_MIN PI/30.0


float cloud_X = 0;
float cloud_Y = 0;
float cloud_X2 = 0;
float cloud_Y2 = 0;
int cloudStatus = 1;
int boatStatus = 1;
float boatX = 0;
float boatY = 0;

void drawBoat();
void tree();
void scene();
void drawSun();
void cloud();
void cloud2();
void drawClock();
void display();
void reshape(int, int);
void redraw(int);
// void keyboard();



//FUNCTION TO INITIALIZE STUFF
void init()
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(0);
	glMatrixMode(GL_PROJECTION);
    glShadeModel(GL_SMOOTH);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
}
void inits()
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(0);
	glMatrixMode(GL_PROJECTION);
    glShadeModel(GL_SMOOTH);
	glLoadIdentity();
	gluOrtho2D(0, 1200, 0, 800);
}





void menu(int num) {
    if (num == 0) {
        glutDestroyWindow(window);
        exit(0);
    }
    else {
        value = num;
    }
    glutPostRedisplay();
}

void createMenu(void) {
    int menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Analog Clock ", 1);
    glutAddMenuEntry("Scenery ", 2);
    glutAddMenuEntry("Exit ", 0);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void anyFunc(){
	glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

	if(value == 1){
		drawClock();
		glutReshapeFunc(reshape);
		glutTimerFunc(15, redraw, 1);
	}
	else{
		// glutKeyboardFunc(keyboard);
		inits();
		display();
	}

	glPopMatrix();
    glFlush();
}

void drawCircle(float cx, float cy, float r, int segments)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
}

void tree()
{
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(1.2, 0.5, 0.4);
	glVertex2i(338, 385);
	glVertex2i(340, 440);
	glVertex2i(338, 510);
	glVertex2i(358, 385);
	glVertex2i(362, 380);
	glEnd();
	glColor3f(0, 0.8, 0.1);
	drawCircle(328, 505, 20, 1000);
	glColor3f(0, 0.8, 0.1);
	drawCircle(348, 505, 20, 1000);
	glColor3f(0, 0.8, 0.1);
	drawCircle(368, 505, 20, 1000);
	glColor3f(0, 0.8, 0.1);
	drawCircle(318, 525, 20, 1000);
	glColor3f(0, 0.8, 0.1);
	drawCircle(338, 525, 20, 1000);
	glColor3f(0, 0.8, 0.1);
	drawCircle(358, 525, 20, 1000);
	glColor3f(0, 0.8, 0.1);
	drawCircle(378, 525, 20, 1000);
	glColor3f(0, 0.8, 0.1);
	drawCircle(328, 545, 20, 1000);
	glColor3f(0, 0.8, 0.1);
	drawCircle(348, 545, 20, 1000);
	glColor3f(0, 0.8, 0.1);
	drawCircle(368, 545, 20, 1000);
	glColor3f(0, 0.8, 0.1);
	drawCircle(348, 560, 20, 1000);
	glPopMatrix();
}

void scene()
{
	glPushMatrix();

	glBegin(GL_POLYGON);     //sky
	glColor3f(0.4, 0.5, 1.0);
	glVertex2i(0, 800);
	glVertex2i(1200, 800);
	glColor3f(0.7, 0.7, 1.0);
	glVertex2i(1200, 0);
	glVertex2i(0, 0);
	glEnd();

	glBegin(GL_POLYGON);    //middle ground
	glColor3f(0, 0.5, 0);
	glVertex2i(0, 200);
	glVertex2i(200, 350);
	glVertex2i(400, 400);
	glVertex2i(600, 350);
	glVertex2i(800, 320);
	glVertex2i(1000, 300);
	glColor3f(0.1, 0.9, 0.1);
	glVertex2i(1200, 200);
	glVertex2i(1200, 100);
	glVertex2i(0, 100);
	glEnd();

	glBegin(GL_POLYGON);    //river
	glColor3f(0.4, 0.4, 1.1);
	glVertex2i(0, 100);
	glVertex2i(200, 120);
	glVertex2i(400, 140);
	glVertex2i(600, 150);
	glColor3f(0.2, 0.3, 1.1);
	glVertex2i(800, 140);
	glVertex2i(1000, 120);
	glVertex2i(1200, 100);
	glVertex2i(1200, 0);
	glVertex2i(0, 0);
	glEnd();

	tree();

	glBegin(GL_POLYGON);    //house
	glColor3f(0.9, 0.7, 0.1);
	glVertex2i(350, 380);
	glVertex2i(350, 460);
	glVertex2i(430, 460);
	glVertex2i(430, 380);
	glEnd();

	glBegin(GL_POLYGON);    //mushroom
	glColor3f(1, 0, 0);
	glVertex2i(910, 315);
	glVertex2i(920, 330);
	glVertex2i(930, 330);
	glVertex2i(940, 315);
	glEnd();

	glBegin(GL_POLYGON);     //mushroom
	glColor3f(0.9, 0.8, 0);
	glVertex2i(922, 300);
	glVertex2i(919, 315);
	glVertex2i(931, 315);
	glVertex2i(928, 300);
	glEnd();

	glBegin(GL_POLYGON);      //house
	glColor3f(0.9, 0, 0);
	glVertex2i(340, 460);
	glVertex2i(390, 500);
	glVertex2i(440, 460);
	glEnd();

	glBegin(GL_POLYGON);     //door
	glColor3f(1, 1, 0);
	glVertex2i(370, 380);
	glVertex2i(370, 430);
	glVertex2i(410, 430);
	glVertex2i(410, 380);
	glEnd();

	glBegin(GL_POLYGON);        //grass 1
	glColor3f(0, 0.8, 0.1);
	glVertex2i(780, 315);
	glVertex2i(770, 330);
	glVertex2i(780, 325);
	glVertex2i(775, 340);
	glVertex2i(785, 330);
	glVertex2i(787, 350);
	glVertex2i(790, 330);
	glVertex2i(800, 340);
	glVertex2i(795, 325);
	glVertex2i(805, 330);
	glVertex2i(795, 315);
	glEnd();
	 
	glBegin(GL_POLYGON);        //grass 2
	glColor3f(0, 0.8, 0.1);
	glVertex2i(810, 310);
	glVertex2i(800, 325);
	glVertex2i(810, 320);
	glVertex2i(805, 335);
	glVertex2i(815, 325);
	glVertex2i(817, 345);
	glVertex2i(820, 325);
	glVertex2i(830, 335);
	glVertex2i(825, 320);
	glVertex2i(835, 325);
	glVertex2i(825, 310);
	glEnd();

	glBegin(GL_POLYGON);        //grass 3
	glColor3f(0, 0.8, 0.1);
	glVertex2i(440, 375);
	glVertex2i(430, 390);
	glVertex2i(440, 385);
	glVertex2i(435, 400);
	glVertex2i(445, 390);
	glVertex2i(447, 410);
	glVertex2i(450, 390);
	glVertex2i(460, 400);
	glVertex2i(455, 385);
	glVertex2i(465, 390);
	glVertex2i(455, 375);
	glEnd();

	glBegin(GL_POLYGON);        //Grass 4 Big
	glColor3f(0.0, 0.5, 0.1); 
	glVertex2i(1085, 105);
	glVertex2i(1070, 125);
	glVertex2i(1060, 135);
	glVertex2i(1080, 125);
	glVertex2i(1070, 155);
	glVertex2i(1090, 135);
	glVertex2i(1095, 175);
	glColor3f(0.8, 0.8, 0.1);
	glVertex2i(1100, 135);
	glVertex2i(1120, 155);
	glVertex2i(1110, 125);
	glVertex2i(1130, 135);
	glVertex2i(1120, 125);
	glVertex2i(1105, 105);
	glEnd();

	glBegin(GL_POLYGON);         //Grass 5 Big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(1135, 100);
	glVertex2i(1120, 120); 
	glVertex2i(1110, 130);
	glVertex2i(1130, 120);
	glVertex2i(1120, 150);
	glVertex2i(1140, 130);
	glVertex2i(1145, 170);
	glColor3f(0.8, 0.8, 0.1);
	glVertex2i(1150, 130);
	glVertex2i(1170, 150);
	glVertex2i(1160, 120);
	glVertex2i(1180, 130);
	glVertex2i(1170, 120);
	glVertex2i(1155, 100);
	glEnd();

	glBegin(GL_POLYGON);          //Grass 6 Big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(35, 100);
	glVertex2i(20, 120);
	glVertex2i(10, 130);
	glVertex2i(30, 120);
	glVertex2i(20, 150);
	glVertex2i(40, 130);
	glVertex2i(45, 170);
	glColor3f(0.8, 0.8, 0.1); 
	glVertex2i(50, 130);
	glVertex2i(70, 150);
	glVertex2i(60, 120);
	glVertex2i(80, 130);
	glVertex2i(70, 120);
	glVertex2i(55, 100);
	glEnd();

	glBegin(GL_POLYGON);         // Grass 7 Big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(95, 110); 
	glVertex2i(80, 130);
	glVertex2i(70, 140);
	glVertex2i(90, 130);
	glVertex2i(30, 160);
	glVertex2i(100, 130);
	glColor3f(0.8, 0.7, 0.1);
	glVertex2i(105, 180);
	glVertex2i(110, 140);
	glVertex2i(130, 160);
	glVertex2i(120, 130);
	glVertex2i(140, 140);
	glVertex2i(130, 130);
	glVertex2i(115, 110);
	glEnd();

	glPopMatrix();
}

void drawSun()
{
	glPushMatrix();
	glColor3f(3, 1, 0.5);
	drawCircle(900, 700, 40, 1000);
	glPopMatrix();
}

void drawCloud()
{
	glPushMatrix();

	glColor3f(0.8, 0.8, 0.8);
	drawCircle(200, 690, 25, 1000);   //1st cloud
	drawCircle(230, 700, 25, 1000);
	drawCircle(180, 700, 25, 1000);
	drawCircle(210, 720, 25, 1000);


	drawCircle(600, 590, 25, 1000);   //2nd cloud
	drawCircle(630, 600, 25, 1000);
	drawCircle(580, 600, 25, 1000);
	drawCircle(610, 620, 25, 1000);

	glPopMatrix();
}

void drawBoat()
{
	glPushMatrix();

	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.8, 0.1);
	glVertex2i(270, 155); 
	glVertex2i(375, 165);
	glVertex2i(480, 155);
	glColor3f(1.9, 0.9, 0.1);
	glVertex2i(400, 20);
	glVertex2i(270, 20);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.1, 0.1);
	glVertex2i(250, 20);
	glVertex2i(180, 100);
	glVertex2i(380, 80);
	glColor3f(0.8, 0.3, 0.1);
	glVertex2i(600, 100);
	glVertex2i(500, 20);
	glEnd();

	glPopMatrix();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'b':
		{
			boatStatus = 1;
			break;
		}
		case 't':
		{
			boatStatus = 0;
			break;
		}
		case 'c':
		{
			cloudStatus = 1;
			break;
		}
		case 'd':
		{
			cloudStatus = 0;
			break;
		}
		default:break;
	}
}

void boat()
{
	if (boatStatus == 1)
	{
		boatX += 0.5;
	}
	if (boatX > 1000)
	{
		boatX = -600;
	}
	glPushMatrix();
	glTranslatef(boatX, boatY, 0);
	drawBoat();
	glPopMatrix();
}

void cloud()
{
	if (cloudStatus == 1)
	{
		cloud_X += 0.2;
	}
	if (cloud_X > 1100)
	{
		cloud_X = -650;
	}
	glPushMatrix();
	glTranslatef(cloud_X, cloud_Y, 0);
	drawCloud();
	glPopMatrix();
}

void cloud2()
{
	if (cloudStatus == 1)
	{
		cloud_X2 += 0.3;
	}
	if (cloud_X > 600)
	{
		cloud_X = -1150;
	}
	glPushMatrix();
	glTranslatef(cloud_X2 + 500, cloud_Y2 + 50, 0);
	drawCloud();
	glPopMatrix();
}

void display()
{
	scene();
	drawSun();
	boat();
	cloud();
	cloud2();
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}
/************************************/

//STRUCTURE DEFINING POINT
typedef struct Point {
	double x, y;
}point;

//ANGLES FOR EACH HAND
double secondAngle = 0, minuteAngle = 0, hourAngle = 0;

/************************************/

/************************************/

//FUNCTION TO DRAW A POINT
void drawPoint(point p) {
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();
}


/************************************/

//FUNCTION TO DRAW A LINE
void drawLine(double x, double y, double angle) {
	glVertex2f(x, x);
	glVertex2f(y * cos(angle), y * sin(angle));
}

/************************************/

void addDate() {
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char* s = asctime(timeinfo);
	char y[20];
	int count_space = 0, i;
	for (i = 0; i < strlen(s); ++i) {
		if (s[i] == ' ') {
			count_space++;
			y[i] = ',';
		}
		else {
			y[i] = s[i];
		}
		if (count_space == 3)
			break;
	}
	y[i] = '\0';
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(0, 90);
	for (i = 0; y[i] != '\0'; ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, y[i]);
	}

}

/************************************/

//FUNCTION TO DRAW THE BASIC CLOCK STRUCTURE
void drawMarks(void) {
	point sp, ep, p;
	int count = 0;
	double i = PI / 6.0;
	sp.x = 0, sp.y = 0;
	ep.x = 0, ep.y = CLOCK_RADIUS;
	glPointSize(10.0);
	drawPoint(sp);
	for (i = 0; i <= 2 * PI; i += PI / 30.0) {
		if (i == PI / 2.0) {
			p.x = CLOCK_RADIUS;
		}
		else if (i == 3 * PI / 2.0) {
			p.x = -CLOCK_RADIUS;
		}
		else {
			p.x = ep.y * sin(i);
		}
		p.y = ep.y * cos(i)
			;
		if (count % 5 == 0) {
			glPointSize(7.0);
			drawPoint(p);

		}
		else {
			glPointSize(3.0);
			drawPoint(p);
		}
		count++;
	}
}

/************************************/

//MAIN DRAW FUNCTION
void drawClock(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(1.0);
	drawMarks();
	addDate();
	glLineWidth(5.0);
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	drawLine(0.0, HOUR_HAND_LENGTH, -hourAngle + PI / 2);
	glEnd();

	glLineWidth(3.0);
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	drawLine(0.0, MINUTE_HAND_LENGTH, -minuteAngle + PI / 2);
	glEnd();

	glLineWidth(1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	drawLine(0.0, SECOND_HAND_LENGTH, -secondAngle + PI / 2);
	glEnd();
	glFlush();
	glutSwapBuffers();
}

/************************************/

//FUNCTION TO MAINTAIN ASPECT RATIO WHEN SCREEN IS RESIZED
void reshape(int w, int h) {
	double aspectRatio;
	//to avoid division by 0
	if (h == 0) {
		h = 1;
	}
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (double)w / (double)h;
	if (w <= h)
		glOrtho(-CLOCK_VOL, CLOCK_VOL, -CLOCK_VOL / aspectRatio, CLOCK_VOL / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-CLOCK_VOL * aspectRatio, CLOCK_VOL * aspectRatio, -CLOCK_VOL, CLOCK_VOL, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/************************************/

//TIMER FUNCTION
void redraw(int _) {
	struct timeb tb;
	time_t tim = time(0);
	struct tm* t;
	t = localtime(&tim);
	ftime(&tb);

	secondAngle = (double)(t->tm_sec + (double)tb.millitm / 1000.0) / 30.0 * PI;
	minuteAngle = (double)(t->tm_min) / 30.0 * PI + secondAngle / 60.0;
	hourAngle = (double)(t->tm_hour > 12 ? t->tm_hour - 12 : t->tm_hour) / 6.0 * PI + minuteAngle / 12.0;

	glutPostRedisplay();
	glutTimerFunc(15, redraw, 1);
}

/************************************/



//DRIVER FUNCTION
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(80, 80);
	glutCreateWindow("CG");

	init();
	createMenu();
	glutDisplayFunc(anyFunc);
	glutMainLoop();

    


	
	return 0;
}