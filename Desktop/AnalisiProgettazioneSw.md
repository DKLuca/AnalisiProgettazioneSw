# Analisi e progettazione del sw

```cpp
git add AnalisiProgettazioneSw.md
git commit -m "Aggiornato Appunti.md con nuove sezioni"
git push origin main
```

## Passaggio di parametri

I parametri formali vengono creati copiando il valore attuale nel record di attivazione della funzione chiamata. Per passare una variabile per riferimento

```cpp
void F(int& a);
```

oppure viene fatto utilizzando i pointer come nella sintassi del C.

Se passo un `int` a una funzione che vuole un `double` viene fatta una conversione implicita (non tutte le conversioni sono ammesse) mentre se li passo per riferimento è necessario che il tipo coincidi.

## File HPP

È buona norma dividere i file in intestazione (header .hpp) e file di corpo (.cpp) e includere l'intestazione nel file di corpo corretta. Non è inusuale che un file hpp venga chiamato da diversi file cpp in quanto le stesse funzioni possono essere chiamate in contesti diversi. Per evitare tali problemi si inserisce nell'intestazione:

```cpp
#ifndef NOME_FILE_HPP
#define NOME_FILE_HPP
//...
//corpo del file
//...
#endif
```

È molto importante che questo frammento venga incluso per evitare errori più o meno gravi quando si lavora con grossi progetti ripartiti in molti file.

## Makefile

Uno strumento sicuramente comodo è il makefile che risponde al comando make. Tale strumento guarda la data di creazione dell'oggetto e la data dell'ultima modifica del cpp. Se la data del cpp è più recente va a compilare nuovamente il file creando un nuovo oggetto. In questo file si possono includere anche compilazioni parziali che facilitano le istruzioni da tastiera. Le compilazioni parziali sono comode per vedere eventuali errori nel file singolo senza dover compilarli tutti.

Il comando clean va ad eliminare tutti i file creati con estensione `.o` e `.exe`

```cpp
ManipolaDate.exe: ManipolaDate.o MainDate.o
    g++ -o ManipolaDate.exe ManipolaDate.o MainDate.o

ManipolaDate.o: ManipolaDate.cpp ManipolaDate.hpp
    g++ -c -Wall ManipolaDate.cpp

MainDate.o: MainDate.cpp ManipolaDate.hpp
    g++ -c -Wall MainDate.cpp
```

Quello sopra è un esempio di makefile.

## Allocazione dinamica della memoria

I vettori a dimensione fissa vengono creati nel record di attivazione della funzione chiamante, non è buona norma chiedere prima la dimensione massima dei vettori e poi crearlo. Per ovviare a questo problema o a eventuale esaurimento della memoria dello spazio di archiviazione si sposta il tutto nell'`heap`. Per creare un vettore dinamico si procede come segue:

```cpp
int *p;
p = new int [n];
```

- `p` è una variabile usata come puntatore;
- `new` è una parola del linguaggio;
- `n` è la dimensione del vettore

L'heap è una sezione di memoria separata ed è importante liberarla una volta finito di utilizzarla tramite il comando:

```cpp
delete []p;
```

- [ ] sono da inserire unicamente se p viene utilizzato come vettore altrimenti sono da omettere.

## Analisi del SW

Ha due argomenti principali:

- ciclo di vita del sw
- qualità del sw

### Ciclo di vita

Secondo il modello a cascata ogni fase è successiva (sequenziale) e questo a livello di sw non è realistico.

1) Studio di fattibilità
2) Analisi (dei requisiti)
3) Progetto e sviluppo
4) Verifica e correzioni
5) Manutenzione

#### 4 Verifica e correzioni

Ci sono due macro famiglie: (a) verifica formale e test (b)

- (a) si usa solo in contesti specifici in quanto si deve dimostrare analiticamente che una funzione svolga il lavoro desiderato. A livello generale non è quasi mai applicabile, anche solo l'alting problem lo dimostra: non è possibile dimostrare che una funzione non vada in ciclo infinito garantendo che la funzione di test non vada in ciclo infinito a sua volta.

- (b) inserisco un input e verifico se l'output è coerente con quello che dovrebbe fare la funzione

- (b1) `test a copertura`: cerca di coprire tutti i rami del programma ad esempio se ho if (a < 50) faccio un test con a < 50 e uno con a > 50 per vedere entrambi gli esiti se corrispondono alle aspettative

