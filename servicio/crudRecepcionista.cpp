#include <iostream>
#include <fstream>
#include <string>
#include <sstream>//Para cuando busco y separo mediante comas

using namespace std;
int contarFilasCSV();//Declarado para el Uso al Agregar Personal
//Basico para poder Verificar Existencia en el Registro
void agregarPersonaAlCSV() {
    // Variables para almacenar los datos de la persona
    string usuario, contrasena;
    int edad;
    int id; 
    // Solicitar los datos
    cout << "Ingrese el Usuario de la persona: ";
    cin >> usuario;
    cout << "Ingrese el Contrasena de la persona: ";
    cin >> contrasena;
    cout << "Ingrese la edad de la persona: ";
    cin >> edad;

    // Abrir o crear el archivo CSV en modo append
    ofstream archivoCSV;
    archivoCSV.open("recepcionistas.csv", ios::app);//Necesito definir correctamente la Ruta

    // Verificar si el archivo se abrió correctamente
    if (!archivoCSV) {
        cerr << "No se pudo abrir o crear el archivo CSV." << endl;
        return;
    }
    id = contarFilasCSV() + 1;
    // Escribir los datos de la persona en el archivo CSV
    archivoCSV << id << ","<< usuario << "," << contrasena << "," << edad << endl;

    // Cerrar el archivo
    archivoCSV.close();

    cout << "Los datos han sido guardados en el archivo en Recepcionistas.csv" << endl;
}

int contarFilasCSV() {
    ifstream archivoCSV("recepcionistas.csv"); // Abrir el archivo en modo lectura
    string linea;
    int contador = 0;

    // Verificar si el archivo se abrió correctamente
    if (!archivoCSV) {
        cerr << "No se pudo abrir el archivo CSV." << endl;
        return -1; // Devuelve -1 si no se pudo abrir el archivo
    }

    // Leer el archivo línea por línea y contar las filas
    while (getline(archivoCSV, linea)) {
        contador++;
    }

    // Cerrar el archivo
    archivoCSV.close();

    return contador; // Devuelve el número de filas
}


bool verificarUsuarioEnCSV(const string& nombre_usuario) {
    ifstream archivoCSV("recepcionistas.csv");

    // Verificar si el archivo se abrió correctamente
    if (!archivoCSV) {
        cerr << "No se pudo abrir el archivo CSV." << endl;
        return false;
    }

    string linea;
    // Leer el archivo línea por línea
    while (getline(archivoCSV, linea)) {
        stringstream ss(linea);
        string id, usuario, contrasena, edad;

        // Separar los campos usando la coma como delimitador
        getline(ss, id, ',');
        getline(ss, usuario, ',');
        getline(ss, contrasena, ',');
        getline(ss, edad, ',');

        // Comparar el nombre de usuario con el parámetro
        if (usuario == nombre_usuario) {
            archivoCSV.close();
            return true; // Usuario encontrado
        }
    }

    // Cerrar el archivo
    archivoCSV.close();

    // Si no se encuentra el usuario, devolver false
    return false;
}