#include <iostream>
#include "HashMap.h"

using namespace std;

int main()
{
    int capacity = 5;

    //Crear un HashMap
    HashMap<int, int> *tabla = new HashMap<int, int>(capacity);

    //Insertar elementos
    tabla->put(1,1);
    tabla->put(5,5);
    tabla->put(11,11);
    tabla->put(15,15);
    tabla->put(2,2);
    tabla->put(8,8);

    cout<< tabla->get(5) << endl;
    cout<< tabla->get(15) << endl;
    cout<< tabla->get(8) << endl;

    //Eliminar la tabla
    delete tabla;

    return 0;
}
