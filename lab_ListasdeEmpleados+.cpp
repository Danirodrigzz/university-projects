/*
ELABORADO POR: DANIELA RODRÍGUEZ Y RAICELYS PERDOMO 
GRUPO N°10
MODIFICACIONES: 1
FECHA: 28/04/2025
MATERIA: LABORATORIO DE DATOS SEC A
PROFESOR(A): HILDREN MORALES

*/

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <ctime>
using namespace std;

struct Fecha {
    int dia, mes, anio;

    void leer(const string& mensaje) {
        bool fechaValida = false;
        while (!fechaValida) {
            cout << mensaje << " (dd mm aaaa): ";
            cin >> dia >> mes >> anio;
            fechaValida = validarFecha();
            if (!fechaValida) {
                cout << "\n!!! FECHA INVALIDA, INTENTE NUEVAMENTE !!!\n";
            }
        }
    }

    void mostrar(const string& etiqueta) const {
        cout << etiqueta << ": " 
             << setfill('0') << setw(2) << dia << "/" 
             << setw(2) << mes << "/" 
             << anio << setfill(' ');
    }

    bool validarFecha() const {
        if (mes < 1 || mes > 12) return false;
        if (dia < 1 || dia > 31) return false;

        time_t t = time(0);
        tm* now = localtime(&t);

        if (anio > (now->tm_year + 1900)) return false;
        if (anio == (now->tm_year + 1900) && mes > (now->tm_mon + 1)) return false;
        if (anio == (now->tm_year + 1900) && mes == (now->tm_mon + 1) && dia > now->tm_mday) return false;

        return true;
    }

    bool estaEnRango(const Fecha& inicio, const Fecha& fin) const {
        if (anio < inicio.anio || anio > fin.anio) return false;
        if (anio == inicio.anio && (mes < inicio.mes || (mes == inicio.mes && dia < inicio.dia))) return false;
        if (anio == fin.anio && (mes > fin.mes || (mes == fin.mes && dia > fin.dia))) return false;
        return true;
    }

    bool esMenorQue(const Fecha& otra) const {
        if (anio != otra.anio) return anio < otra.anio;
        if (mes != otra.mes) return mes < otra.mes;
        return dia < otra.dia;
    }
};

struct Empleado {
    string cedula;
    string nombre;
    double salario;
    Fecha ingreso;
    Fecha nacimiento;
    Fecha ultimoAscenso;
    Empleado* siguiente;

    Empleado() : siguiente(NULL) {}

    void capturarDatosSinCedula() {
        bool nombreValido = false;
        while (!nombreValido) {
            cout << "Nombre completo: "; 
            cin.ignore();
            getline(cin, nombre);
            nombreValido = validarNombre(nombre);
            if (!nombreValido) {
                cout << "\n!!! NOMBRE INVALIDO, SOLO SE PERMITEN LETRAS Y ESPACIOS !!!\n";
            }
        }

        cout << "Salario: ";
        cin >> salario;

        bool fechasValidas = false;
        while (!fechasValidas) {
            ingreso.leer("Fecha de ingreso");
            nacimiento.leer("Fecha de nacimiento");
            ultimoAscenso.leer("Fecha del ultimo ascenso");

            if (!nacimiento.esMenorQue(ingreso)) {
                cout << "\n!!! ERROR: La fecha de nacimiento debe ser anterior a la fecha de ingreso !!!\n";
            } else if (!ingreso.esMenorQue(ultimoAscenso) && !(ingreso.anio == ultimoAscenso.anio && ingreso.mes == ultimoAscenso.mes && ingreso.dia == ultimoAscenso.dia)) {
                cout << "\n!!! ERROR: La fecha de ingreso debe ser anterior o igual a la fecha del ultimo ascenso !!!\n";
            } else {
                fechasValidas = true;
            }
        }
        siguiente = NULL;
    }

    bool validarNombre(const string& nombre) const {
        for (int i = 0; i < nombre.length(); ++i) {
            if (!isalpha(nombre[i]) && nombre[i] != ' ') {
                return false;
            }
        }
        return true;
    }

