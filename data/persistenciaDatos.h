#pragma once
#include <string.h>
#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct fecha
{
  int dia, mes, año;  
};

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

struct nodoDobleLibros
{
    Libro libro;
    nodoDobleLibros *siguiente;
    nodoDobleLibros *anterior;
    // Falta Inicializar anterior a nullptr
    nodoDobleLibros(Libro libro1) : libro(libro1), siguiente(nullptr) {}
};  

struct ListaDobleLibros
{
    nodoDobleLibros *cabeza;
    nodoDobleLibros *final;
    int longitud;
    ListaDobleLibros() : cabeza(nullptr), final(nullptr) {} // Inicializar cabeza a nullptr
};

// Pedidos (libros)
struct Pedidos{
    int ID_pedido,ID_libro,ID_usuario;
    string estadoPedido; //SOLICITADO, PRESTADO, NO_DEVUELTO, DEVUELTO, DEVUELTO_TARDE
    fecha fechaPedido, fechaAdquisicion, devolucion, entregado;
};

struct NodoPedidos{
    Pedidos pedido;
    NodoPedidos *sgte;
    NodoPedidos(Pedidos pedido1): pedido(pedido1), sgte(nullptr) {}; 
    NodoPedidos(): sgte(nullptr) {}; 
};

struct ListaPedidos{
    int longitud;
    NodoPedidos *head;
    ListaPedidos(): head(nullptr), longitud(0) {}; 
};

// Laptops
struct Laptop {
    int id_laptop;        // Identificador único de la laptop
    int id_cliente;       // Identificador del cliente que alquiló la laptop
    string marca;          // Marca de la laptop (ej: "Dell", "HP", etc.)
    string modelo; 
    int estado;          // Estado: true para "Prestado", false para "No prestado"
};

struct NodoLaptops
{
    Laptop laptop;
    NodoLaptops *siguiente;
    NodoLaptops(Laptop laptop1) : laptop(laptop1), siguiente(nullptr) {}
};

struct PilaLaptops
{
    NodoLaptops *cima;
    int longitud;
    PilaLaptops() : cima(nullptr), longitud(0) {} // Inicializar cima a nullptr
};

struct estadisticaLibro{ // para la estadistica de los libros más populares
    int id_libro, vecesSolicitado, vecesPrestado;
    string nombreLibro;
};

struct NodoEstadisticas{
    estadisticaLibro estadistica;
    NodoEstadisticas *sgte;
    int prio;

    NodoEstadisticas(estadisticaLibro stat): prio(estadistica.vecesSolicitado), estadistica(stat), sgte(nullptr){};  
};

struct colaPrioEstadisticas{
    NodoEstadisticas *delante;
    NodoEstadisticas *atras;
    
    colaPrioEstadisticas(): delante(nullptr), atras(nullptr){};

    colaPrioEstadisticas(NodoEstadisticas *primero): delante(primero), atras(primero){};
};


struct colaHistorial{
    NodoPedidos *adelante;
    NodoPedidos *atras;
 
    colaHistorial(): adelante(nullptr), atras(nullptr){};
};
