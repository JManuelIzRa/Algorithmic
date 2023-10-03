#include <iostream>
#include "ordenacionSeleccion.hpp"
#include "productoMatricesCuadradas.hpp"
#include "fibonacciRecursivo.hpp"

int main(){
    int opcion=0;

    srand(time(NULL));

    while(opcion != 4){
        std::cout << "Programa para calcular el tiempo de ejecución de un algoritmo.\n\n";
        std::cout << "Opciones:\n";
        std::cout << "1) Ordenación por selección.\n";
        std::cout << "2) Producto de matrices cuadradas.\n";
        std::cout << "3) Fibonacci Recursivo.\n";
        std::cout << "4) Salir.\n\n";
        std::cout << "Introduzca su opción: ";

        std::cin >> opcion;

        switch (opcion) {
            case 1:
                ordenacionSeleccion();
            break;
            case 2:
                productoMatricesCuadradas();
            break;
            case 3:
                fibonacciRecursivo();
            break;
            case 4:
                std::cout << "\nSaliendo...\n";
            break;
            default:
                std::cout << "\nOpción no válida.\n";
        }
    }
}
