#ifndef APPGRAFO_H_INCLUDED
#define APPGRAFO_H_INCLUDED

#include "Graph.h"
#include <vector>

class appGrafo{
public:
    void loadGraphMatriz(int, int, std::vector < std::vector<int> > &);
    void loadGraphLista(int, int, Graph<int, int> &);
    void DFS(std::vector < std::vector<int> > &, int);
    void BFS(Graph<int, int>, int);
};

#endif // APPGRAFO_H_INCLUDED
