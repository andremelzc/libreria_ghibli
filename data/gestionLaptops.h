#pragma once
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <conio.h>
#include "gestionUsuarios.h"
using namespace std;

// Declaraciones previas

void pushPilaLaptops(PilaLaptops *pila, Laptop *laptop);
Laptop *topPilaLaptops(PilaLaptops *pila);
int sizePilaLaptops(PilaLaptops *pila);
void popPilaLaptops(PilaLaptops *pila);
void mostrarPilaLaptops(PilaLaptops *pila);
void guardar_CSV(PilaLaptops *pila, string nombreArchivo);
void leerLaptopsCSV(PilaLaptops *pila, string nombreArchivo);
void restaurarLaptop(PilaLaptops *pila);
void marcarLaptopFueraServicio(PilaLaptops *pila);

// Completo
void pushPilaLaptops(PilaLaptops *pila, Laptop *laptop)
{
    NodoLaptops *nodo = new NodoLaptops(*laptop);
    nodo->siguiente = pila->cima;
    pila->cima = nodo;
    pila->longitud++;
}

// Completo
Laptop *topPilaLaptops(PilaLaptops *pila)
{
    if (pila->cima == nullptr)
    {
        return nullptr;
    }
    else
    {
        return &pila->cima->laptop;
    }
}

// Completo
int sizePilaLaptops(PilaLaptops *pila)
{
    return pila->longitud;
}

// Completo
void popPilaLaptops(PilaLaptops *pila)
{
    if (pila->cima != nullptr)
    {
        NodoLaptops *eliminado = pila->cima;
        pila->cima = pila->cima->siguiente;
        delete (eliminado);
        pila->longitud--;
    }
}

// Completo
void mostrarPilaLaptops(PilaLaptops *pila)
{
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    
    Lista listaUsuarios = leerUsuariosCSV("output/usuarios.csv");
    NodoLaptops *actual = pila->cima;
    gotoxy(50, 12);
    color(2);
    cout << "Listado de laptops";
    gotoxy(20, 14);
    cout << "ID";
    gotoxy(26, 14);
    cout << "Cliente Asignado";
    gotoxy(48, 14);
    cout << "Marca";
    gotoxy(62, 14);
    cout << "Modelo";
    gotoxy(84, 14);
    cout << "Estado";
    color(0);

    int contador = 0;

    while (actual != nullptr)
    {
        gotoxy(20, 16 + contador);
        cout << actual->laptop.id_laptop;
        gotoxy(26, 16 + contador);
        if (actual->laptop.id_cliente != 0)
        {
            Nodo *actualUsuario = listaUsuarios.cabeza;
            while (actualUsuario != nullptr)
            {
                if (stoi(actualUsuario->usuario.ID_Usuario) == actual->laptop.id_cliente && actualUsuario->usuario.tipo == 0)
                {
                    string nombreCompleto = actualUsuario->usuario.nombre + " " + actualUsuario->usuario.apellidos;
                    if (nombreCompleto.length() > 20)
                    {

                        cout << nombreCompleto.substr(0, 15) << "...";
                    }
                    else
                    {
                        cout << nombreCompleto;
                    }
                }
                actualUsuario = actualUsuario->siguiente;
            }
            // Debe buscar el nombre del cliente en el cvs de clientes
            // Un cliente solo puede tener una laptop
            // cout << "Andre Cuenca";
        }
        else if (actual->laptop.id_cliente == -1)
        {
            cout << "Fuera de Servicio";
        }
        else
        {
            cout << "Sin cliente";
        }

        gotoxy(48, 16 + contador);
        if (actual->laptop.marca.length() > 20)
        {
            cout << actual->laptop.marca.substr(0, 15) << "...";
        }
        else
        {
            cout << actual->laptop.marca;
        }
        gotoxy(62, 16 + contador);
        if (actual->laptop.modelo.length() > 20)
        {
            cout << actual->laptop.modelo.substr(0, 13) << "...";
        }
        else
        {
            cout << actual->laptop.modelo;
        }
        gotoxy(84, 16 + contador);
        if (actual->laptop.estado == 1)
        {
            cout << "No Prestado";
        }
        else if (actual->laptop.estado == 2)
        {
            cout << "Prestado";
        }
        else
        {
            cout << "Fuera de servicio";
        }

        actual = actual->siguiente;

        contador++;
    }
    system("pause>0");
}

