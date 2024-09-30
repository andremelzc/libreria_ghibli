#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

struct nodoLibro {
    string nombre_Libro, Autor, Genero;
    int Ano, Stock_Inventario, StockActual;
    float precio;
    nodoLibro* sgte;
    
    nodoLibro() : sgte(NULL) {}
};

void adicionarCampo(nodoLibro*& Lista) {
    nodoLibro* aux = new nodoLibro;

    // Capturar datos del nuevo libro
    cout << "A continuacion agregue los siguientes campos para un conjunto de libros: " << endl;
    cout << "Nombre del libro : "; getline(cin, aux->nombre_Libro);
    cout << "Nombre del autor : "; getline(cin, aux->Autor);
    cout << "Year de publicacion: "; cin >> aux->Ano;
    cin.ignore();
    cout << "Genero: "; getline(cin, aux->Genero);
    cout << "Stock total en inventario: "; cin >> aux->Stock_Inventario;
    cout << "Stock actual disponible: "; cin >> aux->StockActual;
    cout << "Precio: "; cin >> aux->precio;
    cin.ignore();
    
    aux->sgte = NULL;  // Asegurarse de que el nuevo nodo no apunte a nada

    if (Lista == NULL) {
        // Si la lista está vacía, el nuevo nodo es el primero
        Lista = aux;
    } else {
        // Si la lista no está vacía, encontrar el último nodo y agregar el nuevo nodo
        nodoLibro* temp = Lista;
        while (temp->sgte != NULL) {
            temp = temp->sgte;
        }
        temp->sgte = aux;
    }
}

void guardarLibros(nodoLibro* Lista) {
    ofstream archivo("Libros.csv", ios::app);

    nodoLibro* temp = Lista;
    
    // Encabezados CSV
    archivo << "nombre_Libro;Autor;Ano;Genero;Stock_Inventario;StockActual;Precio\n";
    
    while (temp != NULL) {
        archivo << temp->nombre_Libro << ";" << temp->Autor << ";" << temp->Ano << ";"
                << temp->Genero << ";" << temp->Stock_Inventario << ";" 
                << temp->StockActual << ";" << temp->precio << "\n";
        
        int ID = 1;
        for (int i = 0; i < temp->Stock_Inventario; i++) {
            archivo << "ID: " << ID++ << ",Estado: disponible;\n";
        }
        
        temp = temp->sgte;
    }
    
    archivo.close();
}

int main() {
    nodoLibro* Lista = NULL;  // Inicializar la lista como vacía
    int op;
    
    do {
        cout << "Deseas adicionar un campo extra si(1)/no(2): " << endl;
        cin >> op;
        cin.ignore();
        if (op == 1) {
            adicionarCampo(Lista);  // Agregar un nuevo libro
        }
    } while (op != 2);
    
    guardarLibros(Lista);  // Guardar los libros en el archivo CSV
    
    return 0;
}
