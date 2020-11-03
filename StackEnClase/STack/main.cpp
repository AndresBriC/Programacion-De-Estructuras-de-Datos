#include <iostream>

#include "Stack.h"

using namespace std;

int main()
{
    /* Crear una pila vac�a */
    Stack<int> * stack = new Stack<int>();
    std::cout << "(C) Se crea una pila  vac�a" << std::endl;

    /* Determinar si la pila est� vac�a */
    std::cout << (stack->empty() ? "(E) La pila est� vac�a" : "(E) La pila tiene elementos") << std::endl;

    /* Insertar elementos en la pila */
    for (int i = 1; i < 6; ++i) {
        stack->push(i);
    }

    /* Visualizar el contenido de la pila */
    std::cout << "(L) La pila tiene los siguientes elementos:" << std::endl;
    std::cout << *stack << std::endl;

    /* Obtener tama�o de la pila */
    std::cout << "(S) Tama�o de la pila: " << stack->size() << " elementos" << std::endl;

    /* Obtener el elemento superior de la pila */
    std::cout << "(T) El elemento superior de la pila es:" << *stack->top() << std::endl;

    /* Eliminar un elemento de la pila */
    Node<int> * node  = stack->pop();
    std::cout << "(R) El nodo eliminado de la pila es:" << *node << std::endl;

    std::cout << "(D) Liberando la memoria ocupada por el nodo eliminado" << std::endl;
    delete node;

    /* Visualizar el contenido de la pila */
    std::cout << "(L) La pila tiene los siguientes elementos:" << std::endl;
    std::cout << *stack << std::endl;

    /* Vaciar la pila */
    stack->clear();
    std::cout << "(V) Se vaci� la pila"<< std::endl;

    /* Determinar si la pila est� vac�a */
    std::cout << (stack->empty() ? "(E) La pila est� vac�a" : "(E) La pila tiene elementos") << std::endl;

    /* Liberando la memoria de la pila */
    delete stack;
    std::cout << "(D) Se liber� la memoria de la pila" << std::endl;

    return 0;
}
