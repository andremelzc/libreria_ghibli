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

    PilaLaptops *pila = new PilaLaptops();
    leerLaptopsCSV(pila, "laptops.csv");
    mostrarPilaLaptops(pila);
    Laptop *laptop = new Laptop();
    laptop = topPilaLaptops(pila);
    cout << "ID: " << laptop->id_laptop << endl;
    cout << "Marca: " << laptop->marca << endl;
    cout << "Modelo: " << laptop->modelo << endl;
    cout << "Estado: " << laptop->estado << endl;
    cout << "Tamaño de la pila: " << sizePilaLaptops(pila) << endl;
    popPilaLaptops(pila);
    cout << "Tamaño de la pila después de eliminar un elemento: " << sizePilaLaptops(pila) << endl;
    mostrarPilaLaptops(pila);
    laptop = topPilaLaptops(pila);
    cout << "ID: " << laptop->id_laptop << endl;
    cout << "Marca: " << laptop->marca << endl;
    cout << "Modelo: " << laptop->modelo << endl;
    cout << "Estado: " << laptop->estado << endl;
    system("PAUSE");

    return 0;
}