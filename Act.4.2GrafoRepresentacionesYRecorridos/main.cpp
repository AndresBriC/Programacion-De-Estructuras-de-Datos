#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <time.h>

#include "Graph.h"

using namespace std;

//Complejidad O(V+E)
void loadGraphLista(int v, int e, Graph<int, int> & graph)
{
    Vertex<int,int> *vertexArray[v]; //Array que contiene los vertice indicados por el parametro v

    for(int i = 0; i<v; i++){ //Itera por cada vertice indicado por el parametro v
        vertexArray[i] = new Vertex<int,int>(rand() %100); //Crea vertice conteniendo un numero al azar
        graph.addVertex(vertexArray[i]); //Agrega el vertice al grafo
        //cout << *vertexArray[i] << endl; //Debug tool
    }

    for(int i = 0; i<e ; i++){//Agrega las aristas al grafo
        graph.addEdge(vertexArray[rand() %v], vertexArray[rand() %v], (rand() %50)+1); //Agrega una arista entre los vertices seleccionados al azar, con un peso entre 1 y 50
    }

//    cout << "Grafo enlazado:" << endl; //Debug tool
//    cout << graph << endl; //Debug tool

}

//Complejidad O(V+E)
void loadGraphMatriz(int v, int e, std::vector < std::vector<int> > & graph)
{
    std::vector<int> vertices(v); //Crea un vector con v numero de vertices

    for(int i = 0; i<v; i++){ //Itera por cada vertice indicado por el parametro v
        vertices[i] = (rand() %100)+1; //Le asigna un valor entre  1 y 100 a cada vertice

        //Creacion de columnas
        graph[i] = vector<int>(v); //
        fill(graph[i].begin(), graph[i].end(), 0);
    }

    for(int i = 0; i<e ; i++){//Agrega las aristas al grafo, iterando por cada arista indicado en el parametro e
        graph[rand()%v][rand()%v] = (rand()%50)+1; //Toma una fila y columna al azar y le de un valor entre 1 y 50
    }

//    //Visualizar el grafo
//    cout << "Graph matriz: " << endl;
//    cout << "\t";
//    copy(vertices.begin(), vertices.end(), ostream_iterator<int>(cout, "\t"));
//    cout << endl;
//
//    int i = 0;
//    for (auto fila : graph){
//        cout << vertices[i] << "\t";
//        copy(fila.begin(), fila.end(), ostream_iterator<int>(cout, "\t"));
//        cout << endl;
//        i++;
//    }
}

//Complejidad O(V+E)
void DFS(std::vector < std::vector<int> > & graph, int u)
{
    /* Implementar
    Para todas las arista e incidentes en u:
        Si la arista e no se ha recorrido
            w = nodo al que llega e
            Si w no se ha visitado
                Marca e con línea sólida. Arista de
                    descubrimiento.
            DFS(G, w)
        sino
            Marcar e con línea punteada. Arista en
                retroceso
    */


}

//Complejidad O(V+E)
void BFS(Graph<int, int> & graph, int u)
{
    /* BFS(grafo G, nodo u)
        Crear una cola Q
        Q.push(u)
        marcar u como visitado
        Mientras Q != vacío
            t = Q.pop()
            Si t es lo que buscamos
                return t
            Para todas las arista e incidentes en t:
                o = G.opuesto(t,e)
                Si o no está marcado
                    marcar o
                    Q.push(o)
    */
}

int main()
{
    /* Definir número de vértices y aristas */
    const int vertices = 10;
    const int aristas = 15;

    srand(time(0)); //Crea la seed para la generacion de numeros al azar

    /* Declaración del grafo como matriz de adyacencia */
    std::vector < std::vector<int> > matriz_adyacencia(vertices);

    /* Generar el grafo como matriz de adyacencia */
    loadGraphMatriz(vertices, aristas, matriz_adyacencia);

    /* Recorrido con DFS */
    std::cout << "------ Matriz de adyacencia con DFS ------" << std::endl;
    int nodo_u = 1;
    DFS(matriz_adyacencia, nodo_u);

    /* Declaración del grafo como multilista */
    Graph<int, int> multilista;

    /* Generar el grafo como multilista */
    loadGraphLista(vertices, aristas, multilista);

    /* Recorrido con BFS */
    std::cout << "------ Multilista con BFS ------" << std::endl;
    nodo_u = 1;
    BFS(multilista, nodo_u);

    return 0;
}
