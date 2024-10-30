#include <windows.h>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

#include "hola.h"

int main() {
    ejecutarGradiente(300);
    dibujarLibreria(32, 5);
    dibujarLetras(23, 14);
    dibujarPresionaTecla(24, 22);
    system("pause>0");
    ejecutarGradienteDoble(300);
    dibujarLetras(23, 2);
    system("pause>0");
    return 0;
}
