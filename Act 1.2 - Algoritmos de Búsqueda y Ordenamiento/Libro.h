#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED

#include <string>

using namespace std;

class Libro{
private:
    string titulo;
    string autor;
    int numPaginas;
    string editorial;
    int edicion;
    int anioPublicacion;

public:
    //Constructor
    Libro();

    //Accesors
    string getTitulo();
    string getAutor();
    int getNumPaginas();
    string getEditorial();
    int getEdicion();
    int getAnioPublicacion();

    //Mutators
    void setTitulo(string titulo);
    void setAutor(string autor);
    void setNumPag(int numPag);
    void setEditorial(string editorial);
    void setEdicion(int edicion);
    void setAnioPublicacion(int anio);

};

#endif // LIBRO_H_INCLUDED
