#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

#include "fusion.h"
#include "quicksort.h"
#include "ClaseTiempo.hpp"
#include "funciones.h"


void ordenarFusion(std::vector<int> &v)
{
    if( v.size() < 10 )
        quicksort(1, v.size(), v.size(), v);
    else
    {
        std::vector<int> primero(v.size()/2);
        std::vector<int> segundo(v.size()-v.size()/2);

        for( long unsigned int i=0; i < v.size()/2; ++i )
            primero[i] = v[i];
        
        for( long unsigned int i = v.size()/2; i < v.size(); ++i )
            segundo[i - v.size()/2] = v[i];

        ordenarFusion(primero);
        ordenarFusion(segundo);

        fusionar(primero , segundo, v);
    }
}

void fusionar(std::vector<int> primero, std::vector<int> segundo, std::vector<int> &v)
{
    for( long unsigned int i=0; i < v.size()/2; ++i )
        v[i] = primero[i];
        
    for( long unsigned int i = v.size()/2; i < v.size(); ++i )
        v[i] = segundo[i - v.size()/2];
}

void ordenacionFusion()
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
        tiemposordenacionFusion(i, maximo, repeticiones, tiemposReales, numeroElementos);
        //std::cout<<"i: "<< i<< std::endl;
    }

    std::ofstream fichero1("tiempoRealesFusion.txt");

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

    std::ofstream fichero2("datosFinalesFusion.txt");

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
        std::cout<<"¿Desea calcular el tiempo para un tamaño en concreto?"<<std::endl;
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

void tiemposordenacionFusion(int nMin, int nMax, int repeticiones, std::vector <double> &tiemposReales, std::vector <double> &numeroElementos)
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