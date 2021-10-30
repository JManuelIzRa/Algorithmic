#include <iostream>
#include <vector>
#include <algorithm>    // std::sort
#include "divisa.hpp"
#include "funciones.h"

int main()
{
    std::vector <Divisa> divisas;
    std::vector <Cambio> resultado;

    double cantidad_problema = 0;

    cargaDivisas(divisas);

    //FLAG Vector ordenado: correcto
    /*for(std::vector<Divisa>::iterator it=divisas.begin(); it!=divisas.end(); ++it)
    {
        std::cout << it->getValor() << "\tTipo: " << it->getTipo() << std::endl;
    }*/

    std::cout << "Introduzca la cantidad a cambiar: \n";
    std::cin >> cantidad_problema;
    
    algoritmoCambio(cantidad_problema, divisas, resultado);

    for(std::vector<Cambio>::iterator it=resultado.begin(); it!=resultado.end(); ++it)
    {
        std::cout << "\nValor: " << it->getCantidad() << "\tTipo: " << (it->getDivisa()).getValor() << std::endl;
    }

    return 0;
}
