#include "Punto.h"
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>

Punto::Punto()
{
	p[0] = 0.0;
	p[1] = 0.0;
	p[2] = 0.0;
}

Punto::~Punto()
{

}

void Punto::setOperador(Operador* opera)
{
    op = opera;
}

void Punto::setValues(float x, float y, float z)
{
    p[0] = x;
    p[1] = y;
    p[2] = z;
}

float* Punto::getValues()
{
    return p;
}

void Punto::draw()
{
    op->push();
    op->trsPuntos(p[0],p[1],p[2]);
    op->multPuntos(p,p);

    glBegin(GL_POINTS);
        glColor3f(1.0,1.0,1.0);
        glVertex3f(p[0],p[1],p[2]);
    glEnd();

    op->pop();
}

void Punto::update(){
    p[0] += pp[0];

    if(p[0]>600)
    {
        p[0] = 0;
    }
}
