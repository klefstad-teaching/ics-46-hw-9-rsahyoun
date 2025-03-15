#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    vector<int> distances(G.numVertices, INF);
    previous.resize(G.numVertices - 1);
    vector<bool> visited(G.numVertices, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    distances[source] = 0;
    pq.push({0, source});

    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if(visited[u])
        {
            continue;
        }

        visited[u] = true;

        for(const Edge& edge : G[u])
        {
            int v = edge.dst;
            int weight = edge.weight;

            if(distances[u] != INF && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;

                previous[v] = u;

                pq.push({distances[v], v});
            }
        }
    }

    return distances;

}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{

    vector<int> path;

    if(distances[destination] == INF)
    {
        return path;
    }

    int curr = destination;
    while(curr != -1)
    {
        path.push_back(curr);
        curr = previous[curr];
    }

    reverse(path.begin(), path.end());

    return path;

}

void print_path(const vector<int>& v, int total)
{
    if(v.empty())
    {
        cout << "No path exists" << endl;
        return;
    }

    cout << "Path (cost " << total << "): ";
    for(size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i];
        if(i < v.size() - 1)
        { 
            cout << " ";
        }
    }

    cout << " " << endl;
    cout << "Total cost is " << total << endl;
}