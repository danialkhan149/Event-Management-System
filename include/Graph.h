#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "string"
using namespace std;

class Graph
{
private:
    int vertices;
    vector<vector<int>> adjList;
    vector<string> names;

    void dfsRecursive(int, vector<bool> &);

public:
    Graph(int);

    void setName(int, string);
    void addEdge(int, int);
    void displayGraph();

    void bfs(int);
    void dfs(int);
};

#endif