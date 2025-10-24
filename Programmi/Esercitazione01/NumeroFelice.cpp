#include <iostream>
using namespace std;

int main()
{
    int numero;
    do
    {
        cout << "Inserire il numero per sapere se è felice o meno (positivo): ";
        cin >> numero;
    }while(numero < 0);
    if(Felice(numero))
        cout << "il numero " << numero << " è felice";
    else
}