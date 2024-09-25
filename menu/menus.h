#pragma once
#include "../data/gestionUsuarios.h"
#include "gotoxy.h"
#include "../data/gestionLibros.h"

//Menu de opciones inicial
vector<string> opcionesMenuPrincipal = {"Ver catalogo",
                                        "Registrarse",
                                        "Iniciar sesion",
                                        "Salir"};
int numInicio = opcionesMenuPrincipal.size();

void menu_iniciarSesion();//Declaración Previa  -> Para el Switch caso 3

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
        break;
      }
      case 2:
        // 2. Registrar cuenta
        break;
      case 3:
        // 3. Iniciar sesión
        menu_iniciarSesion();
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

//Menu para Iniciar Sesión
vector<string> opcionesMenuIniciarSesion = {"Ingresar Nombre",
                                        "Ingresar Contrasena",
                                        "Iniciar sesion",
                                        "Salir"};
int numSesion = opcionesMenuIniciarSesion.size();

void menu_iniciarSesion()
{
  bool repeat = true;
  int opt = 1;
  estructura_menu();
  while (repeat)
  {
    system("CLS");
    estructura_menu();
    // Imprimir las opciones
    for (int i = 0; i < numSesion; i++)
    {
      if (i == opt - 1)
      {
        color(2);
        gotoxy(46, 16 + i);
        cout << "=>   ";
        color(7);
        gotoxy(48, 16 + i);
        color(2);
        cout << opcionesMenuIniciarSesion[i] << endl;
        color(7);
      }
      else
      {
        gotoxy(53, 16 + i);
        cout << "   " << opcionesMenuIniciarSesion[i] << endl;
      }
    }
    // Capturamos la entrada de usuario
    int input = _getch();

    switch (input)
    {
    // Aumentar o disminuir la opcion en la que estamos
    case 72: // Flecha arriba
      opt = (opt == 1) ? numSesion : --opt;
      break;
    case 80: // Flecha abajo
      opt = (opt == numSesion) ? 1 : ++opt;
      break;
    // Ejecutar una de las opciones del menu
    case 13:
      switch (opt)
      {
      case 1:
      {
        // 1. Ingresar Nombre
        break;
      }
      case 2:
        // 2. Ingresar Contraseña
        break;
      case 3:
        // 3. Iniciar sesión
        // menu_iniciarSesion();
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

//Menu de opciones administrador
vector<string> opcionesMenuAdministrador = {"Gestionar libros",
                                        "Gestionar usuarios",
                                        "Gestionar pedidos",
                                        "Ver estadisticas",
                                        "Salir"};
int numAdmin = opcionesMenuAdministrador.size();

void menu_opcionesGestionLibros(); // Declaración previa
void menu_opcionesGestionUsuarios(); // Declaración previa  

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

//Menu de opciones de gestionar libros
vector<string> opcionesMenuGestionLibros = {"Registrar libro",
                                        "Modificar libro",
                                        "Aumentar stock",
                                        "Eliminar libro",
                                        "Salir"};
int numGestionLibros = opcionesMenuGestionLibros.size();

void menu_opcionesGestionLibros(){
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
        estructura_menu();
        gestionLibroRegistrarLibros();
        break;
      }
      case 2:
        // 2. Modificar libro
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

//Menu de opciones de gestionar usuarios
vector<string> opcionesMenuGestionUsuarios = {"Registrar usuario",
                                        "Modificar usuario",
                                        "Eliminar usuario",
                                        "Leer usuarios",
                                        "Salir"};
int numGestionUsuarios = opcionesMenuGestionUsuarios.size();

void menu_opcionesGestionUsuarios(){
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
        break;
      case 3:
        // 3. Eliminar usuario
        break;
      case 4:
        // 4. Mostrar usuarios
        
        leerCSV("usuarios.csv", listaDeUsuarios);
        // Mostrar los usuarios cargados en la lista
        mostrar(listaDeUsuarios);
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