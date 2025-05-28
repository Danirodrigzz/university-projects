/*
ELABORADO POR: DANIELA RODRÍGUEZ Y RAICELYS PERDOMO 
GRUPO N°10
Modificaciones: 0
FECHA: 21/04/2025
MATERIA: LABORATORIO DE DATOS SEC A
PROFESOR(A): HILDREN MORALES

*/



#include <iostream>
#include <iomanip>
#include <locale> 

using namespace std;

double capital_compuesto(double m, double x, int n) {
    if (n == 0) {
        return m;
    }
    return (1 + x / 100.0) * capital_compuesto(m, x, n - 1);
}

int main() {
   
    setlocale(LC_ALL, "");
    system("chcp 65001 > nul");  
    double m, x;
    int n;

    cout << "Ingrese el capital inicial o monto: ";
    cin >> m;

    cout << "Ingrese la tasa de interés anual en porcentaje (%): ";
    cin >> x;

    cout << "Ingrese el número de años: ";
    cin >> n;

    if (m < 0 || x < 0 || n < 0) {
        cout << "Los valores deben ser positivos." << endl;
        return 1;
    }

    double resultado = capital_compuesto(m, x, n);

    cout << fixed << setprecision(2);
    cout << "El capital después de " << n << " años será: $" << resultado << endl;

    return 0;
}
