#pragma once
#include <string.h>
#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Usuarios
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

// Libros
struct Libro
{
    string nombre_Libro, Autor, Genero, estado;
    int id, Ano, Stock_Inventario, StockActual;
    float precio;
};
struct nodoLibros
{
    Libro libro;
    nodoLibros *siguiente;
    nodoLibros(Libro libro1) : libro(libro1), siguiente(nullptr) {}
};  
struct ListaLibros
{
    nodoLibros *cabeza;
    int longitud;
    ListaLibros() : cabeza(nullptr) {} // Inicializar cabeza a nullptr
};

// Pedidos (libros)

// Laptops

// Compras (libros)

// Cambios (en libros)
struct nodoDobleLibros
{
    Libro libro;
    nodoDobleLibros *siguiente;
    nodoDobleLibros *anterior;
    nodoDobleLibros(Libro libro1) : libro(libro1), siguiente(nullptr) {}
};  

struct ListaDobleLibros
{
    nodoDobleLibros *cabeza;
    nodoDobleLibros *final;
    int longitud;
    ListaDobleLibros() : cabeza(nullptr), final(nullptr) {} // Inicializar cabeza a nullptr
};