#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <locale>
#include <ctime>
#include <filesystem>
#include "..\menu\gotoxy.h"

using namespace std;

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
// Insertar para crear la listaenlazada
void insertarListaPedidos(ListaPedidos &lista, Pedidos nuevoPedido)
{
    // Crear un nuevo nodo con el pedido
    NodoPedidos *nuevoNodo = new NodoPedidos(nuevoPedido);

    // Insertar el nuevo nodo al principio de la lista
    nuevoNodo->sgte = lista.head;
    lista.head = nuevoNodo;

    // Incrementar la longitud de la lista
    lista.longitud++;
}

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
                << pedido.entregado.dia << "/" << pedido.entregado.mes << "/" << pedido.entregado.año << "\n";

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
                << pedido.entregado.dia << "/" << pedido.entregado.mes << "/" << pedido.entregado.año << "\n";

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
            actual->libro.stock = contarTituloLibro("output/Libros.csv", actual->libro.nombre_Libro);
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

bool verificarMembresiaYMax(Lista &Usuarios, int id)
{ // verifica que tengas membresia activa y menos de 4 libros sin devolver
    bool find = false;
    Nodo *actual = Usuarios.cabeza;

    cout << endl;
    while (actual != nullptr)
    {
        int id_lista_usuario = stoi(actual->usuario.ID_Usuario);
        if (id_lista_usuario == id)
        {
            if (actual->usuario.membresia == "ACTIVA" && actual->usuario.librosPrestados < 3)
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

void adicionarCampoPedido(int id_usuariologeado)
{

    ListaPedidos *listaPedido = new ListaPedidos();

    char respuesta[10];
    int i = 0;
    time_t now = time(0);
    tm *localTime = localtime(&now);
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

        verificarMembresiaYMax(listaUsuarios, id_usuariologeado);

        if (!(verificarMembresiaYMax(listaUsuarios, id_usuariologeado)))
        { // si es falso volvera a preguntar si deseas hacer una peticion
            // cout << endl<< "comprobando q todo esta bien 2";
            gotoxy(27, 13);
            color(4);
            cout << "Usuario no habilitado para solicitar préstamo";
            color(0);
            gotoxy(27, 14);
            cout << "Posibles causas:";
            gotoxy(27, 15);
            cout << "1. Membresia inactiva";
            gotoxy(27, 16);
            cout << "2. Ya tiene 3 libros prestados";
            pausa();
            break;
        }
        else
        {
        }

        string nombreLibro;
        gotoxy(27, 13);
        color(2);
        cout << "Nombre del libro a solicitar préstamo: ";
        color(0);
        getline(cin, nombreLibro);

        cin.ignore();

        ListaLibros libros = leerLibrosCSV("output/libros.csv");
        bool find = mostrarLibroXTitulo(libros, nombreLibro, pedido->ID_libro);
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
            if (!(check == 's' or check == 'S'))
            {
                respuesta[0] = 's';
                continue;
            }
        }
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
        pedido->fechaAdquisicion.dia = 0;
        pedido->fechaAdquisicion.mes = 0;
        pedido->fechaAdquisicion.año = 0;
        pedido->entregado.dia = 0;
        pedido->entregado.mes = 0;
        pedido->entregado.año = 0;
        pedido->devolucion.dia = 0;
        pedido->devolucion.mes = 0;
        pedido->devolucion.año = 0;

        insertarFinalListaPedido(listaPedido, pedido);

        // agregar aqui la actualizacion de la cantidad de libros prestado ojo me puedo guiar de la funcion actualizar membresia usuario que tiene un parecido
        // usamos esta funcion para aumentar en 1 la cantidad prestada
        modificarCantPrestada(pedido->ID_usuario); //------------- quitar de aqui y mandar a cuando se acepte el pedido

        gotoxy(27, 24);
        color(2);
        cout << "Desea solicitar otro prestamo? (s/n): ";
        color(0);
        cin >> respuesta;
        cin.ignore();

    } while (respuesta[0] == 's' || respuesta[0] == 'S');

    guardar_CSV_Pedido(listaPedido, "output/pedidos.csv");
}

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

        insertarListaPedidos(lista, pedido);
    }

    archivo.close(); // Cerrar el archivo CSV
    return lista;    // Regresar la lista de pedidos
}

fecha obtenerFechaActual()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Asignar la fecha actual al objeto fecha
    fecha fechaActual;
    fechaActual.dia = ltm->tm_mday;
    fechaActual.mes = 1 + ltm->tm_mon;     // Meses comienzan desde 0, por lo tanto se suma 1
    fechaActual.año = 1900 + ltm->tm_year; // Año empieza desde 1900, por lo tanto se suma 1900

    return fechaActual;
}

