/*
Imagine that a restaurant (any) has a total of 'N' dishes. Assuming there are dishes of 3 colors, and that someone is washing 
the dishes and stacking them one on top of the other, and that the waiters take the dishes to serve them.Write in pseudocode 
that shows the process of washing and serving dishes and that displays at a certain moment what types of dishes there are, how 
many there are, and what colors are available at a given moment, using stacks. Write in pseudocode that shows the process of washing 
and serving dishes and that shows at a certain moment what types of dishes there are, how many there are, and what colors there are 
at a given moment, using stacks.



Imaginenos que un restaurante (cualquiera) tiene un total de "N" platos. Suponiendo que hay platos de 3 colores, y que alguien 
está lavando platos y los coloca uno sobre otro y que los mesoneros toman de los platos para servirlos. Escriba en pseudocodigo 
que muestre el proceso de lavar y de servir platos y que muestre en un momento determinado que tipo de platos hay, cuantos hay, 
y de que color hay en un momento disponible, usando pilas.


PREPARED BY: DANIELA RODRÍGUEZ AND RAICELYS PERDOMO
GROUP No. 10MODIFICATIONS: 0
DATE: 03/17/2025
SUBJECT: DATA LAB SEC A
TEACHER: HILDREN MORALES



ELABORADO POR: DANIELA RODRÍGUEZ Y RAICELYS PERDOMO 
GRUPO N°10
MODIFICACIONES: 0
FECHA: 17/03/2025
MATERIA: LABORATORIO DE DATOS SEC A
PROFESOR(A): HILDREN MORALES


*/

#include <windows.h>
#include <iostream>
#include <stack>
#include <stdlib.h>
#include <conio.h>
#include <ctime>  

using namespace std;

// Declaring a structure to use the values
// Declarando una estructura para usar los valores 
struct Platos {
    int plato_rojo;
    int plato_azul;    
    int plato_verde;
};

// Function to change the console color according to the desired color
// Función para cambiar el color de la consola según el color deseado
void cambiarColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to print the color and reset to the default color (white)
// Función para imprimir el color y restablecer al color por defecto (blanco)
void imprimirPlatoConColor(string color) {
    if (color == "Red/Rojo" || color == "Reds/Rojos") {
    	                   //Red
        cambiarColor(4);  // Rojo
        cout << "Red/Rojo";
    } else if (color == "Blue/Azul" || color == "Blues/Azules") {
    	                   //Blue
        cambiarColor(1);  // Azul
        cout << "Blue/Azul";
    } else if (color == "Green/Verde" || color == "Green/Verdes") {
    	                  //Green
        cambiarColor(2);  // Verde
        cout << "Green/Verde";
    }
    
                       // Reset to default
    cambiarColor(7);  // Restablecer a blanco 
}  


                                  // Maximum capacity of the battery
   const int MAX_CAPACIDAD = 10; // Capacidad máxima de la pila
   int random_action;

int main() {
    stack<string> pila;
    Platos p;
    char op;
    // Initialize the seed for random numbers
    // Inicializar la semilla de los números aleatorios
    srand(time(0));
    
    cout << "Welcome to the Restaurant! / Bienvenidos al Restaurante!" << endl <<endl;
    cout << "In order to serve the diners, we need to have a good flow of incoming and outgoing dishes." << endl;
     cout << "Para poder atender a los comensales necesitamos tener un buen flujo de entrada y salida de platos." << endl <<endl;
    cout << "Next, we are given a glimpse of that flow from the kitchen: " << endl;
    cout << "A continuacion se nos da un vistazo de dicho flujo desde la cocina: " << endl <<endl;
    system("pause");
    // Random assignment of dishes
    // Asignación aleatoria de platos
    p.plato_rojo = rand() % 30 + 1;
    p.plato_azul = rand() % 30 + 1;
    p.plato_verde = rand() % 30 + 1;

    while (true) {
    	
    	                                 // Generate a random number between 0 and 3 to decide the action
        int random_action = rand() % 4; // Generar un número aleatorio entre 0 y 3 para decidir la acción
        
        if (random_action == 0 && p.plato_rojo > 0) {
        	                                 //Insert value into the stack
            pila.push("Red/Rojo");				//ingresar valor en la pila
            cout << "Entering and washing a colored plate / Entrando y lavando plato de color "; 
            imprimirPlatoConColor("Red/Rojo"); 
            cout << endl;
            p.plato_rojo--;
        } else if (random_action == 1 && p.plato_azul > 0) {
        	                                // Insert value into the stack
            pila.push("Blue/Azul");				//ingresar valor en la pila
            cout << "Entering and washing a colored plate / Entrando y lavando plato de color ";
            imprimirPlatoConColor("Blue/Azul");
            cout << endl;
            p.plato_azul--;
        } else if (random_action == 2 && p.plato_verde > 0) {
        	                                 //Insert value into the stack
            pila.push("Green/Verde");				//ingresar valor en la pila
            cout << "Entering and washing a colored plate / Entrando y lavando plato de color ";
            imprimirPlatoConColor("Green/Verde");
            cout << endl;
            p.plato_verde--;
            Sleep(200);
        } else if (random_action == 3 && !pila.empty()) {
            string plato = pila.top();
            //If the top of the stack is a plate of x color, add 1 (that is to say, it was served and the plate got dirty, it needs to be washed)
            //si el top de la pila de es un plato de x color sumale 1 (es decir se sirvio y se ensucio el plato, hay que lavarlo)
            if(pila.top() == "Red/Rojo"){
            	p.plato_rojo++;
			}else if(pila.top() == "Blue/Azul"){
				p.plato_azul++;
			}else if(pila.top() == "Green/Verde"){
				p.plato_verde++;
			}
                                 //to take value from the stack
            pila.pop();			//sacar valor de la pila
            cout << "Serving and coming out of the kitchen a colorful dish / Sirviendo y saliendo de la cocina un plato de color ";
            imprimirPlatoConColor(plato);
            cout << endl;
            Sleep(200);
        }
        
        	
		if (kbhit() != 0) {
			op = getch();                       //If the pressed key is s or S, break the loop.
			if (op == 's' || op == 'S')  break; //si la tecla presionada es s o S rompe el ciclo
				
		}
		
        
        Sleep(1150);
    }  

    return 0;
}
