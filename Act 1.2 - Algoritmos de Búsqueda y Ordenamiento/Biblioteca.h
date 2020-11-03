#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#include <string>

using namespace std;

class Biblioteca{
    private:
        string nombre;
        int cantidadLibros;

    public:
        void agregarLibro();
        void eliminarLibro();
        Libro busquedaPreAnio(int anio);
        Libro busquedaPostAnio(int anio);
        LibrobusquedaRango(int anioInf, int anioSup);
        Libro busquedaAutor(string autor);
        Libro busquedaEditorial(string editorial);
        Libro ordenaYMuestra(string criterio, string algoritmo, string direccion);

};

#endif // BIBLIOTECA_H_INCLUDED
