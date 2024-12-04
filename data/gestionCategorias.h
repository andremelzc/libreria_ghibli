#pragma once
#include "persistenciaDatos.h"
#include "gestionLibros.h"
#include "prestamoLibro.h"
#include <iomanip> // Asegúrate de incluir esto
using namespace std;

// Función para agregar un nodo al inicio de la lista
void agregarInicio(ListaCategorias& lista, Categorias nuevaCategoria) {
    NodoCategorias* nuevoNodo = new NodoCategorias(nuevaCategoria);
    nuevoNodo->sgte = lista.head;
    lista.head = nuevoNodo;
    lista.longitud++;
}

// Función para agregar un nodo al final de la lista
void agregarFinal(ListaCategorias& lista, Categorias nuevaCategoria) {
    NodoCategorias* nuevoNodo = new NodoCategorias(nuevaCategoria);
    if (lista.head == nullptr) {
        lista.head = nuevoNodo;
    } else {
        NodoCategorias* temp = lista.head;
        while (temp->sgte != nullptr) {
            temp = temp->sgte;
        }
        temp->sgte = nuevoNodo;
    }
    lista.longitud++;
}

// Función para eliminar un nodo al inicio de la lista
void eliminarInicio(ListaCategorias& lista) {
    if (lista.head == nullptr) {
        cout << "La lista est"<<(char)160<<" vacia, no se puede eliminar." << endl;
        return;
    }
    NodoCategorias* temp = lista.head;
    lista.head = lista.head->sgte;
    delete temp;
    lista.longitud--;
}

// Función para eliminar un nodo al final de la lista
void eliminarFinal(ListaCategorias& lista) {
    if (lista.head == nullptr) {
        cout << "La lista est"<<(char)160<<" vacia, no se puede eliminar." << endl;
        return;
    }
    if (lista.head->sgte == nullptr) {
        delete lista.head;
        lista.head = nullptr;
    } else {
        NodoCategorias* temp = lista.head;
        while (temp->sgte->sgte != nullptr) {
            temp = temp->sgte;
        }
        delete temp->sgte;
        temp->sgte = nullptr;
    }
    lista.longitud--;
}

// Función para eliminar todos los registros de una lista
void eliminarTodos(ListaCategorias& lista) {
    NodoCategorias* temp = lista.head;
    while (temp != nullptr) {
        NodoCategorias* nodoAEliminar = temp;
        temp = temp->sgte;
        delete nodoAEliminar; // Liberar la memoria del nodo actual
    }
    lista.head = nullptr;  // La lista queda vacía
    lista.longitud = 0;    // La longitud se reinicia a 0
}

void eliminarNodoXCategoria(ListaCategorias& lista, const std::string& nombre) {
    if (lista.head == nullptr) {
        cout << "La lista est"<<(char)160<<" vac"<<(char)161<<"a.\n";
        return;
    }

    NodoCategorias* temp = lista.head;
    NodoCategorias* anterior = nullptr;

    // Recorrer la lista para encontrar el nodo a eliminar
    while (temp != nullptr) {
        if (temp->categoria.nombre == nombre) {
            // Caso: El nodo a eliminar es el primero
            if (anterior == nullptr) {
                lista.head = temp->sgte;
            } else {
                anterior->sgte = temp->sgte;
            }

            // Liberar la memoria del nodo eliminado
            delete temp;

            cout << "Categor"<<(char)161<<"a \"" << nombre << "\" eliminada.\n";
            return;
        }

        anterior = temp; // Guardar referencia al nodo actual
        temp = temp->sgte; // Avanzar al siguiente nodo
    }

    cout << "Categor"<<(char)161<<"a \"" << nombre << "\" no encontrada.\n";
}


