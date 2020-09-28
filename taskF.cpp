#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

const int INF = 2009000999;

class Graph
{
private:
    friend void print_dist_between_start_and_graph(Graph& graph, int start_ver);
    class edge
    {
    public:
        int to, weight;
        edge(int to, int weight): to(to), weight(weight){};
    };
    std::vector<std::vector<edge>> graph;
    unsigned int n_vertexes;
    std::vector<int> find_shortest_path(int& start)
    {
        std::vector<int> dist(graph.size(), INF);
        std::vector<bool> used(graph.size());
        dist[start] = 0;
        std::priority_queue<std::pair<int, int>> priority_queue;
        priority_queue.push({0, start});
        while(!priority_queue.empty())
        {
            int v = priority_queue.top().second;
            priority_queue.pop();
            while (used[v] and !priority_queue.empty())
            {
                v = priority_queue.top().second;
                priority_queue.pop();
            }
            if(used[v])
            {
                break;
            }
            used[v] = true;
            for (auto to: graph[v])
            {
                if(dist[to.to] > dist[v] + to.weight)
                {
                    dist[to.to] = dist[v] + to.weight;
                    priority_queue.push({-dist[to.to], to.to});
                }
            }
        }
        return dist;
    }

public:
    Graph(int n_vertexes): graph(n_vertexes), n_vertexes(n_vertexes){};
    void add_edge(int v, int u, int weight)
    {
        graph[v].push_back(edge(u, weight));
        graph[u].push_back(edge(v, weight));
    }
};

void print_dist_between_start_and_graph(Graph& graph, int start_ver)
{
    std::vector<int> dist = graph.find_shortest_path(start_ver);
    for(int i = 0; i < dist.size(); i++)
    {
        std::cout << dist[i] << " ";
    }
    std::cout << std::endl;
}
int main()
{
    int numOfRequests;
    std::cin >> numOfRequests;
    for(int i = 0; i < numOfRequests; i++)
    {
        int n_vertexes, m_edges;
        std::cin >> n_vertexes >> m_edges;
        Graph graph(n_vertexes);
        for (int k = 0; k < m_edges; k++)
        {
            int v, u, weight;
            std::cin >> v >> u >> weight;
            graph.add_edge(v, u, weight);
        }
        int start_ver;
        std::cin >> start_ver;
        print_dist_between_start_and_graph(graph, start_ver);
    }
}