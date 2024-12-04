#pragma once
#include "../data/persistenciaDatos.h"
Lista leerUsuariosCSV(string nombreArchivo);
Nodo *buscarUsuarioPorDNI(Lista &listaUsuarios, string &dni); // Declaración previa
#include "../servicio/funcionalidades.h"
#include "../data/ganancias.h"
#include "../data/gestionUsuarios.h"
#include "gotoxy.h"
#include "../data/gestionLibros.h"
#include "../servicio/iniciarSesion.h"
#include "../data/gestionLaptops.h"
#include "../data/carritoLibro.h"
#include "../data/historialYEstadisticaLibros.h"
#include "../data/gestionIncidencias.h"
#include "../data/gestionStock.h"
#include "../data/gestionCategorias.h"
#include "../data/verReportes.h"
// Menu de opciones inicial
vector<string> opcionesMenuPrincipal = {"Ver catalogo",
                                        "Registrarse",
                                        "Iniciar sesion",
                                        "Salir"};
int numInicio = opcionesMenuPrincipal.size();

void menu_iniciarSesion();         // Declaración Previa  -> Para el Switch caso 3
void menu_opcionesAdministrador(); // Declaración Previa  -> Para el Switch caso 3
void menu_opcionesRecepcionista();
void menu_opcionesCliente();
void menu_opcionesLaptop(); // Declaración previa
void menu_opcionesGestionLibros();
void menu_opcionesGestionUsuarios();
void menu_opcionesGestionPedidos();
void menu_opcionesGestionLaptops();
void menu_opcionesPedido();
void menu_opcionesGestionLibros();   // Declaración previa
void menu_opcionesGestionUsuarios(); // Declaración previa
void menu_opcionesGestionPedidos();  // Declaración previa
void menu_opcionesGestionLaptops();  // Declaración previa
void menu_opcionesReportes();        // Declaración previa
void calificar_recepcionista(int);
void guardarCalificacionRecepcionista(int, int);
// Para cuando se inicie sesión
int id_usuariolog = 0;
int costoTotal = 0;
double mora = 0;

void menu_opcionesPrincipal()
{
  bool repeat = true;
  int opt = 1;
  while (repeat)
  {
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 11, 26);
    // Imprimir las opciones
    for (int i = 0; i < numInicio; i++)
    {
      setTextColor(0);
      if (i == opt - 1)
      {
        setTextColor(White);
        setTextColor(2);
        gotoxy(46, 17 + i);
        cout << "=>   ";
        gotoxy(48, 17 + i);
        cout << opcionesMenuPrincipal[i] << endl;
      }
      else
      {
        gotoxy(53, 17 + i);
        cout << "   " << opcionesMenuPrincipal[i] << endl;
      }
    }
    // Capturamos la entrada de usuario
    int input = _getch();
    ListaDobleLibros listaDeLibros;
    switch (input)
    {
    // Aumentar o disminuir la opcion en la que estamos
    case 72: // Flecha arriba
      opt = (opt == 1) ? numInicio : --opt;
      break;
    case 80: // Flecha abajo
      opt = (opt == numInicio) ? 1 : ++opt;
      break;
    // Ejecutar una de las opciones del menu
    case 13:
      switch (opt)
      {
      case 1:
      {
        // 1. Ver catalogo
        listaDeLibros = leerLibrosDoblesCSV("output/libros.csv", true);
        mostrarLibros(listaDeLibros, true);
        break;
      }
      case 2:
        // 2. Registrar cuenta
        menuInicio_registrarUsuario();
        break;
      case 3:
        // 3. Iniciar sesión
        int tipo;
        bool sesion;
        inicioSesion(tipo, sesion, id_usuariolog);
        if (sesion)
        {
          if (tipo == 2)
          {
            // Tipo 2 es para administador
            menu_opcionesAdministrador();
          }
          else if (tipo == 1)
          {
            // Tipo 1 es para recepcionista
            menu_opcionesRecepcionista();
          }
          else
          {
            // Tipo 0 es para usuario
            ListaPedidos pedidos = leerPedidosDesdeCSV("output/pedidos.csv");
            NodoPedidos *actual = pedidos.head;
            bool pedidoEncontrado = false;
            ListaPedidos listaPedidos = leerPedidosDesdeCSV("output/pedidos.csv");
            NodoPedidos *nodoPedidos = listaPedidos.head;
            bool flag = false;
            if (&listaPedidos != NULL)
            {
              while (nodoPedidos != NULL)
              {
                if (nodoPedidos->pedido.ID_recepcionistaRecibe != -1 && nodoPedidos->pedido.evaluacion == -1 && nodoPedidos->pedido.ID_usuario == id_usuariolog)
                {
                  flag = true;
                  break;
                }
                nodoPedidos = nodoPedidos->sgte;
              }
  
            }

            while (actual != nullptr)
            {
              if (actual->pedido.ID_usuario == id_usuariolog && flag == true)
              {
                pedidoEncontrado = true;
                break;
              }
              actual = actual->sgte;
            }
            if (pedidoEncontrado)
            {
              calificar_recepcionista(id_usuariolog);
            }

            menu_opcionesCliente();
          }
        }
        break;
      case 4:
        // 4. Salir
        repeat = false;
        system("CLS");
        break;
      default:
        cout << "Estas fuera del rango\n";
      }
    }
  }
}