- (b2) `scatola nera` i test vengono scritti senza nemmeno vedere il programma ma in base alle specifiche. Il vantaggio è che i test possono essere scritti in anticipo o da persone diverse.

    Si usano i `driver` per provare il programma o `stub` che vengono usate al posto delle funzioni, si fa un return a priori senza dover scrivere la funzione e ci si pensa in un secondo momento.

Mediamente si dedica in % una data quantità del progetto

1) dal 2 al 5%
2) dal 5 al 10%
3) dal 20 al 30%
4) dal 10 al 20%
5) dal 40 al 60%

Ovviamente meglio è fatto il progetto e più semplice sarà la manutenzione

#### 5 Manutenzione

- a. Adeguamento a nuove specifiche (il più importante (40%))

- b. Modifiche dei formati dei dati (20%)

- c. Correzione di errori non rivelati (20%)

- d. Miglioramento dell'efficienza (5%)

- ...

### Qualità del software

#### Qualità esterne

Sono le qualità percepite dall'utente che usa il programma

- correttezza: si considera corretto se l'output è coerente con i dati di ingresso assunti corretti (ovvero che rispettino delle precondizioni). Fuori dalle precondizioni il programma deve essere `robusto`

- robustezza: questo è suddiviso in più livelli, lvl 0 non fa nulla, lvl 1 diagnostica l'errore, lvl 2 cerca di correggerlo. Noi useremo un lvl 1.5, ovvero che lanceremo delle eccezioni a ogni errore senza poi farne il catch.

- usabilità: quanto è semplicemente si può usare

- efficienza: si deve far buon uso delle risorse come spazio di memoria e/o tempo

- costo

#### Qualità interne

Sono le qualità che si riscontrano ispezionando il codice

- modularità: strutturazione in moduli come funzioni, più file, classi etc.

- leggibilità: deve essere facilmente comprensibile da un umano tramite l'utilizzo di nomi significativi e/o commenti

- riusabilità: possibilità di riusare il codice per altri scopi e non creare delle, per esempio, funzioni molto specifiche

- portabilità: usare il codice su dispositivi diversi per SO o per sw

#### Modularità

- coesione: un modulo deve fare una cosa sola (specifico compito)

- interfacciamento esplicito: i metodi comunicano tra di loro in modo esplicito dichiarando i parametri passati e se verranno modificati, l'uso di variabili globali non è esplicito

- interfacciamento minimo: i moduli devono comunicare con il numero minimo di altri moduli

- disaccoppiamento: ogni modulo deve sapere cosa passare e ricevere da una funzione senza sapere i dati come verranno trattati o nulla in più del necessario. Ogni funzione deve essere usabile in senso proprio senza dipendere dalle altre strettamente

- provatezza dell'informazione: un modulo deve nascondere i dettagli per evitare chi lo chiama di sbagliare, "non so com'è fatto ma so come usarlo"

## Programmazione orientata agli oggetti

xxx

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

Se scrivo:

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

## Classe Stack

Ha un utilizzo molto limitato perché ha un numero finito di primitive. È una struttura LIFO (Last In - First Out)

- `push`: inserimento di un dato alla cima della pila
- `pop`: elimina l'elemento in cima alla pila 
- `top`: mi dice l'elemento in cima
- `isEmpty`: restituisce un bool a seconda se la pila è vuota o meno. (true = vuota, false = non vuota)

Le pile sono usate ad esempio nei record di attivazione

```cpp

//...
//corpo del file
//...
#endif
//file.hpp
#ifndef STACK_HPP
#define STACK_HPP
class Stack //(o Pila)
{
    public:
        Stack();
        void Push(int e);
        void Pop() {top--;} //non robusto, andrebbe fatta isEmpty()
        int Top() const { return v[top]; } //non modifica la pila
        bool isEmpty() const {return (top == -1);}

    private:
        //non c'è una isFull(), la pila non dovrebbe avere
        //un limite superiore (uso un vettore dinamico)
        //alloco un vettore di dimension N e quando si riempie
        //dealloco il vettore lungo N e ne rialloco un vettore lungo 2N

        int* v;
        int DIM; //non unsigned (vederemo più avanti perché)
        int top; //posizione elemento in cima

    friend:
        ostream& operator<<(ostream& os, const Stack& s);
        istream& operator>>(istream& is, Stack& s);
};
#endif
```

