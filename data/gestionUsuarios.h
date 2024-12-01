#pragma once
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
void insertarFinal(Lista *lista, Usuario *usuario);
Lista leerUsuariosCSV(string nombreArchivo);
void guardar_CSV(Lista *lista, string nombreArchivo);

// Registrar usuario (vista administrador)
void gestionUsuarios_registrarUsuario()
{
    Lista *lista = new Lista();
    char respuesta[10];

    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);

    Usuario *usuario = new Usuario();
    usuario->estadoUsuario = 1;
    gotoxy(51, 12);
    color(2);
    cout << "Registro de usuario";
    color(0);
    usuario->tipo = 0;
    fflush(stdin);

    // Ingresamos tipo de usuario
    bool tipoValido = false;
    do
    {
        gotoxy(27, 14);
        color(2);
        cout << "Tipo de usuario (0: cliente, 1: recepcionista): ";
        color(0);
        cin >> usuario->tipo;
        cin.ignore();

        if (usuario->tipo != 0 && usuario->tipo != 1)
        {
            gotoxy(27, 15);
            color(4);
            cout << "Ingrese un tipo de usuario válido (0 o 1)";
            pausa();
            limpiarArea(60, 14, 50, 1);
            limpiarArea(27, 15, 70, 1);
            continue;
        }
        else
        {
            tipoValido = true;
        }
    } while (!tipoValido);

    // Ingresamos DNI
    bool dniValido = false;
    do
    {
        gotoxy(27, 15);
        color(2);
        cout << "DNI: ";
        color(0);
        getline(cin, usuario->ID_Usuario);

        try
        {
            stoi(usuario->ID_Usuario);
        }
        catch (const std::invalid_argument &e)
        {
            gotoxy(27, 16);
            color(4);
            cout << "El DNI debe ser un número";
            pausa();
            limpiarArea(31, 15, 20, 1);
            limpiarArea(27, 16, 50, 1);
            continue;
        }

        if (usuario->ID_Usuario.length() != 8)
        {
            gotoxy(27, 15);
            color(4);
            cout << "El DNI debe tener 8 digitos";
            pausa();
            limpiarArea(31, 15, 20, 1);
            limpiarArea(27, 16, 50, 1);
            continue;
        }
        else
        {
            dniValido = true;
        }
    } while (!dniValido);

    // Ingresamos nombre de usuario
    bool usuarioValido = false;
    do
    {
        gotoxy(27, 16);
        fflush(stdin);
        color(2);
        cout << "Nombre de usuario: ";
        color(0);
        getline(cin, usuario->usuario);

        if (usuario->usuario.length() < 6 || usuario->usuario.length() > 15)
        {
            gotoxy(27, 17);
            color(4);
            cout << "El nombre de usuario debe tener al menos 4 caracteres y máximo 15";
            pausa();
            limpiarArea(45, 16, 50, 1);
            limpiarArea(27, 17, 70, 1);
            continue;
        }
        else
        {
            usuarioValido = true;
        }
    } while (!usuarioValido);

    // Ingresamos contraseña
    bool contrasenaValida = false;
    do
    {
        gotoxy(27, 17);
        fflush(stdin);
        color(2);
        cout << "Contrasena: ";
        color(0);
        getline(cin, usuario->contrasena);

        if (usuario->contrasena.length() < 6 || usuario->contrasena.length() > 15)
        {
            gotoxy(27, 18);
            color(4);
            cout << "La contraseña debe tener al menos 6 caracteres y máximo 15";
            pausa();
            limpiarArea(40, 17, 50, 1);
            limpiarArea(27, 18, 70, 1);
            continue;
        }
        else
        {
            contrasenaValida = true;
        }
    } while (!contrasenaValida);

    // Ingresamos nombres
    bool nombreValido = false;
    do
    {
        gotoxy(27, 18);
        fflush(stdin);
        color(2);
        cout << "Nombres: ";
        color(0);
        getline(cin, usuario->nombre);

        if (esSoloLetras(usuario->nombre) == false)
        {
            gotoxy(27, 19);
            color(4);
            cout << "Ingrese nombres válidos";
            pausa();
            limpiarArea(36, 18, 65, 1);
            limpiarArea(27, 19, 70, 1);
            continue;
        }
        else

            if (usuario->nombre.length() < 3 || usuario->nombre.length() > 30)
        {
            gotoxy(27, 19);
            color(4);
            cout << "Ingrese nombres válido";
            pausa();
            limpiarArea(36, 18, 65, 1);
            limpiarArea(27, 19, 70, 1);
            continue;
        }
        else
        {
            nombreValido = true;
        }
    } while (!nombreValido);

    // Ingresamos apellidos
    bool apellidosValidos = false;
    do
    {
        gotoxy(27, 19);
        fflush(stdin);
        color(2);
        cout << "Apellidos: ";
        color(0);
        getline(cin, usuario->apellidos);

        if (esSoloLetras(usuario->apellidos) == false)
        {
            gotoxy(27, 20);
            color(4);
            cout << "Ingrese apellidos válido";
            pausa();
            limpiarArea(36, 19, 65, 1);
            limpiarArea(27, 20, 70, 1);
            continue;
        }
        else

            if (usuario->apellidos.length() < 3 || usuario->apellidos.length() > 30)
        {
            gotoxy(27, 19);
            color(4);
            cout << "Ingrese apellidos válido";
            pausa();
            limpiarArea(36, 19, 65, 1);
            limpiarArea(27, 20, 70, 1);
            continue;
        }
        else
        {
            apellidosValidos = true;
        }
    } while (!apellidosValidos);

    // Ingresamos género
    bool generoValido = false;
    do
    {
        gotoxy(27, 20);
        fflush(stdin);
        color(2);
        cout << "Sexo (F = femenino o M = masculino): ";
        color(0);
        cin >> usuario->genero;
        // Lo pasamos a mayúsculas
        usuario->genero = toupper(usuario->genero);

        if (usuario->genero != 'F' && usuario->genero != 'M')
        {
            gotoxy(27, 21);
            color(4);
            cout << "Ingrese un género válido (F o M)";
            pausa();
            limpiarArea(47, 20, 50, 1);
            limpiarArea(27, 21, 70, 1);
            continue;
        }
        else
        {
            generoValido = true;
        }
    } while (!generoValido);

    // Ingresamos correo electrónico
    bool correoValido = false;
    do
    {
        gotoxy(27, 21);
        fflush(stdin);
        color(2);
        cout << "Correo electronico: ";
        color(0);
        cin.ignore();
        getline(cin, usuario->correoElectronico);

        if (esCorreoValido(usuario->correoElectronico) == false)
        {
            gotoxy(27, 22);
            color(4);
            cout << "Ingrese un correo válido";
            pausa();
            limpiarArea(45, 21, 50, 1);
            limpiarArea(27, 22, 70, 1);
            continue;
        }
        else
        {
            correoValido = true;
        }
    } while (!correoValido);

    // Ingresamos número de teléfono
    bool telefonoValido = false;
    do
    {
        gotoxy(27, 22);
        fflush(stdin);
        color(2);
        cout << "Número celular (9 digitos): ";
        color(0);
        getline(cin, usuario->telefono);

        try
        {
            stoi(usuario->telefono);
        }
        catch (const std::invalid_argument &e)
        {
            gotoxy(27, 23);
            color(4);
            cout << "Ingrese un número de teléfono válido";
            pausa();
            limpiarArea(45, 22, 50, 1);
            limpiarArea(27, 23, 70, 1);
            continue;
        }

        if (usuario->telefono.length() != 9)
        {
            gotoxy(27, 23);
            color(4);
            cout << "Ingrese un número de teléfono válido";
            pausa();
            limpiarArea(45, 22, 50, 1);
            limpiarArea(27, 23, 70, 1);
            continue;
        }
        else
        {
            telefonoValido = true;
        }
    } while (!telefonoValido);

    if (usuario->tipo == 0)
    {
        usuario->membresia = "INACTIVA";
    }
    else
    {
        usuario->membresia = "ACTIVA";
    }

    usuario->fechaInicio = "00/00/0000";
    usuario->fechaFinal = "00/00/0000";
    usuario->librosPrestados = 0;

    insertarFinal(lista, usuario);

    color(2);
    dibujarTextoPuntos(27, 24, "Registrando usuario");
    gotoxy(36, 24);
    cout << "Usuario registrado con exito!";
    pausa();

    guardar_CSV(lista, "output/usuarios.csv");
}

