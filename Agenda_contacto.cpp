/* It is required to elaborate a program in C++ using doubly linked lists for handling 
your phone contacts, which allows storing data, performing searches, and deleting by name.



Se requiere elabore un programa en C++ utilizando listas doblemente enlazadas para 
el manejo de sus contactos telefónicos, que permita almacenar los datos, realizar 
búsquedas y eliminar por nombre.




PREPARED BY: DANIELA RODRÍGUEZ AND RAICELYS PERDOMO
GROUP No. 10
MODIFICATIONS: 0
DATE: 05/13/2025
SUBJECT: DATA LAB SEC A
TEACHER: HILDREN MORALES




ELABORADO POR: DANIELA RODRÍGUEZ Y RAICELYS PERDOMO 
GRUPO N°10
Modificaciones: 0
FECHA: 13/05/2025
MATERIA: LABORATORIO DE DATOS SEC A
PROFESOR(A): HILDREN MORALES

*/

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// Pastel pink color for aesthetic UI / Color rosado pastel para una interfaz estética
#define ROSA_PASTEL "\033[38;5;218m"
#define RESET_COLOR "\033[0m"

struct Contacto {
    string nombre;
    string telefono;
    string correo;
    Contacto* sig;
    Contacto* ant;
};

Contacto* primero = NULL;
Contacto* actual = NULL;

// Validate name is not duplicated / Validar que el nombre no esté repetido
bool validarNombre(const string& nombre) {
    actual = primero;
    while (actual != NULL) {
        if (actual->nombre == nombre) return false;
        actual = actual->sig;
    }
    return true;
}

// Clean phone number format (removes spaces, dashes, parentheses) 
// Limpiar formato del número (quita espacios, guiones, paréntesis)
string limpiarNumero(const string& numeroOriginal) {
    string limpio;
    for (size_t i = 0; i < numeroOriginal.length(); i++) {
        char c = numeroOriginal[i];
        if (isdigit(c) || c == '+') limpio += c;
    }
    return limpio;
}

// Validate international phone number with flexible format 
// Validar número internacional con formato flexible
bool validarTelefono(string numero) {
    string limpio = limpiarNumero(numero);

    if (limpio.empty()) return false;

    if (limpio[0] == '+') {
        for (size_t i = 1; i < limpio.length(); i++) {
            if (!isdigit(limpio[i])) return false;
        }
    } else {
        for (size_t i = 0; i < limpio.length(); i++) {
            if (!isdigit(limpio[i])) return false;
        }
    }

    if (limpio.length() < 10 || limpio.length() > 15) return false;

    actual = primero;
    while (actual != NULL) {
        if (actual->telefono == limpio) return false;
        actual = actual->sig;
    }

    return true;
}

// Validate email format / Validar formato de correo
bool validarCorreo(string correo) {
    size_t arroba = correo.find('@');
    size_t puntoCom = correo.rfind(".com");

    if (arroba == string::npos || puntoCom == string::npos || puntoCom < arroba) {
        return false;
    }

    actual = primero;
    while (actual != NULL) {
        if (actual->correo == correo) return false;
        actual = actual->sig;
    }

    return true;
}

// Add a new contact / Agregar un nuevo contacto
void agregarContacto() {
    Contacto* nuevo = new Contacto();

    do {
        cout << ROSA_PASTEL << "Enter contact name / Ingrese el nombre del contacto: " << RESET_COLOR;
        getline(cin >> ws, nuevo->nombre);
        if (!validarNombre(nuevo->nombre))
            cout << "Name already exists. Try another. / Nombre ya registrado. Intente con otro.\n";
    } while (!validarNombre(nuevo->nombre));

    string telefonoIngresado;
    do {
        cout << ROSA_PASTEL << "Enter phone number (e.g. +584121234567 or (0412) 123-4567) / Ingrese el numero telefonico: " << RESET_COLOR;
        getline(cin, telefonoIngresado);
        if (!validarTelefono(telefonoIngresado))
            cout << "Invalid or duplicate number. Try again. / Numero inválido o repetido. Intente de nuevo.\n";
    } while (!validarTelefono(telefonoIngresado));
    nuevo->telefono = limpiarNumero(telefonoIngresado);

    do {
        cout << ROSA_PASTEL << "Enter email / Ingrese el correo: " << RESET_COLOR;
        getline(cin, nuevo->correo);
        if (!validarCorreo(nuevo->correo))
            cout << "Invalid or duplicate email. / Correo invalido o repetido.\n";
    } while (!validarCorreo(nuevo->correo));

    nuevo->sig = NULL;
    nuevo->ant = NULL;

    // Connect new contact to the list / Conectar el nuevo contacto a la lista
    if (primero == NULL) {
        primero = nuevo;
    } else {
        actual = primero;
        while (actual->sig != NULL) {
            actual = actual->sig;
        }
        actual->sig = nuevo;
        nuevo->ant = actual;
    }

    cout << ROSA_PASTEL << "Contact added successfully. / Contacto agregado exitosamente.\n" << RESET_COLOR;
}