```cpp
Stack p;
p.Push(3);
p.Push(-5);
p.Pop();
cout << p.Top(); //stampa 3
```

```cpp
//file.cpp
Pila::Pila()
{
    DIM = 100;
    v = new int[DIM];
    top = -1;
}

Pila::Push(int e)
{
    if(top + 1 == DIM) //o (top == DIM - 1)
    {
        int *aux;
        aux = new int[2DIM];

        //copio gli elementi nel nuovo
        for(int i = 0; i < DIM; i++) //o (i <= top)
            aux = v;

        delete []v; //libero la memoria
        v = aux; //cambio ptr e lo punto al nuovo blocco
        DIM *= 2; //raddoppio la dimensione
    }
    v[++top] = e; //a valle di eventuale riallocamento
}

ostream& operator<<(ostream& os, const Stack& s)
{
    //(elem1, elem2, ... , elemTop)
    os << '(';

    for(int i = 0; i < s.top; i++)
        os << s.v[i] << ", ";

    //se i <= s.top stampo ( ..., elemTop, ) <- errore trascinamento
    //os << s.v[s.top]; se vuota accedo alla locazione -1

    if(!s.isEmpty())
        os << s.v[s.top];
    os << ')';

    return os;
}

istream& operator>>(istream& is, Stack& s)
{
    //non sapendo la dimensione dello stack letto da input
    //faccio le push degli elementi e ci pensa lei per eventuale
    //stack pieno

    //>> sovrascrive la pila
    s.top = -1; //"cancello" la pila

    int e;
    char ch;
    is >> ch; //elimino la prima (
    //leggo il carattere successivo e se ) la pila è vuota
    //problema che "consumo" un carattere

    //esiste un metodo di istream che prende il primo carattere
    //senza "consumarlo" con la peek
    ch = is.peek();
    if(ch != ')') //stack non vuota;
    {
        do
        {
            is >> e >> ch;
            s.Push(e);
        } while (ch != ')');
    }
    else //devo comunque leggere la chiusa tonda
        is >> ch;

    return is;
}
```
Per leggere i caratteri ci sono tre modi:

- ```is >> ch```; legge un carattere significativo (no spazi, tab, \n)
- ```ch = is.get();``` prende il primo carattere anche non significativo
- ```ch = is.peek();``` "vede" il primo carattere

Quando faccio 

```cpp
Stack s1, s2;
s1 = s2;
```

Con questa assegnazione il puntatore presente dentro a s2 (v) punta al puntato di s1. Facendo ora `p2.Push(21)` vado a scrivere dentro al vettore creato da s1 e non si fa la copia del vettore ma solo del puntatore. Si ha quindi la condivisione di memoria (essendo dinamica) e a sua volta l'interferenza. Il vettore inizialmente creato per s2 viene perso (memory leak) e non è più accessibile. Per ovviare a questo problema si deve ridefinire l'operatore di assegnazione.

Tutte le classi che usano l'allocazione dinamica della memoria devono ridefinire l'operatore di assegnazione e il costruttore di copia.

```cpp
//facciamo con funzioni esterne le operazioni con operatori paritetici
//a sx c'è sempre un oggetto e a dx un parametro

//l'uguale ha precedenza a destra
Stack& Stack::operator=(const Stack& s)
{
    if(this != &s) //evito l'autoassegnazione
    {
        //se s.top >= DIM devo riallocare
        if(s.top >= DIM)
        {
            delete []v; //libero la memoria attuale
            DIM = s.DIM;
            v = new int[s.DIM]; //alloco un vettore più grande (quanto s2)
        }
        top = s.top;
        
        for(int i = 0; i <= top; i++)
            v[i] = s.v[i];
    }
    return *this; //ritorno l'oggetto corrente
}
```

Non è stato risolto il costruttore di copia che viene chiamato quando si crea un oggetto inizializzandolo con un altro oggetto della stessa classe.

```cpp
//costruttore di copia
Stack s1 = s2; //Stack s1(s2);
```

Si deve ridefinire anch'esso come l'operatore di assegnazione

```cpp
Stack::Stack(const Stack& s)
{
    DIM = s.DIM;
    top = s.top;
    v = new int[DIM];

    for(int i = 0; i <= top; i++)
        v[i] = s.v[i];
}
```
Quando passiamo un oggetto per valore o lo restituiamo, viene incocato il costruttore di copia