// Registrar usuario (vista recepcionista y cliente)
void menuInicio_registrarUsuario()
{
    Lista *lista = new Lista();
    char respuesta[10];

    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);

    Usuario *usuario = new Usuario();
    usuario->estadoUsuario = 1;
    gotoxy(51, 12);
    color(2);
    cout << "Registro de usuario";
    color(0);
    usuario->tipo = 0;
    fflush(stdin);

    // Ingresamos DNI
    bool dniValido = false;
    do
    {
        gotoxy(27, 14);
        color(2);
        cout << "DNI: ";
        color(0);
        getline(cin, usuario->ID_Usuario);

        try
        {
            stoi(usuario->ID_Usuario);
        }
        catch (const std::invalid_argument &e)
        {
            gotoxy(27, 15);
            color(4);
            cout << "El DNI debe ser un número";
            pausa();
            limpiarArea(31, 14, 20, 1);
            limpiarArea(27, 15, 50, 1);
            continue;
        }

        if (usuario->ID_Usuario.length() != 8)
        {
            gotoxy(27, 15);
            color(4);
            cout << "El DNI debe tener 8 digitos";
            pausa();
            limpiarArea(31, 14, 20, 1);
            limpiarArea(27, 15, 50, 1);
            continue;
        }
        else
        {
            dniValido = true;
        }
    } while (!dniValido);

    // Ingresamos nombre de usuario
    bool usuarioValido = false;
    do
    {
        gotoxy(27, 15);
        fflush(stdin);
        color(2);
        cout << "Nombre de usuario: ";
        color(0);
        getline(cin, usuario->usuario);

        if (usuario->usuario.length() < 6 || usuario->usuario.length() > 15)
        {
            gotoxy(27, 16);
            color(4);
            cout << "El nombre de usuario debe tener al menos 4 caracteres y máximo 15";
            pausa();
            limpiarArea(45, 15, 50, 1);
            limpiarArea(27, 16, 70, 1);
            continue;
        }
        else
        {
            usuarioValido = true;
        }
    } while (!usuarioValido);

    // Ingresamos contraseña
    bool contrasenaValida = false;
    do
    {
        gotoxy(27, 16);
        fflush(stdin);
        color(2);
        cout << "Contrasena: ";
        color(0);
        getline(cin, usuario->contrasena);

        if (usuario->contrasena.length() < 6 || usuario->contrasena.length() > 15)
        {
            gotoxy(27, 17);
            color(4);
            cout << "La contraseña debe tener al menos 6 caracteres y máximo 15";
            pausa();
            limpiarArea(40, 16, 50, 1);
            limpiarArea(27, 17, 70, 1);
            continue;
        }
        else
        {
            contrasenaValida = true;
        }
    } while (!contrasenaValida);

    // Ingresamos nombres
    bool nombreValido = false;
    do
    {
        gotoxy(27, 17);
        fflush(stdin);
        color(2);
        cout << "Nombres: ";
        color(0);
        getline(cin, usuario->nombre);

        if (esSoloLetras(usuario->nombre) == false)
        {
            gotoxy(27, 18);
            color(4);
            cout << "Ingrese nombres válidos";
            pausa();
            limpiarArea(36, 17, 65, 1);
            limpiarArea(27, 18, 70, 1);
            continue;
        }
        else

            if (usuario->nombre.length() < 3 || usuario->nombre.length() > 30)
        {
            gotoxy(27, 18);
            color(4);
            cout << "Ingrese nombres válido";
            pausa();
            limpiarArea(36, 17, 65, 1);
            limpiarArea(27, 18, 70, 1);
            continue;
        }
        else
        {
            nombreValido = true;
        }
    } while (!nombreValido);

    // Ingresamos apellidos
    bool apellidosValidos = false;
    do
    {
        gotoxy(27, 18);
        fflush(stdin);
        color(2);
        cout << "Apellidos: ";
        color(0);
        getline(cin, usuario->apellidos);

        if (esSoloLetras(usuario->apellidos) == false)
        {
            gotoxy(27, 19);
            color(4);
            cout << "Ingrese apellidos válido";
            pausa();
            limpiarArea(36, 18, 65, 1);
            limpiarArea(27, 19, 70, 1);
            continue;
        }
        else

            if (usuario->apellidos.length() < 3 || usuario->apellidos.length() > 30)
        {
            gotoxy(27, 19);
            color(4);
            cout << "Ingrese apellidos válido";
            pausa();
            limpiarArea(36, 18, 65, 1);
            limpiarArea(27, 19, 70, 1);
            continue;
        }
        else
        {
            apellidosValidos = true;
        }
    } while (!apellidosValidos);

    // Ingresamos género
    bool generoValido = false;
    do
    {
        gotoxy(27, 19);
        fflush(stdin);
        color(2);
        cout << "Sexo (F = femenino o M = masculino): ";
        color(0);
        cin >> usuario->genero;
        // Lo pasamos a mayúsculas
        usuario->genero = toupper(usuario->genero);

        if (usuario->genero != 'F' && usuario->genero != 'M')
        {
            gotoxy(27, 20);
            color(4);
            cout << "Ingrese un género válido (F o M)";
            pausa();
            limpiarArea(47, 19, 50, 1);
            limpiarArea(27, 20, 70, 1);
            continue;
        }
        else
        {
            generoValido = true;
        }
    } while (!generoValido);

    // Ingresamos correo electrónico
    bool correoValido = false;
    do
    {
        gotoxy(27, 20);
        fflush(stdin);
        color(2);
        cout << "Correo electronico: ";
        color(0);
        cin.ignore();
        getline(cin, usuario->correoElectronico);

        if (esCorreoValido(usuario->correoElectronico) == false)
        {
            gotoxy(27, 21);
            color(4);
            cout << "Ingrese un correo válido";
            pausa();
            limpiarArea(45, 20, 50, 1);
            limpiarArea(27, 21, 70, 1);
            continue;
        }
        else
        {
            correoValido = true;
        }
    } while (!correoValido);

    // Ingresamos número de teléfono
    bool telefonoValido = false;
    do
    {
        gotoxy(27, 21);
        fflush(stdin);
        color(2);
        cout << "Número celular (9 digitos): ";
        color(0);
        getline(cin, usuario->telefono);

        try
        {
            stoi(usuario->telefono);
        }
        catch (const std::invalid_argument &e)
        {
            gotoxy(27, 22);
            color(4);
            cout << "Ingrese un número de teléfono válido";
            pausa();
            limpiarArea(45, 21, 50, 1);
            limpiarArea(27, 22, 70, 1);
            continue;
        }

        if (usuario->telefono.length() != 9)
        {
            gotoxy(27, 22);
            color(4);
            cout << "Ingrese un número de teléfono válido";
            pausa();
            limpiarArea(45, 21, 50, 1);
            limpiarArea(27, 22, 70, 1);
            continue;
        }
        else
        {
            telefonoValido = true;
        }
    } while (!telefonoValido);

    insertarFinal(lista, usuario);

    color(2);
    dibujarTextoPuntos(27, 24, "Registrando usuario");
    gotoxy(36, 24);
    cout << "Usuario registrado con exito!";
    pausa();

    guardar_CSV(lista, "output/usuarios.csv");
}

