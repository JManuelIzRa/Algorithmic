#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include "divisa.hpp"
#include "cambio.hpp"

void cargaDivisas(std::vector <Divisa> &divisas);
bool sortFunction (Divisa i,Divisa j);
void cambio(int n, std::vector <Divisa> C, std::vector <Cambio> resultado)


#endif