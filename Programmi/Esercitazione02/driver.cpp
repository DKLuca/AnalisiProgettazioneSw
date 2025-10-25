// File ContoCorrente.cpp
#include <iostream>
#include <iomanip>
#include "ContoCorrente.hpp"

using namespace std;

void InputEuro(int& e, int& c);

int main()
{
  int euro, cent;
  int scelta; 
  float t;
  ContoCorrente cc;

  do
    { cout << "Saldo corrente: " << cc.SaldoInEuro() << "." 
	   << setw(2) << setfill('0') // istruzioni di formato: per vedere i cent
	                              // sempre con due cifre: 13.05 e non 13.5
	   << cc.SaldoCentesimi() << " (lire: " 
	   << cc.SaldoInLire() << ")" << endl
           << "Quale operazione vuoi effettuare?\n"
           << "1: Fissa Tasso\n"
           << "2: Deposita Euro\n"
           << "3: Preleva Euro\n"
           << "4: Aggiorna Saldo\n"
           << "0: Esci\n\n"
           << "Scelta:  ";
      cin >> scelta;
      cout << endl;
      switch (scelta)
        {
        case 1:
	  cout << "Nuovo tasso : ";
	  cin >> t;
	  cc.FissaTassoInteresse(t);
          break;    
        case 2:
          InputEuro(euro,cent);
	  cc.DepositaEuro(euro,cent);
          break;    
        case 3:
          InputEuro(euro,cent);
	  cc.PrelevaEuro(euro,cent);
          break;    
        case 4:
	  cc.AggiornaSaldo();
          break;    
        }
    }
  while (scelta != 0);
}

void InputEuro(int& e, int& c)
{
  cout << "Euro: ";
  cin >> e;
  cout << "Centesimi: ";
  cin >> c;
}
