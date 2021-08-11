#include "Personaje.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <tuple>


Personaje::Personaje()
{
    //Inicializacion

}

Personaje::~Personaje(){
}

float Personaje::RadToDeg(float r, float PI)
{
      return ((180.0*r)/PI);
}

float Personaje::DegToRad(float g, float PI)
{
      return ((g*PI)/180.0);
}

void Personaje::LookAt_Left_Right()
{
    Direction[0] = Direction[0]*cos(DegToRad(THETA, PI)) + Direction[2]*sin(DegToRad(THETA, PI));
    Direction[2] = -Direction[0]*sin(DegToRad(THETA, PI)) + Direction[2]*cos(DegToRad(THETA, PI));
    CENTER_X += Direction[0];
    CENTER_Z += Direction[2];
}

void Personaje::Controlador(int key)
{
    switch(key){
                case GLUT_KEY_UP:
                     EYE_X += Direction[0];
                     EYE_Y += Direction[1];
                     EYE_Z += Direction[2];
                     CENTER_X = EYE_X + Direction[0];
                     CENTER_Y = EYE_Y + Direction[1];
                     CENTER_Z = EYE_Z + Direction[2];
                     break;
                case GLUT_KEY_DOWN:
                     EYE_X -= Direction[0];
                     EYE_Y -= Direction[1];
                     EYE_Z -= Direction[2];
                     CENTER_X = EYE_X + Direction[0];
                     CENTER_Y = EYE_Y + Direction[1];
                     CENTER_Z = EYE_Z + Direction[2];
                     break;
                case GLUT_KEY_LEFT:
                     THETA = 1.0;
                     THETA = (THETA < 0.0) ? 359.0 : THETA;
                     LookAt_Left_Right();
                      break;
                case GLUT_KEY_RIGHT:
                     THETA = -1.0;
                     THETA = (THETA > 359.0) ? 0.0 : THETA;
                     LookAt_Left_Right();
                     break;
    }
}

void Personaje::SetVariables(float ex, float ey, float ez, float cx, float cy, float cz, float o, float pi, float dir1, float dir2, float dir3)
{
    EYE_X = ex;
    EYE_Y = ey;
    EYE_Z = ez;
    CENTER_X = cx;
    CENTER_Y = cy;
    CENTER_Z = cz;
    THETA = o;
    PI = pi;
    UP_X = 0;
    UP_Y = 1;
    UP_Z = 0;
    Direction[0] = dir1;
    Direction[1] = dir2;
    Direction[2] = dir3;
}

float Personaje::GetEX()
{
    return EYE_X;
}

float Personaje::GetEY()
{
    return EYE_Y;
}

float Personaje::GetEZ()
{
    return EYE_Z;
}

float Personaje::GetCX()
{
    return CENTER_X;
}

float Personaje::GetCY()
{
    return CENTER_Y;
}

float Personaje::GetCZ()
{
    return CENTER_Z;
}

float Personaje::GetTheta()
{
    return THETA;
}

float Personaje::GetDir(int i)
{
    return Direction[i];
}
