#include "fibonacciRecursivo.hpp"
#include "ClaseTiempo.hpp"
#include "funcionesAuxiliares.hpp"

/*************************/
/* Funciones secundarias */
/*************************/

/* Función ejercicio 3.0
 *
 * Función de Fibonacci recursivo
 */
long fibonacci(long elemento)
{
    if (elemento < 2)
    {
        return elemento;
    }
    return fibonacci(elemento - 1) + fibonacci(elemento - 2);
}

/* Función ejercicio 3.0
 *
 * Función que llama a Fibonacci recursivo
 * y calcula el tiempo que tarda.
 */
void tiemposFibonacci( long elemento, std::vector<double> &tiemposReales, std::vector<double> &numeroElementos)
{
    Clock reloj;

    reloj.start();

    fibonacci(elemento);

    if (reloj.isStarted())
    {
        reloj.stop();
        double tiempo = reloj.elapsed();
        tiemposReales.push_back(tiempo);
        numeroElementos.push_back(elemento);
        std::cout << "Numero de elementos: " << elemento << ", Tiempo medio de obtención: " << tiempo << std::endl;
    }
}

/* Función ejercicio 3.1
 *
 * Función que calcula el sumatorio de los valores introducidos
 */
double sumatorioFibonacciA( const std::vector<double> &n, const std::vector<double> &t, int expN, int expT)
{
    double total=0;

    for( long unsigned int i = 0; i< n.size(); i++)
    {
        total+=pow(2,n[i]*expN)*pow(2,t[i]*expT);
    }

    return total;
}

double sumatorioFibonacciB( const std::vector<double> &n, const std::vector<double> &t, int expN, int expT)
{
    double total=0;

    for( long unsigned int i = 0; i< n.size(); i++)
    {
        total+=pow(2,n[i]*expN)*pow(t[i],expT);
    }

    return total;
}

/* Función ejercicio 3.1
 *
 * Función que calcula los coeficientes del ajuste de la curva
 */
void ajusteExponencialFibonacci(const std::vector<double> &n, const std::vector<double> &tiemposReales, std::vector<double> &a)
{
    std::vector < std::vector < double > > A(a.size(), std::vector< double >( a.size() ));// Creando matriz NxN
    std::vector < std::vector < double > > B(a.size(), std::vector< double >( 1 ));// Creando matriz Nx1

    //Obtener la matriz de coeficientes (A) y la de terminos independientes (B) del sistema de
    //ecuaciones. Se obtendran calculando los sumatorios correspondientes mediante la funcion sumatorio.
    for( long unsigned int i = 0; i < a.size(); i++)
    {
        for( long unsigned int j = 0; j < a.size(); j++)
        {
            A[i][j]=sumatorioFibonacciA( n, n, j, i);
        }
        B[i][0]=sumatorioFibonacciB( n, tiemposReales, i, 1);
    }

    //ResolverSistema(A, B, matrizX)
    std::vector < std::vector < double > > X(a.size(), std::vector< double >( 1 ));// Creando matriz Nx1
    resolverSistemaEcuaciones( A, B, a.size(), X);

    //Pasar los valores de X al polinomio
    for( long unsigned int i= 0; i< X.size(); i++ )
    {
        a[i]=X[i][0];
    }
}

/* Función ejercicio 3.2
 *
 * Función que calcula los tiempos estimados mediante la ecuación de la curva
 */
void calcularTiemposEstimadosExponencial(const std::vector <double> &n, const std::vector <double> &a, std::vector <double> &tiemposEstimados)
{
    for(long unsigned int i=0;i<n.size();i++)
    {
        tiemposEstimados[i]=a[0]+a[1]*pow(2,n[i]);
    }
}

/*Función ejercicio 3.0
 *
 * Función que calcula la media
 */
double calcMediaFibonacci(const std::vector <double> &vector)
{
    double calc=0;

    for(long unsigned int i = 0; i<vector.size();i++)
    {
        calc+=vector[i];
    }
    return calc/vector.size();
}

/*Función ejercicio 3.0
 *
 * Función que calcula la varianza
 */
double calcVarianzaFibonacci(const std::vector <double> &vector, double media)
{
    double calc=0;

    for(long unsigned int i = 0; i<vector.size();i++)
    {
        calc+=pow(vector[i]-media,2);
    }

    return calc/vector.size();
}

