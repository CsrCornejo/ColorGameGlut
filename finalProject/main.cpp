// transf_instance_main.cpp
// Transformación de Instancias

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <time.h>

#include "quad_gl.h"
#include "cube_gl.h"
#include "pyramid_gl.h"
#include "sphere_gl.h"
#include "image_loader.h"


using namespace std;

// Geometries

std::vector<ObjectGL *> scene;

PolygonGL *p1, *p2, *q1, *l1, *po1, *box;

// Tamaño de la ventana
GLint width = 800;
GLint height = 600;

// Parámetros de la cámara virtual
GLint mouseButton = 0;
GLboolean mouseRotate = false;
GLboolean mouseZoom = false;
GLboolean mousePan = false;
GLint xClick = 0;
GLint yClick = 0;
GLint xAux = 0;
GLint yAux = 0;
GLfloat rotX = 0.f;
GLfloat rotY = 0.f;
GLfloat panX = 0.f;
GLfloat panY = 0.f;
GLfloat zoomZ = -10.f;

//GLfloat rot = 0.f;
GLfloat deltaRot = 0.025f;

GLint indexFigure = 0;
GLint obFigure = 0;

GLfloat rF = 0.0f;
GLfloat gF = 0.0f;
GLfloat bF = 0.0f;

GLfloat colorRatio = 1.f;

string Colors[2][2][2];
string Colors2[2][2][2];

string cObject;

int irColorT;
int igColorT;
int ibColorT;

unsigned char cText[100];
unsigned char obText[100];

GLint Score = 0;
GLint lvl = 1;

string descs[5] = { "\nLevel with just Basic colors.", "\nFast Think! \nGet your score lowered each time you fail.", "\nNew Set of Colors! \nFrom Black to Gray.", "\nGet also the correct shape!", "\n All Possibilities!" };
string figs[3] = { "Cube", "Triangle", "Sphere" };

time_t initSeconds;
time_t clockG;

int tempScore;

GLUquadric *quad;

GLuint textureId;

// Propiedades de la fuente de luz:
GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 0.0, 0.0, 100.0, 1.0 };

// Propiedades del material:
GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };	// material emisor

// Modelo de iluminación
GLfloat scene_light_ambient[] = { .2, .2, .2, 1.0 }; // luz ambiental
GLfloat local_viewer[] = { 1.0 };   // observador local
GLfloat two_side[] = { 1.0 };       // modelo de iluminación de doble lado = true

void generateColorTable(){
	Colors[0][0][0] = "Black";

	Colors[1][0][0] = "Red";
	Colors[0][1][0] = "Lime";
	Colors[0][0][1] = "Blue";

	Colors[1][1][0] = "Yellow";
	Colors[0][1][1] = "Cyan";
	Colors[1][0][1] = "Magenta";

	Colors[1][1][1] = "White";

	Colors2[0][0][0] = "Black";

	Colors2[1][0][0] = "Maroon";
	Colors2[0][1][0] = "Green";
	Colors2[0][0][1] = "Navy";

	Colors2[1][1][0] = "Olive";
	Colors2[0][1][1] = "Teal";
	Colors2[1][0][1] = "Purple";

	Colors2[1][1][1] = "Gray";


}

void getRandomRatio(){
	int rrBit = rand() % 2;

	colorRatio = (rrBit == 0) ? 0.5f : 1.0f;
}

void generateColorGoal(){
	int rBit = rand() % 2;
	int gBit = rand() % 2;
	int bBit = rand() % 2;

	//cout << "Your code objective " << rBit << " " << gBit << " " << bBit << endl;

	string temp = (colorRatio == 1.0f) ? Colors[rBit][gBit][bBit] : Colors2[rBit][gBit][bBit];
	//cout << "Your code objective " << temp << endl;

	if (temp != cObject){
		cObject = temp;
		
	}
	else{
		generateColorGoal();
	}
}

void generateShapeGoal(){
	int sBit = rand() % 3;

	//cout << "Your code objective " << rBit << " " << gBit << " " << bBit << endl;

	//cout << "Your shape objective " << sBit << endl;

	if (sBit != obFigure){
		obFigure = sBit;

	}
	else{
		generateShapeGoal();
	}
}

