#include "funciones.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>//std::sort

bool sortFunction (Divisa i,Divisa j) { return (i.getValor() > j.getValor() ); }

void cargaDivisas(std::vector <Divisa> &divisas)
{
    std::string s;

    std::ifstream f("SistemaMonetario.txt");
    
    if ( f.is_open() ) 
    {
        do
        {
            getline( f, s );

            Divisa nueva_divisa(std::stoi(s));

            divisas.push_back(nueva_divisa);

        }while( !f.eof() );

        std::sort(divisas.begin(), divisas.end(), sortFunction);

    }
    else std::cerr << "Error de apertura del archivo." << std::endl;
}

void cambio(int n, std::vector <Divisa> C, std::vector <Cambio> resultado)
{
    int suma_parcial = 0;
    std::vector<Divisa>::iterator it_di = C.begin();

    Cambio nuevo_cambio(*it_di);

    resultado.push_back(nuevo_cambio);

    std::vector<Cambio>::iterator it_ca = resultado.begin();

    while( suma_parcial != n )
    {
        if( (it_di->getValor() + suma_parcial) <= n )
        {
            it_ca->setCantidad(it_ca->getCantidad()+1);
            suma_parcial += it_di->getValor();
        }
        else
        {
            it_di++;
            
            Cambio nuevo_cambio(*it_di);

            resultado.push_back(nuevo_cambio);

            it_ca++;
        }
    }
}

sino
devolver no encuentro solucion
finsi
finmientras
fin