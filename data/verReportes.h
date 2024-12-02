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
#include "..\menu\gotoxy.h"

using namespace std;
void filtroIncidencias(int x, int y, int &eleccion);

void mostrarReporteIncidencias()
{
    limpiarPantalla();
    setConsoleBackground(White);
    dibujarTitulo(27, 0, 2, letras);
    estructura_menu2(16, 103, 10, 27);

    // Variable para guardar la eleccion del usuario
    int eleccion = -1;

    gotoxy(46, 11);
    color(2);
    cout << "Reportes de incidencias";
    color(0);
    gotoxy(27, 13);
    cout << "Incidencias a mostrar: ";

    filtroIncidencias(50, 13, eleccion);
}

vector<string> tiposIncidencias = {"Libro extraviado", "Libro dañado", "Libro no devuelto", "Todos"};

int numIncidencias = tiposIncidencias.size();

void filtroIncidencias(int x, int y, int &eleccion)
{
    bool repeat = true;
    int opt = 1;
    while (repeat)
    {
        // Imprimir las opciones
        for (int i = 0; i < numIncidencias; i++)
        {
            limpiarArea(x, y + i, 50, 5);
            setTextColor(0);
            if (i == opt - 1)
            {
                setTextColor(White);
                color(2);
                gotoxy(x, y + i);
                cout << "=>   ";
                gotoxy(x+2, y + i);
                cout << tiposIncidencias[i] << endl;
            }
            else
            {
                gotoxy(x+7, y + i);
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
                eleccion = 1;
                break;
            }
            case 2:
                eleccion = 2;
                break;
            case 3:
                eleccion = 3;
                break;
            case 4:
                eleccion = 4;
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