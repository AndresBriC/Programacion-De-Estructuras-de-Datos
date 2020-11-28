//
//  main.cpp
//  HashMap
//
//  Created by inigo guerra on 23/11/20.
//

#include <iostream>
#include "HashMap.cpp"
#include "HashMapChain.cpp"

int main(int argc, const char * argv[]) {

    int capacity = 5;

    /* Crear un HashMap */
    HashMap<int, int> * tabla = new HashMap<int, int>(capacity);

    /* Insertar elementos */
    tabla->put(1, 1);
    tabla->put(5, 5);
    tabla->put(11, 11);
    tabla->put(15, 15);
    tabla->put(2, 2);
    tabla->put(8, 8);

    std::cout << tabla->get(5) << std::endl;
    std::cout << tabla->get(15) << std::endl;
    std::cout << tabla->get(8) << std::endl;

    /* Eliminar la tabla */
    delete tabla;

    capacity = 5;

    /* Crear un HashMap */
    HashMapChain<int, int> * tablaChain = new HashMapChain<int, int>(capacity);

    /* Insertar elementos */
    tablaChain->put(1, 1);
    tablaChain->put(5, 5);
    tablaChain->put(11, 11);
    tablaChain->put(15, 15);
    tablaChain->put(2, 2);
    tablaChain->put(8, 8);
    tablaChain->put(33, 33);
    tablaChain->put(10, 10);

    std::cout << tablaChain->get(5) << std::endl;
    std::cout << tablaChain->get(15) << std::endl;
    std::cout << tablaChain->get(8) << std::endl;
    std::cout << tablaChain->get(33) << std::endl;
    std::cout << tablaChain->get(10) << std::endl;


    /* Eliminar la tabla */
    delete tablaChain;

    return 0;
}