Finito il programma/funzione, i vari vettori allocati non vengono eliminati automaticamente, si deve ridefinire il distruttore della classe per liberare la memoria.

```cpp
Stack::~Stack()
{
    delete []v;
}
```

Nel cpp esiste una costante di tipo puntatore `nullptr` che indica che il puntatore non punta a nulla. Si può usare per inizializzare i puntatori.

## Classe String

La classe stringa è una classe che gestisce le stringhe di caratteri. In C esistono le stringhe come array di caratteri terminati dal carattere nullo `'\0'`. La classe stringa gestisce internamente l'array di caratteri e fornisce delle primitive per manipolarle.

```cpp
String s("Pippo");
//equivale a
s = "Pippo";
//viene chiamato il costruttore che prende come parametro una stringa (array di caratteri)
``` 

Esiste l'operatore `[]` per accedere ai singoli caratteri della stringa.

```cpp
char c = s[0]; //c = 'P'
s[1] = 'a'; //s = "Pappo"

//voglio che funzioni anche
string s[2] = ch;
//se devinisco l'operatore [] come funzione const, non funziona
//il trucco è di definire due operatori []
char& String::operator[](unsigned i) const 
{
    //controlli su i
    return v[i]; //v è il vettore di caratteri
}
char String::operator[](unsigned i) const 
{
    //controlli su i
    return v[i]; //v è il vettore di caratteri
}

//fanno due cose diverse a seconda se l'oggetto è const o meno

ch = s[s.lenth() + 2]; //errore (buffer overflow)

//il metodo at fa il controllo sull'indice
ch = s.at(s.length() + 2); //lancia eccezione
```

## Lettura e scrittura di file
Per leggere e scrivere su file si usano due classi: `ifstream` per la lettura e `ofstream` per la scrittura. Entrambe derivano dalla classe `fstream` che gestisce sia la lettura che la scrittura.

```cpp
#include <fstream>
using namespace std;
//scrittura su file
ofstream os;
os.open("nomefile.txt");
//ofstream fout("nomefile.txt"); open nel costruttore
if(!os)
{
    cerr << "Errore nell'apertura del file" << endl;
    exit(1);
}
os << "Ciao mondo!" << endl; //scrivo dentro al file una riga
os.close();

//sia open che close sono superflue
```

```cpp
//lettura da file
ifstream fin("nomefile.txt");
if(!fin)
{
    cerr << "Errore nell'apertura del file" << endl;
    exit(1);
}
string line;
while(getline(fin, line))
{
    cout << line << endl;
}
fin.close();
```

## Esercizi

File contiene un file di date ordinate cronologicamente, si scriva una funzione che prende un file e si fornisca la media delle date presenti nel file.

Fare le date - data di riferimento, media dei giorni e la sommo alla data di riferimento e ottengo la data media.

In c si usa:

```c
while(fscanf(fp, ... ) != EOF)
```
Per leggere tutto il file fino alla fine.

Mentre in cpp per leggere l'intero file (fino all'EOF):

```cpp
while(is >> d) //con l'operatore di input, se non riesce a leggere: esce. C'è un convertitore da ostream a int (while prende un intero e non un bool per compatibilità con il c)
```

```cpp
#include <iostream>
#include <fstream>
#include "Data.hpp"
using namespace std;

Data mediaDate(string filename)
{
    ifstream is(filename);
    Data d_rif, d1;
    unsigned somma = 0, conta = 0;

    while (is >> d1)
    {
        somma += d1 - d_rif; //conversione in giorni
        conta++;
    }
    return ((d_rif + somma) / conta); //ritorno la data media
}
```

```cpp
int operator-(Data d1, Data d2)
{
    int n = 0;
    if (d1 < d2)
    {
        Data aux = d1; //creo una data ausiliaria per non modificarla
        while (aux != d2)
        {
            aux++;
            n++;
        }
    }
    else
    {
        Data aux = d2;
        while (aux != d1)
        {
            aux++;
            n++;
        }
    }
    return n;
}
```

Non si può invocare il costruttore di un oggetto già costruito

```cpp
A a1(5);
a1(5); //errore
```

cerca di invocare l'operatore `()` sull'oggetto a1. Si può ridefinire l'operatore `()` per una classe anche se in questo esempio non è definito.

