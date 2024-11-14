#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <locale>
#include <ctime>
#include <filesystem>
#include <cctype> 
#include <conio.h>
#include <windows.h>
using namespace std;
void menu_CompraCarrito(int id_usuario);
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
        // std::cerr << "Error: El directorio 'output/carrito.csv' no existe." << std::endl;
        pausa();
        return;
    }

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open())
    {
        // cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
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
        // std::cerr << "Error: Fallo al escribir en el archivo." << std::endl;
        archivo.close();
        return;
    }

    archivo.close();
    // cout << "Datos guardados en " << nombreArchivo << endl;
    //pausa();
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
    // cout << "Datos cargados desde " << nombreArchivo << endl;
    return lista;
}


bool verificarRegistroPreExistente(int id_usuario, std::string nom_libro) {
    // Inicializo registroExiste como false
    bool registroExiste = false;
    
    // Leer las listas desde los archivos CSV
    ListaCarritos listaCarritosGeneral = leerCSV("output/carrito.csv");
    ListaLibros listaLibrosGeneral = leerLibrosCSV("output/libros.csv");
    nodoLibros* libroTraido;

    if (listaCarritosGeneral.head != NULL) {
        NodoCarritos* temporal = listaCarritosGeneral.head;

        // Recorre cada registro en el carrito del usuario
        while (temporal != NULL) {
            // Si el usuario del carrito coincide con id_usuario
            if (temporal->carrito.id_cliente == id_usuario) {
                // Busca el libro en la lista de libros usando el id_producto del carrito
                int idLibroBusqueda = temporal->carrito.id_producto;
                libroTraido = buscarLibroPorID(listaLibrosGeneral, idLibroBusqueda);

                if (libroTraido != NULL) {
                    // Compara el nombre del libro en el carrito con nom_libro
                    if (libroTraido->libro.nombre_Libro == nom_libro) {
                        registroExiste = true;
                        break; // Salir del bucle, ya que encontramos el registro
                    }
                }
            }
            // Avanza al siguiente nodo sin alterar listaCarritosGeneral.head
            temporal = temporal->sgte;
        }
    }
    
    // Devuelve true si el registro existe, false si no
    return registroExiste;
}

int contarPedidosLibroEstado(int id_usuario, std::string nom_libro, std::string estado_libro) {
    // Inicializo el contador en 0
    int contadorPedidos = 0;

    // Leer las listas desde los archivos CSV
    ListaCarritos listaCarritosGeneral = leerCSV("output/carrito.csv");
    ListaLibros listaLibrosGeneral = leerLibrosCSV("output/libros.csv");
    nodoLibros* libroTraido;

    if (listaCarritosGeneral.head != nullptr) {
        NodoCarritos* temporal = listaCarritosGeneral.head;

        // Recorre cada registro en el carrito del usuario
        while (temporal != nullptr) {
            // Si el usuario del carrito coincide con id_usuario
            if (temporal->carrito.id_cliente == id_usuario) {
                // Busca el libro en la lista de libros usando el id_producto del carrito
                int idLibroBusqueda = temporal->carrito.id_producto;
                libroTraido = buscarLibroPorID(listaLibrosGeneral, idLibroBusqueda);

                if (libroTraido != nullptr) {
                    // Compara el nombre del libro en el carrito con nom_libro
                    if (libroTraido->libro.nombre_Libro == nom_libro && libroTraido->libro.estado == estado_libro) {
                        contadorPedidos++; // Incrementa el contador cada vez que hay coincidencia
                    }
                }
            }
            // Avanza al siguiente nodo sin alterar listaCarritosGeneral.head
            temporal = temporal->sgte;
        }
    }

    // Devuelve el número de veces que el usuario ha pedido el libro
    return contadorPedidos;
}


