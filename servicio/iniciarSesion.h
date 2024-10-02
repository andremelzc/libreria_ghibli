#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../menu/gotoxy.h"

using namespace std;

bool verificarUsuarioEnCSV(const string& nombre_usuario);
bool verificarContrasena(const string &usua, const string &contrasena, int &tipo, bool &estados);
bool verificacionInicioSesion(string nombre_usuario, string contraseña_usuario, int &tipo);
int stringAInt(const string &texto);

void inicioSesion(int &tipo, bool &sesion)
{

    string nombre, contra, respuesta;

    system("CLS");
    estructura_menu();
    gotoxy(52, 12);
    color(2);
    cout << "Inicio de sesion";
    gotoxy(36, 14);
    cout << "Usuario: ";
    color(7);
    getline(cin, nombre);
    gotoxy(36, 15);
    color(2);
    cout << "Contraseña: ";
    color(7);
    getline(cin, contra);

    sesion = verificacionInicioSesion(nombre, contra, tipo);
    gotoxy(36, 19);
    system("pause");
}

bool verificacionInicioSesion(string nombre_usuario, string contraseña_usuario, int &tipo)
{
    bool taActivo = false;
    // Debo determinar si Existe
    if (verificarUsuarioEnCSV(nombre_usuario))
    {
        gotoxy(36, 17);
        cout << "Buscando..." << endl;
        if (verificarContrasena(nombre_usuario, contraseña_usuario, tipo, taActivo))
        {

            if (taActivo)
            {
                gotoxy(36, 19);
                cout << "Inicio Sesion con Exito" << endl;
                return true;
            }
            else
            {
                gotoxy(36, 19);
                cout << "Usuario no Activo" << endl;
            }
        }
        else
        {
            gotoxy(36, 19);
            cout << "Contraseña o Usuario Incorrecto" << endl;
        }
    }
    else
    {
        gotoxy(36, 17);
        cout << "Usuario No Existente" << endl;
    }
    return false;
}

bool verificarUsuarioEnCSV(const string& nombre_usuario) {
    ifstream archivoCSV("output/usuarios.csv");

    // Verificar si el archivo se abrió correctamente
    if (!archivoCSV) {
        cerr << "No se pudo abrir el archivo CSV." << endl;
        return false;
    }

    string linea;
    // Leer el archivo línea por línea
    while (getline(archivoCSV, linea)) {
        stringstream ss(linea);
        string id, estado, tipo, dni, usuario, clave, nombreArchivo, apellido, genero, correo, telefono;

        // Leer los campos separados por comas
        getline(ss, estado, ',');
        getline(ss, tipo, ',');
        getline(ss, dni, ',');
        getline(ss, usuario, ',');
        getline(ss, clave, ',');
        getline(ss, nombreArchivo, ',');
        getline(ss, apellido, ',');
        getline(ss, genero, ',');
        getline(ss, correo, ',');
        getline(ss, telefono, ',');

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

bool verificarContrasena(const string &usua, const string &contrasena, int &tipos, bool &estados)
{
    ifstream archivo("output/usuarios.csv");
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return false;
    }
    int tipoEntero = 0;
    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string id, estado, tipo, dni, usuario, clave, nombreArchivo, apellido, genero, correo, telefono;

        // Leer los campos separados por comas
        getline(ss, estado, ',');
        getline(ss, tipo, ',');
        getline(ss, dni, ',');
        getline(ss, usuario, ',');
        getline(ss, clave, ',');
        getline(ss, nombreArchivo, ',');
        getline(ss, apellido, ',');
        getline(ss, genero, ',');
        getline(ss, correo, ',');
        getline(ss, telefono, ',');

        //  contraseña
        if (usuario == usua && clave == contrasena)
        {
            tipoEntero = stringAInt(tipo);
            if (stringAInt(estado) == 1)
            {
                estados = true;
                tipos = stringAInt(tipo);
            }
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

int stringAInt(const string &texto)
{
    stringstream ss(texto);
    int numero = 0;
    ss >> numero;
    return numero;
}