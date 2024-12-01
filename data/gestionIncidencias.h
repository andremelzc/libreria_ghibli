#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <locale>
#include <string>
#include <ctime>
#include <filesystem>
#include "..\menu\gotoxy.h"
#include "..\data\persistenciaDatos.h"

using namespace std;

void insertarFinalGanancias(ListaGanancias *lista, Ganancia *ganancia)
{
    NodoGanancia *nodo = new NodoGanancia(*ganancia);

    if (lista->head == nullptr)
    {
        lista->head = nodo;
    }
    else
    {
        NodoGanancia *puntero = lista->head;
        while (puntero->sgte)
        {
            puntero = puntero->sgte;
        }
        puntero->sgte = nodo;
    }
    lista->longitud++;
}

ListaGanancias cargarCSVtoGanancias(string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    string linea;
    ListaGanancias lista;
    lista.head = nullptr;
    lista.longitud = 0;

    if (!archivo.is_open())
    {
        cerr << "Error: No se pudo abrir el archivo '" << nombreArchivo << "'" << endl;
        return lista;
    }

    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string dato;
        Ganancia ganancia;

        getline(ss, dato, ',');
        ganancia.id_usuario = stoi(dato);
        getline(ss, ganancia.origen, ',');
        getline(ss, dato, ',');
        ganancia.monto = stof(dato);
        getline(ss, ganancia.fecha, ',');

        insertarFinalGanancias(&lista, &ganancia);
    }

    archivo.close();
    return lista;
}

void guardarGananciasCSV(ListaGanancias *lista, string nombreArchivo)
{
    fstream archivo(nombreArchivo, fstream::out | fstream::app);

    if (!filesystem::exists("output"))
    {
        cerr << "Error: El directorio 'output' no existe." << endl;
        return;
    }

    if (!archivo.is_open())
    {
        cerr << "Error: No se pudo abrir el archivo '" << nombreArchivo << "'" << endl;
        return;
    }

    NodoGanancia *actual = lista->head;
    while (actual != nullptr)
    {
        Ganancia ganancia = actual->ganancia;
        archivo << ganancia.id_usuario << ","
                << ganancia.origen << ","
                << ganancia.monto << ","
                << ganancia.fecha << "\n";

        actual = actual->sgte;
    }

    if (archivo.fail())
    {
        cerr << "Error: Fallo al escribir en el archivo." << endl;
        return;
    }

    archivo.close();
}