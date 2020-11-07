#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include "BinaryTree.h"
#include <map>
#include <utility>
#include <string>

template <class T>
class BST : public BinaryTree<T>{

public:
    BST() {};
    virtual ~BST() {};

    TreeNode<T> *search(const T &) const;

    bool insert(T &);
    bool insert(TreeNode<T> *);

    bool insertPair(TreeNode<T> *);
    bool insertPair(T, int);

    //Metodos opreraciones avanzadas BST

    //Visit: complejidad lineal
    void visit(int orderType); //Despliega el BST en el orden indicado por el numero dado.
    void printLevel(TreeNode<T> *, int);
    void printLevelByLevel(TreeNode<T> *);

    //Height: complejidad lineal
    int height(); //Regresa la altura del BST
    int height(TreeNode<T> *); //Regresa la altura del BST

    //Ancestors: complejidad lineal
    void ancestors(T);
    bool ancestors(TreeNode<T> *, T); //Despliega los ancestros del dato dado

    //WhatlevelamI: complejidad lineal
    int whatLevelAmI(T);
    int whatLevelAmI(TreeNode<T> *, T, int); //Regresa un entero que representa el nivel en el que se encuentra un dato

private:
    //Oculta los metodos heredados
    //using BinaryTree<T>::insert; //Inserta nodo ne el arbol

};

template <class T>
TreeNode<T> *BST<T>::search(const T &value) const{

    TreeNode<T> *aux =  this->root;

    while(aux != nullptr){
        if(aux->getInfo() == value){
            return aux;
        }
        else{
            aux = (aux->getInfo() > value ? aux->getLeft() : aux->getRight());
        }
    }
    return nullptr;
}

template <class T>
bool BST<T>::insert(T &value){
    return this->insert(new TreeNode<T>(value));
}

template <class T>
bool BST<T>::insertPair(T _key, int _value){
    return this->insertPair(new TreeNode<T>(_key, _value));
}

template <class T>
bool BST<T>::insert(TreeNode<T> *node){

    //No se puede insertar un nodo nulo
    if(node == nullptr) return false;

    T value = node->getInfo(); //Obtener la info del nodo a insertar
    TreeNode<T> *aux =  this->root; //Nodo auxiliar en la raiz
    TreeNode<T> *parent = nullptr; //Establece una variable para el padre

    //Busca la posicion que le corresponde
    while(aux != nullptr){
        if(aux->getInfo() == value){
            delete node;
            return false;
        }
        else{
            parent = aux;
            aux = aux->getInfo() > value ? aux->getLeft() : aux->getRight();
        }
    }

    node->setParent(parent); //Establece el parent del nodo a insertar

    //Si el arbol esta vacio se inserta en la raiz
    if (parent == nullptr){
        this->root = node;
    }
    else{
        //Si el value es menor, se inserta a la izquierda
        if(parent->getInfo() > value){
            parent->setLeft(node);
        }
        //Si el value a insertar es mayor, se inserta a la derecha
        else{
            parent->setRight(node);
        }
    }

    return true;
}

template <class T>
bool BST<T>::insertPair(TreeNode<T> *node){

    //No se puede insertar un nodo nulo
    if(node == nullptr) return false;

    int value = node->getPairValue(); //Obtener la info del nodo a insertar
    TreeNode<T> *aux =  this->root; //Nodo auxiliar en la raiz
    TreeNode<T> *parent = nullptr; //Establece una variable para el padre

    //Busca la posicion que le corresponde
    while(aux != nullptr){
        if(aux->getPairValue() == value){
            delete node;
            return false;
        }
        else{
            parent = aux;
            aux = aux->getPairValue() > value ? aux->getLeft() : aux->getRight();
        }
    }

    node->setParent(parent); //Establece el parent del nodo a insertar

    //Si el arbol esta vacio se inserta en la raiz
    if (parent == nullptr){
        this->root = node;
    }
    else{
        //Si el value es menor, se inserta a la izquierda
        if(parent->getPairValue() > value){
            parent->setLeft(node);
        }
        //Si el value a insertar es mayor, se inserta a la derecha
        else{
            parent->setRight(node);
        }
    }

    return true;
}

