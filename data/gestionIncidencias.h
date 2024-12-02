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


using namespace std;

void insertarFinalIncidencias(ListaIncidencias *lista, Incidencia *incidencia)
{
    NodoIncidencia *nodo = new NodoIncidencia(*incidencia);

    if (lista->head == nullptr)
    {
        lista->head = nodo;
    }
    else
    {
        NodoIncidencia *puntero = lista->head;
        while (puntero->sgte)
        {
            puntero = puntero->sgte;
        }
        puntero->sgte = nodo;
    }
    lista->longitud++;
}

ListaIncidencias cargarCSVtoIncidencias(string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    string linea;
    ListaIncidencias lista;
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
        Incidencia incidencia;

        getline(ss, dato, ',');
        incidencia.id_incidencia = stoi(dato);
        getline(ss, dato, ',');
        incidencia.id_recepcionista = stoi(dato);
        getline(ss, dato, ',');
        incidencia.id_usuario = stoi(dato);
        getline(ss, dato, ',');
        incidencia.id_libro = stoi(dato);
        getline(ss, incidencia.tipo, ',');
        getline(ss, incidencia.descripcion, ',');
        getline(ss, incidencia.fecha, ',');

        insertarFinalIncidencias(&lista, &incidencia);
    }

    archivo.close();
    return lista;
}

void guardarCSVIncidencias(ListaIncidencias *lista, string nombreArchivo)
{
    ofstream archivo(nombreArchivo, ios::out | ios::app);

    if (!archivo.is_open())
    {
        cerr << "Error: No se pudo abrir el archivo '" << nombreArchivo << "'" << endl;
        return;
    }

    NodoIncidencia *puntero = lista->head;
    while (puntero != nullptr)
    {
        archivo << puntero->incidencia.id_incidencia << ","
                << puntero->incidencia.id_recepcionista << ","
                << puntero->incidencia.id_usuario << ","
                << puntero->incidencia.id_libro << ","
                << puntero->incidencia.tipo << ","
                << puntero->incidencia.descripcion << ","
                << puntero->incidencia.fecha << endl;
        puntero = puntero->sgte;
    }

    archivo.close();
}