#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include"..\menu\gotoxy.h"

using namespace std;

struct nodoLibro{
	string nombre_Libro, Autor,Genero;
	int Ano, Stock_Inventario, StockActual;
	float precio;
	nodoLibro *sgte;
	
	nodoLibro() : sgte(NULL) {
		//cuerpo del constructor
	}
};

void adicionarCampo(nodoLibro* &Lista){
	nodoLibro *t = new nodoLibro;
	t=Lista;
	while(t->sgte!=NULL){
		t=t->sgte;
	}
	if(Lista->sgte == NULL){
        gotoxy(36, 14);
        color(2);
		cout << "A continuacion agregue los siguientes campos para un conjunto de libros: "<<endl;
		gotoxy(36, 15);
        color(2);
		cout << "Nombre del libro : ";
	    getline(cin, Lista->nombre_Libro);
	    gotoxy(36, 16);
        color(2);
		cout << "Nombre del autor : ";
	    getline(cin, Lista->Autor);
		gotoxy(36, 17);
        color(2);
		cout << "year de publicacion: ";
		cin >> Lista->Ano;
		cin.ignore();

		gotoxy(36, 18);
        color(2);
		cout << "Genero: ";
	    getline(cin, Lista->Genero); 
		gotoxy(36, 19);
        color(2);
		cout << "Stock total en inventario: ";
		cin >> Lista->Stock_Inventario;
		gotoxy(36, 20);
        color(2);
		cout << "Stock actual disponible: ";
	    cin >> Lista->StockActual;
	    gotoxy(36, 21);
        color(2);
		cout << "Precio: ";
	    cin >> Lista->precio;
	    
	    cin.ignore();
	}else{
		nodoLibro *aux = new nodoLibro;
	
		aux->sgte = NULL;
		gotoxy(36, 14);
        color(2);
		cout << "A continuacion agregue los siguientes campos para un conjunto de libros: "<<endl;
		gotoxy(36, 15);
        color(2);
		cout << "Nombre del libro : ";
	    getline(cin, aux->nombre_Libro);
	    gotoxy(36, 16);
        color(2);
		cout << "Nombre del autor : ";
	    getline(cin, aux->Autor);
		gotoxy(36, 17);
        color(2);
		cout << "year de publicacion: ";
		cin >> aux->Ano;
		
		cin.ignore();
		gotoxy(36, 18);
        color(2);
		cout << "Genero: ";
	    getline(cin, aux->Genero); 
		gotoxy(36, 19);
        color(2);
		cout << "Stock total en inventario: ";
		cin >> aux->Stock_Inventario;
		gotoxy(36, 20);
        color(2);
		cout << "Stock actual disponible: ";
	    cin >> aux->StockActual;
	    gotoxy(36, 21);
        color(2);
		cout << "Precio: ";
	    cin >> aux->precio;
	    
	    cin.ignore();
	    
	    t->sgte = aux;
    
	}

}

void gestionLibroRegistrarLibros(){
	nodoLibro *Lista = new nodoLibro;
	nodoLibro *t = new nodoLibro;
	ofstream archivo;
	archivo.open("Libros.csv",ios::app);
	string nombre_Libro, Autor,Genero;  
	int Ano, Stock_Inventario, StockActual,op;
	float precio;
	
	do{
        system("CLS");
        estructura_menu();
        gotoxy(36, 14);
        color(2);
		cout << "Deseas adicionar un campo extra si(1)/no(2): " << endl;
		cin >> op;
		cin.ignore();
		if(op==1){
			adicionarCampo(Lista);
		}		
		
	}while(op!=2);
	
	t = Lista;
	
	do{
		archivo<<"nombre_Libro ;Autor ;Ano ;Genero ;Stock_Inventario ;StockActual ;Precio ";
		
		archivo << "\n" <<t->nombre_Libro << ";" << t->Autor << ";" << t->Ano << ";" << t->Genero << ";" << t->Stock_Inventario << ";" << t->StockActual << ";" << t->precio << "\n";
		
		int ID=1,cant = t->Stock_Inventario;
		//cout << "A continuacion agregue la cantidad de libros a registrar: "; cin >> cant;
		while(cant--){
			archivo<<"ID: " << ID++;
			archivo <<",Estado: disponible; ";//por defecto
		}
		archivo << "\n";
		if(t->sgte!=NULL){
			t=t->sgte;      
		}      
	}while(t->sgte!=NULL);
	
	archivo.close();
	
	
	
	//string linea;
	//while(getline(archivo,linea)){
		
	//}
}