// Menu de opciones administrador
vector<string> opcionesMenuAdministrador = {"Gestionar libros",
                                            "Gestionar usuarios",
                                            "Gestionar pedidos",
                                            "Gestionar laptops",
                                            "Ver reportes",
                                            "Cerrar sesion"};
int numAdmin = opcionesMenuAdministrador.size();

void menu_opcionesAdministrador()
{
  bool repeat = true;
  int opt = 1;
  while (repeat)
  {
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    imprimirCarita(103, 10, id_usuariolog);
    // Imprimir las opciones
    for (int i = 0; i < numAdmin; i++)
    {
      setTextColor(0);
      if (i == opt - 1)
      {
        setTextColor(White);
        color(2);
        gotoxy(46, 16 + i);
        cout << "=>   ";
        gotoxy(48, 16 + i);
        cout << opcionesMenuAdministrador[i] << endl;
      }
      else
      {
        gotoxy(53, 16 + i);
        cout << "   " << opcionesMenuAdministrador[i] << endl;
      }
    }
    // Capturamos la entrada de usuario
    int input = _getch();

    switch (input)
    {
    // Aumentar o disminuir la opcion en la que estamos
    case 72: // Flecha arriba
      opt = (opt == 1) ? numAdmin : --opt;
      break;
    case 80: // Flecha abajo
      opt = (opt == numAdmin) ? 1 : ++opt;
      break;
    // Ejecutar una de las opciones del menu
    case 13:
      switch (opt)
      {
      case 1:
      {
        // 1. Gestionar libros
        ejecutarGradienteDoble(150);
        menu_opcionesGestionLibros();
        break;
      }
      case 2:
        // 2. Gestionar usuarios
        ejecutarGradienteDoble(150);
        menu_opcionesGestionUsuarios();
        break;
      case 3:
        // 3. Gestionar pedidos
        ejecutarGradienteDoble(150);
        menu_opcionesGestionPedidos();
        break;
      case 4:
        // 4. Gestionar laptops
        ejecutarGradienteDoble(150);
        menu_opcionesGestionLaptops();
        break;
      case 5:
        // 5. Ver estadisticas
        ejecutarGradienteDoble(150);
        menu_opcionesReportes();
        break;
      case 6:
        // 6. Salir
        repeat = false;
        system("CLS");
        break;
      default:
        cout << "Estas fuera del rango\n";
      }
    }
  }
}

// Menu de opciones de gestionar libros (Administrador)
vector<string> opcionesMenuGestionLibros = {"Registrar libro",
                                            "Modificar libro",
                                            "Aumentar stock",
                                            "Retroceder"};
int numGestionLibros = opcionesMenuGestionLibros.size();

