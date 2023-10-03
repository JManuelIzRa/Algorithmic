#include "ordenacionSeleccion.hpp"
#include "ClaseTiempo.hpp"

/*****************************/
/* Inicio funciones secundarias */
/*****************************/

/* Función ejercicio 1.1
 *
 * Rellena automáticamente un vector pasado como referencia
 */
void rellenarVector( std::vector<int> &v ){
    for( long unsigned int i=0; i<v.size(); i++){
        v[i] = rand()%10000000 ;
    }
}

/* Función ejercicio 1.2
 *
 * Ordenación mediante el método de selección
 * 
 */
bool seleccion( std::vector<int> &v)
{
    int min_idx, temp;
    bool result=false;

    // One by one move boundary of unsorted subarray
    for (long unsigned int i = 0; i < v.size()-1; i++)
    {
        // Busca el elemento minimo en una lista desordenada
        min_idx = i;
        for ( long unsigned int j = i+1; j < v.size(); j++)
        {
            if (v[j] < v[min_idx])
            {
                min_idx = j;
            }

         }

         // Cambia el minimo elemento encontrado con el primer elemento
         temp = v[min_idx];
         v[min_idx] = v[i];
         v[i] = temp;

    }

    result=true;

    return result;
}

/* Función ejercicio 1.3
 *
 * Devuelve true si la ordenación es correcta
 */
bool estaOrdenado( const std::vector<int> &v)
{
    int temp=v[0];

    for ( long unsigned int i = 1; i<v.size(); i++){
        if( v[i] < temp  ){
            return false;
        }
        temp = v[i];
    }
    return true;
}


/* Función ejercicio 1.4
 *
 * Función que llama a la función que ordena el vector,
 * comprueba si está ordenado y calcula cuanto tarda.
 */
void tiemposOrdenacionSeleccion( int nMin, int nMax, int repeticiones, int incremento, std::vector<double> &tiemposReales, std::vector<double> &numeroElementos)
{
    Clock reloj;

    for ( int i = nMin; i< nMax+1; i+= incremento )
    {
        std::vector<int> vect(i);
        double  tiempo =0;

        for ( int j = 0; j < repeticiones; j++ )
        {
            rellenarVector( vect );

            reloj.start();
            if ( !seleccion( vect ) )
            {
                std::cout << "Error al ordenar el vector.\n";
                exit(1);
            }
            if ( !estaOrdenado( vect ) )
            {
                std::cout << "Error al ordenar el vector.\n";
                exit(1);
            }
            if (reloj.isStarted())
            {
                    reloj.stop();
                    tiempo+=reloj.elapsed();
            }
        }

        std::cout << "Numero de elementos: " << i << ", Tiempo medio de ordenacion: " << (tiempo/repeticiones)/1000000 << " segundos." << std::endl;
        
        tiemposReales.push_back(tiempo/repeticiones);
        numeroElementos.push_back(i);
    }
}

/* Función ejercicio 1.6
 *
 * Función para calcular cualquier sumatorio
 */
double sumatorio( const std::vector<double> &n, const std::vector<double> &t, int expN, int expT)
{
    double total=0;

    for( long unsigned int i = 0; i< n.size(); i++)
    {
        total+=pow(n[i],expN)*pow(t[i],expT);
    }

    return total;
}

/* Función ejercicio 1.6
 *
 * Función que calcula los coeficientes de la curva
 */
