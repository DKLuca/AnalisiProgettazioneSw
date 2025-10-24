#include <iostream>
using namespace std;

void Piramide(int);

int main()
{
    int n = 0;
    do
    {
        cout << "Inserire un numero per stampare la piramide ";
        cin >> n;
    }while(n < 1 || n > 9);
    Piramide(n);
}

void Piramide(int n)
{

    for(int j = 0; j < n; j++)
    {
        for(int i = 0; i < n - j ; i++)
            cout << " ";
        for(int k = 0; k < j + 1; k++)
            cout << k + 1;
        for(int k = j; k > 0; k--)
            cout << k;
        cout << endl;
    }
}