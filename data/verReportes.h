#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <locale>
#include <string>
#include <vector>
#include <ctime>
#include <filesystem>
#include <conio.h>
#include <ctime>
#include "..\menu\gotoxy.h"

using namespace std;
void filtroIncidencias(int x, int y, string &eleccion);
void escogerIncidencias(int x, int y, string &eleccion);
void mostrarDatosIncidencia(int x, int y, string tipo);
void mostrarTotalIncidencias();

void mostrarReporteIncidencias()
{
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);

    // Variable para guardar la eleccion del usuario
    string eleccion;

    gotoxy(48, 11);
    color(2);
    cout << "Reportes de incidencias";
    color(0);
    gotoxy(27, 13);
    cout << "Incidencias a mostrar: ";

    filtroIncidencias(50, 13, eleccion);
}

vector<string> tiposIncidencias = {"Libro extraviado", "Libro hurtado", "Libro robado", "Otros", "Todos", "Retroceder"};

int numIncidencias = tiposIncidencias.size();

void filtroIncidencias(int x, int y, string &eleccion)
{
    bool repeat = true;
    int opt = 1;
    while (repeat)
        {
            limpiarPantalla();
            setConsoleBackground(White);
            dibujarTitulo(27, 0, 2, letras);
            estructura_menu2(16, 103, 10, 27);
            gotoxy(48, 11);
            color(2);
            cout << "Reportes de incidencias";
            color(0);
            gotoxy(27, 13);
            cout << "Incidencias a mostrar: ";
            color(0);
            // Imprimir las opciones
            for (int i = 0; i < numIncidencias; i++)
            {
                limpiarArea(x, y + i, 50, 1);
                setTextColor(0);
                if (i == opt - 1)
                {
                    setTextColor(White);
                    color(2);
                    gotoxy(x, y + i);
                    cout << "=>   ";
                    gotoxy(x + 2, y + i);
                    cout << tiposIncidencias[i] << endl;
                }
                else
                {
                    gotoxy(x + 7, y + i);
                    cout << "   " << tiposIncidencias[i] << endl;
                }
            }
            // Capturamos la entrada de usuario
            int input = _getch();

            switch (input)
            {
            // Aumentar o disminuir la opcion en la que estamos
            case 72: // Flecha arriba
                opt = (opt == 1) ? numIncidencias : --opt;
                break;
            case 80: // Flecha abajo
                opt = (opt == numIncidencias) ? 1 : ++opt;
                break;
            // Ejecutar una de las opciones del menu
            case 13:
                switch (opt)
                {
                case 1:
                {
                    eleccion = "EXTRAVIADO";
                    mostrarDatosIncidencia(27, 21, eleccion);
                    pausa();
                    break;
                }
                case 2:
                    eleccion = "HURTO";
                    mostrarDatosIncidencia(27, 21, eleccion);
                    pausa();
                    break;
                case 3:
                    eleccion = "ROBO";
                    mostrarDatosIncidencia(27, 21, eleccion);
                    pausa();
                    break;
                case 4:
                    eleccion = "OTROS";
                    mostrarDatosIncidencia(27, 21, eleccion);
                    pausa();
                    break;
                case 5:
                    mostrarTotalIncidencias();
                    pausa();
                    break;
                case 6:
                    repeat = false;
                    system("CLS");
                    break;
                default:
                    cout << "Estas fuera del rango\n";
                }
            }
        }
}

