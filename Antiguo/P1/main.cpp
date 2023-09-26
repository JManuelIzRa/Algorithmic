#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "ejercicio1.h"
#include "ejercicio2.h"


using namespace std;

int main(int argc, char** argv)
{
    int option;

    srand(time(NULL));

    cout<<"-------------------"<<endl;
    cout<<"Elija una opcion:"<<endl;
    cout<<"1. Ordenar."<<endl;
    cout<<"2. Producto de matrices cuadradas."<<endl;
    cout<<"3. Salir."<<endl;
    cout<<"-------------------"<<endl;
    cin>>option;

    while(option<1 || option>3)
    {
        cout<<"Error. Seleccione una de las opciones:"<<endl;
        cout<<"Elija una opcion:"<<endl;
        cout<<"1. Ordenar"<<endl;
        cout<<"2. Producto de matrices cuadradas."<<endl;
        cout<<"3. Salir."<<endl;
        cin>>option;

    }

    switch(option)
    {
        case 1:
            ordenacionSeleccion();
            break;

        case 2:
            productoMatricesCuadradas();
            break;
        
        case 3:
            std::cout << "Ha elegido salir" << std::endl;
            break;
    }

    return 0;
}