void agregarCarrito(int id_usuario)
{
    ListaCarritos listaCarritosGeneral = leerCSV("output/carrito.csv");
    ListaCarritos listaCarritoActual; // Para almacenar todos los pedidos que haga
    ListaLibros listaLibrosGeneral = leerLibrosCSV("output/libros.csv");//Para cargar las Modificaciones de Estado de los Libros
    bool confirmacion_agregar = false;
    bool seguir_agregando = false;
    bool stock_suficiente = false;
    // Cuento Filas de Carrito para obtener el Id //El agregado debe considerar las iteraciones
    int id_carritoInicial = contarFilasCSV("output/carrito.csv");

    int agregado = 1;
    // int numero_lineas = listaCarritosGeneral.longitud;
    do
    {
        limpiarPantalla();
        setConsoleBackground(White);
        dibujarTitulo(27, 0, 2, letras);
        estructura_menu2(16, 103, 10, 27);

        gotoxy(48, 11);
        color(2);
        cout << "Agregando libro al carrito";
        color(0);

        confirmacion_agregar = false;

        
        // int id_carrito = numero_lineas + agregado;
        int id_producto, cantidad;
        // Creo una lista para obtener todos los libros
        ListaLibros listalibros;
        listalibros = leerLibrosCSV("output/libros.csv");
        nodoLibros *producto;
        
        ListaLibros listaLibroEspecifico;

        string nombreLibro;
        gotoxy(27, 13);
        color(2);
        cout << "Nombre del libro a comprar: ";
        color(0);
        getline(cin, nombreLibro);

        char desicion;
        producto = buscarLibroPorTitulo(listalibros, nombreLibro);//*nodoLibros
        if (producto != nullptr)
        {   
            //Si ingreso un Nombre Valido

            //Si ya lo Habia Agregado Previamente al carrito -> No podrá Agregarlo otra vez
            if(verificarRegistroPreExistente(id_usuario, producto->libro.nombre_Libro)){

                limpiarPantalla();
                setConsoleBackground(White);
                dibujarTitulo(27, 0, 2, letras);
                estructura_menu2(16, 103, 10, 27);
                gotoxy(27, 19);
                color(2);
                cout<<"Usted ya ha agregado este Libro, si desea Agregar mas Modifique su Carrito"<<endl;

                getch();
            }else{
                mostrarLibroXTitulo(listalibros, producto->libro.nombre_Libro, id_producto);
                gotoxy(27, 21);
                color(2);
                cout << "Cantidad que desea comprar: ";
                color(0);
                cin >> cantidad;
                cin.ignore();
                stock_suficiente = false;
                //Verificar si Tengo el Stock Suficiente para esta Compra
                listaLibroEspecifico = leerLibrosCSV_ObtenerStockLibroEspecifico("output/libros.csv", producto->libro.nombre_Libro);
                if(listaLibroEspecifico.longitud >= cantidad ){
                    stock_suficiente = true;
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
                }else{
                    limpiarPantalla();
                    setConsoleBackground(White);
                    dibujarTitulo(27, 0, 2, letras);
                    estructura_menu2(16, 103, 10, 27);
                    
                    color(2);
                    
                    gotoxy(27, 12);
                    cout<<"ERROR: Su pedido excede el Stock Disponible";
                    gotoxy(27, 13);
                    cout<<"Stock Disponible: "<<listaLibroEspecifico.longitud;
                    gotoxy(27, 14);
                    cout<<"Usted ha pedido: "<<cantidad;
                    /*
                    if(listaLibroEspecifico.cabeza!=NULL){
                        while (listaLibroEspecifico.cabeza!=NULL)
                        {
                            cout<<" id: "<<listaLibroEspecifico.cabeza->libro.id <<" Nombre"<<listaLibroEspecifico.cabeza->libro.nombre_Libro<<endl;
                            listaLibroEspecifico.cabeza = listaLibroEspecifico.cabeza->siguiente;
                        }
                    }
                    cout<<"Stock por Funcionalidad General "<<producto->libro.stock<<endl;***/
                    getch();
                }
                
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
            //Los registros son Unicos por cada pedido de Libros

            if(stock_suficiente){
                for(int i=0;i<cantidad;i++){
                    int id_modificar;
                    structCarritoActual.id_carrito = id_carritoInicial + agregado;
                    structCarritoActual.id_producto = listaLibroEspecifico.cabeza->libro.id;
                    id_modificar = listaLibroEspecifico.cabeza->libro.id;
                    structCarritoActual.id_cliente = id_usuario;
                    structCarritoActual.cantidad = 1;
                    structCarritoActual.fecha = to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
                    structCarritoActual.estado = 0;
                    // Agregamos el Nodo a nuestra lista de Pedidos Actuales
                    insertarCarritoFinal(&listaCarritoActual, structCarritoActual);
                    //Modificare la ListaGeneralLibros para guardar los cambios al finalizar el proceso de Agregar Carrito
                    modificarEstadoLibro(&listaLibrosGeneral, id_modificar, "Pedido");
                    eliminarPrimerLibro(&listaLibroEspecifico);
                    agregado++;
                }
            }
            
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
        guardar_CSV_Libros_Sobreescribir(&listaLibrosGeneral, "output/libros.csv");
    }
}

void mostrarTodoCarrito()
{
    ListaCarritos listaCarritosGeneral = leerCSV("output/carrito.csv");

    // Creo una lista para obtener todos los libros
    ListaLibros listalibros;
    listalibros = leerLibrosCSV("output/libros.csv");
    nodoLibros *producto;

    // system("CLS");
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    gotoxy(34, 11);
    color(2);
    cout << "Carrito de Compras";

    if (listaCarritosGeneral.head != NULL)
    {
        NodoCarritos *temporal = listaCarritosGeneral.head;
        while (listaCarritosGeneral.head != NULL)
        {
            cout << temporal->carrito.cantidad << "\t";
            producto = buscarLibroPorID(listalibros, temporal->carrito.id_producto);
            cout << producto->libro.nombre_Libro << "\t";
            cout << temporal->carrito.cantidad * producto->libro.precio << endl;

            listaCarritosGeneral.head = temporal->sgte;
            temporal = listaCarritosGeneral.head;
        }
    }
    else
    {
        cout << "No hay ningun Registro de Carritos" << endl;
    }

    getch();
}

string mostrarEstadoCarrito(int estado)
{   string str_estado;
    switch (estado)
    {
    case 0:
        str_estado = "Pedido";
        break;
    case 1:
        str_estado = "Comprado";
        break;
    case 2:
        str_estado = "Eliminado";
        break;
    default:
        str_estado = "INDEFINIDO";
        break;
    }
    return str_estado;
}

bool VerificarSiLibroEstaLista(ListaLibros lista, std::string nombreLibro) {
    // Puntero al primer nodo de la lista de carritos
    nodoLibros *actual = lista.cabeza;

    // Recorrer la lista enlazada
    while (actual != nullptr) {
        // Comparar el nombre del libro con el nombre pasado como parámetro
        if (actual->libro.nombre_Libro == nombreLibro) {
            return true;  // Coincidencia encontrada, retornar false
        }
        // Avanzar al siguiente nodo
        actual = actual->siguiente;
    }

    // Si no se encontró ninguna coincidencia, retornar true
    return false;
}

void mostrarListaCarrito(ListaCarritos listaMostrar){
    if(listaMostrar.head != NULL){
        while(listaMostrar.head !=NULL){
            cout<<"IdCarrito:"<<listaMostrar.head->carrito.id_carrito<<" - Cliente: "<<listaMostrar.head->carrito.id_cliente<<" - LibroId: "<<listaMostrar.head->carrito.id_producto<<endl;
            listaMostrar.head = listaMostrar.head->sgte;
        }
    }
    
}

void mostrarCarritoUsu(int id_usuario, int estado)
{   
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    gotoxy(50, 11);
    color(2);
    cout << "Carrito de Compras";

    dibujarTitulo(22, 18, 2, carritoCompras);

    ListaCarritos listaCarritosGeneral = leerCSV("output/carrito.csv");
    //mostrarListaCarrito(listaCarritosGeneral); //Empleado para Pruebas
    ListaLibros listaLibrosGeneral = leerLibrosCSV("output/libros.csv");

    ListaLibros listaLibrosUnicos;
    nodoLibros *temporal_libro;
    
    Libro libro_vaceado;

    int cantidad_libro_temporal;
    int precio_total = 0;
    //Voy a Recorrer el ListaCarritoGeneral
    int incremento_linea = 1;
    NodoCarritos *temporal_carrito = listaCarritosGeneral.head;
    if(temporal_carrito != NULL){
            color(2);
            gotoxy(27, 13);
            cout << "Libro";
            gotoxy(50, 13);
            cout << "Cantidad";
            gotoxy(60, 13);
            cout << "P. unitario";
            gotoxy(75, 13);
            cout << "P. total";
            color(0);       
        while(temporal_carrito != NULL ){
            //Mostrare solo los que sea de mi Cliente y esten en Estado 0 osea Pedidos;
            if(temporal_carrito->carrito.id_cliente == id_usuario && temporal_carrito->carrito.estado == 0){
                //Obtener el Libro usando el idCarrito
                temporal_libro = buscarLibroPorID(listaLibrosGeneral, temporal_carrito->carrito.id_producto);
                //Verificamos si ya hemos mostrado ese Libro
                if(VerificarSiLibroEstaLista(listaLibrosUnicos, temporal_libro->libro.nombre_Libro)){
                    //Encontramos el Libro en ListaLibrosUnicos, por lo cual no lo volveremos a imprimir
                    //cout<<"Lo Encontre   :"<<endl;
                }else{
                    //No Encontramos el Libro en ListaLibrosUnicos, por lo cual tendremos que imprimir
                    //cout<<"No Encontre   :"<<endl;
                    libro_vaceado = temporal_libro->libro;
                    insertarLibrosFinal(&listaLibrosUnicos, &libro_vaceado);
                    //Obtener la cantidad de Libros con idUsuario, nombreLibro, estadoLibro en el Registro de Carritos -> Estado Cambiará Cuando implementemos Cmabios de Estado
                    cantidad_libro_temporal = contarPedidosLibroEstado(id_usuario, temporal_libro->libro.nombre_Libro, "Pedido");
                    
                    //Nombre Libro
                    gotoxy(27, 14 + incremento_linea);
                    if (temporal_libro->libro.nombre_Libro.length() > 20)
                    {
                        cout << temporal_libro->libro.nombre_Libro.substr(0, 20) << "...";
                    }
                    else
                    {
                        cout << temporal_libro->libro.nombre_Libro;
                    }
                    //Cantidad
                    gotoxy(53, 14 + incremento_linea);
                    cout<<cantidad_libro_temporal;
                    //Precio Unitario
                    gotoxy(64, 14 + incremento_linea);
                    cout<<temporal_libro->libro.precio;
                    //Precio Total
                    gotoxy(77, 14 + incremento_linea);
                    cout<<cantidad_libro_temporal*temporal_libro->libro.precio<<endl;
                    incremento_linea++;
                    precio_total = precio_total + cantidad_libro_temporal*temporal_libro->libro.precio;
                    //cout<<"idPedido:"<<temporal_carrito->carrito.id_carrito<<" - idUsuario: "<<temporal_carrito->carrito.id_cliente<<" - Estado: "<<temporal_carrito->carrito.estado<<endl;
                }
                
                
            }
            //Paso al siguiente Nodo (Registro en Carrito)
            temporal_carrito = listaCarritosGeneral.head->sgte;
            listaCarritosGeneral.head = temporal_carrito;
        }
        
        gotoxy(77, 14 + incremento_linea + 1);
        cout<<precio_total;
        char compras;
        gotoxy(53, 14 + incremento_linea + 7);
        cout<<"Desea Comprar un Libro(s/n):";
        gotoxy(53, 14 + incremento_linea + 8);
        cin>>compras;
        cin.ignore();
        if(compras == 's' || compras == 'S'){
            menu_CompraCarrito(id_usuario);
        }
    }
    //mostrarListaLibroSimple(listaLibrosUnicos); //Empleado para Pruebas
}

void modificarEstadoRegistroCarritoXIdCarrito(ListaCarritos *listaDeCarritos, int idLibro_Modificar, int estadoNuevo)
{

    NodoCarritos *actual = listaDeCarritos->head; // Asumiendo que la lista tiene un puntero a su nodo cabeza
    if (actual != nullptr){
        // Recorrer la lista enlazada
        while (actual != nullptr)
        {
            // Verificar si el ID del libro actual coincide con el ID proporcionado
            if (actual->carrito.id_producto == idLibro_Modificar)
            {
                
                actual->carrito.estado = estadoNuevo;
                
                return; 
            }
            actual = actual->sgte; 
        }
    }else{
        // Si el libro no se encuentra, mostrar un mensaje
    cout << "No se encontró un Registro en Carritos con el ID " << idLibro_Modificar << " en la lista." << endl;
    }
    
}


void efectuarCompraCarrito(int id_usuario, bool &seguirComprando)
{       
    system("CLS");
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    gotoxy(50, 11);
    color(2);
    
    ListaCarritos listaCarritosGeneral = leerCSV("output/carrito.csv");
    //mostrarListaCarrito(listaCarritosGeneral);
    NodoCarritos *carrito_temporal = listaCarritosGeneral.head;

    ListaLibros listaLibrosGeneral = leerLibrosCSV("output/libros.csv");
    ListaLibros listaLibrosEspecifico;listaLibrosEspecifico.longitud = 0;
    ListaLibros listaLibrosCarrito; listaLibrosCarrito.longitud = 0;
    //mostrarListaLibroSimple(listaLibrosGeneral);

    nodoLibros *libro_temporal;
    nodoLibros *libro_pedido;
    
    Libro libro_vaceado;

    int cantidad_libro;
    char comprar;
    char seguir_comprando;
    
    string nombre_libro_pedido;
    
    gotoxy(27, 15);
    cout<<"Ingrese Nombre del Libro a Comprar:";
    getline(cin,nombre_libro_pedido);
    
    //Obtengo un Libro a partir del nombreDeLibro ingresado
    libro_pedido = buscarLibroPorTituloPedido(listaLibrosGeneral, nombre_libro_pedido);
    
    //Si ingreso un Nombre Valido obtendre un libro 
    if(libro_pedido != nullptr){
        
        //Buscare entre los Los Regsitros del Carrito
        if(carrito_temporal != nullptr){
        
            while(carrito_temporal != nullptr){
                //Obtendre el LibroPedido a partir del idProducto registrado en el Carrito
                libro_temporal = buscarLibroPorID(listaLibrosGeneral, carrito_temporal->carrito.id_producto);

                if(carrito_temporal->carrito.id_cliente == id_usuario && carrito_temporal->carrito.estado == 0 && libro_temporal->libro.nombre_Libro == libro_pedido->libro.nombre_Libro){
                    
                    //cout<<"idPedido: "<<carrito_temporal->carrito.id_carrito;
                    //cout<<" - idLibro: "<<carrito_temporal->carrito.id_producto<<" - "<<libro_temporal->libro.nombre_Libro<<endl;
                    
                    libro_vaceado = libro_temporal->libro;
                    insertarLibrosFinal(&listaLibrosEspecifico, &libro_vaceado);
                    //cout<<"Agregamos Nodo a LISTA ESPECIFICA"<<endl;
                    
                }
                carrito_temporal = carrito_temporal->sgte;
            }
            //mostrarListaLibroSimple(listaLibrosEspecifico);
            gotoxy(27, 16);
            cout<<"Usted ha pedido :"<<listaLibrosEspecifico.longitud<<endl;
            
            //Si el CLiente pidio el Libro
            if(listaLibrosEspecifico.cabeza != nullptr){
                gotoxy(27, 17);
                cout<<"Determine la Cantidad a Comprar:";
                cin>>cantidad_libro;
                int stock_libro = listaLibrosEspecifico.longitud;
                if(listaLibrosEspecifico.longitud >= cantidad_libro && cantidad_libro != 0){
                    //cout<<"Cantidad Suficiente"<<endl;//system("PAUSE");
                    gotoxy(27, 18);
                    cout<<"¿Desea Comprar "<<cantidad_libro<<" de "<<listaLibrosEspecifico.cabeza->libro.nombre_Libro<<" ?(s/n):";
                    cin>>comprar;

                    if(comprar =='s' || comprar =='S'){
                    
                        for(int i=0; i<cantidad_libro; i++){
                            //Agrego a la ListaCarrito
                            libro_vaceado = listaLibrosEspecifico.cabeza->libro;

                            int id_modificar = listaLibrosEspecifico.cabeza->libro.id;
                            modificarEstadoLibro(&listaLibrosGeneral, id_modificar, "Comprado");
                            modificarEstadoRegistroCarritoXIdCarrito(&listaCarritosGeneral, id_modificar, 1);
                            insertarLibrosFinal(&listaLibrosCarrito, &libro_vaceado);

                            //Quita de la ListaEspecfica
                            eliminarPrimerLibro(&listaLibrosEspecifico);

                        }
                        //Debo vacear la listaEspecifica por si quiere un nuevo Comprar un Nuevo Libro
                        for(int i=0; i<stock_libro-cantidad_libro;i++){
                            eliminarPrimerLibro(&listaLibrosEspecifico);
                        }
                        
                        guardar_CSV_Carritos(&listaCarritosGeneral, "output/carrito.csv");
                        guardar_CSV_Libros_Sobreescribir(&listaLibrosGeneral, "output/libros.csv");
                        //Vacio Carrito
                        for(int i=0; i<cantidad_libro; i++){
                            eliminarPrimerLibro(&listaLibrosCarrito);
                        }

                    }else{
                        //No quiso Seguir con la Compra

                    }
                    gotoxy(27, 20);
                    cout<<"Desea seguir Comprando";
                    cin>>seguir_comprando;//Aqui es necesario un cin.ignore()
                    cin.ignore();
                    seguirComprando = false;
                    if(seguir_comprando == 's' || seguir_comprando == 'S'){
                        seguirComprando = true;
                    }
                }else{
                    //system("CLS");
                    gotoxy(27, 26);
                    cout<<"ERROR: Cantidad Pedida mayor a su Carrito o 0"<<endl;
                    gotoxy(27, 27);system("PAUSE");
                    seguirComprando = true;
                }

            }else{
                //system("CLS");
                gotoxy(27, 26);
                cout<<"ERROR: Usted No ha agregado a su Carrito el Libro Solicitado"<<endl;
                gotoxy(27, 27);system("PAUSE");
                seguirComprando = true;
            }
        }else{
            //NO HAY NINGUN REGISTRO DE NINGUN USUARIO EN CARRITO
            gotoxy(27, 26);
            //system("CLS");
            cout<<"ERROR: NO HAY NINGUN REGISTRO DE NINGUN USUARIO EN CARRITO"<<endl;
            gotoxy(27, 27);system("PAUSE");
            seguirComprando = true;
        }
    }
    else{
        //Nombre de Libro Ingresado Invalido
        gotoxy(27, 26);
        //system("CLS");
        cout<<"ERROR:Ha ingresado un Nombre Invalido o no Agregado a su Carrito:"<<nombre_libro_pedido;
        gotoxy(27, 27);system("PAUSE");
        seguirComprando = true;
        
    }
    
}

void menu_CompraCarrito(int id_usuario){
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    gotoxy(50, 11);
    color(2);
    cout << "INFORMACION BANCARIA";

    dibujarTitulo(22, 18, 2, carritoCompras);
    string nTarjeta, contra;
    gotoxy(27, 12);
    cout<<"Ingresar su Tarjeta:";
    getline(cin, nTarjeta);
    gotoxy(27, 14);
    cout<<"Ingresar Clave:";
    getline(cin, contra);
    gotoxy(27, 16);
    cout<<"Verificamos...";

    bool seguir = false;
    do{
        efectuarCompraCarrito(id_usuario, seguir);
    }while(seguir);
}