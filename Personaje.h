#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <tuple>

class Personaje
{
    public:
        Personaje();
        ~Personaje();
        float RadToDeg(float, float);
        float DegToRad(float, float);
        void SetVariables(float, float, float, float, float, float, float, float, float, float, float);
        void LookAt_Left_Right();
        void Controlador(int);
        float GetEX();
        float GetEY();
        float GetEZ();
        float GetCX();
        float GetCY();
        float GetCZ();
        float GetTheta();
        float GetDir(int);

    private:
        float r, g, PI, EYE_X, EYE_Y, EYE_Z, CENTER_X, CENTER_Y, CENTER_Z, UP_X, UP_Y, UP_Z, THETA, Direction[3];
};



#endif // PERSONAJE_H
