// Problem 6: Insert, all traversals (recursive and non-recursive), delete a node
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

Node* minValueNode(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
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
    int choice, val;

    do {
        cout << "\n=== BST MENU (Problem 6) ===\n";
        cout << "1. Insert\n2. Inorder\n3. Preorder\n4. Postorder\n";
        cout << "5. Non-Recursive Inorder\n6. Delete a Node\n7. Exit\n";
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
                cout << "Enter value to delete: ";
                cin >> val;
                root = deleteNode(root, val);
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    deleteTree(root);
    return 0;
}
/*=== BST MENU (Problem 6) ===
1. Insert
2. Inorder
3. Preorder
4. Postorder
5. Non-Recursive Inorder
6. Delete a Node
7. Exit
Enter choice: 1
Enter values to insert (-1 to stop): 50 30 70 20 40 60 80 -1

Tree built with values: 50 30 70 20 40 60 80

Enter choice: 2
Inorder: 20 30 40 50 60 70 80

Enter choice: 3
Preorder: 50 30 20 40 70 60 80

Enter choice: 4
Postorder: 20 40 30 60 80 70 50

Enter choice: 5
Non-Recursive Inorder: 20 30 40 50 60 70 80

Enter choice: 6
Enter value to delete: 30

Tree after deleting 30:
          50
         /  \
        40   70
       /     /  \
      20    60   80

Enter choice: 2
Inorder: 20 40 50 60 70 80

Enter choice: 7
Exiting...
*/