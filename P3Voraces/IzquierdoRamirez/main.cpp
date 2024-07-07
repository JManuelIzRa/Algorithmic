#include <iostream>
#include "problemaDeLaMochila.hpp"
#include "problemaDelCambio.hpp"

using std::cout;
using std::cin;
using std::endl;

int main()
{

    int decision = 0;

    while (decision!=3) 
    {
        cout<<"-------------------"<<endl;
        cout<<"Elija una opcion:"<<endl;
        cout<<"1. Problema del cambio."<<endl;
        cout<<"2. Problema de la mochila."<<endl;
        cout<<"3. Salir."<<endl;
        cout<<"-------------------"<<endl;
        cin>>decision;

        while(decision<1 || decision>3)
        {
            cout<<"Error. Seleccione una de las opciones:"<<endl;
            cout<<"Elija una opcion:"<<endl;
            cout<<"1. Problema del cambio."<<endl;
            cout<<"2. Problema de la mochila."<<endl;
            cout<<"3. Salir."<<endl;
            cin>>decision;

        }

        switch(decision)
        {
            case 1:
                problemaDelCambio();
            break;
            case 2:
                problemaDeLaMochila();
            break;
        }
    }

}
