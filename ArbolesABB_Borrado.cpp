/*  It is required that you complete the program sent yesterday about AVL trees to implement 
the option to delete any node selected by the user.


Se requiere que complete el programa enviado ayer sobre árboles ABB se implemente la opción 
de Borrar un nodo cualesquiera seleccionado por el usuario.


PREPARED BY: DANIELA RODRÍGUEZ AND RAICELYS PERDOMO
GROUP No. 10
MODIFICATIONS: 0
DATE: 05/27/2025
SUBJECT: DATA LAB SEC A
TEACHER: HILDREN MORALES


ELABORADO POR: DANIELA RODRÍGUEZ Y RAICELYS PERDOMO 
GRUPO N°10
MODIFICACIONES: 0
FECHA: 27/05/2025
MATERIA: LABORATORIO DE DATOS SEC A
PROFESOR(A): HILDREN MORALES



*/


#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <queue> 
#include <cmath> 


using namespace std; 
struct NodoABB { 
int dato; 
NodoABB* izq; 
NodoABB* der; 
}; 


NodoABB* crearNodo(int valor) { 
NodoABB* nuevo = new NodoABB(); 
nuevo->dato = valor; 
nuevo->izq = NULL; 
nuevo->der = NULL; 
return nuevo; 
} 


NodoABB* insertar(NodoABB* raiz, int valor) { 
if (raiz == NULL) { 
return crearNodo(valor); 
} 


if (valor < raiz->dato) { 
raiz->izq = insertar(raiz->izq, valor); 
} else if (valor > raiz->dato) { 
        raiz->der = insertar(raiz->der, valor); 
    } 
    return raiz; 
} 
 
 // Function to find the node with the minimum value in a tree
// Función para encontrar el nodo con el valor mínimo en un árbol 
NodoABB* encontrarMinimo(NodoABB* raiz) { 
    while (raiz->izq != NULL) { 
        raiz = raiz->izq; 
    } 
    return raiz; 
} 

 // Function to find the node with the maximum value in a tree
// Función para encontrar el nodo con el valor máximo en un árbol 
NodoABB* encontrarMaximo(NodoABB* raiz) { 
    while (raiz->der != NULL) { 
        raiz = raiz->der; 
    } 
    return raiz; 
} 
 
 // Function to delete a node from the tree
// Función para eliminar un nodo del árbol 
NodoABB* eliminarNodo(NodoABB* raiz, int valor, int opcion) { 
    if (raiz == NULL) return raiz; 
     
     
     // Find the node to delete
    // Buscar el nodo a eliminar 
    if (valor < raiz->dato) { 
        raiz->izq = eliminarNodo(raiz->izq, valor, opcion); 
    } else if (valor > raiz->dato) { 
        raiz->der = eliminarNodo(raiz->der, valor, opcion); 
    } else { 
         //Node with a single child or no children
        // Nodo con un solo hijo o sin hijos 
        if (raiz->izq == NULL) { 
            NodoABB* temp = raiz->der; 
            delete raiz; 
            return temp; 
        } else if (raiz->der == NULL) { 
            NodoABB* temp = raiz->izq; 
            delete raiz; 
            return temp; 
        } 
         // Node with two children
        // Nodo con dos hijos 
        NodoABB* temp; 
        if (opcion == 1) { 
             // Replace with the lesser of the greater (minimum of the right subtree)
            // Reemplazar con el menor de los mayores (mínimo del subárbol derecho) 
            temp = encontrarMinimo(raiz->der); 
            raiz->dato = temp->dato; 
            raiz->der = eliminarNodo(raiz->der, temp->dato, opcion); 
        } else { 
        
             // Replace with the largest of the smallest (maximum of the left subtree)
            // Reemplazar con el mayor de los menores (máximo del subárbol izquierdo) 
            temp = encontrarMaximo(raiz->izq); 
            raiz->dato = temp->dato; 
            raiz->izq = eliminarNodo(raiz->izq, temp->dato, opcion); 
        } 
    } 
return raiz; 
} 
// Function to check if a value exists in the tree
// Función para verificar si un valor existe en el árbol 
bool existe(NodoABB* raiz, int valor) { 
if (raiz == NULL) return false; 
if (raiz->dato == valor) return true; 
if (valor < raiz->dato) return existe(raiz->izq, valor); 
return existe(raiz->der, valor); 
} 

// Function to calculate the height of the tree
// Función para calcular la altura del árbol 
int altura(NodoABB* raiz) { 
if (raiz == NULL) return 0; 
return 1 + max(altura(raiz->izq), altura(raiz->der)); 
} 


