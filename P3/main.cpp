#include <iostream>
#include <vector>
#include <algorithm>    // std::sort
#include "divisa.hpp"
#include "funciones.h"

int main()
{
    std::vector <Divisa> divisas;

    cargaDivisas(divisas);

    //FLAG Vector ordenado: correcto
    /*for(std::vector<Divisa>::iterator it=divisas.begin(); it!=divisas.end(); ++it)
    {
        std::cout << it->getValor() << "\tTipo: " << it->getTipo() << std::endl;
    }*/

    
}
