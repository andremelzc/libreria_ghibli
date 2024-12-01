#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <locale>
#include <string>
#include <ctime>
#include <filesystem>
#include "..\menu\gotoxy.h"

using namespace std;

// Declaraciones de funciones
bool verificarMaxLibros(string membresia, int librosPrestados, int &maxLibros);
bool verificarMembresia(Lista &Usuarios, int idUsuario);
bool mostrarLibroXTitulo(ListaLibros &Libros, string tituloPedido, int &id);
void modificarCantPrestada(int idUsuario);
bool mostrarLibroXidCopy(ListaLibros &Libros, int id);
// void encolarPrestamoPorPrioridad(ColaPedidos &colaPedidos, Pedidos pedido);

// -- FUNCIONES PARA LISTA ENLAZADA DE PEDIDOS --
// Insertar al final para crear la lista enlazada
void insertarFinalListaPedido(ListaPedidos *lista, Pedidos *pedido)
{
    NodoPedidos *NodoPedido = new NodoPedidos(*pedido);

    if (lista->head == nullptr)
    {
        lista->head = NodoPedido;
    }
    else
    {
        NodoPedidos *iterador = lista->head;
        while (iterador->sgte)
        {
            iterador = iterador->sgte;
        }
        iterador->sgte = NodoPedido;
    }
    lista->longitud++;
}
// Insertar para crear la lista enlazada
void insertarListaPedidos(ListaPedidos &lista, Pedidos nuevoPedido)
{
    // Crear un nuevo nodo con el pedido
    NodoPedidos *nuevoNodo = new NodoPedidos(nuevoPedido);
    nuevoNodo->sgte = nullptr;

    // Si la lista está vacía, el nuevo nodo es el primero
    if (lista.head == nullptr)
    {
        lista.head = nuevoNodo;
    }
    else
    {
        // Encontrar el último nodo de la lista
        NodoPedidos *actual = lista.head;
        while (actual->sgte != nullptr)
        {
            actual = actual->sgte;
        }
        // Insertar el nuevo nodo al final de la lista
        actual->sgte = nuevoNodo;
    }

    // Incrementar la longitud de la lista
    lista.longitud++;
}

// -- FUNCIONES PARA LEER Y ESCRIBIR PEDIDOS DESDE UN ARCHIVO CSV --
void guardar_CSV_Pedido(ListaPedidos *Lista, string nombreArchivo)
{
    fstream archivo(nombreArchivo, fstream::out | fstream ::app);

    if (!filesystem::exists(nombreArchivo))
    {
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

    while (nodo != nullptr)
    {
        Pedidos pedido = nodo->pedido;
        archivo << pedido.ID_pedido << ","
                << pedido.ID_usuario << ","
                << pedido.ID_libro << ","
                << pedido.estadoPedido << ","
                << pedido.fechaPedido.dia << "/" << pedido.fechaPedido.mes << "/" << pedido.fechaPedido.año << ","
                << pedido.fechaAdquisicion.dia << "/" << pedido.fechaAdquisicion.mes << "/" << pedido.fechaAdquisicion.año << ","
                << pedido.devolucion.dia << "/" << pedido.devolucion.mes << "/" << pedido.devolucion.año << ","
                << pedido.entregado.dia << "/" << pedido.entregado.mes << "/" << pedido.entregado.año << ","
                << pedido.evaluacion << "," << pedido.ID_recepcionistaEntrega << "," << pedido.ID_recepcionistaRecibe << "\n";

        nodo = nodo->sgte;
    }

    if (archivo.fail())
    {
        std::cerr << "Error: Fallo al escribir en el archivo." << std::endl;
        system("PAUSE");
        return; // Salir con error
    }

    archivo.close();
    cout << "Datos guardados en " << nombreArchivo << endl;
}

void guardar_CSV_PedidoReferencia(ListaPedidos &Lista, const string &nombreArchivo)
{
    fstream archivo(nombreArchivo, fstream::out); // Abrir en modo de escritura (sobrescribirá si el archivo existe)

    // Verificar si se pudo abrir el archivo
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        system("PAUSE");
        return;
    }

    NodoPedidos *nodo = Lista.head; // Obtener el primer nodo de la lista

    // Recorrer la lista de pedidos y escribir en el archivo
    while (nodo != nullptr)
    {
        Pedidos pedido = nodo->pedido;
        archivo << pedido.ID_pedido << ","
                << pedido.ID_usuario << ","
                << pedido.ID_libro << ","
                << pedido.estadoPedido << ","
                << pedido.fechaPedido.dia << "/" << pedido.fechaPedido.mes << "/" << pedido.fechaPedido.año << ","
                << pedido.fechaAdquisicion.dia << "/" << pedido.fechaAdquisicion.mes << "/" << pedido.fechaAdquisicion.año << ","
                << pedido.devolucion.dia << "/" << pedido.devolucion.mes << "/" << pedido.devolucion.año << ","
                << pedido.entregado.dia << "/" << pedido.entregado.mes << "/" << pedido.entregado.año << ","
                << pedido.evaluacion << "," << pedido.ID_recepcionistaEntrega << "," << pedido.ID_recepcionistaRecibe << "\n";

        nodo = nodo->sgte; // Mover al siguiente nodo
    }

    // Verificar si hubo un error al escribir en el archivo
    if (archivo.fail())
    {
        cerr << "Error: Fallo al escribir en el archivo." << endl;
        system("PAUSE");
        return; // Salir con error
    }

    archivo.close(); // Cerrar el archivo
    // cout << "Datos guardados en " << nombreArchivo << endl;
}

