#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include "data/persistenciaDatos.h"
#include "servicio/funcionalidades.h"

using namespace std;

int main() {
    if(tituloGuardado("output/libros.csv", 3, "Circe")){
        cout << "El libro se encuentra en la base de datos" << endl;
    } else {
        cout << "El libro no se encuentra en la base de datos" << endl;
    }
    
    return 0;
}