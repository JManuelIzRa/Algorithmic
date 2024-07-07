#include <iostream>
#include "algoritmoNReinas.hpp"

using std::cout;
using std::cin;
using std::endl;

int main()
{

    int decision = 0;

    while (decision!=4) 
    {
        cout<<"-------------------"<<endl;
        cout<<"Elija una opcion:"<<endl;
        cout<<"1. Problema de las NReinas (general)."<<endl;
        cout<<"2. Problema de las NReinas (solución única)."<<endl;
        cout<<"3. Problema de las NReinas usando el algoritmo de Las Vegas." << endl;
        cout<<"4. Salir."<<endl;       
        cout<<"-------------------"<<endl;
        cin>>decision;

        while(decision<1 || decision>4)
        {
            cout<<"Error. Seleccione una de las opciones:"<<endl;
            cout<<"Elija una opcion:"<<endl;
            cout<<"1. Problema de las NReinas (general)."<<endl;
            cout<<"2. Problema de las NReinas (solución única)."<<endl;
            cout<<"3. Problema de las NReinas usando el algoritmo de Las Vegas." << endl;
            cout<<"4. Salir."<<endl;
            cin>>decision;

        }

        switch(decision)
        {
            case 1:
                algoritmoNReinas(false, false);
            break;
            case 2:
                algoritmoNReinas(true, false);
            break;
            case 3:
                algoritmoNReinas(false, true);
            break;
        }
    }

}
