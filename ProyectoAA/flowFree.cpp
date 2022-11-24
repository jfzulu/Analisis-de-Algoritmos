#include <iostream>
#include <cstdlib>
#include<ctime>
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
    ui.printMatrix();

    cout<<"\nSolucion\n";
    time_t t1,t2;
    time(&t1);
    vector<vector<bool> > visitado(ui.game.tam,vector<bool>(ui.game.tam,false));
    pair<int,int> p=ui.obtenerColor(visitado);
    char color=ui.matriz[p.first][p.second];
    ui.solucionar(p.first,p.second,visitado,color);
    time(&t2);
    ui.printMatrix();

    cout<<"\nTiempo en ejecución:   "<<setprecision(1000)<<difftime(t2,t1)<<" segundos."<<"\n";

    /*bool ganador=false;
    do
    {
        system("clear");
        ui.printMatrix();
        opc = ui.move();
        ganador = ui.validarGanador();

        cout << "Presione una tecla para continuar"<<endl;
        cin.get();
    } while (opc != 4 || !ganador);*/
}