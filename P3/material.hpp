#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{
    private:
        
        int etiqueta_;
        int volumen_;
        int precio_;

    public:
        
        Material(int etiqueta, int volumen, int precio)
        {
            etiqueta_ = etiqueta;
            volumen_ = volumen;
            precio_ = precio;
        }

        inline const int getEtiqueta()
        {
            return this->etiqueta_;
        }

        inline const int getVolumen()
        {
            return this->volumen_;
        }

        inline const int getPrecio()
        {
            return this->precio_;
        }

};

#endif