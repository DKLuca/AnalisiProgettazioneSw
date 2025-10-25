#ifndef CONTOCORRENTE_H
#define CONTOCORRENTE_H

class ContoCorrente 
{
    public:
        ContoCorrente();
        ContoCorrente(double tasso);
        double SaldoInEuro() const { return euro; }
        int SaldoCentesimi() const { return centesimi; }
        int TassoInteresse() const { return tassoInteresse; }
        double SaldoInLire() const;
        void FissaTassoInteresse(double tasso);
        void DepositaEuro(int e, int c);
        void PrelevaEuro(int e, int c);
        void AggiornaSaldo();
    
    private:
        int euro;
        int centesimi;
        double tassoInteresse;
};
#endif