#ifndef PROBLEMA_DE_LA_MOCHILA
#define PROBLEMA_DE_LA_MOCHILA

#include <vector>
#include "materialUsado.hpp"

void problemaDeLaMochila();

void cargarMateriales(std::vector<Material> &materiales, const char *nombreFichero);
void mochila(float volumenMochila, std::vector<Material> &materiales, std::vector<std::vector <double>>& matrizEstados);
void obtenerSolucion(std::vector<std::vector <double>>& matrizEstados, std::vector<Material> &materiales, std::vector<MaterialUsado> &solucion);
void escribirSolucion(std::vector<MaterialUsado> &solucion);

#endif