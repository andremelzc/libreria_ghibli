#pragma once
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <conio.h>
#include "persistenciaDatos.h"
#include "..\menu\gotoxy.h"
#include "gestionUsuarios.h"
#include "prestamoLibro.h"
#include "..\servicio\funcionalidades.h"

using namespace std;

// -- FUNCIONES PARA HISTORIAL DE PEDIDOS --
// Encolamos un pedido en la cola de historial
void encolarHistorial(NodoPedidos *pedido, colaHistorial &q)
{
    if (q.adelante == nullptr)
    {
        q.adelante = pedido;
        q.atras = pedido;
    }
    else
    {
        q.atras->sgte = pedido;
        q.atras = pedido;
    }
}
// Cargar el historial de pedidos a partir de un CSV de un usuario
colaHistorial cargarHistorialxID(string nombreArchivo, int idUsuario)
{
    string linea;
    ifstream archivo(nombreArchivo);
    colaHistorial historial;

    if (!archivo.is_open())
    { // Verificar si el archivo se abrió correctamente
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        system("PAUSE");

        return historial; // Regresar la lista vacía si el archivo no se pudo abrir
    }

    while (getline(archivo, linea))
    {
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

        if (idUsuario == pedido.ID_usuario)
        {

            NodoPedidos *nodo = new NodoPedidos(pedido);

            encolarHistorial(nodo, historial);
        }
    }

    archivo.close();
    return historial;
}
// Desencolar un pedido del historial
NodoPedidos *desencolarHistorial(colaHistorial &q)
{
    if (q.adelante == nullptr)
    {
        return NULL;
    }

    NodoPedidos *stat = q.adelante;
    q.adelante = q.adelante->sgte;

    if (q.adelante == nullptr)
    {
        q.atras = nullptr;
    }

    return stat;
}
// Obtener el nombre de un usuario a partir de su ID
string devolverNombre(Lista &Usuarios, int id)
{
    Nodo *actual = Usuarios.cabeza;
    while (actual != nullptr)
    {
        // cout << endl << "ciclo infinito?";
        if (stoi(actual->usuario.ID_Usuario) == id)
        {
            return actual->usuario.nombre;
        }
        actual = actual->siguiente;
    }

    return "Nombre no encontrado";
}
// Obtener el nombre de un libro a partir de su ID
string devolverLibroNombre(ListaLibros &Libros, int id)
{
    nodoLibros *actual = Libros.cabeza;

    while (actual != nullptr)
    {
        if (actual->libro.id == id)
        {
            return actual->libro.nombre_Libro;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}
// Menú de mostrar historial
void mostrarHistorial()
{
    gotoxy(51, 11);
    color(2);
    cout << "Historial de Pedidos";
    int id;
    gotoxy(26, 13);
    color(2);
    cout << "DNI del cliente a consultar: ";
    color(0);
    cin >> id;
    cin.ignore();

    // Se crea una cola para el usuario ingresado
    colaHistorial historial = cargarHistorialxID("output/pedidos.csv", id);

    NodoPedidos *actual = desencolarHistorial(historial);

    int contador = 0;
    int contadorEntregasTarde = 0;
    bool aptoParaPrestamos = false;

    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(24, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);

    Lista listaUsuarios = leerUsuariosCSV("output/usuarios.csv");
    gotoxy(44, 11);
    color(2);
    cout << "Historial de Pedidos de ";
    color(0);
    cout << devolverNombre(listaUsuarios, id);
    color(2);
    gotoxy(20, 13);
    cout << "ID";
    gotoxy(26, 13);
    cout << "Libro";
    gotoxy(57, 13);
    cout << "Estado";
    gotoxy(75, 13);
    cout << "Fecha de pedido";
    color(0);
    ListaLibros Libros = leerLibrosCSV("output/libros.csv");
    while (actual != nullptr)
    {
        if (contador < 10)
        {
            color(0);
            gotoxy(20, 15 + contador);
            cout << actual->pedido.ID_pedido;
            gotoxy(26, 15 + contador);
            cout << actual->pedido.ID_libro << ") " << devolverLibroNombre(Libros, actual->pedido.ID_libro);
            gotoxy(57, 15 + contador);
            if (actual->pedido.estadoPedido == "NO_DEVUELTO" or actual->pedido.estadoPedido == "DEVUELTO_TARDE")
            {
                color(4);
            }
            cout << actual->pedido.estadoPedido;
            color(0);
            gotoxy(75, 15 + contador);
            cout << fechaAString(actual->pedido.fechaPedido);
        }
        contador++;
        if (actual->pedido.estadoPedido == "DEVUELTO_TARDE")
        {
            contadorEntregasTarde++;
        }
        if (actual->pedido.estadoPedido == "NO_DEVUELTO" && aptoParaPrestamos == false)
        {
            color(0);
            gotoxy(20, 25);
            cout << "Observacion: ";
            color(5);
            cout << "El cliente no es apto para prestamos, pues tiene libros sin devolver ";
            aptoParaPrestamos == true;
        }
        actual = actual->sgte; // pasando al siguiente nodo
    }

    if (contador > 10)
    {
        gotoxy(20, 26);
        cout << "Y mas ...";
    }
    pausa();
}
// Menú de mostrar historial de un cliente
void mostrarHistorialCliente(int dni)
{
    gotoxy(51, 11);
    color(2);
    cout << "Historial de Pedidos";

    // Se crea una cola para el usuario ingresado
    colaHistorial historial = cargarHistorialxID("output/pedidos.csv", dni);
    Lista listaUsuarios = leerUsuariosCSV("output/usuarios.csv");
    NodoPedidos *actual = desencolarHistorial(historial);
    if (actual == NULL)
    {
        limpiarPantalla();
        setConsoleBackground(White);
        dibujarTitulo(24, 0, 2, letras);
        estructura_menu2(16, 103, 10, 27);
        gotoxy(44, 11);
        color(2);
        cout << "Historial de Pedidos de ";
        color(0);
        cout << devolverNombre(listaUsuarios, dni);
        color(2);
        gotoxy(20, 13);
        cout << "ID";
        gotoxy(26, 13);
        cout << "Libro";
        gotoxy(57, 13);
        cout << "Estado";
        gotoxy(75, 13);
        cout << "Fecha de pedido";
        color(0);
        gotoxy(20, 15);
        color(4);
        cout << "No se encontraron pedidos para el usuario";
        color(0);
        pausa();
        return;
    }

    int contador = 0;
    int contadorEntregasTarde = 0;
    bool aptoParaPrestamos = false;

    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(24, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);

    gotoxy(44, 11);
    color(2);
    cout << "Historial de Pedidos de ";
    color(0);
    cout << devolverNombre(listaUsuarios, dni);
    color(2);
    gotoxy(20, 13);
    cout << "ID";
    gotoxy(26, 13);
    cout << "Libro";
    gotoxy(57, 13);
    cout << "Estado";
    gotoxy(75, 13);
    cout << "Fecha de pedido";
    color(0);
    ListaLibros Libros = leerLibrosCSV("output/libros.csv");
    while (actual != nullptr)
    {
        if (contador < 10)
        {
            color(0);
            gotoxy(20, 15 + contador);
            cout << actual->pedido.ID_pedido;
            gotoxy(26, 15 + contador);
            cout << actual->pedido.ID_libro << ") " << devolverLibroNombre(Libros, actual->pedido.ID_libro);
            gotoxy(57, 15 + contador);
            if (actual->pedido.estadoPedido == "NO_DEVUELTO" or actual->pedido.estadoPedido == "DEVUELTO_TARDE")
            {
                color(4);
            }
            cout << actual->pedido.estadoPedido;
            color(0);
            gotoxy(75, 15 + contador);
            cout << fechaAString(actual->pedido.fechaPedido);
        }
        contador++;
        if (actual->pedido.estadoPedido == "DEVUELTO_TARDE")
        {
            contadorEntregasTarde++;
        }
        actual = actual->sgte; // pasando al siguiente nodo
    }

    if (contador > 10)
    {
        gotoxy(20, 26);
        cout << "Y mas ...";
    }
    pausa();
}

// a partir de aqui tiene que ver con estadisticas

ListaStrings cargarNombreLibrosCSV()
{
    ListaStrings listaLibros;
    ListaLibros libros = leerLibrosCSV("output/libros.csv");
    nodoLibros *actual = libros.cabeza;

    while (actual != nullptr)
    {
        NodoStrings *nodo = new NodoStrings(actual->libro.nombre_Libro);
        if (listaLibros.cabeza == nullptr)
        {
            listaLibros.cabeza = nodo;
        }
        else
        {
            bool encontrado = false;
            NodoStrings *ultimo = listaLibros.cabeza;
            while (ultimo->sgte != nullptr)
            {
                if (ultimo->dato == nodo->dato)
                {
                    encontrado = true;
                }
                ultimo = ultimo->sgte;
            }
            if (!encontrado)
            {
                ultimo->sgte = nodo;
            }
        }
        listaLibros.longitud++;
        actual = actual->siguiente;
    }

    return listaLibros;
}

// -- FUNCIONES PARA ESTADISTICAS DE LIBROS --
// Encolar una estadística en la cola de estadísticas
void encolarEstadistica(NodoEstadisticas *stat, colaPrioEstadisticas &q)
{

    if (q.delante == nullptr)
    {
        q.delante = stat;
        q.atras = stat;
        stat->sgte = nullptr;
    }
    else if (stat->prio > q.delante->prio)
    {   
        // Nueva mayor prioridad
        stat->sgte = q.delante;
        q.delante = stat;
    }
    else
    {
        NodoEstadisticas *actual = q.delante;
        NodoEstadisticas *anterior = nullptr;

        while (actual != nullptr and actual->prio >= stat->prio)
        {
            anterior = actual;
            actual = actual->sgte;
        }

        if (anterior != nullptr)
        {
            anterior->sgte = stat;
        }
        stat->sgte = actual;
        if (actual == nullptr)
        {
            q.atras = stat;
        }
    }
}
// Desencolar una estadística de la cola de estadísticas
NodoEstadisticas *desencolar(colaPrioEstadisticas &q)
{
    if (q.delante == nullptr)
    {
        return NULL;
    }

    NodoEstadisticas *stat = q.delante;
    q.delante = q.delante->sgte;

    if (q.delante == nullptr)
    {
        q.atras = nullptr;
    }

    return stat;
}
// Cargar las estadísticas de libros a partir de un CSV
colaPrioEstadisticas cargarEstadisticaCSV(string nombreArchivo)
{
    /*
    - recuperar la informacion de estadisticas de libros desde un archivo CSV
    - crear un array de strings con los nombres de los libros
    - crear una funcion que transforme el id de los libros del pedido en el nombre del libro
    - crear un doble for que recorra el array de strings y compare con el nombre del libro del pedido
    al final de este for se estaría creando un nodoEstadistica con el nombre del libro y las veces solicitado
    */
    fstream archivo(nombreArchivo);

    colaPrioEstadisticas colaPrincipal; // crear una cola de prioridad vacia

    string linea;

    if (!archivo.is_open())
    { // Verificar si el archivo se abrió correctamente
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        system("PAUSE");

        return colaPrincipal; // Regresar la lista vacía si el archivo no se pudo abrir
    }
    int vecesSolicitado = 0, vecesPrestado = 0, cantIncidencias = 0;
    // cargo los nombres de los libros
    ListaStrings listaLibros = cargarNombreLibrosCSV();
    NodoStrings *actualLibro = listaLibros.cabeza;
    while (actualLibro != nullptr)
    {
        estadisticaLibro stat;
        // Resetear el cursor al inicio del archivo
        archivo.clear();  // Limpia los flags de error del archivo
        archivo.seekg(0); // Mueve el cursor al inicio del archivo
        
        vecesSolicitado = 0, vecesPrestado = 0, cantIncidencias = 0;
        while (getline(archivo, linea))
        {
            stringstream ss(linea);
            string campo;
            getline(ss, campo, ','); // saltando el id del pedido
            getline(ss, campo, ','); // saltando el id del usuario

            // Leer el ID de libro
            getline(ss, campo, ',');
            ListaLibros libros = leerLibrosCSV("output/Libros.csv");
            string nombreLibro = devolverLibroNombre(libros, stoi(campo));
            // Leer el estado del pedido
            getline(ss, campo, ',');
            if (actualLibro->dato == nombreLibro)
            {
                if (campo == "PRESTADO")
                {
                    // veces prestado
                    vecesPrestado++;
                }
                else if (campo == "INCIDENCIA")
                {
                    // veces devuelto tarde
                    cantIncidencias++;
                }
                else if (campo == "SOLICITADO")
                {
                    // veces solicitado
                    vecesSolicitado++;
                }
            }
        }
        /*cout << "Id libro: " << actualLibro->dato << endl;
        cout << cantIncidencias<< endl;
        pausa();*/
        stat.nombreLibro = actualLibro->dato;
        stat.vecesSolicitado = vecesSolicitado;
        stat.vecesPrestado = vecesPrestado;
        stat.cantIncidencias = cantIncidencias;

        NodoEstadisticas *nodo = new NodoEstadisticas(stat);

        if (colaPrincipal.delante == nullptr)
        {
            colaPrincipal.delante = nodo;
            colaPrincipal.atras = nodo;
        }
        else
        {
            encolarEstadistica(nodo, colaPrincipal);
        }
        actualLibro = actualLibro->sgte;
    }
    archivo.close();
    return colaPrincipal;
}

void mostrarEstadisticas()
{

    colaPrioEstadisticas estadisticas = cargarEstadisticaCSV("output/pedidos.csv");

    NodoEstadisticas *actual = desencolar(estadisticas);

    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 32);

    gotoxy(44, 11);
    color(2);
    cout << "Estadisticas de Libros";
    color(0);
    gotoxy(20, 13);
    cout << "Nombre del libro";
    gotoxy(51, 13);
    cout << "Veces solicitado";
    gotoxy(69, 13);
    cout << "Veces prestado";
    gotoxy(86, 13);
    cout << "Incidencias";

    int espacioV = 0;
    while (actual != nullptr)
    {
        // Verificar y cortar si es necesario
        if (actual->estadistica.nombreLibro.length() > 28)
        {
            actual->estadistica.nombreLibro = actual->estadistica.nombreLibro.substr(0, 28 - 3) + "...";
        }
        color(0);
        gotoxy(20, 15 + espacioV);
        cout << actual->estadistica.nombreLibro;
        gotoxy(57, 15 + espacioV);
        cout << actual->estadistica.vecesSolicitado;
        gotoxy(75, 15 + espacioV);
        cout << actual->estadistica.vecesPrestado;
        gotoxy(93, 15 + espacioV);
        cout << actual->estadistica.cantIncidencias;
        actual = actual->sgte; // pasando al siguiente nodo
        espacioV++;
    }

    pausa();
}

// -- FUNCIONES PARA ESTADISTICAS DE VENTAS --

// Cargar las estadísticas de ventas a partir de un CSV
ListaGanancias cargarEstadisticaVentasCSV(string nombreArchivo)
{
    fstream archivo(nombreArchivo);

    ListaGanancias listaGanancias; // crear una lista de ganancias vacia

    string linea;

    if (!archivo.is_open())
    { // Verificar si el archivo se abrió correctamente
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        system("PAUSE");

        return listaGanancias; // Regresar la lista vacía si el archivo no se pudo abrir
    }

    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string campo;
        Ganancia ganancia;

        // Leer el ID de la venta
        getline(ss, campo, ',');
        ganancia.id_usuario = stoi(campo);

        // Leer el ID del libro
        getline(ss, campo, ',');
        ganancia.origen = campo;

        // Leer el precio de venta
        getline(ss, campo, ',');
        ganancia.monto = stof(campo);

        // Leer la fecha de venta
        getline(ss, campo, ',');
        ganancia.fecha = campo; // falta convertir a fecha

        NodoGanancia *nodo = new NodoGanancia(ganancia);

        if (listaGanancias.head == nullptr)
        {
            listaGanancias.head = nodo;
        }
        else
        {
            NodoGanancia *ultimo = listaGanancias.head;
            while (ultimo->sgte != nullptr)
            {
                ultimo = ultimo->sgte;
            }
            ultimo->sgte = nodo;
        }
        listaGanancias.longitud++;
    }

    archivo.close();
    return listaGanancias;
}

