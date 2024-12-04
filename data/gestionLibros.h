#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <filesystem>
#include <ctime> /*Para registrar la fecha */
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <conio.h>
#include <locale>
#include <ctime>
using namespace std;

// Declaraciones previas
void insertarLibrosFinal(ListaLibros *lista, Libro *libro);
void guardar_CSV_Libros(ListaLibros *lista, string nombreArchivo);
void adicionarCampo();
void modificarLibro();
ListaLibros leerLibrosCSV(string nombreArchivo);
bool mostrarLibroXid(ListaLibros &Libros, int id);
void insertarArbolLibro(LibroNodoArbol *&raiz, Libro *libro);
void buscarLibroArbol(LibroNodoArbol *raiz, const string &nombreLibroBuscar, ListaLibros &resultados, bool &busquedaExacta);
LibroNodoArbol *leerLibrosArbol(string nombreArchivo, bool userView);

// --- FUNCIONES PARA LISTAS ENLAZADAS DE LIBROS ---
// Inserta libros al final de una lista enlazada
void insertarLibrosFinal(ListaLibros *lista, Libro *libro)
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

    if (!filesystem::exists("output/libros.csv"))
    {
        // std::cerr << "Error: El directorio 'output' no existe." << std::endl;
        pausa();
        return;
    }

    if (!archivo.is_open())
    {
        // cout << "No se pudo abrir el archivo. " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        pausa();
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
                << libro.precio << ","
                << libro.StockInventario << ","
                << libro.StockActual << "\n";

        actual = actual->siguiente;
    }

    if (archivo.fail())
    {
        std::cerr << "Error: Fallo al escribir en el archivo." << std::endl;
        return; // Salir con error
    }

    archivo.close();
    // cout << "Datos guardados en " << nombreArchivo << endl;
    pausa();
}

// Interacción con el usuario para ingresar datos
void adicionarCampo()
{
    ListaLibros *listaLibros = new ListaLibros();
    int contador = 1;
    char respuesta[10];
    do
    {
        limpiarPantalla();
        setConsoleBackground(White);
        dibujarTitulo(24, 0, 2, letras);
        estructura_menu2(16, 103, 10, 27);
        Libro *libro = new Libro();
        libro->estado = "Disponible";
        gotoxy(52, 12);
        color(2);
        cout << "Registro de libros";

        // Ingremos nombre del libro
        bool nombreCorrecto = false;
        do
        {
            gotoxy(27, 14);
            color(2);
            cout << "Nombre del libro: ";
            color(0);
            getline(cin, libro->nombre_Libro);
            if (libro->nombre_Libro.length() > 0)
            {
                nombreCorrecto = true;
            }
            else
            {
                gotoxy(27, 15);
                color(4);
                cout << "Ingrese un nombre v"<<(char)160<<"lido";
                pausa();
                limpiarArea(27, 14, 50, 1);
                limpiarArea(27, 15, 50, 1);
            }
        } while (!nombreCorrecto);

        // Ingresamos autor
        bool autorCorrecto = false;
        do
        {
            gotoxy(27, 15);
            color(2);
            cout << "Nombre del autor: ";
            color(0);
            getline(cin, libro->Autor);
            if (libro->Autor.length() > 0)
            {
                autorCorrecto = true;
            }
            else
            {
                gotoxy(27, 16);
                color(4);
                cout << "Ingrese un autor v"<<(char)160<<"lido";
                pausa();
                limpiarArea(27, 15, 50, 1);
                limpiarArea(27, 16, 50, 1);
            }
        } while (!autorCorrecto);

        // Ingresamos año de publicación
        bool anoCorrecto = false;
        do
        {
            gotoxy(27, 16);
            color(2);
            cout << "A"<<(char)164<<"o de publicaci"<<(char)162<<"n: ";
            color(0);
            cin >> libro->Ano;
            cin.ignore();
            if (libro->Ano > 0 && libro->Ano <= 2024)
            {
                anoCorrecto = true;
            }
            else
            {
                gotoxy(27, 17);
                color(4);
                cout << "Ingrese un año v"<<(char)160<<"lido";
                pausa();
                limpiarArea(27, 16, 50, 1);
                limpiarArea(27, 17, 50, 1);
            }
        } while (!anoCorrecto);

        // Ingresamos género

        gotoxy(27, 17);
        color(2);
        cout << "Genero: ";
        color(0);
        getline(cin, libro->Genero);

        // Ingresamos stock ingresado
        bool stockCorrecto = false;
        do
        {
            gotoxy(27, 18);
            color(2);
            cout << "Stock ingresado: ";
            color(0);
            cin >> libro->StockInventario;
            cin.ignore();

            if (libro->StockInventario > 0)
            {
                break;
            }
            else
            {
                gotoxy(27, 19);
                color(4);
                cout << "Ingrese un stock v"<<(char)160<<"lido";
                pausa();
                limpiarArea(27, 18, 50, 1);
                limpiarArea(27, 19, 50, 1);
            }
        } while (!stockCorrecto);
        libro->StockActual = libro->StockInventario;

        // Ingresamos precio
        bool precioCorrecto = false;
        do
        {
            gotoxy(27, 19);
            color(2);
            cout << "Precio (S/): ";
            color(0);
            cin >> libro->precio;
            cin.ignore();

            if (libro->precio > 0)
            {
                precioCorrecto = true;
            }
            else
            {
                gotoxy(27, 20);
                color(4);
                cout << "Ingrese un precio v"<<(char)160<<"lido";
                pausa();
                limpiarArea(27, 19, 50, 1);
                limpiarArea(27, 20, 50, 1);
            }
        } while (!precioCorrecto);

        insertarLibrosFinal(listaLibros, libro);
        contador++;

        dibujarTextoPuntos(27, 21, "Registrando libro(s)");
        gotoxy(27, 21);
        cout << "Libro(s) registrado con exito!";

        gotoxy(27, 24);
        color(2);
        cout << "Desea registrar otro(s) libro(s)? (s/n): ";
        color(0);
        cin >> respuesta;
        cin.ignore();
    } while (respuesta[0] == 's' || respuesta[0] == 'S');

    guardar_CSV_Libros(listaLibros, "output/libros.csv");
}

