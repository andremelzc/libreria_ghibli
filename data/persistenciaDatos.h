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

  bool operator<=(const fecha& other) const {
        if (año < other.año) return true;
        if (año > other.año) return false;
        if (mes < other.mes) return true;
        if (mes > other.mes) return false;
        return dia <= other.dia;
    }
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
    int numeroCastigos; // Número de castigos
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
    int id;
    string nombre_Libro;
    string Autor;
    int Ano;
    string Genero;
    float precio;
    string estado;
    int stock;
    int StockInventario, StockActual;
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

struct LibroNodoArbol
{
    Libro libro;
    LibroNodoArbol *izquierda;
    LibroNodoArbol *derecha;
    LibroNodoArbol(Libro libro1) : libro(libro1), izquierda(nullptr), derecha(nullptr) {}
};


// Pedidos (libros)
struct Pedidos{
    int ID_pedido,ID_libro,ID_usuario;
    string estadoPedido; //SOLICITADO, PRESTADO, NO_DEVUELTO, DEVUELTO, DEVUELTO_TARDE
    fecha fechaPedido, fechaAdquisicion, devolucion, entregado;
    int ID_recepcionistaEntrega, ID_recepcionistaRecibe;
    int evaluacion;
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

struct ColaPedidos{
    NodoPedidos *delante;
    NodoPedidos *atras;
    ColaPedidos(): delante(nullptr), atras(nullptr){};
};

//Carrito de Compras
struct Carritos{
    int id_carrito;
    int id_cliente;
    int id_producto;
    string fecha;
    int cantidad;
    int estado;
};

struct NodoCarritos{
    Carritos carrito;
    NodoCarritos *sgte;
    NodoCarritos(Carritos carrito1) : carrito(carrito1), sgte(nullptr) {};//Constructor para que sea por default
    NodoCarritos():sgte(nullptr){};
};

struct ListaCarritos{
    int longitud;
    NodoCarritos *head;
    ListaCarritos(): head(nullptr), longitud(0) {};
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

struct NodoLibroSimple {
    int idLibro;                // ID del libro
    NodoLibroSimple* siguiente; // Puntero al siguiente nodo
};

// Cola de libros
struct ColaLibros {
    NodoLibroSimple* frente;    // Frente de la cola
    NodoLibroSimple* final;     // Final de la cola

    // Constructor
    ColaLibros() : frente(nullptr), final(nullptr) {}


};

// Nodo para la cola de clientes
struct NodoCliente {
    int dni;                // DNI del cliente
    ColaLibros libros;      // Cola de libros asociados
    NodoCliente* siguiente; // Puntero al siguiente nodo
};

// Cola de clientes
struct ColaClientes {
    NodoCliente* frente;    // Frente de la cola
    NodoCliente* final;     // Final de la cola

    // Constructor
    ColaClientes() : frente(nullptr), final(nullptr) {}


};

// Ganancia
struct Ganancia{
    int id_usuario;
    string origen;
    float monto;
    string fecha;
};

struct NodoGanancia{
    Ganancia ganancia;
    NodoGanancia *sgte;
    NodoGanancia(Ganancia ganancia1): ganancia(ganancia1), sgte(nullptr) {}; 
    NodoGanancia(): sgte(nullptr) {}; 
};

struct ListaGanancias{
    int longitud;
    NodoGanancia *head;
    ListaGanancias(): head(nullptr), longitud(0) {}; 
};

// Incidencia
struct Incidencia{
    int id_incidencia;
    int id_recepcionista;
    int id_usuario;
    string tipo;
    string descripcion;
    string fecha;
};

struct NodoIncidencia{
    Incidencia incidencia;
    NodoIncidencia *sgte;
    NodoIncidencia(Incidencia incidencia1): incidencia(incidencia1), sgte(nullptr) {}; 
    NodoIncidencia(): sgte(nullptr) {}; 
};


struct ListaIncidencias{
    int longitud;
    NodoIncidencia *head;
    ListaIncidencias(): head(nullptr), longitud(0) {}; 
};