void menu_opcionesGestionLibros()
{
  bool repeat = true;
  int opt = 1;
  while (repeat)
  {
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    // Imprimir las opciones
    for (int i = 0; i < numGestionLibros; i++)
    {
      color(0);
      if (i == opt - 1)
      {
        setTextColor(White);
        color(2);
        gotoxy(46, 16 + i);
        cout << "=>   ";
        gotoxy(48, 16 + i);
        cout << opcionesMenuGestionLibros[i] << endl;
      }
      else
      {
        gotoxy(53, 16 + i);
        cout << "   " << opcionesMenuGestionLibros[i] << endl;
      }
    }
    // Capturamos la entrada de usuario
    int input = _getch();

    switch (input)
    {
    // Aumentar o disminuir la opcion en la que estamos
    case 72: // Flecha arriba
      opt = (opt == 1) ? numGestionLibros : --opt;
      break;
    case 80: // Flecha abajo
      opt = (opt == numGestionLibros) ? 1 : ++opt;
      break;
    // Ejecutar una de las opciones del menu
    case 13:
      switch (opt)
      {
      case 1:
      {
        // 1. Registrar libro
        adicionarCampo();
        break;
      }
      case 2:
        // 2. Modificar libro
        modificarLibro();
        break;
      case 3:
        // 3. Aumentar stock
        aumentarStock();
        break;
      case 4:
        // 4. Salir
        repeat = false;
        system("CLS");
        break;
      default:
        cout << "Estas fuera del rango\n";
      }
    }
  }
}

// Menu de opciones de gestionar usuarios (Administrador)
vector<string> opcionesMenuGestionUsuarios = {"Registrar usuario",
                                              "Modificar usuario",
                                              "Eliminar usuario",
                                              "Leer usuarios",
                                              "Retroceder"};
int numGestionUsuarios = opcionesMenuGestionUsuarios.size();

void menu_opcionesGestionUsuarios()
{
  bool repeat = true;
  int opt = 1;
  while (repeat)
  {
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    // Imprimir las opciones
    for (int i = 0; i < numGestionUsuarios; i++)
    {
      color(0);
      if (i == opt - 1)
      {
        setTextColor(White);
        color(2);
        gotoxy(46, 16 + i);
        cout << "=>   ";
        gotoxy(48, 16 + i);
        cout << opcionesMenuGestionUsuarios[i] << endl;
      }
      else
      {
        gotoxy(53, 16 + i);
        cout << "   " << opcionesMenuGestionUsuarios[i] << endl;
      }
    }
    // Capturamos la entrada de usuario
    int input = _getch();

    Lista listaDeUsuarios;
    switch (input)
    {
    // Aumentar o disminuir la opcion en la que estamos
    case 72: // Flecha arriba
      opt = (opt == 1) ? numGestionUsuarios : --opt;
      break;
    case 80: // Flecha abajo
      opt = (opt == numGestionUsuarios) ? 1 : ++opt;
      break;
    // Ejecutar una de las opciones del menu
    case 13:
      switch (opt)
      {
      case 1:
      {
        // 1. Registrar usuario
        gestionUsuarios_registrarUsuario();
        break;
      }
      case 2:
        // 2. Modificar usuario
        gestionUsuario_modificarUsuario();
        break;
      case 3:
        // 3. Eliminar usuario
        break;
      case 4:
        // 4. Mostrar usuarios
        limpiarPantalla();
        setConsoleBackground(White);
        dibujarTitulo(27, 0, 2, letras);
        estructura_menu2(16, 103, 10, 27);
        listaDeUsuarios = leerUsuariosCSV("output/usuarios.csv");
        // Mostrar los usuarios cargados en la lista
        mostrarUsuarios(listaDeUsuarios);
        pausa();
        break;
      case 5:
        // 5. Salir
        repeat = false;
        system("CLS");
        break;
      default:
        cout << "Estas fuera del rango\n";
      }
    }
  }
}

// Menu de opciones de gestionar pedidos (Administrador)
vector<string> opcionesMenuGestionPedidos = {"Registrar pedido",
                                             "Modificar pedido",
                                             "Eliminar pedido",
                                             "Leer pedidos",
                                             "Retroceder"};
