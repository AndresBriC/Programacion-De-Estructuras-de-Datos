#include <iostream>
#include "Queue.h"

using namespace std;

int main()
{
    /* Crear una cola vac�a */
    Queue<int> * queue = new Queue<int>();
    std::cout << "(C) Se crea una cola  vac�a" << std::endl;

    /* Determinar si la cola est� vac�a */
    std::cout << (queue->empty() ? "(E) La cola est� vac�a" : "(E) La cola tiene elementos") << std::endl;

    /* Insertar elementos en la cola */
    for (int i = 1; i < 6; ++i) {
        queue->enqueue(i);
    }

    /* Visualizar el contenido de la cola */
    std::cout << "(L) La cola tiene los siguientes elementos:" << std::endl;
    std::cout << *queue << std::endl;

    /* Obtener tama�o de la cola */
    std::cout << "(S) Tama�o de la cola: " << queue->size() << " elementos" << std::endl;

    /* Obtener el primer elemento de la cola */
    std::cout << "(T) El primer elemento de la cola es:" << *queue->first() << std::endl;

    /* Obtener el �ltimo elemento de la cola */
    std::cout << "(U) El �ltimo elemento de la cola es:" << *queue->last() << std::endl;


    /* Eliminar un elemento de la cola */
    Node<int> * node  = queue->dequeue();
    std::cout << "(R) El nodo eliminado de la cola es:" << *node << std::endl;

    std::cout << "(D) Liberando la memoria ocupada por el nodo eliminado" << std::endl;
    delete node;

    /* Visualizar el contenido de la cola */
    std::cout << "(L) La cola tiene los siguientes elementos:" << std::endl;
    std::cout << *queue << std::endl;

    /* Vaciar la cola */
    queue->clear();
    std::cout << "(V) Se vaci� la cola"<< std::endl;

    /* Determinar si la cola est� vac�a */
    std::cout << (queue->empty() ? "(E) La cola est� vac�a" : "(E) La cola tiene elementos") << std::endl;

    /* Liberando la memoria de la cola */
    delete queue;
    std::cout << "(D) Se liber� la memoria de la cola" << std::endl;

    return 0;
}
