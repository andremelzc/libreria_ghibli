#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>


//Headers
#include "menu/gotoxy.h"
#include "menu/menus.h"

using namespace std;

int main() {
    system("CLS");
    estructura_menu();
    menu_opcionesPrincipal();
    gotoxy(100,36);
    return 0;
}