#ifndef _ALGORITMO_N_REINAS_
#define _ALGORITMO_N_REINAS_

#include <vector>

void nReinasBacktracking(int n, std::vector<std::vector <int>>&soluciones);
void nReinasBacktracking(int n, std::vector<int>&solucion);
bool nReinasLasVegas(int n, std::vector<int>& solucion);


void escribirSoluciones(std::vector<std::vector <int>>&soluciones);
void escribirSolucion(std::vector<int>&solucion);

void algoritmoNReinas(bool solUnica, bool lasVegas);

#endif