void mostrarVistaEstadisticasGanancias()
{
    ListaGanancias ganancias = cargarEstadisticaVentasCSV("output/ganancias.csv");
    NodoGanancia *actual = ganancias.head;

    int contGananciasMora = 0;
    int contGananciasMembresias = 0;
    int contGananciasAmbos = 0;

    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(10, 130, 10, 35);

    gotoxy(50, 11);
    color(2);
    cout << "Estadisticas de Ventas";

    while (actual != nullptr)
    {
        fecha fechaPago = convertirFecha(actual->ganancia.fecha);
        if (esDelMesActual(fechaPago))
        {
            if (actual->ganancia.origen == "MORA")
            {
                contGananciasMora += actual->ganancia.monto;
                contGananciasAmbos += actual->ganancia.monto;
            }
            else if (actual->ganancia.origen != "MORA")
            {

                contGananciasMembresias += actual->ganancia.monto;
                contGananciasAmbos += actual->ganancia.monto;
            }
        }
        actual = actual->sgte; // pasando al siguiente nodo
    }

    float valorEscalado1 = ((float)(contGananciasMora) * (20)) / (contGananciasAmbos);
    float valorEscalado2 = ((float)(contGananciasMembresias) * (20)) / (contGananciasAmbos);

    color(0);
    gotoxy(15, 32);
    cout << "Ganancias por mora: " << contGananciasMora;
    for (int i = 0; i < valorEscalado1; i++)
    {
        color(11);
        gotoxy(26, 30 - i);
        cout << "****";
    }
    color(0);
    gotoxy(55, 32);
    cout << "Ganancias por Membresias: " << contGananciasMembresias;
    for (int i = 0; i < valorEscalado2; i++)
    {
        color(11);
        gotoxy(70, 30 - i);
        cout << "****";
    }

    color(0);
    gotoxy(100, 32);
    cout << "Ganancias totales: " << contGananciasAmbos;

    for (int i = 0; i < 20; i++)
    {
        color(11);
        gotoxy(113, 30 - i);
        cout << "****";
    }
    pausa();
}


