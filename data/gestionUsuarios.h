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

using namespace std;

void gestionUsuarios_registrarUsuario();
void insertarFinal(Lista *lista, Usuario *usuario);

void gestionUsuarios_registrarUsuario()
{
    Lista *lista = new Lista();
    char respuesta[10];
    do
    {
        system("CLS");
        estructura_menu();
        Usuario *usuario = new Usuario();
        usuario->estadoUsuario = 1;
        gotoxy(51, 12);
        color(2);
        cout << "Registro de usuario";
        color(7);
        gotoxy(36, 14);
        color(2);
        cout << "Tipo del usuario (2, 1 o 0): ";
        color(7);
        cin >> usuario->tipo;
        gotoxy(36, 15);
        color(2);
        cout << "DNI: ";
        color(7);
        cin.ignore();
        getline(cin, usuario->ID_Usuario);
        gotoxy(36, 16);
        color(2);
        cout << "Nombre de usuario: ";
        color(7);
        getline(cin, usuario->usuario);
        gotoxy(36, 17);
        color(2);
        cout << "Contrasena: ";
        color(7);
        getline(cin, usuario->contrasena);
        gotoxy(36, 18);
        color(2);
        cout << "Nombres: ";
        color(7);
        getline(cin, usuario->nombre);
        gotoxy(36, 19);
        color(2);
        cout << "Apellidos: ";
        color(7);
        getline(cin, usuario->apellidos);
        gotoxy(36, 20);
        color(2);
        cout << "Sexo (F = femenino o M = masculino): ";
        color(7);
        cin >> usuario->genero;
        gotoxy(36, 21);
        color(2);
        cout << "Correo electronico: ";
        color(7);
        cin.ignore();
        getline(cin, usuario->correoElectronico);
        gotoxy(36, 22);
        color(2);
        cout << "Número celular (9 digitos): ";
        color(7);
        getline(cin, usuario->telefono);

        insertarFinal(lista, usuario);
        gotoxy(36, 24);
        color(2);
        cout << "Desea registrar otro usuario? (s/n): ";
        color(7);
        cin >> respuesta;

    } while (respuesta[0] == 's' || respuesta[0] == 'S');

    guardar_CSV(lista, "output/usuarios.csv");
}

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

// Leo y Muestro Todos los Registros del CSV
void sleerUsuariosCSV()
{
    ifstream archivo("usuarios.csv");
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo de Usuarios " << endl;
        system("PAUSE");
        cout << "\nTamos Cagaos, no podemos ni leer" << endl;
        return;
    }
    int posicionFila;
    int filaInicial = 4;

    int gotoX;
    string linea;
    while (getline(archivo, linea))
    {

        posicionFila = 0; // Usado para determinar el Tipo de dato que estoy Tratando
        gotoX = 4;
        stringstream ss(linea);
        string valor;
        while (getline(ss, valor, ','))
        {

            switch (posicionFila)
            {
            case 0:                         // X mismo para la categoria - Y cambia pues son las Filas
                gotoxy(gotoX, filaInicial); // estado
                gotoX = gotoX + 4;
                cout << valor;
                break;
            case 1:
                gotoxy(gotoX, filaInicial); // tipo empleado
                gotoX = gotoX + 4;
                cout << valor;
                break;
            case 2:
                gotoxy(gotoX, filaInicial); // dni
                gotoX = gotoX + 11;
                cout << valor;
                break;
            case 3:
                gotoxy(gotoX, filaInicial); // usuario
                gotoX = gotoX + 14;
                cout << valor;
                break;
            case 4:
                gotoxy(gotoX, filaInicial); // contraseña
                gotoX = gotoX + 12;
                cout << valor;
                break;
            case 5:
                gotoxy(gotoX, filaInicial); // nombre
                gotoX = gotoX + 15;
                cout << valor;
                break;
            case 6:
                gotoxy(gotoX, filaInicial); // apellido
                gotoX = gotoX + 15;
                cout << valor;
                break;
            case 7:
                gotoxy(gotoX, filaInicial); // genero
                gotoX = gotoX + 4;
                cout << valor;
                break;
            case 8:
                gotoxy(gotoX, filaInicial); // gmail
                gotoX = gotoX + 20;
                cout << valor;
                break;
            case 9:
                gotoxy(gotoX, filaInicial); // telefono
                gotoX = gotoX + 15;
                cout << valor;
                break;
            }

            posicionFila++;
        }
        filaInicial++; // Cambia para la siguiente fila
        // cout << endl;  // Imprimir salto de línea al final de cada registro
    }
    cout << endl;
    archivo.close();
}

// Función para dividir una cadena en base a un delimitador
vector<string> dividir(const string &cadena, char delimitador)
{
    vector<string> resultado;
    stringstream ss(cadena);
    string valor;

    while (getline(ss, valor, delimitador))
    {
        resultado.push_back(valor);
    }
    return resultado;
}

