#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "Ciudad.h"

using namespace std;

int main()
{
    const int numVertices = 6;

    //Vector de vertices
    vector<Ciudad> vertices(numVertices);

    //Generar los vertices
    for(int i = 0; i < numVertices; i++){
 //        vertices[i] = 65 + i;
        std::string nombre = "Ciudad " + std::to_string(i + 1);
        vertices[i] = Ciudad(nombre, rand() %10000000);
    }

    //Crear el grafo
    vector< vector<int> >grafo(numVertices);

    //Crea las columnas
    for (int i = 0; i < numVertices; i++){
        grafo[i] = vector<int>(numVertices);
        fill(grafo[i].begin(), grafo[i].end(), 0);
    }

    //Adicionar aristas al grafo
    grafo[0][1] = 1; //A -> B
    grafo[0][3] = 1; //A -> D

    grafo[1][0] = 1; //B -> A
    grafo[1][2] = 1; //B -> C
    grafo[1][4] = 1; //B -> E
    grafo[1][5] = 1; //B -> F

    grafo[2][1] = 1; //C -> B
    grafo[2][5] = 1; //C -> F

    grafo[3][0] = 1; //D -> A

    grafo[4][1] = 1; //E -> B

    grafo[5][1] = 1; //F -> B
    grafo[5][2] = 1; //F -> C

    //Visualizar el grafo
    cout << "\t";
    copy(vertices.begin(), vertices.end(), ostream_iterator<Ciudad>(cout, "\t"));
    cout << endl;

    int i = 0;
    for (auto fila : grafo){
        cout << vertices[i] << "\t";
        copy(fila.begin(), fila.end(), ostream_iterator<int>(cout, "\t"));
        cout << endl;
        i++;
    }

    //Obtener camino de A a F
    cout << endl;
    for (int i = 0; i < numVertices; i++){
        for (int j = i+1; j < numVertices; j++){
            if (grafo[i][j] == 1){
                cout << vertices[i] << "<-->" << vertices[j] << endl;
            }
        }
    }

    return 0;
}
