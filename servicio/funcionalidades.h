#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int contarFilasCSV(string nombreArchivo) {
    ifstream archivoCSV(nombreArchivo); // Abrir el archivo en modo lectura
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