// Funcion para modificar un libro
void modificarLibro()
{
    int id;
    string dato;
    string respuesta;
    int opcion;
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(24, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    color(2);
    gotoxy(52, 12);
    cout << "Modificando Libro";
    gotoxy(36, 14);
    cout << "ID del libro: ";
    color(0);
    fflush(stdin);
    getline(cin, dato);
    id = stoi(dato);

    ListaLibros listalibros;
    listalibros = leerLibrosCSV("output/libros.csv");
    gotoxy(36, 15);
    bool encontrado = mostrarLibroXid(listalibros, id);
    if (encontrado)
    {
        gotoxy(36, 25);
        color(2);
        cout << "Desea modificar datos de este libro? (s/n): ";
        color(0);
        fflush(stdin);
        getline(cin, respuesta);
        cout << respuesta;
        if (respuesta == "s" || respuesta == "S")
        {
            gotoxy(36, 26);
            color(2);
            cout << "Que campo desea modificar?: ";
            color(0);
            cin >> opcion;
            cin.ignore();

            limpiarPantalla();
            setConsoleBackground(White);
            dibujarTitulo(24, 0, 2, letras);
            estructura_menu2(16, 103, 10, 27);
            color(2);
            gotoxy(52, 12);
            cout << "Modificando Libro";
            gotoxy(36, 14);
            cout << "ID del libro: ";
            color(0);
            cout << id;
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
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo nombre: ";
                        color(0);
                        cout << actual->libro.nombre_Libro;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo nombre: ";
                        color(0);
                        fflush(stdin);
                        getline(cin, datoString);
                        actual->libro.nombre_Libro = datoString;
                        break;
                    case 2:
                        // Modificar autor
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo autor: ";
                        color(0);
                        cout << actual->libro.Autor;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo autor: ";
                        color(0);
                        fflush(stdin);
                        getline(cin, datoString);
                        actual->libro.Autor = datoString;
                        break;
                    case 3:
                        // Modificar género
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo g"<<(char)130<<"nero: ";
                        color(0);
                        cout << actual->libro.Genero;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo g"<<(char)130<<"nero: ";
                        color(0);
                        fflush(stdin);
                        getline(cin, datoString);
                        actual->libro.Genero = datoString;
                        break;
                    case 4:
                        // Modificar año
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo a"<<(char)164<<"o: ";
                        color(0);
                        cout << actual->libro.Ano;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo a"<<(char)164<<"o: ";
                        color(0);
                        cin >> datoInt;
                        cin.ignore();
                        actual->libro.Ano = datoInt;
                        break;
                    case 5:
                        // Modificar precio
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo precio: ";
                        color(0);
                        cout << actual->libro.precio;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo precio: ";
                        color(0);
                        cin >> actual->libro.precio;
                        cin.ignore();
                        break;
                    case 6:
                        // Modificar estado
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo estado: ";
                        color(0);
                        cout << actual->libro.estado;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo estado: ";
                        color(0);
                        getline(cin, datoString);
                        actual->libro.estado = datoString;
                        break;
                    default:
                        cout << "Opci"<<(char)162<<"n no v"<<(char)160<<"lida." << endl;
                        break;
                    }

                    // Mensaje de éxito
                    color(2);
                    dibujarTextoPuntos(36, 19, "Modificando libro");
                    gotoxy(36, 19);
                    cout << "Libro modificado exitosamente";
                    color(0);
                    system("pause>0");
                    limpiarCSV("output/libros.csv");
                    guardar_CSV_Libros(&listalibros, "output/libros.csv");
                    return; // Salir de la función después de modificar
                }
                actual = actual->siguiente; // Mover al siguiente nodo
            }
        }
        else
        {
            color(4);
            dibujarTextoPuntos(36, 15, "Cancelando");
            gotoxy(36, 15);
            cout << "Modifiaci"<<(char)162<<"n cancelada";
            system("pause>0");
        }
    }
    dibujarTextoPuntos(36, 22, "Modificando libro");
    gotoxy(36, 22);
    color(2);
    cout << "Modificaci"<<(char)162<<"n realizada con "<<(char)130<<"xito";
    system("pause>0");
}