int numGestionPedidos = opcionesMenuGestionPedidos.size();

void menu_opcionesGestionPedidos()
{
  bool repeat = true;
  int opt = 1;
  while (repeat)
  {
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    // Imprimir las opciones
    for (int i = 0; i < numGestionPedidos; i++)
    {
      color(0);
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 16 + i);
        cout << "=>   ";
        gotoxy(48, 16 + i);
        cout << opcionesMenuGestionPedidos[i] << endl;
      }
      else
      {
        gotoxy(53, 16 + i);
        cout << "   " << opcionesMenuGestionPedidos[i] << endl;
      }
    }
    // Capturamos la entrada de usuario
    int input = _getch();

    switch (input)
    {
    // Aumentar o disminuir la opcion en la que estamos
    case 72: // Flecha arriba
      opt = (opt == 1) ? numGestionPedidos : --opt;
      break;
    case 80: // Flecha abajo
      opt = (opt == numGestionPedidos) ? 1 : ++opt;
      break;
    // Ejecutar una de las opciones del menu
    case 13:
      switch (opt)
      {
      case 1:
      {
        // 1. Registrar pedido

        break;
      }
      case 2:
        // 2. Modificar pedido
        break;
      case 3:
        // 3. Eliminar pedido
        break;
      case 4:
        // 4. Mostrar pedidos
        break;
      case 5:
        // 5. Salir
        repeat = false;
        system("CLS");
        break;
      default:
        cout << "Estas fuera del rango\n";
      }
    }
  }
}

// Menu de opciones de gestionar laptops (Administrador)
vector<string> opcionesMenuGestionLaptops = {"Visualizar Pila de Laptops",
                                             "Agregar Laptop",
                                             "Eliminar Laptop",
                                             "Restaurar Laptop",
                                             "Salir"};
int numGestionLaptops = opcionesMenuGestionLaptops.size();

// Menu de opciones de reportes (Administrador)
vector<string> opcionesVerReportes = {"Ganancias",
                                      "Historial de libros",
                                      "Estadisticas de libros",
                                      "Incidencias",
                                      "Retroceder"};
int numReportes = opcionesVerReportes.size();

void menu_opcionesReportes()
{
  bool repeat = true;
  int opt = 1;
  while (repeat)
  {
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    gotoxy(46, 12);
    color(2);
    cout << "Reportes de la biblioteca";
    gotoxy(27, 14);
    color(0);
    cout << "Bienvenido, en esta sección puede ver los reportes de la biblioteca";
    gotoxy(27, 16);
    color(0);
    cout << "Ver reportes sobre";
    // Imprimir las opciones
    for (int i = 0; i < numReportes; i++)
    {
      color(0);
      if (i == opt - 1)
      {
        color(2);
        gotoxy(52, 16 + i);
        cout << "=>   ";
        gotoxy(54, 16 + i);
        cout << opcionesVerReportes[i] << endl;
      }
      else
      {
        gotoxy(59, 16 + i);
        cout << "   " << opcionesVerReportes[i] << endl;
      }
    }
    // Capturamos la entrada de usuario
    int input = _getch();

    switch (input)
    {
    // Aumentar o disminuir la opcion en la que estamos
    case 72: // Flecha arriba
      opt = (opt == 1) ? numReportes : --opt;
      break;
    case 80: // Flecha abajo
      opt = (opt == numReportes) ? 1 : ++opt;
      break;
    case 27: // Escape
      repeat = false;
      limpiarPantalla();
      break;
    // Ejecutar una de las opciones del menu
    case 13:
      switch (opt)
      {
      case 1:
      {
        // 1. Ganancias
        mostrarVistaEstadisticasGanancias();
        break;
      }
      case 2:
        // 2. Historial de libros
        break;
      case 3:
        // 3. Estadisticas de libros
        mostrarEstadisticas();
        break;
      case 4:
        // 4. Incidencias
        mostrarReporteIncidencias();
        break;
      case 5:
        // 5. Salir
        repeat = false;
        system("CLS");
        break;
      default:
        cout << "Estas fuera del rango\n";
      }
    }
  }
}