void ajustePolinomico( const std::vector<double> &numeroElementos, const std::vector<double> &tiempoReales, std::vector<double> &a)
{
    std::vector < std::vector < double > > A(a.size(), std::vector< double >( a.size() ));// Creando matriz NxN
    std::vector < std::vector < double > > B(a.size(), std::vector< double >( 1 ));// Creando matriz Nx1

    //Obtener la matriz de coeficientes (A) y la de terminos independientes (B) del sistema de
    //ecuaciones. Se obtendran calculando los sumatorios correspondientes mediante la funcion sumatorio.
    for( long unsigned int i = 0; i < a.size(); i++)
    {
        for( long unsigned int j = 0; j < a.size(); j++)
        {
            A[i][j]=sumatorio( numeroElementos, numeroElementos, j, i);
        }
        B[i][0]=sumatorio( numeroElementos, tiempoReales, i, 1);
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

/* Función ejercicio 1.7
 *
 * Función que calcula el tiempo estimado
 * mediante la curva de estimación
 */
void calcularTiemposEstimadosPolinomico(const std::vector <double> &numeroElementos, const std::vector <double> &a, std::vector <double> &tiemposEstimados)
{
    for(long unsigned int i=0;i<numeroElementos.size();i++)
    {
        tiemposEstimados[i]=a[0]+a[1]*numeroElementos[i]+a[2]*pow(numeroElementos[i],2);
    }
}

/*Función ejercicio 1.8
 *
 * Función que calcula la media
 */
double calcMedia(const std::vector <double> &vector){
    double calc=0;

    for(long unsigned int i = 0; i<vector.size();i++)
    {
        calc+=vector[i];
    }
    return calc/vector.size();
}

/*Función ejercicio 1.8
 *
 * Función que calcula la varianza
 */
double calcVarianza(const std::vector <double> &vector, double media)
{
    double calc=0;

    for(long unsigned int i = 0; i<vector.size();i++)
    {
        calc+=pow(vector[i]-media,2);
    }

    return calc/vector.size();
}

/*Función ejercicio 1.8
 *
 * Función que calcula el coeficiente de determiación
 */
double calcularCoeficienteDeterminacion(const std::vector <double> &tiemposReales, const std::vector <double> &tiemposEstimados)
{
    double media, varianzaReales, varianzaEstimados;

    //Calcular varianza de los tiempos reales
    media=calcMedia(tiemposReales);

    varianzaReales=calcVarianza(tiemposReales,media);

    //Calcular la varianza de los tiempos estimados
    media=calcMedia(tiemposEstimados);

    varianzaEstimados=calcVarianza(tiemposEstimados,media);

    return varianzaEstimados/varianzaReales;
}

/* Función 1.10
 *
 * Función que calcula el tiempo estimado
 * en ordenar un vector de tamaño n
 */
double calcularTiempoEstimadoPolinomico(const double &n, std::vector <double> &a)
{
    return a[0] + a[1] * n + a[2] * pow(n,2);
}

/*****************************/
/* Fin funciones secundarias */
/*****************************/


/*********************/
/* Funcion principal */
/*********************/

/* Función ejercicio 1
 *
 * Función que pide los parámetros, llama a la
 * función de ordenar y calcular los tiempos y
 * guarda los datos en un fichero.
 */
void ordenacionSeleccion()
{
    int valMin, valMax, incremento, repeticion, opcion=0;
    double valor=1;

    std::cout << "Introduzca la cantidad mínima de elementos del vector: ";
    std::cin >> valMin;
    std::cout << "Introduzca la cantidad máxima de elementos del vector: ";
    std::cin >> valMax;
    std::cout << "Introduzca el incremento del número de elementos: ";
    std::cin >> incremento;
    std::cout << "Introduzca el número de veces que se repetirá la ordenación: ";
    std::cin >> repeticion;

    std::vector<double> tiemposReales, numeroElementos;


    tiemposOrdenacionSeleccion( valMin, valMax, repeticion, incremento, tiemposReales, numeroElementos);

    //Escribir en un fichero los tiempos reales y el números de elementos del vector
    std::ofstream archivo("tiempoReales.txt");

    if (!archivo.is_open())
    {
        std::cout << "Error creando el archivo.\n";
    }
    
    for(long unsigned int i =0;i< tiemposReales.size();i++)
    {
        archivo << numeroElementos[i] << " " << tiemposReales[i] << "\n";
    
    }

    archivo.close();
    ////////

    std::vector<double> a(3); //Vector de coeficientes

    ajustePolinomico( numeroElementos, tiemposReales, a);

    std::vector<double> tiemposEstimados(numeroElementos.size()); //Vector de tiempos estimados

    calcularTiemposEstimadosPolinomico(numeroElementos, a, tiemposEstimados);

    std::ofstream archivo2("datosFinales.txt");

    if (!archivo2.is_open())
    {
        std::cout << "Error creando el archivo.\n";
    }
    for(long unsigned int i =0;i< tiemposReales.size();i++)
    {
        archivo2 << numeroElementos[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << "\n";
    }

    archivo2.close();

    std::cout << "\nLa ecuación de la curva ajustada por mínimos cuadrados es: t(n) = " << a[0] <<" + " << a[1] << "*n + " << a[2] << "*n^2\n\n";

    std::cout << "El coeficiente de determinación es de : " << calcularCoeficienteDeterminacion(tiemposReales,tiemposEstimados) << "\n\n";

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
            double tiempoEstimado = calcularTiempoEstimadoPolinomico(valor, a);
            double tiempoEstimadoRestante = 0;

            double tiempoEstimadoSegundos = tiempoEstimado/1000000;

            int anios = 0;
            int dias = 0;
            int minutos = 0;
            int segundos = 0;

            anios = tiempoEstimado/(60 * 60 * 24 * 365);
            tiempoEstimadoRestante = fmod(tiempoEstimado, (60 * 60 * 24 * 365));

            dias = tiempoEstimadoRestante/(60 * 60 * 24);
            tiempoEstimadoRestante = fmod(tiempoEstimadoRestante, (60 * 60 * 24));

            minutos = tiempoEstimadoRestante/(60 * 60);
            tiempoEstimadoRestante = fmod(tiempoEstimadoRestante, (60 * 60));

            segundos = tiempoEstimadoRestante/(60);
            std::cout << "\nTiempo estimado en microsegundos: " << tiempoEstimado << std::endl;
            std::cout << "El tiempo estimado que tardaría con un ejemplar de " << valor << " elementos sería: " << anios << " años " 
            << dias << " dias " << minutos << " minutos " << segundos << " segundos."<< std::endl;
        
        }
    }

    std::cout << "\n";
}

/**************************/
/* Fin función principal  */
/**************************/
