#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <filesystem>
#include <ctime> /*Para registrar la fecha */
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

void aumentarStock()
{
    limpiarPantalla();
    setConsoleBackground(White);
    ejecutarGradienteDoble(150);
    estructura_menu2(16, 103, 11, 26);
    dibujarTitulo(24, 0, 2, letras);
    gotoxy(50, 12);
    color(2);
    cout << "Aumentar Stock";
    gotoxy(27, 14);
    color(0);
    cout << "Para registrar el nuevo stock, por favor ingrese el ID del título: ";
    gotoxy(27, 15);
    color(2);
    cout << "ID del título: ";
    color(0);
    int idTitulo;
    cin >> idTitulo;
    cin.ignore();

    // Buscar el libro por ID
    ListaLibros listaLibros = leerLibrosCSV("output/libros.csv");
    nodoLibros *libroEncontrado = buscarLibroPorID(listaLibros, idTitulo);

    if (libroEncontrado == nullptr)
    {
        gotoxy(27, 17);
        color(4);
        cout << "No se puede aumentar el stock.";
        gotoxy(27, 18);
        color(0);
        cout << "Causa: El título ingresado no se encuentra registrado";
        gotoxy(27, 19);
        color(2);
        cout << "¿Desea registrarlo? (s/n): ";
        // Falta implementar la lógica para registrar un nuevo libro
        pausa();
        return;
    }

    gotoxy(27, 17);
    color(2);
    cout << "Título encontrado: ";
    color(0);
    cout << libroEncontrado->libro.nombre_Libro;
    gotoxy(27, 18);
    color(0);
    cout << "Stock actual: " << libroEncontrado->libro.StockActual;

    color(2);
    string respuesta;
    bool respuetaValida = false;
    do
    {
        gotoxy(27, 20);
        cout << "¿Este es el título que desea aumentar el stock? (s/n): ";
        color(0);
        getline(cin, respuesta);
        if (respuesta[0] == 's' || respuesta[0] == 'S')
        {
            respuetaValida = true;
        }
        else if (respuesta[0] == 'n' || respuesta[0] == 'N')
        {
            gotoxy(27, 21);
            color(4);
            cout << "Proceso cancelado.";
            respuetaValida = true;
            return;
        }
        else
        {
            gotoxy(27, 21);
            color(4);
            cout << "Respuesta inválida. Intente de nuevo.";
            pausa();
            limpiarArea(27, 20, 50, 1);
            limpiarArea(27, 21, 50, 1);
        }
    } while (!respuetaValida);

    // Ingresar el nuevo stock
    int nuevoStock;
    gotoxy(27, 22);
    color(2);
    cout << "Stock agregado: ";
    color(0);
    cin >> nuevoStock;
    cin.ignore();

    // Actualizar el stock en el csv
    libroEncontrado->libro.StockInventario += nuevoStock;
    libroEncontrado->libro.StockActual += nuevoStock;
    limpiarCSV("output/libros.csv");
    guardar_CSV_Libros(&listaLibros, "output/libros.csv");

    pausa();
}