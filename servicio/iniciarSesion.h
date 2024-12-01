#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../menu/gotoxy.h"

using namespace std;

bool verificarUsuarioEnCSV(const string &nombre_usuario);
bool verificarContrasena(const string &usua, const string &contrasena, int &tipo, bool &estados, int &dni);
bool verificacionInicioSesion(string nombre_usuario, string contraseña_usuario, int &tipo, int &dni);
int stringAInt(const string &texto);

void inicioSesion(int &tipo, bool &sesion, int &id)
{

    string nombre, contra, respuesta;

    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 11, 26);
    gotoxy(52, 12);
    setTextColor(2);
    cout << "Inicio de sesion";
    gotoxy(36, 14);
    // Ingresamos usuario
    cout << "Usuario: ";
    setTextColor(0);
    getline(cin, nombre);
    gotoxy(36, 15);
    setTextColor(2);
    // Ingresamos contraseña
    cout << "Contraseña: ";
    setTextColor(0);
    // Captura de contraseña con asteriscos
    char caracter;
    caracter = getch(); // Espera a que el usuario presione una tecla
    contra = "";

    while (caracter != 13) // 13 es el código ASCII para Enter
    {
        if (caracter == 8) // 8 es el código ASCII para Backspace
        {
            if (contra.size() > 0)
            {
                contra.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            contra.push_back(caracter);
            cout << "*";
        }
        caracter = getch();
    }

    sesion = verificacionInicioSesion(nombre, contra, tipo, id);

    if (sesion)
    {
        gotoxy(36, 17);
        setTextColor(2);
        cout << "Inicio de Sesion exitoso!" << endl;
        pausa();
        ejecutarGradienteDoble(150);
    }
}

bool verificacionInicioSesion(string nombre_usuario, string contraseña_usuario, int &tipo, int &dni)
{
    // Verificando con los puntitos
    dibujarTextoPuntos(36, 17, "Verificando");
    bool taActivo = false;
    // Debo determinar si Existe
    if (verificarUsuarioEnCSV(nombre_usuario))
    {
        gotoxy(36, 17);
        // cout << "Buscando..." << endl;
        if (verificarContrasena(nombre_usuario, contraseña_usuario, tipo, taActivo, dni))
        {

            if (taActivo)
            {
                gotoxy(36, 19);
                // cout << "Inicio Sesion con Exito" << endl;
                return true;
            }
            else
            {
                gotoxy(36, 19);
                // cout << "Usuario no Activo" << endl;
            }
        }
        else
        {
            gotoxy(36, 17);
            color(4);
            cout << "Contraseña o Usuario Incorrecto" << endl;
            color(7);
            pausa();
        }
    }
    else
    {
        gotoxy(36, 17);
        color(4);
        cout << "Usuario No Existente" << endl;
        color(7);
        pausa();
    }
    return false;
}

bool verificarUsuarioEnCSV(const string &nombre_usuario)
{
    ifstream archivoCSV("output/usuarios.csv");

    // Verificar si el archivo se abrió correctamente
    if (!archivoCSV)
    {
        // cerr << "No se pudo abrir el archivo CSV." << endl;
        return false;
    }

    string linea;
    // Leer el archivo línea por línea
    while (getline(archivoCSV, linea))
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

        // Comparar el nombre de usuario con el parámetro
        if (usuario == nombre_usuario)
        {
            archivoCSV.close();
            return true; // Usuario encontrado
        }
    }

    // Cerrar el archivo
    archivoCSV.close();

    // Si no se encuentra el usuario, devolver false
    return false;
}

bool verificarContrasena(const string &usua, const string &contrasena, int &tipos, bool &estados, int &dni)
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
        string id, estado, tipo, dnis, usuario, clave, nombreArchivo, apellido, genero, correo, telefono;

        // Leer los campos separados por comas
        getline(ss, estado, ',');
        getline(ss, tipo, ',');
        getline(ss, dnis, ',');
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
                dni = stringAInt(dnis);
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