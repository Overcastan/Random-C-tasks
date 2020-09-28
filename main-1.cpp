#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

const int INF = 100000000;

class Graph
{
private:
    friend void print_min_value(Graph& graph, int start, int k, int f);
    class edge
    {
    public:
        int to, weight;
        edge(int to, int weight):to(to), weight(weight){};
    };
    std::vector<std::vector<edge>> graph;
    int n_vertexes;
    std::vector<std::vector<int>> ford_bellman(int start, int limit)
    {
        std::vector<std::vector<int>> dist(n_vertexes, std::vector<int>(limit + 1, INF));
        dist[start - 1][0] = 0;
        for (int k = 1; k <= limit; ++k)
        {
            for (int i = 0; i < n_vertexes; ++i)
            {
                for (int j = 0; j < graph[i].size(); ++j)
                {
                    int v = graph[i][j].to;
                    int w = graph[i][j].weight;
                    if (dist[i][k - 1] < INF)
                    {
                        dist[v][k] = std::min(dist[v][k], dist[i][k - 1] + w);
                    }
                }
            }
        }
        return dist;
    }


public:
    Graph(int n_vertexes): n_vertexes(n_vertexes), graph(n_vertexes){};
    void add_edge(int v, int u, int weight)
    {
        graph[v].push_back({u, weight});
    }
};

void print_min_value(Graph& graph, int start, int k, int f)
{
    std::vector<std::vector<int>> path = graph.ford_bellman(start, k);
    int min = INF;
    for (int i = 1; i <= k; ++i)
    {
        min = std::min(min, path[f - 1][i]);
    }
    if (min != INF)
    {
        std::cout << min;
    }
    else
    {
        std::cout << -1;
    }
    std::cout << std::endl;

}

int main()
{
    int citiesNum, flightNum, nightNum, city, conference;
    std::cin >> citiesNum>> flightNum >> nightNum
             >> city >> conference;
    Graph graph(citiesNum);
    for (int i = 0; i < flightNum; i++)
    {
        int v, u, weight;
        std::cin >> v >> u >> weight;
        graph.add_edge(v - 1, u - 1, weight);
    }
    print_min_value(graph, city, nightNum, conference);
    return 0;
}