// Función para mostrar la lista
void mostrarLista(const ListaCategorias& lista) {
    NodoCategorias* temp = lista.head;
    if (temp == nullptr) {
        cout << "La lista est"<<(char)160<<" vacia." << endl;
        return;
    }
    while (temp != nullptr) {
        cout << "Categoria: " << temp->categoria.nombre << ", Popularidad: " << temp->categoria.popularidad << endl;
        temp = temp->sgte;
    }
}
void mostrarListaConLibro(const ListaCategorias& lista) {
    ListaPedidos listaPedidosGeneral = leerPedidosDesdeCSV("output/pedidos.csv");
    
    
    NodoCategorias* temp = lista.head;
    if (temp == nullptr) {
        color(0);//Negro
        gotoxy(27, 15);
        cout << "La lista est"<<(char)160<<" vacia." << endl;
        return;
    }
    int lineaBase = 14;
    while (temp != nullptr) {
        color(0);//Negro
        gotoxy(27, lineaBase);
        cout << temp->categoria.nombre;
        gotoxy(50, lineaBase);
        cout << temp->categoria.libroPopular.nombre_Libro;
        gotoxy(85, lineaBase);
        int popu = temp->categoria.libroPopular.popularidad;
        cout << popu;
        gotoxy(90, lineaBase);
        int longi = listaPedidosGeneral.longitud;
        float porce = (static_cast<float>(popu) / longi) * 100;
        cout << fixed << setprecision(2) << porce << "%";
        lineaBase++;
        temp = temp->sgte;
    }
}

// Función para buscar un nombre en la lista
bool buscarExistenciaCategoria(const ListaCategorias& lista, const string& nombre) {
    NodoCategorias* temp = lista.head;
    while (temp != nullptr) {
        if (temp->categoria.nombre == nombre) {
            return true; // Se encontró el nombre
        }
        temp = temp->sgte;
    }
    return false; // No se encontró el nombre o es Nulo
}

// Función para buscar un nombre en la lista
void aumentarPopularidadCategoria(ListaCategorias& lista, const string& nombre) {
    NodoCategorias* temp = lista.head; // Apuntador al inicio de la lista
    while (temp != nullptr) {
        if (temp->categoria.nombre == nombre) {
            temp->categoria.popularidad++; // Incrementar popularidad
            break; // Salir del bucle al encontrar
        }
        temp = temp->sgte; // Avanzar al siguiente nodo
    }
}

NodoCategorias* nodoConMayorPopularidad(ListaCategorias& lista) {
    if (lista.head == nullptr) {
        return nullptr; // La lista está vacía
    }

    NodoCategorias* mayor = lista.head; // Apuntador al nodo con mayor popularidad
    NodoCategorias* temp = lista.head->sgte; // Comenzamos desde el segundo nodo

    while (temp != nullptr) {
        if (temp->categoria.popularidad > mayor->categoria.popularidad) {
            mayor = temp; // Actualizar el nodo con mayor popularidad
        }
        temp = temp->sgte; // Avanzar al siguiente nodo
    }

    return mayor; // Retornar el nodo encontrado
}


void obtenerTodasCategoriasClienteParticular(int idCliente, ListaCategorias *listaCate){
    //Obtengo lista Pedidos 
    //ListaPedidos leerPedidosDesdeCSV(string nombreArchivo) -> de prestamoLibro.h
    ListaPedidos listaPedidosGeneral = leerPedidosDesdeCSV("output/pedidos.csv");
    NodoPedidos *temporalPedido = listaPedidosGeneral.head;
    //Obtengo Lista Libros
    //leerPedidosDesdeCSV(string nombreArchivo) -> prestamoLibro.h
    ListaLibros listaLibrosGeneral = leerLibrosCSV("output/Libros.csv");
    nodoLibros *temporalLibro;
    //Creo Categorias para agregar
    Categorias cateVaciado;

    //Recorro la Lista de Pedidos
    //cout<<"El usuario es: "<<idCliente<<endl;
    while(temporalPedido != nullptr){
        //Si el pedido es de mi cliente obtego el libro usando
        if(temporalPedido->pedido.ID_usuario == idCliente){
            //nodoLibros *buscarLibroPorID(ListaLibros &listaLibros, int idLibro)
            temporalLibro = buscarLibroPorID(listaLibrosGeneral, temporalPedido->pedido.ID_libro);
            //cout<<"Libro: "<<temporalPedido->pedido.ID_libro<<" "<<temporalLibro->libro.nombre_Libro<<" "<<temporalLibro->libro.Genero<<endl;
            
            //Si la categoría es nueva la Agrego
            //bool buscarExistenciaCategoria(const ListaCategorias& lista, const string& nombre)->propia
            string categoriaTemporal = temporalLibro->libro.Genero;
            if(buscarExistenciaCategoria(*listaCate, categoriaTemporal)){
                //cout<<"Lo encontramos"<<endl;
                //Si no es nuevo Sumo en Popularidad
                //void aumentarPopularidadCategoria(ListaCategorias& lista, const string& nombre)->propia
                aumentarPopularidadCategoria(*listaCate, categoriaTemporal);
            }else{
                //cout<<"No lo encontramos"<<endl;
                //void agregarFinal(ListaCategorias& lista, Categorias nuevaCategoria) -> propio
                cateVaciado.nombre = categoriaTemporal;
                cateVaciado.popularidad = 1;
                agregarFinal(*listaCate, cateVaciado);
            }
            
        }
        
        temporalPedido = temporalPedido->sgte;
    }
    //Al finalizar la listaCategorias estara cargada con las Categorias del Usuario y su respectiva popularidad
}   