void menu_opcionesGestionLaptops()
{
  bool repeat = true;
  int opt = 1;
  while (repeat)
  {
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    // Imprimir las opciones
    for (int i = 0; i < numGestionLaptops; i++)
    {
      color(0);
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 16 + i);
        cout << "=>   ";
        gotoxy(48, 16 + i);
        cout << opcionesMenuGestionLaptops[i] << endl;
      }
      else
      {
        gotoxy(53, 16 + i);
        cout << "   " << opcionesMenuGestionLaptops[i] << endl;
      }
    }
    // Capturamos la entrada de usuario
    int input = _getch();
    PilaLaptops *pila = new PilaLaptops();
    leerLaptopsCSV(pila, "output/laptops.csv");
    switch (input)
    {
    // Aumentar o disminuir la opcion en la que estamos
    case 72: // Flecha arriba
      opt = (opt == 1) ? numGestionLaptops : --opt;
      break;
    case 80: // Flecha abajo
      opt = (opt == numGestionLaptops) ? 1 : ++opt;
      break;
    // Ejecutar una de las opciones del menu
    case 13:

      // Variable para verificar si se ha cambiado el estado de alguna laptop
      bool laptopRestaurada = false;
      switch (opt)
      {
      case 1:
      {
        // 1. Visualizar Pila de Laptops
        mostrarPilaLaptops(pila);
        getch();
        break;
      }
      case 2:
        // 2. Agregar Laptop
        gestionLaptops_registrarLaptop();
        getch();
        break;
      case 3:
        // 3. Eliminar Laptop
        marcarLaptopFueraDeServicio(pila);
        break;
      case 4:
        // 4. Restaurar Laptop
        restaurarLaptop(pila);
        break;
      case 5:
        // 5. Salir
        repeat = false;
        system("CLS");
        break;
      default:
        cout << "Estas fuera del rango\n";
      }
    }
  }
}

// Menu de opciones de recepcionista
vector<string> opcionesMenuRecepcionista = {"Gestionar pedido de libro",
                                            "Gestionar pedido de laptop",
                                            "Registrar cliente",
                                            "Activar membresia",
                                            "Cerrar sesion"};
int numRecepcionista = opcionesMenuRecepcionista.size();

void menu_opcionesRecepcionista()
{
  bool repeat = true;
  int opt = 1;
  while (repeat)
  {
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    // Imprimir las opciones
    for (int i = 0; i < numRecepcionista; i++)
    {
      color(0);
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 15 + i);
        cout << "=>   ";
        gotoxy(48, 15 + i);
        cout << opcionesMenuRecepcionista[i] << endl;
      }
      else
      {
        gotoxy(53, 15 + i);
        cout << "   " << opcionesMenuRecepcionista[i] << endl;
      }
    }
    // Capturamos la entrada de usuario
    int input = _getch();

    switch (input)
    {
    // Aumentar o disminuir la opcion en la que estamos
    case 72: // Flecha arriba
      opt = (opt == 1) ? numRecepcionista : --opt;
      break;
    case 80: // Flecha abajo
      opt = (opt == numRecepcionista) ? 1 : ++opt;
      break;
    // Ejecutar una de las opciones del menu
    case 13:
      switch (opt)
      {
      case 1:
      {
        // 1. Gestionar pedido de libro
        limpiarPantalla();
        setConsoleBackground(White);
        dibujarTitulo(27, 0, 2, letras);
        estructura_menu2(16, 103, 10, 27);
        menu_opcionesPedido();
        break;
      }
      case 2:
        // 2. Gestionar pedido de laptop
        menu_opcionesLaptop();
        break;
      case 3:
        // 3. Registrar cliente
        menuInicio_registrarUsuario();
        break;
      case 4:
        // 4. Activar membresia
        activarMembresi();
        break;
      case 5:
        // 5. Salir
        repeat = false;
        system("CLS");
        break;
      default:
        cout << "Estas fuera del rango\n";
      }
    }
  }
}

// Menu de opciones de gestionar pedidos de laptop (Recepcionista)