void gestionarpedido()
{

    Lista lista;
    lista = leerUsuariosCSV("output/usuarios.csv");
    ListaLibros listaLibros;
    listaLibros = leerLibrosCSV("output/libros.csv");
    ListaPedidos listaPedidos;
    listaPedidos = leerPedidosDesdeCSV("output/pedidos.csv");

    string dni;
    cout << "Ingrese el DNI del usuario: ";
    cin >> dni;

    // Buscar el usuario en la lista de usuarios
    Nodo *usuarioEncontrado = buscarUsuarioPorDNI(lista, dni);
    if (usuarioEncontrado == nullptr)
    {
        cout << "Usuario no encontrado." << endl;
        return;
    }

    cout << "Usuario encontrado: " << usuarioEncontrado->usuario.nombre << " " << usuarioEncontrado->usuario.apellidos << endl;

    // Buscar si el usuario tiene algún pedido con estado "SOLICITADO"
    NodoPedidos *actualPedido = listaPedidos.head;
    bool pedidoEncontrado = false;

    while (actualPedido != nullptr)
    {
        if (actualPedido->pedido.ID_usuario == stoi(dni) && actualPedido->pedido.estadoPedido == "SOLICITADO")
        {
            pedidoEncontrado = true;
            cout << "Pedido encontrado. ID del pedido: " << actualPedido->pedido.ID_pedido << endl;

            // Buscar el libro correspondiente
            nodoLibros *libroEncontrado = buscarLibroPorID(listaLibros, actualPedido->pedido.ID_libro);
            if (libroEncontrado != nullptr)
            {
                cout << "Libro encontrado: " << libroEncontrado->libro.nombre_Libro << endl;

                // Preguntar al usuario si desea prestar el libro
                char respuesta;
                cout << "¿Desea prestar este libro? (S/N): ";
                cin >> respuesta;

                if (respuesta == 'S' || respuesta == 's')
                {
                    cout << "Esta seguro de que quiere prestar el libro? (S/N): ";
                    cin >> respuesta;

                    if (respuesta == 'S' || respuesta == 's')
                    {
                        // Cambiar el estado a "PRESTADO"
                        actualPedido->pedido.estadoPedido = "PRESTADO";
                        cout << "El estado del pedido ha sido actualizado a PRESTADO." << endl;

                        // Obtener la fecha actual usando la función obtenerFechaActual
                        actualPedido->pedido.fechaAdquisicion = obtenerFechaActual();

                        cout << "Fecha de adquisicion: " << actualPedido->pedido.fechaAdquisicion.dia << "/"
                             << actualPedido->pedido.fechaAdquisicion.mes << "/"
                             << actualPedido->pedido.fechaAdquisicion.año << endl;
                    }
                    else
                    {
                        cout << "Operación cancelada." << endl;
                    }
                }
                else
                {
                    cout << "Operación cancelada." << endl;
                }
            }
            else
            {
                cout << "Libro no encontrado." << endl;
            }
        }
        actualPedido = actualPedido->sgte;
    }

    if (!pedidoEncontrado)
    {
        cout << "No hay pedidos solicitados para este usuario." << endl;
    }
    guardar_CSV_PedidoReferencia(listaPedidos, "output/pedidos.csv");
    system("PAUSE");
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
    NodoPedidos *actual = listaPedidos.head;
    ListaLibros listaLibros = leerLibrosCSV("output/libros.csv");

    int contador = 0;
    int id_libro;
    bool usuarioEncontrado = false;

    Lista listaUsuarios = leerUsuariosCSV("output/usuarios.csv");
    Nodo *actualUsuario = buscarUsuarioPorDNI(listaUsuarios, dni);

    gotoxy(47, 17);
    color(2);
    cout << "Pedidos de " << actualUsuario->usuario.nombre << " " << actualUsuario->usuario.apellidos;
    gotoxy(18, 19);
    cout << "ID";
    gotoxy(25, 19);
    cout << "Libro";
    gotoxy(66, 19);
    cout << "F. Pedido ";
    gotoxy(90, 19);
    cout << "Estado ";
    color(0);
    while (actual != nullptr)
    {
        if (actual->pedido.ID_usuario == stoi(dni) && actual->pedido.estadoPedido == "PRESTADO" || actual->pedido.estadoPedido == "NO_DEVUELTO")
        {
            gotoxy(18, 21 + contador);
            cout << actual->pedido.ID_pedido;
            gotoxy(25, 21 + contador);
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
            gotoxy(66, 21 + contador);
            cout << actual->pedido.fechaPedido.dia << "/" << actual->pedido.fechaPedido.mes << "/" << actual->pedido.fechaPedido.año;
            gotoxy(90, 21 + contador);
            cout << actual->pedido.estadoPedido;
            usuarioEncontrado = true;
            contador++;
        }
        actual = actual->sgte;
    }
    if (usuarioEncontrado == false)
    {
        gotoxy(40, 21);
        color(4);
        cout << "Usuario no tiene libros prestados.";
        color(0);
    }
    else
    {
        gotoxy(27, 15);
        color(2);
        cout << "Usuario encontrado!  ";
    }

    pausa();
    return usuarioEncontrado;
}

