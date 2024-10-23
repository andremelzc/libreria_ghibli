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
    int contador=1;
    char respuesta[10];
    do
    {
        system("CLS");
        estructura_menu();
        Libro *libro = new Libro();
        libro->id = contarFilasCSV("libros.csv")+contador;
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
        cin.ignore();
        contador++;
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
    listalibros = leerLibrosCSV("libros.csv");
    gotoxy(36, 15);
    bool encontrado = mostrarLibroXid(listalibros, id);
    if (encontrado)
    {
        gotoxy(36, 25);
        color(2);
        cout << "Desea modificar datos de este usuario? (s/n): ";
        color(7);
        fflush(stdin);
        getline(cin, respuesta);
        cout << respuesta;
        if (respuesta == "s" || respuesta == "S")
        {
            gotoxy(36, 26);
            color(2);
            cout << "Que campo desea modificar?: ";
            color(7);
            cin >> opcion;
            cin.ignore();

            system("CLS");
            estructura_menu();
            color(2);
            gotoxy(52, 12);
            cout << "Modificando Libro";
            gotoxy(36, 14);
            cout<<"ID del libro: ";
            color(7);
            cout<<id;
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
                        color(7);
                        cout << actual->libro.nombre_Libro;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo nombre: ";
                        color(7);
                        fflush(stdin);
                        getline(cin, datoString);
                        actual->libro.nombre_Libro = datoString;
                        break;
                    case 2:
                        // Modificar autor
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo autor: ";
                        color(7);
                        cout << actual->libro.Autor;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo autor: ";
                        color(7);
                        fflush(stdin);
                        getline(cin, datoString);
                        actual->libro.Autor = datoString;
                        break;
                    case 3:
                        // Modificar género
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo género: ";
                        color(7);
                        cout << actual->libro.Genero;
                        gotoxy(36, 17); 
                        color(2);
                        cout << "Nuevo género: ";
                        color(7);
                        fflush(stdin);
                        getline(cin, datoString);
                        actual->libro.Genero = datoString;
                        break;
                    case 4:
                        // Modificar año
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo año: ";
                        color(7);
                        cout << actual->libro.Ano;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo año: ";
                        color(7);
                        cin >> datoInt;
                        cin.ignore();
                        actual->libro.Ano = datoInt;
                        break;
                    case 5:
                        // Modificar stock de inventario
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo stock de inventario: ";
                        color(7);
                        cout << actual->libro.Stock_Inventario;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo stock de inventario: ";
                        color(7);
                        cin >> datoInt;
                        cin.ignore();
                        actual->libro.Stock_Inventario = datoInt;
                        break;
                    case 6:
                        // Modificar stock actual
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo stock actual: ";
                        color(7);
                        cout << actual->libro.StockActual;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo stock actual: ";
                        color(7);
                        cin >> datoInt;
                        cin.ignore();
                        actual->libro.StockActual = datoInt;
                        break;
                    case 7:
                        // Modificar precio
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo precio: ";
                        color(7);
                        cout << actual->libro.precio;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo precio: ";
                        color(7);
                        cin >> actual->libro.precio;
                        cin.ignore();
                        break;
                    case 8:
                        // Modificar estado
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo estado: ";
                        color(7);
                        cout << actual->libro.estado;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo estado: ";
                        color(7);
                        getline(cin, datoString);
                        actual->libro.estado = datoString;
                        break;
                    default:
                        cout << "Opción no válida." << endl;
                        break;
                    }

                    // Mensaje de éxito
                    gotoxy(36, 19);
                    color(2);
                    cout << "Libro modificado exitosamente." << endl;
                    color(7);
                    system("pause>0");
                    limpiarCSV("libros.csv");
                    guardar_CSV_Libros(&listalibros, "libros.csv");
                    return; // Salir de la función después de modificar
                }
                actual = actual->siguiente; // Mover al siguiente nodo
            }
        }
        else
        {
            gotoxy(36, 15);
            cout << "Modifiación cancelada";
            system("pause>0");
        }
    }

    
    

    gotoxy(36, 22);
    color(2);
    cout << "Modificación realizada con éxito";
    system("pause>0");
}

