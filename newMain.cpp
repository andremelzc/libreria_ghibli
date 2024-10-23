#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <filesystem>

using namespace std;

int main() {
    filesystem::path current_path = filesystem::current_path();

    // Imprimir el directorio de trabajo
    cout << "Directorio de trabajo: " << current_path << endl;
   


    return 0;
}