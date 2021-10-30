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
            std::getline( f, s );

            Divisa nueva_divisa(std::stoi(s));

            divisas.push_back(nueva_divisa);

        }while( !f.eof() );

        std::sort(divisas.begin(), divisas.end(), sortFunction);

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