vector<string> opcionesMenuLaptop = {"Visualizar Pila de Laptops",
                                     "Prestar Laptop",
                                     "Devolver Laptop",
                                     "Salir"};
int numLaptop = opcionesMenuLaptop.size();

void menu_opcionesLaptop()
{
  bool repeat = true;
  int opt = 1;
  while (repeat)
  {
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    // Imprimir las opciones
    for (int i = 0; i < numLaptop; i++)
    {
      color(0);
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 15 + i);
        cout << "=>   ";
        gotoxy(48, 15 + i);
        cout << opcionesMenuLaptop[i] << endl;
      }
      else
      {
        gotoxy(53, 15 + i);
        cout << "   " << opcionesMenuLaptop[i] << endl;
      }
    }
    // Capturamos la entrada de usuario
    int input = _getch();
    PilaLaptops *pila = new PilaLaptops();
    leerLaptopsCSV(pila, "output/laptops.csv");
    switch (input)
    {
    // Aumentar o disminuir la opcion en la que estamos
    case 72: // Flecha arriba
      opt = (opt == 1) ? numLaptop : --opt;
      break;
    case 80: // Flecha abajo
      opt = (opt == numLaptop) ? 1 : ++opt;
      break;
    // Ejecutar una de las opciones del menu
    case 13:
      switch (opt)
      {
      case 1:
      {
        // 1. Visualizar Pila de Laptops
        mostrarPilaLaptops(pila);
        getch();
        break;
      }
      case 2:
        // 2. Prestar Laptop
        prestarLaptop(pila);
        getch();
        break;
      case 3:
        // 3. Devolver Laptop
        devolverLaptop(pila);
        getch();
        break;
      case 4:
        // 6. Salir
        repeat = false;
        system("CLS");
        break;
      default:
        cout << "Estas fuera del rango\n";
      }
    }
  }
}

// Menu de opciones de cliente (Recepcionista)
vector<string> opcionesMenuCliente = {
    "Ver catalogo",
    "Realizar pedido",
    "Ver historial de pedidos",
    "Sugerencias",
    "Cerrar sesion",
};
int numCliente = opcionesMenuCliente.size();

void menu_opcionesCliente()
{
  bool repeat = true;
  int opt = 1;
  while (repeat)
  {
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    // Imprimir las opciones
    for (int i = 0; i < numCliente; i++)
    {
      color(0);
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 15 + i);
        cout << "=>   ";
        gotoxy(48, 15 + i);
        cout << opcionesMenuCliente[i] << endl;
      }
      else
      {
        gotoxy(53, 15 + i);
        cout << "   " << opcionesMenuCliente[i] << endl;
      }
    }
    // Capturamos la entrada de usuario
    int input = _getch();

    ListaDobleLibros listaDeLibros;

    switch (input)
    {
    // Aumentar o disminuir la opcion en la que estamos
    case 72: // Flecha arriba
      opt = (opt == 1) ? numCliente : --opt;
      break;
    case 80: // Flecha abajo
      opt = (opt == numCliente) ? 1 : ++opt;
      break;
    // Ejecutar una de las opciones del menu
    case 13:
      switch (opt)
      {
      case 1:
      {
        // 1. Ver catalogo
        listaDeLibros = leerLibrosDoblesCSV("output/libros.csv", true);
        mostrarLibros(listaDeLibros, true);
        break;
      }
      case 2:
        // 2. Realizar pedido
        adicionarCampoPedido(id_usuariolog);
        // adicionarCampoPedido();
        break;
      case 3:
        // 3. Ver historial de pedidos
        limpiarPantalla();
        mostrarHistorialCliente(id_usuariolog);
        break;
      case 4:
        menu_sugerencias(id_usuariolog);
        break;
      case 5:
        repeat = false;
        system("CLS");
        break;
      default:
        cout << "Estas fuera del rango\n";
      }
    }
  }
}

// Menu de opciones de gestionar pedidos de libros (Recepcionista)
vector<string> opcionesMenuGestionPedidosLibros = {"Atender pedido",
                                                   "Registrar devolucion de libro",
                                                   "Ver pedidos de cliente",
                                                   "Retroceder"};
