#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include "Operador.h"
#include "math.h"

#define PI 3.14159265359

Operador::Operador()
{
    identidad(A);
    identidad(R);
    identidad(T);
    identidad(E);
}

Operador::~Operador()
{
}
void Operador::identidad(){
    identidad(A);
}

void Operador::identidad(float M[][4]){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(i==j){
                M[i][j] = 1;
            } else {
                M[i][j] = 0;
            }
        }
    }
}

void Operador::multM(float M1[][4], float M2[][4], float Res[][4]){
    float tmp[4][4];

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            tmp[i][j] = 0;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
                for(int k=0;k<4;k++){
                    tmp[i][j] += M2[i][k]*M1[k][j];
                }
        }
    }

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            Res[i][j] = tmp[i][j];
        }
    }
}

void Operador::multPuntos(float P[3], float Res[3]){
    float tmp[3];

    for(int i=0; i<3; i++)
        tmp[i] = 0;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
                    tmp[i] += P[j]*A[j][i];
        }
        tmp[i] += A[i][3];
    }

    for(int i=0; i<3; i++){
        Res[i] = tmp[i];
    }
}

void Operador::trsPuntos(float x, float y, float z){
    identidad(T);
    T[0][3] = x;
    T[1][3] = y;
    T[2][3] = z;
}

void Operador::escPuntos(float x, float y, float z){
    identidad(E);
    E[0][3] = x;
    E[1][3] = y;
    E[2][3] = z;
}

void Operador::trs(float x, float y, float z){
    trsPuntos(x,y,z);
    multM(T,A,A);
}

void Operador::esc(float x, float y, float z){
    escPuntos(x,y,z);
    multM(E,A,A);
}

void Operador::trsX(float b, float c, float d){
    identidad(R);
    R[1][1] = c/d;
    R[1][2] = -b/d;
    R[2][1] = b/d;
    R[2][2] = c/d;
}

void Operador::trsX(float deg){
    identidad(R);
    R[1][1] = cos(deg);
    R[1][2] = -sin(deg);
    R[2][1] = sin(deg);
    R[2][2] = cos(deg);
}

void Operador::trsY(float a, float d){
    identidad(R);
    R[0][0] = d;
    R[0][2] = a;
    R[2][0] = -a;
    R[2][2] = d;
}

void Operador::trsY(float deg){
    identidad(R);
    R[0][0] = cos(deg);
    R[0][2] = sin(deg);
    R[2][0] = -sin(deg);
    R[2][2] = cos(deg);
}

void Operador::trsZ(float deg){
    identidad(R);
    R[0][0] = cos(deg);
    R[0][1] = -sin(deg);
    R[1][0] = sin(deg);
    R[1][1] = cos(deg);
}

void Operador::rotar(float deg, float p1[3], float p2[3]){
    float a = p2[0]-p1[0];
    float b = p2[1]-p1[1];
    float c = p2[2]-p1[2];
    float v = sqrt(pow(a,2)+pow(b,2)+pow(c,2));
    a = a/v;
    b = b/v;
    c = c/v;
    float d = sqrt(pow(b,2)+pow(c,2));
    deg = deg*PI/180;

    trs(-p1[0],-p1[1],-p1[2]);
    identidad(R);
    if(d != 0.0)
        trsX(b,c,d);
    multM(R,T,A);
    trsY(a,d);
    multM(R,A,A);

    trsZ(deg);
    multM(R,A,A);

    trsY(-a,d);
    multM(R,A,A);

    if(d != 0){
        trsX(-b,c,d);
        multM(R,A,A);
    }

    trs(p1[0],p1[1],p1[2]);
    multM(T,A,A);
}

void Operador::rotX(float deg){
    deg *= PI/180;
    trsX(deg);
    multM(R,A,A);
}

void Operador::rotY(float deg){
    deg *= PI/180;
    trsY(deg);
    multM(R,A,A);
}

void Operador::rotZ(float deg){
    deg *= PI/180;
    trsZ(deg);
    multM(R,A,A);
}

void Operador::push(){
    Matriz tmp;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            tmp.M[i][j] = A[i][j];
        }
    }
    pila.push(tmp);
}

void Operador::pop(){
    Matriz tmp = pila.top();
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            A[i][j] = tmp.M[i][j];
        }
    }
    pila.pop();
}