void insertarNodoLibroAlFinal(ListaLibros *lista, nodoLibros *nodo)
{
    // Verificar que el nodo no sea nullptr
    if (nodo == nullptr)
    {
        std::cerr << "Error: Nodo es nullptr y no puede insertarse en la lista." << std::endl;
        return;
    }

    // Asegurar que el nodo agregado al final apunte a nullptr
    nodo->siguiente = nullptr;

    // Verificar si la lista está vacía; si es así, el nuevo nodo será la cabeza
    if (lista->cabeza == nullptr)
    {
        lista->cabeza = nodo;
    }
    else
    {
        // Recorre hasta el último nodo de la lista
        nodoLibros *puntero = lista->cabeza;
        while (puntero->siguiente != nullptr)
        {
            puntero = puntero->siguiente;
        }
        // Conectar el nuevo nodo al final de la lista
        puntero->siguiente = nodo;
    }

    // Incrementar la longitud de la lista
    lista->longitud++;
}

// Creada para poder ser Usada en Lista LibroEspecifico en CarritoLibro.h
void eliminarPrimerLibro(ListaLibros *lista)
{
    // Verificar si la lista está vacía
    if (lista->cabeza == nullptr)
    {
        cout << "La lista est"<<(char)160<<" vac"<<(char)161<<"a. No hay libros para eliminar." << endl;
        return;
    }

    // Guardar el nodo actual de la cabeza en un puntero temporal
    nodoLibros *nodoAEliminar = lista->cabeza;

    // Mover la cabeza al siguiente nodo
    lista->cabeza = lista->cabeza->siguiente;

    // Liberar la memoria del nodo eliminado
    delete nodoAEliminar;

    // Disminuir la longitud de la lista
    lista->longitud--;
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

            // Suponiendo que el CSV tiene los campos en el siguiente orden (para mostrar catálogo):
            // id, Nombre, Autor, Año, Género, precio, stock inventario, stock actual
            getline(ss, dato, ',');
            libro.id = stoi(dato); // Convertir a entero
            getline(ss, libro.nombre_Libro, ',');
            getline(ss, libro.Autor, ',');
            getline(ss, dato, ',');
            libro.Ano = stoi(dato);
            getline(ss, libro.Genero, ',');
            getline(ss, dato, ',');
            libro.precio = stoi(dato);
            getline(ss, dato, ',');
            libro.StockInventario = stoi(dato);
            getline(ss, dato, ',');
            libro.StockActual = stoi(dato);

            // Insertar el libro en la lista enlazada
            insertarLibrosFinal(&listaDeLibros, &libro);
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
    return listaDeLibros;
}

