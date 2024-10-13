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

using namespace std;

// Declaraciones previas

void pushPilaLaptops(PilaLaptops *pila, Laptop *laptop);
Laptop *topPilaLaptops(PilaLaptops *pila);
int sizePilaLaptops(PilaLaptops *pila);
void popPilaLaptops(PilaLaptops *pila);
void mostrarPilaLaptops(PilaLaptops *pila);
void guardar_CSV(PilaLaptops *pila, string nombreArchivo);
void leerLaptopsCSV(PilaLaptops *pila, string nombreArchivo);

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
    if (pila->cima != NULL)
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
    system("CLS");
    estructura_menu();
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
    color(7);

    int contador = 0;

    while (actual != nullptr)
    {
        gotoxy(20, 16 + contador);
        cout << actual->laptop.id_laptop;
        gotoxy(26, 16 + contador);
        if (actual->laptop.id_cliente != 0)
        {
            // Debe buscar el nombre del cliente en el cvs de clientes
            // Un cliente solo puede tener una laptop
            cout << "Andre Cuenca";
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

}

// Completo
void gestionLaptops_registrarLaptop()
{
    PilaLaptops *pila = new PilaLaptops();
    leerLaptopsCSV(pila, "laptops.csv");
    char respuesta[10];
    int aux = 1;
    do
    {
        system("CLS");
        estructura_menu();
        Laptop *laptop = new Laptop();

        laptop->id_laptop = contarFilasCSV("laptops.csv") + aux;
        aux++;
        laptop->id_cliente = 0;
        laptop->estado = 1;
        gotoxy(51, 12);
        color(2);
        cout << "Registro de Laptop: ";
        color(7);
        gotoxy(36, 14);
        color(2);
        cout << "Marca de la Laptop: ";
        color(7);
        getline(cin, laptop->marca);
        gotoxy(36, 15);
        color(2);
        cout << "Modelo de la Laptop: ";
        color(7);
        getline(cin, laptop->modelo);

        pushPilaLaptops(pila, laptop);
        gotoxy(36, 24);
        color(2);
        cout << "Desea registrar otra laptop? (s/n): ";
        color(7);
        cin >> respuesta;
        cin.ignore();

    } while (respuesta[0] == 's' || respuesta[0] == 'S');

    limpiarCSV("laptops.csv");
    guardar_CSV(pila, "laptops.csv");
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

        // Suponiendo que el CSV tiene los campos en el siguiente orden:
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
    system("CLS");
    mostrarPilaLaptops(pila);

    int idCliente;
    int tamanoDespues;
    int tamanoAntes = sizePilaLaptops(pila);
    Laptop laptopsPrestadas[tamanoAntes] = {};
    gotoxy(35, 27);
    color(2);
    cout << "ID del cliente que solicita una Laptop: ";
    color(7);
    cin >> idCliente;

    NodoLaptops *actual = pila->cima;
    int contador = 0;
    while (actual != nullptr && actual->laptop.estado != 0)
    {
        if (actual->laptop.estado == 1)
        {
            actual->laptop.id_cliente = idCliente;
            actual->laptop.estado = 2;
            laptopsPrestadas[contador] = actual->laptop;
            popPilaLaptops(pila);
            tamanoDespues = sizePilaLaptops(pila);
            break;
        }
        laptopsPrestadas[contador] = actual->laptop;
        contador++;
        popPilaLaptops(pila);
        actual = pila->cima;
        tamanoDespues = sizePilaLaptops(pila);
    }
    if (tamanoDespues == 0)
    {
        gotoxy(30, 27);
        color(4);
        cout << "              No hay laptops disponibles...            ";
        color(7);
        getch();
    }
    else
    {
        for (int i = tamanoAntes - tamanoDespues - 1; i >= 0; i--)
        {
            pushPilaLaptops(pila, &laptopsPrestadas[i]);
        }

        mostrarPilaLaptops(pila);
        limpiarCSV("laptops.csv");
        guardar_CSV(pila, "laptops.csv");
    } 
}

void devolverLaptop(PilaLaptops *pila)
{
    system("CLS");
    mostrarPilaLaptops(pila);

    int idCliente;
    int tamanoDespues;
    int tamanoAntes = sizePilaLaptops(pila);
    Laptop laptopsPrestadas[tamanoAntes] = {};  // Arreglo temporal para almacenar laptops
    gotoxy(35, 27);
    color(2);
    cout << "ID del cliente que devuelve una Laptop: ";
    color(7);
    cin >> idCliente;

    NodoLaptops *actual = pila->cima;
    int contador = 0;
    bool encontrado = false;  // Bandera para verificar si se encontró el cliente

    // Recorremos la pila buscando la laptop prestada por el cliente
    while (actual != nullptr)
    {
        if (actual->laptop.id_cliente == idCliente && actual->laptop.estado == 2) // Cliente correcto y laptop prestada
        {
            // Cambiar el estado de la laptop a disponible (estado = 1) y eliminar el ID del cliente
            actual->laptop.estado = 1;
            actual->laptop.id_cliente = 0;
            encontrado = true;  // Se encontró el cliente
            break;  // Salimos del ciclo, ya que no necesitamos seguir buscando
        }

        // Si no es la laptop del cliente, la guardamos temporalmente
        laptopsPrestadas[contador] = actual->laptop;
        contador++;
        popPilaLaptops(pila);  // Sacar laptop de la pila
        actual = pila->cima;   // Actualizar puntero a la nueva cima
    }

    tamanoDespues = sizePilaLaptops(pila);  // Tamaño después de las operaciones

    // Si no se encontró la laptop prestada por el cliente
    if (!encontrado)
    {
        gotoxy(30, 27);
        color(4);
        cout << "No coincide con ningun ID de cliente...";
        color(7);
    }

    // Devolver las laptops no relacionadas a la pila
    for (int i = contador - 1; i >= 0; i--)
    {
        pushPilaLaptops(pila, &laptopsPrestadas[i]);
    }

    mostrarPilaLaptops(pila);  // Mostrar el estado actualizado de la pila
    limpiarCSV("laptops.csv");  // Limpiar el archivo CSV
    guardar_CSV(pila, "laptops.csv");  // Guardar el nuevo estado de la pila en el CSV
}

