#include "Libro.h"

using namespace std;

Libro::Libro(){
    titulo = "";
    autor = "";
    numPaginas = 0;
    editorial = "";
    edicion = 0;
    anioPublicacion = 0;
}

//Accesors
string Libro::getTitulo(){
    return titulo;
}

string Libro::getAutor(){
    return autor;
}

int Libro::getNumPaginas(){
    return numPaginas;
}

string Libro::getEditorial(){
    return editorial;
}

int Libro::getEdicion(){
    return edicion;
}

int Libro::getAnioPublicacion(){
    return anioPublicacion;
}

//Mutators
void Libro::setTitulo(string titulo){
    this->titulo = titulo;
}

void Libro::setAutor(string autor){
    this->autor = autor;
}

void Libro::setNumPag(int numPag){
    numPaginas = numPag;
}

void Libro::setEditorial(string editorial){
    this->editorial = editorial;
}

void Libro::setEdicion(int edicion){
    this->edicion = edicion;
}

void Libro::setAnioPublicacion(int anio){
    anioPublicacion = anio;
}

