#include "graph.h"
#include <algorithm>
#include <QDebug>

Graph::Graph(int vertices) : V(vertices)
{
    adj.resize(V);
}

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

std::vector<int> Graph::bfs(int start, int end)
{
    std::vector<bool> visited(V, false);
    std::vector<int> prev(V, -1);
    std::queue<int> queue;

    visited[start] = true;
    if (start < 0 || start >= V || end < 0 || end >= V) {
        qDebug() << "Ошибка: некорректные индексы start или end";
        return {};
    };

    queue.push(start);

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();

        if (node == end)
            break;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                prev[neighbor] = node;
                queue.push(neighbor);
            }
        }
    }

    std::vector<int> path;
    for (int at = end; at != -1; at = prev[at])
        path.push_back(at);

    std::reverse(path.begin(), path.end());

    if (!path.empty() && path[0] == start)
        return path;
    qDebug() << "Путь найден:" <<path;


    return {};
}