int numGestionPedidosLibros = opcionesMenuGestionPedidosLibros.size();

void menu_opcionesPedido()
{
  bool repeat = true;
  int opt = 1;
  while (repeat)
  {
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    // Imprimir las opciones
    for (int i = 0; i < numGestionPedidosLibros; i++)
    {
      color(0);
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 15 + i);
        cout << "=>   ";
        gotoxy(48, 15 + i);
        cout << opcionesMenuGestionPedidosLibros[i] << endl;
      }
      else
      {
        gotoxy(53, 15 + i);
        cout << "   " << opcionesMenuGestionPedidosLibros[i] << endl;
      }
    }
    // Capturamos la entrada de usuario
    int input = _getch();
    switch (input)
    {
    // Aumentar o disminuir la opcion en la que estamos
    case 72: // Flecha arriba
      opt = (opt == 1) ? numGestionPedidosLibros : --opt;
      break;
    case 80: // Flecha abajo
      opt = (opt == numGestionPedidosLibros) ? 1 : ++opt;
      break;
    // Ejecutar una de las opciones del menu
    case 13:
      switch (opt)
      {
      case 1:
      {
        // 1. Atender pedido
        limpiarPantalla();
        setConsoleBackground(White);
        dibujarTitulo(27, 0, 2, letras);
        estructura_menu2(16, 103, 10, 27);
        atenderPrestamoMenu(id_usuariolog);
        getch();
        break;
      }
      case 2:
        // 2. Registrar devolucion de libro
        system("CLS");
        registrarDevolucionLibro(mora, id_usuariolog);
        getch();
        break;
      case 3:
        // 3. Ver pedidos de cliente
        limpiarPantalla();
        setConsoleBackground(White);
        dibujarTitulo(27, 0, 2, letras);
        estructura_menu2(16, 103, 10, 27);
        mostrarHistorial();
        break;
      case 4:
        // 5. Salir
        repeat = false;
        system("CLS");
        break;
      default:
        cout << "Estas fuera del rango\n";
      }
    }
  }
}

void calificar_recepcionista(int id_usuariolog)
{
  limpiarPantalla();
  setConsoleBackground(White);
  dibujarTitulo(27, 0, 2, letras);
  estructura_menu2(16, 103, 10, 27);
  gotoxy(46, 12);
  color(2);
  cout << "Calificar al recepcionista";
  gotoxy(27, 14);
  color(0);
  cout << "Bienvenido, por favor califique el servicio del último recepcionista";
  gotoxy(45, 15);
  cout << "que le atendió en la biblioteca";
  gotoxy(27, 17);
  color(0);
  cout << "Calificacion: ";
  int calificacion = 0;
  cin >> calificacion;
  if (calificacion < 0 || calificacion > 5)
  {
    gotoxy(27, 19);
    cout << "La calificacion debe estar entre 0 y 5\n";
    pausa();
    calificar_recepcionista(id_usuariolog);
  }
  else
  {
    // Guardar la calificacion
    guardarCalificacionRecepcionista(id_usuariolog, calificacion);
    gotoxy(27, 19);
    cout << "Gracias por su calificacion";
    pausa();
  }
}

void guardarCalificacionRecepcionista(int id_usuariolog, int calificacion)
{
  ListaPedidos listaPedidos = leerPedidosDesdeCSV("output/pedidos.csv");
  NodoPedidos *nodoPedidos = listaPedidos.head;
  if (&listaPedidos != NULL)
  {

    while (nodoPedidos != NULL)
    {
      if (nodoPedidos->pedido.ID_recepcionistaRecibe != -1 && nodoPedidos->pedido.evaluacion == -1 && nodoPedidos->pedido.ID_usuario == id_usuariolog)
      {
        nodoPedidos->pedido.evaluacion = calificacion;
        break;
      }
      nodoPedidos = nodoPedidos->sgte;
    }
    guardar_CSV_PedidoReferencia(listaPedidos, "output/pedidos.csv");
  }
}
