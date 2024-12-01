#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>


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
        // id, nombre_Libro, Autor, Ano, Genero, stock, Precio, Estado
        getline(ss, dato, ',');           // Leer el ID
        getline(ss, tituloLibro, ',');    // Leer el título del libro
        getline(ss, dato, ',');           // Leer el autor
        getline(ss, dato, ',');           // Leer el año
        getline(ss, dato, ',');           // Leer el género
        getline(ss, dato, ',');           // Leer el precio
        getline(ss, estadoLibro, ',');    // Leer el estado

        // Comparar el título del libro con el título buscado y verificar si está disponible
        if (tituloLibro == titulo && estadoLibro == "Disponible")
        {
            contador++;
        }
    }

    // Cerrar el archivo
    archivoCSV.close();

    return contador; // Devuelve el número de filas que cumplen con el criterio
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

// Función para convertir un string a minúsculas
string convertirAMinuscula(const string& str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

fecha obtenerFechaActual()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Asignar la fecha actual al objeto fecha
    fecha fechaActual;
    fechaActual.dia = ltm->tm_mday;
    fechaActual.mes = 1 + ltm->tm_mon;     // Meses comienzan desde 0, por lo tanto se suma 1
    fechaActual.año = 1900 + ltm->tm_year; // Año empieza desde 1900, por lo tanto se suma 1900

    return fechaActual;
}

fecha sumarDiasAFecha(fecha fechaOriginal, int diasASumar) {

    tm ltm = {};
    ltm.tm_mday = fechaOriginal.dia;
    ltm.tm_mon = fechaOriginal.mes - 1; // Meses comienzan desde 0
    ltm.tm_year = fechaOriginal.año - 1900; // Año empieza desde 1900

    // Convertir a time_t
    time_t tiempo = mktime(&ltm);

    // Sumar los días en segundos
    tiempo += diasASumar * 24 * 60 * 60;

    // Convertir de nuevo a tm
    ltm = *localtime(&tiempo);

    // Asignar la nueva fecha
    fecha nuevaFecha;
    nuevaFecha.dia = ltm.tm_mday;
    nuevaFecha.mes = ltm.tm_mon + 1;
    nuevaFecha.año = ltm.tm_year + 1900;

    return nuevaFecha;
}

int calcularDiasEntreFechas(int anio1, int mes1, int dia1, int anio2, int mes2, int dia2)
{
    // Estructura tm para la primera fecha
    tm fecha1 = {};
    pausa();
    fecha1.tm_year = anio1 - 1900; // tm_year es años desde 1900
    fecha1.tm_mon = mes1 - 1;      // tm_mon es de 0 a 11
    fecha1.tm_mday = dia1;

    // Estructura tm para la segunda fecha
    tm fecha2 = {};
    fecha2.tm_year = anio2 - 1900;
    fecha2.tm_mon = mes2 - 1;
    fecha2.tm_mday = dia2;

    // Convertir las fechas a tiempo en segundos desde la época
    time_t tiempo1 = mktime(&fecha1);
    time_t tiempo2 = mktime(&fecha2);

    // Calcular la diferencia en segundos y convertirla a días
    double diferenciaSegundos = difftime(tiempo2, tiempo1);
    int diferenciaDias = diferenciaSegundos / (60 * 60 * 24); // Convierte de segundos a días

    return abs(diferenciaDias); // Valor absoluto de la diferencia en días
}

// Función para verificar si una cadena contiene solo letras y espacios
bool esSoloLetras(const string &s)
{
    for (char c : s)
    {
        if (!isalpha(c) && c != ' ')
        {
            return false;
        }
    }
    return true;
}

// Funcion para verificar si una cadena contiene solo numeros
bool esSoloNumeros(const string &s)
{
    for (char c : s)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

// Función para verificar si el correo electrónico es válido
bool esCorreoValido(const string &correo)
{
    // Verificar si el correo contiene un solo '@'
    size_t posArroba = correo.find('@');
    if (posArroba == string::npos || correo.find('@', posArroba + 1) != string::npos)
    {
        return false;
    }

    // Verificar si el correo contiene un punto después de la arroba
    size_t posPunto = correo.find('.', posArroba);
    if (posPunto == string::npos)
    {
        return false;
    }

    return true;
}

// Funcion para convertir un int a string
string intToString(int num)
{
    stringstream ss;
    ss << num;
    return ss.str();
}