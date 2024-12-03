#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>

// Headers
#include "menu/gotoxy.h"
#include "menu/menus.h"

using namespace std;

int main()
{
    // Inicio

    levantarCastigoUsuarios();
    actualizarMembresiaUsuarios();
    ejecutarGradiente(300);
    dibujarTitulo(32, 5, 1, libros);
    dibujarTitulo(24, 14, 2, letras);
    dibujarPresionaTecla(24, 23);
    ocultarCursor();
    pausa();
    // Menú de inicio
    ejecutarGradienteDoble(150);
    dibujarTitulo(24, 0, 2, letras);
    ocultarCursor();
    estructura_menu2(16, 103, 11, 26);
    menu_opcionesPrincipal();


    return 0;
}