//Metodos de operaciones avanzadas

//Desplega los datos del BST dependiendo del numero entrado
template <class T>
void BST<T>::visit(int orderType){
    switch(orderType){
    case 1: //Preorder
        this->preOrden();
        break;
    case 2: //Inorder
        this->inOrden();
        break;
    case 3: //Postorder
        this->postOrden();
        break;
    case 4: //Level by level
        this->printLevelByLevel(this->root);
        break;
    case 5: //Postorder
        this->inOrdenDesc();
        break;

    default:
        std::cout << "Se debe indicar un numero entre 1 y 4 para el tipo de display" << std::endl;
    }
}

//Con apoyo de: https://www.geeksforgeeks.org/level-order-tree-traversal/
template <class T>
void BST<T>::printLevel(TreeNode<T> *node, int level){
    if(node == nullptr){
        return;
    }

    if(level == 1){
        std::cout << node->getInfo() << " ";
    }
    else if(level > 1){
        printLevel(node->getLeft(), level-1);
        printLevel(node->getRight(), level-1);
    }
}

template <class T>
void BST<T>::printLevelByLevel(TreeNode<T> *node){
    int height = this->height();

    for(int i = 1; i <= height; i++){
        printLevel(node, i);
    }
}

//Regresa la altura del BST. Basado en la informacion de: https://www.thecrazyprogrammer.com/2019/11/height-and-depth-of-binary-tree.html
template <class T>
int BST<T>::height(){  //Usado para iniciar la busqueda de la altura
    return height(this->root);
}

template <class T>
int BST<T>::height(TreeNode<T> *node){

    if(node == nullptr){ //Si esta vacio, la altura es 0
        return 0;
    }
    else{
        int leftHeight, rightHeight; //Contador de alturas

        //Recorrido en postorden
        //Desplazar a la izquierda
        leftHeight = height( node->getLeft() );
        //Desplazar a la derecha
        rightHeight = height( node->getRight() );

        if(leftHeight > rightHeight){
            return(leftHeight + 1);
        }
        else{
            return(rightHeight + 1);
        }
    }
}

//Basado en la informacion de: https://www.techiedelight.com/find-ancestors-of-given-node-binary-tree/
template <class T>
bool BST<T>::ancestors(TreeNode<T> *node, T dato){

    //Caso base
    if(node == nullptr){
        return false;
    }

    //Regresa true si se encuentra el nodo
    if(node->getInfo() == dato){
        return true;
    }

    //Busca en la izquierda de la base
    bool left = ancestors(node->getLeft(), dato);

    //Busca en la derecha de la base
    bool right = false;
    if(!left){
        right = ancestors(node->getRight(), dato);
    }

    //Si se encuentra el dato a la izquierda o a la derecha, se muestra el ancestro del nodo actual
    if(left || right){
        std::cout << node->getInfo() << " ";
    }

    //Regresa true si se encuentra el nodo buscado
    return left || right;
}

template <class T>
void BST<T>::ancestors(T dato){
    if(!ancestors(this->root, dato)){
        std::cout << "El dato dado no existe en el arbol" << std::endl;
    };
}

//Busca el nivel del dato indicado. Con ayuda de: https://www.geeksforgeeks.org/get-level-of-a-node-in-a-binary-tree/
template <class T>
int BST<T>::whatLevelAmI(TreeNode<T> *node, T dato, int level){

    //Si no se encuentra el nodo
    if(node == nullptr){
        return -1;
    }

    //Si se encuentra el dato, comienza la cuenta del nivel, comenzando en 1
    if(node->getInfo() == dato){
        return level;
    }

    //Busca el dato a la izquierda del nodo actual
    int downLevel = whatLevelAmI(node ->getLeft(), dato, level+1);


    if(downLevel != -1){
        return downLevel;
    }

    downLevel = whatLevelAmI(node->getRight(), dato, level+1);

    return downLevel;
}

template <class T>
int BST<T>::whatLevelAmI(T dato){
    return whatLevelAmI(this->root, dato, 1);
}

#endif // BST_H_INCLUDED