// Insertar un usuario al final de la lista enlazada
void insertarFinal(Lista *lista, Usuario *usuario)
{
    Nodo *nodo = new Nodo(*usuario);

    if (lista->cabeza == nullptr)
    {
        lista->cabeza = nodo;
    }
    else
    {
        Nodo *puntero = lista->cabeza;
        while (puntero->siguiente)
        {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nodo;
    }
    lista->longitud++;
}

// Guardar una lista en el csv
void guardar_CSV(Lista *lista, string nombreArchivo)
{
    fstream archivo(nombreArchivo, ios::out | ios::app);

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo. " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        system("PAUSE");
        return;
    }

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    // Recorre la lista enlazada y escribe cada nodo en el archivo
    Nodo *actual = lista->cabeza;
    while (actual != nullptr)
    {
        // cout << "estoy datos en el archivo .csv";
        // system("PAUSE");
        Usuario usuario = actual->usuario;

        archivo << usuario.estadoUsuario << "," << usuario.tipo << "," << usuario.ID_Usuario << "," << usuario.usuario << "," << usuario.contrasena << "," << usuario.nombre << "," << usuario.apellidos << "," << usuario.genero << ","
                << usuario.correoElectronico << "," << usuario.telefono << "," << usuario.membresia << "," << usuario.librosPrestados << "," << usuario.fechaInicio << "," << usuario.fechaFinal << "\n";

        actual = actual->siguiente;
    }

    archivo.close();
    // cout << "Datos guardados en " << nombreArchivo << endl;
}

