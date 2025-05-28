/*  A recursive program is required that receives a sequence of nodes through the screen and inserts it into 
a binary search tree (BST); the result of the created tree should be printed. Perform pre-order, in-order, 
and post-order traversals on the BST.



Se requiere labore un programa recursivo que reciba por pantalla una secuencia cualquiera de nodos y lo 
inserte en un árbol ABB se debe imprimir el resultado del árbol creado. Sobre el árbol ABB realice los 
recorridos en preorden, inorden, postorder



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

// Definition of a node / Definición de un nodo
struct NodoABB { 
    int dato; 
    NodoABB* izq; 
    NodoABB* der; 
}; 

// Create a new node / Crear un nuevo nodo
NodoABB* crearNodo(int valor) { 
    NodoABB* nuevo = new NodoABB(); 
    nuevo->dato = valor; 
    nuevo->izq = NULL; 
    nuevo->der = NULL; 
    return nuevo; 
} 

// Insert a value into the tree / Insertar un valor en el árbol
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

// Calculate the height of the tree / Calcular la altura del árbol
int altura(NodoABB* raiz) { 
    if (raiz == NULL) return 0; 
    return 1 + max(altura(raiz->izq), altura(raiz->der)); 
} 

// Display the tree vertically / Mostrar el árbol verticalmente
void mostrarArbolVertical(NodoABB* raiz) { 
    if (raiz == NULL) return; 
    
    int h = altura(raiz); 
    queue<NodoABB*> q; 
    q.push(raiz); 
    
    int nivel = 1; 
    int nodosNivel = 1; 
    int espacios = pow(2, h) - 1; 
    
    while (nivel <= h) { 
        int espaciosAntes = espacios / 2; 
        int espaciosEntre = espacios; 
        
        // Print spaces before first node / Imprimir espacios antes del primer nodo
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
            
            // Print spaces between nodes / Imprimir espacios entre nodos
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

// Preorder traversal / Recorrido en preorden
void preorden(NodoABB* raiz) { 
    if (raiz != NULL) { 
        cout << raiz->dato << " "; 
        preorden(raiz->izq); 
        preorden(raiz->der); 
    } 
} 

// Inorder traversal / Recorrido en inorden
void inorden(NodoABB* raiz) { 
    if (raiz != NULL) { 
        inorden(raiz->izq); 
        cout << raiz->dato << " "; 
        inorden(raiz->der); 
    } 
} 

// Postorder traversal / Recorrido en postorden
void postorden(NodoABB* raiz) { 
    if (raiz != NULL) { 
        postorden(raiz->izq); 
        postorden(raiz->der); 
        cout << raiz->dato << " "; 
    } 
} 

// Generate random tree / Generar árbol aleatorio
void generarArbolAleatorio(NodoABB* &raiz, int cantidad) { 
    srand(time(0)); 
    cout << "\nGenerated numbers / Nuwmeros generados: "; 
    for (int i = 0; i < cantidad; i++) { 
        int num = rand() % 100; // Numbers between 0 and 99 / Números entre 0 y 99
        cout << num << " "; 
        raiz = insertar(raiz, num); 
    } 
    cout << endl; 
} 

int main() { 
    NodoABB* arbol = NULL; 
    int n; 

    cout << "Enter the number of random nodes to generate / Ingrese cantidad de nodos aleatorios a generar: "; 
    cin >> n; 

    generarArbolAleatorio(arbol, n); 

    cout << "\nGenerated tree / Arbol generado:\n"; 
    mostrarArbolVertical(arbol); 

    cout << "\nPreorder traversal / Recorrido Preorden: "; 
    preorden(arbol); 

    cout << "\nInorder traversal / Recorrido Inorden: "; 
    inorden(arbol); 

    cout << "\nPostorder traversal / Recorrido Postorden: "; 
    postorden(arbol); 

    return 0; 
}
