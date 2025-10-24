#include <iostream>
#include <cmath>
using namespace std;

#define TOLERANCE 1e-15

double Radice(double numero);

int main()
{
    double numero;
    double mysqrt;

    cout << "inserire un numero di cui calcolare la radice: ";
    cin >> numero;
    numero = abs(numero);

    mysqrt = Radice(numero);
    cout << "La radice è: " << mysqrt;
}
double Radice(double numero)
{
    double n1 = numero;
    double n2 = 1;
    while(abs(n1 - n2) > TOLERANCE)
    {
        n1 = (n1 + n2) / 2;
        n2 = numero / n1;
    }
    return n1;
}