// Completo
void gestionLaptops_registrarLaptop()
{
    PilaLaptops *pila = new PilaLaptops();
    leerLaptopsCSV(pila, "output/laptops.csv");
    char respuesta[10];
    int aux = 1;
    do
    {
        limpiarPantalla();
        setConsoleBackground(White);
        dibujarTitulo(27, 0, 2, letras);
        estructura_menu2(16, 103, 10, 27);
        Laptop *laptop = new Laptop();

        laptop->id_laptop = contarFilasCSV("output/laptops.csv") + aux;
        aux++;
        laptop->id_cliente = 0;
        laptop->estado = 1;
        gotoxy(51, 12);
        color(2);
        cout << "Registro de Laptop: ";
        color(0);
        gotoxy(36, 14);
        color(2);
        cout << "Marca de la Laptop: ";
        color(0);
        getline(cin, laptop->marca);
        gotoxy(36, 15);
        color(2);
        cout << "Modelo de la Laptop: ";
        color(0);
        getline(cin, laptop->modelo);

        pushPilaLaptops(pila, laptop);
        gotoxy(36, 24);
        color(2);
        cout << "Desea registrar otra laptop? (s/n): ";
        color(0);
        cin >> respuesta;
        cin.ignore();

        dibujarTextoPuntos(36, 26, "Registrando laptop");
        gotoxy(36, 26);
        cout << "Laptop registrada con exito!";

    } while (respuesta[0] == 's' || respuesta[0] == 'S');

    limpiarCSV("output/laptops.csv");
    guardar_CSV(pila, "output/laptops.csv");
}

// Completo
void guardar_CSV(PilaLaptops *pila, string nombreArchivo)
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
    NodoLaptops *actual = pila->cima;
    while (actual != nullptr)
    {
        // cout << "estoy datos en el archivo .csv";
        // system("PAUSE");
        Laptop laptop = actual->laptop;
        archivo << laptop.id_laptop << ","
                << laptop.id_cliente << ","
                << laptop.marca << ","
                << laptop.modelo << ","
                << laptop.estado << "\n";

        actual = actual->siguiente;
    }

    archivo.close();
}

// Completo
void leerLaptopsCSV(PilaLaptops *pila, string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    string linea;
    vector<string> lineas; // Almacenar las líneas del archivo

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo. " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        system("PAUSE");
        return;
    }

    // Leer el archivo y almacenar cada línea en el vector "lineas"
    while (getline(archivo, linea))
    {
        lineas.push_back(linea); // Agregar cada línea al vector
    }

    archivo.close(); // Cerrar el archivo una vez que todas las líneas se han leído

    // Recorrer las líneas en orden inverso (de abajo hacia arriba)
    for (int i = lineas.size() - 1; i >= 0; i--)
    {
        stringstream ss(lineas[i]);
        string dato;

        // Crear un puntero a Laptop y asignar memoria dinámicamente
        Laptop *laptop = new Laptop;

        // id_laptop, id_cliente, marca, modelo, estado

        getline(ss, dato, ',');
        laptop->id_laptop = stoi(dato);
        getline(ss, dato, ',');
        laptop->id_cliente = stoi(dato);
        getline(ss, laptop->marca, ',');
        getline(ss, laptop->modelo, ',');
        getline(ss, dato, ',');
        laptop->estado = stoi(dato);

        // Insertar la laptop en la pila
        pushPilaLaptops(pila, laptop);
    }
}

