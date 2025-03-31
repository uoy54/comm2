#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <queue>

class Graph
{
public:
    Graph(int vertices);
    void addEdge(int u, int v);
    std::vector<int> bfs(int start, int end);

private:
    int V;
    std::vector<std::vector<int>> adj;
};


#endif // GRAPH_H