// Show all contacts / Mostrar todos los contactos
void mostrarContactos() {
    if (primero == NULL) {
        cout << ROSA_PASTEL << "No contacts to display. / No hay contactos para mostrar.\n" << RESET_COLOR;
        return;
    }

    actual = primero;
    cout << ROSA_PASTEL << "\n*** Contact List / Lista de Contactos ***\n" << RESET_COLOR;
    while (actual != NULL) {
        cout << ROSA_PASTEL;
        cout << "Name / Nombre: " << actual->nombre << endl;
        cout << "Phone / Telefono: " << actual->telefono << endl;
        cout << "Email / Correo: " << actual->correo << endl;
        cout << "***************************\n" << RESET_COLOR;
        actual = actual->sig;
    }
}

// Search for a contact by name / Buscar un contacto por nombre
void buscarContacto() {
    string nombreBuscado;
    cout << ROSA_PASTEL << "Enter the name to search / Ingrese el nombre a buscar: " << RESET_COLOR;
    getline(cin >> ws, nombreBuscado);

    actual = primero;
    bool encontrado = false;
    while (actual != NULL) {
        if (actual->nombre == nombreBuscado) {
            cout << ROSA_PASTEL;
            cout << "Name / Nombre: " << actual->nombre << endl;
            cout << "Phone / Telefono: " << actual->telefono << endl;
            cout << "Email / Correo: " << actual->correo << endl;
            cout << RESET_COLOR;
            encontrado = true;
            break;
        }
        actual = actual->sig;
    }

    if (!encontrado)
        cout << "Contact not found. / Contacto no encontrado.\n";
}

// Delete a contact by name / Eliminar un contacto por nombre
void eliminarContacto() {
    string nombreEliminar;
    cout << ROSA_PASTEL << "Enter the contact name to delete / Ingrese el nombre del contacto a eliminar: " << RESET_COLOR;
    getline(cin >> ws, nombreEliminar);

    actual = primero;
    while (actual != NULL) {
        if (actual->nombre == nombreEliminar) {
            if (actual->ant != NULL)
                actual->ant->sig = actual->sig;
            else
                primero = actual->sig;

            if (actual->sig != NULL)
                actual->sig->ant = actual->ant;

            delete actual;
            cout << "Contact deleted successfully. / Contacto eliminado exitosamente.\n";
            return;
        }
        actual = actual->sig;
    }
    cout << "Contact not found. / Contacto no encontrado.\n";
}

// Main menu / Menú principal
void menu() {
    int opcion;
    do {
        system("cls"); // Use "clear" if you're on Linux/Mac / Usa "clear" si estás en Linux/Mac
        cout << ROSA_PASTEL;
        cout << "*************************************\n";
        cout << "*     CONTACTS AGENDA / AGENDA DE CONTACTOS     *\n";
        cout << "*-----------------------------------*\n";
        cout << "* 1. Add contact / Agregar contacto *\n";
        cout << "* 2. Show contacts / Mostrar todos  *\n";
        cout << "* 3. Search contact / Buscar nombre *\n";
        cout << "* 4. Delete contact / Eliminar      *\n";
        cout << "* 5. Exit / Salir                   *\n";
        cout << "*************************************\n";
        cout << "Select an option / Seleccione una opción: ";
        cout << RESET_COLOR;
        cin >> opcion;

        switch (opcion) {
            case 1: agregarContacto(); break;
            case 2: mostrarContactos(); break;
            case 3: buscarContacto(); break;
            case 4: eliminarContacto(); break;
            case 5:
                cout << ROSA_PASTEL << "Thanks for using the agenda. Goodbye! / Gracias por usar la agenda. Hasta pronto!\n" << RESET_COLOR;
                break;
            default:
                cout << ROSA_PASTEL << "Invalid option. Try again. / Opcion invalida. Intente de nuevo.\n" << RESET_COLOR;
                break;
        }

        if (opcion != 5) {
            cout << ROSA_PASTEL << "\nPress ENTER to continue... / Presione ENTER para continuar..." << RESET_COLOR;
            cin.ignore();
            cin.get();
        }

    } while (opcion != 5);
}

int main() {
    menu();
    return 0;
}
