//PROGRAMA QUE IDENTIFICA TIPO DE VARIABLES.

#include <stdio.h>
#include <stdbool.h> // Necesario para usar el tipo de dato booleano

int main() {
    int entero;
    float flotante;
    char cadena[100]; // Tamaño máximo de la cadena
    bool booleano;

    printf("Ingrese un valor: ");
    if (scanf("%d", &entero) == 1) {
        printf("Es una variable entera.\n");
    } else if (scanf("%f", &flotante) == 1) {
        printf("Es una variable de coma flotante.\n");
    } else if (scanf("%s", cadena) == 1) {
        printf("Es una cadena (string).\n");
    } else if (scanf("%d", &booleano) == 1) {
        printf("Es una variable booleana.\n");
    } else {
        printf("No se pudo determinar el tipo de variable.\n");
    }

    return 0;
}
