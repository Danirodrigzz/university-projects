#include <iostream>
#include <cmath>
using namespace std;

// Funci�n que calcula la longitud m�xima de la cabilla y el �ngulo
void calcularCabilla(double ancho1, double ancho2, double &longitud, double &angulo) {
  // Aplicar el teorema de Pit�goras para hallar la hipotenusa
  longitud = sqrt(ancho1 * ancho1 + ancho2 * ancho2);

  // Aplicar la funci�n arcoseno para hallar el �ngulo en radianes
  angulo = asin(ancho2 / longitud);

  // Convertir el �ngulo a grados
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

  // Validar que los anchos est�n en el rango permitido
  if (ancho1 < 6 || ancho1 > 12 || ancho2 < 6 || ancho2 > 12) {
    cout << "Los anchos deben estar entre 6 y 12 metros." << endl;
    return 0;
  }

  // Llamar a la funci�n que calcula la longitud y el �ngulo
  calcularCabilla(ancho1, ancho2, longitud, angulo);

  // Mostrar los resultados
  cout << "La longitud m�xima de la cabilla es " << longitud << " metros." << endl;
  cout << "El �ngulo que debe formar la cabilla con el primer pasillo es " << angulo << " grados." << endl;

  return 0;
}
