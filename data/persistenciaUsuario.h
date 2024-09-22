#pragma once
#include <string.h>
#include <fstream>

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