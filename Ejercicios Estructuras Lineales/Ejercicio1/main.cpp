#include <iostream>
#include "D:\Universidad\OneDrive - Instituto Tecnologico y de Estudios Superiores de Monterrey\3er Semestre\Estructuras de Datos\QueueEnClase\Queue\Queue.h" //Queue
#include "D:\Universidad\OneDrive - Instituto Tecnologico y de Estudios Superiores de Monterrey\3er Semestre\Estructuras de Datos\StackEnClase\STack\Stack.h" //Stack

using namespace std;

int main()
{
    //Crear una cola vacía
    Queue<int> * queue = new Queue<int>();
    cout << "Se crea una cola  vacía" << endl;

    //Insertar elementos en la cola
    for (int i = 1; i < 11; ++i) {
        queue->enqueue(i);
    }

    //Muestra los elementos de la cola
    cout << "Elementos de la cola:" << endl;
    cout << *queue << endl;

    //Invertir la cola

    //Crear una pila auxiliar
    Stack<int> *stack = new Stack<int>();

    //Pasar los elementos de la cola a la pila
    while( !queue->empty() ){
        stack->push( queue->dequeue() );
    }

    //Pasar los elementos de la pila a la cola
    while( !stack->empty() ){
        queue->enqueue( stack->pop() );
    }

    delete stack;

    //Muestra los elementos de la cola
    cout << "Elementos de la cola:" << endl;
    cout << *queue << endl;

    return 0;
}
