#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include <iostream>
#include "TreeNode.h"

template <class T>
class BinaryTree{

protected:
    TreeNode<T> *root = nullptr;
    void clear(TreeNode<T> *); //Clear privado para que no se borre una sola rama

public:
    BinaryTree() {}
    virtual ~BinaryTree();

    bool insert(T &, TreeNode<T> *); //Inserta nodo ne el arbol
    bool insert(TreeNode<T> *, TreeNode<T> *);

    bool empty();

    virtual TreeNode<T> *remove(T &); //Elimina un nodo del arbol

    void clear(); //Elimina todos los nodos del arbol

    //Recorridos de un arbol
    void preOrden();
    void preOrden(TreeNode<T> *);
    void inOrden();
    void inOrden(TreeNode<T> *);
    void inOrdenDescTop(int);
    void inOrdenDescTop(TreeNode<T> *, int, int);
    void postOrden();
    void postOrden(TreeNode<T> *);

private:

};

template <class T>
BinaryTree<T>::~BinaryTree(){
    this-> clear(this->root);
}

//Inserta nodo en un arbol
template <class T>
bool BinaryTree<T>::insert(T & value, TreeNode<T> *parent){ //Inserta nodo ne el arbol
    return this->insert(new TreeNode<T>(value), parent );
}

template <class T>
bool BinaryTree<T>::insert(TreeNode<T> *node, TreeNode<T> *parent){ //Inserta nodo ne el arbol

    bool inserted = false;

    //Verifica si el arbol esta vacio
    if (this->root == nullptr){
        //Establecer el nodo como la raiz del arbol
        this->root = node;
    }
    else if(parent == nullptr){
        //Insertar un nuevo nodo raiz
        node->setLeft(root);
        root = node;
    }
    else{
        if(parent->getLeft() == nullptr){
            parent->setLeft(node);
            inserted = true;
        }
        else if(parent->getRight() == nullptr){
            parent->setRight(node);
            inserted = true;
        }
        else{
            inserted = insert(node, parent->getLeft() );
            if(!inserted){
                insert(node, parent->getRight() );
            }
        }
    }

    return inserted;
}

template <class T>
bool BinaryTree<T>::empty(){
    return this-> root == nullptr;
}

template <class T>
TreeNode<T> *BinaryTree<T>::remove(T &){ //Elimina un nodo del arbol
    //Pendiente
    return nullptr;
}


template <class T>
void BinaryTree<T>::clear(){ //Elimina todos los nodos del arbol
    this->clear(this->root);
    this->root = nullptr;
}

//Clear sobrecarga
template <class T>
void BinaryTree<T>::clear(TreeNode<T> *node){ //Elimina todos los nodos del arbol
    if (node != nullptr){
        clear( node->getLeft() );
        clear( node->getRight() );
        delete node;
    }
}

//Recorridos de un arbol
//Preorden
template <class T>
void BinaryTree<T>::preOrden(){
    this->preOrden( this->root );
}

//Sobrecarga preOrden
template <class T>
void BinaryTree<T>::preOrden(TreeNode<T> *node){
    if (node != nullptr){
        //Procesar el nodo
        std::cout << *node << " ";
        //Desplazar a la izquierda
        preOrden( node->getLeft() );
        //Desplazar a la derecha
        preOrden( node->getRight() );
    }
}

//InOrden
template <class T>
void BinaryTree<T>::inOrden(){
    this->inOrden( this->root );
}

template <class T>
void BinaryTree<T>::inOrden(TreeNode<T> *node){
    if (node != nullptr){
        //Desplazar a la izquierda
        inOrden( node->getLeft() );
        //Procesar el nodo
        std::cout << *node << " ";
        //Desplazar a la derecha
        inOrden( node->getRight() );
    }
}

template <class T>
void BinaryTree<T>::inOrdenDescTop(int nPrimeros){
    this->inOrdenDescTop(this->root, nPrimeros, 0);
}

template <class T>
void BinaryTree<T>::inOrdenDescTop(TreeNode<T> *node, int limit, int _counter){
    if (_counter < limit && node != nullptr){
        //Desplazar a la derecha
        inOrdenDescTop( node->getRight(), limit, _counter++);
        //Procesar el nodo
        std::cout << *node << endl;
        //if(counter < limit){
            //Desplazar a la izquierda
            inOrdenDescTop( node->getLeft(), limit, _counter++);
        //}
    }
}

//Posrorden
template <class T>
void BinaryTree<T>::postOrden(){
    this->postOrden( this->root );
}

template <class T>
void BinaryTree<T>::postOrden(TreeNode<T> *node){
    if (node != nullptr){
        //Desplazar a la izquierda
        postOrden( node->getLeft() );
        //Desplazar a la derecha
        postOrden( node->getRight() );
        //Procesar el nodo
        std::cout << *node << " ";
    }
}

#endif // BINARYTREE_H_INCLUDED
