#ifndef __INTERFAZ__H__
#define __INTERFAZ__H__
#include "library.h"
#include "juego.h"
#include "move.h"

class Interfaz
{
public:
    Juego game;
    char matriz[10][10];

    void initialMatrix();
    void printMatrix();
    int move();
    int validarCasilla(pair<int, int> target, Color &mov);

};

#include "interfaz.cpp"
#endif