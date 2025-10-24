#include <iostream>
using namespace std;

bool Perfetto(unsigned);

int main()
{
    unsigned numero;

    cout << "inserire il numero per vedere se è perfetto: ";
    cin >> numero;

    if(Perfetto(numero))
        cout << "il numero " << numero << " è perfetto" << endl;
    else
        cout << "il numero " << numero << " NON è perfetto" << endl;
}

bool Perfetto(unsigned n)
{
    unsigned somma_divisori = 1;
    for(unsigned i = 2; i <= n/2; i++)
        if(n % i == 0)
            somma_divisori += i;
    return (somma_divisori == n) ? true : false;
}