// -- FUNCIONES PARA ESTADISTICAS DE RECEPCIONISTA

ListaRecepcionistas cargarRecepcionistasCSV()
{
    ListaRecepcionistas listaRecepcionistas;
    Lista listaUsuarios = leerUsuariosCSV("output/usuarios.csv");
    Nodo *actual = listaUsuarios.cabeza;

    while (actual != nullptr)
    {
        if (actual->usuario.tipo == 1) // Si es recepcionista
        {
            NodoRecepcionista *nodoTrabajador = new NodoRecepcionista(actual->usuario);
            // Si la lista está vacía
            if (listaRecepcionistas.head == nullptr)
            {
                listaRecepcionistas.head = nodoTrabajador;
            }
            else
            {
                // Insertar al final
                NodoRecepcionista *ultimo = listaRecepcionistas.head;
                while (ultimo->sgte != nullptr)
                {
                    ultimo = ultimo->sgte;
                }
                ultimo->sgte = nodoTrabajador;
            }
            listaRecepcionistas.longitud++;
        }
        actual = actual->siguiente;
    }
    
    return listaRecepcionistas;
}

ListaRecepcionistas cargarEstadisticaRecepcionistaCSV() {
    ListaRecepcionistas listaRecepcionistas = cargarRecepcionistasCSV();
    fstream archivo("output/pedidos.csv");
    string linea, campo;
    
    // Array fijo de 11 campos porque el CSV tiene 11 columnas:
    // 0: ID pedido
    // 1: ID cliente
    // 2: ID producto
    // 3: Estado
    // 4: FechaPedido
    // 5: FechaEnvio
    // 6: FechaEntrega
    // 7: FechaDevolucion
    // 8: Descuento
    // 9: PrecioOriginal
    // 10: PrecioFinal
    const int NUM_CAMPOS = 11;
    string campos[NUM_CAMPOS];

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        int i = 0;
        
        while (getline(ss, campo, ',') && i < NUM_CAMPOS) {
            campos[i] = campo;
            i++;
        }
        
        // Verificamos i == NUM_CAMPOS para asegurar que leímos todos los campos
        if (i == NUM_CAMPOS) {
            string idTrabajador = campos[9]; //el recepcionista que atiende primero
            cout << "idTrabajador: " << idTrabajador << endl;
            float pesoCalificacion = stof(campos[8]);
            cout << "peso " << pesoCalificacion << endl;
            pausa();
            if (idTrabajador != "-1") {
                NodoRecepcionista* actual = listaRecepcionistas.head;
                while (actual != nullptr) {
                    if (actual->trabajador.ID_Usuario == idTrabajador) {
                        if(pesoCalificacion != -1){
                            actual->Peso += pesoCalificacion;
                        }
                        actual->Peso++;
                        cout << "idTrabajador: " << idTrabajador << endl;
                        cout << "peso 2: " << actual->Peso << endl;
                        pausa();
                        break;
                    }
                    actual = actual->sgte;
                }
            }
        }
    }
    
    archivo.close();
    return listaRecepcionistas;
}

