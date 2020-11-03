#include <iostream>
#include "BinaryTree.h"
#include "TreeNode.h"
#include "BST.h"

using namespace std;

int main()
{
    /* Creación de nodos */
    std::cout << "--- Creación y eliminación de nodos ---" << std::endl;
    std::cout << std::endl;

    /* Uso de constructor predeterminado TreeNode<T>() */
    TreeNode<int> n1;
    std::cout << "-> Nodo creado con constructor predeterminado: " << n1 << std::endl;

    /* Uso de constructor con parámetros TreeNode<T>(T) */
    TreeNode<float> n2(3.14);
    std::cout << "-> Nodo creado con constructor con parámetros: " << n2 << std::endl;

    /* Uso de constructor copia TreeNode<T>(TreeNode<T> &) */
    TreeNode<int> n3 = n1;
    std::cout << "-> Nodo creado con constructor copia: " << n3 << std::endl;

    /* Crear un nodo con memoria dinámica */
    TreeNode<int> * nodeptr = new TreeNode<int>(10);
    std::cout << "-> Nodo creado con memoria dinámica: " << *nodeptr << std::endl;

    /* Liberar la memoria ocupada por el nodo */
    std::cout << "<- Nodo eliminado con delete: " << *nodeptr << std::endl;
    delete nodeptr;

    //Creacion de un BinaryTree Vacio
    std::cout << "Demonstracion de un BinaryTree" << std::endl;
    std::cout << std::endl;

    //Crear un arbol
    BinaryTree<int> *tree = new BinaryTree<int>();

    //Insertar nodos en el arbol
    TreeNode<int> *root = new TreeNode<int>(1);

    tree->insert(root, nullptr);

    TreeNode<int> *a = new TreeNode<int>(2);
    TreeNode<int> *b = new TreeNode<int>(3);
    TreeNode<int> *c = new TreeNode<int>(4);
    TreeNode<int> *d = new TreeNode<int>(5);
    TreeNode<int> *e = new TreeNode<int>(6);
    TreeNode<int> *f = new TreeNode<int>(7);

    tree->insert(a, root);
    tree->insert(b, root);
    tree->insert(c, root);
    tree->insert(d, root);

    tree->insert(e, b);
    tree->insert(f, b);

    std::cout << "Se imprime en PreOrden" << std::endl;
    tree->preOrden();
    std::cout << std::endl;

    std::cout << "Se imprime en InOrden" << std::endl;
    tree->inOrden();
    std::cout << std::endl;

    std::cout << "Se imprime en PostOrden" << std::endl;
    tree->postOrden();
    std::cout << std::endl;

    std::cout << "Se eliminan los elementos del arbol" << std::endl;
    tree->clear();

    std::cout << "Esta limpio: " << tree->empty() << std::endl;

    //Crear un BST
    std::cout << std::endl;
    std::cout << "--- Demostración del uso de un Binary Search Tree ---" << std::endl;
    std::cout << std::endl;

    /* Crear un árbol */
    std::cout << "(C) Se crea un BST vacío" << std::endl;
    BST<int> * bst = new BST<int>();

    /* Insertar nodos en el árbol */

    std::cout << "(I) Se insertaron algunos nodos" << std::endl;

    TreeNode<int> * na = new TreeNode<int>(10);
    TreeNode<int> * nb = new TreeNode<int>(8);
    TreeNode<int> * nc = new TreeNode<int>(4);
    TreeNode<int> * nd = new TreeNode<int>(12);
    TreeNode<int> * ne = new TreeNode<int>(6);
    TreeNode<int> * nf = new TreeNode<int>(9);
    TreeNode<int> * ng = new TreeNode<int>(15);
    TreeNode<int> * nh = new TreeNode<int>(7);
    TreeNode<int> * ni = new TreeNode<int>(5);
    TreeNode<int> * nj = new TreeNode<int>(11);

    bst->insert(na);
    bst->insert(nb);
    bst->insert(nc);
    bst->insert(nd);
    bst->insert(ne);
    bst->insert(nf);
    bst->insert(ng);
    bst->insert(nh);
    bst->insert(ni);
    bst->insert(nj);

    /* Insertar un nodo repetido */
    TreeNode<int> * repetido = new TreeNode<int>(9);
    bool inserted = bst->insert(repetido);

    std::cout << (inserted ? "(I) El valor 9 se insertó" : "(I) El valor 9 ya existe existe") << std::endl;

    std::cout << "(V) Se imprime el BST en PreOrden" << std::endl;
    bst->preOrden();
    std::cout << std::endl;

    std::cout << "(V) Se imprime el BST en InOrden" << std::endl;
    bst->inOrden();
    std::cout << std::endl;

    std::cout << "(V) Se imprime el BST en PostOrden" << std::endl;
    bst->postOrden();
    std::cout << std::endl;

    TreeNode<int> * exist = bst->search(6);
    /* Buscar si el nodo existe */
    if (exist != nullptr) {
        std::cout << "(S) El valor 6 se encontró y su padre es ";
        std::cout << exist->getParent()->getInfo() << std::endl;
    }
    else {
        std::cout << "(S) El valor 6 no existe" << std::endl;
    }

    exist = bst->search(20);
    /* Buscar si el nodo existe */
    std::cout << (exist ? "(S) El valor 20 se encontró" : "(S) El valor 20 no existe") << std::endl;


    //Casos de prueba
    /*Arbol
             10
            /  \
           8     12
          / \   /  \
         4   9 11    15
          \
           6
          / \
         5   7
    */

    std::cout << "\n \nCasos de prueba Act 3.1" << std::endl << std::endl;

    std::cout << "\nArbol: " <<  std::endl;
    std::cout << "1             10" << std::endl;
    std::cout << "2           8     12" <<  std::endl;
    std::cout << "3         4  9  11  15" <<  std::endl;
    std::cout << "4           6" <<  std::endl;
    std::cout << "5         5   7" <<  std::endl;

    std::cout << "\nVisit preorder" << std::endl;
    bst->visit(1);
    std::cout << "\nVisit inorder" << std::endl;
    bst->visit(2);
    std::cout << "\nVisit postorder" << std::endl;
    bst->visit(3);
    std::cout << "\nVisit level by level" << std::endl;
    bst->visit(4);

    std::cout << "\nBST height:" << std::endl;
    std::cout << bst->height() << std::endl;

    std::cout << "\nAncestors:" << std::endl;
    int nodeToCheck;

    std::cout << "Buscar ancestros del: ";
    std::cin >> nodeToCheck;
    bst->ancestors(nodeToCheck);

    std::cout << "\nWhat level am I: ";
    std::cin >> nodeToCheck;
    std::cout << bst->whatLevelAmI(nodeToCheck) << std::endl;


    std::cout << "\n \n(C) Se eliminan todos los nodos del árbol" << std::endl;
    bst->clear();

    /* Determinar si el BST está vacío */
    std::cout << (bst->empty() ? "(E) El BST está vacío" : "(E) El BST tiene elementos") << std::endl;

    /* Eliminar la memoria ocupada por el BST */
    delete bst;
    std::cout << "(D) Se liberó la memoria del BST" << std::endl;

    return 0;
}
