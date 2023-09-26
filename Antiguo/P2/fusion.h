#ifndef FUSION_H
#define FUSION_H

#include <vector>

void ordenacionFusion();
void ordenarFusion(std::vector<int> &v);
void tiemposordenacionFusion(int nMin, int nMax, int repeticiones, std::vector <double> &tiemposReales, std::vector <double> &numeroElementos);
void fusionar(std::vector<int> primero, std::vector<int> segundo, std::vector<int> &v);

#endif