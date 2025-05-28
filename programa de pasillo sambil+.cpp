#include <iostream>
#include <cmath>
using namespace std;

// Función que calcula la longitud máxima de la cabilla y el ángulo
void calcularCabilla(double ancho1, double ancho2, double &longitud, double &angulo) {
  // Aplicar el teorema de Pitágoras para hallar la hipotenusa
  longitud = sqrt(ancho1 * ancho1 + ancho2 * ancho2);

  // Aplicar la función arcoseno para hallar el ángulo en radianes
  angulo = asin(ancho2 / longitud);

  // Convertir el ángulo a grados
  angulo = angulo * 180 / M_PI;
}

// Programa principal
int main() {
  // Declarar las variables
  double ancho1, ancho2, longitud, angulo;

  // Pedir al usuario los datos de entrada
  cout << "Ingrese el ancho del primer pasillo (en metros): ";
  cin >> ancho1;
  cout << "Ingrese el ancho del segundo pasillo (en metros): ";
  cin >> ancho2;

  // Validar que los anchos estén en el rango permitido
  if (ancho1 < 6 || ancho1 > 12 || ancho2 < 6 || ancho2 > 12) {
    cout << "Los anchos deben estar entre 6 y 12 metros." << endl;
    return 0;
  }

  // Llamar a la función que calcula la longitud y el ángulo
  calcularCabilla(ancho1, ancho2, longitud, angulo);

  // Mostrar los resultados
  cout << "La longitud máxima de la cabilla es " << longitud << " metros." << endl;
  cout << "El ángulo que debe formar la cabilla con el primer pasillo es " << angulo << " grados." << endl;

  return 0;
}
