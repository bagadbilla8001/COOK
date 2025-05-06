#include <bits/stdc++.h>
using namespace std;

// Dijkstra's algorithm using priority queue (min-heap)
void dijkstra(vector<vector<pair<int,int>>>& adj, vector<bool>& visited, vector<int>& dist, int source, vector<int>& parent) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, source});
    dist[source] = 0;
    
    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();
        
        if (visited[node]) continue;
        visited[node] = true;
        
        for (auto& neighbor : adj[node]) {
            int adj_node = neighbor.first;
            int edge_weight = neighbor.second;
            
            if (!visited[adj_node] && dist[node] + edge_weight < dist[adj_node]) {
                dist[adj_node] = dist[node] + edge_weight;
                parent[adj_node] = node;
                pq.push({dist[adj_node], adj_node});
            }
        }
    }
}

int main() {
    int num_edges, num_vertices;
    cout << "Enter the number of edges and vertices:\n";
    cin >> num_edges >> num_vertices;
    
    if (num_vertices <= 0) {
        cout << "Invalid number of vertices.\n";
        return 0;
    }
    if (num_edges < 0) {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    vector<vector<pair<int,int>>> adj(num_vertices);
    cout << "Enter the edges and their weights (u v weight):\n";
    
    for (int i = 0; i < num_edges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;

        if (u < 0 || u >= num_vertices || v < 0 || v >= num_vertices) {
            cout << "Invalid vertex number(s) in edge " << i + 1 << ".\n";
            return 0;
        }

        if (weight <= 0) {
            cout << "Invalid weight for edge " << i + 1 << ". Weight must be greater than zero.\n";
            return 0;
        }

        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    int source;
    cout << "Enter the source vertex:\n";
    cin >> source;
    
    if (source < 0 || source >= num_vertices) {
        cout << "Invalid source vertex.\n";
        return 0;
    }

    vector<bool> visited(num_vertices, false);
    vector<int> dist(num_vertices, INT_MAX);
    vector<int> parent(num_vertices, -1);
    
    dijkstra(adj, visited, dist, source, parent);

    // Print shortest distances
    cout << "Shortest distances from source " << source << ":\n";
    for (int i = 0; i < num_vertices; i++) {
        cout << "Vertex " << i << ": ";
        if (dist[i] == INT_MAX) {
            cout << "Unreachable";
        } else {
            cout << dist[i];
        }
        cout << endl;
    }

    // Print shortest paths
    cout << "\nShortest paths from source " << source << ":\n";
    for (int i = 0; i < num_vertices; i++) {
        if (i == source) continue;
        
        cout << "Path to " << i << ": ";
        if (dist[i] == INT_MAX) {
            cout << "No path exists";
        } else {
            vector<int> path;
            int current = i;
            while (current != source) {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(source);
            reverse(path.begin(), path.end());
            
            for (int j = 0; j < path.size(); j++) {
                cout << path[j];
                if (j != path.size() - 1) {
                    cout << " -> ";
                }
            }
        }
        cout << endl;
    }

    return 0;
}
/*Enter the number of edges and vertices:
6 5
Enter the edges and their weights (u v weight):
0 1 10
0 2 5
1 2 2
1 3 1
2 3 9
3 4 4

Enter the source vertex:
0


Shortest distances from source 0:
Vertex 0: 0
Vertex 1: 7
Vertex 2: 5
Vertex 3: 8
Vertex 4: 12

Shortest paths from source 0:
Path to 1: 0 -> 2 -> 1
Path to 2: 0 -> 2
Path to 3: 0 -> 2 -> 1 -> 3
Path to 4: 0 -> 2 -> 1 -> 3 -> 4
*/