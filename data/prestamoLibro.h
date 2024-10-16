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

bool mostrarLibroXidCopy(ListaLibros &Libros, int id)
{
    nodoLibros *actual = Libros.cabeza; // Apuntar al primer nodo de la lista

    // Recorrer la lista buscando el libro con el ID indicado
    while (actual != nullptr)
    {
        if (actual->libro.id == id) // Si el ID del libro coincide
        {
            // Mostrar los datos del libros
            gotoxy(36, 17);
            color(2);
            cout << "1. Nombre del Libro: ";
            color(7);
            cout << actual->libro.nombre_Libro;
            gotoxy(36, 18);
            color(2);
            cout << "2. Autor: ";
            color(7);
            cout << actual->libro.Autor;
            gotoxy(36, 19);
            color(2);
            cout << "3. Genero: ";
            color(7);
            cout << actual->libro.Genero;
            gotoxy(36, 20);
            color(2);
            cout << "4. Ano: ";
            color(7);
            cout << actual->libro.Ano;
            gotoxy(36, 21);
            color(2);
            cout << "5. Stock Inventario: ";
            color(7);
            cout << actual->libro.Stock_Inventario;
            gotoxy(36, 22);
            color(2);
            cout << "6. Stock Actual: ";
            color(7);
            cout << actual->libro.StockActual;
            gotoxy(36, 23);
            color(2);
            cout << "7. Precio: ";
            color(7);
            cout << actual->libro.precio;
            gotoxy(36, 24);
            color(2);
            cout << "8. Estado: ";
            color(7);
            cout << actual->libro.estado;
            return true; // Retorna true si el libro fue encontrado
            break;
        }
        actual = actual->siguiente; // Mover al siguiente nodo
    }

    // Si el libro no fue encontrado
    cout << "No se encontro ningun libro con el ID: " << id << endl;
    return false; // Retorna false si no encontró el libro
}

void adicionarCampoPedido(){ //osea que el cliente haga el pedido
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
        pedido->ID_pedido = countLinesFile("Pedidos.csv"); // falta hacer que cuente las lineas para que ponga el id --------------------------------
        gotoxy(36, 11);
        color(2);
        cout << "a continuación confirme que desea realizar un pedido (s/n)" << endl;
        gotoxy(36, 12);
        color(7);
        cin >> respuesta;
        if(respuesta[0] == 'n' or respuesta[0] == 'N'){
            break;
        }
        gotoxy(36, 13);
        color(2);
        cout << "Ingrese su codigo de usuario: "; // falta automatizar --------------------------------
        gotoxy(36, 14);
        color(7);
        cin >> pedido->ID_usuario;
        cin.ignore();
        color(7);
        gotoxy(36, 15);
        color(2);
        cout << "Ahora ingrese el codigo identificador del libro: ";
        gotoxy(36, 16);
        color(7);
        cin >> pedido->ID_libro;
        ListaLibros libros = leerLibrosCSV("Libros.csv");
        bool find = mostrarLibroXidCopy(libros, pedido->ID_libro);
        if(find){
            char check;
            gotoxy(36,25);
            color(2);
            cout <<"Este es el libro que deseas solcitar?(s/n): ";
            color(7);
            cin >> check;
            if(!(check == 's' or check == 'S')){
                respuesta[0] = 's';
                continue;
            }

        }

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

        gotoxy(36, 27);
        color(2);
        cout << "Desea registrar otro pedido? (s/n): ";
        color(7);
        cin >> respuesta;
    }while(respuesta[0] =='s'||respuesta[0] =='S');

    guardar_CSV_Pedido(listaPedido, "Pedidos.csv");
}

ListaPedidos leerPedidosCSV(string nombreArchivo){
    ifstream archivo(nombreArchivo);
    ListaPedidos listaDePedidos; //reutilizo el codigo de gestion libros porque solo necesito 
    string line;

    if(filesystem::exists(nombreArchivo) && filesystem::file_size(nombreArchivo) > 0){
        if(archivo.is_open()){
            while (getline(archivo, line)) {
                string dato;
                Libro libro;
                stringstream ss(line);
                
                // Dividir la línea usando la coma como delimitador
                getline(ss, dato, ',');
                libro.id = stoi(dato); // Convertir a entero
                getline(ss, libro.nombre_Libro, ',');
                getline(ss, libro.Autor, ',');
                getline(ss, dato, ',');
                libro.Ano = stoi(dato);
                getline(ss, libro.Genero, ',');
                getline(ss, dato, ',');
                libro.Stock_Inventario = stoi(dato);
                getline(ss, dato, ',');
                libro.StockActual = stoi(dato);
                getline(ss, dato, ',');
                libro.precio = stoi(dato);
                getline(ss, libro.estado, ',');

                //insertarLibro(listaDePedidos, libro);

               }
            archivo.close();  // Cerrar el archivo
        }else{
            cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
            perror("Error al abrir el archivo");
            system("PAUSE");
            return listaDePedidos;
        }
    }else {
        cout << "El archivo está vacío o no existe." << endl;
    }
    
}

void modificarCampoPedido(){

}
