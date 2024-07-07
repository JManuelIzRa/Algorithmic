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

    mochila(volumen, materiales,  materiales_resultado);

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

bool sortFunctionMaterial (Material i,Material j) { return (i.getPrecio() > j.getPrecio() ); }

void mochila(float   volumenMochila,   std::vector<Material>   &materiales,   std::vector<MaterialUsado> &solucion)
{
    std::sort(materiales.begin(), materiales.end(), sortFunctionMaterial);

    for(std::vector<Material>::iterator it=materiales.begin(); it!=materiales.end(); it++)
    {
        Material nuevo_material(it->getEtiqueta(), it->getVolumen(), it->getPrecio());

        solucion.push_back(MaterialUsado(nuevo_material, 0));
    }

    double volumen_ocupado = 0;

    int i=0;

    while(volumen_ocupado < volumenMochila && i <materiales.size())
    {
        if (materiales[i].getVolumen() + volumen_ocupado <= volumenMochila)
        {
            solucion[i].setVolumenUsado(materiales[i].getVolumen());
            volumen_ocupado += materiales[i].getVolumen();
            i++;
        }
        else if (volumen_ocupado < volumenMochila)
        {
            solucion[i].setVolumenUsado(solucion[i].getVolumenUsado()+volumenMochila-volumen_ocupado);
            volumen_ocupado += volumenMochila-volumen_ocupado;
        }
        else
        {
            i++;
        }
    }
}

void escribirSolucion(std::vector<MaterialUsado> &solucion)
{
    std::cout << "-------------------\n";
    std::cout << "La mochila contiene los siguientes elementos: "<<std::endl;

    double valor_mochila = 0;

    for (int i=0; i<solucion.size(); i++)
    {
        std::cout << "Etiqueta: " << solucion[i].getMaterial().getEtiqueta() << ", Volumen: " << solucion[i].getVolumenUsado() << std::endl;

        valor_mochila += solucion[i].getMaterial().getPrecio() * solucion[i].getVolumenUsado();
    }

    std::cout << "El valor de la mochila será de: " << valor_mochila << std::endl;
    std::cout << "-------------------\n";

}
