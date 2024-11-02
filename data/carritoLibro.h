#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <locale>
#include <ctime>
#include <filesystem>
#include <cctype> // Para usar isdigit()
using namespace std;

// Miguel:tmb presente en el codigo de Fabri
int countLinesFiles(string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    string linea;
    int cont = 0;
    while (getline(archivo, linea))
    {
        cont++;
    }
    return cont;
}
// Uno listas en los Carritos
void unirListas(ListaCarritos &lista1, ListaCarritos &lista2)
{
    if (lista1.head == nullptr)
    {
        // Si lista1 está vacía, lista1 se convierte en lista2
        lista1.head = lista2.head;
        lista1.longitud = lista2.longitud;
        return;
    }

    // Encontrar el último nodo de lista1
    NodoCarritos *temp = lista1.head;
    while (temp->sgte != nullptr)
    {
        temp = temp->sgte;
    }

    // Conectar el último nodo de lista1 al primer nodo de lista2
    temp->sgte = lista2.head;

    // Actualizar la longitud de lista1
    lista1.longitud += lista2.longitud;
}

// Insertar al final de la lista
void insertarCarritoFinal(ListaCarritos *lista, Carritos libro)
{
    NodoCarritos *nodo = new NodoCarritos(libro);

    if (lista->head == nullptr)
    {
        lista->head = nodo;
    }
    else
    {
        NodoCarritos *puntero = lista->head;
        while (puntero->sgte)
        {
            puntero = puntero->sgte;
        }
        puntero->sgte = nodo;
    }
    lista->longitud++;
}

// Insertar para crear la lista enlazada
void insertarCarritoInicio(ListaCarritos &lista, Carritos carrito)
{
    NodoCarritos *nuevoNodo = new NodoCarritos(carrito); // Uso un pseudo Constructor
    nuevoNodo->sgte = lista.head;
    lista.head = nuevoNodo;
    lista.longitud++;
}

// Función para guardar la lista de carritos en un archivo CSV
void guardar_CSV_Carritos(ListaCarritos *lista, string nombreArchivo)
{
    fstream archivo(nombreArchivo, fstream::out);

    // Verificar si el directorio existe
    if (!filesystem::exists("output/carrito.csv"))
    {
        //std::cerr << "Error: El directorio 'output/carrito.csv' no existe." << std::endl;
        pausa();
        return;
    }

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open())
    {
        //cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        pausa();
        return;
    }

    // Recorrer la lista enlazada y escribir cada nodo en el archivo
    NodoCarritos *actual = lista->head;
    while (actual != nullptr)
    {
        Carritos carrito = actual->carrito;
        archivo << carrito.id_carrito << ","
                << carrito.id_cliente << ","
                << carrito.id_producto << ","
                << carrito.fecha << ","
                << carrito.cantidad << ","
                << carrito.estado << "\n";
        actual = actual->sgte;
    }

    // Verificar si ocurrió un error al escribir
    if (archivo.fail())
    {
        //std::cerr << "Error: Fallo al escribir en el archivo." << std::endl;
        archivo.close();
        return;
    }

    archivo.close();
    //cout << "Datos guardados en " << nombreArchivo << endl;
    pausa();
}

// Función para leer el archivo CSV y devolver una lista de carritos
ListaCarritos leerCSV(string nombreArchivo)
{
    ListaCarritos lista;
    ifstream archivo(nombreArchivo);

    // Verificar si el archivo existe y se puede abrir
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        return lista; // Devuelve una lista vacía
    }

    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        Carritos carrito;
        string campo;

        // Leer cada campo de la línea separada por comas
        getline(ss, campo, ',');
        carrito.id_carrito = stoi(campo);

        getline(ss, campo, ',');
        carrito.id_cliente = stoi(campo);

        getline(ss, campo, ',');
        carrito.id_producto = stoi(campo);

        getline(ss, campo, ',');
        carrito.fecha = campo;

        getline(ss, campo, ',');
        carrito.cantidad = stoi(campo);

        getline(ss, campo, ',');
        carrito.estado = stoi(campo);

        // Crear un nuevo nodo y añadirlo a la lista
        NodoCarritos *nuevoNodo = new NodoCarritos(carrito);
        if (lista.head == nullptr)
        {
            lista.head = nuevoNodo;
        }
        else
        {
            NodoCarritos *temp = lista.head;
            while (temp->sgte != nullptr)
            {
                temp = temp->sgte;
            }
            temp->sgte = nuevoNodo;
        }
        lista.longitud++;
    }

    archivo.close();
    cout << "Datos cargados desde " << nombreArchivo << endl;
    return lista;
}

