// Problem 4: Insert, all traversals, height, mirror image
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

int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

Node* mirror(Node* root) {
    if (!root) return nullptr;
    Node* mirrored = new Node(root->data);
    mirrored->left = mirror(root->right);
    mirrored->right = mirror(root->left);
    return mirrored;
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
    Node* mirrored = nullptr;
    int choice, val;

    do {
        cout << "\n=== BST MENU (Problem 4) ===\n";
        cout << "1. Insert\n2. Inorder\n3. Preorder\n4. Postorder\n";
        cout << "5. Non-Recursive Inorder\n6. Height\n7. Mirror Tree\n8. Exit\n";
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
                cout << "Height of Tree: " << height(root) << endl;
                break;
            case 7:
                mirrored = mirror(root);
                cout << "Mirror tree created. Inorder of mirror: "; inorder(mirrored); cout << endl;
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    deleteTree(root);
    deleteTree(mirrored);
    return 0;
}
/*=== BST MENU (Problem 4) ===
1. Insert
2. Inorder
3. Preorder
4. Postorder
5. Non-Recursive Inorder
6. Height
7. Mirror Tree
8. Exit
Enter choice: 1
Enter values to insert (-1 to stop): 40 20 60 10 30 50 70 -1

=== BST MENU (Problem 4) ===
Enter choice: 2
Inorder: 10 20 30 40 50 60 70 

=== BST MENU (Problem 4) ===
Enter choice: 3
Preorder: 40 20 10 30 60 50 70 

=== BST MENU (Problem 4) ===
Enter choice: 4
Postorder: 10 30 20 50 70 60 40 

=== BST MENU (Problem 4) ===
Enter choice: 5
Non-Recursive Inorder: 10 20 30 40 50 60 70 

=== BST MENU (Problem 4) ===
Enter choice: 6
Height of Tree: 3

=== BST MENU (Problem 4) ===
Enter choice: 7
Mirror tree created. Inorder of mirror: 70 60 50 40 30 20 10 

=== BST MENU (Problem 4) ===
Enter choice: 8
Exiting...
*/