/*
void librosPopularesXCategorias(ListaCategorias *listaCate){
    ListaCategorias *listaCategoriasCliente = listaCate;
    //NodoCategorias *categoriaTemporal = listaCate->head;

    //Obtengo lista Pedidos 
    //ListaPedidos leerPedidosDesdeCSV(string nombreArchivo) -> de prestamoLibro.h
    ListaPedidos listaPedidosGeneral = leerPedidosDesdeCSV("output/pedidos.csv");
    NodoPedidos *temporalPedido = listaPedidosGeneral.head;
    //Obtengo Lista Libros
    //leerPedidosDesdeCSV(string nombreArchivo) -> prestamoLibro.h
    ListaLibros listaLibrosGeneral = leerLibrosCSV("output/Libros.csv");
    nodoLibros *temporalLibro;
    //Para obtener los Libros de una Categoria Especifica
    ListaLibros listaLibroCateEspecifica;
    //Para cada categoría de la ListaCategorias
    

    while(listaCategoriasCliente->head != nullptr){
        string nombreCateTemporal;
        //Verifico que iniciemos en el Incio de la Lista
        temporalPedido = listaPedidosGeneral.head;
        //Recorrere los pedidos
        while(temporalPedido != nullptr){
            //Obtengo libro del Pedido
            //nodoLibros *buscarLibroPorID(ListaLibros &listaLibros, int idLibro)
            temporalLibro = buscarLibroPorID(listaLibrosGeneral, temporalPedido->pedido.ID_libro);
            //Si es de la categoría de este ciclo ejecuto
            if(temporalLibro->libro.Genero == nombreCateTemporal){
                string nombreLibroTemporal = temporalLibro->libro.Genero;
                //Determinar si ya he considerado este Libro
                //bool determinarSiExisteLibro(const ListaLibros &lista, const string &nombreBusco)
                if(determinarSiExisteLibro(listaLibroCateEspecifica, nombreLibroTemporal)){
                    //Ya Lo he Encontrado
                    //void incrementarPopularidadLibro(ListaLibros &lista, const string &nLibro)
                    incrementarPopularidadLibro(listaLibroCateEspecifica, nombreLibroTemporal);
                }else{
                    //No lo he encontrado
                    Libro libroVaceado = temporalLibro->libro;
                    libroVaceado.popularidad = 1;
                    //insertarLibrosFinal(ListaLibros *lista, Libro *libro)
                    insertarLibrosFinal(&listaLibroCateEspecifica, &libroVaceado);
                }
            }
        }
        //En este Punto la ListaLibros Especificos esta llena con todos los Libros de La categoria Especifica
        //nodoLibros* obtenerLibroMasPopular(ListaLibros &lista)
        //Obtener el Libro con Mayor Popularidad
        nodoLibros *nodoLibroTemporalMasPopular =  obtenerLibroMasPopular(listaLibroCateEspecifica);
        //Agregarselo a la listaCate
        listaCategoriasCliente->head->categoria.libroPopular = nodoLibroTemporalMasPopular->libro;
        
        //Vacio la Lista de Libros Especificos
        //void vaciarListaLibros(ListaLibros &lista)
        vaciarListaLibros(listaLibroCateEspecifica);
        //Paso a la Siguiente Categoria en la Lista
        listaCategoriasCliente->head = listaCategoriasCliente->head->sgte;
    }

}*/

