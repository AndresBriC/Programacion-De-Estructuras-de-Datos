#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
#include "D:\Universidad\OneDrive - Instituto Tecnologico y de Estudios Superiores de Monterrey\3er Semestre\Estructuras de Datos\ListaEnlazadaProfe\LinkedList.h"

template <class T>
class Stack : private LinkedList<T> {
public:
    Stack() : LinkedList<T>() {}
    virtual ~Stack() { };

    /* Obtener un apuntador al elemento de la parte superior de la pila*/
    Node<T> * top() const;

    /* Eliminar el elemento de la parte superior de la pila */
    Node<T> * pop();

    /* Insertar un elemento en la pila */
    void push(const T &);
    void push(Node<T> *);

    /* Mostrar el contenido de la pila */
    template <typename Tn>
    friend std::ostream & operator <<(std::ostream &, const Stack<Tn> &);

    /* Publicando los métodos heredados */
    using LinkedList<T>::empty;
    using LinkedList<T>::size;
    using LinkedList<T>::clear;
};

/* Obtener un apuntador al elemento de la parte superior de la pila
 * Complejidad: O(1)
 */
template <class T>
Node<T> * Stack<T>::top() const
{
    return this->first();
}

/* Eliminar el elemento de la parte superior de la pila
 * Complejidad: O(1)
 */
template <class T>
Node<T> * Stack<T>::pop()
{
    return this->remove_front();
}

/* Insertar un elemento en la pila
 * Complejidad: O(1)
 */
template <class T>
void Stack<T>::push(const T & value)
{
    this->insert_front(value);
}

template <class T>
void Stack<T>::push(Node<T> * node)
{
    this->insert_front(node);
}

/* Mostrar el contenido de la pila
 * Complejidad: O(n)
 */
template <class T>
std::ostream & operator <<(std::ostream & os, const Stack<T> & stack)
{
    /* Recorrer los elementos con un iterador */
    for (const Node<T> & node : stack) {
        os << node << std::endl;
    }

    return os;
}

#endif // STACK_H_INCLUDED