void agregarCarrito(int id_usuario)
{
    ListaCarritos listaCarritosGeneral = leerCSV("output/carrito.csv");
    ListaCarritos listaCarritoActual; // Para almacenar todos los pedidos que haga
    bool confirmacion_agregar = false;
    bool seguir_agregando = false;
    int agregado = 1;
    // int numero_lineas = listaCarritosGeneral.longitud;
    do
    {
        limpiarPantalla();
        setConsoleBackground(White);
        dibujarTitulo(27, 0, 2, letras);
        estructura_menu2(16, 103, 10, 27);

        gotoxy(48,11);
        color(2);
        cout << "Agregando carrito al libro";
        color(0);

        confirmacion_agregar = false;

        // Cuento Filas de Carrito para obtener el Id //El agregado debe considerar las iteraciones
        int id_carrito = contarFilasCSV("output/carrito.csv") + agregado;
        // int id_carrito = numero_lineas + agregado;
        int id_producto, cantidad;
        // Creo una lista para obtener todos los libros
        ListaLibros listalibros;
        listalibros = leerLibrosCSV("output/libros.csv");
        nodoLibros *producto;

        gotoxy(27, 13);
        color(2);
        cout << "ID del libro a comprar: ";
        color(0);
        cin >> id_producto;
        cin.ignore();   


        char desicion;
        producto = buscarLibroPorID(listalibros, id_producto);
        if (producto != nullptr)
        {
            mostrarLibroXidCopy(listalibros, id_producto);
            gotoxy(27, 21);
            color(2);
            cout << "Cantidad que desea comprar: ";
            color(0);
            cin >> cantidad;
            cin.ignore();
            gotoxy(27, 22);
            color(2);
            cout << "Desea agregar " << cantidad << " unidades de " << producto->libro.nombre_Libro << " al carrito? (s/n): ";
            color(0);
            cin >> desicion;
            cin.ignore();
            color(2);
            dibujarTextoPuntos(27, 23, "Agregando al carrito");
            gotoxy(27, 23);
            cout << "Libro(s) agregado(s) al carrito con éxito!";
            color(0);

            if (desicion == 's' || desicion == 'S')
            {
                confirmacion_agregar = true;
            }
        }
        if (confirmacion_agregar)
        {
            // Creo un nodo para almacenar al compra
            Carritos structCarritoActual;

            // Obtener la fecha y hora actual
            time_t now = time(0);
            // Convertir a una estructura tm
            tm *ltm = localtime(&now);
            // Obtener día, mes y año
            int dia = ltm->tm_mday;
            int mes = 1 + ltm->tm_mon;      // tm_mon va de 0 a 11
            int anio = 1900 + ltm->tm_year; // tm_year cuenta años desde 1900

            structCarritoActual.id_carrito = id_carrito;
            structCarritoActual.id_producto = id_producto;
            structCarritoActual.id_cliente = id_usuario;
            structCarritoActual.cantidad = cantidad;
            structCarritoActual.fecha = to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
            structCarritoActual.estado = 0;
            // Agregamos el Nodo a nuestra lista de Pedidos Actuales
            insertarCarritoFinal(&listaCarritoActual, structCarritoActual);
            agregado++;

            seguir_agregando = false;
            gotoxy(27, 26);
            color(2);
            cout << "Desea agregar otro(s) libro(s) a su carrito (s/n): ";
            color(0);
            cin >> desicion;
            cin.ignore();
            if (desicion == 's' || desicion == 'S')
            {
                seguir_agregando = true;
            }
        }

    } while (seguir_agregando);

    if (confirmacion_agregar)
    {
        // Cargare al csv todo lo de lista Carrito Actual
        unirListas(listaCarritosGeneral, listaCarritoActual);
        guardar_CSV_Carritos(&listaCarritosGeneral, "output/carrito.csv");
    }
}