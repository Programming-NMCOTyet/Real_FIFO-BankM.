#include <iostream>
#include <string>
using namespace std;

struct Cliente {
    string numeroCuenta;
    int tipoCuenta;
    int turno;
    Cliente* siguiente;
};

Cliente* cabezaTrad = NULL;
Cliente* cabezaPref = NULL;
int contadorTrad = 0;
int contadorPref = 0;

void reasignarTurnos() {
    int turno = 1;
    
    // Reasignar turnos para clientes tradicionales
    Cliente* tempTrad = cabezaTrad;
    while (tempTrad != NULL) {
        tempTrad->turno = turno;
        tempTrad = tempTrad->siguiente;
        turno++;
    }
    
    // Reasignar turnos para clientes preferenciales
    Cliente* tempPref = cabezaPref;
    while (tempPref != NULL) {
        tempPref->turno = turno;
        tempPref = tempPref->siguiente;
        turno++;
    }
}

void verificarTransferencia() {
    if (contadorTrad >= 5 && contadorPref <= 2) {
        if (contadorTrad >= 3) {
            Cliente* tempTrad = cabezaTrad;
            for (int i = 1; i < 3; ++i) {
                tempTrad = tempTrad->siguiente;
            }
            Cliente* nuevoPref = tempTrad->siguiente;
            tempTrad->siguiente = nuevoPref->siguiente;
            nuevoPref->siguiente = cabezaPref;
            cabezaPref = nuevoPref;
            contadorTrad--;
            contadorPref++;
            reasignarTurnos();
        }
    }
}

void registrarCliente() {
    Cliente* nuevoCliente = new Cliente;
    cout << "Ingrese su numero de cuenta: ";
    cin >> nuevoCliente->numeroCuenta;
    cout << "Tipo de cuenta (1 para preferencial, 2 para tradicional): ";
    cin >> nuevoCliente->tipoCuenta;
    nuevoCliente->siguiente = NULL;

    if (nuevoCliente->tipoCuenta == 1) {
        if (contadorPref == 0) {
            cabezaPref = nuevoCliente;
        } else {
            Cliente* temp = cabezaPref;
            while (temp->siguiente != NULL) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoCliente;
        }
        contadorPref++;
    } else {
        if (contadorTrad == 0) {
            cabezaTrad = nuevoCliente;
        } else {
            Cliente* temp = cabezaTrad;
            while (temp->siguiente != NULL) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoCliente;
        }
        contadorTrad++;
    }

    nuevoCliente->turno = (nuevoCliente->tipoCuenta == 1) ? contadorPref : contadorTrad;

    verificarTransferencia();
}

void mostrarFilas() {
    cout << "Fila de clientes tradicionales:" << endl;
    Cliente* tempTrad = cabezaTrad;
    while (tempTrad != NULL) {
        cout << "Turno " << tempTrad->turno << ": Cuenta: " << tempTrad->numeroCuenta << endl;
        tempTrad = tempTrad->siguiente;
    }
    cout << endl;

    cout << "Fila de clientes preferenciales:" << endl;
    Cliente* tempPref = cabezaPref;
    while (tempPref != NULL) {
        cout << "Turno " << tempPref->turno << ": Cuenta: " << tempPref->numeroCuenta << endl;
        tempPref = tempPref->siguiente;
    }
    cout << endl;
}

void eliminarCliente() {
    string numeroCuentaEliminar;
    cout << "Ingrese el numero de cuenta del cliente que desea eliminar: ";
    cin >> numeroCuentaEliminar;

    // Eliminar cliente de la fila tradicional
    Cliente* tempTrad = cabezaTrad;
    Cliente* prevTrad = NULL;
    while (tempTrad != NULL && tempTrad->numeroCuenta != numeroCuentaEliminar) {
        prevTrad = tempTrad;
        tempTrad = tempTrad->siguiente;
    }

    if (tempTrad != NULL) {
        if (prevTrad != NULL) {
            prevTrad->siguiente = tempTrad->siguiente;
        } else {
            cabezaTrad = tempTrad->siguiente;
        }
        delete tempTrad;
        contadorTrad--;
        reasignarTurnos();
        return; // Terminar la función después de eliminar el cliente
    }

    // Eliminar cliente de la fila preferencial
    Cliente* tempPref = cabezaPref;
    Cliente* prevPref = NULL;
    while (tempPref != NULL && tempPref->numeroCuenta != numeroCuentaEliminar) {
        prevPref = tempPref;
        tempPref = tempPref->siguiente;
    }

    if (tempPref != NULL) {
        if (prevPref != NULL) {
            prevPref->siguiente = tempPref->siguiente;
        } else {
            cabezaPref = tempPref->siguiente;
        }
        delete tempPref;
        contadorPref--;
        reasignarTurnos();
    }
}

int main() {
    int opcion;
    do {
        cout << "Menu:" << endl;
        cout << "1. Registrar cliente" << endl;
        cout << "2. Mostrar filas" << endl;
        cout << "3. Eliminar cliente" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                registrarCliente();
                break;
            case 2:
                mostrarFilas();
                break;
            case 3:
                eliminarCliente();
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}
