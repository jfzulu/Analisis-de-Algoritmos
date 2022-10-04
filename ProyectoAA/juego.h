#ifndef __JUEGO__H__
#define __JUEGO__H__
#include "library.h"
#include "Color.h"
using namespace std;

class Juego{
    public:
        int tam;
        vector< Color > colores;

        void cargarJuegos(vector <Juego> &juegos);
        Juego leerLinea(string line);
        void imprimirJuegos(vector <Juego> juegos);
        Juego configGame(vector <Juego> &juegos);
        void imprimirJuego( Juego juego);

};

#include "juego.cpp"
#endif