int calcularDiasEntreFechas(int anio1, int mes1, int dia1, int anio2, int mes2, int dia2)
{
    // Estructura tm para la primera fecha
    tm fecha1 = {};
    fecha1.tm_year = anio1 - 1900; // tm_year es años desde 1900
    fecha1.tm_mon = mes1 - 1;      // tm_mon es de 0 a 11
    fecha1.tm_mday = dia1;

    // Estructura tm para la segunda fecha
    tm fecha2 = {};
    fecha2.tm_year = anio2 - 1900;
    fecha2.tm_mon = mes2 - 1;
    fecha2.tm_mday = dia2;

    // Convertir las fechas a tiempo en segundos desde la época
    time_t tiempo1 = mktime(&fecha1);
    time_t tiempo2 = mktime(&fecha2);

    // Calcular la diferencia en segundos y convertirla a días
    double diferenciaSegundos = difftime(tiempo2, tiempo1);
    int diferenciaDias = diferenciaSegundos / (60 * 60 * 24); // Convierte de segundos a días

    return abs(diferenciaDias); // Valor absoluto de la diferencia en días
}

void registrarDevolucionLibro(int &mora)
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
        gotoxy(44, 12);
        color(2);
        cout << "Registrar devolucion de libro";
        gotoxy(27, 14);
        cout << "DNI del usuario: ";
        color(0);
        getline(cin, dni);
        color(2);
        dibujarTextoPuntos(27, 15, "Buscando usuario");

        usuarioEncontrado = mostrarPedidosxdni(listaPedidos, dni);

        if (!usuarioEncontrado)
        {
            gotoxy(27, 15);
            color(4);
            cout << "Usuario no encontrado";
            gotoxy(40, 16);
            cout << "Desea buscar otro usuario (s/n): ";
            string respuesta;
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
        getline(cin, id_libro);

        NodoPedidos *actual = listaPedidos.head;
        string nombreLibroDevuelto;
        while (actual != nullptr)
        {
            if (actual->pedido.ID_usuario == stoi(dni) && actual->pedido.ID_libro == stoi(id_libro) && (actual->pedido.estadoPedido == "PRESTADO" || actual->pedido.estadoPedido == "NO_DEVUELTO"))
            {
                idLibroEncontrado = true;
                ListaLibros listaLibros = leerLibrosCSV("output/libros.csv");
                nodoLibros *actualLibro = listaLibros.cabeza;
                while (actualLibro != nullptr)
                {
                    if (actualLibro->libro.id == stoi(id_libro))
                    {
                        actualLibro->libro.estado = "Disponible";
                        nombreLibroDevuelto = actualLibro->libro.nombre_Libro;
                        break;
                    }
                    actualLibro = actualLibro->siguiente;
                }

                guardar_CSV_Libros_Sobreescribir(&listaLibros, "output/libros.csv");

                time_t tiempoActual = time(nullptr);

                // Convierte el tiempo a una estructura tm
                tm *tiempoLocal = localtime(&tiempoActual);

                actual->pedido.devolucion.año = tiempoLocal->tm_year + 1900;
                actual->pedido.devolucion.mes = tiempoLocal->tm_mon + 1;
                actual->pedido.devolucion.dia = tiempoLocal->tm_mday;

                dias = calcularDiasEntreFechas(actual->pedido.fechaPedido.año, actual->pedido.fechaPedido.mes, actual->pedido.fechaPedido.dia, actual->pedido.devolucion.año, actual->pedido.devolucion.mes, actual->pedido.devolucion.dia);

                if (dias > 7)
                {
                    mora = 3 * (dias - 7);
                    actual->pedido.estadoPedido = "DEVUELTO_TARDE";
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