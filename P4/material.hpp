#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
class Material
{
    private:
        
        int etiqueta_;
        int volumen_;
        int precio_;
        std::string parcial_;

    public:
        Material(){}
        Material(int etiqueta, int volumen, int precio)
        {
            etiqueta_ = etiqueta;
            volumen_ = volumen;
            precio_ = precio;
            parcial_ = "No";
        }

        inline const int getEtiqueta()
        {
            return this->etiqueta_;
        }

        inline const int getVolumen()
        {
            return this->volumen_;
        }

        inline void setVolumen(const int volumen)
        {
            volumen_=volumen;
        }

        inline const int getPrecio()
        {
            return this->precio_;
        }

        inline void setPrecio(const int precio)
        {
            precio_=precio;
        }

        Material getMaterial()
        {
            Material material(etiqueta_, volumen_, precio_);
            
            return material;
        }

        inline std::string getParcial()
        {
            return this->parcial_;
        }

        inline void setParcial(std::string parcial)
        {
            parcial_=parcial;
        }

};

#endif