#pragma once
#include <string.h>
#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Usuario
{
    int tipo;          // 2, 1 ó 0 (Administrador, recepcionista o cliente)
    string ID_Usuario; // DNI
    int estadoUsuario; // 1 = Activo, 0 = Inactivo
    string usuario;
    string contrasena;
    string nombre;
    string apellidos;
    char genero; // F o M
    string correoElectronico;
    string telefono; // 9 dígitos
    // Para los clientes
    string membresia;    // 1 = Activa, 0 = Inactiva
    string fechaInicio;  // fecha de inicio de membresia
    string fechaFinal;   // fecha de fin de membresia
    int librosPrestados; // Máximo 3 por cliente
};

struct Nodo
{
    Usuario usuario;
    Nodo *siguiente;
    Nodo(Usuario usuario1) : usuario(usuario1), siguiente(nullptr) {}
};

struct Lista
{
    Nodo *cabeza;
    int longitud;
    Lista() : cabeza(nullptr) {} // Inicializar cabeza a nullptr
};

void leerUsuariosCSV(string nombreArchivo, Lista &lista); // Declaración previa

// Función para insertar un usuario en la lista
void insertar(Lista &lista, Usuario nuevoUsuario)
{
    Nodo *nuevoNodo = new Nodo(nuevoUsuario);
    nuevoNodo->siguiente = lista.cabeza;
    lista.cabeza = nuevoNodo;
    lista.longitud++;
}

// Función para mostrar los usuarios en la lista
void mostrar(Lista &lista)
{
    Nodo *actual = lista.cabeza;
    int contador = 0;
    gotoxy(50, 12);
    color(2);
    cout << "Lista de usuarios";
    gotoxy(20, 14);
    cout << "ID";
    gotoxy(33, 14);
    cout << "Nombre";
    gotoxy(54, 14);
    cout << "Apellidos";
    gotoxy(74, 14);
    cout << "Usuario";
    color(7);
    while (actual != nullptr)
    {

        gotoxy(20, 16 + contador);
        cout << actual->usuario.ID_Usuario;
        gotoxy(33, 16 + contador);
        cout << actual->usuario.nombre;
        gotoxy(54, 16 + contador);
        cout << actual->usuario.apellidos;
        gotoxy(74, 16 + contador);
        cout << actual->usuario.usuario;

        actual = actual->siguiente;
        contador++;
    }
    system("PAUSE>0");
}

void guardar_CSV(Lista *lista, string nombreArchivo)
{
    fstream archivo(nombreArchivo, ios::out | ios::app);

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo. " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        system("PAUSE");
        return;
    }

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    // Recorre la lista enlazada y escribe cada nodo en el archivo
    Nodo *actual = lista->cabeza;
    while (actual != nullptr)
    {
        cout << "estoy datos en el archivo .csv";
        system("PAUSE");
        Usuario usuario = actual->usuario;
        if(usuario.tipo == 0){
            usuario.membresia = "INACTIVA";
        }else{
            usuario.membresia = "ACTIVA";
        }
        
        usuario.fechaInicio = "00/00/0000";
        usuario.fechaFinal = "00/00/0000";
        usuario.librosPrestados = 0;
        archivo << usuario.estadoUsuario << "," << usuario.tipo << "," << usuario.ID_Usuario << "," << usuario.usuario << "," << usuario.contrasena << "," << usuario.nombre << "," << usuario.apellidos << "," << usuario.genero << ","
                << usuario.correoElectronico << "," << usuario.telefono << "," << usuario.membresia << "," << usuario.librosPrestados << "," << usuario.fechaFinal << "," << usuario.fechaInicio << "\n";

        actual = actual->siguiente;
    }

    archivo.close();
    cout << "Datos guardados en " << nombreArchivo << endl;
}

// Función para leer el CSV y llenar la lista enlazada
Lista leerUsuariosCSV(string nombreArchivo)
{
    Lista listaDeUsuarios;

    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo. " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        system("PAUSE");
        return listaDeUsuarios;
    }

    if (archivo.is_open())
    {
        // Leer el archivo línea por línea
        while (getline(archivo, linea))
        {
            stringstream ss(linea);
            string dato;

            Usuario usuario;

            // Suponiendo que el CSV tiene los campos en el siguiente orden:
            // estado, tipo, id_usuario (dni), usuario, contrasena, nombre, apellidos, genero, correo electronico, telefono, membresia, fecha inicio, fecha fin, libros prestados
            getline(ss, dato, ',');
            usuario.estadoUsuario = stoi(dato); // Convertir a entero

            getline(ss, dato, ',');
            usuario.tipo = stoi(dato); // Convertir a entero
            getline(ss, usuario.ID_Usuario, ',');
            getline(ss, usuario.usuario, ',');
            getline(ss, usuario.contrasena, ',');
            getline(ss, usuario.nombre, ',');
            getline(ss, usuario.apellidos, ',');

            getline(ss, dato, ',');
            usuario.genero = dato[0]; // Solo tomar el primer carácter

            getline(ss, usuario.correoElectronico, ',');
            getline(ss, usuario.telefono, ',');

            getline(ss, usuario.membresia, ',');
            getline(ss, usuario.fechaInicio, ',');
            getline(ss, usuario.fechaFinal, ',');
            getline(ss, dato, ',');
            usuario.librosPrestados = stoi(dato); // Convertir a entero

            // Insertar el usuario en la lista enlazada
            insertar(listaDeUsuarios, usuario);
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
    return listaDeUsuarios;
}