// Leer los pedidos desde un archivo CSV
ListaPedidos leerPedidosDesdeCSV(string nombreArchivo)
{
    ListaPedidos lista;              // Crear una lista vacía
    ifstream archivo(nombreArchivo); // Abrir el archivo CSV

    if (!archivo.is_open())
    { // Verificar si el archivo se abrió correctamente
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        system("PAUSE");

        return lista; // Regresar la lista vacía si el archivo no se pudo abrir
    }

    string linea;
    while (getline(archivo, linea))
    { // Leer línea por línea del archivo CSV
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

        // Leer la evaluación
        getline(ss, campo, ',');
        pedido.evaluacion = stoi(campo);

        // Leer el ID del recepcionista que entrega y que recibe
        getline(ss, campo, ',');
        pedido.ID_recepcionistaEntrega = stoi(campo);
        getline(ss, campo, ',');
        pedido.ID_recepcionistaRecibe = stoi(campo);

        insertarListaPedidos(lista, pedido);
    }

    archivo.close(); // Cerrar el archivo CSV
    return lista;    // Regresar la lista de pedidos
}

// -- FUNCIONES PARA REGISTRAR PEDIDOS DE LIBROS --
void adicionarCampoPedido(int id_usuariologeado)
{

    ListaPedidos *listaPedido = new ListaPedidos();

    char respuesta[10];
    int i = 1;
    time_t now = time(0);
    tm *localTime = localtime(&now);
    int maxLibros = 0;

    do
    {
        limpiarPantalla();
        setConsoleBackground(White);
        dibujarTitulo(27, 0, 2, letras);
        estructura_menu2(16, 103, 10, 27);
        Pedidos *pedido = new Pedidos();
        pedido->ID_pedido = contarFilasCSV("output/pedidos.csv") + i;

        gotoxy(52, 11);
        cout << "Préstamo de libro";

        pedido->ID_usuario = id_usuariologeado;

        Lista listaUsuarios = leerUsuariosCSV("output/usuarios.csv"); // cargando lista de usuarios

        // Verificar si el usuario tiene una membresia activa
        if (!(verificarMembresia(listaUsuarios, id_usuariologeado)))
        {
            gotoxy(27, 13);
            color(4);
            cout << "Usuario no habilitado para solicitar préstamo";
            color(0);
            gotoxy(27, 14);
            cout << "Causa: Membresia inactiva";
            pausa();
            break;
        }

        // Verificar si el usuario ha alcanzado el máximo de libros prestados, y si no, asiganamos el  máximo
        std::string id_usuario_str = std::to_string(id_usuariologeado);
        Nodo *usuario = buscarUsuarioPorDNI(listaUsuarios, id_usuario_str);

        if (verificarMaxLibros(usuario->usuario.membresia, usuario->usuario.librosPrestados, maxLibros))
        {
            gotoxy(27, 13);
            color(4);
            cout << "Usuario no habilitado para solicitar préstamo";
            color(0);
            gotoxy(27, 14);
            cout << "Causa: Máximo de libros prestados alcanzado";
            pausa();
            break;
        }

        maxLibros = maxLibros - usuario->usuario.librosPrestados;

        // Búsqueda del libro por id
        gotoxy(27, 13);
        color(2);
        cout << "ID del libro a solicitar préstamo: ";
        color(0);
        cin >> pedido->ID_libro;
        cin.ignore();

        // Verificar si el libro ya fue prestado por el usuario
        ListaPedidos pedidos = leerPedidosDesdeCSV("output/pedidos.csv");
        NodoPedidos *actual = pedidos.head;
        bool prestado = false;
        while (actual != nullptr)
        {
            if (actual->pedido.ID_usuario == id_usuariologeado && actual->pedido.ID_libro == pedido->ID_libro)
            {
                prestado = true;
                break;
            }
            actual = actual->sgte;
        }

        if (prestado)
        {
            gotoxy(27, 14);
            color(4);
            cout << "Usuario no habilitado para solicitar este libro";
            color(0);
            gotoxy(27, 15);
            cout << "Causa: El libro ya ha sido prestado o solicitado anteriormente";
            gotoxy(27, 16);
            cout << "y todavía no ha sido devuelto";
            pausa();
            continue;
        }

        ListaLibros libros = leerLibrosCSV("output/libros.csv");
        bool find = mostrarLibroXidCopy(libros, pedido->ID_libro);

        // Si es que el libro ingresado existe
        if (find)
        {
            char check;
            i++;
            gotoxy(27, 21);
            color(2);
            cout << "Este es el libro que deseas solicitar?(s/n): ";
            color(0);
            cin >> check;
            cin.ignore();
            color(2);
            dibujarTextoPuntos(27, 22, "Solicitando prestamo");
            gotoxy(27, 22);
            cout << "Préstamo solicitado con éxito!";

            // Reducimos el stock del libro
            nodoLibros *actual = libros.cabeza;
            while (actual != nullptr)
            {
                if (actual->libro.id == pedido->ID_libro)
                {
                    actual->libro.StockActual--;
                    break;
                }
                actual = actual->siguiente;
            }
            limpiarCSV("output/libros.csv");
            guardar_CSV_Libros(&libros, "output/libros.csv");

            if (!(check == 's' or check == 'S'))
            {
                respuesta[0] = 's';
                continue;
            }
        }
        // Si el libro no existe
        else
        {
            gotoxy(27, 18);
            color(4);
            cout << "Libro no existente o no disponible, revise en el catálogo";
            pausa();
            continue;
        }

        // Estableciendo estadoPedido
        pedido->estadoPedido = "SOLICITADO";

        // agregando la fecha del día que se realizo el pedido
        pedido->fechaPedido.dia = localTime->tm_mday;
        pedido->fechaPedido.mes = localTime->tm_mon + 1;     // mas 1 pq los meses empiezan en 0
        pedido->fechaPedido.año = localTime->tm_year + 1900; // tm year solo cuenta los años desde 1900

        // setting las fechas que no pueden puede ser establecidas en la creacion del pedido
        pedido->fechaAdquisicion.dia = 00;
        pedido->fechaAdquisicion.mes = 00;
        pedido->fechaAdquisicion.año = 00;
        pedido->entregado.dia = 00;
        pedido->entregado.mes = 00;
        pedido->entregado.año = 00;
        pedido->devolucion.dia = 00;
        pedido->devolucion.mes = 00;
        pedido->devolucion.año = 00;
        pedido->evaluacion = -1;
        pedido->ID_recepcionistaEntrega = -1;
        pedido->ID_recepcionistaRecibe = -1;

        // Modificar la cantidad de libros prestados al usuario
        modificarCantPrestada(pedido->ID_usuario);

        insertarFinalListaPedido(listaPedido, pedido);

        if (maxLibros == 0)
        {
            break;
        }

        gotoxy(27, 24);
        color(2);
        cout << "Desea solicitar otro prestamo? (s/n): ";
        color(0);
        cin >> respuesta;
        cin.ignore();

    } while (respuesta[0] == 's' || respuesta[0] == 'S');

    guardar_CSV_Pedido(listaPedido, "output/pedidos.csv");
}

