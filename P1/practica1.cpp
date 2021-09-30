#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "funciones.h"

using namespace std;

int main(int argc, char** argv)
{
    int option;

    srand(time(NULL));

    cout<<"-------------------"<<endl;
    cout<<"Elija una opcion:"<<endl;
    cout<<"1. Ordenar"<<endl;
    cout<<"-------------------"<<endl;
    cin>>option;

    while(option<1 || option>1)
    {
        cout<<"Error. Seleccione una de las opciones:"<<endl;
        cout<<"Elija una opcion:"<<endl;
        cout<<"1. Ordenar"<<endl;
        cin>>option;

    }

    switch(option)
    {
        case 1:
            ordenacionSeleccion();
            break;

    }

    return 0;
}