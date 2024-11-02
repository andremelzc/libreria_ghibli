#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> 

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

int convertirCadenaAEntero(string& cadena) {
    try {
        // Intentar convertir la cadena a entero
        return stoi(cadena);
    } catch (const invalid_argument& e) {
        cerr << "Error: La cadena '" << cadena << "' no es un número válido. " << e.what() << endl;
        return -1; // Valor de error o alguna forma de manejar el problema
    } catch (const out_of_range& e) {
        cerr << "Error: El número está fuera de rango. " << e.what() << endl;
        return -1; // Valor de error o alguna forma de manejar el problema
    }
}

void limpiarCSV(string nombreArchivo) {
    ofstream archivoSalida(nombreArchivo); // Abrir el archivo en modo escritura

    // Verificar si el archivo se abrió correctamente
    if (!archivoSalida) {
        cerr << "No se pudo abrir el archivo CSV para escritura." << endl;
        return;
    }

    // Cerrar el archivo inmediatamente para limpiar su contenido
    archivoSalida.close();
}

fecha convertirFecha(const string &campo)
{
    stringstream ss(campo);
    string parte;
    int dia, mes, año;

    // Leer el día
    getline(ss, parte, '/');
    dia = stoi(parte);

    // Leer el mes
    getline(ss, parte, '/');
    mes = stoi(parte);

    // Leer el año
    getline(ss, parte);
    año = stoi(parte);

    // Retornar un objeto de tipo 'fecha'
    return {dia, mes, año};
}

string fechaAString(const fecha &f) {
    ostringstream ss;
    ss << setw(2) << setfill('0') << f.dia << "/"
       << setw(2) << setfill('0') << f.mes << "/"
       << f.año;
    return ss.str();
}