// -- FUNCIONES PARA MOSTRAR PEDIDOS --
bool mostrarLibroXidCopy(ListaLibros &Libros, int id)
{
    nodoLibros *actual = Libros.cabeza; // Apuntar al primer nodo de la lista

    // Recorrer la lista buscando el libro con el ID indicado
    while (actual != nullptr)
    {
        if (actual->libro.id == id) // Si el ID del libro coincide
        {
            // Mostrar los datos del libros
            gotoxy(27, 14);
            color(2);
            cout << "1. Nombre del Libro: ";
            color(0);
            cout << actual->libro.nombre_Libro;
            gotoxy(27, 15);
            color(2);
            cout << "2. Autor: ";
            color(0);
            cout << actual->libro.Autor;
            gotoxy(27, 16);
            color(2);
            cout << "3. Genero: ";
            color(0);
            cout << actual->libro.Genero;
            gotoxy(27, 17);
            color(2);
            cout << "4. Ano: ";
            color(0);
            cout << actual->libro.Ano;
            gotoxy(27, 18);
            color(2);
            cout << "5. Stock: ";
            color(0);
            cout << actual->libro.StockActual;
            gotoxy(27, 19);
            color(2);
            cout << "6. Precio: ";
            color(0);
            cout << actual->libro.precio;

            return true; // Retorna true si el libro fue encontrado
            break;
        }
        actual = actual->siguiente; // Mover al siguiente nodo
    }

    // Si el libro no fue encontrado
    // cout << "No se encontro ningun libro con el ID: " << id << endl;
    return false; // Retorna false si no encontró el libro
}

