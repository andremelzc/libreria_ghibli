#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include"..\menu\gotoxy.h"
#include "persistenciaUsuario.h"
using namespace std;

struct Libro{
	string nombre_Libro, Autor,Genero,estado;
	int Ano, Stock_Inventario, StockActual;
	float precio;
};
struct nodoLibros{
	Libro libro;
	nodoLibros *siguiente;
	nodoLibros(Libro libro1):libro(libro1),siguiente(nullptr){}
};
struct ListaLibros
{
    nodoLibros *cabeza;
    int longitud;  
    ListaLibros() : cabeza(nullptr) {} // Inicializar cabeza a nullptr
};

void insertarFinalListaLibro(ListaLibros *lista, Libro *libro)
{
    nodoLibros *nodoLibro = new nodoLibros (*libro);

    if (lista->cabeza == nullptr)
    {
        lista->cabeza = nodoLibro;
    }
    else
    {
        nodoLibros *puntero = lista->cabeza;
        while (puntero->siguiente)
        {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nodoLibro;
    }
    lista->longitud++;
}
void guardar_CSV_Libros(ListaLibros *lista,string nombreArchivo){
	fstream archivo(nombreArchivo, fstream::out | fstream::app);

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    // Recorre la lista enlazada y escribe cada nodo en el archivo
    nodoLibros *actual = lista->cabeza;
    while (actual != nullptr)
    {
        Libro libro = actual->libro;
        archivo << libro.nombre_Libro << ","
                << libro.Autor << ","
                << libro.Ano << ","
                << libro.Genero << ","
				<< libro.Stock_Inventario << ","
				<< libro.StockActual << ","
				<< libro.precio << ","
                << libro.estado << "\n";

        actual = actual->siguiente;
    }

    archivo.close();
    cout << "Datos guardados en " << nombreArchivo << endl;
}
void adicionarCampo(){
	ListaLibros *listaLibros = new ListaLibros();
	char respuesta[10];
	do{
		system("CLS");
        estructura_menu();
		Libro *libro = new Libro();
		libro->estado="Disponible";
		cin.ignore();
		gotoxy(36, 14);
        color(2);
		cout << "A continuacion agregue los siguientes campos para un conjunto de libros: "<<endl;
		gotoxy(36, 15);
        color(2);
		cout << "Nombre del libro : ";
	    getline(cin, libro->nombre_Libro);
		cin.ignore();
	    gotoxy(36, 16);
        color(2);
		cout << "Nombre del autor : ";
	    getline(cin, libro->Autor);
		gotoxy(36, 17);
        color(2);
		cout << "year de publicacion: ";
		cin >> libro->Ano;
		cin.ignore();
		gotoxy(36, 18);
        color(2);
		cout << "Genero: ";
	    getline(cin, libro->Genero); 
		gotoxy(36, 19);
        color(2);
		cout << "Stock total en inventario: ";
		cin >> libro->Stock_Inventario;
		gotoxy(36, 20);
        color(2);
		cout << "Stock actual disponible: ";
	    cin >> libro->StockActual;
	    gotoxy(36, 21);
        color(2);
		cout << "Precio: ";
	    cin >> libro->precio;
	    cin.ignore();

		insertarFinalListaLibro(listaLibros,libro);

		gotoxy(36, 24);
        color(2);
        cout << "Desea registrar otro usuario? (s/n): ";
        color(7);
        cin >> respuesta;
	}while(respuesta[0] =='s'||respuesta[0] =='S');

	guardar_CSV_Libros(listaLibros, "Libros.csv");
}

