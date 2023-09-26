#include "productoMatricesCuadradas.hpp"
#include "ClaseTiempo.hpp"
#include "sistemaEcuaciones.hpp"
#include <iostream>
#include <vector>
#include <fstream> 
#include <math.h>  

/*********************/
/* Funcion Principal */
/*********************/

void productoMatricesCuadradas()
{
    int minimo, maximo, incremento;
    double valor=1;

    std::cout<<"Introduzca el maximo: "<< std::endl;
    std::cin>>maximo;

    std::cout<<"Introduzca el minimo: "<< std::endl;
    std::cin>>minimo;

    std::cout<<"Introduzca el incremento: "<< std::endl;
    std::cin>>incremento;


    std::vector<double> tiemposReales;
    std::vector<double> ordenMatriz;

    std::vector<std::vector<double>> matriz(3,std::vector<double>(3) );

    tiemposProductoMatrices( minimo, maximo, tiemposReales, ordenMatriz);

    std::ofstream fichero1("tiempoRealesMatriz.txt");

    if (!fichero1.is_open())
    {
        std::cout << "Error abriendo el fichero." << std::endl;
        exit(EXIT_FAILURE);
    }

    for(long unsigned int i =0;i< tiemposReales.size();i++)
        fichero1 << ordenMatriz[i] << " " << tiemposReales[i] << std::endl;
    

    fichero1.close();
    

    std::vector<double> a(4);

    ajusteCubicoMatrices( ordenMatriz, tiemposReales, a);

    std::vector<double> tiemposEstimados(ordenMatriz.size());

    calcularTiemposEstimadosPolinomicoMatrices(ordenMatriz, tiemposReales, a, tiemposEstimados);

    std::ofstream fichero2("datosFinalesM.txt");

    if (!fichero2.is_open())
    {
        std::cout << "Error abriendo el fichero." << std::endl;
        exit(EXIT_FAILURE);
    }

    for(long unsigned int i =0;i< tiemposReales.size();i++)
        fichero2 << ordenMatriz[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << std::endl;
    
    fichero2.close();
        

    std::cout << "t(n) = " << a[0] <<" + " << a[1] << " * n + " << a[2] << " * n^2 + " << a[3] << " * n^3 "<<std::endl;

    std::cout << "Coeficiente de determinación: " << calcularCoeficienteDeterminacionMatrices(tiemposReales,tiemposEstimados) << std::endl;
    
    int opcion = 0;

    std::cout << "¿Quieres hacer una estimación de tiempos para un determinado orden?" << std::endl;
    std::cout << "1. Sí. \t2. No." <<std::endl;
    std::cout << "Introduzca su respuesta: ";
    std::cin >> opcion;

    while(opcion == 1 && valor != 0)
    {
        std::cout << "Introduzca el tamaño, introduzca 0 para salir: "<<std::endl;
        std::cin >> valor;

        if(valor != 0)
        {
            std::cout <<" El tiempo estimado que tardaría con un ejemplar de " << valor << " elementos sería: " << calcularTiempoEstimadoPolinomicoMatrices(valor, a) << std::endl;
        }
    }

}

/************************/
/* Funciones auxiliares */
/************************/

/* Función ejercicio 2.1
*
* Función que rellena la matriz aleatoriamente
* con valores entre 0.95 y 1.05
*/
void rellenarMatriz( std::vector<std::vector<double>> &matriz ){
    
    for( long unsigned int i=0; i<matriz.size(); i++)
        for( long unsigned int j=0; j<matriz[i].size(); j++)
        {
            matriz[i][j] = ((( rand()%11)+95)/100) ;
        }
}

/*
*
*
*
*/
void ProductoMatrices( std::vector<std::vector<double>> &matrizA, std::vector<std::vector<double>> &matrizB, std::vector<std::vector<double>> &matrizResultado)
{
    int ordenM = matrizA.size();

    for(int i=0; i<ordenM; i++)
        for(int j=0; j<ordenM; j++)
            for(int k=0; k<ordenM; k++)
            {
                matrizResultado[i][j] += matrizA[i][k] * matrizB[k][j];
            }
}


void tiemposProductoMatrices( int minimo, int maximo, std::vector<double> &tiemposReales, std::vector<double> &ordenMatriz)
{
    for(int i=minimo; i<maximo+1;i++)
    {
        std::vector<std::vector<double>> matrizA(i, std::vector<double>(i));
        std::vector<std::vector<double>> matrizB(i, std::vector<double>(i));
        std::vector<std::vector<double>> matrizResultado(i, std::vector<double>(i));

        Clock reloj;

        rellenarMatriz( matrizA );
        rellenarMatriz( matrizB );
        ordenMatriz.push_back(i);

        reloj.start();
        ProductoMatrices( matrizA, matrizB, matrizResultado);
        
        if (reloj.isStarted())
        {
            reloj.stop();
            double tiempo = reloj.elapsed();
            tiemposReales.push_back(tiempo);

            std::cout << "Orden de la matriz: " << i << ", Tiempo de ejecución: " << tiempo << std::endl;
        }
    }
}

double sumatorioMatrices( const std::vector<double> &n, const std::vector<double> &t, int expN, int expT)
{
    double sumatorio=0;

    for( long unsigned int i = 0; i< n.size(); i++)
        sumatorio += pow(n[i],expN)*pow(t[i],expT);
    
    return sumatorio;
}

void ajusteCubicoMatrices(const std::vector<double> &ordenMatriz, const std::vector<double> &tiemposReales, std::vector <double> &a)
{
    std::vector < std::vector < double > > matrizA(a.size(), std::vector< double >( a.size() ));
    std::vector < std::vector < double > > matrizB(a.size(), std::vector< double >( 1 ));

    std::vector < std::vector < double > > matrizResultado(a.size(), std::vector< double >( 1 ));// Creando matriz Nx1


    for( long unsigned int i = 0; i < a.size(); i++)
    {
        for( long unsigned int j = 0; j < a.size(); j++)
        {
            matrizA[i][j]=sumatorioMatrices( ordenMatriz, ordenMatriz, j, i);
        }
        
        matrizB[i][0]=sumatorioMatrices( ordenMatriz, tiemposReales, i, 1);
    }

        
        resolverSistemaEcuaciones( matrizA, matrizB, a.size(), matrizResultado);

        for( long unsigned int i= 0; i< matrizResultado.size(); i++ )
            a[i] = matrizResultado[i][0];
        
}

void calcularTiemposEstimadosPolinomicoMatrices(const std::vector <double> &ordenMatriz, std::vector <double> &tiemposReales, const std::vector <double> &a, std::vector <double> &tiemposEstimados)
{
    for(long unsigned int i=0;i<ordenMatriz.size();i++)
        tiemposEstimados[i]=a[0]+a[1]*ordenMatriz[i]+a[2]*pow(ordenMatriz[i],2)+a[3]*pow(ordenMatriz[i],3);

}

double calcMediaMatrices(const std::vector <double> &vector)
{
    double sumatorio=0;

    for(long unsigned int i = 0; i<vector.size();i++)
        sumatorio += vector[i];
    
    return sumatorio/vector.size();
}

double calcVarianzaMatrices(const std::vector <double> &vector, double media)
{
    double total=0;

    for(long unsigned int i = 0; i<vector.size();i++)
        total += pow(vector[i]-media,2);

    return total/vector.size();
}


double calcularCoeficienteDeterminacionMatrices(const std::vector <double> &tiemposReales, const std::vector <double> &tiemposEstimados)
{
    double mediaTReales, mediaTEstimados, varianzaReales, varianzaEstimados;

    
    mediaTReales=calcMediaMatrices(tiemposReales);
    mediaTEstimados=calcMediaMatrices(tiemposEstimados);


    varianzaReales=calcVarianzaMatrices(tiemposReales,mediaTReales);
    varianzaEstimados=calcVarianzaMatrices(tiemposEstimados,mediaTEstimados);

    return varianzaEstimados/varianzaReales;
}

double calcularTiempoEstimadoPolinomicoMatrices(const double &n, std::vector <double> &a)
{
    return a[0] + a[1] * n + a[2] * pow(n,2);
}