// Mostrar usuarios
void mostrarUsuarios(Lista &lista)
{
    Nodo *actual = lista.cabeza;
    int contador = 0;
    gotoxy(50, 12);
    color(2);
    cout << "Lista de usuarios";
    gotoxy(20, 14);
    cout << "ID";
    gotoxy(33, 14);
    cout << "Nombre";
    gotoxy(54, 14);
    cout << "Apellidos";
    gotoxy(74, 14);
    cout << "Usuario";
    color(0);
    while (actual != nullptr)
    {

        gotoxy(20, 16 + contador);
        cout << actual->usuario.ID_Usuario;
        gotoxy(33, 16 + contador);
        cout << actual->usuario.nombre;
        gotoxy(54, 16 + contador);
        cout << actual->usuario.apellidos;
        gotoxy(74, 16 + contador);
        cout << actual->usuario.usuario;

        actual = actual->siguiente;
        contador++;
    }
}

// Modificar datos de usuario
void gestionUsuario_modificarUsuario()
{
    string dni;
    string respuesta;
    int opcion;

    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    color(2);
    gotoxy(52, 12);
    cout << "Modificando Usuario";
    gotoxy(36, 14);
    cout << "DNI del usuario: ";
    color(0);
    fflush(stdin);
    getline(cin, dni);

    Lista listaUsuarios;
    listaUsuarios = leerUsuariosCSV("output/usuarios.csv");

    Nodo *actual = listaUsuarios.cabeza;

    // Iteramos la lista
    while (actual != nullptr)
    {
        string respuesta;
        // Encontramos el dni del usuario ingresado
        if (actual->usuario.ID_Usuario == dni)
        {
            gotoxy(36, 16);
            color(2);
            cout << "Usuario encontrado: ";
            color(0);
            cout << actual->usuario.nombre << " " << actual->usuario.apellidos << endl;
            gotoxy(36, 17);
            color(2);
            cout << "Desea modificar datos de este usuario? (s/n): ";
            color(0);
            fflush(stdin);
            getline(cin, respuesta);
            cout << respuesta;
            if (respuesta == "s" || respuesta == "S")
            {
                limpiarPantalla();
                setConsoleBackground(White);
                dibujarTitulo(27, 0, 2, letras);
                estructura_menu2(16, 103, 10, 27);
                color(2);
                gotoxy(52, 12);
                cout << "Modificando Usuario";
                gotoxy(36, 14);
                cout << "Que campo desea modificar?";
                gotoxy(36, 15);
                color(0);
                cout << "1. Estado";
                gotoxy(50, 15);
                cout << "2. Tipo";
                gotoxy(64, 15);
                cout << "3. DNI";
                gotoxy(78, 15);
                cout << "4. Usuario";
                gotoxy(36, 16);
                cout << "5. Contraseña";
                gotoxy(50, 16);
                cout << "6. Nombre";
                gotoxy(64, 16);
                cout << "7. Apellido";
                gotoxy(78, 16);
                cout << "8. Género";
                gotoxy(36, 17);
                cout << "9. Correo";
                gotoxy(50, 17);
                cout << "10. Teléfono";
                gotoxy(36, 18);
                color(2);
                cout << "--> ";
                color(0);
                cin >> opcion;
                cin.ignore();

                // Datos para ingresar
                int datoInt;
                string datoString;

                switch (opcion)
                {
                case 1:
                    // Modificar estado
                    gotoxy(36, 20);
                    color(2);
                    cout << "Antiguo estado: ";
                    gotoxy(52, 20);
                    color(0);
                    cout << actual->usuario.estadoUsuario;
                    gotoxy(36, 21);
                    color(2);
                    cout << "Nuevo estado (0: desactivado, 1: activado): ";
                    color(0);
                    fflush(stdin);
                    cin >> datoInt;
                    cin.ignore();
                    fflush(stdin);
                    actual->usuario.estadoUsuario = datoInt;
                    break;
                case 2:
                    // Modificar tipo
                    gotoxy(36, 20);
                    color(2);
                    cout << "Antiguo tipo: ";
                    gotoxy(50, 20);
                    color(0);
                    cout << actual->usuario.tipo;
                    gotoxy(36, 21);
                    color(2);
                    cout << "Nuevo tipo (0, 1, 2): ";
                    color(0);
                    fflush(stdin);
                    cin >> datoInt;
                    cin.ignore();
                    fflush(stdin);
                    actual->usuario.tipo = datoInt;
                    break;
                case 3:
                    // Modificar DNI
                    gotoxy(36, 20);
                    color(2);
                    cout << "Antiguo DNI: ";
                    gotoxy(49, 20);
                    color(0);
                    cout << actual->usuario.ID_Usuario;
                    gotoxy(36, 21);
                    color(2);
                    cout << "Nuevo DNI: ";
                    color(0);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.ID_Usuario = datoString;
                    break;
                case 4:
                    // Modificar usuario
                    gotoxy(36, 20);
                    color(2);
                    cout << "Antiguo usuario: ";
                    gotoxy(54, 20);
                    color(0);
                    cout << actual->usuario.usuario;
                    gotoxy(36, 21);
                    color(2);
                    cout << "Nuevo usuario: ";
                    color(0);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.usuario = datoString;
                    break;
                case 5:
                    // Modificar contraseña
                    gotoxy(36, 20);
                    color(2);
                    cout << "Antigua contraseña: ";
                    gotoxy(58, 20);
                    color(0);
                    cout << actual->usuario.contrasena;
                    gotoxy(36, 21);
                    cout << "Nueva contraseña: ";
                    color(0);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.contrasena = datoString;
                    break;
                case 6:
                    // Modificar nombre
                    gotoxy(36, 20);
                    color(2);
                    cout << "Antiguo nombre: ";
                    gotoxy(52, 20);
                    color(0);
                    cout << actual->usuario.nombre;
                    gotoxy(36, 21);
                    color(2);
                    cout << "Nuevo nombre: ";
                    color(0);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.nombre = datoString;
                    break;
                case 7:
                    // Modificar apellido
                    gotoxy(36, 20);
                    color(2);
                    cout << "Antiguo apellido: ";
                    gotoxy(54, 20);
                    color(0);
                    cout << actual->usuario.apellidos;
                    gotoxy(36, 21);
                    color(2);
                    cout << "Nuevo apellido: ";
                    color(0);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.apellidos = datoString;
                    break;
                case 8:
                    // Modificar género
                    gotoxy(36, 20);
                    color(2);
                    cout << "Antiguo género: ";
                    gotoxy(53, 20);
                    color(0);
                    cout << actual->usuario.genero;
                    gotoxy(36, 21);
                    color(2);
                    cout << "Nuevo género: ";
                    color(0);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.genero = datoString[0];
                    break;
                case 9:
                    // Modificar correo
                    gotoxy(36, 20);
                    color(2);
                    cout << "Antiguo correo: ";
                    gotoxy(52, 20);
                    color(0);
                    cout << actual->usuario.correoElectronico;
                    gotoxy(36, 21);
                    color(2);
                    cout << "Nuevo correo: ";
                    color(0);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.correoElectronico = datoString;
                    break;
                case 10:
                    // Modificar teléfono
                    gotoxy(36, 20);
                    color(2);
                    cout << "Antiguo teléfono: ";
                    gotoxy(55, 20);
                    color(0);
                    cout << actual->usuario.telefono;
                    gotoxy(36, 21);
                    color(2);
                    cout << "Nuevo teléfono: ";
                    color(0);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.telefono = datoString;
                    break;
                }
            }
            else
            {
                gotoxy(36, 19);
                cout << "Modifiación cancelada";
            }
        }
        actual = actual->siguiente;
    }

    limpiarCSV("output/usuarios.csv");
    guardar_CSV(&listaUsuarios, "output/usuarios.csv");

    gotoxy(36, 23);
    color(2);
    cout << "Modificación realizada con éxito";
    system("pause>0");
}