void librosPopularesXCategorias(ListaCategorias *listaCate) {
    // Verificación inicial
    if (listaCate == nullptr || listaCate->head == nullptr) {
        return; // Lista vacía o nula, no hay nada que procesar
    }

    // Lista de categorías
    NodoCategorias *categoriaActual = listaCate->head;

    // Obtengo lista de pedidos
    ListaPedidos listaPedidosGeneral = leerPedidosDesdeCSV("output/pedidos.csv");
    NodoPedidos *temporalPedido;

    // Obtengo lista de libros
    ListaLibros listaLibrosGeneral = leerLibrosCSV("output/Libros.csv");
    nodoLibros *temporalLibro;

    // Para obtener los libros de una categoría específica
    ListaLibros listaLibroCateEspecifica;

    // Para cada categoría de la ListaCategorias
    while (categoriaActual != nullptr) {
        string nombreCateTemporal = categoriaActual->categoria.nombre; // Nombre de la categoría actual

        // Recorro los pedidos
        temporalPedido = listaPedidosGeneral.head;
        while (temporalPedido != nullptr) {
            // Obtengo libro del pedido
            temporalLibro = buscarLibroPorID(listaLibrosGeneral, temporalPedido->pedido.ID_libro);

            // Verifico que el libro sea válido y que pertenezca a la categoría actual
            if (temporalLibro != nullptr && temporalLibro->libro.Genero == nombreCateTemporal) {
                string nombreLibroTemporal = temporalLibro->libro.nombre_Libro;

                // Determino si ya he considerado este libro
                if (determinarSiExisteLibro(listaLibroCateEspecifica, nombreLibroTemporal)) {
                    // Incremento la popularidad del libro
                    incrementarPopularidadLibro(listaLibroCateEspecifica, nombreLibroTemporal);
                } else {
                    // No lo he encontrado, lo añado a la lista específica
                    Libro libroVaceado = temporalLibro->libro;
                    libroVaceado.popularidad = 1;
                    insertarLibrosFinal(&listaLibroCateEspecifica, &libroVaceado);
                }
            }

            temporalPedido = temporalPedido->sgte; // Avanzo al siguiente pedido
        }

        // En este punto, la lista `listaLibroCateEspecifica` está llena con todos los libros de la categoría actual
        nodoLibros *nodoLibroTemporalMasPopular = obtenerLibroMasPopular(listaLibroCateEspecifica);

        // Verifico que haya un libro popular antes de asignarlo
        if (nodoLibroTemporalMasPopular != nullptr) {
            categoriaActual->categoria.libroPopular = nodoLibroTemporalMasPopular->libro;
        }

        // Vacío la lista de libros específicos
        vaciarListaLibros(listaLibroCateEspecifica);

        // Paso a la siguiente categoría
        categoriaActual = categoriaActual->sgte;
    }
}

void menu_sugerencias(int idUsuario){
    ListaCategorias listaUsuario;
    obtenerTodasCategoriasClienteParticular(idUsuario, &listaUsuario);
    librosPopularesXCategorias(&listaUsuario);

    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);

    gotoxy(43, 12);
    color(2);//Verde
    cout << "Le Recomendamos segun sus Preferencias";

    
    gotoxy(27, 13);
    cout << "Categoria";
    gotoxy(50, 13);
    cout << "Nombre";
    gotoxy(85, 13);
    cout << "#";
    gotoxy(90, 13);
    cout << "%";

    mostrarListaConLibro(listaUsuario);

    gotoxy(35, 25);
    color(2);//Verde
    system("PAUSE");
}