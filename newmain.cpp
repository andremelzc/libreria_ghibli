#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>

//Headers
#include "menu/gotoxy.h"
#include "menu/menus.h"
#include "servicio/crudRecepcionista.cpp"
using namespace std;

int main() {
    system("CLS");
    //estructura_menu();
    //menu_opcionesPrincipal();
    //menu_opcionesAdministrador();->NO descomentar
    //gotoxy(100,36);
    //agregarPersonaAlCSV();
    //cout<<"El numero de elementos es: "<<contarFilasCSV()<<endl;
    string nUsuario;
    do{
        cout<<"Ingrese el nombre de Usuario a Buscar: "<<endl;
        cin>>nUsuario;
        if(nUsuario.compare("salir") == 0){
            break;
        }
        if(verificarUsuarioEnCSV(nUsuario)){
            cout<<"Usuario Encontrado"<<endl;
        }else{
            cout<<"Usuario No Enconstrado"<<endl;
        }
    }while(true);
    

    getch();
    return 0;
}