#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <filesystem>

using namespace std;
// Declaraciones previas
void insertarFinalListaLibro(ListaLibros *lista, Libro *libro);
void guardar_CSV_Libros(ListaLibros *lista, string nombreArchivo);
void adicionarCampo();
void modificarLibro();
void insertarLibro(ListaLibros &lista, Libro nuevoLibro);
ListaLibros leerLibrosCSV(string nombreArchivo);
bool mostrarLibroXid(ListaLibros &Libros, int id);

// Inserta libros al final de una lista enlazada
void insertarFinalListaLibro(ListaLibros *lista, Libro *libro)
{
    nodoLibros *nodoLibro = new nodoLibros(*libro);

    if (lista->cabeza == nullptr)
    {
        lista->cabeza = nodoLibro;
    }
    else
    {
        nodoLibros *puntero = lista->cabeza;
        while (puntero->siguiente)
        {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nodoLibro;
    }
    lista->longitud++;
}

// Guarda los datos de la lista de libros en un archivo CSV
void guardar_CSV_Libros(ListaLibros *lista, string nombreArchivo)
{
    fstream archivo(nombreArchivo, fstream::out | fstream::app);

    if (!filesystem::exists("libros.csv"))
    {
        std::cerr << "Error: El directorio 'output' no existe." << std::endl;
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

    // Recorre la lista enlazada y escribe cada nodo en el archivo
    nodoLibros *actual = lista->cabeza;
    while (actual != nullptr)
    {
        Libro libro = actual->libro;
        archivo << libro.id << ","
                << libro.nombre_Libro << ","
                << libro.Autor << ","
                << libro.Ano << ","
                << libro.Genero << ","
                << libro.Stock_Inventario << ","
                << libro.StockActual << ","
                << libro.precio << ","
                << libro.estado << "\n";

        actual = actual->siguiente;
    }

    if (archivo.fail())
    {
        std::cerr << "Error: Fallo al escribir en el archivo." << std::endl;
        return; // Salir con error
    }

    archivo.close();
    cout << "Datos guardados en " << nombreArchivo << endl;
    system("PAUSE");
}

// Interacción con el usuario para ingresar datos
void adicionarCampo()
{
    ListaLibros *listaLibros = new ListaLibros();
    char respuesta[10];
    do
    {
        system("CLS");
        estructura_menu();
        Libro *libro = new Libro();
        libro->id = contarFilasCSV("libros.csv");
        libro->estado = "Disponible";
        gotoxy(52, 12);
        color(2);
        cout << "Registro de libros";
        color(7);
        gotoxy(36, 14);
        color(2);
        cout << "Nombre del libro: ";
        color(7);
        getline(cin, libro->nombre_Libro);
        gotoxy(36, 15);
        color(2);
        cout << "Nombre del autor: ";
        color(7);
        getline(cin, libro->Autor);
        gotoxy(36, 16);
        color(2);
        cout << "year de publicacion: ";
        color(7);
        cin >> libro->Ano;
        cin.ignore();
        gotoxy(36, 17);
        color(2);
        cout << "Genero: ";
        color(7);
        getline(cin, libro->Genero);
        gotoxy(36, 18);
        color(2);
        cout << "Stock total en inventario: ";
        color(7);
        cin >> libro->Stock_Inventario;
        gotoxy(36, 19);
        color(2);
        cout << "Stock actual disponible: ";
        color(7);
        cin >> libro->StockActual;
        gotoxy(36, 20);
        color(2);
        cout << "Precio (S/): ";
        color(7);
        cin >> libro->precio;
        cin.ignore();

        insertarFinalListaLibro(listaLibros, libro);

        gotoxy(36, 22);
        color(2);
        cout << "Desea registrar otro usuario? (s/n): ";
        color(7);
        cin >> respuesta;
    } while (respuesta[0] == 's' || respuesta[0] == 'S');

    guardar_CSV_Libros(listaLibros, "libros.csv");
}

// Funcion para modificar un libro
void modificarLibro()
{
    int id;
    string dato;
    string respuesta;
    int opcion;
    system("CLS");
    estructura_menu();
    color(2);
    gotoxy(52, 12);
    cout << "Modificando Libro";
    gotoxy(36, 14);
    cout << "ID del libro: ";
    color(7);
    fflush(stdin);
    getline(cin, dato);
    id = stoi(dato);

    ListaLibros listalibros;
    listalibros = leerLibrosCSV("Libros.csv");
    gotoxy(36, 15);
    bool encontrado = mostrarLibroXid(listalibros, id);
    if (encontrado)
    {
        gotoxy(36, 24);
        color(2);
        cout << "Desea modificar datos de este usuario? (s/n): ";
        color(7);
        fflush(stdin);
        getline(cin, respuesta);
        cout << respuesta;
        if (respuesta == "s" || respuesta == "S")
        {
            gotoxy(36, 25);
            cout << "Que campo desea modificar? , ingrese el número : ";
            cin >> opcion;
            cin.ignore();

            system("CLS");
            estructura_menu();

            // Datos para ingresar
            int datoInt;
            string datoString;

            // Buscar el nodo del libro con el ID
            nodoLibros *actual = listalibros.cabeza;
            while (actual != nullptr)
            {
                if (actual->libro.id == id) // Si el ID del libro coincide
                {
                    switch (opcion)
                    {
                    case 1:
                        // Modificar nombre
                        gotoxy(36, 20);
                        color(2);
                        cout << "Nuevo nombre: ";
                        color(7);
                        fflush(stdin);
                        getline(cin, datoString);
                        actual->libro.nombre_Libro = datoString;
                        break;
                    case 2:
                        // Modificar autor
                        gotoxy(36, 20);
                        color(2);
                        cout << "Nuevo autor: ";
                        color(7);
                        fflush(stdin);
                        getline(cin, datoString);
                        actual->libro.Autor = datoString;
                        break;
                    case 3:
                        // Modificar género
                        gotoxy(36, 20);
                        color(2);
                        cout << "Nuevo género: ";
                        color(7);
                        fflush(stdin);
                        getline(cin, datoString);
                        actual->libro.Genero = datoString;
                        break;
                    case 4:
                        // Modificar año
                        gotoxy(36, 20);
                        color(2);
                        cout << "Nuevo año: ";
                        color(7);
                        cin >> datoInt;
                        actual->libro.Ano = datoInt;
                        break;
                    case 5:
                        // Modificar stock de inventario
                        gotoxy(36, 20);
                        color(2);
                        cout << "Nuevo stock de inventario: ";
                        color(7);
                        cin >> datoInt;
                        actual->libro.Stock_Inventario = datoInt;
                        break;
                    case 6:
                        // Modificar stock actual
                        gotoxy(36, 20);
                        color(2);
                        cout << "Nuevo stock actual: ";
                        color(7);
                        cin >> datoInt;
                        actual->libro.StockActual = datoInt;
                        break;
                    case 7:
                        // Modificar precio
                        gotoxy(36, 20);
                        color(2);
                        cout << "Nuevo precio: ";
                        color(7);
                        cin >> actual->libro.precio;
                        break;
                    case 8:
                        // Modificar estado
                        gotoxy(36, 20);
                        color(2);
                        cout << "Nuevo estado: ";
                        color(7);
                        fflush(stdin);
                        getline(cin, datoString);
                        actual->libro.estado = datoString;
                        break;
                    default:
                        cout << "Opción no válida." << endl;
                        break;
                    }

                    // Mensaje de éxito
                    gotoxy(36, 26);
                    color(2);
                    cout << "Libro modificado exitosamente." << endl;
                    return; // Salir de la función después de modificar
                }
                actual = actual->siguiente; // Mover al siguiente nodo
            }
        }
        else
        {
            gotoxy(36, 15);
            cout << "Modifiación cancelada";
        }
    }

    limpiarCSV("Libros.csv");
    guardar_CSV_Libros(&listalibros, "Libros.csv");

    gotoxy(36, 22);
    color(2);
    cout << "Modificación realizada con éxito";
    system("pause>0");
}

// Insertar para crear la lista enlazada
void insertarLibro(ListaLibros &lista, Libro nuevoLibro)
{
    nodoLibros *nuevoNodo = new nodoLibros(nuevoLibro);
    nuevoNodo->siguiente = lista.cabeza;
    lista.cabeza = nuevoNodo;
    lista.longitud++;
}

ListaLibros leerLibrosCSV(string nombreArchivo)
{
    ListaLibros listaDeLibros;

    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo. " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        system("PAUSE");
        return listaDeLibros;
    }

    if (archivo.is_open())
    {
        // Leer el archivo línea por línea
        while (getline(archivo, linea))
        {
            stringstream ss(linea);
            string dato;

            Libro libro;

            // Suponiendo que el CSV tiene los campos en el siguiente orden:
            // id, nombre_Libro,Autor,Ano,Genero,Stock_Inventario,StockActual,Precio,Estado
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

            // Insertar el libro en la lista enlazada
            insertarLibro(listaDeLibros, libro);
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
    return listaDeLibros;
}

//
bool mostrarLibroXid(ListaLibros &Libros, int id)
{
    nodoLibros *actual = Libros.cabeza; // Apuntar al primer nodo de la lista

    // Recorrer la lista buscando el libro con el ID indicado
    while (actual != nullptr)
    {
        if (actual->libro.id == id) // Si el ID del libro coincide
        {
            // Mostrar los datos del libro
            cout << "ID: " << actual->libro.id << endl;
            cout << "1. Nombre del Libro: " << actual->libro.nombre_Libro << endl;
            cout << "2. Autor: " << actual->libro.Autor << endl;
            cout << "3. Genero: " << actual->libro.Genero << endl;
            cout << "4. Ano: " << actual->libro.Ano << endl;
            cout << "5. Stock Inventario: " << actual->libro.Stock_Inventario << endl;
            cout << "6. Stock Actual: " << actual->libro.StockActual << endl;
            cout << "7. Precio: " << actual->libro.precio << endl;
            cout << "8. Estado: " << actual->libro.estado << endl;
            return true; // Retorna true si el libro fue encontrado
        }
        actual = actual->siguiente; // Mover al siguiente nodo
    }

    // Si el libro no fue encontrado
    cout << "No se encontro ningun libro con el ID: " << id << endl;
    return false; // Retorna false si no encontró el libro
}

// Insertar para crear la lista enlazada doble
void insertarDobleLibro(ListaDobleLibros &lista, Libro nuevoLibro)
{
    nodoDobleLibros *nuevoNodo = new nodoDobleLibros(nuevoLibro);
    if (lista.cabeza == nullptr)
    {
        lista.cabeza = nuevoNodo;
        lista.final = nuevoNodo; //
    }
    else
    {
        lista.final->siguiente = nuevoNodo;
        nuevoNodo->anterior = lista.final;
        lista.final = nuevoNodo;
    }
    lista.longitud++;
}

// Función para crear una lista enlazada doble en base a los datos del csv
ListaDobleLibros leerLibrosDoblesCSV(string nombreArchivo)
{
    ListaDobleLibros listaLibros;

    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo. " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        system("PAUSE");
        return listaLibros;
    }

    if (archivo.is_open())
    {
        // Leer el archivo línea por línea
        while (getline(archivo, linea))
        {
            stringstream ss(linea);
            string dato;

            Libro libro;

            // Suponiendo que el CSV tiene los campos en el siguiente orden:
            // ID, Nombre, Autor, Año, Género, Stock max, Stock actual, precio, estado
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

            // Insertar el libro en la lista enlazada
            insertarDobleLibro(listaLibros, libro);
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
    return listaLibros;
}

// Funcion para leer una lista enlazada doble
void mostrarLibros(ListaDobleLibros &lista)
{
    system("CLS");
    estructura_menu();
    nodoDobleLibros *actual = lista.cabeza;
    int contador = 0;
    int seguir = 1;
    gotoxy(50, 12);
    color(2);
    cout << "Catálogo de libros";
    gotoxy(20, 14);
    cout << "ID";
    gotoxy(33, 14);
    cout << "Nombre";
    gotoxy(54, 14);
    cout << "Autor";
    gotoxy(74, 14);
    cout << "Genero";
    color(7);
    while (actual != nullptr)
    {

        gotoxy(20, 16 + contador);
        cout << actual->libro.id;
        gotoxy(33, 16 + contador);
        if (actual->libro.nombre_Libro.length() > 20)
        {
            cout << actual->libro.nombre_Libro.substr(0, 15) << "...";
        }
        else
        {
            cout << actual->libro.nombre_Libro;
        }
        gotoxy(54, 16 + contador);
        if (actual->libro.Autor.length() > 20)
        {
            cout << actual->libro.Autor.substr(0, 13) << "...";
        }
        else
        {
            cout << actual->libro.Autor;
        }
        gotoxy(74, 16 + contador);
        cout << actual->libro.Genero;
        actual = actual->siguiente;

        contador++;

        if (contador == 10)
        {
            gotoxy(20, 27);
            color(2);
            cout << "Ingrese? (0 = salir, 1 = anterior, 2 = siguiente): ";
            color(7);
            cin >> seguir;
            fflush(stdin);
            if (seguir == 0)
            {
                break;
            }
            else if (seguir == 1)
            {
                contador = 0;
                for (int i = 0; i < 10; i++)
                {
                    if (actual->anterior != nullptr)
                    {
                        actual = actual->anterior;
                    }
                }
                system("CLS");
                estructura_menu();
                gotoxy(50, 12);
                color(2);
                cout << "Catálogo de libros";
                gotoxy(20, 14);
                cout << "ID";
                gotoxy(33, 14);
                cout << "Nombre";
                gotoxy(54, 14);
                cout << "Autor";
                gotoxy(74, 14);
                cout << "Genero";
                color(7);
            }
            else if (seguir == 2)
            {
                system("CLS");
                estructura_menu();
                gotoxy(50, 12);
                color(2);
                cout << "Catálogo de libros";
                gotoxy(20, 14);
                cout << "ID";
                gotoxy(33, 14);
                cout << "Nombre";
                gotoxy(54, 14);
                cout << "Autor";
                gotoxy(74, 14);
                cout << "Genero";
                color(7);
            }
            contador = 0;
        }
    }
    system("PAUSE>0");
}