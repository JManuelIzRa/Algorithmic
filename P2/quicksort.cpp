#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

#include "quicksort.h"
#include "ClaseTiempo.hpp"
#include "funciones.h"

void ordenacionQuickSort()
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
        tiemposordenacionQuickSort(i, maximo, repeticiones, tiemposReales, numeroElementos);
        //std::cout<<"i: "<< i<< std::endl;
    }

    std::ofstream fichero1("tiempoRealesQuicksort.txt");

    if(!fichero1.is_open())
    {
        std::cout << "Error abriendo el fichero"<<std::endl;
        exit(EXIT_FAILURE);
    } 


    for(long unsigned int i = 0; i < tiemposReales.size(); i++)
    {
        fichero1 << tiemposReales[i] << " " << numeroElementos[i] << std::endl;
    }       
    

    fichero1.close();

    std::vector<double> a(2);

    ajustePolinomico(numeroElementos, tiemposReales, a);

    /*for(int i = 0; i<a.size(); i++)
    {
        std::cout << a[i] << std::endl;
    }*/

    std::vector <double> tiemposEstimados(numeroElementos.size());

    calcularTiemposEstimadosPolinomico(numeroElementos, a, tiemposEstimados);

    std::ofstream fichero2("datosFinalesQuicksort.txt");

    if(!fichero2.is_open())
    {
        std::cout << "Error abriendo el fichero"<<std::endl;
        exit(EXIT_FAILURE);
    } 

    std::cout << "Ecuacion de la curva: "<< std::endl;
    std::cout << "t(n) = " << a[0] << " + " << a[1] << " * nlog(n)" << std::endl; 

    for(long unsigned int i = 0; i < tiemposEstimados.size(); i++)
    {
        fichero2 << numeroElementos[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << std::endl;
    }       
    
    float coeficienteDeterminacion;

    coeficienteDeterminacion = calculoCoeficienteDeterminacion(tiemposEstimados, tiemposReales);

    std::cout << coeficienteDeterminacion << std::endl;

    fichero2.close();

    int eleccion = 0;
    double tamanioMuestra;
    double tiempo;
    
    while(eleccion<1 || eleccion>2)
    {
        std::cout<<"¿Desea calcular el tiempo para un tamaño en concreto?"<< std::endl;
        std::cout<<"1. Sí\t2.No"<<std::endl;
        std::cin>>eleccion;
    }

    while( tamanioMuestra!=0 && eleccion!=2)
    {
        std::cout << "Introduzca el tamaño de la muestra, 0 para salir: "<< std::endl;
        std::cin >> tamanioMuestra;

        if(tamanioMuestra!=0)
        {
            tiempo = calcularTiempoEstimadoPolinomico(tamanioMuestra, a);

            std::cout << "La estimacion es de " << tiempo << "dias." << std::endl;
        }
    }

}

void quicksort(double izq, double der, double n, std::vector <int> &v)
{
    
    int i = izq;
    int j = der;

    int x = v[ round( (izq+der)/2 ) ];

    do
    {
        while ( v[i] < x )
        {
            ++i;
        }
        
        while ( v[j] > x )
        {
            --j;
        }

        if( i<=j )
        {
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            /*std::cout << "v["<< j << "]: " << v[j] << std::endl;
            std::cout << "v["<< i << "]: " << v[i] << std::endl;*/

            ++i;
            --j;
        }

    } while (i <= j);
    
        
    if(izq < j)
    {
        quicksort(izq, j, n, v);
    }
    
    if(i < der )
    {
        quicksort(i, der, n, v);
    }
}

void tiemposordenacionQuickSort(int nMin, int nMax, int repeticiones, std::vector <double> &tiemposReales, std::vector <double> &numeroElementos)
{
    Clock time;
    int t = 0;
    std::vector <int> v(nMin);
    
    for(int i=0; i<repeticiones; i++)
    {
        numeroElementos.push_back(nMin);

        rellenarVector(v);

        time.start();

        if(time.isStarted())
        {
            //En la primera llamada izq = 1; der = n
            quicksort(1, nMin, nMin, v);

            time.stop();
            
            estaOrdenado(v);

            //std::cout<<time.elapsed()<<std::endl;
            t = time.elapsed();
            tiemposReales.push_back(log(t) + t);

        }
        
    }

}