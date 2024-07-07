#ifndef PROBLEMA_DEL_CAMBIO
#define PROBLEMA_DEL_CAMBIO

#include <vector>
#include "moneda.hpp"

// Función de medio nivel
void problemaDelCambio();

// Función encargada de cargar el Sistema Monetario
void cargarSistemaMonetario(std::vector <Moneda> &divisas, const char *nombre_fichero);


void cambio(double n, std::vector<Moneda> C, std::vector <std::vector <int>> &matrizEstados);

void obtenerSolucion( std::vector<std::vector <int>>& matrizEstados, std::vector <Moneda> &sistemaMonetario, std::vector<int> &solucion);

void escribirSolucion(std::vector<int> &solucion, std::vector <Moneda> &sistemaMonetario);

#endif