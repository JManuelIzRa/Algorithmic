#include "funciones.h"
#include "ClaseTiempo.hpp"
#include "sistemaEcuaciones.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>

void ordenacionSeleccion()
{
    int maximo, minimo, incremento, repeticiones;

    std::cout<<"Introduzca el maximo: "<< std::endl;
    std::cin>>maximo;

    std::cout<<"Introduzca el minimo: "<< std::endl;
    std::cin>>minimo;

    std::cout<<"Introduzca el incremento: "<< std::endl;
    std::cin>>incremento;

    std::cout<<"Introduzca el numero de repeticiones: "<< std::endl;
    std::cin>>repeticiones;

    std::vector<double> tiemposReales;
    std::vector<double> numeroElementos;

    for(int i = minimo; i<=maximo; i=i+incremento)
    {
        tiemposOrdenacionSeleccion(i, maximo, repeticiones, tiemposReales, numeroElementos);
    }

    std::ofstream fichero1("tiempoReales.txt");

   
    for(int i = 0; i < tiemposReales.size(); i++)
    {
        fichero1 << tiemposReales[i] << " " << numeroElementos[i] << std::endl;
    }       
    

    fichero1.close();

    std::vector<double> a(3);

    ajustePolinomico(numeroElementos, tiemposReales, a);

    /*for(int i = 0; i<a.size(); i++)
    {
        std::cout << a[i] << std::endl;
    }*/

    std::vector <double> tiemposEstimados(numeroElementos.size());

    calcularTiemposEstimadosPolinomico(numeroElementos, a, tiemposEstimados);

    std::ofstream fichero2("datosFinales.txt");
    std::cout << "Ecuacion de la curva: "<< std::endl;
    std::cout << "t(n) = " << a[0] << " + " << a[1] << " * n + " << a[2] << " * (n^2)" << std::endl; 

    for(int i = 0; i < tiemposEstimados.size(); i++)
    {
        fichero2 << numeroElementos[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << std::endl;
    }       
    
    float coeficienteDeterminacion;

    coeficienteDeterminacion = calculoCoeficienteDeterminacion(tiemposEstimados, tiemposReales);

    std::cout << coeficienteDeterminacion << std::endl;

    fichero2.close();


}

void rellenarVector(std::vector<int> &v)
{
    

    for(int i; i < v.size(); i++)
    {
        v[i] = rand()%10000000;
    }
}

bool seleccion(std::vector <int> &v)
{
    
    int posicionMenor;
    int aux;
    int resultado = false;

    for(int i=1; i<(v.size())-1; i++)
    {
        posicionMenor = i;

        for(int j=1; j<(v.size())-1; j++)
        {
            if(v[j]<v[posicionMenor])
            {
                posicionMenor = j;
            }
        }

        aux = v[i];
        v[i] = v[posicionMenor];
        v[posicionMenor] = aux;

    }

    resultado = true;

    return resultado;
}

bool estaOrdenado(const std::vector <int> &v)
{
    for(int i=0; i<v.size(); i++)
    {
        if(v[i]>v[i+1])
        {
            return false;
        }
    }

    return true;
}

void tiemposOrdenacionSeleccion(int nMin, int nMax, int repeticiones, std::vector <double> &tiemposReales, std::vector <double> &numeroElementos)
{
    Clock time;
    
    for(int i=0; i<repeticiones; i++)
    {
        numeroElementos.push_back(nMin);

        std::vector <int> v(nMin);
        rellenarVector(v);

        time.start();

        if(time.isStarted())
        {
            seleccion(v);

            time.stop();
            
            estaOrdenado(v);

            //std::cout<<time.elapsed()<<std::endl;
            
            tiemposReales.push_back(time.elapsed());

        }
        
    }

  

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
            matrizA[i][j] = sumatorio(numeroElementos, numeroElementos, i, j);
            std::cout<< matrizA[i][j] << "\t\t\t";
        }

        matrizB[i][0] = sumatorio(numeroElementos, tiemposReales, i, 0);
         std::cout<< matrizB[i][0] << std::endl;
    }

    std::vector < std::vector < double > > matrizResultado;
    matrizResultado = std::vector< std::vector< double > > (a.size(), std::vector< double > (1) );

    resolverSistemaEcuaciones(matrizA, matrizB, 3, matrizResultado);

    for(int i = 0; i<a.size(); i++)
    {
        std::cout << "REsultado: " << matrizResultado[i][0];
        a[i] = matrizResultado[i][0];
    }

}

double sumatorio(const std::vector<double> &n, const std::vector <double> &t, int expN, int expT)
{
    double total=0;

    for(double i = 0; i<n.size(); i++)
    {
        total += pow(n[i], expN) + pow(t[i], expT);
    }

    return total;
}

void calcularTiemposEstimadosPolinomico(const std::vector<double> &numeroElementos, const std::vector <double> &a, std::vector <double> &tiemposEstimados)
{
    for(int i = 0; i<numeroElementos.size() ; i++)
    {
        tiemposEstimados[i] = a[0] + a[1]*numeroElementos[i] + ( a[2]*pow(numeroElementos[i],2) );
    }
}

float calculoCoeficienteDeterminacion(const std::vector<double> tiemposEstimados, const std::vector<double> tiemposReales)
{
    float mediaTEstimados = 0.0;
    float mediaTReales = 0.0;

    double sumatorio = 0;

    float sumatorioTEstimados = 0.0;
    float sumatorioTReales = 0.0;

    //Calculo media tiemposEstimados
    for(int i = 0; i<tiemposEstimados.size(); i++)
    {
        sumatorio += tiemposEstimados[i];
    }

    mediaTEstimados = sumatorio/tiemposEstimados.size();

    //Calculo media tiemposReales

    sumatorio = 0;

    for(int i = 0; i<tiemposReales.size(); i++)
    {
        sumatorio += tiemposReales[i];
    }

    mediaTReales = sumatorio/tiemposReales.size();

    //
    
    for(int i = 0; i<tiemposEstimados.size(); i++)
    {
        sumatorioTEstimados +=  pow(tiemposEstimados[i] - mediaTEstimados,2);
    }

    for(int i = 0; i<tiemposReales.size(); i++)
    {
        sumatorioTReales +=  pow(tiemposReales[i] - mediaTReales,2);
    }

    return sumatorioTEstimados/sumatorioTReales;

}