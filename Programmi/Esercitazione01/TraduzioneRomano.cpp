#include <iostream>
#include <string>
using namespace std;

int Traduzione(string);
int ConvertiCarattere(char);

int main()
{
    string s;
    int romano;

    cout << "inserire il numero romano: ";
    cin >> s;
    for(int i = 0; i < (int)s.length(); i++)
        s[i] = toupper(s[i]);
    cout << s;
    romano = Traduzione(s);
    cout << romano;
}

int Traduzione(string s)
{
    int numero = 0; //numero convertito
    int elemento; //carattere convertito
    int elementoSucc; //carattere successivo convertito
    int i; //indice del vettore di caratteri da convertire

    cout << "lunghezza stringa: " << (int)s.length() << endl;
    for(i = 0; i < (int)s.length() - 1; i++)
    {
        elemento = ConvertiCarattere(s[i]); //converto il numero attuale
        elementoSucc = ConvertiCarattere(s[i + 1]); //converto il successivo

        //cout << "i: " << i << " elemento: " << elemento << "elementoSucc: " << elementoSucc << endl;

        if(elemento == -1 || elementoSucc == -1)  //se uno dei due caratteri non esiste -> esco
            return -1;
        else
            if(elemento >= elementoSucc) //se l'elemento attuale è maggiore o uguale del successivo
                numero += elemento; //lo sommo
            else //l'elemento attuale è più piccolo del successivo
            {
                numero += (elementoSucc - elemento); //sommo il numero successivo meno attuale (IX = X - I  = 9)
                i++; //incremento l'indice a elementoSucc che ho sommato
            }
        
    }
    //cout << "Fuori dal for, i: " << i << "numero: " << numero << endl;
    //verificare se sono arrivato alla fine della conversione o meno
    if(i == ((int)s.length() - 1))
        numero += ConvertiCarattere(s[i]);
    return numero;
}
int ConvertiCarattere(char c)
{
    switch(c)
    {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return -1;
    }
}