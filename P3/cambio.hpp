#ifndef CAMBIO_H
#define CAMBIO_H

#include "divisa.hpp"

class Cambio
{
    private:
        
        Divisa divisa_;//cts.
        int cantidad_;//cantidad de cada billete o moneda

    public:
        
        Cambio(int valor):divisa_(valor)
        {
            cantidad_=0;
        }

        inline void setCantidad(const int cantidad)
        {
            cantidad_=cantidad;
        }

        inline const int getCantidad()
        {
            return this->cantidad_;
        }

        inline Divisa getDivisa()
        {
            return this->divisa_;
        }
};


#endif