#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void topologicalSort(vector<vector<int>>& adj, int V) {
    vector<int> indegree(V, 0);
    for (int i = 0; i < V; i++)
        for (int node : adj[i])
            indegree[node]++;

    queue<int> q;
    for (int i = 0; i < V; i++)
        if (indegree[i] == 0)
            q.push(i);

    cout << "Topological Order: ";
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";
        for (int node : adj[curr]) {
            indegree[node]--;
            if (indegree[node] == 0)
                q.push(node);
        }
    }
    cout << endl;
}

void bfsTraversal(vector<vector<int>>& adj, int V, int start) {
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";
        for (int node : adj[curr]) {
            if (!visited[node]) {
                visited[node] = true;
                q.push(node);
            }
        }
    }
    cout << endl;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> adj(V);
    cout << "Enter directed edges (from to):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    topologicalSort(adj, V);

    int start;
    cout << "Enter start vertex for BFS: ";
    cin >> start;
    bfsTraversal(adj, V, start);

    return 0;
}
/*Enter number of vertices and edges: 6 6
Enter directed edges (from to):
0 1
0 2
1 3
1 4
2 4
3 5

Enter start vertex for BFS: 0
*/