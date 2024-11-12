#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <filesystem>
#include <ctime> /*Para registrar la fecha */
using namespace std;

// Declaraciones previas
void insertarFinalListaLibro(ListaLibros *lista, Libro *libro);
void guardar_CSV_Libros(ListaLibros *lista, string nombreArchivo);
void adicionarCampo();
void modificarLibro();
void insertarLibro(ListaLibros &lista, Libro nuevoLibro);
ListaLibros leerLibrosCSV(string nombreArchivo);
bool mostrarLibroXid(ListaLibros &Libros, int id);
void insertarArbolLibro(LibroNodoArbol *&raiz, Libro *libro);
Libro *buscarLibroArbol(LibroNodoArbol *raiz, string nombreLibroBuscar);
LibroNodoArbol *leerLibrosArbol(string nombreArchivo, bool userView);

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
                << libro.estado << "\n";

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
        dibujarTitulo(27, 0, 2, letras);
        estructura_menu2(16, 103, 10, 27);
        Libro *libro = new Libro();
        libro->estado = "Disponible";
        gotoxy(52, 12);
        color(2);
        cout << "Registro de libros";
        color(0);
        gotoxy(36, 14);
        color(2);
        cout << "Nombre del libro: ";
        color(0);
        getline(cin, libro->nombre_Libro);
        gotoxy(36, 15);
        color(2);
        cout << "Nombre del autor: ";
        color(0);
        getline(cin, libro->Autor);
        gotoxy(36, 16);
        color(2);
        cout << "Año de publicacion: ";
        color(0);
        cin >> libro->Ano;
        cin.ignore();
        gotoxy(36, 17);
        color(2);
        cout << "Genero: ";
        color(0);
        getline(cin, libro->Genero);
        gotoxy(36, 18);
        color(2);
        cout << "Stock ingresado: ";
        color(0);
        cin >> libro->stock;
        gotoxy(36, 19);
        color(2);
        cout << "Precio (S/): ";
        color(0);
        cin >> libro->precio;
        cin.ignore();

        for (int i = 0; i < libro->stock; i++)
        {
            libro->id = contarFilasCSV("output/libros.csv") + contador;
            insertarFinalListaLibro(listaLibros, libro);
            contador++;
        }

        dibujarTextoPuntos(36, 21, "Registrando libro(s)");
        gotoxy(36, 21);
        cout << "Libro(s) registrado con exito!";

        gotoxy(36, 24);
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
    dibujarTitulo(27, 0, 2, letras);
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
            dibujarTitulo(27, 0, 2, letras);
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
                        cout << "Antiguo género: ";
                        color(0);
                        cout << actual->libro.Genero;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo género: ";
                        color(0);
                        fflush(stdin);
                        getline(cin, datoString);
                        actual->libro.Genero = datoString;
                        break;
                    case 4:
                        // Modificar año
                        gotoxy(36, 16);
                        color(2);
                        cout << "Antiguo año: ";
                        color(0);
                        cout << actual->libro.Ano;
                        gotoxy(36, 17);
                        color(2);
                        cout << "Nuevo año: ";
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
                        cout << "Opción no válida." << endl;
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
            cout << "Modifiación cancelada";
            system("pause>0");
        }
    }
    dibujarTextoPuntos(36, 22, "Modificando libro");
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

            // Suponiendo que el CSV tiene los campos en el siguiente orden (para mostrar catálogo):
            // Nombre, Autor, Año, Género, Stock, precio, estado
            getline(ss, dato, ',');
            libro.id = stoi(dato); // Convertir a entero
            getline(ss, libro.nombre_Libro, ',');
            getline(ss, libro.Autor, ',');
            getline(ss, dato, ',');
            libro.Ano = stoi(dato);
            getline(ss, libro.Genero, ',');
            getline(ss, dato, ',');
            libro.precio = stoi(dato);
            libro.stock = contarTituloLibro("output/libros.csv", libro.nombre_Libro);
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
            // Nombre, Autor, Año, Género, Stock, precio, estado
            getline(ss, dato, ',');
            libro.id = stoi(dato); // Convertir a entero
            getline(ss, libro.nombre_Libro, ',');
            if (userView)
            {
                if (tituloGuardado("output/libros.csv", libro.id, libro.nombre_Libro))
                {
                    continue;
                }
            }
            getline(ss, libro.Autor, ',');
            getline(ss, dato, ',');
            libro.Ano = stoi(dato);
            getline(ss, libro.Genero, ',');
            getline(ss, dato, ',');
            if (userView)
            {
                libro.stock = contarTituloLibro("output/libros.csv", libro.nombre_Libro);
            }
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
void mostrarLibros(ListaDobleLibros &lista, bool userView)
{
    // Verificamos si la lista está vacía
    if (lista.cabeza == nullptr)
    {
        cout << "La lista de libros está vacía." << endl;
        return;
    }

    // Creamos un nodo de los libros para tener referencia de la posición en la lista (como puntero)
    nodoDobleLibros *actual = lista.cabeza;
    int opcion = -1; // Variable para las opciones del menú (Salir, página anterior, página siguiente)

    int resta = 0;

    if (userView)
    {
        resta = 5;
    }
    else
    {
        resta = 0;
    }

    while (opcion != 0) // 0 significa salir
    {
        limpiarPantalla();
        setConsoleBackground(White);
        dibujarTitulo(27, 0, 2, letras);
        estructura_menu2(8, 111, 10, 27);

        int contador = 0; // Contador para mostrar los libros de 10 en 10

        gotoxy(50, 11);
        color(2);
        cout << "Catálogo de libros";
        if (!userView)
        {
            gotoxy(13, 13);
            cout << "ID";
        }

        gotoxy(18 - resta, 13);
        cout << "Nombre";
        gotoxy(47, 13);
        cout << "Autor";
        gotoxy(71, 13);
        cout << "Género";
        if (userView)
        {
            gotoxy(93, 13);
            cout << "Año";
            gotoxy(102, 13);
            cout << "Stock";
        }
        else
        {
            gotoxy(93, 13);
            cout << "Estado";
        }

        color(0);

        // Mostrar los libros a partir de la posición actual
        nodoDobleLibros *temporal = actual; // Se usa un puntero temporal para mostrar los libros
        while (temporal != nullptr && contador < 10)
        {
            if (!userView)
            {
                gotoxy(13, 15 + contador);
                cout << temporal->libro.id;
            }

            gotoxy(18 - resta, 15 + contador);
            if (temporal->libro.nombre_Libro.length() > 25)
            {
                cout << temporal->libro.nombre_Libro.substr(0, 22) + "...";
            }
            else
            {
                cout << temporal->libro.nombre_Libro;
            }

            gotoxy(47, 15 + contador);
            if (temporal->libro.Autor.length() > 18)
            {
                cout << temporal->libro.Autor.substr(0, 15) + "...";
            }
            else
            {
                cout << temporal->libro.Autor;
            }

            gotoxy(71, 15 + contador);
            if (temporal->libro.Genero.length() > 17)
            {
                cout << temporal->libro.Genero.substr(0, 14) + "...";
            }
            else
            {
                cout << temporal->libro.Genero;
            }
            if (userView)
            {
                gotoxy(93, 15 + contador);
                cout << temporal->libro.Ano;
                gotoxy(102, 15 + contador);
                cout << temporal->libro.stock;
            }
            else
            {
                gotoxy(93, 15 + contador);
                cout << temporal->libro.estado;
            }

            temporal = temporal->siguiente;
            contador++;
        }

        // Mostrar el menú de navegación al final de la lista
        gotoxy(13, 26);
        color(2);
        if (userView)
        {
            cout << "Opciones: (0 = salir, 1 = anterior, 2 = siguiente, 3 = buscar por título): ";
        }
        else
        {
            cout << "Opciones: (0 = salir, 1 = anterior, 2 = siguiente): ";
        }

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
            
            LibroNodoArbol *arbol = leerLibrosArbol("output/libros.csv", true);
            string titulo;
            gotoxy(13, 27);
            color(2);
            cout << "Título del libro: ";
            color(0);
            getline(cin, titulo);
            Libro *libroEncontrado = buscarLibroArbol(arbol, titulo);

            limpiarPantalla();
            setConsoleBackground(White);
            dibujarTitulo(27, 0, 2, letras);
            estructura_menu2(8, 111, 10, 27);

            int contador = 0; // Contador para mostrar los libros de 10 en 10

            gotoxy(50, 11);
            color(2);
            cout << "Catálogo de libros";

            gotoxy(13, 13);
            color(2);
            cout << "Resultados para: ";
            color(0);
            cout << titulo;

            color(2);
            gotoxy(18 - resta, 15);
            cout << "Nombre";
            gotoxy(47, 15);
            cout << "Autor";
            gotoxy(71, 15);
            cout << "Género";
            gotoxy(93, 15);
            cout << "Año";
            gotoxy(102, 15);
            cout << "Stock";
            color(0);

            gotoxy(18 - resta, 17);
            if (libroEncontrado->nombre_Libro.length() > 25)
            {
                cout << libroEncontrado->nombre_Libro.substr(0, 22) + "...";
            }
            else
            {
                cout << libroEncontrado->nombre_Libro;
            }

            gotoxy(47, 17);
            if (libroEncontrado->Autor.length() > 18)
            {
                cout << libroEncontrado->Autor.substr(0, 15) + "...";
            }
            else
            {
                cout << libroEncontrado->Autor;
            }

            gotoxy(71, 17);
            if (libroEncontrado->Genero.length() > 17)
            {
                cout << libroEncontrado->Genero.substr(0, 14) + "...";
            }
            else
            {
                cout << libroEncontrado->Genero;
            }
            if (userView)
            {
                gotoxy(93, 17);
                cout << libroEncontrado->Ano;
                gotoxy(102, 17);
                cout << libroEncontrado->stock;
            }

            pausa();
        }
        else if (opcion != 0)
        {
            cout << "Opción no válida. Inténtelo de nuevo." << endl;
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

// Buscar libro por título
nodoLibros *buscarLibroPorTitulo(ListaLibros &listaLibros, string tituloLibro)
{
    nodoLibros *actual = listaLibros.cabeza;
    while (actual != nullptr)
    {
        int distancia = distanciaLevenshtein(actual->libro.nombre_Libro, tituloLibro);
        if (distancia < 4 && actual->libro.estado == "Disponible")
        {
            return actual; // Libro encontrado
        }
        actual = actual->siguiente;
    }
    return nullptr; // Libro no encontrado
}

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
                << libro.estado << "\n";

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

// Función para buscar un libro en el arbol
Libro *buscarLibroArbol(LibroNodoArbol *raiz, string nombreLibroBuscar)
{
    if (raiz == nullptr)
    {
        return nullptr;
    }

    // Buscar si el título ingresado es una subcadena del título del nodo
    if (raiz->libro.nombre_Libro.find(nombreLibroBuscar) != string::npos || raiz->libro.nombre_Libro == nombreLibroBuscar)
    {
        return &raiz->libro;
    }

    // Buscar en el subárbol izquierdo
    if (raiz->libro.nombre_Libro > nombreLibroBuscar)
    {
        return buscarLibroArbol(raiz->izquierda, nombreLibroBuscar);
    }
    else
    { // Buscar en el subárbol derecho
        return buscarLibroArbol(raiz->derecha, nombreLibroBuscar);
    }
}

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
        // Nombre, Autor, Año, Género, Stock, precio, estado
        try
        {
            getline(ss, dato, ',');
            libro.id = stoi(dato); // Convertir a entero

            getline(ss, libro.nombre_Libro, ',');
            if (userView && tituloGuardado("output/libros.csv", libro.id, libro.nombre_Libro))
            {
                continue;
            }

            getline(ss, libro.Autor, ',');

            getline(ss, dato, ',');
            libro.Ano = stoi(dato);

            getline(ss, libro.Genero, ',');

            getline(ss, dato, ',');
            if (userView)
            {
                libro.stock = contarTituloLibro("output/libros.csv", libro.nombre_Libro);
            }

            libro.precio = stoi(dato);
            getline(ss, libro.estado, ',');

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
