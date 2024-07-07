#ifndef MATERIALUSADO
#define MATERIALUSADO
#include "material.hpp"

class MaterialUsado {
    private:
        Material _m;
        float _volumenUsado;


    public:
    MaterialUsado(Material m, float volumenUsado)
    {
    	_m = m;
        setVolumenUsado(volumenUsado);
    };

    float getVolumenUsado() const
    {
    	return _volumenUsado;
    };

    Material getMaterial() const
    {
        return _m;
    }

    void setVolumenUsado(float volumenUsado)
    {
    	_volumenUsado = volumenUsado;
    };

    void setMaterial(Material m)
    {
        _m = m;
    }

};

#endif