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

//contar lineas -- falta agregar algo para que si agregas más de un pedido te lo cuente
int countLinesFile(string nombreArchivo, int i){
    ifstream archivo(nombreArchivo);
    string linea;
    int cont = 0;
    while(getline(archivo, linea)){
        cont++;
    }
    return cont + i;
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
//Insertar para crear la listaenlazada
void insertarListaPedidos(ListaPedidos &lista, Pedidos nuevoPedido) {
    // Crear un nuevo nodo con el pedido
    NodoPedidos *nuevoNodo = new NodoPedidos(nuevoPedido);
    
    // Insertar el nuevo nodo al principio de la lista
    nuevoNodo->sgte = lista.head;
    lista.head = nuevoNodo;
    
    // Incrementar la longitud de la lista
    lista.longitud++;
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

void guardar_CSV_PedidoReferencia(ListaPedidos &Lista, const string &nombreArchivo) {
    fstream archivo(nombreArchivo, fstream::out); // Abrir en modo de escritura (sobrescribirá si el archivo existe)

    // Verificar si se pudo abrir el archivo
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        system("PAUSE");
        return;
    }

    NodoPedidos *nodo = Lista.head; // Obtener el primer nodo de la lista

    // Recorrer la lista de pedidos y escribir en el archivo
    while (nodo != nullptr) {
        Pedidos pedido = nodo->pedido;
        archivo << pedido.ID_pedido << ","
                << pedido.ID_usuario << ","
                << pedido.ID_libro << ","
                << pedido.estadoPedido << ","
                << pedido.fechaPedido.dia << "/" << pedido.fechaPedido.mes << "/" << pedido.fechaPedido.año << ","
                << pedido.fechaAdquisicion.dia << "/" << pedido.fechaAdquisicion.mes << "/" << pedido.fechaAdquisicion.año << ","
                << pedido.devolucion.dia << "/" << pedido.devolucion.mes << "/" << pedido.devolucion.año << ","
                << pedido.entregado.dia << "/" << pedido.entregado.mes << "/" << pedido.entregado.año << "\n";

        nodo = nodo->sgte; // Mover al siguiente nodo
    }

    // Verificar si hubo un error al escribir en el archivo
    if (archivo.fail()) {
        cerr << "Error: Fallo al escribir en el archivo." << endl;
        system("PAUSE");
        return; // Salir con error
    }

    archivo.close(); // Cerrar el archivo
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
            gotoxy(36, 18);
            color(2);
            cout << "1. Nombre del Libro: ";
            color(7);
            cout << actual->libro.nombre_Libro;
            gotoxy(36, 19);
            color(2);
            cout << "2. Autor: ";
            color(7);
            cout << actual->libro.Autor;
            gotoxy(36, 20);
            color(2);
            cout << "3. Genero: ";
            color(7);
            cout << actual->libro.Genero;
            gotoxy(36, 21);
            color(2);
            cout << "4. Ano: ";
            color(7);
            cout << actual->libro.Ano;
            gotoxy(36, 22);
            color(2);
            cout << "5. Stock Inventario: ";
            color(7);
            cout << actual->libro.Stock_Inventario;
            gotoxy(36, 23);
            color(2);
            cout << "6. Stock Actual: ";
            color(7);
            cout << actual->libro.StockActual;
            gotoxy(36, 24);
            color(2);
            cout << "7. Precio: ";
            color(7);
            cout << actual->libro.precio;
            gotoxy(36, 25);
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

bool verificarMembresiaYMax(Lista &Usuarios, int id){ //verifica que tengas membresia activa y menos de 4 libros sin devolver
    Nodo *actual = Usuarios.cabeza;
    while(actual != nullptr){
        //cout << endl << "ciclo infinito?";
        if(stoi(actual->usuario.ID_Usuario) == id){
            if(actual->usuario.membresia == "ACTIVA" && actual->usuario.librosPrestados <= 2){
                return true;
            }
        }
        actual = actual->siguiente;
    }

    return false;
}

void modificarCantPrestada(int idUsuario){
    Lista listaUsuarios;
    listaUsuarios = leerUsuariosCSV("usuarios.csv");

    Nodo *actual = listaUsuarios.cabeza;
    
    while(actual != nullptr){
        if(stoi(actual->usuario.ID_Usuario) == idUsuario){
            actual->usuario.librosPrestados++;
        }
        actual = actual->siguiente;
    }
    limpiarCSV("usuarios.csv");
    guardar_CSV(&listaUsuarios, "usuarios.csv");
}

void adicionarCampoPedido(int id_usuariologeado){

    ListaPedidos *listaPedido = new ListaPedidos();
    
    char respuesta[10];
    int i=0;
    time_t now = time(0);
    tm* localTime = localtime(&now);
    do{
        system("CLS");
        estructura_menu();
        Pedidos *pedido = new Pedidos();
        pedido->ID_pedido = countLinesFile("Pedidos.csv",i);
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
        cout << "Su codigo de usuario es: "; 
        color(7);
        gotoxy(36,14);
        cout << id_usuariologeado;
        pedido->ID_usuario = id_usuariologeado; 
        Lista listaUsuarios = leerUsuariosCSV("usuarios.csv");
        //cout << endl<< "comprobando q todo esta bien"; 
        if(!(verificarMembresiaYMax(listaUsuarios, id_usuariologeado))){ //si es falso volvera a preguntar si deseas hacer una peticion
            //cout << endl<< "comprobando q todo esta bien 2"; 
            gotoxy(27, 16);
            color(3);
            cout << "No tiene una membresia para el prestamo o supero el limite de libros prestados";
            gotoxy(27, 17);
            system("PAUSE");
            respuesta[0] = 's';
            continue;
        }

        gotoxy(36, 15);
        color(2);
        cout << "Ahora ingrese el codigo identificador del libro: ";
        gotoxy(36, 16);
        color(7);
        cin.ignore();
        cin >> pedido->ID_libro;
        ListaLibros libros = leerLibrosCSV("libros.csv");
        bool find = mostrarLibroXidCopy(libros, pedido->ID_libro);
        if(find){
            char check;
            i++;
            gotoxy(36,26);
            color(2);
            cout <<"Este es el libro que deseas solcitar?(s/n): ";
            color(7);
            cin >> check;
            if(!(check == 's' or check == 'S')){
                respuesta[0] = 's';
                continue;
            }
        }else {
            gotoxy(36,18);
            color(3);
            cout << "No se encontro un libro con el codigo que buscas";
            respuesta[0] = 's';
            continue;
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

        //agregar aqui la actualizacion de la cantidad de libros prestado ojo me puedo guiar de la funcion actualizar membresia usuario que tiene un parecido
        //usamos esta funcion para aumentar en 1 la cantidad prestada
        modificarCantPrestada(pedido->ID_usuario); //------------- quitar de aqui y mandar a cuando se acepte el pedido

        gotoxy(36, 28);
        color(2);
        cout << "Desea solicitar otro prestamo? (s/n): ";
        color(7);
        cin >> respuesta;
    }while(respuesta[0] =='s'||respuesta[0] =='S');

    guardar_CSV_Pedido(listaPedido, "Pedidos.csv");
}

fecha convertirFecha(const string& campo) {
    stringstream ss(campo);
    string parte;
    int dia, mes, año;

    // Leer el día
    getline(ss, parte, '/');
    dia = stoi(parte);

    // Leer el mes
    getline(ss, parte, '/');
    mes = stoi(parte);

    // Leer el año
    getline(ss, parte);
    año = stoi(parte);

    // Retornar un objeto de tipo 'fecha'
    return {dia, mes, año};
}

ListaPedidos leerPedidosDesdeCSV(string nombreArchivo) {
    ListaPedidos lista; // Crear una lista vacía
    ifstream archivo(nombreArchivo); // Abrir el archivo CSV
    
    if (!archivo.is_open()) { // Verificar si el archivo se abrió correctamente
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        system("PAUSE");

        return lista; // Regresar la lista vacía si el archivo no se pudo abrir
    }
    
    string linea;
    while (getline(archivo, linea)) { // Leer línea por línea del archivo CSV
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

        insertarListaPedidos(lista,pedido);

    }

    archivo.close(); // Cerrar el archivo CSV
    return lista; // Regresar la lista de pedidos
}

fecha obtenerFechaActual() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Asignar la fecha actual al objeto fecha
    fecha fechaActual;
    fechaActual.dia = ltm->tm_mday;
    fechaActual.mes = 1 + ltm->tm_mon; // Meses comienzan desde 0, por lo tanto se suma 1
    fechaActual.año = 1900 + ltm->tm_year; // Año empieza desde 1900, por lo tanto se suma 1900

    return fechaActual;
}

void gestionarpedido(){
    
    Lista lista;
    lista = leerUsuariosCSV("usuarios.csv");
    ListaLibros listaLibros;
    listaLibros = leerLibrosCSV("libros.csv");
    ListaPedidos listaPedidos;
    listaPedidos  = leerPedidosDesdeCSV("pedidos.csv");
    
    string dni;
    cout << "Ingrese el DNI del usuario: ";
    cin >> dni;

    // Buscar el usuario en la lista de usuarios
    Nodo* usuarioEncontrado = buscarUsuarioPorDNI(lista, dni);
    if (usuarioEncontrado == nullptr) {
        cout << "Usuario no encontrado." << endl;
        return;
    }

    cout << "Usuario encontrado: " << usuarioEncontrado->usuario.nombre << " " << usuarioEncontrado->usuario.apellidos << endl;

    // Buscar si el usuario tiene algún pedido con estado "SOLICITADO"
    NodoPedidos* actualPedido = listaPedidos.head;
    bool pedidoEncontrado = false;

    while (actualPedido != nullptr) {
        if (actualPedido->pedido.ID_usuario == stoi(dni) && actualPedido->pedido.estadoPedido == "SOLICITADO") {
            pedidoEncontrado = true;
            cout << "Pedido encontrado. ID del pedido: " << actualPedido->pedido.ID_pedido << endl;

            // Buscar el libro correspondiente
            nodoLibros* libroEncontrado = buscarLibroPorID(listaLibros, actualPedido->pedido.ID_libro);
            if (libroEncontrado != nullptr) {
                cout << "Libro encontrado: " << libroEncontrado->libro.nombre_Libro << endl;
                
                // Preguntar al usuario si desea prestar el libro
                char respuesta;
                cout << "¿Desea prestar este libro? (S/N): ";
                cin >> respuesta;

                if (respuesta == 'S' || respuesta == 's') {
                    cout << "Esta seguro de que quiere prestar el libro? (S/N): ";
                    cin >> respuesta;

                    if (respuesta == 'S' || respuesta == 's') {
                        // Cambiar el estado a "PRESTADO"
                        actualPedido->pedido.estadoPedido = "PRESTADO";
                        cout << "El estado del pedido ha sido actualizado a PRESTADO." << endl;

                        // Obtener la fecha actual usando la función obtenerFechaActual
                        actualPedido->pedido.fechaAdquisicion = obtenerFechaActual();

                        cout << "Fecha de adquisicion: " << actualPedido->pedido.fechaAdquisicion.dia << "/"
                             << actualPedido->pedido.fechaAdquisicion.mes << "/"
                             << actualPedido->pedido.fechaAdquisicion.año << endl;

                    } else {
                        cout << "Operación cancelada." << endl;
                    }
                } else {
                    cout << "Operación cancelada." << endl;
                }
            } else {
                cout << "Libro no encontrado." << endl;
            }
        }
        actualPedido = actualPedido->sgte;
    }

    if (!pedidoEncontrado) {
        cout << "No hay pedidos solicitados para este usuario." << endl;
    }
    guardar_CSV_PedidoReferencia(listaPedidos,"pedidos.csv");
    system("PAUSE");
    
}

void mostrarPedidos(ListaPedidos &listaPedidos){
    NodoPedidos *actual = listaPedidos.head;
    int contador = 0;
    gotoxy(50, 12);
    color(2);
    cout << "Lista de Pedidos";
    gotoxy(20, 14);
    cout << "id Pedido:";
    gotoxy(33, 14);
    cout << "Usuario: ";
    gotoxy(54, 14);
    cout << "Libro: ";
    gotoxy(74, 14);
    cout << "Estado del libro: ";
    color(7);
    while (actual != nullptr)
    {

        gotoxy(20, 16 + contador);
        cout << actual->pedido.ID_pedido;
        gotoxy(33, 16 + contador);
        cout << actual->pedido.ID_usuario;
        gotoxy(54, 16 + contador);
        cout << actual->pedido.ID_libro;
        gotoxy(74, 16 + contador);
        cout << actual->pedido.estadoPedido;

        actual = actual->sgte;
        contador++;
    }
    system("PAUSE>0");
}