string getActualColor(float r, float g, float b){
	if (r == 0.5){
		irColorT = 1;
	}
	else{
		irColorT = (int)r;
	}

	if (g == 0.5){
		igColorT = 1;
	}
	else{
		igColorT = (int)g;
	}

	if (b == 0.5){
		ibColorT = 1;
	}
	else{
		ibColorT = (int)b;
	}
	
	//cout << "Tu color code es: " << irColorT << " " << igColorT << " " << ibColorT << " " << endl;


	return colorRatio == 1.f ? Colors[irColorT][igColorT][ibColorT] : Colors2[irColorT][igColorT][ibColorT];
	
}


void lighting(){
	// Fuentes de luz
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// materiales
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	// Modelo de iluminación
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, scene_light_ambient); // luz ambiental  
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_viewer); // tipo de observador 
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, two_side); // tipo de modelo de iluminación

	// Modelo de sombreado
	glShadeModel(GL_FLAT);    // interpolado plano

	// prueba de profundidad
	glEnable(GL_DEPTH_TEST);
}

// Función que inicializa el Contexto OpenGL y la geometría de la escena
void init()
{
	glClearColor(0.25f, 0.15f, 0.25f, 0.f);
	glColor3f(1.f, 1.f, 1.f);
	generateColorTable();
	generateColorGoal();

	Score = 0;
	lvl = 1;
	
	

	initSeconds = time(NULL);
	//cout << "Initial Second " << initSeconds << endl;

	CubeGL *c1 = new CubeGL();
	c1->FaceMode = GL_FILL;
	//c1->setColor(0.0f, 0.0f, 0.f);
	//c1->translate(0.0f, -2.0f, 0.f);
	//c1->scale(2.0f, 2.f, 1.f);

	PyramidGL *py1 = new PyramidGL();
	py1->FaceMode = GL_FILL;
	//py1->setColor(0.0f, 0.f, 0.f);
	//py1->translate(2.0f, -1.0f, 0.f);
	//py1->rotate(rot, 1.f, 0.f, 0.f);
	//py1->scale(2.f, 1.f, 1.f);


	SphereGL *s1 = new SphereGL();
	s1->FaceMode = GL_FILL;
	//s1->setColor(0.0f, 0.f, 0.f);
	//s1->translate(0.0f, -1.0f, 0.f);
	s1->rotate(90.f, 0.f, 1.f, 0.f);
	//s1->scale(1.5f, 1.f, 1.f);

	scene.push_back(c1);
	scene.push_back(py1);
	scene.push_back(s1);

	lighting();

}

// Función que se invoca cada vez que se redimensiona la ventana
void resize(GLint w, GLint h)
{
	if (h == 0)
	{
		h = 1;
	}
	width = w;
	height = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.f, (float)width / height, 0.1f, 1000.f);		// Transf. de Proyección en Perspectiva
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, width, height);								// Transf. de Viewport (mapeo al área de dibujo)
}

// Geometría sistema coordenado
void geomCoordSys(GLfloat size)
{
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);

	// Eje X (Rojo)
	glColor3f(1., 0., 0.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(size, 0., 0.);
	glEnd();

	// Eje Y (Verde))
	glColor3f(0., 1., 0.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., size, 0.);
	glEnd();

	// Eje Z (Azul)
	glColor3f(0., 0., 1.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., 0., size);
	glEnd();

	glColor3f(currentColor[0], currentColor[1], currentColor[2]);
}

void generateColorText(){
	
	glRasterPos2i(0, -1);
	strcpy((char*)cText, getActualColor(rF, gF, bF).c_str());
	//strcpy((char*)cText, "Texto");
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, cText);
	
	
}

void generateGoalText(){
	
	glRasterPos2i(-1, 1);
	string text = "The next goal is: " + cObject + " !!!";
	if (lvl > 3){
		text = "The next goal is: " + cObject + " " + figs[obFigure] + " !!!";
	}
	strcpy((char*)cText, text.c_str());
	//strcpy((char*)cText, "Texto");
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, cText);
	

}

void generateScoreText(){

	glRasterPos2i(-1, 2);
	string text = "Current Score is: " + to_string(Score);
	strcpy((char*)cText, text.c_str());
	//strcpy((char*)cText, "Texto");
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, cText);


}