    void mostrar() const {
        cout << "\n=================================\n";
        cout << "CEDULA: " << cedula << "\n";
        cout << "NOMBRE: " << nombre << "\n";
        cout << "SALARIO: $" << fixed << setprecision(2) << salario << "\n";
        ingreso.mostrar("FECHA INGRESO");
        cout << "\n";
        nacimiento.mostrar("FECHA NACIMIENTO");
        cout << "\n";
        ultimoAscenso.mostrar("ULTIMO ASCENSO");
        cout << "\n=================================\n";
    }
};

class ListaEmpleados {
private:
    Empleado* primero;

public:
    ListaEmpleados() : primero(NULL) {}

    ~ListaEmpleados() {
        limpiar();
    }

    bool cedulaExiste(const string& cedula) const {
        Empleado* actual = primero;
        while (actual) {
            if (actual->cedula == cedula) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    void agregar() {
        Empleado* nuevo = new Empleado();

        bool cedulaValida = false;
        while (!cedulaValida) {
            cout << "\n--- NUEVO EMPLEADO ---\n";
            cout << "Cedula: ";
            cin >> nuevo->cedula;

            if (cedulaExiste(nuevo->cedula)) {
                cout << "\n!!! CEDULA YA EXISTENTE, INTENTE CON OTRA !!!\n";
            } else {
                cedulaValida = true;
            }
        }

        nuevo->capturarDatosSinCedula();

        if (!primero || primero->salario < nuevo->salario) {
            nuevo->siguiente = primero;
            primero = nuevo;
        } else {
            Empleado* actual = primero;
            while (actual->siguiente && actual->siguiente->salario >= nuevo->salario) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
        cout << "\n>>> EMPLEADO REGISTRADO CON EXITO <<<\n";
    }

    void mostrarTodos() const {
        if (!primero) {
            cout << "\n!!! NO HAY EMPLEADOS REGISTRADOS !!!\n";
            return;
        }

        cout << "\n=== LISTA DE EMPLEADOS ===\n";
        Empleado* actual = primero;
        int contador = 1;
        while (actual) {
            cout << "\nEMPLEADO #" << contador++;
            actual->mostrar();
            actual = actual->siguiente;
        }
    }

    void buscarPorSalario() const {
        if (!primero) {
            cout << "\n!!! NO HAY EMPLEADOS REGISTRADOS !!!\n";
            return;
        }

        double salario;
        cout << "\nIngrese el salario a buscar: ";
        cin >> salario;

        Empleado* actual = primero;
        bool encontrado = false;
        while (actual) {
            if (actual->salario == salario) {
                actual->mostrar();
                encontrado = true;
            }
            actual = actual->siguiente;
        }

        if (!encontrado) {
            cout << "\n!!! NO SE ENCONTRARON EMPLEADOS CON ESE SALARIO !!!\n";
        }
    }

    void buscarPorCedula() const {
        if (!primero) {
            cout << "\n!!! NO HAY EMPLEADOS REGISTRADOS !!!\n";
            return;
        }

        string cedula;
        cout << "\nIngrese la cedula a buscar: ";
        cin >> cedula;

        Empleado* actual = primero;
        while (actual) {
            if (actual->cedula == cedula) {
                actual->mostrar();
                return;
            }
            actual = actual->siguiente;
        }

        cout << "\n!!! NO SE ENCONTRO EL EMPLEADO !!!\n";
    }

    void buscarPorRangoFechas() const {
        if (!primero) {
            cout << "\n!!! NO HAY EMPLEADOS REGISTRADOS !!!\n";
            return;
        }

        int opcion;
        cout << "\nBuscar por rango de:\n";
        cout << "1. Fechas de ingreso\n";
        cout << "2. Fechas de nacimiento\n";
        cout << "3. Fechas de ultimo ascenso\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion < 1 || opcion > 3) {
            cout << "\n!!! OPCION INVALIDA !!!\n";
            return;
        }

        Fecha inicio, fin;
        cout << "\n--- RANGO DE FECHAS ---\n";
        inicio.leer("Fecha inicial");
        fin.leer("Fecha final");

        Empleado* actual = primero;
        bool encontrado = false;
        while (actual) {
            const Fecha* fecha = NULL;
            switch (opcion) {
                case 1: fecha = &actual->ingreso; break;
                case 2: fecha = &actual->nacimiento; break;
                case 3: fecha = &actual->ultimoAscenso; break;
            }

            if (fecha && fecha->estaEnRango(inicio, fin)) {
                actual->mostrar();
                encontrado = true;
            }
            actual = actual->siguiente;
        }

        if (!encontrado) {
            cout << "\n!!! NO SE ENCONTRARON EMPLEADOS EN ESE RANGO !!!\n";
        }
    }

    void borrarPorCedula() {
        if (!primero) {
            cout << "\n!!! NO HAY EMPLEADOS REGISTRADOS !!!\n";
            return;
        }

        string cedula;
        cout << "\nIngrese la cedula del empleado a borrar: ";
        cin >> cedula;

        Empleado* actual = primero;
        Empleado* anterior = NULL;

        while (actual) {
            if (actual->cedula == cedula) {
                if (anterior) {
                    anterior->siguiente = actual->siguiente;
                } else {
                    primero = actual->siguiente;
                }
                delete actual;
                cout << "\n>>> EMPLEADO ELIMINADO CON EXITO <<<\n";
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }

        cout << "\n!!! NO SE ENCONTRO EL EMPLEADO CON ESA CEDULA !!!\n";
    }

    void borrarPorSalario() {
        if (!primero) {
            cout << "\n!!! NO HAY EMPLEADOS REGISTRADOS !!!\n";
            return;
        }

        double salario;
        cout << "\nIngrese el salario del empleado(s) a borrar: ";
        cin >> salario;

        Empleado* actual = primero;
        Empleado* anterior = NULL;
        bool encontrado = false;

        while (actual) {
            if (actual->salario == salario) {
                Empleado* temp = actual;
                if (anterior) {
                    anterior->siguiente = actual->siguiente;
                } else {
                    primero = actual->siguiente;
                }
                actual = actual->siguiente;
                delete temp;
                encontrado = true;
            } else {
                anterior = actual;
                actual = actual->siguiente;
            }
        }

        if (encontrado) {
            cout << "\n>>> EMPLEADO(S) ELIMINADO(S) CON EXITO <<<\n";
        } else {
            cout << "\n!!! NO SE ENCONTRARON EMPLEADOS CON ESE SALARIO !!!\n";
        }
    }

    void limpiar() {
        Empleado* actual = primero;
        while (actual) {
            Empleado* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        primero = NULL;
    }
};

void mostrarMenuPrincipal() {
    cout << "\n===============================\n"; 
    cout << "  SISTEMA DE GESTION DE EMPLEADOS\n"; 
    cout << "===============================\n"; 
    cout << "1. Agregar nuevo empleado\n"; 
    cout << "2. Mostrar todos los empleados\n"; 
    cout << "3. Buscar empleados por salario\n"; 
    cout << "4. Buscar empleado por cedula\n"; 
    cout << "5. Buscar empleados por rango de fechas\n"; 
    cout << "6. Borrar empleado por cedula\n";
    cout << "7. Borrar empleados por salario\n";
    cout << "8. Salir del sistema\n"; 
    cout << "Seleccione una opcion: "; 
}

int main() {
    ListaEmpleados lista;
    int opcion;

    do {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion) {
            case 1: lista.agregar(); break;
            case 2: lista.mostrarTodos(); break;
            case 3: lista.buscarPorSalario(); break;
            case 4: lista.buscarPorCedula(); break;
            case 5: lista.buscarPorRangoFechas(); break;
            case 6: lista.borrarPorCedula(); break;
            case 7: lista.borrarPorSalario(); break;
            case 8: cout << "\n>>> SISTEMA CERRADO <<<\n"; break;
            default: cout << "\n!!! OPCION NO VALIDA, INTENTE NUEVAMENTE !!!\n";
        }
    } while (opcion != 8);

    return 0;
}