// Función para modificar un registro en el archivo CSV sin archivo temporal
void modificarRegistroCSV(const string &nombreArchivo, int idModificar)
{
    ifstream archivoEntrada(nombreArchivo); // Abrimos el archivo original en modo lectura

    // Verificación de la apertura del archivo
    if (!archivoEntrada.is_open())
    {
        cerr << "No se pudo abrir el archivo CSV al inicio de la modificación" << endl;
        return;
    }

    vector<string> contenidoArchivo; // Vector para almacenar el contenido completo del archivo
    string linea;
    bool encontrado = false;

    // Lectura del archivo CSV original
    while (getline(archivoEntrada, linea))
    {
        contenidoArchivo.push_back(linea); // Guardamos cada línea en el vector
    }
    archivoEntrada.close(); // Cerramos el archivo tras la lectura

    // Búsqueda y modificación del registro
    for (auto &registro : contenidoArchivo)
    {
        vector<string> campos = dividir(registro, ',');

        // Si el ID del registro coincide con el ID a modificar
        if (convertirCadenaAEntero(campos[2]) == idModificar)
        { // Ajusta según la posición del ID en tu CSV
            encontrado = true;
            int opcion;
            string nuevoValor;

            cout << "Registro encontrado: " << registro << endl;
            cout << "¿Qué campo deseas modificar?" << endl;
            cout << "1. Estado \n2. Tipo\n3. DNI\n4. Usuario\n5. Contraseña\n6. Nombre\n7. Apellido\n8. Género\n9. Correo\n10. Teléfono\n";
            cin >> opcion;
            cin.ignore(); // Limpieza del buffer de entrada
            cout << endl;

            cout << "Introduce el nuevo valor: " << endl;
            getline(cin, nuevoValor);

            // Validación de la opción seleccionada
            if (opcion >= 1 && opcion <= 10)
            {
                campos[opcion - 1] = nuevoValor; // Modificación del campo seleccionado
            }
            else
            {
                cout << "Opción no válida." << endl;
                return;
            }

            // Reensamblamos la línea modificada
            stringstream ss;
            for (size_t i = 0; i < campos.size(); ++i)
            {
                ss << campos[i];
                if (i != campos.size() - 1)
                    ss << ",";
            }
            registro = ss.str(); // Actualizamos el registro en el vector
            break;
        }
    }

    // Reescribimos todo el contenido del archivo
    ofstream archivoSalida(nombreArchivo); // Abrimos el archivo en modo escritura para sobrescribirlo

    if (!archivoSalida.is_open())
    {
        cerr << "No se pudo abrir el archivo CSV para escritura." << endl;
        return;
    }

    // Escribimos todo el contenido (modificado o no) de vuelta en el archivo
    for (const auto &linea : contenidoArchivo)
    {
        archivoSalida << linea << endl;
    }

    archivoSalida.close(); // Cerramos el archivo de salida

    if (encontrado)
    {
        cout << "Registro modificado correctamente." << endl;
    }
    else
    {
        cout << "No se encontró el registro con el ID: " << idModificar << endl;
    }
}

void gestionUsuario_modificarUsuario()
{
    string dni;
    string respuesta;
    int opcion;

    system("CLS");
    estructura_menu();
    color(2);
    gotoxy(52, 12);
    cout << "Modificando Usuario";
    gotoxy(36, 14);
    cout << "DNI del usuario: ";
    color(7);
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
            color(7);
            cout << actual->usuario.nombre << " " << actual->usuario.apellidos << endl;
            gotoxy(36, 17);
            color(2);
            cout << "Desea modificar datos de este usuario? (s/n): ";
            color(7);
            fflush(stdin);
            getline(cin, respuesta);
            cout << respuesta;
            if (respuesta == "s" || respuesta == "S")
            {
                system("CLS");
                estructura_menu();
                color(2);
                gotoxy(52, 12);
                cout << "Modificando Usuario";
                gotoxy(36, 14);
                cout << "Que campo desea modificar?";
                gotoxy(36, 15);
                color(7);
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
                color(7);
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
                    cout << "Nuevo estado (0: desactivado, 1: activado): ";
                    color(7);
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
                    cout << "Nuevo tipo (0, 1, 2): ";
                    color(7);
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
                    cout << "Nuevo DNI: ";
                    color(7);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.ID_Usuario = datoString;
                    break;
                case 4:
                    // Modificar usuario
                    gotoxy(36, 20);
                    color(2);
                    cout << "Nuevo usuario: ";
                    color(7);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.usuario = datoString;
                    break;
                case 5:
                    // Modificar contraseña
                    gotoxy(36, 20);
                    color(2);
                    cout << "Nueva contraseña: ";
                    color(7);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.contrasena = datoString;
                    break;
                case 6:
                    // Modificar nombre
                    gotoxy(36, 20);
                    color(2);
                    cout << "Nuevo nombre: ";
                    color(7);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.nombre = datoString;
                    break;
                case 7:
                    // Modificar apellido
                    gotoxy(36, 20);
                    color(2);
                    cout << "Nuevo apellido: ";
                    color(7);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.apellidos = datoString;
                    break;
                case 8:
                    // Modificar género
                    gotoxy(36, 20);
                    color(2);
                    cout << "Nuevo género: ";
                    color(7);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.genero = datoString[0];
                    break;
                case 9:
                    // Modificar correo
                    gotoxy(36, 20);
                    color(2);
                    cout << "Nuevo correo: ";
                    color(7);
                    fflush(stdin);
                    getline(cin, datoString);
                    actual->usuario.correoElectronico = datoString;
                    break;
                case 10:
                    // Modificar teléfono
                    gotoxy(36, 20);
                    color(2);
                    cout << "Nuevo teléfono: ";
                    color(7);
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

    gotoxy(36, 22);
    color(2);
    cout << "Modificación realizada con éxito";
    system("pause>0");
}

// Activar membresia
void activarMembresi()
{
    string dni;

    system("CLS");
    estructura_menu();
    gotoxy(52, 12);
    color(2);
    cout << "Activando membresia";
    gotoxy(36, 14);
    cout << "DNI del usuario: ";
    color(7);
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
            color(7);
            cout << actual->usuario.nombre << " " << actual->usuario.apellidos << endl;
            gotoxy(36, 17);
            color(2);
            cout << "Desea activar la membresia? (s/n): ";
            color(7);
            fflush(stdin);
            getline(cin, respuesta);
            cout << respuesta;
            if (respuesta == "s" || respuesta == "S")
            {
                actual->usuario.membresia = "ACTIVA";
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