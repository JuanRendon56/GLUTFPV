#ifndef OBJETO_H
#define OBJETO_H
#include "Punto.h"
#include "Operador.h"


class Objeto
{
	private:
		Punto misPuntos[8], misPuntosP[8];
		Operador *op;
		float puntosPivote[3], puntosOrigen[3];
    public:
        Objeto(Operador*);
		~Objeto();
		void setOrigen(float x, float y, float z);
		void loadTextureFromFile(char* , int);
		void drawFace(float,float, float, float, float, float, float, float, float, float, float, float);
		void drawImage(int);
        void draw();
        void update();
};

#endif // OBJETO_H
