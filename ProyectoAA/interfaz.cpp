#include "library.h"
#include "interfaz.h"

void Interfaz::initialMatrix()
{
    int tam = this->game.tam;
    this->game.contador = tam;
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            this->matriz[i][j] = ' ';
        }
    }

    for (int k = 0; k < game.colores.size(); k++)
    {
        for (int j = 0; j <= 1; j++)
        {
            matriz[game.colores[k].puntos[j].first][game.colores[k].puntos[j].second] = game.colores[k].color;
        }
    }
}

void Interfaz::printMatrix()
{
    int tam = game.tam;

    cout << " ";
    for (int i = 0; i < tam; i++)
    {
        cout << "| " << i << " |";
    }
    cout << endl;

    for (int i = 0; i < tam; i++)
    {
        cout << i;
        for (int j = 0; j < tam; j++)
        {
            cout << "| " << matriz[i][j] << " |";
        }
        cout << endl;
    }
}

int Interfaz::validarCasilla(pair<int, int> target, Color &mov)
{
    cout << "Validando con " << mov.historial.size() << endl;
    int estado = 0;
    // cout << target.first<<" - "<<target.second<<endl;
    // cout << game.tam<<endl;

    // Si es mayor del tamaño del tablero
    if (target.first > game.tam - 1 || target.second > game.tam - 1)
    {
        return -1;
    }
    if (target.first < 0 || target.second < 0)
    {
        if (target.first == -1 || target.second == -1)
        {
            return 3;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        if (mov.historial.empty()) // El primer movimiento debe ser la casilla de un color
        {
            bool primer = false;
            for (int i = 0; i <= 1; i++)
            {
                if (mov.puntos[i].first == target.first &&
                    mov.puntos[i].second == target.second)
                {
                    primer = true;
                }
            }

            if (primer == false)
            {
                cout << "Primera seleccion: Seleccione casilla inicial del color " << endl;
                return -1;
            }
            else
            {
                cout << "Casilla inicial valida" << endl;
                return 1;
            }
        }

        else // En caso de que no sea la primera seleccion
        {
            if (matriz[target.first][target.second] != ' ' && matriz[target.first][target.second] != mov.color)
            {
                return -1;
            }
            int tam = mov.historial.size();
            cout << "Historial de jugadas: " << endl;
            for (int i = 0; i < tam; i++)
            {
                cout << "\t" << mov.historial[i].first << " - " << mov.historial[i].second << endl;
            }

            pair<int, int> previo = mov.historial[mov.historial.size() - 1];
            bool valido = false;
            bool existente = false;
            existente = validarExistente(mov, target);

            if (previo == target) // Es la misma casilla ya marcada
            {
                cout << "Casilla ya marcada" << endl;
                cin.get();
                return -1;
            }
            // Si no es igual a la casilla ya marcada
            // Valide si es una casilla continua
            if (previo != target)
            {
                if (previo.first + 1 == target.first && previo.second + 0 == target.second) // Abajo
                {
                    valido = true;
                }
                if (previo.first + 0 == target.first && previo.second + 1 == target.second) // Derecha
                {
                    valido = true;
                }
                if (previo.first - 1 == target.first && previo.second + 0 == target.second) // Arriba
                {
                    valido = true;
                }
                if (previo.first + 0 == target.first && previo.second - 1 == target.second) // Izquierda
                {
                    valido = true;
                }
            }

            if (valido)
            {
                bool end = validarFinalMov(mov, target);
                if (end)
                    return 2;

                cout << "Movimiento valido: Casilla continua correcta" << endl;
                cin.get();
                return 1;
            }
            else
            {
                cout << "Movimiento invalido: Casilla no continua" << endl;
                cin.get();
                return -1;
            }
        }
    }

    return estado;
}

bool Interfaz::validarExistente(Color mov, pair<int, int> target)
{
    bool valido = false;
    for (int i = 0; i < mov.historial.size(); i++)
    {
        if (target == mov.historial[i])
            valido = true;
    }

    return valido;
}

bool Interfaz::validarFinalMov(Color mov, pair<int, int> target)
{
    bool valido = false;

    if ((target == mov.puntos[0] && mov.historial[0] == mov.puntos[1]) ||
        (target == mov.puntos[1] && mov.historial[0] == mov.puntos[0]))
    {
        valido = true;
        return true;
    }

    return valido;
}

int Interfaz::move()
{
    int retorno = 0;
    int posColor = -1;
    Color mov;
    char c;
    bool flag_color = false;
    pair<int, int> previo;
    pair<int, int> target;

    do
    {
        cout << "\nColores: ";
        for (int i = 0; i < game.colores.size(); i++)
        {
            cout << game.colores[i].color << "   ";
        }
        cout << endl;
        cout << "\nIngrese color a unir(caracter): ";
        cin >> c;
        c = toupper(c);
        for (int i = 0; i < game.colores.size(); i++)
        {
            if (game.colores[i].color == c)
            {
                mov = game.colores[i];
                posColor = i;
                flag_color = true;
                break;
            }
        }

        if (flag_color == false)
        {
            system("clear");
            cout << "Color no encontrado, ingrese un caracter valido" << endl;
            // cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
            printMatrix();
        }
        if (flag_color == true)
        {
            cout << "Color seleccionado y valido: " << c << endl;
            cout << "Puntos: " << endl;
            cout << "\tFila"
                 << "\tColumna" << endl;
            cout << "\t" << mov.puntos[0].first << "\t" << mov.puntos[0].second << endl;
            cout << "\t" << mov.puntos[1].first << "\t" << mov.puntos[1].second << endl;
            cout << "Presione una tecla para continuar...";
            cin.get();
            cin.get();
        }
    } while (flag_color == false);

    if (flag_color == true)
    {
        int flag_casilla = 0;
        do
        {

            system("clear");
            printMatrix();
            mov.historial = game.colores[posColor].historial;
            cout << "Movimiento en color: " << mov.color << endl;
            cout << "\n\nSELECCIONE CASILLA A MARCAR: " << endl;
            cout << "\t-Si es su primera seleccion en el movimiento: Seleccione la casilla del color " << mov.color
                 << " por donde desea iniciar" << endl;
            cout << "\t-Ingrese -1 como fila o columna para finalizar movimiento, se guardara las casillas marcadas " << endl;
            cout << "Puntos del color " << mov.color << " : " << endl;
            cout << "\tFila"
                 << "\tColumna" << endl;
            cout << "\t" << mov.puntos[0].first << "\t" << mov.puntos[0].second << endl;
            cout << "\t" << mov.puntos[1].first << "\t" << mov.puntos[1].second << endl;

            cout << "Fila: ";
            cin >> target.first;
            cout << "Columna: ";
            cin >> target.second;

            flag_casilla = validarCasilla(target, mov);
            //cout << flag_casilla << endl;
            if (flag_casilla == -1)
            {
                cout << "Casilla invalida" << endl;
            }
            if (flag_casilla == 1)
            {
                mov.historial.push_back(target);
                matriz[target.first][target.second] = mov.color;
                game.colores[posColor].historial.push_back(target);
                previo = target;
            }

            if (flag_casilla == 2)
            {
                cout << "Color conectado" << endl;
                this->game.contador--;
            }
            if (flag_casilla == 3 || flag_casilla == 2) // flag_casilla = 3: Salir
            {
                cout << "Finaliza movimiento" << endl;
                game.colores[posColor].historial = mov.historial;
                mov.historial.clear();
                cout << "Presione una tecla para continuar...";
                cin.get();
                cin.get();
                return -1;
            }

            cout << "Presione una tecla para continuar...";
            cin.get();
            cin.get();

        } while (flag_casilla != 3 || flag_casilla != 2);
    }

    return retorno;
}

bool Interfaz::validarGanador()
{
    bool ganador = false;
    int tam = game.tam;
    bool vacio = false;

    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (matriz[i][j] == ' ')
            {
                vacio = true;
                break;
                break;
            }
        }
    }

    if (vacio == false && game.contador < 1)
    {
        return true;
    }
    else
        return false;
}
