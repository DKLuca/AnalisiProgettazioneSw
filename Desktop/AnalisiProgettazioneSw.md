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