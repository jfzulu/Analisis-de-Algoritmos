#include "library.h"
#include "interfaz.h"


bool Interfaz::valid(int i, int j, int & n,vector<vector<bool> >& visitado){
	return (i>=0 && j>=0 && i<=n-1 && j<=n-1 && visitado[i][j]==false);
}

int dx[4]={-1,0,0,1};
int dy[4]={0,-1,1,0};
pair<int,int> Interfaz::obtenerColor(int & n,vector<vector<bool> >& visitado){
	pair<int,int> p;
	p.first=-1;
	p.second=-1;
    bool encontro = false;
    int i = 0;

    while(!encontro && i<n){
        int j = 0;
        while(!encontro && j<n){
            if(matriz[i][j]!=32 && visitado[i][j]==false){
				p.first=i;
				p.second=j;
				encontro = true;
			}
            j++;
        };
        i++;
    };
    return p;

	/*for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(matriz[i][j]!=32 && visitado[i][j]==false){
				p.first=i;
				p.second=j;
				return p;
			}
		}
	}
	return p;*/
}

bool Interfaz::solucionar(int i, int j,vector<vector<bool> >& visitado, char & color){
	
    visitado[i][j]=true;

	for(int p=0;p<4;p++){
		int i1=i+dx[p];
		int j1=j+dy[p];
		if(valid(i1,j1,game.tam,visitado)){
			if(matriz[i1][j1]==color){
				visitado[i1][j1]=true;
				pair<int,int> p=obtenerColor(game.tam,visitado);
				if(p.first==-1 && p.second==-1){
					return true;
				}
	            char c=matriz[p.first][p.second];
	            if(solucionar(p.first,p.second,visitado,c)){
	            	return true;
	            }
	            visitado[i1][j1]=false;
			}
			else if(matriz[i1][j1]==32){
				matriz[i1][j1]=color;
				if(solucionar(i1,j1,visitado,color)){
					return true;
				}
				matriz[i1][j1]=32;
			}
		}
	}
	visitado[i][j]=false;
	return false;
}

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
