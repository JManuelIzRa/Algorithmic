#include "problemaDeLaMochila.hpp"
#include "material.hpp"
#include "materialUsado.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

// Funcion de nivel medio para resolver el problema de la móchila.
void problemaDeLaMochila(){

    int volumen = 0;

    std::vector<Material> materiales;
    std::vector<MaterialUsado> materiales_resultado;

    std::cout << "Introduzca el volumen de la mochila: \n";
    std::cin >> volumen;

    const char* nombreFichero = "materialesmochila.txt";

    cargarMateriales(materiales, nombreFichero);

    std::vector < std::vector <double>> matrizEstados(materiales.size(), std::vector< double >( volumen+1 ));

    mochila(volumen, materiales,  matrizEstados);

    obtenerSolucion(matrizEstados, materiales, materiales_resultado);

    escribirSolucion(materiales_resultado);

}


void cargarMateriales(std::vector<Material> &materiales, const char *nombreFichero)
{
    std::string etiqueta;
    std::string volumen;
    std::string precio;

    std::ifstream f(nombreFichero);

    if(f.is_open())
    {
        while((f >> etiqueta) && (f >> volumen) && (f >> precio))
        {
            Material nuevo_material(std::stoi(etiqueta), std::stof(volumen), std::stof(precio));
            materiales.push_back(nuevo_material);
        }
    }
    else
    {
        std::cerr << "Error de apertura del archivo." << std::endl;
    }
}


/*void mochila(float volumenMochila, std::vector<Material> &materiales, std::vector<std::vector <double>>& matrizEstados){
    //n -> materiales
    //V -> volumen de la mochila
    //C -> matriz de estados

    //std::sort(materiales.begin(), materiales.end(), sortFunctionMaterial);
    /*
    Rellenamos columna 0
    para i de 0 a n − 1 hacer
    C(i, 0) ← 0
    finpara
    */

    /*for (int i=0; i<materiales.size()-1; i++)
    {
        matrizEstados[i][0] = 0;
    }*/

    /*
    Rellenamos fila 0
p   para j de 0 a V hacer
    */
    /*for (int j=0; j<volumenMochila; j++)
    {
        /*
            si j < D(0).volumen entonces
                C(0, j) ← 0
        */
        /*if(j<materiales[0].getVolumen())
        {
            matrizEstados[0][j] = 0;
        }
        /*
            sino
            C(0, j) ← D(0).precio ∗ D(0).volumen
            finsi
        */
        /*else
        {
            matrizEstados[0][j] = materiales[0].getPrecio() * materiales[0].getVolumen();
        }
        //finpara
        /*
            Rellenamos resto de filas
            para i de 1 a n − 1 hacer
            para j de 1 a V hacer
        */
        /*for (int i=1; i<materiales.size()-1; i++)
        {
            for(int j=1; j<materiales.size()-1; j++)
            {
                /*
                    si j < D(i).volumen entonces
                    C(i, j) ← C(i − 1, j)
                */
                /*if (j < materiales[i].getVolumen())
                {
                    matrizEstados[i][j] = matrizEstados[i-1][j];
                }
                /*
                    sino
                        C(i, j) ← m´ax(C(i − 1, j), D(i).precio ∗ D(i).volumen + C(i − 1, j −
                        D(i).volumen)

                */
                /*else 
                {
                    int izqda = matrizEstados[i-1][j];
                    int dcha = materiales[i].getPrecio()*materiales[i].getVolumen() + matrizEstados[i-1][j-materiales[i].getVolumen()];

                    matrizEstados[i][j] = std::max(izqda, dcha);
                }
            }
            //finsi
        }
        //finpara

    }

    for (int i = 0; i < materiales.size(); i++) {
        for (int j = 1; j <= volumenMochila; j++) {
        
            std::cout << matrizEstados[i][j] <<", ";
        }
        std::cout << std::endl;
    }

}*/

void  mochila(float volumenMochila, std::vector<Material> &materiales, std::vector<std::vector<double>> &matrizEstados) {
    // Rellenamos columna 0
    for (int i = 0; i < materiales.size(); i++) {
        matrizEstados[i][0] = 0;
    }

    // Rellenamos fila 0
    for (int j = 0; j <= volumenMochila; j++) {
        if (j < materiales[0].getVolumen()) {
            matrizEstados[0][j] = 0;
        } else {
            matrizEstados[0][j] = materiales[0].getPrecio() * materiales[0].getVolumen();
        }
    }

    // Rellenamos el resto de filas
    for (int i = 1; i < materiales.size(); i++) {
        for (int j = 1; j <= volumenMochila; j++) {
            if (j < materiales[i].getVolumen()) {
                matrizEstados[i][j] = matrizEstados[i - 1][j];
            } else {
                double izquierda = matrizEstados[i - 1][j];
                double derecha = materiales[i].getPrecio() * materiales[i].getVolumen() + matrizEstados[i - 1][j - materiales[i].getVolumen()];
                matrizEstados[i][j] = std::max(izquierda, derecha);
            }
        }
    }

}

void obtenerSolucion(std::vector<std::vector <double>>& matrizEstados, std::vector<Material> &materiales, std::vector<MaterialUsado> &solucion)
{

    int i = materiales.size() - 1;
    int j = matrizEstados[0].size() - 1;

    while (i > 0 && j > 0) {
        //C(3, 11) =C(2, 11−v 4 )+p 3 ∗v 3 
        if (matrizEstados[i][j] != matrizEstados[i - 1][j]) {
            // El material i se utiliza en la solución
            double cantidadUsada = matrizEstados[i][j] / materiales[i].getPrecio();
            solucion.push_back(MaterialUsado(materiales[i], cantidadUsada));
            j -= cantidadUsada * materiales[i].getVolumen();
        }
        i--;
    }

    // Manejar el caso especial del primer material
    if (j > 0) {
        double cantidadUsada = matrizEstados[i][j] / materiales[i].getVolumen();
        solucion.push_back(MaterialUsado(materiales[i], cantidadUsada));
    }
}

void escribirSolucion(std::vector<MaterialUsado> &solucion)
{
    std::cout << "-------------------\n";
    std::cout << "La mochila contiene los siguientes elementos:" << std::endl;

    double valor_mochila = 0;

    for (int i = 0; i < solucion.size(); i++) {
        // Obtener el material asociado
        Material material = solucion[i].getMaterial();

        std::cout << "Etiqueta: " << material.getEtiqueta() << ", Volumen: " << solucion[i].getVolumenUsado() << std::endl;

        valor_mochila += material.getPrecio() * solucion[i].getVolumenUsado();
    }

    std::cout << "El valor de la mochila será de: " << valor_mochila << std::endl;
    std::cout << "-------------------\n";

}
