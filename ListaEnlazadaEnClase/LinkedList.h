#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include <ostream>
#include "Node.h"

template <class T>
class LinkedList{
private:
    Node<T> * _first = nullptr;
    int _size = 0;

public:
    //Constructor
    LinkedList() {};

    //Destructor
    virtual ~LinkedList();

    //Obtener el tamanio de la lista
    int size() const;

    //Obtener el primer elemento
    Node<T> *first() const;

    //Determinar si la lista esta vacia
    bool empty() const;

    //Insertar un elemento en cierta posicion
    void insert(const T &, int);
    void insert(Node<T> *, int);

    //Insertar al inicio
    void insert_front(const T &);
    void insert_front(Node<T> *);

    //Insertar al final
    void insert_back(const T &);
    void insert_back(Node<T> *);

    //Eliminar un elemento y regresar un apuntador al mismo.
    //Nota: No liberan la memmoria ocupada por el nodo eliminado
    //
    // Eliminar el elemento en la posición dada
    Node<T> * remove(int);

    // Eliminar el primer elemento
    Node<T> * remove_front();

    // Eliminar el último elemento
    Node<T> * remove_back();

    // Eliminar un elemento dado
    Node<T> * remove(Node<T> *);

    // Eliminar todos los elementos de la lista y liberar la memoria ocupada
    virtual void clear();

    // Obtener el elemento que se encuentra en una posición
    Node<T> * at(int) const;

    // Obtener la posición de un nodo
    int at(Node<T> *) const;

    // Mostrar el contenido de la lista
    template <typename Tn>
    friend std::ostream & operator <<(std::ostream &, const LinkedList<Tn> &);

    //Cuenta el numero de veces que ocurre un elemento dado en la lista
    int count(T element);

    //Dada una lista ordenada en orden creciente, inserta un nodo en la posicion conrrecta
    void sortedInsert(Node<T> *node);

    //Toma una lista ordenada crecientemente y elimina los duplicados de la lista
    void removeDuplicates();

    //Invierte la lista enlazada, reorganizando los punteros next y el first
    void reverse();

};

template <class T>
LinkedList<T>::~LinkedList(){
    this->clear();
}

//Obtener el tamanio de la lista
template <class T>
int LinkedList<T>::size() const{
    return this->_size;
}

//Obtener el primer elemento
template <class T>
Node<T> *LinkedList<T>::first() const{
    return this->_first;
}

//Determinar si la lista esta vacia
template <class T>
bool LinkedList<T>::empty() const{
    return this->_first == nullptr;
}

//Insertar un elemento en cierta posicion
template <class T>
void LinkedList<T>::insert(const T &, int){

}

template <class T>
void LinkedList<T>::insert(Node<T> * node, int targetPos){

    Node<T> *tempNode = this->_first;
    int currentPos = 0; //Para conocer la posicion actual de cada nodo en la lista

    if(targetPos == 0){
        insert_front(node);
    }
    else if(targetPos < 0 || targetPos > this->_size){
        std::cout << "Posicion invalida, debe ser mayor a -1 y menor a " << this->_size << std::endl;
    }
    else{
        while(tempNode != nullptr){
            if(currentPos == targetPos-1){ //Se detiene en la posicion antes del nodo deseado
                node->setNext(tempNode->getNext()); //Hace que el next del nodo nuevo, sea el next del nodo antes de la posicion deseada
                tempNode->setNext(node); //Pone el next del anterior a la posicion como el nuevo nodo
                ++this->_size; //Aumenta el tamanio de la lista
                break; //Hace que deje de pasar por cada nodo de la lista
            }

            tempNode = tempNode->getNext();
            currentPos++; //Pasa a la siguiente posicion de la lista
        }
    }
}

//Insertar al inicio
template <class T>
void LinkedList<T>::insert_front(const T & value){
    //Crear un nodo
    Node<T> * newnode = new Node<T>(value);
    this->insert_front(newnode);
}