// Activar membresia
void activarMembresi()
{
    string dni;

    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);
    gotoxy(52, 12);
    color(2);
    cout << "Activando membresia";
    gotoxy(36, 14);
    cout << "DNI del usuario: ";
    color(0);
    getline(cin, dni);

    Lista listaUsuarios;
    listaUsuarios = leerUsuariosCSV("output/usuarios.csv");

    Nodo *actual = listaUsuarios.cabeza;

    while (actual != nullptr)
    {
        string respuesta;
        if (actual->usuario.ID_Usuario == dni)
        {
            gotoxy(36, 16);
            color(2);
            cout << "Usuario encontrado: ";
            color(0);
            cout << actual->usuario.nombre << " " << actual->usuario.apellidos << endl;
            gotoxy(36, 17);
            color(2);
            cout << "Desea activar la membresia? (s/n): ";
            color(0);
            fflush(stdin);
            getline(cin, respuesta);
            cout << respuesta;
            if (respuesta == "s" || respuesta == "S")
            {
                string fecha;
                actual->usuario.membresia = "ACTIVA";
                time_t t = time(0);
                tm *localTime = localtime(&t);
                // Fecha de inicio
                string diaStr = to_string(localTime->tm_mday);
                string mesStr = to_string(localTime->tm_mon + 1);
                string añoStr = to_string(localTime->tm_year + 1900);
                fecha = diaStr + "/" + mesStr + "/" + añoStr;
                actual->usuario.fechaInicio = fecha;
                // Fecha de fin
                añoStr = to_string(localTime->tm_year + 1901);
                fecha = diaStr + "/" + mesStr + "/" + añoStr;
                actual->usuario.fechaFinal = fecha;
                color(2);
                dibujarTextoPuntos(36, 19, "Activando membresia");
                gotoxy(36, 19);
                cout << "Membresia activada correctamente!";
            }
            else
            {
                gotoxy(36, 19);
                cout << "Membresia no activada";
            }
        }
        actual = actual->siguiente;
    }
    limpiarCSV("output/usuarios.csv");
    guardar_CSV(&listaUsuarios, "output/usuarios.csv");

    system("pause>0");
}

