#include "funciones.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>//std::sort

bool sortFunctionDivisa (Divisa i,Divisa j) { return (i.getValor() > j.getValor() ); }
bool sortFunctionMaterial (Material i,Material j) { return (i.getPrecio() > j.getPrecio() ); }


void cargaDivisas(std::vector <Divisa> &divisas)
{
    std::string s;

    std::ifstream f("sistemamonetario.txt");
    
    if ( f.is_open() ) 
    {
        do
        {
            std::getline( f, s );

            Divisa nueva_divisa(std::stoi(s));

            divisas.push_back(nueva_divisa);

        }while( !f.eof() );

        std::sort(divisas.begin(), divisas.end(), sortFunctionDivisa);

    }
    else std::cerr << "Error de apertura del archivo." << std::endl;
}

void algoritmoCambio(double n, std::vector <Divisa> C, std::vector <Cambio> &resultado)
{
    double suma_parcial = 0;

    for(std::vector<Divisa>::iterator it=C.begin(); it!=C.end(); ++it)
    {
        Cambio nuevo_cambio(it->getValor());
        resultado.push_back(nuevo_cambio);
    }
    
    std::vector<Cambio>::iterator it_ca = resultado.begin();

    while( suma_parcial != n )
    {
        if( ((it_ca->getDivisa()).getValor() + suma_parcial) <= n )
        {
            it_ca->setCantidad(it_ca->getCantidad()+1);
            suma_parcial += (it_ca->getDivisa()).getValor();                    
        }
        else
        {
            if( (it_ca+1) != resultado.end() )
            {
                it_ca++;
            }
            
            
        }
    }
}


void cargaMateriales(std::vector <Material> &materiales)
{
    std::string s;

    int etiqueta;
    int volumen;
    int precio;

    FILE* f;
    f = fopen("materialesmochila.txt","rt");
    
    if ( f!=NULL ) 
    {
        while(fscanf(f, "%d %d %d", &etiqueta, &volumen, &precio)==3)
        {
            Material nuevo_material(etiqueta, volumen, precio);

            materiales.push_back(nuevo_material);

        }

        std::sort(materiales.begin(), materiales.end(), sortFunctionMaterial);

    }
    else std::cerr << "Error de apertura del archivo." << std::endl;
}

Mochila algoritmoMochila(std::vector <Material> C, int volumen)
{
    Mochila mochila(volumen);

    double volumen_parcial = 0;

    int dividir_volumen_material = 0;
    int precio_parcial = 0;
    Material m_dividido;
    int precioNuevo = 0;
    
    std::vector<Material>::iterator it_ma = C.begin();

    while( volumen_parcial != volumen && it_ma!=C.end())
    {
        if( ((it_ma->getVolumen()) + volumen_parcial) <= volumen )
        {
            mochila.setMaterial(it_ma->getMaterial());
            mochila.setPrecioParcial(it_ma->getPrecio());
            volumen_parcial += it_ma->getVolumen();    
        }
        else
        {
            dividir_volumen_material = mochila.getVolumen() - volumen_parcial;

            m_dividido = it_ma->getMaterial();
            m_dividido.setVolumen(dividir_volumen_material);
            
            precioNuevo = (dividir_volumen_material*it_ma->getPrecio())/it_ma->getVolumen();
            m_dividido.setPrecio( precioNuevo );
            m_dividido.setParcial("Si");
            
            mochila.setMaterial(m_dividido); 
            mochila.setPrecioParcial(precioNuevo); 

            volumen_parcial += dividir_volumen_material;                      
            
        }

         //if( (it_ma+1) != C.end() )
         //{
                it_ma++;
         //}
        
    }

    return mochila;
}