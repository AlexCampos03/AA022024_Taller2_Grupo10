#include <iostream>
#include <fstream> // Librería permitida

using namespace std;

void intercambiar(int& a, int& b);

void intercambiar(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
// Función para leer los salarios desde el archivo
int leerSalarios(const string& Archivo, int salarios[], int maxSalario) {
    ifstream archivo(Archivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << Archivo << endl;
        return 0;
    }

    int i = 0;
    while (archivo >> salarios[i] && i < maxSalario) {
        i++;
    }

    archivo.close();
    return i;
}

void heapify(int salarios[], int n, int i) {
    int mayor = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;

    if (izq < n && salarios[izq] > salarios[mayor])
        mayor = izq;

    if (der < n && salarios[der] > salarios[mayor])
        mayor = der;

    if (mayor != i) {
        intercambiar(salarios[i], salarios[mayor]);
        heapify(salarios, n, mayor);
    }
}



void ordenarSalarios(int salarios[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(salarios, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        intercambiar(salarios[0], salarios[i]);
        heapify(salarios, i, 0);
    }
}

void insertarHeap(int salarios[], int& n, int valor) {
    n++;
    int i = n - 1;
    salarios[i] = valor;

    while (i != 0 && salarios[(i - 1) / 2] < salarios[i]) {
        intercambiar(salarios[i], salarios[(i - 1) / 2]);
        i = (i - 1) / 2;
    } 
}

int eliminarMax(int salarios[], int& n) {
    if (n <= 0) return -1;
    if (n == 1) {
        n--;
        return salarios[0];
    }

    int raiz = salarios[0];
    salarios[0] = salarios[n - 1];
    n--;
    heapify(salarios, n, 0);

    return raiz;
}

bool buscarHeap(int salarios[], int n, int valor) {
    for (int i = 0; i < n; ++i) {
        if (salarios[i] == valor) return true;
    }
    return false;
}

int main() {
    const int MAX_SALARIOS = 1000;
    int salarios[MAX_SALARIOS];
    int numSalarios = leerSalarios("C:\\Users\\Usuario\\Desktop\\Salarios.txt", salarios, MAX_SALARIOS);

    if (numSalarios == 0) {
        cerr << "No se pudieron leer los datos del archivo." << endl;
        return 1;
    }

    int opcion;

    do {
        cout << "\n----- MENU -----" << endl;
        cout << "1. Insertar un nuevo salario" << endl;
        cout << "2. Buscar un salario" << endl;
        cout << "3. Eliminar el salario máximo" << endl;
        cout << "4. Ordenar los salarios" << endl;
        cout << "5. Mostrar los primeros 10 salarios" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int nuevoSalario;
                cout << "Ingrese el nuevo salario a insertar: ";
                cin >> nuevoSalario;
                insertarHeap(salarios, numSalarios, nuevoSalario);
                cout << "Salario $" << nuevoSalario << " insertado correctamente." << endl;
                break;
            }
            case 2: {
                int salarioBuscado;
                cout << "Ingrese el salario a buscar: ";
                cin >> salarioBuscado;
                bool encontrado = buscarHeap(salarios, numSalarios, salarioBuscado);
                if (encontrado) {
                    cout << "El salario $" << salarioBuscado << " se encontró en el heap." << endl;
                } else {
                    cout << "El salario $" << salarioBuscado << " no se encontró en el heap." << endl;
                }
                break;
            }
            case 3: {
                int salarioEliminado = eliminarMax(salarios, numSalarios);
                if (salarioEliminado != -1) {
                    cout << "El salario máximo eliminado es: $" << salarioEliminado << endl;
                } else {
                    cout << "El heap está vacío, no se puede eliminar." << endl;
                }
                break;
            }
            case 4: {
                ordenarSalarios(salarios, numSalarios);
                cout << "Salarios ordenados correctamente." << endl;
                break;
            }
            case 5: {
                cout << "Primeros 10 salarios (disponibles):" << endl;
                for (int i = 0; i < 10 && i < numSalarios; ++i) {
                    cout << i + 1 << ". $" << salarios[i] << endl;
                }
                break;
            }
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 6);

    return 0;
}
