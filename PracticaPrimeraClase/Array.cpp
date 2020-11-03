#include <iostream>
#include "Array.h"

    int obtener(int index);{
        if (index >= 0 & index < longitud){
            return datos(index);
        }
        else{
            return -1;
        }
    }
    int longitud();{
        return longitud;
    }
    bool lleno();{
        return longitud == MAX;
    }
    int eliminar();{
        //Por implementar
    }
    void insertar(int item);{
        //Por implementar
    }
