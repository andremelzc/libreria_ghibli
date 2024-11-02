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
#include "persistenciaDatos.h"
#include "prestamoLibro.h"
#include "..\menu\gotoxy.h"
#include "gestionUsuarios.h"

using namespace std;

void encolarHistorial(NodoPedidos *pedido, colaHistorial &q){
    if(q.adelante == nullptr){
        q.adelante = pedido;
        q.atras = pedido;
    }else{
        q.atras->sgte = pedido;
        q.atras = pedido;
    }
    
}

colaHistorial cargarHistorialxID (string nombreArchivo, int idUsuario){
    string linea;
    ifstream archivo(nombreArchivo);
    colaHistorial historial;
    
    if (!archivo.is_open()) { // Verificar si el archivo se abrió correctamente
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        system("PAUSE");

        return historial; // Regresar la lista vacía si el archivo no se pudo abrir

    }

    while(getline(archivo,linea)){
        stringstream ss(linea);
        string campo;
        Pedidos pedido;

        // Leer el ID del pedido
        getline(ss, campo, ',');
        pedido.ID_pedido = stoi(campo);

        // Leer el ID del usuario
        getline(ss, campo, ',');
        pedido.ID_usuario = stoi(campo);

        // Leer el ID del libro
        getline(ss, campo, ',');
        pedido.ID_libro = stoi(campo);

        // Leer el estado del pedido
        getline(ss, campo, ',');
        pedido.estadoPedido = campo;

        // Leer y convertir las fechas
        getline(ss, campo, ',');
        pedido.fechaPedido = convertirFecha(campo);

        getline(ss, campo, ',');
        pedido.fechaAdquisicion = convertirFecha(campo);

        getline(ss, campo, ',');
        pedido.devolucion = convertirFecha(campo);

        getline(ss, campo, ',');
        pedido.entregado = convertirFecha(campo);

        if(idUsuario == pedido.ID_usuario){
            
            NodoPedidos *nodo = new NodoPedidos(pedido);

            encolarHistorial(nodo, historial);
        }

    }

    archivo.close();
    return historial;
}

NodoPedidos* desencolarHistorial(colaHistorial &q){
    if(q.adelante == nullptr){
        cout << "La cola de prioridad esta vacia"<< endl;
        system("pause>0");
        return NULL;
    }

    NodoPedidos* stat = q.adelante;
    q.adelante = q.adelante->sgte;

    if(q.adelante==nullptr){
        q.atras = nullptr;
    }

    return stat;
}

string devolverNombre(Lista &Usuarios, int id){
    Nodo *actual = Usuarios.cabeza;
    while(actual != nullptr){
        //cout << endl << "ciclo infinito?";
        if(stoi(actual->usuario.ID_Usuario) == id){
            return actual->usuario.nombre;
        }
        actual = actual->siguiente;
    }

    return "Nombre no encontrado";
}

void mostrarHistorial(){
    gotoxy(51,11);
    color(2);
    cout << "Historial de Pedidos";
    int id;
    gotoxy(26, 13);
    color(2);
    cout << "DNI del cliente a consultar: ";
    gotoxy(40, 14);
    color(0);
    cin >> id;
    cin.ignore();
    
    // Se crea una cola para el usuario ingresado
    colaHistorial historial = cargarHistorialxID("output/pedidos.csv",id);
    
    NodoPedidos *actual = desencolarHistorial(historial);

    int contador = 0;
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    
    Lista listaUsuarios = leerUsuariosCSV("output/usuarios.csv");
    gotoxy(44, 12);
    color(2);
    cout << "Historial de Pedidos de "<<devolverNombre(listaUsuarios,id) ;

    gotoxy(20, 14);
    cout << "ID";
    gotoxy(26, 14);
    cout << "Libro";
    gotoxy(54, 14);
    cout << "Estado";
    gotoxy(70, 14);
    cout << "Fecha de pedido";
    color(0);

    while (actual != nullptr)
    {

        gotoxy(20, 16 + contador);
        cout << actual->pedido.ID_pedido;
        gotoxy(26, 16 + contador);
        cout << actual->pedido.ID_libro;
        gotoxy(54, 16 + contador);
        cout << actual->pedido.estadoPedido;
        gotoxy(70, 16 + contador);
        cout << fechaAString(actual->pedido.fechaPedido);
        actual = actual->sgte;
        contador++;
    }
    pausa();
}

void encolarEstadistica(NodoEstadisticas *stat, colaPrioEstadisticas &q){

    if(q.delante==nullptr){
        q.delante = stat;
        q.atras = stat;
    }else if(stat->prio > q.delante->prio){
        stat->sgte = q.delante;
        q.delante = stat;
    }else{
        NodoEstadisticas *actual = q.delante;
        NodoEstadisticas *anterior = nullptr;

        while(actual != nullptr and actual->prio >= stat->prio){
            anterior = actual;
            actual = actual->sgte;
        }

        if(anterior != nullptr){
            anterior->sgte = stat;
        }
        stat->sgte=actual;
        if(actual == nullptr){
            q.atras = stat;
        }
    }
}

NodoEstadisticas* desencolar(colaPrioEstadisticas &q){
    if(q.delante == nullptr){
        cout << "La cola de prioridad esta vacia"<< endl;
        system("pause>0");
        return NULL;
    }

    NodoEstadisticas* stat = q.delante;
    q.delante = q.delante->sgte;

    if(q.delante==nullptr){
        q.atras = nullptr;
    }

    return stat;
}

colaPrioEstadisticas cargarEstadisticaCSV(string nombreArchivo){
    fstream archivo(nombreArchivo);

    colaPrioEstadisticas colaPrincipal; //crear una cola de prioridad vacia
    string linea;

    if (!archivo.is_open()) { // Verificar si el archivo se abrió correctamente
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        system("PAUSE");

        return colaPrincipal; // Regresar la lista vacía si el archivo no se pudo abrir
    }

    while(getline(archivo, linea)){
        stringstream ss(linea);
        string campo;
        estadisticaLibro stat;
        
        //Leer el ID de libro

        //veces solicitado

        //veces prestado

        //veces devuelto tarde
    }

    return colaPrincipal;
}