void generateLvlText(){

	glRasterPos2i(-1, -1);
	string text = "\n\nLvl " + to_string(lvl);
	strcpy((char*)cText, text.c_str());
	//strcpy((char*)cText, "Texto");
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, cText);

	glRasterPos2i(-1, -1);
	text = "\n\n\n Description: " + descs[lvl-1];
	strcpy((char*)cText, text.c_str());
	//strcpy((char*)cText, "Texto");
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, cText);


}

void verifyLvl(){
	if (Score < 4){
		lvl = 1;
		colorRatio = 1.0f;
	}
	else if (Score < 8){
		lvl = 2;
		colorRatio = 1.0f;
	}
	else if (Score < 12){
		lvl = 3;
		colorRatio = 0.5f;
	}
	else if (Score < 16){
		lvl = 4;
		colorRatio = 0.5f;
	}
	else if (Score < 19){
		lvl = 5;
		//colorRatio = 0.5f;
	}

	initSeconds = time(NULL);
	if (lvl > 3){
		generateShapeGoal();
	}

	if (lvl > 4){
		getRandomRatio();
	}
	generateColorGoal();
}

void generateClock(){

	clockG = time(NULL) - initSeconds;
	if (lvl > 1){
		if ((clockG % 6) == 4){
			tempScore = Score - 1;
		}
		else if ((clockG % 6) == 5){
			Score = tempScore;
			verifyLvl();
		}
	}

}

void generateInstrucText(){

	glRasterPos2i(1.5, 0.5);
	string text = "Cambiar Forma: \n       <- y -> \nCambiar Colores: \n   Rojo (D y C)\n  Verde (F y V)\n   Azul (G y B)";
	strcpy((char*)cText, text.c_str());
	//strcpy((char*)cText, "Texto");
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, cText);

}

void generateClockText(){

	glRasterPos2i(-2, 2);
	string text = "Clock: " + to_string(clockG);
	strcpy((char*)cText, text.c_str());
	//strcpy((char*)cText, "Texto");
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, cText);


}


void generateObjective(){
	
	mat_diffuse[0] = rF;
	mat_diffuse[1] = gF;
	mat_diffuse[2] = bF;
	mat_diffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	for (int i = 0; i < scene.size(); i++){
		if (i == indexFigure){
			//scene.at(i)->setColor(rF,gF,bF);
			scene.at(i)->render();
		}
	}
	
	glDisable(GL_LIGHTING);
	generateColorText();
	generateGoalText();
	generateScoreText();
	generateLvlText();
	generateClock();
	generateClockText();
	generateInstrucText();
}


// Función que se invoca cada vez que se dibuja
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Se limpian los buffers con el color activo definido por glClearColor

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Transformación de vista
	glTranslatef(panX, panY, zoomZ);
	glRotatef(rotY, 1.0, 0.0, 0.0);
	glRotatef(rotX, 0.0, 1.0, 0.0);

	// Escena
	//geomCoordSys(2.f);
	

	glPushMatrix();
	glEnable(GL_LIGHTING);
	generateObjective();
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glutSwapBuffers();			// Se intercambian buffers
}

void mouse(int button, int state, int x, int y)
{
	mouseButton = button;
	mouseRotate = false;
	mouseZoom = false;
	mousePan = false;
	xClick = x;
	yClick = y;
	if (button == GLUT_LEFT_BUTTON)
	{
		mouseRotate = true;
		xAux = rotX;
		yAux = rotY;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		mouseZoom = true;
		xAux = zoomZ;
	}
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		mousePan = true;
		xAux = panX;
		yAux = panY;
	}
}

void mouseMotion(int x, int y)
{
	if (mouseRotate == true)
	{
		if (mouseButton == GLUT_LEFT_BUTTON)
		{
			if ((x - xClick + xAux) > 360.0)
			{
				xAux = xAux - 360.0;
			}
			if ((x - xClick + xAux) < 0.0)
			{
				xAux = xAux + 360.0;
			}
			if ((y - yClick + yAux) > 360.0)
			{
				yAux = yAux - 360.0;
			}
			if ((y - yClick + yAux) < 0.0)
			{
				yAux = yAux + 360.0;
			}
			rotX = x - xClick + xAux;
			rotY = y - yClick + yAux;
		}
	}
	else if (mouseZoom == true)
	{
		if (mouseButton == GLUT_RIGHT_BUTTON)
		{
			zoomZ = ((x - xClick) / 10.0) + xAux;
		}
	}
	else if (mousePan == true)
	{
		if (mouseButton == GLUT_MIDDLE_BUTTON)
		{
			panX = ((x - xClick) / 63.0) + xAux;
			panY = ((y - yClick) / (-63.0)) + yAux;
		}
	}
	glutPostRedisplay();
}