void prestarLaptop(PilaLaptops *pila)
{
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);

    mostrarPilaLaptops(pila);

    int idCliente;
    int tamanoDespues;
    int tamanoAntes = sizePilaLaptops(pila);
    Laptop laptopsPrestadas[tamanoAntes] = {};
    Lista listaUsuarios = leerUsuariosCSV("output/usuarios.csv");

    gotoxy(35, 27);
    color(2);
    cout << "DNI del cliente que solicita una Laptop: ";
    color(0);
    cin >> idCliente;

    NodoLaptops *actual = pila->cima;
    int contador = 0;
    bool clienteEncontrado = false; // se encontró el cliente válido?

    // Verificar si el cliente es válido (existe en la lista y es tipo cliente (0))
    Nodo *actualUsuario = listaUsuarios.cabeza;
    while (actualUsuario != nullptr)
    {
        if (stoi(actualUsuario->usuario.ID_Usuario) == idCliente && actualUsuario->usuario.tipo == 0)
        {
            clienteEncontrado = true;
            break; // Salimos del bucle porque encontramos un cliente válido
        }
        actualUsuario = actualUsuario->siguiente;
    }

    if (clienteEncontrado) // Si el cliente es válido, proceder a buscar una laptop disponible
    {
        bool laptopEncontrada = false; // Variable para saber si encontramos una laptop disponible

        while (actual != nullptr)
        {
            if (actual->laptop.estado == 1) // Laptop disponible
            {
                // Asignar la laptop al cliente
                actual->laptop.id_cliente = idCliente;
                actual->laptop.estado = 2; // Cambiar estado a prestada
                laptopsPrestadas[contador] = actual->laptop;
                popPilaLaptops(pila);
                laptopEncontrada = true;
                tamanoDespues = sizePilaLaptops(pila);
                break;
            }

            // Guardar temporalmente las laptops no disponibles
            laptopsPrestadas[contador] = actual->laptop;
            contador++;
            popPilaLaptops(pila);
            actual = pila->cima;
        }

        if (!laptopEncontrada)
        {
            gotoxy(30, 27);
            color(4);
            cout << "              No hay laptops disponibles...            ";
            color(0);
            getch();
        }
        else
        {
            for (int i = tamanoAntes - tamanoDespues - 1; i >= 0; i--)
            {
                pushPilaLaptops(pila, &laptopsPrestadas[i]);
            }

            mostrarPilaLaptops(pila);
            limpiarCSV("output/laptops.csv");
            guardar_CSV(pila, "output/laptops.csv");
        }
    }
    else
    {
        // Mostrar mensaje si el DNI no pertenece a un cliente registrado o no es tipo 0
        gotoxy(30, 27);
        color(4);
        cout << "     El DNI ingresado no está registrado como cliente...";
        color(0);
        getch(); // Esperar a que el usuario presione una tecla
    }
}

