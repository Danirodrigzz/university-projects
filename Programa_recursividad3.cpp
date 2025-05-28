/*
ELABORADO POR: DANIELA RODRÍGUEZ Y RAICELYS PERDOMO 
GRUPO N°10
Modificaciones: 0
FECHA: 21/04/2025
MATERIA: LABORATORIO DE DATOS SEC A
PROFESOR(A): HILDREN MORALES

*/




#include <iostream>
using namespace std;


double potencia(int a, int b) {
 
    if (b == 0) {
        return 1;
    }
   
    else if (b < 0) {
        return 1 / potencia(a, -b);
    }
    
    else {
        return a * potencia(a, b - 1);
    }
}

int main() {
    int base, exponente;
    
    cout << "Ingrese la base: ";
    cin >> base;
    
    cout << "Ingrese el exponente: ";
    cin >> exponente;
    
    double resultado = potencia(base, exponente);
    
    cout << base << " elevado a " << exponente << " es: " << resultado << endl;
    
    return 0;
}