```cpp
int main()
{
    A a1(5), a2(5);
    a1.Set(3,-4);
    a1.Set(4,9);
    a2 = a1;
    a2.Set(4,-6);
    a2.Flip();
    cout << a1.Get(4) << ' ' << a2.Get(4) << endl;
}
```
C'è un errore in questo codice in quanto c'è la condivisione di memoria tra a1 e a2. Si deve ridefinire l'operatore di assegnazione e il costruttore di copia per evitare questo problema.

Prima del fix viene stampato `-4` e `0`

```cpp
//costruttore di copia
A::A(const A& a)
{
    unsigned i;
    b = a.b;
    size = a.size;
    p1 = new int[size];
    for(i = 0; i < size; i++)
        p1[i] = a.p1[i];
    if(a.p2 == nullptr)
        p2 = nullptr;
    else
    {
        p2 = new int[size];
        for(i = 0; i < size; i++)
            p2[i] = a.p2[i];
    }
}
```

L'operatore di assegnazione:

```cpp
A& A::operator=(const A& a)
{
    unsigned i;
    b = a.b;
    size = a.size; //eventuale if per riallocare se dimensioni diverse, in caso copia degli elementi
    delete []p1; //elimino i vettori creati
    delete []p2;
    p1 = new int[size];
    for(i = 0; i < size; i++)
        p1[i] = a.p1[i];
    if(a.p2 == nullptr)
        p2 = nullptr;
    else
    {
        p2 = new int[size];
        for(i = 0; i < size; i++)
            p2[i] = a.p2[i];
    }
    return *this;
}
```

### Esercitazione 3

Gestione di un polinomio con coefficienti reali ed esponenti interi. È imposto che vengano inseriti in un vettore fino al massimo esponente. Le celle contengono il coefficiente (es 1x^3 + 1 va inserito in un vettore di dimensione 4 con celle 1,0,0,1). 

Il vettore va fatto di dimensione massima pari all'eponente.

C'è un costruttore che costruisce un monomio: `Polinomio P(3,100);`. Operatore che valuta il polinomio, si fa con l'operatore (). `double operator()(double y)` (quanto vale il polinomio nel punto, sostituisco x con il valore dentro le parentesi).

Le parentesi [] vogliono un unsigned int unico, le parentesi tonde è molto più generico.

Leggere e scrivere nel seguente modo: `-3.2x^4 + 3.1x^2 + -7.2x^0` sempre nell'ordine dal più grande al più piccolo. Ci dice quanto grande allocare il vettore.

## Composizione tra classi

```cpp
class A
{
    //...
};
class B
{
    //...
    A a; //ha un campo di tipo A
};
int main()
{
    //quando dichiaro due oggetti di tipo B
    B b1, b2;
    b1 = b2;
    //invoca l'operatore di assegnazione di B, se non presente invoca quello di default. Si copia anche l'oggetto A con il proprio operatore di assegnazione.
    //B può essere statica e A dinamica e viene gestito internamente
    //se non ho scritto il costruttore di B ma di A, quando creo b1 e b2 non viene inizializzato nessun elemento tranne la classe A perché ha un proprio costruttore
}

```

```cpp
//se avessi un costruttore in B
class B
{
    B(int k, int j);
    int i;
    A a;
}
//j lo voglio usare per inizializzare A
//ipotizzo che A abbia un costruttore con parametro int
B::B(int k, int j)
    : a(j)
{
    i = k;
}
//se non iserito :a(j) viene chiamato quello di default senza parametri
B::B(int k, int j)
{
    i = k;
    a = A(j);
}
//è uguale ma si crea un oggetto di appoggio (A(j)) solo per l'assegnazione.
```

### Classe Impegno

```cpp
Impegno(string nome, Data d1, Data d2 = Data());
//questo costruttore imposta la data di default a d2 se non passato come parametro
//si ipotizza che l'impegno non abbia fine se la sua data (di fine) è quella di default
```

Supponendo di voler un impegno senza una data di fine (con nessun valore di riferimento), devo usare un puntatore. Se il puntatore punta a `nullptr` significa che non c'è una data di fine. È più complesso in quanto si deve implementare la gestione di un oggetto.

### Classe Impegno2

```cpp
class Impegno2
{
    //...
    private:
        string nome;
        Data inizio;
        Data* p_fine; //puntatore a data
};
```