void devolverLaptop(PilaLaptops *pila)
{
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);

    mostrarPilaLaptops(pila);

    int idCliente;
    int tamanoAntes = sizePilaLaptops(pila);
    Laptop laptopsPrestadas[tamanoAntes]; // Arreglo temporal para almacenar laptops

    gotoxy(35, 27);
    color(2);
    cout << "DNI del cliente que devuelve una Laptop: ";
    color(0);
    cin >> idCliente;

    NodoLaptops *actual = pila->cima;
    int contador = 0;
    bool encontrado = false; // se encontró la laptop del cliente?
    Laptop laptopDevuelta;   // Variable para almacenar la laptop devuelta

    // Recorremos la pila buscando la laptop prestada por el cliente
    while (actual != nullptr)
    {
        if (actual->laptop.id_cliente == idCliente && actual->laptop.estado == 2) // Cliente correcto y laptop prestada
        {
            // Cambiar el estado de la laptop a disponible (estado = 1) y eliminar el ID del cliente
            actual->laptop.estado = 1;
            actual->laptop.id_cliente = 0;
            laptopDevuelta = actual->laptop; // Guardamos la laptop encontrada para agregarla después
            encontrado = true;               // Se encontró la laptop del cliente
            popPilaLaptops(pila);            // Sacar la laptop de la pila
            break;                           // Salimos del ciclo ya que no necesitamos seguir buscando
        }

        // Si no es la laptop del cliente, la guardamos temporalmente
        laptopsPrestadas[contador++] = actual->laptop;
        popPilaLaptops(pila); // Sacar laptop de la pila
        actual = pila->cima;
    }
    // Devolver las laptops no relacionadas a la pila
    for (int i = contador - 1; i >= 0; i--)
    {
        pushPilaLaptops(pila, &laptopsPrestadas[i]);
    }

    // Si se encontró la laptop, agregarla al final de la pila
    if (encontrado)
    {
        pushPilaLaptops(pila, &laptopDevuelta);
    }

    mostrarPilaLaptops(pila); // Mostrar el estado actualizado de la pila
    if (!encontrado)
    {
        gotoxy(30, 27);
        color(4);
        cout << "     No coincide con ningun DNI de los clientes registrados...";
        color(0);
    }
    limpiarCSV("output/laptops.csv");        // Limpiar el archivo CSV
    guardar_CSV(pila, "output/laptops.csv"); // Guardar el nuevo estado de la pila en el CSV
}

void restaurarLaptop(PilaLaptops *pila)
{

    NodoLaptops *actualCima = pila->cima;

    // Variable para verificar si se ha cambiado el estado de alguna laptop
    bool laptopRestaurada = false;

    // Lógica para cambiar el estado de la primera laptop que está en estado 0 (fuera de servicio)
    while (actualCima != nullptr)
    {
        if (actualCima->laptop.estado == 0)
        { // Solo cambiar el estado si es 0
            // Cambiar el estado a 1 y asignar el id_cliente a 0
            actualCima->laptop.estado = 1;     // Cambiar el estado a 1
            actualCima->laptop.id_cliente = 0; // Asignar un id_cliente de 0 (Sin asignar)
            gotoxy(36, 27);
            cout << "La laptop ha sido restaurada y está ahora en servicio." << endl;
            laptopRestaurada = true; // Indicamos que se ha restaurado una laptop
            break;                   // Salimos del bucle después de restaurar una laptop
        }
        actualCima = actualCima->siguiente;
    }

    if (!laptopRestaurada)
    {
        gotoxy(36, 27);
        cout << "No hay laptops fuera de servicio para restaurar." << endl;
    }

    // Actualizar el archivo CSV después de restaurar la laptop
    limpiarCSV("output/laptops.csv");
    guardar_CSV(pila, "output/laptops.csv");

    getch();
}

void marcarLaptopFueraDeServicio(PilaLaptops *pila)
{
    NodoLaptops *actual = pila->cima;

    // Variable para verificar si se ha cambiado el estado de alguna laptop
    bool laptopMarcada = false;

    // Lógica para cambiar el estado de la primera laptop que no está en estado 2
    while (actual != nullptr)
    {
        if (actual->laptop.estado != 2 && actual->laptop.estado != 0) // si no está prestada ni fuera de servicio
        {
            actual->laptop.estado = 0;      // Cambiar el estado a 0
            actual->laptop.id_cliente = -1; // Asignar un valor especial para indicar "Fuera de Servicio"
            gotoxy(36, 27);
            cout << "La laptop ha sido marcada como fuera de servicio." << endl;
            laptopMarcada = true; // Indicamos que se ha marcado una laptop
            break;
        }
        actual = actual->siguiente;
    }

    if (!laptopMarcada)
    {
        gotoxy(36, 27);
        cout << "No hay laptops disponibles para cambiar el estado." << endl;
    }
    limpiarCSV("output/laptops.csv");
    guardar_CSV(pila, "output/laptops.csv");

    getch();
}