/*Función ejercicio 3.0
 *
 * Función que calcula el coeficiente de determiación
 */
double calcularCoeficienteDeterminacionFibonacci(const std::vector <double> &tiemposReales, const std::vector <double> &tiemposEstimados)
{
    double media, varianzaReales, varianzaEstimados;

    //Calcular varianza de los tiempos reales
    media=calcMediaFibonacci(tiemposReales);

    varianzaReales=calcVarianzaFibonacci(tiemposReales,media);

    //Calcular la varianza de los tiempos estimados
    media=calcMediaFibonacci(tiemposEstimados);

    varianzaEstimados=calcVarianzaFibonacci(tiemposEstimados,media);

    return varianzaEstimados/varianzaReales;
}

/* Función ejercicio 3.2
 *
 * Función que calcula el tiempo estimado de un ejemplar mediante la ecuación de la curva
 */
double calcularTiempoEstimadoExponencial(const double &numeroElementos, const std::vector <double> &a)
{
    return a[0]+a[1]*pow(2,numeroElementos);
}
/*****************************/
/* Fin funciones secundarias */
/*****************************/

/*********************/
/* Funcion principal */
/*********************/

void fibonacciRecursivo()
{
    long minEle, maxEle;
    int opcion = 0;
    double valor = 1;

    std::cout << "Introduzca el primer elemento de la sucesion de Fibonacci que desea calcular: ";
    std::cin >> minEle;
    std::cout << "Introduzca el último elemento de la sucesion de Fibonacci que desea calcular: ";
    std::cin >> maxEle;

    std::vector<double> tiemposReales, n;

    for( int i = minEle; i < maxEle; i++)
    {
        tiemposFibonacci( i, tiemposReales, n);
    }

    //Escribir en un fichero los tiempos reales y el el números de elementos del vector
    std::ofstream archivo("tiempoRealesF.txt");

    if (!archivo.is_open())
    {
        std::cout << "Error creando el archivo.\n";
    }

    for(long unsigned int i =0;i< tiemposReales.size();i++)
    {
        archivo << n[i] << " " << tiemposReales[i] << "\n";
    }

    archivo.close();

    /////////////////POR AQUI LO HE DEJADO, REVISAR
    std::vector<double> a(2); //Vector de coeficientes

    ajusteExponencialFibonacci(n, tiemposReales, a);

    std::cout << "\nLa ecuación de la curva ajustada por mínimos cuadrados es: t(n) = " << a[0] << " + " << a[1] << " * 2^n\n";

    std::vector<double> tiemposEstimados(n.size()); //Vector de tiempos estimados
    calcularTiemposEstimadosExponencial(n, a, tiemposEstimados);

//////
    std::ofstream archivo2("datosFinalesF.txt");

    if (!archivo2.is_open())
    {
        std::cout << "Error creando el archivo.\n";
    }
    for(long unsigned int i =0;i< tiemposReales.size();i++)
    {
        archivo2 << n[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << "\n";
    }

    archivo2.close();

    std::cout << "\nEl coeficiente de determinación es de : " << calcularCoeficienteDeterminacionFibonacci(tiemposReales,tiemposEstimados) << "\n\n";

    std::cout << "¿Quieres hacer una estimación de tiempos para un determinado valor del tamaño del ejemplar?\n";
    std::cout << "1) Sí\n";
    std::cout << "2) No\n";
    std::cout << "Introduzca su respuesta: ";
    std::cin >> opcion;

    while(opcion == 1 && valor != 0)
    {
        std::cout << "Introduzca el tamaño del ejemplar (0 para salir): ";
        std::cin >> valor;

        if(valor != 0)
        {
            double tiempoEstimado = calcularTiempoEstimadoExponencial(valor, a);

            double anios, dias, horas, minutos, segundos;

            convertirMicrosegundos(tiempoEstimado, &anios, &dias, &minutos, &minutos, &segundos);

            std::cout << "\nTiempo estimado en microsegundos: " << tiempoEstimado << std::endl;
            
            std::cout << "El tiempo estimado que tardaría con un ejemplar de " << valor << " elementos sería: " << trunc(anios) << " años " 
            << trunc(dias) << " dias " << trunc(minutos) << " minutos " << trunc(segundos) << " segundos."<< std::endl;        }
    }

    std::cout << "\n";
}

/**************************/
/* Fin función principal  */
/**************************/
