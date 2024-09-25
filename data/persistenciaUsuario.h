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

    // Función para insertar un usuario en la lista
    void insertar(Lista &lista, Usuario nuevoUsuario) {
        Nodo *nuevoNodo = new Nodo(nuevoUsuario);
        nuevoNodo->siguiente = lista.cabeza;
        lista.cabeza = nuevoNodo;
        lista.longitud++;
    }

    // Función para mostrar los usuarios en la lista
    void mostrar(Lista &lista) {

        Nodo *actual = lista.cabeza;
        while (actual != nullptr) {
            cout << "ID: " << actual->usuario.ID_Usuario << ", Nombre: " 
                 << actual->usuario.nombre << " " << actual->usuario.apellidos 
                 << ", Usuario: " << actual->usuario.usuario << endl;
            actual = actual->siguiente;
        }
    }

void guardar_CSV(Lista *lista, string nombreArchivo)
{
    fstream archivo(nombreArchivo, fstream::out | fstream::app);

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    // Recorre la lista enlazada y escribe cada nodo en el archivo
    Nodo *actual = lista->cabeza;
    while (actual != nullptr)
    {
        Usuario usuario = actual->usuario;
        archivo << usuario.estadoUsuario << ","
                << usuario.tipo << ","
                << usuario.ID_Usuario << ","
                << usuario.estadoUsuario << ","
                << usuario.usuario << ","
                << usuario.contrasena << ","
                << usuario.nombre << ","
                << usuario.apellidos << ","
                << usuario.genero << ","
                << usuario.correoElectronico << ","
                << usuario.telefono << "\n";

        actual = actual->siguiente;
    }

    archivo.close();
    cout << "Datos guardados en " << nombreArchivo << endl;
}

// Función para leer el CSV y llenar la lista enlazada
void leerCSV(string nombreArchivo, Lista &lista) {
    ifstream archivo(nombreArchivo);
    string linea;
    
    if (archivo.is_open()) {
        // Leer el archivo línea por línea
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string dato;

            Usuario usuario;

            // Suponiendo que el CSV tiene los campos en el siguiente orden:
            // tipo, ID_Usuario, estadoUsuario, usuario, contrasena, nombre, apellidos, genero, correoElectronico, telefono
            
            getline(ss, dato, ',');
            usuario.tipo = stoi(dato); // Convertir a entero

            getline(ss, usuario.ID_Usuario, ',');

            getline(ss, dato, ',');
            usuario.estadoUsuario = stoi(dato); // Convertir a entero

            getline(ss, usuario.usuario, ',');
            getline(ss, usuario.contrasena, ',');
            getline(ss, usuario.nombre, ',');
            getline(ss, usuario.apellidos, ',');

            getline(ss, dato, ',');
            usuario.genero = dato[0]; // Solo tomar el primer carácter

            getline(ss, usuario.correoElectronico, ',');
            getline(ss, usuario.telefono, ',');

            // Insertar el usuario en la lista enlazada
            insertar(lista, usuario);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
}