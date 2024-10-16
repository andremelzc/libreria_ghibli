#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <locale>
#include <ctime>
#include <filesystem>
#include"..\menu\gotoxy.h"

using namespace std;

/* pedidos_libro (libros prestados):
id_pedido
id_usuario
id_libro
estadoPedido (SOLICITADO, PRESTADO, NO_DEVUELTO, DEVUELTO, DEVUELTO_TARDE)
fechaaAdquisicion:
fechaDevolucion:
fechaEntregado: */

struct fecha
{
  int dia, mes, año;  
};


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

int countLinesFile(string nombreArchivo){
    ifstream archivo(nombreArchivo);
    string linea;
    int cont = 0;
    while(getline(archivo, linea)){
        cont++;
    }
    return cont;
}

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
    cerr << "Error: El archivo '" << nombreArchivo << "' no existe." << endl;
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
                << pedido.ID_usuario << ","
                << pedido.ID_libro << ","
                << pedido.estadoPedido << ","
                << pedido.fechaPedido.dia<<"/"<< pedido.fechaPedido.mes<<"/" << pedido.fechaPedido.año << ","
                << pedido.fechaAdquisicion.dia<<"/"<< pedido.fechaAdquisicion.mes<<"/" << pedido.fechaAdquisicion.año << ","
                << pedido.devolucion.dia<<"/"<< pedido.devolucion.mes<<"/" << pedido.devolucion.año << ","
                << pedido.entregado.dia<<"/"<< pedido.entregado.mes<<"/" << pedido.entregado.año << "\n";
             

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

void adicionarCampoPedido(int id_usuariologeado){
    ListaPedidos *listaPedido = new ListaPedidos();
    
    char respuesta[10];
    int i=0;
    time_t now = time(0);

    tm* localTime = localtime(&now);
    do{
        i++;
        system("CLS");
        estructura_menu();
        Pedidos *pedido = new Pedidos();
        pedido->ID_pedido = i;
        gotoxy(45, 12);
        color(2);
        cout << "Solicitando prestamo de libro";
        color(7);
        cout << "Fecha de devolución (dia fecha año): ";
        color(4);
        cin >> pedido->ID_libro;

        //Estableciendo estadoPedido
        pedido->estadoPedido = "SOLICITADO";

        //agregando la fecha del día que se realizo el pedido 
        pedido->fechaPedido.dia = localTime->tm_mday;
        pedido->fechaPedido.mes = localTime->tm_mon + 1; // mas 1 pq los meses empiezan en 0
        pedido->fechaPedido.año = localTime->tm_year + 1900; //tm year solo cuenta los años desde 1900

        //setting las fechas que no pueden puede ser establecidas en la creacion del pedido
        pedido->fechaAdquisicion.dia = 0; pedido->fechaAdquisicion.mes = 0; pedido->fechaAdquisicion.año = 0; 
        pedido->entregado.dia = 0; pedido->entregado.mes = 0; pedido->entregado.año = 0; 
        pedido->devolucion.dia = 0; pedido->devolucion.mes = 0; pedido->devolucion.año = 0; 

        insertarFinalListaPedido(listaPedido,pedido);

        gotoxy(36, 19);
        color(2);
        cout << "Desea solicitar otro prestamo? (s/n): ";
        color(7);
        cin >> respuesta;
    }while(respuesta[0] =='s'||respuesta[0] =='S');

    guardar_CSV_Pedido(listaPedido, "pedidos.csv");
}