#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>

void ordenacionQuickSort();
void quicksort(double izq, double der, double n, std::vector <int> &v);
void tiemposordenacionQuickSort(int nMin, int nMax, int repeticiones, std::vector <double> &tiemposReales, std::vector <double> &numeroElementos);

#endif