void mostrarEstadisticasRecepcionistas() {
    // Cargar y ordenar lista
    ListaRecepcionistas lista = cargarEstadisticaRecepcionistaCSV();
    
    // Ordenar por peso (bubble sort)
    NodoRecepcionista *actual = lista.head;
    while (actual != nullptr) {
        NodoRecepcionista *siguiente = actual->sgte;
        while (siguiente != nullptr) {
            if (siguiente->Peso > actual->Peso) {
                // Intercambiar datos
                Usuario tempUser = actual->trabajador;
                float tempPeso = actual->Peso;
                
                actual->trabajador = siguiente->trabajador;
                actual->Peso = siguiente->Peso;
                
                siguiente->trabajador = tempUser;
                siguiente->Peso = tempPeso;
            }
            siguiente = siguiente->sgte;
        }
        actual = actual->sgte;
    }

    // Mostrar resultados
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(10, 130, 10, 35);

    gotoxy(50, 11);
    color(2);
    cout << "Estadisticas de Recepcionistas";

    // Encabezados
    color(0);
    gotoxy(20, 13);
    cout << "Nombre";
    gotoxy(45, 13);
    cout << "ID";
    gotoxy(70, 13);
    cout << "Rating";

    // Imprimir lista ordenada
    actual = lista.head;
    int espacioV = 0;
    while (actual != nullptr) {
        gotoxy(20, 15 + espacioV);
        cout << actual->trabajador.nombre;
        gotoxy(45, 15 + espacioV);
        cout << actual->trabajador.ID_Usuario;
        gotoxy(70, 15 + espacioV);
        cout << actual->Peso;
        
        espacioV ++;
        actual = actual->sgte;
    }
    pausa();
}