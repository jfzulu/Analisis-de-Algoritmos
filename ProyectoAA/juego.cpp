#include "juego.h"
#include "library.h"

void Juego::cargarJuegos(vector<Juego> &juegos)
{
    string file = "mapas.txt";
    fstream archivo(file.c_str());
    string line;
    Juego add;
    while (getline(archivo, line))
    {
        add = leerLinea(line);
        juegos.push_back(add);
    }
}

Juego Juego::leerLinea(string line)
{
    Juego j1;
    j1.tam = line[0] - '0';
    // cout << "tam: " << j1.tam << endl;
    Color c;
    c.historial.clear();
    pair<int, int> p;
    p.first = -1;
    p.second = -1;
    int aux;
    int acum, tam;
    for (int i = 1; i < line.size(); i = i + 5)
    {
        if (line[i] >= 65 && line[i] <= 90)
        {
            c.color = line[i];
            // cout << line[i] << endl;
            acum = 0;
            for (int j = i + 1; j < i + 5; j = j + 2)
            {
                aux = line[j] - '0';
                acum = line[j + 1] - '0';
                p.first = aux;
                p.second = acum;
                c.puntos.push_back(p);

                // cout << p.first << " - " << p.second << endl;
            }
        }

        j1.colores.push_back(c);

        c.puntos.clear();
        // cout << endl;
    }
    return j1;
}

void Juego::imprimirJuegos(vector<Juego> juegos)
{
    int tam = juegos.size();
    int aux;
    cout << "Numero de juegos: " << tam << endl;

    for (int i = 0; i < juegos.size(); i++)
    {
        cout << "Juego " << i + 1 << endl;
        cout << "N Colores: " << juegos[i].colores.size() << endl;
        for (int j = 0; j < juegos[i].colores.size(); j++)
        {
            cout << juegos[i].colores[j].color << " : " << endl;
            // cout << "\t" << juegos[i].colores[j].puntos[0].first << " - " << juegos[i].colores[j].puntos[0].second << endl;
            // cout << "\t" << juegos[i].colores[j].puntos[1].first << " - " << juegos[i].colores[j].puntos[1].second << endl;
            for (int k = 0; k < juegos[i].colores[j].puntos.size(); k++)
            {
                cout << "\t" << juegos[i].colores[j].puntos[k].first << " - " << juegos[i].colores[j].puntos[k].second << endl;
            }
        }

        cout << endl;
    }
}

Juego Juego::configGame(vector<Juego> &juegos)
{
    Juego select;
    int opc, tam;
    cout << "Seleccione un tamanyo de tablero: " << endl;
    cout << "1. 6x6" << endl;
    cout << "2. 7x7" << endl;
    cout << "3. 8x8" << endl;
    cout << "4. 9x9" << endl;
    cout << "Ingrese opc: ";
    cin >> opc;
    switch (opc)
    {
    case 1:
        tam = 6;

        break;
    case 2:
        tam = 7;

        break;
    case 3:
        tam = 8;

        break;
    case 4:
        tam = 9;

        break;

    default:
        break;
    }

    vector<int> indices;
    
    for (int i = 0; i < juegos.size(); i++)
    {
        if (tam == juegos[i].tam)
        {
            // cout << "J: " << juegos[i].tam << " - " << i << endl;
            indices.push_back(i);
        }
    }

    int tamIndices = indices.size();
    srand(time(0));
    int choosen = rand() % tamIndices;
    int jPos = indices[choosen];

    select = juegos[jPos];

    // for (int i = 0; i < juegos[jPos].colores.size(); i++)
    // {
    //     cout << juegos[jPos].colores[i].color<<endl;
    //     cout << "\t"<<juegos[jPos].colores[i].puntos[0].first << " - " << juegos[jPos].colores[i].puntos[0].second << endl;
    //     cout << "\t"<<juegos[jPos].colores[i].puntos[1].first << " - " << juegos[jPos].colores[i].puntos[1].second << endl;
    // }

    return select;
}

void Juego::imprimirJuego(Juego juego)
{
    cout << "Tam: " << juego.tam << endl;
    for (int i = 0; i < juego.colores.size(); i++)
    {
        cout << juego.colores[i].color << endl;
        cout << "\t" << juego.colores[i].puntos[0].first << " - " << juego.colores[i].puntos[0].second << endl;
        cout << "\t" << juego.colores[i].puntos[1].first << " - " << juego.colores[i].puntos[1].second << endl;
        cout <<endl;
    }
}