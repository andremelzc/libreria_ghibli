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
    int stock = contarTituloLibro("output/libros.csv", "Circe");
    cout << "Stock: " << stock << endl;
    
    return 0;
}