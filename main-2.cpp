#include<iostream>
#include<vector>
#include <algorithm>

class Graph {
private:
    std::vector<std::vector<int>> edges;
    std::vector<std::vector<int>> dist;
    int n_vertexes;
    void Shortest_path();

public:
    Graph(int n_vertexes):n_vertexes(n_vertexes), edges(n_vertexes, std::vector<int>(n_vertexes, 0)), dist(n_vertexes, std::vector<int>(n_vertexes, 0)) {};
    void add_edge(int i, int j, int a){
        edges[i][j] = a;
    }
    const int INF = 100000000;
    int find_shortest_path(int stat, int end) {
        Shortest_path();
        int distance = dist[stat - 1][end - 1];
        if (distance == INF) {
            return -1;
        }
        else {
            return distance;
        }
    }
};

int main()
{
    int n, s, e;
    std::cin >> n >> s >> e;
    Graph G(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int edge;
            std::cin >> edge;
            if (edge == -1) {
                G.add_edge(i, j, G.INF);
            }
            else {
                G.add_edge(i, j, edge);
            }
        }
    }
    std::cout << G.find_shortest_path(s, e);
    return 0;
}

void Graph::Shortest_path() {
    for (int i = 0; i < n_vertexes; i++) {
        for (int j = 0; j < n_vertexes; j++) {
            dist[i][j] = edges[i][j];
        }
    }
    for(int k = 0; k < n_vertexes; k++) {
        for(int i = 0; i < n_vertexes; i++) {
            for (int j = 0; j < n_vertexes; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}