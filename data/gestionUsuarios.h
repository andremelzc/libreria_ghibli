#pragma once
#include "persistenciaUsuario.h"
#include "../menu/gotoxy.h"
#include <string.h>
#include <fstream>

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
        gotoxy(36, 10);
        cout << "Ingrese el tipo del usuario (2, 1 o 0): ";
        cin >> usuario->tipo;
        gotoxy(36, 11);
        cout << "Ingrese el ID del usuario (DNI): ";
        cin.ignore();
        getline(cin, usuario->ID_Usuario);
        gotoxy(36, 12);
        cout << "Ingrese el nombre de usuario: ";
        cin.ignore();
        getline(cin, usuario->usuario);
        gotoxy(36, 13);
        cout << "Ingrese la contrasena: ";
        getline(cin, usuario->contrasena);
        gotoxy(36, 14);
        cout << "Ingrese el nombre: ";
        getline(cin, usuario->nombre);
        gotoxy(36, 15);
        cout << "Ingrese los apellidos: ";
        getline(cin, usuario->apellidos);
        gotoxy(36, 16);
        cout << "Ingrese el genero (F o M): ";
        cin >> usuario->genero;
        gotoxy(36, 17);
        cout << "Ingrese el correo electronico: ";
        cin.ignore();
        getline(cin, usuario->correoElectronico);
        gotoxy(36, 18);
        cout << "Ingrese el telefono (9 digitos): ";
        getline(cin, usuario->telefono);
    
        insertarFinal(lista, usuario);
        gotoxy(36, 20);
        cout << "¿Desea registrar otro usuario? (s/n): ";
        cin >> respuesta;

    } while (respuesta[0] == 's' || respuesta[0] == 'S');

    guardar_CSV(lista, "usuarios.csv");
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
