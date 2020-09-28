#include<iostream>
#include<vector>
#include <algorithm>

class Graph
{
private:
    const int INF = 100000000;
    std::vector<std::vector<int>> edges;
    std::vector<std::vector<int>> dist;
    int n_vertexes;
    void Floyd()
    {
        for (int i = 0; i < n_vertexes; i++)
        {
            for (int j = 0; j < n_vertexes; j++)
            {
                dist[i][j] = edges[i][j];
            }
        }
        for(int k = 0; k < n_vertexes; k++)
        {
            for(int i = 0; i < n_vertexes; i++)
            {
                for (int j = 0; j < n_vertexes; j++)
                {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

public:
    Graph(int n_vertexes):n_vertexes(n_vertexes)
    {
        edges.assign(n_vertexes, std::vector<int>(n_vertexes, 0));
        dist.assign(n_vertexes, std::vector<int>(n_vertexes, 0));
    }
    void scan_edges(std::istream& streamIn)
    {
        for (int i = 0; i < n_vertexes; i++)
        {
            for (int j = 0; j < n_vertexes; j++)
            {
                int edge;
                streamIn >> edge;
                if (edge == -1)
                {
                    edges[i][j] = INF;
                }
                else
                {
                    edges[i][j] = edge;
                }
            }
        }
    }
    int find_shortest_path(int start_ver, int end_ver)
    {
        Floyd();
        int distance = dist[start_ver - 1][end_ver - 1];
        if (distance == INF)
        {
            return -1;
        }
        else
        {
            return distance;
        }
    }
};

int main()
{
    int n_vertexes, start_ver, end_ver;
    std::cin >> n_vertexes >> start_ver >> end_ver;
    Graph graph(n_vertexes);
    graph.scan_edges(std::cin);
    std::cout << graph.find_shortest_path(start_ver, end_ver);
    return 0;
}