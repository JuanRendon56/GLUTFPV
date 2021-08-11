#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "RgbImage.h"
#include "Personaje.h"
#include "Operador.h"
#include "Objeto.h"

#define NTextures 4
GLuint	texture[NTextures];

Personaje miPersonaje;
Operador OPERA3D;
Objeto demon(&OPERA3D);
Objeto demonCaco(&OPERA3D);
Objeto armorpack(&OPERA3D);
Objeto medpack(&OPERA3D);


//Dimensiones
int WIDTH=800;
int HEIGTH=1300;

//Ejes
float X_MIN=-50;
float X_MAX=50;
float Y_MIN=-50;
float Y_MAX=50;
float Z_MIN=-50;
float Z_MAX=50;

//POV
float FOVY=60.0;
float ZNEAR=0.01;
float ZFAR=100.0;
float EYE_X=0.0;
float EYE_Y=0.0;
float EYE_Z=15.0;
float CENTER_X=0;
float CENTER_Y=0;
float CENTER_Z=0;
float UP_X=0;
float UP_Y=1;
float UP_Z=0;
float THETA=0;
float PI = 3.14159265359;
float Direction[3] = {0.0,0.0,-1.0};
float d, g;
int cambio;

char* armor = "doomArmor.bmp";
char* demon1 = "doomDemon1.bmp";
char* demon2 = "doomDemon2.bmp";
char* backfloor = "doomBack1.bmp";
char* background = "doomBack2.bmp";
char* cacodemon = "doomCacodemon.bmp";
char* backwalls = "doomWall.bmp";
char* health = "doomMed.bmp";

//Carga de imagen del escenario
void loadTextureFromFile(char *filename, int index)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	RgbImage theTexMap( filename );

    glGenTextures(1, &texture[index]);
    glBindTexture(GL_TEXTURE_2D, texture[index]);


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0,
                     GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
    theTexMap.Reset();
}

//Caras generales
void drawFace(float x1, float y1, float z1,
              float x2, float y2, float z2,
              float x3, float y3, float z3,
              float x4, float y4, float z4)
{
   glBegin(GL_QUADS);
       glTexCoord2f(0.0, 0.0);
       glVertex3f(x1, y1, z1);

       glTexCoord2f(0.0, 1.0);
       glVertex3f(x2, y2, z2);

       glTexCoord2f(1.0, 1.0);
       glVertex3f(x3, y3, z3);

       glTexCoord2f(1.0, 0.0);
       glVertex3f(x4, y4, z4);
   glEnd();
}
//Escenario con imagenes
void drawFiller()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glColor3f(1.0,1.0,1.0);

    //Floor
    drawFace(X_MIN,-2.0,Z_MIN,X_MAX,-2.0,Z_MIN,X_MAX,-2.0,Z_MAX,X_MIN,-2.0,Z_MAX);

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glColor3f(1.0,1.0,1.0);

    //Skybox
    drawFace(X_MIN,10,Z_MIN,X_MAX,10,Z_MIN,X_MAX,10,Z_MAX,X_MIN,10,Z_MAX);

    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glColor3f(1.0,1.0,1.0);

    //FrontWall
    drawFace(X_MIN,-2,Z_MIN,X_MAX,-2,Z_MIN,X_MAX,10,Z_MIN,X_MIN,10,Z_MIN);

    //LeftWall
    drawFace(X_MIN,-2,Z_MIN,X_MIN,-2,Z_MAX,X_MIN,10,Z_MAX,X_MIN,10,Z_MIN);

    //RightWall
    drawFace(X_MAX,-2,Z_MIN,X_MAX,-2,Z_MAX,X_MAX,10,Z_MAX,X_MAX,10,Z_MIN);

    //BackWall
    drawFace(X_MIN,-2,Z_MAX,X_MAX,-2,Z_MAX,X_MAX,10,Z_MAX,X_MIN,10,Z_MAX);


    glDisable(GL_TEXTURE_2D);
}

void init()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)WIDTH/HEIGTH, ZNEAR, ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z);
    glClearColor(0,0,0,0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    loadTextureFromFile(backfloor, 1);
    loadTextureFromFile(background, 2);
    loadTextureFromFile(backwalls, 3);
}


//Controlador de POV
void SpecialInput(int key, int x, int y)
{

    miPersonaje.Controlador(key);
    EYE_X = miPersonaje.GetEX();
    EYE_Y = miPersonaje.GetEY();
    EYE_Z = miPersonaje.GetEZ();
    CENTER_X = miPersonaje.GetCX();
    CENTER_Y = miPersonaje.GetCY();
    CENTER_Z = miPersonaje.GetCZ();
    THETA = miPersonaje.GetTheta();
    Direction[0] = miPersonaje.GetDir(0);
    Direction[1] = miPersonaje.GetDir(1);
    Direction[2] = miPersonaje.GetDir(2);

    glLoadIdentity();
    gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z);
    glutPostRedisplay();




}

//Escenario
void display()
{
    d += 0.5; //Velocidad de animacion
    g += 2.0;
    cambio = 0;
    Sleep(50);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawFiller();
    OPERA3D.identidad();
    OPERA3D.push();
    OPERA3D.push();
    OPERA3D.push();
    OPERA3D.push();
    OPERA3D.rotZ(180);
    demon.loadTextureFromFile(demon1, 1);
    if (d < 15)
        OPERA3D.trs(0,0,-d);
    else
        OPERA3D.trs(0,0,(-20+d));
    demon.drawImage(1);
    demon.update();
    OPERA3D.pop();
    OPERA3D.trs(2,0, -5);
    medpack.loadTextureFromFile(health, 3);
    OPERA3D.rotZ(180);
    OPERA3D.rotY(g);
    if (d < 15)
        OPERA3D.trs(0,-(d/40),0);
    else
        OPERA3D.trs(0,(d/40),0);
    medpack.drawImage(3);
    medpack.update();
    OPERA3D.pop();
    OPERA3D.trs(1,-1,7);
    armorpack.loadTextureFromFile(armor, 4);
    OPERA3D.rotZ(180);
    OPERA3D.esc(-1,-1,-1);
    armorpack.drawImage(4);
    OPERA3D.pop();
    OPERA3D.trs(0,5,-10);
    demonCaco.loadTextureFromFile(cacodemon,5);
    OPERA3D.rotZ(180);
    if (d < 15)
        OPERA3D.trs(-(d/4),(d/80),(d/10));
    else
        OPERA3D.trs(-4 + (d/4),0.35 - (d/80),(d/10));
    demonCaco.drawImage(5);
    OPERA3D.pop();
    glutSwapBuffers();

    if(d > 30)
        d = 0;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGTH);
    glutCreateWindow("Entrega Final");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    miPersonaje.SetVariables(EYE_X, EYE_Y, EYE_Z, CENTER_X, CENTER_Y, CENTER_Z, THETA, PI, Direction[0], Direction[1], Direction[2]);
    glutSpecialFunc(SpecialInput);
    glutMainLoop();
    return 0;
}