Al posto di avere un oggetto statico, ne ho uno dinamico. Devo implementare il costruttore di copia e l'operatore di assegnazione per evitare la condivisione di memoria.

```cpp
Impegno2::Impegno2(string n, Data d1, Data d2)
    : nome(nome), inizio(d1)
{
    if(d2 == Data()) //se d2 è la data di default
        p_fine = nullptr; //nessuna data di fine
    else
        p_fine = new Data(d2); //creo una nuova data con il valore di d2 (costruttore di copia)
}
```

Siamo abitatuati a usare `p = new int[DIM];` per creare vettori dinamici, ma si può usare anche per oggetti singoli tramite l'uso di parentesi tonde: `p = new int(valore);`

Se usassi: `p = new Data[10];` verrebbe chiamato il costruttore di default e non quello con parametro per creare un vettore di Date lungo 10.

Per il distruttore del singolo oggetto si usa: `delete p` mentre per i vettori `delete []p;`. Le parentesi quadre in realtà servirebbero per indicare che il distruttore va chiamato per ogni elemento del vettore. Nel vettore di interi non sarebbe necessario in quanto non sono oggetti i singoli elementi.

```cpp
Impegno2::Impegno2(string n, int anno 1, int anno2)
    : nome(n), inizio(1,1,anno1)
{
    p_fine = new Data(31,12,anno2);
}
```

```cpp
Impegno2::Impegno2(const Impegno2& im)
    : nome(im.nome), inizio(im.inizio)
{
    if(im.p_fine == nullptr)
        p_fine = nullptr;
    else
        p_fine = new Data(*(im.p_fine)); //dereferenzio il puntatore per ottenere l'oggetto Data
        //copio il valore dell'oggetto puntato (senza puntatore copierei l'indirizzo di memoria e tutti gli elementi dell'oggetto)
}
```

```cpp
Impegno2& Impegno2::operator=(const Impegno2& im)
{
    nome = im.nome;
    inizio = im.inizio;
    //se l'elemento che voglio copiare non ha data di fine
    if(im.p_fine == nullptr)
    {
        //l'oggetto in cui sto copiando ne ha una
        //la cancello
        if(p_fine != nullptr)
        {
            delete p_fine; //libero la memoria attuale
            p_fine = nullptr;
        }
        //se sono entrambi nullptr non faccio nulla
    }
    //l'elemento che voglio copiare ha una data di fine
    else
    {
        if(p_fine == nullptr)
            p_fine = new Data(*(im.p_fine)); //creo un nuovo oggetto Data
        else
            //faccio la copia profonda
            *(p_fine) = *(im.p_fine); //assegno il valore all'oggetto esistente
            //la copia delle date è gestito dalla classe Data
            //non mi preoccupo di come è fatto internamente
    }
    return *this;
}
```

```cpp
Impegno2::~Impegno2()
{
    delete p_fine; //se p_fine è nullptr non succede nulla
}
```

```cpp
Data Impegno2::getFine() const
{
    if(p_fine == nullptr)
        //throw lancia un'eccezione (si rivedrà più avanti)
        throw runtime_error("Impegno senza data di fine");
    return *p_fine; //ritorno l'oggetto puntato
}
```
## Template

Si dichiara una classe generica che può essere istanziata con diversi tipi di dato tramite l'uso di template.

Si userà poi, ad esempio,
`Pila<int> p1;` per una pila di interi e `Pila<double> p2;` per una pila di double. Istanzierà due classi distinte con tipi diversi, non si potrà fare l'assegnazione tra oggetti di tipo diverso.

Si potrà fare anche per le funzioni esterne e non solo per i metodi di una classe

Il template sta tutto nell'hpp e non avrò un cpp separato.
```cpp
template <typename T>
class Pila
{
    public:
        Pila();
        Pila(const Pila<T>& p);
        Pila<T>& operator=(const Pila<T>& p);
        void Push(const T& e); //passo un T per riferimento costante
        void Pop() {top--;} //non robusto, andrebbe fatta isEmpty()
        T Top() const { return v[top]; } //non modifica la pila
        bool isEmpty() const {return (top == -1);}
    private:
        T* v; //generito tipo T
        int DIM; //dimensione del vettore
        int top; //posizione elemento in cima
};

template <typename T>
Pila<T>::Pila()
{
    DIM = 100;
    v = new T[DIM];
    top = -1;
}
//posso creare uno stack di oggetti A ma la classe deve contenere il costruttore di copia e l'operatore di assegnazione oltre che il costruttore senza parametri
//posso usare qualsiasi cosa finché abbia le operazioni che uso dentro la classe Pila (anche, per esempio, l'input e output)
```

