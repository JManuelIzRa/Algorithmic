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

    for (int i=0; i<divisas.size(); i++)
    {
        resultado.push_back(0);
    }

    std::vector < std::vector <int>> matrizEstados(divisas.size(), std::vector< int >( cantidad+1 ));

    cambio(cantidad, divisas, matrizEstados);

    obtenerSolucion(matrizEstados, divisas, resultado);

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
 * @brief Funcion da el cambio usando programacion dinamica
 * 
 */
void cambio(double n, std::vector<Moneda> C, std::vector <std::vector <int>> &matrizEstados){

    for (int i = 0; i < matrizEstados.size(); i++) {
        matrizEstados[i][0] = 0;
    }

    for (int i = 0; i < C.size(); i++) {
        for (int j = 1; j <= n; j++) {
            if (i == 0) {
                matrizEstados[i][j] = 1 + matrizEstados[i][j-C[0].getValor()];
            } else {
                if (j < C[i].getValor()) {
                    matrizEstados[i][j] = matrizEstados[i - 1][j];
                } else {
                    matrizEstados[i][j] = std::min(matrizEstados[i - 1][j], 1 + matrizEstados[i][j - C[i].getValor()]);
                }
            }
        }
    }
}

void obtenerSolucion( std::vector<std::vector <int>>& matrizEstados, std::vector <Moneda> &sistemaMonetario, std::vector<int> &solucion){

     int i = sistemaMonetario.size() - 1;
    int j = matrizEstados[0].size() - 1;

    while (i > 0 && j > 0) {
        if (matrizEstados[i][j] == matrizEstados[i - 1][j]) {
            // La moneda i no se utiliza en la solución
            i--;
        } else {
            // La moneda i se utiliza en la solución
            solucion.push_back(sistemaMonetario[i].getValor());
            j -= sistemaMonetario[i].getValor();
        }
    }

    // Manejar el caso especial de la primera moneda
    if (j > 0) {
        solucion.push_back(sistemaMonetario[i].getValor());
    }

    std::reverse(solucion.begin(), solucion.end());
}

// Funcion que 
void escribirSolucion(std::vector<int> &solucion, std::vector <Moneda> &sistemaMonetario)
{
    if (solucion.empty()) {
        std::cout << "No hay solución." << std::endl;
        return;
    }

    std::cout << "Solución: ";
    for (size_t i = 0; i < solucion.size(); ++i) {
        std::cout << solucion[i];
        if (i < solucion.size() - 1) {
            std::cout << ", ";
        }
    }

    std::cout << std::endl;

    std::cout << "Detalles:" << std::endl;
    //Recorre el sistema monetario
    for (size_t i = 0; i < sistemaMonetario.size(); ++i) {
        int cantidad = 0;
        //Buscando cuantas veces aparece una moneda en la solucion
        for (size_t j = 0; j < solucion.size(); ++j) {
            if (solucion[j] == sistemaMonetario[i].getValor() && solucion[j]!=0) {
                cantidad++;
            }
        }
        
        std::cout << sistemaMonetario[i].getValor() << " U.M. : " << cantidad << " ";
        
        if (cantidad > 1) {
            std::cout << "monedas";
        } else {
            std::cout << "moneda";
        }
        std::cout << std::endl;
    }
}