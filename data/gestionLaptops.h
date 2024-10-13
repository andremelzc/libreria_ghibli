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

//Completo
void pushPilaLaptops(PilaLaptops *pila, Laptop *laptop)
{
    NodoLaptops *nodo = new NodoLaptops(*laptop);
    nodo->siguiente = pila->cima;
    pila->cima = nodo;
    pila->longitud++;
}

//Completo
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

//Completo
int sizePilaLaptops(PilaLaptops *pila)
{
    return pila->longitud;
}

//Completo
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

//Completo
void mostrarPilaLaptops(PilaLaptops *pila)
{
    NodoLaptops *aux = pila->cima;
    while (aux != nullptr)
    {
        cout << "ID: " << aux->laptop.id_laptop << endl;
        cout << "Marca: " << aux->laptop.marca << endl;
        cout << "Modelo: " << aux->laptop.modelo << endl;
        cout << "Estado: " << aux->laptop.estado << endl;
        cout << "ID Cliente: " << aux->laptop.id_cliente << endl;
        cout << "-------------------" << endl;
        aux = aux->siguiente;
    }
}

//Completo
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

//Completo
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
    cout << "Datos guardados en " << nombreArchivo << endl;
}

//Completo
void leerLaptopsCSV(PilaLaptops *pila, string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    string linea;
    vector<string> lineas;  // Almacenar las líneas del archivo

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
        lineas.push_back(linea);  // Agregar cada línea al vector
    }

    archivo.close();  // Cerrar el archivo una vez que todas las líneas se han leído

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