La classe è identica alla Stack precedente ma in forma generica, è stato sostituito `int` con `T`.

Si può fare anche `Pila<Pila<int>> p;` per avere una pila di pile di interi.

Per le classi friend con template, devo usare un secondo template.

Si può usare il template per le funzioni esterne, ad esempio per le funzioni di minimo o massimo. Se la classe o i tipi hanno l'operatore `<` definito, si può fare il calcolo del minimo (e del massimo)

```cpp
template <typename T>
//return per riferimento costante
const T& min(const T& a, const T& b)
{
    return (a < b) ? a : b;
}
```

## Vector
La classe vector è una classe che gestisce un vettore dinamico di oggetti di tipo T. Si comporta come un array dinamico ma con una gestione più semplice della memoria.

```cpp
#include <vector>
using namespace std;
vector<int> v; //vettore di interi

//costruttori
vector<int> v1; //vettore vuoto (dimensione 0)
vector<int> v2(10); //vettore di dimensione 10 con valori a 0
vector<int> v3(10, 5); //vettore di dimensione 10 con tutti gli elementi inizializzati a 5 (v3(unsigned, T))
vector<int> v4{3,4,5,6}; //vettore con inizializzazione lista

//accesso agli elementi
v3[2] = 10; //assegna 10 alla terza posizione del vettore v3
int d = v2[3]; //assegna alla d il valore della quarta posizione di v2, non c'è check di posizione e si può usare se v2 è const
d = v2.at(3); //assegna alla d il valore della quarta posizione di v2, c'è il check di posizione e lancia eccezione se fuori range

//dimensione del vettore
unsigned n = v.size(); //restituisce la dimensione del vettore
v.push_back(3); //inserisce in fondo al vettore l'elemento, se il vettore è pieno lo ridimensiona automaticamente aggiungendo una posizione (di solito raddoppia la dimensione)
v.resize(20); //ridimensiona il vettore a 20 elementi, se più grande aggiunge elementi a 0, se più piccolo elimina gli elementi in eccesso
v.resize(20, 7); //ridimensiona il vettore a 20 elementi, se più grande aggiunge elementi a 7, se più piccolo elimina gli elementi in eccesso
v.clear(); //equivalente alla resize(0), elimina tutti gli elementi del vettore

//esiste anche la push_front() ma è inefficiente in quanto sposta tutti gli elementi

v3.pop_back(); //elimina l'ultimo elemento del vettore

v3.back(); //restituisce l'ultimo elemento del vettore 
//equivale a v3[v3.size() - 1];

v3.pop_front(); //elimina il primo elemento del vettore, inefficiente in quanto sposta tutti gli elementi 

//Il vector è tutto consecutivo in memoria, non ci sono buchi come con le pile

v2.insert(v2.begin() + 2, 10); //inserisce il valore 10 nella terza posizione del vettore v2, spostando tutti gli elementi successivi di una posizione

v2.erase(v2.begin() + 3); //elimina il quarto elemento del vettore v2, spostando tutti gli elementi successivi di una posizione indietro 
//devo fornire l'indirizzo iniziale del vettore più lo spostamento perché vuole l'indirizzo corretto e non solo l'offset.

//esiste la erase per intervalli
v2.erase(v2.begin() + 2, v2.begin() + 5); //elimina gli elementi dalla terza alla quinta posizione (esclusa la quinta) del vettore v2

v2.insert(v2.begin() + 2, 3, 7); //inserisce tre elementi con valore 7 a partire dalla terza posizione del vettore v2

//insert ed erase sono operazioni costose in quanto spostano gli elementi del vettore tramite l'uso di iteratori

sort(v.begin(), v.end()); //ordina il vettore v in ordine crescente, richiede l'header <algorithm>

v.reserve(1000); //riserva spazio per 1000 elementi, non cambia la dimensione del vettore ma solo la capacità (evita riallocazioni continue se si sa che si devono inserire molti elementi). Non fa new o delete future
```

