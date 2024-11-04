#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

int contarFilasCSV(string nombreArchivo)
{
    ifstream archivoCSV(nombreArchivo); // Abrir el archivo en modo lectura
    string linea;
    int contador = 0;

    // Verificar si el archivo se abrió correctamente
    if (!archivoCSV)
    {
        cerr << "No se pudo abrir el archivo CSV." << endl;
        return -1; // Devuelve -1 si no se pudo abrir el archivo
    }

    // Leer el archivo línea por línea y contar las filas
    while (getline(archivoCSV, linea))
    {
        contador++;
    }

    // Cerrar el archivo
    archivoCSV.close();

    return contador; // Devuelve el número de filas
}

int convertirCadenaAEntero(string &cadena)
{
    try
    {
        // Intentar convertir la cadena a entero
        return stoi(cadena);
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: La cadena '" << cadena << "' no es un número válido. " << e.what() << endl;
        return -1; // Valor de error o alguna forma de manejar el problema
    }
    catch (const out_of_range &e)
    {
        cerr << "Error: El número está fuera de rango. " << e.what() << endl;
        return -1; // Valor de error o alguna forma de manejar el problema
    }
}

void limpiarCSV(string nombreArchivo)
{
    ofstream archivoSalida(nombreArchivo); // Abrir el archivo en modo escritura

    // Verificar si el archivo se abrió correctamente
    if (!archivoSalida)
    {
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

string fechaAString(const fecha &f)
{
    ostringstream ss;
    ss << setw(2) << setfill('0') << f.dia << "/"
       << setw(2) << setfill('0') << f.mes << "/"
       << f.año;
    return ss.str();
}

int contarTituloLibro(string nombreArchivo, string titulo)
{
    ifstream archivoCSV(nombreArchivo); // Abrir el archivo en modo lectura
    string linea;
    int contador = 0;

    // Verificar si el archivo se abrió correctamente
    if (!archivoCSV)
    {
        cerr << "No se pudo abrir el archivo CSV." << endl;
        return -1; // Devuelve -1 si no se pudo abrir el archivo
    }

    // Leer el archivo línea por línea y contar las filas
    while (getline(archivoCSV, linea))
    {
        stringstream ss(linea);
        string dato;
        string tituloLibro;
        string estadoLibro;

        // Suponiendo que el CSV tiene los campos en el siguiente orden:
        // id, nombre_Libro,Autor,Ano,Genero,stock,Precio,Estado
        getline(ss, dato, ','); // Leer el ID
        getline(ss, tituloLibro, ','); // Leer el título del libro
        getline(ss, dato, ','); // Leer el autor
        getline(ss, dato, ','); // Leer el año
        getline(ss, dato, ','); // Leer el género
        getline(ss, dato, ','); // Leer el stock 
        getline(ss, dato, ','); // Leer el precio
        getline(ss, estadoLibro, ','); // Leer el estado

        // Comparar el título del libro con el título buscado
        if (dato == titulo && estadoLibro == "Disponible")
        {
            contador++;
        }
    }

    // Cerrar el archivo
    archivoCSV.close();

    return contador; // Devuelve el número de filas
}

bool tituloGuardado(string nombreArchivo, int id, string titulo)
{
    // Si es el primer libro, retorna falso porque no puede repetirse
    if (id == 1)
    {
        return false;
    }

    // Abrimos el archivo
    ifstream archivoCSV(nombreArchivo);
    string linea;
    string tituloCiclo;

    // Verificar si el archivo se abrió correctamente
    if (!archivoCSV)
    {
        cerr << "No se pudo abrir el archivo CSV." << endl;
        return false; // Devuelve falso si no se pudo abrir el archivo
    }

    // Leemos hasta la fila id
    for (int i = 1; i < id; i++)
    {
        if (!getline(archivoCSV, linea))
        {
            break;
        }

        stringstream ss(linea);
        string dato;

        // Leemos id - título
        getline(ss, dato, ',');
        getline(ss, tituloCiclo, ',');

        // Comparar el título del libro con el título buscado
        if (tituloCiclo == titulo)
        {
            // Si ya existe, devolvemos true
            archivoCSV.close();
            return true;
        }
    }

    archivoCSV.close();

    return false; // Retorna false si no se encontró el título
}

int distanciaLevenshtein(const std::string& s1, const std::string& s2) {
    std::vector<std::vector<int>> d(s1.size() + 1, std::vector<int>(s2.size() + 1));

    // Inicializar la matriz
    for (size_t i = 0; i <= s1.size(); ++i) {
        d[i][0] = i; // Borrados
    }
    for (size_t j = 0; j <= s2.size(); ++j) {
        d[0][j] = j; // Insertados
    }

    // Calcular la distancia
    for (size_t i = 1; i <= s1.size(); ++i) {
        for (size_t j = 1; j <= s2.size(); ++j) {
            int costo = (s1[i - 1] == s2[j - 1]) ? 0 : 1;

            int borrado = d[i - 1][j] + 1;        // Borrado
            int insercion = d[i][j - 1] + 1;      // Inserción
            int sustitucion = d[i - 1][j - 1] + costo; // Sustitución

            // Encuentra el mínimo
            d[i][j] = std::min(borrado, std::min(insercion, sustitucion));
        }
    }
    return d[s1.size()][s2.size()];
}
