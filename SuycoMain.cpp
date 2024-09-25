#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>

//Headers
#include "menu/gotoxy.h"
#include "menu/menus.h"
#include "servicio/crudRecepcionista.cpp"
#include "data/persistenciaUsuario.h"
using namespace std;

int main() {
    Lista listaDeUsuarios;
    
    // Leer el archivo CSV
    leerCSV("usuarios.csv", listaDeUsuarios);
    
    // Mostrar los usuarios cargados en la lista
    listaDeUsuarios.mostrar();

    return 0;
}