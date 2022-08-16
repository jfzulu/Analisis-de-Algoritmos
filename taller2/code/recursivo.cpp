#include <stdio.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <chrono>

std::vector<int> numerosViejos;
std::vector<int> numerosNuevos;

void reverse(int ini, int tam)
{
    if (ini == tam)
    {
        int num = numerosViejos[ini];
        numerosNuevos.push_back(num);
    }
    else
    {
        int q = (tam + ini) / 2;
        reverse(q + 1, tam);
        reverse(ini, q);
    }
}

void desBinarisar(int &num, int &exp, int ini, int tam)
{
    if (ini == tam)
    {
        if (numerosNuevos[tam] == 1)
        {
            num += std::pow(2, exp);
        }
        exp++;
    }
    else
    {
        int q = (tam + ini) / 2;
        desBinarisar(num, exp, q + 1, tam);
        desBinarisar(num, exp, ini, q);
    }
}

void binarizar(int numero)
{
    if (numero != 0)
    {
        numerosViejos.push_back(numero % 2);
        binarizar(numero / 2);
    }
}

int main()
{
    
   int numero = 1;
    while (numero != 0)
    {
        int respuesta = 0;
        int exp = 0;
        std::cout << "Ingrese un numero ( escriba 0 para salir)" << std::endl;
        std::cin >> numero;
        if (numero==0){
            std::cout << "El decimal del binario inverso es: " << 0 << std::endl;
        }else{
        auto start = std::chrono::high_resolution_clock::now();
        binarizar(numero);

        reverse(0, numerosViejos.size() - 1);
        numerosViejos = numerosNuevos;
        numerosNuevos.clear();
        reverse(0, numerosViejos.size() - 1);

        desBinarisar(respuesta, exp, 0, numerosNuevos.size() - 1);
        std::cout << "El decimal del binario inverso es: " << respuesta << std::endl;
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "El codigo se demoro: " << duration.count() << " microsegundos" << std::endl;
        numerosNuevos.clear();
        numerosViejos.clear();
        }
    }
    return 0;
}