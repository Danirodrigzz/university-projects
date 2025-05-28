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

void invertir_arreglos(int arr[], int inicio, int fin) {

    cout << "Antes: ";
    for(int i = 0; i <= fin; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

   
    if (inicio >= fin) {
        return;
    }

   invertir_arreglos(arr, inicio + 1, fin - 1);
    int temp = arr[inicio];
    arr[inicio] = arr[fin];
    arr[fin] = temp;

 
   

  
    cout << "Despues del backtracking: ";
    for(int i = 0; i <= fin; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}





int main() {
    int arreglo[] = {1, 2, 3, 4, 5};
    int n = sizeof(arreglo) / sizeof(arreglo[0]);

    invertir_arreglos(arreglo, 0, n - 1);

    cout << "Arreglo final invertido: ";
    for(int i = 0; i < n; i++) {
        cout << arreglo[i] << " ";
    }
    cout << endl;

    return 0;
}
