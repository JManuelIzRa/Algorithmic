#ifndef PROBLEMA_DE_LA_MOCHILA
#define PROBLEMA_DE_LA_MOCHILA

#include <vector>
#include "material.hpp"
#include "materialUsado.hpp"

void problemaDeLaMochila();

void cargarMateriales(std::vector<Material> &materiales, const char *nombreFichero);
void mochila(float   volumenMochila,   std::vector<Material>   &materiales,   std::vector<MaterialUsado> &solucion);
void escribirSolucion(std::vector<MaterialUsado> &solucion);

#endif