//Function to display the tree vertically with the root at the top
// Función para mostrar el árbol verticalmente con la raíz arriba 
void mostrarArbolVertical(NodoABB* raiz) { 
if (raiz == NULL) { 
cout << "The tree is empty. / El arbol esta vacio.\n"; 
return; 
} 
int h = altura(raiz); 
queue<NodoABB*> q; 
q.push(raiz); 
    int nivel = 1; 
    int nodosNivel = 1; 
    int espacios = pow(2, h) - 1; 
     
    while (nivel <= h) { 
        int espaciosAntes = espacios / 2; 
        int espaciosEntre = espacios; 
         
         // Print spaces before the first node of the level
        // Imprimir espacios antes del primer nodo del nivel 
        for (int i = 0; i < espaciosAntes; i++) { 
            cout << " "; 
        } 
         
        for (int i = 0; i < nodosNivel; i++) { 
            NodoABB* actual = q.front(); 
            q.pop(); 
             
            if (actual != NULL) { 
                cout << actual->dato; 
                q.push(actual->izq); 
                q.push(actual->der); 
            } else { 
                cout << " "; 
                q.push(NULL); 
                q.push(NULL); 
            } 
             
             // Print spaces between nodes
            // Imprimir espacios entre nodos 
            for (int j = 0; j < espaciosEntre; j++) { 
                cout << " "; 
            } 
        } 
         
        cout << endl << endl; 
        nivel++; 
        nodosNivel *= 2; 
        espacios = espaciosAntes; 
    } 
} 
 
void preorden(NodoABB* raiz) { 
    if (raiz != NULL) { 
        cout << raiz->dato << " "; 
        preorden(raiz->izq); 
        preorden(raiz->der); 
    } 
} 
 
void inorden(NodoABB* raiz) { 
    if (raiz != NULL) { 
        inorden(raiz->izq); 
        cout << raiz->dato << " "; 
        inorden(raiz->der); 
    } 
} 
 
void postorden(NodoABB* raiz) { 
    if (raiz != NULL) { 
        postorden(raiz->izq); 
        postorden(raiz->der); 
        cout << raiz->dato << " "; 
    } 
} 
 
void generarArbolAleatorio(NodoABB* &raiz, int cantidad) { 
    srand(time(0)); 
    cout << "\nGenerated numbers / Numeros generados: "; 
    for (int i = 0; i < cantidad; i++) { 
                                   //Numbers between 0 and 99
        int num = rand() % 100; // Números entre 0 y 99 
        cout << num << " "; 
        raiz = insertar(raiz, num); 
    } 
    cout << endl; 
} 
 
void menu(NodoABB* &arbol) { 
    int opcion, valor; 
    do { 
        cout << "\n\n----- MENU -----\n"; 
        cout << "1. Show tree graphically / Mostrar arbol graficamente\n"; 
        cout << "2. Pre-order traversal / Recorrido Preorden\n"; 
        cout << "3. Inorder Traversal / Recorrido Inorden\n"; 
        cout << "4. Postorder Traversal / Recorrido Postorden\n"; 
        cout << "5. Delete a node / Eliminar un nodo\n"; 
        cout << "6. to go out/Salir\n"; 
        cout << "Select an option / Seleccione una opcion: "; 
        cin >> opcion; 
         
        switch(opcion) { 
            case 1: 
                cout << "\nCurrent tree / Arbol actual:\n"; 
                mostrarArbolVertical(arbol); 
                break; 
            case 2: 
                cout << "\nPre-order traversal / Recorrido Preorden: "; 
                preorden(arbol); 
                break; 
            case 3: 
                cout << "\nInorder Traversal / Recorrido Inorden: "; 
                inorden(arbol); 
                break; 
            case 4: 
                cout << "\nPostorder Traversal / Recorrido Postorden: "; 
                postorden(arbol); 
                break; 
            case 5: 
                cout << "\nEnter the value of the node to be deleted / Ingrese el valor del nodo a eliminar: "; 
                cin >> valor; 
                if (!existe(arbol, valor)) { 
                    cout << "The node with value / El nodo con valor " << valor << " does not exist in the tree / no existe en el arbol.\n"; 
                } else { 
                    int opcionEliminar; 
                    cout << "Does the node have two children? (1 for YES, 0 for NO): "; 
                    cout << "El nodo tiene dos hijos? (1 para SI, 0 para NO): "; 
                    cin >> opcionEliminar; 
                    if (opcionEliminar == 1) { 
                        cout << "How do you want to restructure the tree? / Como desea reestructurar el arbol?\n"; 
                        cout << "1. Replace with the smaller of the greater ones / Reemplazar con el menor de los mayores\n"; 
                        cout << "2. Replace with the greatest of the least / Reemplazar con el mayor de los menores\n"; 
                        cout << "Select an option / Seleccione una opcion: "; 
                        cin >> opcionEliminar; 
                    } 
                    arbol = eliminarNodo(arbol, valor, opcionEliminar); 
                    cout << "Node deleted. Tree updated / Nodo eliminado. Arbol actualizado:\n"; 
                    mostrarArbolVertical(arbol); 
                } 
                break; 
            case 6: 
                cout << "Leaving the program / Saliendo del programa...\n"; 
                break; 
            default: 
                cout << "Invalid option. Please try again. / Opcion no valida. Intente nuevamente.\n"; 
        } 
    } while (opcion != 6); 
} 
 
int main() { 
    NodoABB* arbol = NULL; 
    int n; 
 
    cout << "Enter the amount of random nodes to generate / Ingrese cantidad de nodos aleatorios a generar: "; 
cin >> n; 
generarArbolAleatorio(arbol, n); 
menu(arbol); 
return 0; 
}
