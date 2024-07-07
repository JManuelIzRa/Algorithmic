#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "moneda.hpp"
#include "problemaDelCambio.hpp"

/**
 * @brief Función de nivel medio para solver el problema del cambio.
 * @param None
 */
void problemaDelCambio(){

    int cantidad = 0;

    std::vector <Moneda> divisas;
    std::vector <int> resultado;

    std::cout << "Introduzca la cantidad a cambiar: \n";
    std::cin >> cantidad;

    const char* nombreFichero = "sistemamonetario.txt";

    cargarSistemaMonetario(divisas, nombreFichero);

    cambio(cantidad, divisas, resultado);

    escribirSolucion(resultado, divisas);        
    
    std::cout << "\n";


}

/**
 * @brief Funcion que carga el sistema monetario a partir del fichero "sistemamonetario.txt"
 * 
 * @param divisas Vector que se rellenara con las divisas que conforman el sistema monetario.
 * @param nombre_fichero Variable que almacena el nombre del fichero que contiene las unidades del sistema monetario.
 */
void cargarSistemaMonetario(std::vector <Moneda> &divisas, const char *nombre_fichero)
{
    std::string s;

    std::ifstream f(nombre_fichero);
    
    if ( f.is_open() ) 
    {
        while(f >> s)
        {
            //std::getline( f, s );

            Moneda nueva_divisa(std::stoi(s));

            divisas.push_back(nueva_divisa);
        }

    }
    else std::cerr << "Error de apertura del archivo." << std::endl;
}

/**
 * @brief Funcion da el cambio usando un algoritmo voraz
 * 
 * @param n Variable que contiene el valor para el cual se busca el cambio.
 * @param C Vector que contiene el sistema monetario del dominio de nuestro problema.
 * @param resultado Vector que almacena la cantidad de cada unidad monetaria usada para dar el cambio.
 */
void cambio(double n, std::vector<Moneda> C, std::vector<int> &resultado){

    double suma_parcial = 0;

    for(std::vector<Moneda>::iterator it=C.begin(); it!=C.end(); ++it)
    {
        int nuevo_cambio(it->getValor());
        resultado.push_back(0);
    }
    
    std::vector<int>::iterator it_ca = resultado.begin();

    int i = 0;

    while(suma_parcial<n)
    {
        if (C[i].getValor() + suma_parcial <= n)
        {
            resultado[i]++;
            suma_parcial += C[i].getValor();
        }
        else{
            i++;
        }
    }
}

// Funcion que 
void escribirSolucion(std::vector<int> &solucion, std::vector <Moneda> &sistemaMonetario)
{
    std::cout << "El cambio es el siguiente: " << std::endl;

    for(int i = 0; i<solucion.size(); i++)
    {
        std::cout << sistemaMonetario[i].getValor() << " U.M.: " << solucion[i] << std::endl;
    }
}