#include <cstdlib>

#include <iostream> // Necesaria para ver el resultado en pantalla



using namespace std;



int main()

{

div_t resultado;

resultado = div(14,5); // El primer numero sera dividido entre el segundo



cout << "El resultado es:" << resultado.quot << endl;

cout << "El residuo es:" << resultado.rem << endl;



    system("pause");

    return 0;

}