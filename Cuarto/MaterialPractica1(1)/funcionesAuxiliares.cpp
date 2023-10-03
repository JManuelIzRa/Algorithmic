#include "funcionesAuxiliares.hpp"
#include <math.h>


void convertirMicrosegundos(double tiempoEstimado, double* anios, double* dias, double* horas, double* minutos, double* segundos) {
    
    double tiempoEstimadoSegundos = tiempoEstimado/1000000;
    double tiempoEstimadoRestante = 0;

    *anios = tiempoEstimadoSegundos/(60 * 60 * 24 * 365);
    tiempoEstimadoRestante = fmod(tiempoEstimadoSegundos, (60 * 60 * 24 * 365));

    *dias = tiempoEstimadoRestante/(60 * 60 * 24);
    tiempoEstimadoRestante = fmod(tiempoEstimadoRestante, (60 * 60 * 24));

    *minutos = tiempoEstimadoRestante/(60 * 60);
    tiempoEstimadoRestante = fmod(tiempoEstimadoRestante, (60 * 60));

    *segundos = tiempoEstimadoRestante/(60);
}