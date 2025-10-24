#include <iostream>
using namespace std;

bool NumeriPrimi(int);

int main()
{
    int n = 0;
    do
    {
        cout << "Inserire il numero per vedere se è primo: ";
        cin >> n;
    }while(n <= 0);
    
    if(NumeriPrimi(n))
        cout << "Il numero è primo";
    else
        cout << "Il numero non è primo";
}

bool NumeriPrimi(int n)
{
    bool primo = true;
    int i = 2;

    if(n<2)
        return false;
    else if(n == 2)
        return true;
    while(i < n/2 && primo)
    {
        if(n % i == 0)
            primo = false;
        i++;
    }
    return primo;
}