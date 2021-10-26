#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "funciones.h"
#include "quicksort.h"
#include "fusion.h"

using namespace std;

int main(int argc, char** argv)
{
    int option;

    srand(time(NULL));

    while(option != 3)
    {
        cout<<"-------------------"<<endl;
        cout<<"Elija una opcion:"<<endl;
        cout<<"1. Ordenar con quicksort."<<endl;
        cout<<"2. Ordenar por fusion."<<endl;
        cout<<"3. Salir."<<endl;
        cout<<"-------------------"<<endl;
        cin>>option;

        while(option<1 || option>3)
        {
            cout<<"Error. Seleccione una de las opciones:"<<endl;
            cout<<"Elija una opcion:"<<endl;
            cout<<"1. Ordenar con quicksort"<<endl;
            cout<<"2. Ordenar por fusion"<<endl;
            cout<<"3. Salir."<<endl;
            cin>>option;

        }

        switch(option)
        {
            case 1:
                ordenacionQuickSort();
                system("./generarGrafico.sh && xdg-open graficoComparativo.eps");
                break;

            case 2:
                ordenacionFusion();
                system("./generarGrafico.sh && xdg-open graficoComparativo.eps");
                break;
        
            case 3:
                std::cout << "Ha elegido salir" << std::endl;
                break;
        }
    }

    return 0;
}