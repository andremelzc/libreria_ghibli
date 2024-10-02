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
