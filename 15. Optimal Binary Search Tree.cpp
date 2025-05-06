#include <bits/stdc++.h>
using namespace std;
#define MAX 50

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* construct(int r[][MAX], int i, int j) {
    if (i > j || !r[i][j]) return nullptr;
    Node* root = new Node(r[i][j]);
    root->left = construct(r, i, r[i][j] - 1);
    root->right = construct(r, r[i][j] + 1, j);
    return root;
}

Node* optimalbst(int p[], int q[], int n) {
    int w[MAX][MAX], c[MAX][MAX], r[MAX][MAX];

    // Initialize all entries to 0
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            w[i][j] = c[i][j] = r[i][j] = 0;
        }
    }

    // Base case: single node (keys are from 1 to n)
    for (int i = 1; i <= n; i++) {
        w[i][i] = q[i - 1] + p[i] + q[i];
        c[i][i] = w[i][i];
        r[i][i] = i;
    }

    // Fill DP tables for subtrees of size 2 to n
    for (int sz = 2; sz <= n; sz++) {
        for (int i = 1; i + sz - 1 <= n; i++) {
            int j = i + sz - 1;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            c[i][j] = INT_MAX;

            // Try all possible roots between i and j
            for (int k = i; k <= j; k++) {
                int cost = w[i][j] + (k > i ? c[i][k - 1] : 0) + (k < j ? c[k + 1][j] : 0);
                if (cost < c[i][j]) {
                    c[i][j] = cost;
                    r[i][j] = k;
                }
            }
        }
    }

    cout << "Cost of optimal BST is: " << c[1][n] << endl;
    return construct(r, 1, n);
}

void preorder(string words[], Node* node) {
    if (!node) return;
    cout << words[node->data] << " ";
    preorder(words, node->left);
    preorder(words, node->right);
}

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    string words[n + 1];  // 1-based indexing
    cout << "Enter the keys (words):\n";
    for (int i = 1; i <= n; i++) {
        cin >> words[i];
    }

    int p[n + 1];  // p[1..n]
    cout << "Enter probabilities for keys (p[1..n]):\n";
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    int q[n + 1];  // q[0..n]
    cout << "Enter probabilities for dummy keys (q[0..n]):\n";
    for (int i = 0; i <= n; i++) {
        cin >> q[i];
    }

    Node* root = optimalbst(p, q, n);
    cout << "Preorder traversal of the optimal BST:\n";
    preorder(words, root);
    cout << endl;

    return 0;
}
/*Enter the number of keys: 4
Enter the keys (words):
apple banana cherry date
Enter probabilities for keys (p[1..n]):
3 2 6 4
Enter probabilities for dummy keys (q[0..n]):
2 1 2 3 1

Cost of optimal BST is: 28
Preorder traversal of the optimal BST:
banana apple cherry date
*/