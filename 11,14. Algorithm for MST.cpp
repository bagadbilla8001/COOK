#include <bits/stdc++.h>
using namespace std;

// Using set for Prim's algorithm (MST)
void prims_algo_set(vector<vector<pair<int,int>>>& adj, vector<bool>& visited, vector<int>& mst_nodes, int &cost, vector<int>& parent) {
    set<pair<int, int>> s1;  // {weight, node}
    s1.insert({0, 0});
    cost = 0;
    
    while (!s1.empty()) {
        auto it = s1.begin();
        int node = it->second;
        int wt = it->first;
        s1.erase(it);
        
        if (!visited[node]) {
            cost += wt;
            mst_nodes.push_back(node);
            visited[node] = true;
            
            for (auto& neighbor : adj[node]) {
                int adj_node = neighbor.first;
                int edge_wt = neighbor.second;
                if (!visited[adj_node]) {
                    s1.insert({edge_wt, adj_node});
                    parent[adj_node] = node;
                }
            }
        }
    }
}

// Find parent in Kruskal's algorithm (Union-Find)
int find_parent(vector<int>& parent, int u) {
    if (parent[u] != u) {
        parent[u] = find_parent(parent, parent[u]);
    }
    return parent[u];
}

// Union by rank for Kruskal's algorithm (Union-Find)
bool union_by_rank(int u, int v, vector<int>& parent, vector<int>& rank) {
    int pu = find_parent(parent, u);
    int pv = find_parent(parent, v);
    if (pu == pv) {
        return false;
    }
    if (rank[pu] > rank[pv]) {
        parent[pv] = pu;
    } else if (rank[pu] < rank[pv]) {
        parent[pu] = pv;
    } else {
        parent[pu] = pv;
        rank[pv]++;
    }
    return true;
}

// Using Kruskal's algorithm (MST)
void kruskal_algo(vector<vector<pair<int, int>>>& adj, vector<pair<int, int>>& mst_edges, int& cost, vector<int>& parent, vector<int>& rank) {
    vector<pair<int, pair<int, int>>> edges; // {weight, {u, v}}
    
    for (int u = 0; u < adj.size(); u++) {
        for (auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int wt = neighbor.second;
            if (u < v) { // To avoid duplicate edges in undirected graph
                edges.push_back({wt, {u, v}});
            }
        }
    }
    
    // Sort edges by weight
    sort(edges.begin(), edges.end());
    
    cost = 0;
    for (auto& edge : edges) {
        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        
        if (union_by_rank(u, v, parent, rank)) {
            mst_edges.push_back({u, v});
            cost += wt;
            if (mst_edges.size() == adj.size() - 1) break;
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

    vector<vector<pair<int, int>>> adj(num_vertices);
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

    int choice;
    cout << "\nChoose the algorithm:\n";
    cout << "1. Prim's Algorithm\n";
    cout << "2. Kruskal's Algorithm\n";
    cout << "Enter your choice: ";
    cin >> choice;
    
    if (choice == 1) {
        vector<bool> visited(num_vertices, false);
        vector<int> mst_nodes;
        vector<int> parent(num_vertices, -1);
        int cost = 0;
        
        prims_algo_set(adj, visited, mst_nodes, cost, parent);
        
        cout << "The cost of the MST is: " << cost << endl;
        cout << "The MST nodes in order of addition: ";
        for (auto node : mst_nodes) {
            cout << node << " ";
        }
        cout << endl;
        
        cout << "Parent relationships:\n";
        for (int i = 0; i < num_vertices; i++) {
            cout << i << " -> " << parent[i] << endl;
        }
    }
    else if (choice == 2) {
        vector<pair<int, int>> mst_edges;
        int cost = 0;
        vector<int> parent(num_vertices);
        vector<int> rank(num_vertices, 0);
        
        for (int i = 0; i < num_vertices; i++) {
            parent[i] = i;
        }
        
        kruskal_algo(adj, mst_edges, cost, parent, rank);
        
        cout << "The cost of the MST is: " << cost << endl;
        cout << "The MST edges are:\n";
        for (auto& edge : mst_edges) {
            cout << edge.first << " - " << edge.second << endl;
        }
    }
    else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

/*Enter the number of edges and vertices:
5 4
Enter the edges and their weights (u v weight):
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4

Choose the algorithm:
1. Prim's Algorithm
2. Kruskal's Algorithm
Enter your choice: 1
*/