// Insertar al final de la lista
void insertarLibrosFinal(ListaLibros *lista, Libro *libro)
{
    nodoLibros *nodo = new nodoLibros(*libro);

    if (lista->cabeza == nullptr)
    {
        lista->cabeza = nodo;
    }
    else
    {
        nodoLibros *puntero = lista->cabeza;
        while (puntero->siguiente)
        {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nodo;
    }
    lista->longitud++;
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
            color(7);
            cout << actual->libro.nombre_Libro;
            gotoxy(36, 17);
            color(2);
            cout << "2. Autor: ";
            color(7);
            cout << actual->libro.Autor;
            gotoxy(36, 18);
            color(2);
            cout << "3. Genero: ";
            color(7);
            cout << actual->libro.Genero;
            gotoxy(36, 19);
            color(2);
            cout << "4. Ano: ";
            color(7);
            cout << actual->libro.Ano;
            gotoxy(36, 20);
            color(2);
            cout << "5. Stock Inventario: ";
            color(7);
            cout << actual->libro.Stock_Inventario;
            gotoxy(36, 21);
            color(2);
            cout << "6. Stock Actual: ";
            color(7);
            cout << actual->libro.StockActual;
            gotoxy(36, 22);
            color(2);
            cout << "7. Precio: ";
            color(7);
            cout << actual->libro.precio;
            gotoxy(36, 23);
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
    // Verificamos si la lista está vacía
    if (lista.cabeza == nullptr)
    {
        cout << "La lista de libros está vacía." << endl;
        return;
    }

    // Creamos un nodo de los libros para tener referencia de la posición en la lista (como puntero)
    nodoDobleLibros* actual = lista.cabeza;
    int opcion = -1;  // Variable para las opciones del menú (Salir, página anterior, página siguiente)

    while (opcion != 0)  // 0 significa salir
    {
        system("CLS");
        estructura_menu();

        int contador = 0;  // Contador para mostrar los libros de 10 en 10

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
        cout << "Género";
        color(7);

        // Mostrar los libros a partir de la posición actual
        nodoDobleLibros* temporal = actual;  // Se usa un puntero temporal para mostrar los libros
        while (temporal != nullptr && contador < 10)
        {
            gotoxy(20, 16 + contador);
            cout << temporal->libro.id;

            gotoxy(33, 16 + contador);
            if(temporal->libro.nombre_Libro.length() > 20)
            {
                cout << temporal->libro.nombre_Libro.substr(0, 17) + "...";
            }
            else
            {
                cout << temporal->libro.nombre_Libro;
            }

            gotoxy(54, 16 + contador);
            if(temporal->libro.Autor.length() > 20)
            {
                cout << temporal->libro.Autor.substr(0, 17) + "...";
            }
            else
            {
                cout << temporal->libro.Autor;
            }

            gotoxy(74, 16 + contador);
            cout << temporal->libro.Genero;

            temporal = temporal->siguiente;
            contador++;
        }

        // Mostrar el menú de navegación al final de la lista
        gotoxy(20, 27);
        color(2);
        cout << "Ingrese opción: (0 = salir, 1 = anterior, 2 = siguiente): ";
        color(7);
        cin >> opcion;

        // Manejo de la navegación
        if (opcion == 1)  // Retroceder
        {
            // Retroceder 10 libros si es posible
            for (int i = 0; i < 10 && actual->anterior != nullptr; i++)
            {
                actual = actual->anterior;
            }
        }
        else if (opcion == 2)  // Avanzar
        {
            // Avanzar 10 libros si es posible
            for (int i = 0; i < 10 && actual->siguiente != nullptr; i++)
            {
                actual = actual->siguiente;
            }
        }
        else if (opcion != 0)
        {
            cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }
    }

    system("PAUSE>0");
}

nodoLibros* buscarLibroPorID(ListaLibros& listaLibros, int idLibro) {
    nodoLibros* actual = listaLibros.cabeza;
    while (actual != nullptr) {
        if (actual->libro.id == idLibro) {
            return actual;  // Libro encontrado
        }
        actual = actual->siguiente;
    }
    return nullptr;  // Libro no encontrado
}