// Muestra un libro al ingresar su ID
bool mostrarLibroXid(ListaLibros &Libros, int id)
{
    nodoLibros *actual = Libros.cabeza; // Apuntar al primer nodo de la lista

    // Recorrer la lista buscando el libro con el ID indicado
    while (actual != nullptr)
    {
        if (actual->libro.id == id) // Si el ID del libro coincide
        {
            // Mostrar los datos del libros
            gotoxy(36, 16);
            color(2);
            cout << "1. Nombre del Libro: ";
            color(0);
            cout << actual->libro.nombre_Libro;
            gotoxy(36, 17);
            color(2);
            cout << "2. Autor: ";
            color(0);
            cout << actual->libro.Autor;
            gotoxy(36, 18);
            color(2);
            cout << "3. Genero: ";
            color(0);
            cout << actual->libro.Genero;
            gotoxy(36, 19);
            color(2);
            cout << "4. Ano: ";
            color(0);
            cout << actual->libro.Ano;
            gotoxy(36, 20);
            color(2);
            cout << "5. Precio: ";
            color(0);
            cout << actual->libro.precio;
            gotoxy(36, 21);
            color(2);
            cout << "6. Estado: ";
            color(0);
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

// -- FUNCIONES PARA VER CATÁLOGO DE LIBROS --

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
ListaDobleLibros leerLibrosDoblesCSV(string nombreArchivo, bool userView)
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

            // Suponiendo que el CSV tiene los campos en el siguiente orden (para mostrar catálogo):
            // ID, Nombre, Autor, Año, Género, Stock, precio, estado
            getline(ss, dato, ',');
            libro.id = stoi(dato); // Convertir a entero
            getline(ss, libro.nombre_Libro, ',');
            getline(ss, libro.Autor, ',');
            getline(ss, dato, ',');
            libro.Ano = stoi(dato);
            getline(ss, libro.Genero, ',');
            getline(ss, dato, ',');
            libro.precio = stoi(dato);
            getline(ss, dato, ',');
            libro.StockInventario = stoi(dato);
            getline(ss, dato, ',');
            libro.StockActual = stoi(dato);

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
void mostrarLibros(ListaDobleLibros &lista, bool userView)
{
    // Verificamos si la lista está vacía
    if (lista.cabeza == nullptr)
    {
        cout << "La lista de libros est"<<(char)160<<" vac"<<(char)161<<"a." << endl;
        return;
    }

    // Creamos un nodo de los libros para tener referencia de la posición en la lista (como puntero)
    nodoDobleLibros *actual = lista.cabeza;
    int opcion = -1; // Variable para las opciones del menú (Salir, página anterior, página siguiente)

    while (opcion != 0) // 0 significa salir
    {
        limpiarPantalla();
        setConsoleBackground(White);
        dibujarTitulo(24, 0, 2, letras);
        estructura_menu2(5, 114, 10, 28);

        int contador = 0; // Contador para mostrar los libros de 10 en 10

        gotoxy(50, 11);
        color(2);
        cout << "Cat"<<(char)160<<"logo de libros";

        gotoxy(10, 13);
        cout << "ID";
        gotoxy(16, 13);
        cout << "Nombre";
        gotoxy(50, 13);
        cout << "Autor";
        gotoxy(74, 13);
        cout << "G"<<(char)130<<"nero";
        gotoxy(96, 13);
        cout << "A"<<(char)164<<"o";
        gotoxy(105, 13);
        cout << "Stock";

        color(0);

        // Mostrar los libros a partir de la posición actual
        nodoDobleLibros *temporal = actual; // Se usa un puntero temporal para mostrar los libros
        while (temporal != nullptr && contador < 10)
        {

            gotoxy(10, 15 + contador);
            cout << temporal->libro.id;

            gotoxy(16, 15 + contador);
            if (temporal->libro.nombre_Libro.length() > 25)
            {
                cout << temporal->libro.nombre_Libro.substr(0, 22) + "...";
            }
            else
            {
                cout << temporal->libro.nombre_Libro;
            }

            gotoxy(50, 15 + contador);
            if (temporal->libro.Autor.length() > 18)
            {
                cout << temporal->libro.Autor.substr(0, 15) + "...";
            }
            else
            {
                cout << temporal->libro.Autor;
            }

            gotoxy(74, 15 + contador);
            if (temporal->libro.Genero.length() > 17)
            {
                cout << temporal->libro.Genero.substr(0, 14) + "...";
            }
            else
            {
                cout << temporal->libro.Genero;
            }

            gotoxy(96, 15 + contador);
            cout << temporal->libro.Ano;
            gotoxy(105, 15 + contador);
            cout << temporal->libro.StockActual;

            temporal = temporal->siguiente;
            contador++;
        }

        // Mostrar el menú de navegación al final de la lista
        gotoxy(10, 26);
        color(2);

        cout << "Opciones: (0 = salir, 1 = anterior, 2 = siguiente, 3 = buscar por t"<<(char)161<<"tulo): ";

        color(0);
        cin >> opcion;
        cin.ignore();

        // Manejo de la navegación
        if (opcion == 1) // Retroceder
        {
            // Retroceder 10 libros si es posible
            for (int i = 0; i < 10 && actual->anterior != nullptr; i++)
            {
                actual = actual->anterior;
            }
        }
        else if (opcion == 2) // Avanzar
        {
            // Avanzar 10 libros si es posible
            for (int i = 0; i < 10 && actual->siguiente != nullptr; i++)
            {
                actual = actual->siguiente;
            }
        }
        else if (opcion == 3 && userView) // Filtro
        {
            // Creo un árbol con los libros para buscar por título
            LibroNodoArbol *arbol = leerLibrosArbol("output/libros.csv", true);
            // Bool para saber si se encontró el libro exacto o son resultados similares
            bool busquedaExacta = false;
            // Variable para guardar el titulo ingresado por el usuario
            string titulo;
            gotoxy(10, 27);
            color(2);
            cout << "T"<<(char)161<<"tulo del libro: ";
            color(0);
            getline(cin, titulo);
            // Lista enlazada para guardar los libros encontrados
            ListaLibros resultados;
            // Buscar el libro en el árbol
            buscarLibroArbol(arbol, titulo, resultados, busquedaExacta);
            // Libro *libroEncontrado = buscarLibroArbol(arbol, titulo, busquedaExacta);

            limpiarPantalla();
            setConsoleBackground(White);
            dibujarTitulo(24, 0, 2, letras);
            estructura_menu2(5, 114, 10, 28);

            int contador = 0; // Contador para mostrar los libros de 10 en 10

            gotoxy(50, 11);
            color(2);
            cout << "Cat"<<(char)160<<"logo de libros";

            gotoxy(10, 13);
            color(2);
            if (busquedaExacta)
            {
                cout << "Resultados para: ";
                color(0);
                cout << titulo;
            }
            else
            {
                cout << "Resultados similares a: ";
                color(0);
                cout << titulo;
            }

            color(2);
            gotoxy(10, 15);
            cout << "ID";
            gotoxy(16, 15);
            cout << "Nombre";
            gotoxy(50, 15);
            cout << "Autor";
            gotoxy(74, 15);
            cout << "G"<<(char)130<<"nero";
            gotoxy(96, 15);
            cout << "A"<<(char)164<<"o";
            gotoxy(105, 15);
            cout << "Stock";
            color(0);

            // Mostrar los libros a partir de la posición actual
            nodoLibros *temporal = resultados.cabeza;
            while (temporal != nullptr)
            {
                gotoxy(10, 17 + contador);
                cout << temporal->libro.id;

                gotoxy(16, 17 + contador);
                if (temporal->libro.nombre_Libro.length() > 25)
                {
                    cout << temporal->libro.nombre_Libro.substr(0, 22) + "...";
                }
                else
                {
                    cout << temporal->libro.nombre_Libro;
                }

                gotoxy(50, 17 + contador);
                if (temporal->libro.Autor.length() > 18)
                {
                    cout << temporal->libro.Autor.substr(0, 15) + "...";
                }
                else
                {
                    cout << temporal->libro.Autor;
                }

                gotoxy(74, 17 + contador);
                if (temporal->libro.Genero.length() > 17)
                {
                    cout << temporal->libro.Genero.substr(0, 14) + "...";
                }
                else
                {
                    cout << temporal->libro.Genero;
                }

                gotoxy(96, 17 + contador);
                cout << temporal->libro.Ano;
                gotoxy(105, 17 + contador);
                cout << temporal->libro.StockActual;

                temporal = temporal->siguiente;
                contador++;
            }
            getch();
        }
        else if (opcion != 0)
        {
            cout << "Opci"<<(char)162<<"n no v"<<(char)160<<"lida. Int"<<(char)130<<"ntelo de nuevo." << endl;
            pausa();
        }
    }
}

// Buscar libro por id
nodoLibros *buscarLibroPorID(ListaLibros &listaLibros, int idLibro)
{
    nodoLibros *actual = listaLibros.cabeza;
    while (actual != nullptr)
    {
        if (actual->libro.id == idLibro)
        {
            return actual; // Libro encontrado
        }
        actual = actual->siguiente;
    }
    return nullptr; // Libro no encontrado
}

// Buscar libro por título y estado
nodoLibros *buscarLibroPorTitulo(ListaLibros &listaLibros, string tituloLibro, string estado)
{
    nodoLibros *actual = listaLibros.cabeza;
    while (actual != nullptr)
    {
        int distancia = distanciaLevenshtein(actual->libro.nombre_Libro, tituloLibro);
        if (distancia < 4 && actual->libro.estado == estado)
        {
            return actual; // Libro encontrado
        }
        actual = actual->siguiente;
    }
    return nullptr; // Libro no encontrado
}

// Función para guardar los datos de los libros en un archivo CSV
void guardar_CSV_Libros_Sobreescribir(ListaLibros *lista, string nombreArchivo)
{
    fstream archivo(nombreArchivo, fstream::out);

    if (!filesystem::exists("output/libros.csv"))
    {
        // std::cerr << "Error: El directorio 'output' no existe." << std::endl;
        pausa();
        return;
    }

    if (!archivo.is_open())
    {
        // cout << "No se pudo abrir el archivo. " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        pausa();
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
                << libro.precio << ","
                << libro.StockInventario << ","
                << libro.StockActual << "\n";

        actual = actual->siguiente;
    }

    if (archivo.fail())
    {
        std::cerr << "Error: Fallo al escribir en el archivo." << std::endl;
        return; // Salir con error
    }

    archivo.close();
    // cout << "Datos guardados en " << nombreArchivo << endl;
}

// -- FUNCIONES PARA EL ÁRBOL DE LIBROS --

// Función para insertar nodos en el arbol
void insertarArbolLibro(LibroNodoArbol *&raiz, Libro *libro)
{
    if (raiz == nullptr)
    {
        // Si es el primer elemento, se crea la raíz
        raiz = new LibroNodoArbol(*libro);
    }
    else
    {
        if (libro->nombre_Libro < raiz->libro.nombre_Libro)
        {
            insertarArbolLibro(raiz->izquierda, libro);
        }
        else
        {
            insertarArbolLibro(raiz->derecha, libro);
        }
    }
}

// Función para buscar un libro en el árbol
void buscarLibroArbol(LibroNodoArbol *raiz, const string &nombreLibroBuscar, ListaLibros &resultados, bool &busquedaExacta)
{
    if (raiz == nullptr)
    {
        return;
    }

    // Convertir ambos títulos a minúsculas
    string tituloNodo = convertirAMinuscula(raiz->libro.nombre_Libro);
    string tituloBuscar = convertirAMinuscula(nombreLibroBuscar);

    if (tituloNodo == tituloBuscar)
    {
        busquedaExacta = true;
        insertarLibrosFinal(&resultados, &raiz->libro);
        return;
    }

    // Buscar si el título ingresado es una subcadena del título del nodo
    if (tituloNodo.find(tituloBuscar) != string::npos)
    {
        insertarLibrosFinal(&resultados, &raiz->libro);
    }

    // Buscar en el subárbol izquierdo
    buscarLibroArbol(raiz->izquierda, nombreLibroBuscar, resultados, busquedaExacta);

    // Buscar en el subárbol derecho
    buscarLibroArbol(raiz->derecha, nombreLibroBuscar, resultados, busquedaExacta);
}

// Función para leer los libros de un archivo CSV y crear un árbol
LibroNodoArbol *leerLibrosArbol(string nombreArchivo, bool userView)
{
    LibroNodoArbol *arbol = nullptr;
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo. " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        system("PAUSE");
        return arbol;
    }

    // Leer el archivo línea por línea
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string dato;

        Libro libro;

        // Suponiendo que el CSV tiene los campos en el siguiente orden (para mostrar catálogo):
        // ID, Nombre, Autor, Año, Género, precio, stock inventario, stock actual
        try
        {
            getline(ss, dato, ',');
            libro.id = stoi(dato); // Convertir a entero
            getline(ss, libro.nombre_Libro, ',');
            getline(ss, libro.Autor, ',');
            getline(ss, dato, ',');
            libro.Ano = stoi(dato);
            getline(ss, libro.Genero, ',');
            getline(ss, dato, ',');
            libro.precio = stoi(dato);
            getline(ss, dato, ',');
            libro.StockInventario = stoi(dato);
            getline(ss, dato, ',');
            libro.StockActual = stoi(dato);

            // Insertar el libro en el árbol
            insertarArbolLibro(arbol, &libro);
        }
        catch (const std::exception &e)
        {
        }
    }

    archivo.close();
    return arbol;
}

bool determinarSiExisteLibro(const ListaLibros &lista, const string &nombreBusco) {
    nodoLibros *actual = lista.cabeza; // Comienza desde el primer nodo
    while (actual != nullptr) {
        if (actual->libro.nombre_Libro == nombreBusco) {
            return true; // Si el nombre coincide, devuelve true
        }
        actual = actual->siguiente; // Avanza al siguiente nodo
    }
    return false; // Si no se encuentra el libro, devuelve false
}

void incrementarPopularidadLibro(ListaLibros &lista, const string &nLibro) {
    nodoLibros *actual = lista.cabeza; // Comienza desde el primer nodo
    while (actual != nullptr) {
        if (actual->libro.nombre_Libro == nLibro) {
            actual->libro.popularidad++; // Incrementa la popularidad en 1
            return; // Termina la función una vez se ha encontrado y actualizado el libro
        }
        actual = actual->siguiente; // Avanza al siguiente nodo
    }
}

void vaciarListaLibros(ListaLibros &lista) {
    nodoLibros *actual = lista.cabeza;
    while (actual != nullptr) {
        nodoLibros *temp = actual;
        actual = actual->siguiente;
        delete temp; // Libera la memoria del nodo actual
    }
    lista.cabeza = nullptr; // La cabeza de la lista ahora es nullptr, dejando la lista vacía
    lista.longitud = 0; // Resetea la longitud de la lista a 0
}

nodoLibros* obtenerLibroMasPopular(ListaLibros &lista) {
    if (lista.cabeza == nullptr) {
        return nullptr; // Si la lista está vacía, devuelve nullptr
    }

    nodoLibros *actual = lista.cabeza;
    nodoLibros *masPopular = actual;

    while (actual != nullptr) {
        if (actual->libro.popularidad > masPopular->libro.popularidad) {
            masPopular = actual; // Actualiza el nodo con la mayor popularidad
        }
        actual = actual->siguiente;
    }

    return masPopular; // Devuelve el nodo con la mayor popularidad
}