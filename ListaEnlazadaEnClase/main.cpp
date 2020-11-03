#include <iostream>
#include "Node.h"
#include "LinkedList.h"

using namespace std;

int main()
{
    //Checar el github del profe para tenerlo bien
    Node<int> n1;
    cout << n1 << endl;

    Node<float> n2(3.14);
    cout << n2 << endl;

    Node<int> n3 = n1;
    cout << n3 << endl;

    //Nodo con memoria dinamica
    Node<int> * nodeptr = new Node<int>(10);
    cout << *nodeptr << endl;

    //Liberar memoria ocupada por el nodo
    delete nodeptr;

    //Crear una lista
    LinkedList<int> * list = new LinkedList<int>();

    //Determinar si la lista esta vacia
    std::cout << (list->empty() ? "La lista esta vacia" : "La lista tiene elementos") << std::endl;

    //Insertar elementos en la lista
    list->insert_front(1);
    list->insert_front(2);

    //Mostrar el contenido de la lista
    std::cout << *list << std::endl;

    //Obtener el tamanio de la lista
    std::cout << "Tamanio de la lista: " << list->size() << " elementos" << std::endl;

    //Eliminar un elemento de la lista
    Node<int> * node = list->remove_front();

    //Imprimir el nodo eliminado
    std::cout << "El nodo eliminado es: " << *node << std::endl;

    //Liberar memoria del nodo eliminado
    delete node;

        //Eliminar un elemento de la lista
    node = list->remove_front();

    //Imprimir el nodo eliminado
    std::cout << "El nodo eliminado es: " << *node << std::endl;

    //Liberar memoria del nodo eliminado
    delete node;

    //Casos de prueba 5 metodos
    list->insert_front(7);
    list->insert_front(5);
    list->insert_front(3);
    list->insert_front(3);
    list->insert_front(1);
    list->insert_front(1);

    //Mostrar contenido de la lista
    std::cout << "\nImprime lista\n" << *list << std::endl;

    //Funcion count
    cout << "1 count: " << list->count(1) << endl;

    int numToInsert;

    //Indica el numero a insertar
    cout << "\nNumero a insertar: ";
    cin >> numToInsert;

    //Crea un nuevo nodo con el numero indicado
    Node<int> *sortedInsertNode = new Node<int>(numToInsert);

    //Insertar el numero indicado
    list->sortedInsert(sortedInsertNode);

    //Mostrar contenido de la lista
    std::cout << "\nImprime lista con numero " << numToInsert << " insertado\n" << *list << std::endl;

        //Comprobar clear
    std::cout << "\nTamanio lista\n" << list->size() << std::endl;

    //Mostrar contenido de la lista
    std::cout << "\nImprime lista\n" << *list << std::endl;

    //Remover duplicados
    list->removeDuplicates();

        //Comprobar clear
    std::cout << "\nTamanio lista\n" << list->size() << std::endl;

    //Mostrar contenido de la lista
    std::cout << "\nImprime lista\n" << *list << std::endl;

    //Eliminar la lista
    delete list;

    //Comprobar clear
    std::cout << "\nTamanio lista\n" << list->size() << std::endl;

    //Mostrar contenido de la lista
    std::cout << "\nImprime lista\n" << *list << std::endl;


    return 0;
}
