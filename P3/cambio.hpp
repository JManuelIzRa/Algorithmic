#ifndef CAMBIO_H
#define CAMBIO_H

#include "divisa.hpp"
class Cambio
{
    private:
        
        Divisa divisa_;//cts.
        int cantidad_;//cantidad de cada billete o moneda

    public:
        
        Cambio(const Divisa divisa):divisa_(divisa)
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
};


#endif