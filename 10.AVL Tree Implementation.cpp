#include <iostream>
using namespace std;

struct Node {
    int data, height;
    Node *left, *right;

    Node(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

int height(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node; // No duplicates

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->data)
        return rightRotate(node);
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int treeHeight(Node* root) {
    return height(root);
}

int main() {
    Node* root = nullptr;
    int choice, val;

    do {
        cout << "\n=== AVL Tree Menu ===\n";
        cout << "1. Insert\n2. Inorder Traversal\n3. Print Height\n0. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                root = insert(root, val);
                break;
            case 2:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 3:
                cout << "Height of AVL Tree: " << treeHeight(root) << endl;
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}

/*=== AVL Tree Menu ===
1. Insert
2. Inorder Traversal
3. Print Height
0. Exit
Enter choice: 1
Enter value: 10

=== AVL Tree Menu ===
1. Insert
2. Inorder Traversal
3. Print Height
0. Exit
Enter choice: 1
Enter value: 20

=== AVL Tree Menu ===
1. Insert
2. Inorder Traversal
3. Print Height
0. Exit
Enter choice: 1
Enter value: 30

=== AVL Tree Menu ===
1. Insert
2. Inorder Traversal
3. Print Height
0. Exit
Enter choice: 2
Inorder Traversal: 10 20 30 

=== AVL Tree Menu ===
1. Insert
2. Inorder Traversal
3. Print Height
0. Exit
Enter choice: 3
Height of AVL Tree: 2

=== AVL Tree Menu ===
1. Insert
2. Inorder Traversal
3. Print Height
0. Exit
Enter choice: 0
*/