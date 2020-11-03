#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#define MAX 50

class Array
{
private:
    int datos(MAX);
    int longitud = 0;

public:
    int obtener(int index);
    int longitud();
    bool lleno();
    int eliminar();
    void insertar(int item);
};

#endif // ARRAY_H_INCLUDED
