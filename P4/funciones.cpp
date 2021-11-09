#include "funciones.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>//std::sort

bool sortFunctionDivisa (Divisa i,Divisa j) { return (i.getValor() > j.getValor() ); }
bool sortFunctionMaterial (Material i,Material j) { return (i.getPrecio() > j.getPrecio() ); }

void cargaDivisas(std::vector <Divisa> &divisas, int &cantidadDivisas)
{
    std::string s;

    std::ifstream f("sistemamonetario.txt");
    
    if ( f.is_open() ) 
    {
        do
        {
            std::getline( f, s );

            Divisa nueva_divisa(std::stoi(s));

            divisas.push_back(nueva_divisa);

            cantidadDivisas++;

        }while( !f.eof() );

        std::sort(divisas.begin(), divisas.end(), sortFunctionDivisa);

    }
    else std::cerr << "Error de apertura del archivo." << std::endl;
}

void algoritmoCambio(double n, std::vector <std::vector <int> > C, std::vector <Cambio> &resultado)
{
    /*for (int i = 0; i < 5; i++) {
  
        // Inserting elements at every
        // row i using push_back()
        // function in vector
        for (int j = 0; j < 5; j++) {            
            C[i].push_back(j);   
        }

        for (auto it = C[i].begin(); it != C[i].end(); it++) {
            // (*it) is used to get the
            // value at iterator is
            // pointing
            std::cout << *it << '\t';
        }
        std::cout << "\n";
        
    }*/

    for(int i=1; i<5; i++ )
    {
        C[i][0] = 0;        
    }

    
    for(int i=1; i<5; i++ )
    {
        for (auto it = C.begin(); it != C.end(); it++) {
            // (*it) is used to get the
            // value at iterator is
            // pointing
            std::cout << *it << '\t';
        }
        std::cout << "\n";

        
    }
    



    
}

void cargaMateriales(std::vector <Material> &materiales)
{
    std::string s;

    int etiqueta;
    int volumen;
    int precio;

    FILE* f;
    f = fopen("materialesmochila.txt","rt");
    
    if ( f!=NULL ) 
    {
        while(fscanf(f, "%d %d %d", &etiqueta, &volumen, &precio)==3)
        {
            Material nuevo_material(etiqueta, volumen, precio);

            materiales.push_back(nuevo_material);

        }

        std::sort(materiales.begin(), materiales.end(), sortFunctionMaterial);

    }
    else std::cerr << "Error de apertura del archivo." << std::endl;
}

Mochila algoritmoMochila(std::vector <Material> C, int volumen)
{
    
}