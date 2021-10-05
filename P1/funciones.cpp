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
        //std::cout<<"i: "<< i<< std::endl;
    }

    std::ofstream fichero1("tiempoReales.txt");

   
    for(long unsigned int i = 0; i < tiemposReales.size(); i++)
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

    for(long unsigned int i = 0; i < tiemposEstimados.size(); i++)
    {
        fichero2 << numeroElementos[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << std::endl;
    }       
    
    float coeficienteDeterminacion;

    coeficienteDeterminacion = calculoCoeficienteDeterminacion(tiemposEstimados, tiemposReales);

    std::cout << coeficienteDeterminacion << std::endl;

    fichero2.close();

    int eleccion = 0;
    int tamanioMuestra;
    double tiempo;
    
    while(eleccion!=2)
    {
        while(eleccion<1 || eleccion>2)
        {
            cout<<"¿Desea calcular el tiempo para un tamaño en concreto?"<<endl;
            cout<<"1. Sí\t2.No"<<endl;
            cin>>eleccion;
        }

        if(eleccion!=2)
        {
            cout << "Introduzca el tamaño de la muestra: "<< endl;
            cin >> tamanioMuestra;

            if(tamanioMuestra==0)
            {
                break;
            }

            tiempo = calcularTiempoEstimadoPolinomico(tamanioMuestra, a);

            cout << "La estimacion es de " << tiempo << endl;
        }
       
        eleccion = 0;
        
    }


}

void rellenarVector(std::vector<int> &v)
{
    for(long unsigned int i; i < v.size(); i++)
    {
        v[i] = rand()%10000000;
    }
}

bool seleccion(std::vector <int> &v)
{
    
    int posicionMenor;
    int aux;
    int resultado = false;

    for(long unsigned int i=1; i<(v.size())-1; i++)
    {
        posicionMenor = i;

        for(long unsigned int j=1; j<(v.size())-1; j++)
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
    for(long unsigned int i=0; i<v.size(); i++)
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
    std::vector <int> v(nMin);
    
    for(int i=0; i<repeticiones; i++)
    {
        numeroElementos.push_back(nMin);

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
    for(long unsigned int i = 0; i<numeroElementos.size() ; i++)
    {
        tiemposEstimados[i] = a[0] + a[1]*numeroElementos[i] + ( a[2]*pow(numeroElementos[i],2) );
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

    estimacion = a[0] + a[1]*n + ( a[2]*pow(n,2) );

    return estimacion;
}