Non sono presenti matrici nella libreria standard, si può usare un vector di vector per simulare una matrice.

```cpp
vector<vector<int>> mat; //matrice di interi vuota

vector<vector<int>> mat(10); //matrice con 10 righe e 0 colonne di vettori tutti vuoti
vector<vector<float>> mat(10, vector<float>(5, -2)); //matrice 10x5 con tutti gli elementi inizializzati a -2
mat[2][3] = 5; //assegna 5 alla riga 2 e colonna 3 della matrice
```
## ESERCITAZIONE 3
Sistemare il costruttore con due parametri, esponente default a 0 per fare la conversione di tipo di un float `p + 3.2`. 

Allo stesso modo deve funzionare `3.2 + p` tramite l'operatore somma. USARE IL SUO DRIVER PER I TEST

## Esercizio Compitino 2020-2021
```cpp
class B
{
    public:
        B(int n) { num = n; }
        void set(int n) { num = n; }
        int Get() const { return num; }
    private:
        int num;
};
//*p.campo = p->campo
class A
{
    public:
        A(int v = 0) { p1 = new B(v); p2 = p1;}
        void Set1(int v) { p1 -> set(v); }
        void Set2(int v) { p2 -> set(v); }
        int Get1() const {return p1->Get(); } //restituisce un intero (fanno get del oggetto attaccato a p1 (un oggetto di tipo B))
        int Get2() const {return p2->Get(); }
        //passo da un oggetto condiviso a due oggetti con lo stesso valore
        void Flip()
        {
            if (p1 == p2)
                p2 = new B(p1->Get());
            else
            {
                delete p2;
                p2 = p1;
            }
        }
    //i due pointer puntano allo stesso oggetto o a oggetti distinti ma uguali
    private:
        B* p1;
        B* p2;
};

int main()
{
    A a1(5);
    a1.Flip();
    a1.Set1(6);
    A a2 = a1;
    a2.Set1(4);
    cout << a1.Get1() << '/' << a2.Get1() << endl;
    return 0;
}

//riga 1:
//un solo oggetto B con valore 5 puntato da entrambi
//riga 2:
//due oggetti B distinti con valore 5
//riga 3:
//a1 ha p1 che punta a B(6) e p2 che punta a B(5)
//riga 4:
//a2 ha p1 e p2 che puntano a B(6) e B(5) (gli stessi di a1)
//riga 5:
//a2 ha p1 che punta a B(4) e p2 che punta a B(5) (gli stessi di a1)
// stampa 4/5

//se non ci fosse stata interferenza avrebbe stampato 6/5
```

Scrivere il costruttore di copia e l'operatore di assegnazione per la classe A in modo che non ci sia interferenza tra oggetti distinti e infine, scrivere il distruttore per evitare memory leak.
```cpp
//costruttore di copia
A::A(const A& a)
{
    p1 = new B(*(a.p1)); //creo un nuovo oggetto B con il valore di a.p1 tramite costruttore di copia

    //analogo:
    //p1 = new B(a.p1->Get()); //chiamo il costruttore normale

    if(a.p1 == a.p2) //se i due puntatori puntano allo stesso oggetto
        p2 = p1; //p2 punta allo stesso oggetto di p1
    else
        p2 = new B(*(a.p2)); //creo un nuovo oggetto B con il valore di a.p2

        //analogo:
        //p2 = new B(a.p2->Get());
}
```
```cpp
A& A::operator=(const A& a)
{
    *p1 = *(a.p1);  // copia l'oggetto puntato da p1 
    // (non è necessario deallocarlo e riallocarlo)
    if (a.p1 == a.p2)
    {
        if (p1 != p2)
        {
            delete p2;
            p2 = p1;
        }
        // else: nessuna azione 
    }
    else
        if (p1 == p2)
        p2 = new B(*(a.p2)); 
        else
        *p2 = *(a.p2);
    return *this;
} 
```

Non si può fare la delete di un oggetto due volte, il compilatore segnala errore se si tenta di farlo. 

Uno può eliminare il costruttore di copia e l'operatore di assegnazione se non si vuole permettere la copia degli oggetti della classe A. 

`A(const A& a) = delete;` e `A& operator=(const A& a) = delete;`

Non si può chiamare il costruttore di copia o l'operatore di assegnazione in quanto sono stati eliminati.

