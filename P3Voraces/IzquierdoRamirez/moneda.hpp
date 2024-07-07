#ifndef MONEDA
#define MONEDA

class Moneda
{
    private:
        int _valor;
        
    public:
        Moneda()
        {
        };
        Moneda(int n)
        {
            setValor(n);
        };
        int getValor() const
        {
            return _valor;
        };
        void setValor(int n)
        {
            _valor = n;
        };
};


#endif
