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
    ListaPedidos listaPedidos;
    listaPedidos=leerPedidosDesdeCSV("pedidos.csv");
    /*ListaLibros listalibros;
    listalibros = leerLibrosCSV("Libros.csv");*/
    /*Lista listaUsuarios;
    listaUsuarios = leerUsuariosCSV("usuarios.csv");*/
    cout<<"GAAAAAA";
    cout<<"PERRRRRRRRRRRRRA"<<endl;

    // Ejemplo de cómo usar la función 'convertirFecha'
Pedidos pedido;

// Suponiendo que 'campo' contiene la fecha en formato string como "16/10/2024"
string campo = "16/10/2024";
pedido.fechaPedido = convertirFecha(campo);

// Mostrar la fecha para verificar
cout << "Dia: " << pedido.fechaPedido.dia << endl;
cout << "Mes: " << pedido.fechaPedido.mes << endl;
cout << "Ano: " << pedido.fechaPedido.año << endl;
   


    return 0;
}