template <class T>
void LinkedList<T>::insert_front(Node<T> * node){
    //Insertar el primer elemento
    if(this->empty()){
        this->_first = node;
    }
    else{ //Insertar cualquier elemento
        node->setNext(this->_first);
        this->_first = node;
    }

    ++this->_size; //Icrementar el tamanio de la lista
}

//Insertar al final
template <class T>
void LinkedList<T>::insert_back(const T &){

}

template <class T>
void LinkedList<T>::insert_back(Node<T> *){

}

//Eliminar el elemento en la posición dada
template <class T>
Node<T> * LinkedList<T>::remove(int targetPos)
{
//    Node<T> *tempNode = this->_first;
//    int currentPos = 0; //Para conocer la posicion actual de cada nodo en la lista
//
//    if(targetPos == 0){
//        this->_first = tempNode->getNext(); //Pone el nodo seleccionado como el primero
//        delete(tempNode);
//        --this->_size;
//    }
//    else if(targetPos < 0 || targetPos > this->_size){ //Para evitar referencias a posiciones que no existen
//        std::cout << "Posicion invalida, debe ser mayor a -1 y menor a " << this->_size << std::endl;
//    }
//    else{
//        while(tempNode != nullptr){
//            if(currentPos == targetPos-1){ //Se detiene en la posicion antes del nodo deseado
//                node->setNext(tempNode->getNext()); //Hace que el next del nodo nuevo, sea el next del nodo antes de la posicion deseada
//                tempNode->setNext(node); //Pone el next del anterior a la posicion como el nuevo nodo
//                --this->_size; //Aumenta el tamanio de la lista
//                break; //Hace que deje de pasar por cada nodo de la lista
//            }
//
//            tempNode = tempNode->getNext();
//            currentPos++; //Pasa a la siguiente posicion de la lista
//        }
//    }
}

// Eliminar el primer elemento
template <class T>
Node<T> *LinkedList<T>::remove_front(){
    //Declarar una variable temporal
    Node<T> * node = nullptr;

    //Verifica si la lista esta vacia
    if (!this->empty()){
        node = this->_first; //Guarda referencia al primer elemento
        this->_first = node->getNext(); //Actualiza first al siguiente elemento
        node->setNext(nullptr); //El next del almacenado es un nullptr
        --this->_size; //Decrementar el tamanio de la lista
    }

    return node;
}

//Eliminar el último elemento
template <class T>
Node<T> * LinkedList<T>::remove_back()
{
    //Por implementar
}

//Eliminar un elemento dado
template <class T>
Node<T> * LinkedList<T>::remove(Node<T> *)
{
    //Por implementar
}

//Eliminar todos los elementos de la lista y liberar la memoria ocupada
template <class T>
void LinkedList<T>::clear()
{
    if(this->empty()){ //Checa si la lista esta vacia antes de hacer nada
        std::cout << "La lista ya estaba vacia" << std::endl;
    }
    else if(!this->empty()){
        Node<T> *tempNode = this->_first; //Toma el primer elemento de la lista

        //Pasa por todos los elementos de la lista
        while(tempNode != nullptr){
            tempNode = tempNode->getNext();
            delete(this->remove_front());
        }

        //Asegurar qeu el tamanio sea 0 y el primero sea nullptr
        this->_size = 0;
        this->_first = nullptr;

        //Mensaje de exito
        std::cout << "\nList cleared" << std::endl;
    }
}


//Sobrecarga de operadores
template <class T>
std::ostream & operator <<(std::ostream & os, const LinkedList<T> & list){
    //Obtener el primer elemento de la lista
    Node<T> * tmp = list._first;

    //Desplazarse mientras tmp != nullptr
    while(tmp != nullptr){
        os << *tmp << std::endl;

        //Desplazar el apuntador al siguiente elemento
        tmp = tmp->getNext();
    }

    return os;
}

