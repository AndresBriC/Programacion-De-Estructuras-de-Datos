#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <iostream>
#include "D:\Universidad\OneDrive - Instituto Tecnologico y de Estudios Superiores de Monterrey\3er Semestre\Estructuras de Datos\ListaEnlazadaProfe\LinkedList.h"

template <class T>
class Queue : private LinkedList<T> {
private:
    Node<T> * _last = nullptr;

public:
    Queue() : LinkedList<T>() {}
    virtual ~Queue();

    /* Obtener un apuntador al �ltimo elemento de la cola */
    Node<T> * last() const;

    /* Eliminar el primer elemento de la cola */
    Node<T> * dequeue();

    /* Eliminar todos los elementos de la cola y liberar la memoria ocupada */
    void clear() override;

    /* Insertar un elemento en la cola */
    void enqueue(const T &);
    void enqueue(Node<T> *);

    /* Mostrar el contenido de la cola */
    template <typename Tn>
    friend std::ostream & operator <<(std::ostream &, const Queue<Tn> &);

    /* Publicando los m�todos heredados */
    using LinkedList<T>::first;
    using LinkedList<T>::empty;
    using LinkedList<T>::size;
    using LinkedList<T>::clear;
};


template <class T>
Queue<T>::~Queue()
{
    this->clear();
}


/* Obtener un apuntador al �ltimo elemento cola
 * Complejidad: O(1)
 */
template <class T>
Node<T> * Queue<T>::last() const
{
    return this->_last;
}

/* Eliminar el primer elemento de la cola
 * Complejidad: O(1)
 */
template <class T>
Node<T> * Queue<T>::dequeue()
{
    return this->remove_front();
}

/* Eliminar todos los elementos de la cola y liberar la memoria ocupada
 * Complejidad: O(n)
 */
template <class T>
void Queue<T>::clear()
{
    LinkedList<T>::clear();

    /* Establecer last en nullptr */
    this->_last = nullptr;
}


/* Insertar un elemento en la cola
 * Complejidad: O(1)
 */
template <class T>
void Queue<T>::enqueue(const T & value)
{
    Node<T> * node = new Node<T>(value);

    this->enqueue(node);
}

template <class T>
void Queue<T>::enqueue(Node<T> * node)
{
    if ( this->empty() ) {
        this->_last = this->_first = node;
    }
    else {
        this->_last->setNext(node);
        this->_last = node;
    }

    ++this->_size;
}

/* Mostrar el contenido de la pila
 * Complejidad: O(n)
 */
template <class T>
std::ostream & operator <<(std::ostream & os, const Queue<T> & queue)
{
    /* Recorrer los elementos con un iterador */
    for (const Node<T> & node : queue) {
        os << node << " ";
    }

    return os;
}
#endif // QUEUE_H_INCLUDED
