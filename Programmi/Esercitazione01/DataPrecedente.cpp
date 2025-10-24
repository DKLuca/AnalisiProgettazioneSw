#include <iostream>
using namespace std;

bool DataValida(unsigned, unsigned, unsigned);
unsigned GiorniDelMese(unsigned,unsigned);
bool Bisestile(unsigned a);
void DataPrecedente(unsigned &g, unsigned &m, unsigned &a);

int main()
{
    unsigned g, m, a;
    do
    {
        cout << "Inserire giorno, mese, anno: ";
        cin >> g >> m >> a;
    } while (!DataValida(g, m, a));
    DataPrecedente(g, m , a);
    cout << g << "/" << m << "/" << a;
    
}
bool DataValida(unsigned g, unsigned m, unsigned a)
{
    return ((a >= 1) && (m >= 1 && m <= 12) && (g >= 1 && g <= GiorniDelMese(m, a)));
}
unsigned GiorniDelMese(unsigned m,unsigned a)
{
    if(m == 1 || m == 4 || m == 6 || m == 9)
        return 30;
    else if(m == 2)
        if(Bisestile(a))
            return 29;
        else
            return 28;
    else
        return 31;
}
bool Bisestile(unsigned a)
{
    if(a % 4 != 0)
        return false;
    else if(a % 100 != 0)
        return true;
    else if(a % 400 != 0)
        return false;
    else
        return true;
}
void DataPrecedente(unsigned &g, unsigned &m, unsigned &a)
{
    if(g > 1)
        g--;
    else
    {
        if(m > 1)
        {
            m--;
            g = GiorniDelMese(m, a);
        }
        else
        {
            a--;
            m = 12;
            g = 31;
        }
    }
}