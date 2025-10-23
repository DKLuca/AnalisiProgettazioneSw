# Titolo
## Intestazione
```cpp
codice cpp
```
* elenchi puntati

**bold**

*italic*

`evidenziata`

## Overload degli operatori
Con l'overload è possibile ridefinire l'utilizzo degli operatori per classi in cui non sono di base implementati. Non tutti gli operatori possono essere sovrascritti, ci sono alcuni operatori riservati.
### Data
Per esempio operatore ++Data:
```cpp
Data& Data::operator++()
{ 
  if (giorno != GiorniDelMese())
    giorno++;
  else 
    if (mese != 12)  
      { 
        giorno = 1;
        mese++;
      }
    else
      { 
        giorno = 1;
        mese = 1;
        anno++;
      }
  return *this;
}
```
#### friend
Si può definire un operatore come funzione esterna, ovvero non dipendente dall'oggetto chiamato. Per `==` o `<=, >=` (sono operatori paritetici).
```cpp
bool operator==(const Data &d1, const Data &d2);
bool operator<(const Data &d1, const Data &d2);
```
Definite fuori dalla classe (stesso file hpp)

```cpp
bool operator==(const Data &d1, const Data &d2)
{
    return ((d1.giorno == d2.giorno) && (d1.mese == d2.mese) && (d1.anno == d2.anno);
}
```
Sono funzioni esterne per sintassi, ma sarebbero definibili come funzioni interne. Si dichiarano quindi come funzioni `friend` e possono accedere ai dati privati. Dentro la classe vanno inizializzate per indicare che sono `friend`.
```cpp
class Data
{
    friend bool operator==(const Data &d1, const Data &d2);
    friend bool operator<(const Data &d1, const Data &d2);
    //...
}
```
La dichiarazione delle funzioni come `friend` sono dichiarazioni vere e proprie, si possono rimuovere quelle fuori dalla classe.

```cpp
bool operator<(const Data &d1, const Data &d2)
{
    return ((d1.anno < d2.anno)
        || ((d1.anno == d2.anno) && (d1.mese < d2.mese))
        || ((d2.anno == d2.anno) && (d1.mese == d2.mese) && (d1.giorno < d2.giorno))
    );
}
```
```cpp
bool operator<=(const Data &d1, const Data &d2)
{
    return ((d1.anno < d2.anno)
        || ((d1.anno == d2.anno) && (d1.mese < d2.mese))
        || ((d2.anno == d2.anno) && (d1.mese == d2.mese) && (d1.giorno <= d2.giorno))
    );
}
```
Cambia dal `<` solo con l'ultima condizione dell'or in cui al posto di `<` si pone `<=`.
### Complessi
La classe complessa è composta da un campo Re e un campo Im che sono degli interi:
```cpp
class Complesso
{
    private:
        int Re;
        int Im;
        Complesso();
        Complesso(int Re, int Im = 0);
}
```

```cpp
Complesso(int Reale, int Immaginario = 0)
{
    Re = Reale;
    Im = Immaginario;
}
void Complesso::operator+=(const Complesso& c)
{
    Re = c.Re;
    Im = c.Im;
}
Complesso Complesso::operator+(const Complesso& c) const
{
    //il const a dx della funzione indica che è un selettore
    //il const del parametro indica che il parametro è const
    /*
    Complesso r;
    r.Re = Re + c.Re;
    r.Im = Im + c.Im
    */
    return Complesso(Re + c.Re, Im + c.Im);
}
```
Creo un oggetto anonimo che viene restituito immediatamente, non dovendolo utilizzare è inutile crearne uno. Si può sfruttare il costruttore per creare l'oggetto con i campi dati dalla somma dei due
```cpp
Complesso Complesso::operator*(const Complesso& c) const
{
return Complesso(Re * c.Re - Im * c.Im, Re * c.Im + Im * c.Re);
}
```
Sia `+` che `*` sono operandi con operatori paritetici, si possono ripensare come funzioni friend esterne

```cpp
Complesso operator+(const Complesso &c1, const Complesso &c2)
{
    return Complesso(c1.Re + c2.Re, c1.Im + c2.Im);
}
```
E vanno inserite le funzioni come `friend`:

```cpp
class Complesso
{
    friend:
        Complesso operator+(const Complesso &c1, const Complesso &c2);
        Complesso operator*(const Complesso &c1, const Complesso &c2);
        //...
}
```
se io inserisco
```cpp
c1 = c2 + 3.14;
```
esiste un convertitore tra `double` e `Complesso` tramite il costruttore, questa espressione è quindi sensata e corretta.

Se scrivo 
```cpp
c1 = 3.14 + c2;
```
Se utilizzato l'operator + interno alla classe non funziona in quanto non può fare la conversione dell'oggetto chiamante. Si può eseguire giustamente solo se definita come esterna (o friend) che permette la conversione di entrambi gli operandi e non unicamente di quelli a destra. (Analogo nella classe Data però sono più delicate, hanno un'aritmetica particolare).

### Operatori input-output
`<<` : L'operatore di output è definito su due operatori: `cout` e `Oggetto`.

`cout` è un oggetto della classe `ostream` . L'operatore viene definito come funzione esterna, non si può definire un metodo della classe di destra ma solo di quella di sinistra. Dovrei modificare la classe `ostream` e non si può fare.

Si dichiara come `friend` della classe `Data`

```cpp
    friend void operator<<(ostream& os, const Data& d);
```
l'abbiamo definita come `void` in prima approssimazione, la funzione non restituisce niente concettualmente.

```cpp
    void operator<<(ostream& os, const Data& d)
    {
        os << d.giorno << '/' << d.mese << '/' << d.anno;
    }
```
Gli operatori in/out li abbiamo concatenati molto spesso, con questo overload non è possibile. Dobbiamo restituire `l'ostream` stesso. 

```cpp
    friend ostream& operator<<(ostream& os, const Data& d);
    //...
    ostream& operator<<(ostream& os, const Data& d)
    {
        os << d.giorno << '/' << d.mese << '/' << d.anno;
        return os;
    }
```
Devo restituire `os` stesso e non una copia (senza `&` non sarebbe possibile perché ritorna la copia dell'oggetto e non è permesso dalla classe `ostream`)

```cpp
    friend istream& operator>>(istream &is, Data &d);
    //...
    istream& operator>>(istream &is, Data &d)
    {
        char ch;
        is >> d.giorno >> ch >> d.mese >> ch >> d.anno;
        //leggo gg/mm//aa (o gg-mm-aa);
        return is;
        //se (gg mm aa) gli spazi e i tab non vengono considerati caratteri significativi e non vengono
        //presi dal cin >> ch
        //per controllare la validità
        if(d.isValid())
        {
            d.giorno = 1;
            d.mese = 1;
            d.anno = 1970;
        }
    }
```
