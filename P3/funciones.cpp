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