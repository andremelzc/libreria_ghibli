#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <locale>
#include <filesystem>
#include"..\menu\gotoxy.h"

using namespace std;

/* ID_pedido
libroXUsuario;
estadoUsuario[Activo/Inactivo]
Usuario;
contraseña;
Nombre;Apellidos;
?Genero(F/M);
Correo electrónico;
telefono;
fechaInicio;
fechaFinal */

struct fecha
{
  int dia, mes, año;  
};


struct Pedidos{
    int ID_pedido,librosYaPrestados;
    string Usuario, contraseña, estadoUsuario;
    fecha inicio, final;
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
    ListaPedidos(): head(nullptr) {}; 
};

void insertarFinalListaPedido(ListaPedidos *lista, Pedidos *pedido)
{
    NodoPedidos *NodoPedido = new NodoPedidos(*pedido);

    if(lista->head == nullptr){
        lista->head = NodoPedido;
    }else{
        NodoPedidos *iterador = lista->head;
        while(iterador->sgte){
            iterador=iterador->sgte;
        }
        iterador->sgte = NodoPedido;
    }
    lista->longitud++;
}

void guardar_CSV_Pedido(ListaPedidos *Lista, string nombreArchivo){
    fstream archivo(nombreArchivo, fstream::out | fstream ::app);

    if (!filesystem::exists(nombreArchivo)) {
    cerr << "Error: El directorio 'output' no existe." << endl;
    system("PAUSE");
    return;
    }

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo. " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        system("PAUSE");
        return;
    }

    NodoPedidos *nodo = Lista->head;

    while(nodo != nullptr){
        Pedidos pedido = nodo->pedido;
        archivo << pedido.ID_pedido << ","
                << pedido.Usuario << "," 
                << pedido.contraseña << ","
                << pedido.estadoUsuario << "," 
                << pedido.inicio.dia<<"/"<< pedido.inicio.mes<<"/" << pedido.inicio.año << ","
                << pedido.final.dia<<"/"<< pedido.final.mes<<"/" << pedido.final.año << ","
                << pedido.librosYaPrestados << "\n";
             

        nodo = nodo->sgte; 
    }

    if (archivo.fail()) {
        std::cerr << "Error: Fallo al escribir en el archivo." << std::endl;
        system("PAUSE");
        return ; // Salir con error
    }

    archivo.close();
    cout << "Datos guardados en " << nombreArchivo << endl;
}

void adicionarCampoPedido(){
    ListaPedidos *listaPedido = new ListaPedidos();
    char respuesta[10];
    int i=0;
    do{
        i++;
        system("CLS");
        estructura_menu();
        Pedidos *pedido = new Pedidos();
        pedido->ID_pedido = i;
        gotoxy(36, 14);
        color(2);
        cout << "a continuación agrese los siguientes campos para realizar su pedido" << endl;
        gotoxy(36, 15);
        cout << "Usuario: ";
        color(4);
        getline(cin, pedido ->Usuario);
        gotoxy(36, 16);
        color(2);
        cout << "Contraseña: ";
        color(4);
        getline(cin, pedido->contraseña);
        gotoxy(36, 17);
        color(2);
        cout << "Estado: ";
        color(4);
        getline(cin, pedido->estadoUsuario);
        gotoxy(36, 18);
        color(2);
        cout << "Fecha de pedido (dia fecha año): ";
        cin.ignore();
        color(4);
        cin >> pedido->inicio.dia >>pedido->inicio.mes >> pedido->inicio.año ;
        cin.ignore();
        gotoxy(36, 19);
        color(2);
        cout << "Fecha de devolución (dia fecha año): ";
        color(4);
        cin >> pedido->final.dia >>pedido->final.mes >> pedido->final.año ;

        insertarFinalListaPedido(listaPedido,pedido);

        gotoxy(36, 20);
        color(2);
        cout << "Desea registrar otro usuario? (s/n): ";
        color(7);
        cin >> respuesta;
    }while(respuesta[0] =='s'||respuesta[0] =='S');

    guardar_CSV_Pedido(listaPedido, "Pedidos.csv");
}