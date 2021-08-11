#ifndef OPERADOR_H
#define OPERADOR_H
#include <stack>

using namespace std;

class Matriz{
public:
    float M[4][4];
};

class Operador{
    private:

	    stack <Matriz> pila;
		void identidad(float M[][4]);
		void multM(float M1[][4], float M2[][4], float Res[][4]);

	public:
	    float T[4][4], R[4][4], E[4][4], A[4][4];
		Operador();
		~Operador();
		void identidad();
        void trs(float x, float y, float z);
        void esc(float x, float y, float z);
        void trsPuntos(float x, float y, float z);
		void escPuntos(float x, float y, float z);
        void trsX(float b, float c, float d);
        void trsX(float deg);
        void trsY(float a, float d);
        void trsY(float deg);
        void trsZ(float deg);
		void multPuntos(float Puntos[3], float M[3]);
		void rotar(float deg, float p1[3], float p2[3]);
		void rotX(float deg);
		void rotY(float deg);
		void rotZ(float deg);

		void push();
		void pop();
};

#endif // OPERADOR_H
