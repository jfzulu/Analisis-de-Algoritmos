#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>


using namespace std;

vector<int> bin;
void ToBin(int n);
void ToDec(int &n, int exp);
int main()
{
    int n ;

    cin >> n;
    auto start = std::chrono::high_resolution_clock::now();
    ToBin(n);

    int exp = 0;
    int num = 0;

    ToDec(num, exp);

    cout << "El decimal del binario inverso es: " << num << endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "El codigo se demoro: " << duration.count() << " microsegundos" << std::endl;

    return 0;
}

void ToBin(int n)
{

    for (int i = 0; n != 0; i++)
    {
        bin.push_back(n % 2);
        n = n / 2;
    }
}

void ToDec(int &n, int exp)
{
    for (int i = bin.size() - 1; i >= 0; i--)
    {
        if (bin[i] == 1)
        {
            n += pow(2, exp);
        }
        exp++;
    }
}