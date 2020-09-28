#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

const long long INF = 2000000000000000;

class Tunnels
{
private:
    friend void print_answer_can_they_survive(Tunnels& tunnels, int start, int finish);
    unsigned int n_vertexes;
    std::vector<long long> fire, live;
    std::vector<std::vector<long long>> g, d;
    std::set<std::pair<long long, long long>> q;
    void Dijkstra_fire()
    {
        int count = 0;
        while (!q.empty() && count < n_vertexes)
        {
            int v = q.begin()->second;
            q.erase(q.begin());
            for (int j = 0; j < g[v].size(); ++j)
            {
                if (fire[v] + d[v][j] < fire[g[v][j]])
                {
                    if (fire[g[v][j]] < INF)
                    {
                        q.erase(std::make_pair(fire[g[v][j]], g[v][j]));
                    }
                    fire[g[v][j]] = fire[v] + d[v][j];
                    q.insert(std::make_pair(fire[g[v][j]], g[v][j]));
                }
            }
            ++count;
        }
    }

    void Dijkstra_live(int start)
    {
        int count = 0;
        live[start] = 0;
        std::set<std::pair<int, int>> set_q;
        set_q.insert(std::make_pair(0, start));
        while (!set_q.empty() && count < n_vertexes)
        {
            int v = set_q.begin()->second;
            set_q.erase(set_q.begin());
            for (int j = 0; j < g[v].size(); ++j)
            {
                if (live[v] + d[v][j] < fire[g[v][j]] && live[v] + d[v][j] < live[g[v][j]])
                {
                    if (live[g[v][j]] < INF)
                    {
                        set_q.erase(std::make_pair(live[g[v][j]], g[v][j]));
                    }
                    live[g[v][j]] = live[v] + d[v][j];
                    set_q.insert(std::make_pair(live[g[v][j]], g[v][j]));
                }
            }
            ++count;
        }
    }

public:
    Tunnels(int n_vertexes): fire(n_vertexes, INF), live(n_vertexes, INF), n_vertexes(n_vertexes),
                             g(n_vertexes), d(n_vertexes){};
    void add_edge_x(int v)
    {
        fire[v] = 0;
        q.insert(std::make_pair(0, v));
    }
    void add_edge(int x, int y, int l)
    {
        g[x].push_back(y);
        g[y].push_back(x);
        d[x].push_back(l);
        d[y].push_back(l);
    }
};

void print_answer_can_they_survive(Tunnels& tunnels, int start, int finish)
{
    tunnels.Dijkstra_fire();
    tunnels.Dijkstra_live(start);
    if (tunnels.live[finish] < INF)
    {
        std::cout << tunnels.live[finish];
    }
    else
    {
        std::cout << -1;
    }
}

int main()
{
    int station, tunnel, burningTunnel;
    std::cin >> station >> tunnel >> burningTunnel;
    Tunnels tunnels(station);
    for (int i = 0; i < burningTunnel; ++i)
    {
        int x;
        std::cin >> x;
        tunnels.add_edge_x(x - 1);
    }
    for (int i = 0; i < tunnel; ++i)
    {
        int x, y, l;
        std::cin >> x >> y >> l;
        tunnels.add_edge(x - 1, y - 1, l);
    }
    int start, finish;
    std::cin >> start >> finish;
    print_answer_can_they_survive(tunnels, start - 1, finish - 1);
    return 0;
}