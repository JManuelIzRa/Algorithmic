#ifndef CAMBIO_H
#define CAMBIO_H

class Cambio
{
    private:
        
        int valor_;//cts.
        int cantidad_;//cantidad de cada billete o moneda

    public:
        
        Cambio(const int valor)
        {
            valor_=valor;
        }

        inline void setCantidad(const int cantidad)
        {
            cantidad_=cantidad;
        }

        inline const int getCantidad()
        {
            return this->cantidad_;
        }
};


#endif