bool mostrarLibroXTitulo(ListaLibros &Libros, string tituloPedido, int &id)
{
    nodoLibros *actual = Libros.cabeza; // Apuntar al primer nodo de la lista

    // Recorrer la lista buscando el libro con el ID indicado
    while (actual != nullptr)
    {
        int distancia = distanciaLevenshtein(actual->libro.nombre_Libro, tituloPedido);
        if (distancia < 4 && actual->libro.estado == "Disponible") // Si el titulo del libro coincide y si hay alguno disponible
        {
            // Mostrar los datos del libros
            id = actual->libro.id;
            gotoxy(27, 14);
            color(2);
            cout << "1. Nombre del Libro: ";
            color(0);
            cout << actual->libro.nombre_Libro;
            gotoxy(27, 15);
            color(2);
            cout << "2. Autor: ";
            color(0);
            cout << actual->libro.Autor;
            gotoxy(27, 16);
            color(2);
            cout << "3. Genero: ";
            color(0);
            cout << actual->libro.Genero;
            gotoxy(27, 17);
            color(2);
            cout << "4. Ano: ";
            color(0);
            cout << actual->libro.Ano;
            gotoxy(27, 18);
            color(2);
            cout << "5. Stock: ";
            color(0);
            actual->libro.stock = contarTituloLibro("output/libros.csv", actual->libro.nombre_Libro);
            cout << actual->libro.stock;
            gotoxy(27, 19);
            color(2);
            cout << "6. Precio: ";
            color(0);
            cout << "S/ " << actual->libro.precio;

            return true; // Retorna true si el libro fue encontrado
            break;
        }
        actual = actual->siguiente; // Mover al siguiente nodo
    }

    // Si el libro no fue encontrado
    // cout << "No se encontro ningun libro con el ID: " << id << endl;
    return false; // Retorna false si no encontró el libro
}

bool verificarMaxLibros(string membresia, int librosPrestados, int &maxLibros)
{
    if (membresia == "ESTANDAR")
    {
        maxLibros = 1;
        if (librosPrestados == 1)
        {
            return true;
        }
    }
    else if (membresia == "PREMIUM")
    {
        maxLibros = 3;
        if (librosPrestados == 3)
        {
            return true;
        }
    }
    else if (membresia == "VIP")
    {
        maxLibros = 5;
        if (librosPrestados == 5)
        {
            return true;
        }
    }
    return false;
}

bool verificarMembresia(Lista &Usuarios, int id)
{ // verifica que tengas membresia activa
    bool find = false;
    Nodo *actual = Usuarios.cabeza;

    cout << endl;
    while (actual != nullptr)
    {
        int id_lista_usuario = stoi(actual->usuario.ID_Usuario);
        if (id_lista_usuario == id)
        {
            if (actual->usuario.membresia != "INACTIVA")
            {
                find = true;
                return true;
            }
        }
        actual = actual->siguiente;
    }

    return false;
}

void modificarCantPrestada(int idUsuario)
{
    Lista listaUsuarios;
    listaUsuarios = leerUsuariosCSV("output/usuarios.csv");

    Nodo *actual = listaUsuarios.cabeza;

    while (actual != nullptr)
    {
        if (stoi(actual->usuario.ID_Usuario) == idUsuario)
        {
            actual->usuario.librosPrestados++;
        }
        actual = actual->siguiente;
    }
    limpiarCSV("output/usuarios.csv");
    guardar_CSV(&listaUsuarios, "output/usuarios.csv");
}

