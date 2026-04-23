#include "Graph.h"
#include "iostream"
#include "iomanip"
using namespace std;

void Graph::dfsRecursive(int v, vector<bool> &visited)
{
    visited[v] = true;
    cout << names[v] << " -> ";

    for (int neighbor : adjList[v])
    {
        if (!visited[neighbor])
        {
            dfsRecursive(neighbor, visited);
        }
    }
}

Graph::Graph(int v)
{
    vertices = v;
    adjList.resize(v);
    names.resize(v);
}

void Graph::setName(int index, string name)
{
    if (index >= 0 && index < vertices)
    {
        names[index] = name;
    }
}

void Graph::addEdge(int u, int v)
{
    if (u >= 0 && u < vertices && v >= 0 && v < vertices)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
}

void Graph::displayGraph()
{
    cout << "\n\t<========== MODULE & EVENT NETWORK (ADJACENCY LIST) ==========>\n";
    for (int i = 0; i < vertices; i++)
    {

        cout << left << setw(20) << names[i] << " connects to: ";

        for (int neighbor : adjList[i])
        {
            cout << "[" << names[neighbor] << "] ";
        }
        cout << "\n";
    }
}

void Graph::bfs(int start)
{
    vector<bool> visited(vertices, false);
    vector<int> queue;

    visited[start] = true;
    queue.push_back(start);

    cout << "\nBFS Traversal starting from '" << names[start] << "':\n";

    int head = 0;
    while (head < queue.size())
    {
        int current = queue[head++];
        cout << names[current] << " -> ";

        for (int neighbor : adjList[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                queue.push_back(neighbor);
            }
        }
    }
    cout << "END\n";
}

void Graph::dfs(int start)
{
    vector<bool> visited(vertices, false);
    cout << "\nDFS Traversal starting from '" << names[start] << "':\n";
    dfsRecursive(start, visited);
    cout << "END\n";
}
