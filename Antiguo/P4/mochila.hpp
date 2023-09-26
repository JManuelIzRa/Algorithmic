#ifndef _MOCHILA_H
#define _MOCHILA_H

#include "material.hpp"
#include <vector>

class Mochila
{
    private:
        int volumen_;
        int precioTotal_;
        std::vector<Material> materiales_;

    public:

        Mochila(){}
        
        Mochila(int volumen)
        {
            volumen_ = volumen;
            precioTotal_ = 0;
        }

        inline const int getVolumen()
        {
            return this->volumen_;
        }

        inline const int getPrecioTotal()
        {
            return this->precioTotal_;
        }

        inline void setPrecioParcial(int precio)
        {
            precioTotal_ += precio;
        }

        void setMaterial(Material material)
        {
            materiales_.push_back(material);
        }

        inline const std::vector<Material> getContenido()
        {
            return materiales_;
        }
};


#endif