void mostrarPedidos(ListaPedidos &listaPedidos)
{
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
    color(0);
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

bool mostrarPedidosxdni(ListaPedidos &listaPedidos, string dni)
{
    // Verificar si el DNI es válido (solo números y no vacío)
    if (dni.empty() || !all_of(dni.begin(), dni.end(), ::isdigit))
    {
        gotoxy(40, 21);
        color(4);
        cout << "DNI inválido. Asegúrese de ingresar solo números.";
        color(0);
        return false;
    }

    NodoPedidos *actual = listaPedidos.head;
    ListaLibros listaLibros = leerLibrosCSV("output/libros.csv");

    int contador = 1;
    bool usuarioEncontrado = false;

    Lista listaUsuarios = leerUsuariosCSV("output/usuarios.csv");
    Nodo *actualUsuario = buscarUsuarioPorDNI(listaUsuarios, dni);

    gotoxy(27, 19);
    cout << "ID";
    gotoxy(33, 19);
    cout << "Libro";
    gotoxy(67, 19);
    cout << "Estado ";
    gotoxy(83, 19);
    cout << "F. Pedido ";

    color(0);
    while (actual != nullptr)
    {
        // Convertir DNI a entero para comparación
        if (actual->pedido.ID_usuario == stoi(dni) &&
            (actual->pedido.estadoPedido == "PRESTADO" || actual->pedido.estadoPedido == "NO_DEVUELTO"))
        {
            gotoxy(27, 19 + contador);
            cout << actual->pedido.ID_pedido;
            gotoxy(33, 19 + contador);
            cout << actual->pedido.ID_libro << ") ";
            nodoLibros *actualLibro = listaLibros.cabeza;
            while (actualLibro != nullptr)
            {
                if (actualLibro->libro.id == actual->pedido.ID_libro)
                {
                    if (actualLibro->libro.nombre_Libro.length() > 24)
                    {
                        cout << actualLibro->libro.nombre_Libro.substr(0, 24) << "...";
                    }
                    else
                    {
                        cout << actualLibro->libro.nombre_Libro;
                    }
                    break;
                }
                actualLibro = actualLibro->siguiente;
            }
            gotoxy(83, 19 + contador);
            cout << actual->pedido.fechaPedido.dia << "/" << actual->pedido.fechaPedido.mes << "/" << actual->pedido.fechaPedido.año;
            gotoxy(67, 19 + contador);
            cout << actual->pedido.estadoPedido;
            usuarioEncontrado = true;
            contador++;
        }
        actual = actual->sgte;
    }

    if (!usuarioEncontrado)
    {
        gotoxy(40, 21);
        color(4);
        cout << "Usuario no tiene libros prestados.";
        color(0);
    }
    else if (actualUsuario)
    {
        gotoxy(27, 17);
        color(2);
        cout << "Usuario encontrado: " << actualUsuario->usuario.nombre << " " << actualUsuario->usuario.apellidos;
    }
    else
    {
        gotoxy(27, 17);
        color(4);
        cout << "No se pudo encontrar el usuario en la base de datos.";
        color(0);
    }

    return usuarioEncontrado;
}


// -- FUNCIONES PARA DEVOLVER LIBROS --
void registrarDevolucionLibro(int &mora, int idRecepcionista)

{
    string dni;
    string id_libro;
    ListaPedidos listaPedidos = leerPedidosDesdeCSV("output/pedidos.csv");
    int dias;
    bool usuarioEncontrado = false;
    mora = 0;
    bool idLibroEncontrado = false;
    do
    {
        limpiarPantalla();
        setConsoleBackground(White);
        ejecutarGradienteDoble(150);
        estructura_menu2(16, 103, 11, 26);
        dibujarTitulo(27, 0, 2, letras);
        gotoxy(46, 12);
        color(2);
        cout << "Registrar devolucion de libro";
        gotoxy(27, 14);
        color(0);
        cout << "Para registrar la devolución de un libro, por favor ingrese el";
        gotoxy(27, 15);
        cout << "DNI del usuario que desea devolver el libro.";
        gotoxy(27, 16);
        color(2);
        cout << "DNI del usuario: ";
        color(0);
        
        // Leer el DNI del usuario por si ingresó un escape
        getline(cin, dni);
        cout<<"             "<<dni;


        color(2);
        dibujarTextoPuntos(27, 17, "Buscando usuario");

        usuarioEncontrado = mostrarPedidosxdni(listaPedidos, dni);

        if (!usuarioEncontrado)
        {
            gotoxy(27, 17);
            color(4);
            cout << "Usuario no encontrado";
            gotoxy(40, 18);
            cout << "Desea buscar otro usuario (s/n): ";
            string respuesta;
            color(0);
            getline(cin, respuesta);
            if (respuesta[0] == 'n' || respuesta[0] == 'N')
            {
                break;
            }
        }
    } while (!usuarioEncontrado);

    if (usuarioEncontrado)
    {
        gotoxy(27, 25);
        color(2);
        cout << "ID del libro a devolver: ";
        color(0);
        // Leer el ID del libro por si ingresó un escape
        getline(cin, id_libro);

        NodoPedidos *actual = listaPedidos.head;
        string nombreLibroDevuelto;
        while (actual != nullptr)
        {
            if (actual->pedido.ID_usuario == stoi(dni) && actual->pedido.ID_libro == stoi(id_libro) && (actual->pedido.estadoPedido == "PRESTADO" || actual->pedido.estadoPedido == "NO_DEVUELTO"))
            {
                // Modificamos datos del libros.csv
                idLibroEncontrado = true;
                ListaLibros listaLibros = leerLibrosCSV("output/libros.csv");
                nodoLibros *actualLibro = listaLibros.cabeza;
                while (actualLibro != nullptr)
                {
                    if (actualLibro->libro.id == stoi(id_libro))
                    {
                        actualLibro->libro.StockActual++;
                        nombreLibroDevuelto = actualLibro->libro.nombre_Libro;
                        break;
                    }
                    actualLibro = actualLibro->siguiente;
                }

                guardar_CSV_Libros_Sobreescribir(&listaLibros, "output/libros.csv");

                time_t tiempoActual = time(nullptr);

                // Convierte el tiempo a una estructura tm
                tm *tiempoLocal = localtime(&tiempoActual);

                actual->pedido.entregado.año = tiempoLocal->tm_year + 1900;
                actual->pedido.entregado.mes = tiempoLocal->tm_mon + 1;
                actual->pedido.entregado.dia = tiempoLocal->tm_mday;
                actual->pedido.ID_recepcionistaRecibe=idRecepcionista;

                dias = calcularDiasEntreFechas(actual->pedido.entregado.año, actual->pedido.entregado.mes, actual->pedido.entregado.dia, actual->pedido.devolucion.año, actual->pedido.devolucion.mes, actual->pedido.devolucion.dia);
                
                if (dias > 7)
                {
                    mora = 3 * (dias - 7);
                    actual->pedido.estadoPedido = "DEVUELTO_TARDE";

                    // Registramos la mora en ganancias
                    ListaGanancias listaGanancias;
                    Ganancia ganancia;
                    ganancia.id_usuario = stoi(dni);
                    ganancia.monto = mora;
                    ganancia.fecha = fechaAString(actual->pedido.entregado);
                    ganancia.origen = "MORA";
                    insertarFinalGanancias(&listaGanancias, &ganancia);
                    guardarGananciasCSV(&listaGanancias, "output/ganancias.csv");
                }
                else
                {
                    actual->pedido.estadoPedido = "DEVUELTO";
                }

                guardar_CSV_PedidoReferencia(listaPedidos, "output/pedidos.csv");

                Lista listaUsuarios = leerUsuariosCSV("output/usuarios.csv");
                Nodo *actualUsuario = listaUsuarios.cabeza;

                while (actualUsuario != nullptr)
                {
                    if (actualUsuario->usuario.ID_Usuario == dni)
                    {
                        actualUsuario->usuario.librosPrestados--;
                        break;
                    }
                    actualUsuario = actualUsuario->siguiente;
                }
                limpiarCSV("output/usuarios.csv");
                guardar_CSV(&listaUsuarios, "output/usuarios.csv");
            }

            actual = actual->sgte;
        }
        if (idLibroEncontrado)
        {
            limpiarPantalla();
            setConsoleBackground(White);
            ejecutarGradienteDoble(150);
            estructura_menu2(16, 103, 11, 26);
            dibujarTitulo(27, 0, 2, letras);
            gotoxy(44, 12);
            color(2);
            cout << "Registrar devolucion de libro";
            dibujarTextoPuntos(27, 14, "Devolviendo libro");
            gotoxy(27, 14);
            cout << "Libro '";
            color(0);
            cout << nombreLibroDevuelto;
            color(2);
            cout << "' ha sido devuelto con exito!";
            gotoxy(27, 16);
            cout << "Dias de prestamo: ";
            color(0);
            cout << dias << " días";
            gotoxy(27, 17);
            color(2);
            cout << "Dias de retraso: ";
            color(0);
            if (dias > 7)
            {
                cout << dias - 7 << " días";
            }
            else
            {
                cout << "0 días";
            }
            gotoxy(27, 18);
            color(2);
            cout << "Mora a pagar: S/ ";
            color(0);
            cout << mora;
        }
        else
        {
            gotoxy(40, 22);
            cout << "Libro no encontrado...";
        }
    }
}

// -- FUNCIONES PARA ATENDER PRÉSTAMO DE LIBROS  (USANDO COLAS) --
// Función que sirve para insertar un pedido en la cola de pedidos
void encolarPrestamoPorPersona(ColaPedidos &colaPedidos, Pedidos pedido)
{
    NodoPedidos *nuevoNodo = new NodoPedidos(pedido);
    if (colaPedidos.delante == nullptr)
    {
        colaPedidos.delante = nuevoNodo;
        colaPedidos.atras = nuevoNodo;
    }
    else
    {
        colaPedidos.atras->sgte = nuevoNodo;
        colaPedidos.atras = nuevoNodo;
    }
};

// Función que sirve para desencolar un pedido de la cola de pedidos
Pedidos desencolarPrestamo(ColaPedidos &colaPedidos)
{
    if (colaPedidos.delante == nullptr)
    {
        cout << "La cola de pedidos está vacía";
        return Pedidos{}; // Pedido vacio
    }

    // Nodo que se desencolará
    NodoPedidos *nodoDesencolado = colaPedidos.delante;
    // Pedido del nodo
    Pedidos pedidoDesencolado = nodoDesencolado->pedido;

    // Actualización de punteros
    colaPedidos.delante = nodoDesencolado->sgte;
    if (colaPedidos.delante == nullptr)
    {
        // Si la cosa se quedó vacía
        colaPedidos.atras = nullptr;
    }

    delete nodoDesencolado;
    return pedidoDesencolado;
}

// Hacer una cola por usuario
ColaPedidos cargarColaPedidosUsuario(int idUsuario)
{
    ColaPedidos colaPedidos;

    ifstream archivo("output/pedidos.csv");
    string linea;

    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo 'output/pedidos.csv'" << endl;
        return colaPedidos;
    }

    if (archivo.is_open())
    {
        // Leer el archivo línea por línea
        while (getline(archivo, linea))
        {
            stringstream ss(linea);
            string dato;

            Pedidos pedido;
            // El CSV tiene la siguiente estructura:
            // ID_pedido, ID_usuario, ID_libro, estadoPedido, fechaPedido, fechaAdquisicion, fechaDevolucion, fechaEntregado
            getline(ss, dato, ',');
            pedido.ID_pedido = stoi(dato);
            getline(ss, dato, ',');
            pedido.ID_usuario = stoi(dato);
            getline(ss, dato, ',');
            pedido.ID_libro = stoi(dato);
            getline(ss, pedido.estadoPedido, ',');
            getline(ss, dato, ',');
            pedido.fechaPedido = convertirFecha(dato);
            getline(ss, dato, ',');
            pedido.fechaAdquisicion = convertirFecha(dato);
            getline(ss, dato, ',');
            pedido.devolucion = convertirFecha(dato);
            getline(ss, dato, ',');
            pedido.entregado = convertirFecha(dato);

            if (pedido.ID_usuario == idUsuario && pedido.estadoPedido == "SOLICITADO")
            {
                encolarPrestamoPorPersona(colaPedidos, pedido);
            }
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo 'output/pedidos.csv'" << endl;
    }
    return colaPedidos;
}

// Función para marcar un pedido como entregado (tmb se actualiza en el csv)
void atenderPrestamo(ColaPedidos &colaPedidos, int idRecepcionista)
{
    if (colaPedidos.delante == nullptr)
    {
        cout << "No hay pedidos pendientes para este usuario" << endl;
        return;
    }

    ListaPedidos listaPedidos = leerPedidosDesdeCSV("output/pedidos.csv");

    // Desencolar y atender el primer pedido
    Pedidos pedido = desencolarPrestamo(colaPedidos);

    // Buscar el pedido en la lista de pedidos
    NodoPedidos *actual = listaPedidos.head;
    while (actual != nullptr)
    {
        if (actual->pedido.ID_pedido == pedido.ID_pedido)
        {
            // Actualizar el estado del pedido
            actual->pedido.estadoPedido = "PRESTADO";
            // Actualizar la fecha de adquisición
            actual->pedido.fechaAdquisicion = obtenerFechaActual();
            actual->pedido.devolucion = sumarDiasAFecha(obtenerFechaActual(), 7);
            actual->pedido.ID_recepcionistaEntrega = idRecepcionista;
            actual->pedido.evaluacion = -1;
            actual->pedido.ID_recepcionistaRecibe = -1;
            break;
        }
        actual = actual->sgte;
    }

    // Buscar el libro en la lista de libros
    ListaLibros listaLibros = leerLibrosCSV("output/libros.csv");
    nodoLibros *actualLibro = buscarLibroPorID(listaLibros, pedido.ID_libro);
    while (actualLibro != nullptr)
    {
        if (actualLibro->libro.id == pedido.ID_libro)
        {
            // Actualizar el estado del libro
            actualLibro->libro.StockActual--;
            break;
        }
        actualLibro = actualLibro->siguiente;
    }

    // Modificamos los csv
    limpiarCSV("output/pedidos.csv");
    guardar_CSV_PedidoReferencia(listaPedidos, "output/pedidos.csv");
}

// Función para mostrar la cola de pedidos de préstamo de un usuario
void muestraColaPedidosPrestamo(ColaPedidos &colaPedidos, int x, int y, bool &pedidosPendientes)
{
    NodoPedidos *actual = colaPedidos.delante;
    int contador = 2;
    gotoxy(x, y);
    cout << "ID";
    gotoxy(x + 6, y);
    cout << "Libro";
    gotoxy(x + 40, y);
    cout << "Estado";
    gotoxy(x + 55, y);
    cout << "Fecha Pedido";

    if (actual == nullptr)
    {
        pedidosPendientes = false;
        return;
    }

    while (actual != nullptr)
    {
        color(0);
        gotoxy(x, y + contador);
        cout << actual->pedido.ID_pedido;
        gotoxy(x + 6, y + contador);
        // Buscamos al libro
        ListaLibros listaLibros = leerLibrosCSV("output/libros.csv");
        nodoLibros *Libro = buscarLibroPorID(listaLibros, actual->pedido.ID_libro);
        cout << actual->pedido.ID_libro << ") ";
        if (Libro->libro.nombre_Libro.length() > 30)
        {
            cout << Libro->libro.nombre_Libro.substr(0, 30) << "...";
        }
        else
        {
            cout << Libro->libro.nombre_Libro;
        }
        gotoxy(x + 40, y + contador);
        cout << actual->pedido.estadoPedido;
        gotoxy(x + 55, y + contador);
        cout << actual->pedido.fechaPedido.dia << "/" << actual->pedido.fechaPedido.mes << "/" << actual->pedido.fechaPedido.año;
        actual = actual->sgte;
        contador++;
    }
}

// Función para atender los préstamos de un usuario
void atenderPrestamoMenu(int idRecepcionista)
{
    gotoxy(50, 11);
    color(2);
    cout << "Atendiendo Préstamos";
    color(0);
    gotoxy(27, 13);
    cout << "Para atender los préstamos, ingrese el DNI del usuario que";
    gotoxy(27, 14);
    cout << "desea atender.";
    gotoxy(27, 15);
    color(2);
    cout << "DNI del usuario: ";

    color(0);
    string idUsuarioIngresado;

    // Leeemos el DNI del usuario por si ingresa un ESCAPE
    if (!leerInputEscape(idUsuarioIngresado))
    {
        return;
    }
    cin.ignore();

    color(2);
    dibujarTextoPuntos(27, 17, "Cargando pedidos");
    gotoxy(27, 17);
    cout << "Pedidos cargados con éxito";
    ColaPedidos colaPedidos = cargarColaPedidosUsuario(stoi(idUsuarioIngresado));
    if (colaPedidos.delante == nullptr)
    {
        gotoxy(27, 18);
        color(4);
        cout << "No hay pedidos pendientes para este usuario";
        color(0);
        pausa();
    }
    else
    {
        string respuesta = "s";
        bool pedidosPendientes = true;
        do
        {
            limpiarPantalla();
            setConsoleBackground(White);
            ejecutarGradienteDoble(150);
            estructura_menu2(16, 103, 11, 26);
            dibujarTitulo(27, 0, 2, letras);
            gotoxy(50, 11);
            color(2);
            cout << "Atendiendo Préstamos";
            color(0);
            gotoxy(27, 13);
            cout << "Para atender los préstamos, ingrese el DNI del usuario que";
            gotoxy(27, 14);
            cout << "desea atender.";
            gotoxy(27, 15);
            color(2);
            cout << "DNI del usuario: " << idUsuarioIngresado;
            muestraColaPedidosPrestamo(colaPedidos, 27, 18, pedidosPendientes);
            if (!pedidosPendientes)
            {
                gotoxy(27, 24);
                color(4);
                cout << "No hay pedidos pendientes para este usuario";
                break;
            }
            gotoxy(27, 24);
            color(2);
            cout << "¿Desea atender prestamo? (s/n): ";
            color(0);

            // Leemos la respuesta por si ingresó un ESCAPE
            if (!leerInputEscape(respuesta))
            {
                return;
            }

            if (respuesta == "s" || respuesta == "S")
            {
                atenderPrestamo(colaPedidos, idRecepcionista);
            }
        } while (respuesta == "s" || respuesta == "S" || pedidosPendientes);
    }
}
