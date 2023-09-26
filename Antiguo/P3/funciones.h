#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include "divisa.hpp"
#include "cambio.hpp"
#include "material.hpp"
#include "mochila.hpp"

void cargaDivisas(std::vector <Divisa> &divisas);
bool sortFunctionDivisa (Divisa i,Divisa j);
void algoritmoCambio(double n, std::vector <Divisa> C, std::vector <Cambio> &resultado);
void cargaMateriales(std::vector <Material> &materiales);
bool sortFunctionMaterial (Material i,Material j);
Mochila algoritmoMochila(std::vector <Material> C, int volumen);


#endif