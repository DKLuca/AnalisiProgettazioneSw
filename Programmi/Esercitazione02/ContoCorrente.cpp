#include <iostream>
#include "ContoCorrente.hpp"
using namespace std;

ContoCorrente::ContoCorrente(){euro = 0; centesimi = 0; tassoInteresse = 0.0;};
ContoCorrente::ContoCorrente(double tasso) {euro = 0; centesimi = 0; tassoInteresse = tasso; };
double ContoCorrente::SaldoInLire() const
{
    double lire = 0;
    double conversione = 1936.27;
    lire += euro * conversione;
    lire += (centesimi * conversione) / 100;
    return lire;
}
void ContoCorrente::FissaTassoInteresse(double tasso)
{
    if(tasso > 0)
        tassoInteresse = tasso;
    else
    {
        cout << "tasso negativo, inserito a 1 di default" << endl;
        tassoInteresse = 1;
    }
}
void ContoCorrente::DepositaEuro(int e, int c)
{
    if(c >= 0 && e >= 0)
    {
        e += c / 100;
        c = c % 100;
        //se centesimi conto + deposito > 100 li converto in euro
        if(centesimi + c >= 100)
        {
            c = (centesimi + c) % 100;
            e++;
            euro += e;
        }
        else
        {
            centesimi += c;
            euro += e;
        }
    }
    else
    {
        cout << "euro o centesimi negativi, reinserire" << endl;
    }

}

void ContoCorrente::PrelevaEuro(int e, int c)
{
    //farlo convertendo tutto in cent
    if(c >= 0 && e >=0)
    {
        e += c / 100;
        c = c % 100;
        if((e > euro) || (e == euro && c > centesimi))
        {
            cout << "operazione annullata" << endl;
        }
        else
        {
            if(centesimi - c >= 0)
                centesimi -= c;
            else
            {
                e++;
                //centesimi - c è negativo (es. -20)
                //il saldo è 100 - 20 = 100 + (-20)
                centesimi = 100 + (centesimi - c);
            }
            euro -= e;
        }
    }
    else
    {
        cout << "valori negativi, reinserire" << endl;
    }
}

void ContoCorrente::AggiornaSaldo()
{
    //saldo * 1 
}