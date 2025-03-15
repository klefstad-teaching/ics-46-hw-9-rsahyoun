#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int numVertices = G.numVertices;

    vector<int> distances(numVertices, INF);
    previous.resize(numVertices, -1);
    vector<bool> visited(numVertices, false);

    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    
    minHeap.push({0, source});

    while(!minHeap.empty())
    {
        int dist = minHeap.top().first;
        int u = minHeap.top().second;

        minHeap.pop();

        if(visited[u])
        {
            continue;
        }

        visited[u] = true;

        for(const Edge& edge : G[u])
        {
            int v = edge.dst;
            int weight = edge.weight;

            if(!visited[v] && distances[u] != INF && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }

        }
    }

    return distances;

}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    vector<int> path;

    for(int current = destination; current != -1; current = previous[current])
    {
        path.push_back(current);
    }

    reverse(path.begin(), path.end());
    return path;

}

void print_path(const vector<int>& v, int total)
{

    if (v.empty() && total > 0) {
        cout << endl;
        cout << "Total cost is " << total << endl;
        return;
    }

    if (v.empty()) 
    {
        cout << "No path exists" << endl;
        return;
    }
    
    for (size_t i = 0; i < v.size(); ++i) 
    {
        cout << v[i];
        if (i < v.size() - 1) {
            cout << " ";
        }
    }
    cout << " " << endl;
    cout << "Total cost is " << total << endl;
}