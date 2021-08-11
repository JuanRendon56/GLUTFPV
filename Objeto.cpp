#include "Objeto.h"
#include "RgbImage.h"
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
GLuint images[10];

Objeto::Objeto(Operador *opera)
{
    for(int i = 0; i < 8; i++)
        misPuntos[i].setOperador(opera);

    misPuntos[0].setValues(0,0,0); //Origen
    misPuntos[1].setValues(1,0,0); //Origen derecha
    misPuntos[2].setValues(0,1,0); //Origen arriba
    misPuntos[3].setValues(1,1,0); //Origen esquina
    misPuntos[4].setValues(0,0,1); //Z origen
    misPuntos[5].setValues(1,0,1); //Z derecha
    misPuntos[6].setValues(0,1,1); //Z arriba
    misPuntos[7].setValues(1,1,1); //Z esquina

    for (int i = 0; i < 8; i++)
        misPuntosP[i] = misPuntos[i];

    for (int i = 0; i < 3; i++)
    {
        puntosOrigen[i] = 0;
        puntosPivote[i] = 0;
    }
    op = opera;
}

Objeto::~Objeto()
{
    //dtor
}

void Objeto::setOrigen(float x, float y, float z)
{
    puntosOrigen[0] = x;
    puntosOrigen[1] = y;
    puntosOrigen[2] = z;

    for (int i = 0; i < 3; i++)
        puntosPivote[i] = puntosOrigen[i];
}


void Objeto::update(){
        for(int i=0; i<3; i++)
            puntosPivote[i] = puntosOrigen[i];
}

void Objeto::loadTextureFromFile(char *filename, int index)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	RgbImage theTexMap( filename );

    glGenTextures(1, &images[index]);
    glBindTexture(GL_TEXTURE_2D, images[index]);


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0,
                     GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
    theTexMap.Reset();
}

void Objeto::drawFace(float x1, float y1, float z1,
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

void Objeto::drawImage(int i)
{
    op->push();

    op->trsPuntos(puntosPivote[0], puntosPivote[1], puntosPivote[2]);
    for(int i=0; i<8; i++)
    {
        op->multPuntos(misPuntos[i].p, misPuntosP[i].p);
    }
   //Activate textures
   glEnable(GL_TEXTURE_2D);

   //front face
   glBindTexture(GL_TEXTURE_2D, images[i]);
   drawFace(misPuntosP[6].p[0], misPuntosP[6].p[1], misPuntosP[6].p[2],
            misPuntosP[4].p[0], misPuntosP[4].p[1], misPuntosP[4].p[2],
            misPuntosP[5].p[0], misPuntosP[5].p[1], misPuntosP[5].p[2],
            misPuntosP[7].p[0], misPuntosP[7].p[1], misPuntosP[7].p[2]);
   //right face
   drawFace(misPuntosP[7].p[0], misPuntosP[7].p[1], misPuntosP[7].p[2],
            misPuntosP[5].p[0], misPuntosP[5].p[1], misPuntosP[5].p[2],
            misPuntosP[1].p[0], misPuntosP[1].p[1], misPuntosP[1].p[2],
            misPuntosP[3].p[0], misPuntosP[3].p[1], misPuntosP[3].p[2]);
   //back face
   drawFace(misPuntosP[3].p[0], misPuntosP[3].p[1], misPuntosP[3].p[2],
            misPuntosP[2].p[0], misPuntosP[2].p[1], misPuntosP[2].p[2],
            misPuntosP[0].p[0], misPuntosP[0].p[1], misPuntosP[0].p[2],
            misPuntosP[1].p[0], misPuntosP[1].p[1], misPuntosP[1].p[2]);
   //left face 2, 0, 4, 6
   drawFace(misPuntosP[2].p[0], misPuntosP[2].p[1], misPuntosP[2].p[2],
            misPuntosP[0].p[0], misPuntosP[0].p[1], misPuntosP[0].p[2],
            misPuntosP[4].p[0], misPuntosP[4].p[1], misPuntosP[4].p[2],
            misPuntosP[6].p[0], misPuntosP[6].p[1], misPuntosP[6].p[2]);
   glDisable(GL_TEXTURE_2D);

   op->pop();
}
