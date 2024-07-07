#include <iostream>
#include "algoritmoNReinas.hpp"
#include "ClaseTiempo.hpp"


bool lugar(int k, int x, const std::vector<int> &solucion) {
    for (int i = 0; i < k; i++) {
        if (solucion[i] == x || solucion[i] - i == x - k || solucion[i] + i == x + k) {
            return false;
        }
    }
    return true;
}

void escribirSoluciones(std::vector<std::vector<int>>&soluciones) {
    
    std::cout<<"-------------------"<<std::endl;

    for (int i = 0; i < soluciones.size(); i++)
    {
        std::cout << "Solucion: " << i << ":" << std::endl;
        int n = soluciones[i].size();

        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (soluciones[i][j] == k) {
                    std::cout << "Q ";
                } else {
                    std::cout << ". ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout<<"-------------------"<<std::endl;
    }
}

void escribirSolucion(std::vector<int>&solucion)
{
    std::cout << "Solucion encontrada: " << std::endl;
    int n = solucion.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (solucion[i] == j) {
                std::cout << "Q ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout<<"-------------------"<<std::endl;
}


void nReinasBacktracking(int n, std::vector<std::vector<int>> &soluciones) {
    std::vector<int> x(n, -1);
    int k = 0;

    while (k > -1) {
        x[k]++;

        while (x[k] < n && !lugar(k, x[k], x)) {
            x[k]++;
        }

        if (x[k] < n) {
            if (k == n - 1) {
                // Ha encontrado una solución
                soluciones.push_back(x);
         
            } else {
                // Pasa a la siguiente fila para colocar la siguiente reina
                k++;
                x[k] = -1;
            }
        } else {
            // Retrocede a la fila anterior, para probar otra posición de esa reina
            k--;
        }
    }
}

void nReinasBacktracking(int n, std::vector<int>&solucion)
{
    std::vector<int> x(n, -1);
    int k = 0;

    while (k > -1) {
        x[k]++;

        while (x[k] < n && !lugar(k, x[k], x)) {
            x[k]++;
        }

        if (x[k] < n) {
            if (k == n - 1) {
                // Ha encontrado una solución
                solucion = x;
                break;         
            } else {
                // Pasa a la siguiente fila para colocar la siguiente reina
                k++;
                x[k] = -1;
            }
        } else {
            // Retrocede a la fila anterior, para probar otra posición de esa reina
            k--;
        }
    }
}

bool nReinasLasVegas(int n, std::vector<int>& solucion) {
    
    bool exito;
    std::vector<int> x(n); // Vector para almacenar las posiciones de las reinas
    int contador, columna;
    std::vector<int> ok(n); // Vector para almacenar las posiciones posibles de la reina k

    // Inicializamos la solución a 0
    for (int i = 0; i < n; i++) {
        x[i] = 0;
    }

    // Intentos para encontrar la solución
    int intentos = 0;

    // Se han colocado k-1 reinas y se buscan todas las posiciones para la k-ésima
    for (int k = 0; k < n; k++) {
        contador = -1;

        // Almacena todas las posiciones posibles de la reina k en el vector ok
        for (int j = 0; j < n; j++) {
            x[k] = j; // Probamos la reina k en la columna j
            if (lugar(k, x[k], x)) { // Se puede colocar en la columna j
                contador++;
                ok[contador] = j; // Guardamos la posición disponible
            }
        }

        // Salir si no se ha encontrado posición para la reina k
        if (contador == -1) {
            exito = false;
            break;
        }

        // Se puede colocar la reina k y se selecciona una posición aleatoria
        columna = ok[rand() % (contador + 1)];
        x[k] = columna;

        intentos++;

        // Almacenamos la solución parcial
        solucion = x;
    }

    std::cout << "Solución encontrada en " << intentos << " intentos." << std::endl;

    return true; // Se encontró una solución
}

void algoritmoNReinas(bool solUnica, bool lasVegas)
{
    int n;
    std::cout << "Introduzca el numero de reinas: ";
    std::cin >> n;

    if(solUnica && !lasVegas)
    {
        std::vector<int> solucion(n);
        
        Clock reloj;
        
        reloj.start();
        
        if (reloj.isStarted())
        {
            nReinasBacktracking(n, solucion);

            reloj.stop();
            double tiempo = reloj.elapsed();

            escribirSolucion(solucion);
            std::cout << "La solución ha sido encontrada en " << tiempo << " microsegundos." << std::endl;
        }
    }
    else if(!solUnica && !lasVegas)
    {
        std::vector<std::vector<int>> soluciones;

        nReinasBacktracking(n, soluciones);
        escribirSoluciones(soluciones);
    }
    else
    {
        std::vector<int> solucion(n);
        Clock reloj;
        
        reloj.start();
        
        if (reloj.isStarted())
        {
            nReinasLasVegas(n, solucion);
            
            reloj.stop();
            double tiempo = reloj.elapsed();

            escribirSolucion(solucion);

            std::cout << "La solución ha sido encontrada en " << tiempo << " microsegundos." << std::endl;
        }

    }

    
}
