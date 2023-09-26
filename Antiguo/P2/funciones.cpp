#include "funciones.h"
#include "sistemaEcuaciones.hpp"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>




void rellenarVector(std::vector<int> &v)
{
    for(long unsigned int i=0; i < v.size(); i++)
    {
        v[i] = rand()%10000000;
    }
}

bool estaOrdenado(const std::vector <int> &v)
{
    for(long unsigned int i=0; i<v.size(); i++)
    {
        if(v[i]>v[i+1])
        {
            return false;
        }
    }

    return true;
}

void ajustePolinomico(const std::vector <double> &numeroElementos, const std::vector <double> &tiemposReales, std::vector <double> &a)
{
    //Declaracion de la matriz
    std::vector < std::vector < double > > matrizA;
    matrizA = vector< vector< double > > (a.size(), std::vector< double > (a.size()) );

    std::vector < std::vector < double > > matrizB;
    matrizB = std::vector< std::vector< double > > (a.size(), std::vector< double > (1) );

    for(double i = 0; i<a.size(); i++)
    {
        for(double j = 0; j<a.size(); j++)
        {
            matrizA[i][j] = sumatorio(numeroElementos, numeroElementos, j, i);
            //std::cout<< matrizA[i][j] << "\t\t\t";
        }

        matrizB[i][0] = sumatorio(numeroElementos, tiemposReales, i, 1);
        //std::cout<< matrizB[i][0] << std::endl;
    }

    std::vector < std::vector < double > > matrizResultado;
    matrizResultado = std::vector< std::vector< double > > (a.size(), std::vector< double > (1) );

    resolverSistemaEcuaciones(matrizA, matrizB, a.size(), matrizResultado);

    for(long unsigned int i = 0; i<a.size(); i++)
    {
        //std::cout << "a[" << i << "]: " << matrizResultado[i][0] << std::endl;
        a[i] = matrizResultado[i][0];
    }

}

double sumatorio(const std::vector<double> &n, const std::vector <double> &t, int expN, int expT)
{
    double total=0;

    for(double i = 0; i<n.size(); i++)
    {
        total += pow(n[i], expN) * pow(t[i], expT);
    }

    return total;
}

void calcularTiemposEstimadosPolinomico(const std::vector<double> &numeroElementos, const std::vector <double> &a, std::vector <double> &tiemposEstimados)
{
    double z = 0;
    for(long unsigned int i = 0; i<numeroElementos.size() ; i++)
    {
        tiemposEstimados[i] = a[0] + a[1]*numeroElementos[i];
    }
}

float calculoCoeficienteDeterminacion(const std::vector<double> tiemposEstimados, const std::vector<double> tiemposReales)
{
    float mediaTEstimados = 0.0;
    float mediaTReales = 0.0;

    float varianzaTEstimados = 0.0;
    float varianzaTReales = 0.0;

    mediaTEstimados = media(tiemposEstimados);
    //std::cout <<"MediaTEstimados" << mediaTEstimados << std::endl;

    mediaTReales = media(tiemposReales);    
    //std::cout <<"MediaTReales" << mediaTReales << std::endl;

    varianzaTEstimados = varianza(tiemposEstimados, mediaTEstimados);
    //std::cout <<"varianzaTEstimados " << varianzaTEstimados << std::endl;
    varianzaTReales = varianza(tiemposReales, mediaTReales);
    //std::cout <<"varianzaTReales " << varianzaTReales << std::endl;
    
    return varianzaTEstimados/varianzaTReales;

}

float media(const std::vector<double> v)
{
    float sumatorio = 0;
    float media = 0;

    for(long unsigned int i = 0; i<v.size(); i++)
    {
        sumatorio += v[i];
    }

    media = sumatorio/v.size();

    return media;
}

float varianza(const std::vector<double> v, float media)
{
    float sumatorio = 0;

    for(long unsigned int i = 0; i<v.size(); i++)
    {
        sumatorio +=  pow(v[i] - media,2);
    }

    return sumatorio/v.size();
}


double calcularTiempoEstimadoPolinomico(const double &n, vector <double> &a)
{
    double estimacion = 0;

    estimacion = a[0] + a[1]*n;

    estimacion = estimacion/(8.64*pow(10,10));

    return estimacion;
}