//Cuenta el numero de veces que ocurre un elemento dado en la lista
template <class T>
int LinkedList<T>::count(T element){

    int elementCounter = 0; //Para contar repeticiones del elemento
    Node<T> *tempNode = this->_first; //Toma el primer elemento de la lista

    while(tempNode != nullptr){

        if(element == tempNode->getInfo()){
            elementCounter++;
        }

        tempNode = tempNode->getNext();
    }

    return elementCounter;
}

template <class T>
void LinkedList<T>::sortedInsert(Node<T> *node){
    Node<T> *tempNode = this->_first; //Toma el primer elemento de la lista
    Node<T> *tempNodeTwo = this->_first; //Toma el primer elemento de la lista

    int currentPos = 0; //Referencia a la posicion actual en la lista

    //Pasa por toda la lista
    while(tempNode != nullptr){

        //Casos de prueba individuales (juntarlos todos despues del debug)

        //Si es menor que el actual
        if((node->getInfo() < tempNode->getInfo())){
            std::cout << "Posicion encontrada al principio" << std::endl;
            insert(node, currentPos);
            break;
        }

        //Para hacer la comparacion del actual con el siguiente
        if(tempNode->getNext() != nullptr){
            tempNodeTwo = tempNode->getNext(); //Toma referencia al siguiente nodo, siempre que no se este al final de la lista
        }

        std::cout << tempNode->getInfo() << std::endl; //Despliega lista

        //Mayor que el actual y menor que el siguiente
        if((node->getInfo() > tempNode->getInfo() && node->getInfo() < tempNodeTwo->getInfo())){
            std::cout << "Posicion encontrada" << std::endl;
            insert(node, currentPos+1);
            break;
        }

        //Igual que el actual al final de la lista
        if(node->getInfo() == tempNode->getInfo() && tempNode->getNext() == nullptr){
            std::cout << "Posicion encontrada al final dupl" << std::endl;
            insert(node, currentPos+1);
            break;
        }

        //Mayor que el actual al final de la lista
        if(node->getInfo() != tempNode->getInfo() && tempNode->getNext() == nullptr){
            std::cout << "Posicion encontrada al final mayor" << std::endl;
            insert(node, currentPos+1);
            break;
        }


        tempNode = tempNode->getNext();
        currentPos++; //Mueve el contador a la sig posicion de la lista
    }
}

template <class T>
void LinkedList<T>::removeDuplicates(){
    Node<T> *tempNode = this->_first; //Toma el primer elemento de la lista
    Node<T> *tempNodeTwo = this->_first; //Toma el primer elemento de la lista, usado para comparar con el siguiente

    int currentPos = 0; //Referencia a la posicion actual en la lista

    //Pasa por toda la lista
    while(tempNode != nullptr){

        if(tempNode->getNext() != nullptr){
            tempNodeTwo = tempNode->getNext(); //Para comparar el actual con el siguiente
        }

        if(tempNode->getInfo() == tempNodeTwo->getInfo() && tempNode->getNext() != nullptr){
            std::cout << "Duplicado encontrado. Actual " << tempNode->getInfo() << " Siguiente: " << tempNodeTwo->getInfo() << std::endl;
            //remove(currentPos);
        }

        std::cout << tempNode->getInfo() << std::endl; //Despliega lista

        tempNode = tempNode->getNext();
        currentPos++; //Mueve el contador a la sig posicion de la lista
    }
}

template <class T>
void LinkedList<T>::reverse(){
    Node<T> *tempNode = this->_first; //Toma el primer elemento de la lista

    //Hacer que el primero apunte a nullptr
    //Hacer que el segundo apunte al primero y asi hasta que se llegue al final

    while(tempNode != nullptr){
            if(/*estamos en el primero*/true){
                //Referencia a nullptr
                //Guarda la direccion del primero
            }
            else{
                //Referencia a la direccion almacenada temporalmente
                //Guarda la direccion del elemento actual
            }
        }

        tempNode = tempNode->getNext();
    }



#endif // LINKEDLIST_H_INCLUDED
