#ifndef PUNTO_H
#define PUNTO_H
#include "Operador.h"

class Punto
{
    private:
		Operador *op;
	public:
		Punto();
		~Punto();
		float p[3], pp[3];
		void setOperador(Operador*);
		void setValues(float x,float y,float z);
		float * getValues();
		void draw();
		void update();
};

#endif // PUNTO_H
