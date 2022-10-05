#include <iostream>
#include <cstdlib>
#include "juego.h"
#include "interfaz.h"
using namespace std;
int main()
{
    vector<Juego> juegos;
    Juego select;
    Interfaz ui;
    Juego j1;
    j1.cargarJuegos(juegos);
    // j1.imprimirJuegos(juegos);
    select = j1.configGame(juegos);
    // select.imprimirJuego(select);
    ui.game = select;
    // ui.game.imprimirJuego(ui.game);
    ui.initialMatrix();
    int opc;
    bool ganador=false;
    do
    {
        system("clear");
        ui.printMatrix();
        opc = ui.move();
        ganador = ui.validarGanador();
        cout << "Presione una tecla para continuar"<<endl;
        cin.get();
    } while (opc != 4 || !ganador);
}