#ifndef EJERCICIO2_H
#define EJERCICIO2_H

#include <vector>

void productoMatricesCuadradas();

void rellenarMatriz( std::vector<std::vector<double>> &matriz );

void ProductoMatrices( std::vector<std::vector<double>> &matrizA, std::vector<std::vector<double>> &matrizB, std::vector<std::vector<double>> &matrizResultado);

void tiemposProductoMatrices( int minimo, int maximo, std::vector<double> &tiemposReales, std::vector<double> &ordenMatriz);

double sumatorioMatrices( const std::vector<double> &n, const std::vector<double> &t, int expN, int expT);

void ajusteCubicoMatrices(const std::vector<double> &ordenMatriz, const std::vector<double> &tiemposReales, std::vector <double> &a);
void calcularTiemposEstimadosPolinomicoMatrices(const std::vector <double> &ordenMatriz, std::vector <double> &tiemposReales, const std::vector <double> &a, std::vector <double> &tiemposEstimados);

double calcMediaMatrices(const std::vector <double> &vector);

double calcVarianzaMatrices(const std::vector <double> &vector, double media);

double calcularCoeficienteDeterminacionMatrices(const std::vector <double> &tiemposReales, const std::vector <double> &tiemposEstimados);
double calcularTiempoEstimadoPolinomicoMatrices(const double &n, std::vector <double> &a);

#endif