void idle(){
	//rot = deltaRot;
	scene.at(indexFigure)->rotate(deltaRot, 0.f, 1.f, 0.f);
	glutPostRedisplay();
}

void verifyGoals(){
	if (getActualColor(rF, gF, bF) == cObject){
		if (obFigure == indexFigure){
			Score++;
			verifyLvl();
		}
	}
}

void changeFigure(int key, int x, int y){

	//cout << key << endl;
	if (key == GLUT_KEY_LEFT){
		if (indexFigure == 0){
			indexFigure = scene.size() - 1;
		}
		else{
			indexFigure = (indexFigure - 1) % scene.size();
		}
	}

	if (key == GLUT_KEY_RIGHT){
		indexFigure = (indexFigure + 1 ) % scene.size();
	}

	if (lvl > 3){
		verifyGoals();
	}

}

float changing(float value, float additive){
	value = value + additive;

	if (value > colorRatio){
		return colorRatio;
	}
	else if (value < 0.0f){
		return 0.0f;
	}

	return value;
}

void colorManager(float r, float g, float b){
	rF = changing(rF, r);
	gF = changing(gF, g);
	bF = changing(bF, b);

	//cout << "Values are: " << rF << " " << gF << " " << bF << endl;

	//cout << getActualColor(rF, gF, bF) << endl;

	if (lvl > 3){
		verifyGoals();
	}else if (getActualColor(rF, gF, bF) == cObject){
		//cout << "Found the objective :D, Generating new obj" << endl;
		Score++;
		verifyLvl();

	}
	
}



void changeColor(unsigned char key, int x, int y){
	//cout << "X: " << x << " Y: " << y << endl;

	switch (key){
	case 'd':{
				 cout << "Add R" << endl;
				 colorManager(colorRatio,0.0f,0.0f);
				 break;
	}
	case 'c':{
				 cout << "Subs R" << endl;
				 colorManager(-colorRatio, 0.0f, 0.0f);
				 break;
	}
	case 'f':{
				 cout << "Add G" << endl;
				 colorManager(0.0f, colorRatio, 0.0f);
				 break;
	}
	case 'v':{
				 cout << "Subs G" << endl;
				 colorManager(0.0f, -colorRatio, 0.0f);
				 break;
	}
	case 'g':{
				 cout << "Add B" << endl;
				 colorManager(0.0f, 0.0f, colorRatio);
				 break;
	}
	case 'b':{
				 cout << "Subs B" << endl;
				 colorManager(0.0f, 0.0f, -colorRatio);
				 break;
	}



	/*case 'a':{
				 cout << "Change ratio to 1" << endl;
				 colorRatio = 1.0f;
				 break;
	}
	case 'z':{
				 cout << "Change ratio to 0.5" << endl;
				 colorRatio = 0.5f;
				 break;
	}*/
	}
}

int main(GLint argc, GLchar **argv)
{
// 1. Se crea una ventana y un contexto OpenGL usando GLUT
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
glutInitWindowSize(width, height);
glutCreateWindow("Coloring Shapes Game");

// 1.2 Se definen las funciones callback para el manejo de eventos
glutReshapeFunc(resize);
glutDisplayFunc(render);
glutMouseFunc(mouse);
glutMotionFunc(mouseMotion);
glutIdleFunc(idle);
glutSpecialFunc(changeFigure);
glutKeyboardFunc(changeColor);

// 2. Se direcciona a las funciones correctas del API de OpenGL
GLenum err = glewInit();
if (GLEW_OK != err)
{
fprintf(stderr, "GLEW Error");
return false;
}

// 3. Se inicializa el contexto de OpenGL y la geometría de la escena
init();

// 4. Se inicia el ciclo de escucha de eventos
glutMainLoop();
return 0;
}