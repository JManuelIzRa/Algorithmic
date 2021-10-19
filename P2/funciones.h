#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>


void ordenacionQuickSort();
void ordenacionFusion();


void rellenarVector(std::vector<int> &v);

void quicksort(double izq, double der, double n, std::vector <int> &v);

bool estaOrdenado(const std::vector <int> &v);

void tiemposordenacionQuickSort(int nMin, int nMax, int repeticiones, std::vector <double> &tiemposReales, std::vector <double> &numeroElementos);
void tiemposordenacionFusion(int nMin, int nMax, int repeticiones, std::vector <double> &tiemposReales, std::vector <double> &numeroElementos);

void ajustePolinomico(const std::vector <double> &numeroElementos, const std::vector <double> &tiemposReales, std::vector <double> &a);

double sumatorio(const std::vector<double> &n, const std::vector <double> &t, int expN, int expT);

void calcularTiemposEstimadosPolinomico(const std::vector<double> &numeroElementos, const std::vector <double> &a, std::vector <double> &tiemposEstimados);

float calculoCoeficienteDeterminacion(const std::vector<double> tiemposEstimados, const std::vector<double> tiemposReales);

float media(const std::vector<double> v);
float varianza(const std::vector<double> v, float media);

double calcularTiempoEstimadoPolinomico(const double &n, std::vector <double> &a);

#endif