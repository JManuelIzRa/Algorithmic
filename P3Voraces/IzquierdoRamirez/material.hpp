#ifndef MATERIAL
#define MATERIAL

class Material 
{
    private:
    int _etiqueta;
    float _volumen;
    float _precio;

    public:
    Material()
    {};
    Material(int etiqueta, float volumen, float precio)
    {
    	setEtiqueta(etiqueta);
    	setVol(volumen);
    	setPrecio(precio);
    };
    int getEtiqueta() const
    {
    	return _etiqueta;
    };
    int getVolumen() const
    {
    	return _volumen;
    };
    int getPrecio() const
    {
    	return _precio;
    };

    void setEtiqueta(int etiqueta)
    {
    	_etiqueta = etiqueta;
    };
    void setVol(float volumen)
    {
    	_volumen = volumen;
    };
    void setPrecio(float precio)
    {
    	_precio = precio;
    };

};

#endif