void escogerIncidencias(int x, int y, string &eleccion)
{
    bool repeat = true;
    int opt = 1;
    while (repeat)
    {
        // Imprimir las opciones
        for (int i = 0; i < numIncidencias; i++)
        {
            limpiarArea(x, y + i, 30, 1);
            setTextColor(0);
            if (i == opt - 1)
            {
                setTextColor(White);
                color(2);
                gotoxy(x, y + i);
                cout << "=>   ";
                gotoxy(x + 2, y + i);
                cout << tiposIncidencias[i] << endl;
            }
            else
            {
                gotoxy(x + 7, y + i);
                cout << "   " << tiposIncidencias[i] << endl;
            }
        }
        // Capturamos la entrada de usuario
        int input = _getch();

        switch (input)
        {
        // Aumentar o disminuir la opcion en la que estamos
        case 72: // Flecha arriba
            opt = (opt == 1) ? numIncidencias : --opt;
            break;
        case 80: // Flecha abajo
            opt = (opt == numIncidencias) ? 1 : ++opt;
            break;
        // Ejecutar una de las opciones del menu
        case 13:
            switch (opt)
            {
            case 1:
            {
                eleccion = "EXTRAVIADO";
                repeat = false;
                break;
            }
            case 2:
                eleccion = "HURTO";
                repeat = false;
                break;
            case 3:
                eleccion = "ROBO";
                repeat = false;
                break;
            case 4:
                eleccion = "OTROS";
                repeat = false;
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

void mostrarDatosIncidencia(int x, int y, string tipo)
{
    ListaIncidencias listaIncidencias = cargarCSVtoIncidencias("output/incidencias.csv");
    NodoIncidencia *temp = listaIncidencias.head;

    int incidenciasMes = 0;
    int incidenciasMesPasado = 0;
    int incidenciasTotales = 0;

    // Obtener el me actual
    time_t now = time(0);
    tm *localTime = localtime(&now);
    int mesActual = 1 + localTime->tm_mon;
    int mesPasado = localTime->tm_mon;
    string mesActualStr = to_string(mesActual);
    string mesPasadoStr = to_string(mesPasado);

    // Contar las incidencias
    Lista *listaUsuarios = new Lista();
    listaUsuarios->cabeza = nullptr;

    while (temp != nullptr)
    {
        if (temp->incidencia.tipo == tipo)
        {
            // Contamos las incidencias totales
            incidenciasTotales++;

            // Incidencias del mes
            if (temp->incidencia.fecha.substr(2, 2) == mesActualStr)
            {
                incidenciasMes++;
            }

            // Incidencias del mes pasado
            if (temp->incidencia.fecha.substr(2, 2) == mesPasadoStr)
            {
                incidenciasMesPasado++;
            }

            // Contar las incidencias por usuario
            if (listaUsuarios->cabeza == nullptr)
            {
                Usuario nuevoUsuario;
                nuevoUsuario.ID_Usuario = to_string(temp->incidencia.id_usuario);
                nuevoUsuario.numeroCastigos = 1; // Inicializar con 1 incidencia
                Nodo *usuario = new Nodo(nuevoUsuario);
                listaUsuarios->cabeza = usuario;
            }
            else
            {
                Nodo *actual = listaUsuarios->cabeza;
                bool usuarioEncontrado = false;
                while (actual != nullptr)
                {
                    if (actual->usuario.ID_Usuario == to_string(temp->incidencia.id_usuario))
                    {
                        actual->usuario.numeroCastigos++;
                        usuarioEncontrado = true;
                        break;
                    }
                    actual = actual->siguiente;
                }
                if (!usuarioEncontrado)
                {
                    Usuario nuevoUsuario;
                    nuevoUsuario.ID_Usuario = to_string(temp->incidencia.id_usuario);
                    nuevoUsuario.numeroCastigos = 1; // Inicializar con 1 incidencia
                    Nodo *usuario = new Nodo(nuevoUsuario);
                    usuario->siguiente = listaUsuarios->cabeza;
                    listaUsuarios->cabeza = usuario;
                }
            }
        }
        temp = temp->sgte;
    }

    // Encontrar el usuario con más incidencias
    Nodo *maxIncidenciasNodo = nullptr;
    int maxIncidencias = -1;
    Nodo *actual = listaUsuarios->cabeza;
    while (actual != nullptr)
    {
        if (actual->usuario.numeroCastigos > maxIncidencias)
        {
            maxIncidencias = actual->usuario.numeroCastigos;
            maxIncidenciasNodo = actual;
        }
        actual = actual->siguiente;
    }
    limpiarArea(x, y, 65, 5);
    color(2);
    gotoxy(x, y);
    cout << "Incidencias en el "<<(char)163<<"ltimo mes: ";
    color(0);
    cout << incidenciasMes;
    color(2);
    gotoxy(x, y + 1);
    cout << "Incidencias totales: ";
    color(0);
    cout << incidenciasTotales;
    color(2);
    gotoxy(x, y + 2);
    cout << "Usuario con m"<<(char)160<<"s incidencias: ";
    color(0);
    if (maxIncidenciasNodo != nullptr)
    {
        Lista listaUsuariosCSV = leerUsuariosCSV("output/usuarios.csv");
        Nodo *usuarioMaximo = buscarUsuarioPorDNI(listaUsuariosCSV, maxIncidenciasNodo->usuario.ID_Usuario);
        cout << usuarioMaximo->usuario.nombre << " " << usuarioMaximo->usuario.apellidos;
        cout << " con " << maxIncidencias << " incidencias.";
    }
    else
    {
        cout << "No hay incidencias de este tipo";
    }
    gotoxy(x, y + 4);
    color(2);
    cout << "Variaci"<<(char)162<<"n desde el "<<(char)163<<"ltimo mes: ";
    color(0);
    float variacion = (incidenciasMes - incidenciasMesPasado);
    if (variacion > 0)
    {
        color(4);
        if (incidenciasMesPasado == 0)
        {
            cout << "+" << variacion;
        }
        else
        {
            cout << "+" << (variacion / incidenciasMesPasado) * 100 << "%";
        }
    }
    else
    {
        color(2);
        if (incidenciasMesPasado == 0)
        {
            cout << variacion;
        }
        else
        {
            cout << (variacion / incidenciasMesPasado) * 100 << "%";
        }
    }
}

// Función para dibujar una barra
void dibujarBarra(int x, int y, int altura, char simbolo, int c)
{
    for (int i = 0; i < altura; ++i)
    {
        color(c);
        gotoxy(x, y - i);
        cout << simbolo;
    }
}

void mostrarTotalIncidencias()
{
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);

    ListaIncidencias listaIncidencias = cargarCSVtoIncidencias("output/incidencias.csv");
    NodoIncidencia *temp = listaIncidencias.head;

    int incidenciaRobo = 0;
    int incidenciaHurtado = 0;
    int incidenciaExtraviado = 0;
    int incidenciaOtros = 0;

    int incidenciaRoboMes = 0;
    int incidenciaHurtadoMes = 0;
    int incidenciaExtraviadoMes = 0;
    int incidenciaOtrosMes = 0;

    // Obtener el mes actual
    time_t now = time(0);
    tm *localTime = localtime(&now);
    int mesActual = 1 + localTime->tm_mon;
    int mesPasado = localTime->tm_mon;
    string mesActualStr = to_string(mesActual);
    string mesPasadoStr = to_string(mesPasado);

    // Contar las incidencias
    while (temp != nullptr)
    {
        if (temp->incidencia.tipo == "ROBO")
        {
            incidenciaRobo++;
            if (temp->incidencia.fecha.substr(2, 2) == mesActualStr)
            {
                incidenciaRoboMes++;
            }
        }
        else if (temp->incidencia.tipo == "HURTO")
        {
            incidenciaHurtado++;
            if (temp->incidencia.fecha.substr(2, 2) == mesActualStr)
            {
                incidenciaHurtadoMes++;
            }
        }
        else if (temp->incidencia.tipo == "EXTRAVIADO")
        {
            incidenciaExtraviado++;
            if (temp->incidencia.fecha.substr(2, 2) == mesActualStr)
            {
                incidenciaExtraviadoMes++;
            }
        }
        else if (temp->incidencia.tipo == "OTROS")
        {
            incidenciaOtros++;
            if (temp->incidencia.fecha.substr(2, 2) == mesActualStr)
            {
                incidenciaOtrosMes++;
            }
        }
        temp = temp->sgte;
    }

    gotoxy(48, 11);
    color(2);
    cout << "Reportes de incidencias";
    int alturaMaxima = 10;
    bool respuestaValida = false;
    string respuesta;
    do
    {
        gotoxy(27, 13);
        color(2);
        cout << "Periodo a mostrar (T: Total, M: Mes actual): ";
        color(0);
        getline(cin, respuesta);
        if (respuesta == "T" || respuesta == "t")
        {
            respuestaValida = true;
            color(0);
            gotoxy(27, 22);
            color(0);
            cout << "Incidencias totales: ";
            cout << incidenciaRobo + incidenciaHurtado + incidenciaExtraviado + incidenciaOtros;
            gotoxy(27, 23);
            color(4);
            cout << "Incidencias de robo: ";
            cout << incidenciaRobo;
            gotoxy(27, 24);
            color(2);
            cout << "Incidencias de hurto: ";
            cout << incidenciaHurtado;
            color(1);
            gotoxy(27, 25);
            cout << "Incidencias de extrav"<<(char)161<<"o: ";
            cout << incidenciaExtraviado;
            color(5);
            gotoxy(27, 26);
            cout << "Otras incidencias: ";
            cout << incidenciaOtros;

            int alturaRobo = (float)incidenciaRobo / (incidenciaRobo + incidenciaHurtado + incidenciaExtraviado + incidenciaOtros) * alturaMaxima;
            int alturaHurtado = (float)incidenciaHurtado / (incidenciaRobo + incidenciaHurtado + incidenciaExtraviado + incidenciaOtros) * alturaMaxima;
            int alturaExtraviado = (float)incidenciaExtraviado / (incidenciaRobo + incidenciaHurtado + incidenciaExtraviado + incidenciaOtros) * alturaMaxima;
            int alturaOtros = (float)incidenciaOtros / (incidenciaRobo + incidenciaHurtado + incidenciaExtraviado + incidenciaOtros) * alturaMaxima;

            dibujarBarra(72, 26, alturaMaxima, '#', 0);
            dibujarBarra(74, 26, alturaRobo, '#', 4);
            dibujarBarra(76, 26, alturaHurtado, '#', 2);
            dibujarBarra(78, 26, alturaExtraviado, '#', 1);
            dibujarBarra(80, 26, alturaOtros, '#', 5);
            pausa();
        }
        else if (respuesta == "M" || respuesta == "m")
        {
            respuestaValida = true;
            color(0);
            gotoxy(27, 22);
            color(0);
            cout << "Incidencias en el mes actual: ";
            cout << incidenciaRoboMes + incidenciaHurtadoMes + incidenciaExtraviadoMes + incidenciaOtrosMes;
            gotoxy(27, 23);
            color(4);
            cout << "Incidencias de robo: ";
            cout << incidenciaRoboMes;
            gotoxy(27, 24);
            color(2);
            cout << "Incidencias de hurto: ";
            cout << incidenciaHurtadoMes;
            color(1);
            gotoxy(27, 25);
            cout << "Incidencias de extrav"<<(char)161<<"o: ";
            cout << incidenciaExtraviadoMes;
            color(5);
            gotoxy(27, 26);
            cout << "Otras incidencias: ";
            cout << incidenciaOtrosMes;

            int alturaRobo = (float)incidenciaRoboMes / (incidenciaRoboMes + incidenciaHurtadoMes + incidenciaExtraviadoMes + incidenciaOtrosMes) * alturaMaxima;
            int alturaHurtado = (float)incidenciaHurtadoMes / (incidenciaRoboMes + incidenciaHurtadoMes + incidenciaExtraviadoMes + incidenciaOtrosMes) * alturaMaxima;
            int alturaExtraviado = (float)incidenciaExtraviadoMes / (incidenciaRoboMes + incidenciaHurtadoMes + incidenciaExtraviadoMes + incidenciaOtrosMes) * alturaMaxima;
            int alturaOtros = (float)incidenciaOtrosMes / (incidenciaRoboMes + incidenciaHurtadoMes + incidenciaExtraviadoMes + incidenciaOtrosMes) * alturaMaxima;

            dibujarBarra(72, 26, alturaMaxima, '#', 0);
            dibujarBarra(74, 26, alturaRobo, '#', 4);
            dibujarBarra(76, 26, alturaHurtado, '#', 2);
            dibujarBarra(78, 26, alturaExtraviado, '#', 1);
            dibujarBarra(80, 26, alturaOtros, '#', 5);
            pausa();
        }
        else if (respuesta == "S" || respuesta == "s")
        {
            respuestaValida = true;
        }
        else
        {
            gotoxy(27, 14);
            color(4);
            cout << "Ingrese una opci"<<(char)162<<"n v"<<(char)160<<"lida";
            pausa();
            limpiarArea(27, 13, 50, 1);
            limpiarArea(27, 14, 50, 1);
        }

    } while (!respuestaValida);
}