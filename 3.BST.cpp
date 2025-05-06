// Problem 3: Insert, all traversals, clone, delete original tree
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

void nonRecursiveInorder(Node* root) {
    stack<Node*> s;
    Node* curr = root;
    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top(); s.pop();
        cout << curr->data << " ";
        curr = curr->right;
    }
}

Node* clone(Node* root) {
    if (!root) return nullptr;
    Node* newNode = new Node(root->data);
    newNode->left = clone(root->left);
    newNode->right = clone(root->right);
    return newNode;
}

void deleteTree(Node*& root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
}

int main() {
    Node* root = nullptr;
    Node* cloned = nullptr;
    int choice, val;

    do {
        cout << "\n=== BST MENU (Problem 3) ===\n";
        cout << "1. Insert\n2. Inorder\n3. Preorder\n4. Postorder\n";
        cout << "5. Non-Recursive Inorder\n6. Clone Tree\n7. Delete Original Tree\n8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter values to insert (-1 to stop): ";
                while (true) {
                    cin >> val;
                    if (val == -1) break;
                    root = insert(root, val);
                }
                break;
            case 2:
                cout << "Inorder: "; inorder(root); cout << endl;
                break;
            case 3:
                cout << "Preorder: "; preorder(root); cout << endl;
                break;
            case 4:
                cout << "Postorder: "; postorder(root); cout << endl;
                break;
            case 5:
                cout << "Non-Recursive Inorder: "; nonRecursiveInorder(root); cout << endl;
                break;
            case 6:
                cloned = clone(root);
                cout << "Tree cloned. Inorder of clone: "; inorder(cloned); cout << endl;
                break;
            case 7:
                deleteTree(root);
                cout << "Original tree deleted.\n";
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    deleteTree(root);
    deleteTree(cloned);
    return 0;
}

/*
=== BST MENU (Problem 3) ===
1. Insert
2. Inorder
3. Preorder
4. Postorder
5. Non-Recursive Inorder
6. Clone Tree
7. Delete Original Tree
8. Exit
Enter choice: 1
Enter values to insert (-1 to stop): 50 30 70 20 40 60 80 -1

=== BST MENU (Problem 3) ===
1. Insert
2. Inorder
3. Preorder
4. Postorder
5. Non-Recursive Inorder
6. Clone Tree
7. Delete Original Tree
8. Exit
Enter choice: 2
Inorder: 20 30 40 50 60 70 80 

=== BST MENU (Problem 3) ===
Enter choice: 3
Preorder: 50 30 20 40 70 60 80 

=== BST MENU (Problem 3) ===
Enter choice: 4
Postorder: 20 40 30 60 80 70 50 

=== BST MENU (Problem 3) ===
Enter choice: 5
Non-Recursive Inorder: 20 30 40 50 60 70 80 

=== BST MENU (Problem 3) ===
Enter choice: 6
Tree cloned. Inorder of clone: 20 30 40 50 60 70 80 

=== BST MENU (Problem 3) ===
Enter choice: 7
Original tree deleted.

=== BST MENU (Problem 3) ===
Enter choice: 2
Inorder: 

=== BST MENU (Problem 3) ===
Enter choice: 8
Exiting...
*/