#include <bits/stdc++.h>
using namespace std;

// Topological Sort using DFS
void topo_sort(vector<vector<int>>& adj, stack<int>& s1, vector<bool>& visited, int node) {
    if (visited[node]) {
        return;
    }
    visited[node] = true;
    
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            topo_sort(adj, s1, visited, neighbor);
        }
    }

    // Push the node to stack after visiting all neighbors
    s1.push(node);
}

// Topological Sort using Kahn's Algorithm (BFS approach)
void topo_sort_bfs(vector<vector<int>>& adj, vector<int>& indegree, vector<int>& result) {
    queue<int> q;
    for (int i = 0; i < adj.size(); i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);

        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
}

// DFS Traversal for a Directed Acyclic Graph (DAG)
void dfs(vector<vector<int>>& adj, vector<bool>& visited, int node) {
    visited[node] = true;
    cout << node << " ";

    // Recur for all the vertices adjacent to this vertex
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(adj, visited, neighbor);
        }
    }
}

int main() {
    int u, v;
    cout << "Enter the number of edges and vertices:\n";
    cin >> u >> v;

    vector<vector<int>> adj(v);
    vector<int> indegree(v, 0);

    cout << "Enter the edges (u, v):\n";
    for (int i = 0; i < u; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        indegree[y]++;  // Update indegree of the destination vertex
    }

    int choice;
    cout << "Menu:\n1. Toposort using DFS\n2. Toposort using BFS (Kahn's Algorithm)\n3. DFS Traversal\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        // Topological Sort using DFS
        stack<int> s1;
        vector<bool> visited(v, false);

        for (int i = 0; i < v; i++) {
            if (!visited[i]) {
                topo_sort(adj, s1, visited, i);
            }
        }

        cout << "Topological Sort using DFS: \n";
        while (!s1.empty()) {
            cout << s1.top() << " ";
            s1.pop();
        }
        cout << endl;
    } else if (choice == 2) {
        // Topological Sort using BFS (Kahn's Algorithm)
        vector<int> result;
        topo_sort_bfs(adj, indegree, result);

        cout << "Topological Sort using BFS (Kahn's Algorithm): \n";
        for (int node : result) {
            cout << node << " ";
        }
        cout << endl;
    } else if (choice == 3) {
        // DFS Traversal
        vector<bool> visited(v, false);
        cout << "DFS Traversal starting from all unvisited nodes:\n";
        for (int i = 0; i < v; i++) {
            if (!visited[i]) {
                dfs(adj, visited, i);
                cout << endl;
            }
        }
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
/*Enter the number of edges and vertices:
6 6
Enter the edges (u, v):
5 2
5 0
4 0
4 1
2 3
3 1
Menu:
1. Toposort using DFS
2. Toposort using BFS (Kahn's Algorithm)
3. DFS Traversal
Enter your choice: 1


DFS Traversal starting from all unvisited nodes:
5 2 3 1 4 0 
*/