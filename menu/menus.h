#pragma once
#include "../servicio/funcionalidades.h"
#include "../data/persistenciaDatos.h"
#include "../data/gestionUsuarios.h"
#include "gotoxy.h"
#include "../data/gestionLibros.h"
#include "../servicio/iniciarSesion.h"
#include "../data/gestionLaptops.h"
#include "../data/prestamoLibro.h"

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

void menu_opcionesPrincipal()
{
  bool repeat = true;
  int opt = 1;
  estructura_menu();
  while (repeat)
  {
    system("CLS");
    estructura_menu();
    // Imprimir las opciones
    for (int i = 0; i < numInicio; i++)
    {
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 16 + i);
        cout << "=>   ";
        color(7);
        gotoxy(48, 16 + i);
        color(2);
        cout << opcionesMenuPrincipal[i] << endl;
        color(7);
      }
      else
      {
        gotoxy(53, 16 + i);
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
        listaDeLibros = leerLibrosDoblesCSV("libros.csv");
        mostrarLibros(listaDeLibros);
        break;
      }
      case 2:
        // 2. Registrar cuenta
        estructura_menu();
        menuInicio_registrarUsuario();
        break;
      case 3:
        // 3. Iniciar sesión
        int tipo;
        bool sesion;
        inicioSesion(tipo, sesion);
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
            menu_opcionesCliente();
          }
        }
        system("pause>0");
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
                                            "Ver estadisticas",
                                            "Salir"};
int numAdmin = opcionesMenuAdministrador.size();

void menu_opcionesGestionLibros();   // Declaración previa
void menu_opcionesGestionUsuarios(); // Declaración previa
void menu_opcionesGestionPedidos();  // Declaración previa

void menu_opcionesAdministrador()
{
  bool repeat = true;
  int opt = 1;
  estructura_menu();
  while (repeat)
  {
    system("CLS");
    estructura_menu();
    // Imprimir las opciones
    for (int i = 0; i < numAdmin; i++)
    {
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 15 + i);
        cout << "=>   ";
        color(7);
        gotoxy(48, 15 + i);
        color(2);
        cout << opcionesMenuAdministrador[i] << endl;
        color(7);
      }
      else
      {
        gotoxy(53, 15 + i);
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
        menu_opcionesGestionLibros();
        break;
      }
      case 2:
        // 2. Gestionar usuarios
        menu_opcionesGestionUsuarios();
        break;
      case 3:
        // 3. Gestionar pedidos
        menu_opcionesGestionPedidos();
        break;
      case 4:
        // 4. Ver estadisticas
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

// Menu de opciones de gestionar libros (Administrador)
vector<string> opcionesMenuGestionLibros = {"Registrar libro",
                                            "Modificar libro",
                                            "Aumentar stock",
                                            "Eliminar libro",
                                            "Salir"};
int numGestionLibros = opcionesMenuGestionLibros.size();

void menu_opcionesGestionLibros()
{
  bool repeat = true;
  int opt = 1;
  estructura_menu();
  while (repeat)
  {
    system("CLS");
    estructura_menu();
    // Imprimir las opciones
    for (int i = 0; i < numGestionLibros; i++)
    {
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 16 + i);
        cout << "=>   ";
        color(7);
        gotoxy(48, 16 + i);
        color(2);
        cout << opcionesMenuGestionLibros[i] << endl;
        color(7);
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
        break;
      case 4:
        // 4. Eliminar libro
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

// Menu de opciones de gestionar usuarios (Administrador)
vector<string> opcionesMenuGestionUsuarios = {"Registrar usuario",
                                              "Modificar usuario",
                                              "Eliminar usuario",
                                              "Leer usuarios",
                                              "Salir"};
int numGestionUsuarios = opcionesMenuGestionUsuarios.size();

void menu_opcionesGestionUsuarios()
{
  bool repeat = true;
  int opt = 1;
  estructura_menu();
  while (repeat)
  {
    system("CLS");
    estructura_menu();
    // Imprimir las opciones
    for (int i = 0; i < numGestionUsuarios; i++)
    {
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 16 + i);
        cout << "=>   ";
        color(7);
        gotoxy(48, 16 + i);
        color(2);
        cout << opcionesMenuGestionUsuarios[i] << endl;
        color(7);
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
        estructura_menu();
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
        listaDeUsuarios = leerUsuariosCSV("usuarios.csv");
        // Mostrar los usuarios cargados en la lista
        mostrarUsuarios(listaDeUsuarios);
        getch();
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
                                             "Salir"};
int numGestionPedidos = opcionesMenuGestionPedidos.size();

void menu_opcionesGestionPedidos()
{
  bool repeat = true;
  int opt = 1;
  estructura_menu();
  while (repeat)
  {
    system("CLS");
    estructura_menu();
    // Imprimir las opciones
    for (int i = 0; i < numGestionPedidos; i++)
    {
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 16 + i);
        cout << "=>   ";
        color(7);
        gotoxy(48, 16 + i);
        color(2);
        cout << opcionesMenuGestionPedidos[i] << endl;
        color(7);
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

// Menu de opciones de recepcionista
vector<string> opcionesMenuRecepcionista = {"Gestionar pedido de libro",
                                            "Gestionar pedido de laptop",
                                            "Registrar cliente",
                                            "Activar membresia",
                                            "Ver historial de cliente",
                                            "Salir"};
int numRecepcionista = opcionesMenuRecepcionista.size();

void menu_opcionesRecepcionista()
{
  bool repeat = true;
  int opt = 1;
  estructura_menu();
  while (repeat)
  {
    system("CLS");
    estructura_menu();
    // Imprimir las opciones
    for (int i = 0; i < numRecepcionista; i++)
    {
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 15 + i);
        cout << "=>   ";
        color(7);
        gotoxy(48, 15 + i);
        color(2);
        cout << opcionesMenuRecepcionista[i] << endl;
        color(7);
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
        break;
      }
      case 2:
        // 2. Gestionar pedido de laptop
        estructura_menu();
        
        gestionLaptops_registrarLaptop();
        break;
      case 3:
        // 3. Registrar cliente
        estructura_menu();
        menuInicio_registrarUsuario();
        break;
      case 4:
        // 4. Activar membresia
        activarMembresi();
        break;
      case 5:
        // 5. Ver historial de cliente
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

// Menu de opciones de cliente
vector<string> opcionesMenuCliente = {"Ver catalogo",
                                      "Realizar pedido",
                                      "Ver historial de pedidos",
                                      "Salir"};
int numCliente = opcionesMenuCliente.size();

void menu_opcionesCliente()
{
  bool repeat = true;
  int opt = 1;
  estructura_menu();
  while (repeat)
  {
    system("CLS");
    estructura_menu();
    // Imprimir las opciones
    for (int i = 0; i < numCliente; i++)
    {
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 15 + i);
        cout << "=>   ";
        color(7);
        gotoxy(48, 15 + i);
        color(2);
        cout << opcionesMenuCliente[i] << endl;
        color(7);
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
        listaDeLibros = leerLibrosDoblesCSV("libros.csv");
        mostrarLibros(listaDeLibros);
        break;
      }
      case 2:
        // 2. Realizar pedido
        adicionarCampoPedido();
        break;
      case 3:
        // 3. Ver historial de pedidos
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