// Insertar para crear la lista enlazada
void insertar(Lista &lista, Usuario nuevoUsuario)
{
    Nodo *nuevoNodo = new Nodo(nuevoUsuario);
    nuevoNodo->siguiente = lista.cabeza;
    lista.cabeza = nuevoNodo;
    lista.longitud++;
}

// Función para crear una lista enlazada en base a los datos del csv
Lista leerUsuariosCSV(string nombreArchivo)
{
    Lista listaDeUsuarios;

    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo. " << nombreArchivo << endl;
        perror("Error al abrir el archivo");
        system("PAUSE");
        return listaDeUsuarios;
    }

    if (archivo.is_open())
    {
        // Leer el archivo línea por línea
        while (getline(archivo, linea))
        {
            stringstream ss(linea);
            string dato;

            Usuario usuario;

            // Suponiendo que el CSV tiene los campos en el siguiente orden:
            // estado, tipo, id_usuario (dni), usuario, contrasena, nombre, apellidos, genero, correo electronico, telefono, membresia, libros prestados, fecha inicio, fecha fin,
            getline(ss, dato, ',');
            usuario.estadoUsuario = stoi(dato); // Convertir a entero

            getline(ss, dato, ',');
            usuario.tipo = stoi(dato); // Convertir a entero

            getline(ss, usuario.ID_Usuario, ',');
            getline(ss, usuario.usuario, ',');
            getline(ss, usuario.contrasena, ',');
            getline(ss, usuario.nombre, ',');
            getline(ss, usuario.apellidos, ',');

            getline(ss, dato, ',');
            usuario.genero = dato[0]; // Solo tomar el primer carácter

            getline(ss, usuario.correoElectronico, ',');
            getline(ss, usuario.telefono, ',');

            getline(ss, usuario.membresia, ',');

            getline(ss, dato, ',');
            usuario.librosPrestados = stoi(dato); // Convertir a entero

            getline(ss, usuario.fechaInicio, ',');
            getline(ss, usuario.fechaFinal, ',');

            // Insertar el usuario en la lista enlazada
            insertarFinal(&listaDeUsuarios, &usuario);
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
    return listaDeUsuarios;
}

// Función para actualizar estado de membresia
void actualizarMembresiaUsuarios()
{
    Lista listaUsuarios;
    listaUsuarios = leerUsuariosCSV("output/usuarios.csv");

    Nodo *actual = listaUsuarios.cabeza;
    time_t t = time(0);
    tm *localTime = localtime(&t);
    string fecha;
    string diaStr = to_string(localTime->tm_mday);
    string mesStr = to_string(localTime->tm_mon + 1);
    string añoStr = to_string(localTime->tm_year + 1900);
    fecha = diaStr + "/" + mesStr + "/" + añoStr;

    while (actual != nullptr)
    {
        if (actual->usuario.membresia == "ACTIVA")
        {
            if (actual->usuario.fechaFinal == fecha)
            {
                actual->usuario.membresia = "INACTIVA";
                actual->usuario.fechaInicio = "00/00/0000";
                actual->usuario.fechaFinal = "00/00/0000";
            }
        }
        actual = actual->siguiente;
    }
    limpiarCSV("output/usuarios.csv");
    guardar_CSV(&listaUsuarios, "output/usuarios.csv");
}

// Muestra un usuario al ingresar su DNI
bool mostrarUsuarioXDNI(Lista &listaUsuarios, const string &dni)
{
    Nodo *actual = listaUsuarios.cabeza; // Apuntar al primer nodo de la lista

    // Recorrer la lista buscando el usuario con el DNI indicado
    while (actual != nullptr)
    {
        if (actual->usuario.ID_Usuario == dni)
        { // Si el DNI del usuario coincide
            // Mostrar los datos del usuario
            gotoxy(36, 16);
            color(2);
            cout << "1. Nombre: ";
            color(0);
            cout << actual->usuario.nombre;
            gotoxy(36, 17);
            color(2);
            cout << "2. Apellidos: ";
            color(0);
            cout << actual->usuario.apellidos;
            gotoxy(36, 18);
            color(2);
            cout << "3. Genero: ";
            color(0);
            cout << actual->usuario.genero;
            gotoxy(36, 19);
            color(2);
            cout << "4. Correo Electronico: ";
            color(0);
            cout << actual->usuario.correoElectronico;
            gotoxy(36, 20);
            color(2);
            cout << "5. Telefono: ";
            color(0);
            cout << actual->usuario.telefono;
            gotoxy(36, 21);
            color(2);
            cout << "6. Usuario: ";
            color(0);
            cout << actual->usuario.usuario;
            gotoxy(36, 22);
            color(2);
            cout << "7. Estado: ";
            color(0);
            cout << (actual->usuario.estadoUsuario == 1 ? "Activo" : "Inactivo");
            gotoxy(36, 23);
            color(2);
            cout << "8. Membresia: ";
            color(0);
            cout << (actual->usuario.membresia == "1" ? "Activa" : "Inactiva");
            gotoxy(36, 24);
            color(2);
            cout << "9. Libros Prestados: ";
            color(0);
            cout << actual->usuario.librosPrestados;
            return true; // Retorna true si el usuario fue encontrado
            break;
        }
        actual = actual->siguiente; // Mover al siguiente nodo
    }

    // Si el usuario no fue encontrado
    cout << "No se encontro ningun usuario con el DNI: " << dni << endl;
    return false; // Retorna false si no encontró el usuario
}

// Función para buscar un usuario por DNI
Nodo *buscarUsuarioPorDNI(Lista &listaUsuarios, const string &dni)
{
    Nodo *actual = listaUsuarios.cabeza;
    while (actual != nullptr)
    {
        if (actual->usuario.ID_Usuario == dni)
        {
            return actual; // Usuario encontrado
        }
        actual = actual->siguiente;
    }
    return nullptr; // Usuario no encontrado
}