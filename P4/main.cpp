#include <iostream>
#include <vector>
#include <algorithm>    // std::sort
#include "divisa.hpp"
#include "funciones.h"
#include "material.hpp"
#include "mochila.hpp"

using std::cout;
using std::cin;
using std::endl;

int main()
{
    std::vector <Divisa> divisas;
    std::vector <Cambio> resultado;

    std::vector <Material> materiales;
    Mochila mochila;
    std::vector<Material> contenidoMochila;

    int decision = 0;


    int cantidadMonedas = 0;
    cargaDivisas(divisas, cantidadMonedas);

    std::vector < std::vector <int> > tabla_de_secuencias;

    cargaMateriales(materiales);



    while(decision != 3)
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

        double cantidad_problema = 0;

        switch(decision)
        {
            case 1:


                //FLAG Vector ordenado: correcto
                /*for(std::vector<Divisa>::iterator it=divisas.begin(); it!=divisas.end(); ++it)
                {
                    std::cout << it->getValor() << "\tTipo: " << it->getTipo() << std::endl;
                }*/

                std::cout << "Introduzca la cantidad a cambiar: \n";
                std::cin >> cantidad_problema;
    
                algoritmoCambio(cantidad_problema, tabla_de_secuencias, resultado);

                std::cout << "\nEl cambio es: " << std::endl;

                for(std::vector<Cambio>::iterator it=resultado.begin(); it!=resultado.end(); ++it)
                {
                    if(it->getCantidad()>0)
                    {
                        std::cout << it->getCantidad() << " " << (it->getDivisa()).getTipo() << "(s) de " << (it->getDivisa()).getValor() << std::endl;
                    }
                }                
                
                std::cout << "\n";

                break;

            case 2:
                //FLAG Vector ordenado: correcto
                //for(std::vector<Material>::iterator it=materiales.begin(); it!=materiales.end(); ++it)
                //{
                  //  std::cout <<"Etiqueta: " << it->getEtiqueta() << "\tVolumen: " << it->getVolumen() << "\tPrecio: " << it->getPrecio() << std::endl;
                //}
                
                std::cout << "Introduzca el volumen de la mochila: \n";
                std::cin >> cantidad_problema;

                mochila = algoritmoMochila(materiales, cantidad_problema);
                
                contenidoMochila = mochila.getContenido();

                std::cout << "El contenido de la mochila es: \n"; 

                for(std::vector<Material>::iterator it=contenidoMochila.begin(); it!=contenidoMochila.end(); ++it)
                {
                    std::cout <<"Etiqueta: " << it->getEtiqueta() << "\tVolumen: " << it->getVolumen() << "\tPrecio: " << it->getPrecio();

                    if(it->getParcial() == "Si")
                    {
                        std::cout << "\tEs parcial\n";
                    }
                    else
                    {
                        std::cout << "\n";
                    }
                }

                std::cout << "Precio Total: " << mochila.getPrecioTotal() << std::endl;

                break;
        
            case 3:
                std::cout << "Ha elegido salir" << std::endl;
                break;
        }
    }

    return 0;
}
