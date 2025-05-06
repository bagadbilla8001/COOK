// Problem 7: Threaded BST - Insert and Inorder Traversal
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool lthread, rthread;
    Node(int val) : data(val), left(nullptr), right(nullptr), lthread(true), rthread(true) {}
};

class ThreadedBST {
    Node *root;

    Node* leftMost(Node* node) {
        if (!node) return nullptr;
        while (!node->lthread) node = node->left;
        return node;
    }

public:
    ThreadedBST() : root(nullptr) {}

    void insert(int key) {
        if (!root) {
            root = new Node(key);
            return;
        }

        Node *curr = root, *parent = nullptr;
        while (curr) {
            if (key == curr->data) return;
            parent = curr;
            if (key < curr->data) {
                if (!curr->lthread) curr = curr->left;
                else break;
            } else {
                if (!curr->rthread) curr = curr->right;
                else break;
            }
        }

        Node *newNode = new Node(key);
        if (key < parent->data) {
            newNode->left = parent->left;
            newNode->right = parent;
            parent->lthread = false;
            parent->left = newNode;
        } else {
            newNode->right = parent->right;
            newNode->left = parent;
            parent->rthread = false;
            parent->right = newNode;
        }
    }

    void inorder() {
        Node* curr = leftMost(root);
        while (curr) {
            cout << curr->data << " ";
            if (curr->rthread) curr = curr->right;
            else curr = leftMost(curr->right);
        }
        cout << endl;
    }
};

int main2() {
    ThreadedBST tbst;
    int choice, val;
    do {
        cout << "\n=== Threaded BST Menu (Problem 7) ===\n";
        cout << "1. Insert\n2. Inorder Traversal\n0. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value: "; cin >> val;
                tbst.insert(val);
                break;
            case 2:
                cout << "Inorder: "; tbst.inorder();
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}

// Problem 8: Convert Normal BST to Threaded BST and Inorder Traversal
#include <iostream>
using namespace std;

struct TNode {
    int data;
    TNode *left, *right;
    bool lthread, rthread;
    TNode(int val) : data(val), left(nullptr), right(nullptr), lthread(false), rthread(false) {}
};

class ThreadedConverter {
    TNode* root;

    void convertUtil(TNode* curr, TNode*& prev) {
        if (!curr) return;
        convertUtil(curr->left, prev);
        if (!curr->left) {
            curr->left = prev;
            curr->lthread = true;
        }
        if (prev && !prev->right) {
            prev->right = curr;
            prev->rthread = true;
        }
        prev = curr;
        convertUtil(curr->right, prev);
    }

    TNode* leftMost(TNode* node) {
        while (node && !node->lthread) node = node->left;
        return node;
    }

public:
    ThreadedConverter() : root(nullptr) {}

    void insert(TNode*& node, int val) {
        if (!node) {
            node = new TNode(val);
            return;
        }
        if (val < node->data) insert(node->left, val);
        else if (val > node->data) insert(node->right, val);
    }

    void convert() {
        TNode* prev = nullptr;
        convertUtil(root, prev);
    }

    void inorder() {
        TNode* curr = leftMost(root);
        while (curr) {
            cout << curr->data << " ";
            if (curr->rthread) curr = curr->right;
            else curr = leftMost(curr->right);
        }
        cout << endl;
    }

    void insertNode(int val) {
        insert(root, val);
    }
};

int main() {
    ThreadedConverter bst;
    int choice, val;
    do {
        cout << "\n=== Convert BST to Threaded BST Menu (Problem 8) ===\n";
        cout << "1. Insert in Normal BST\n2. Convert to Threaded BST\n3. Inorder Traversal\n0. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value: "; cin >> val;
                bst.insertNode(val);
                break;
            case 2:
                bst.convert();
                cout << "Converted to Threaded BST.\n";
                break;
            case 3:
                cout << "Inorder: "; bst.inorder();
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
/*=== Threaded BST Menu (Problem 7) ===
1. Insert
2. Inorder Traversal
0. Exit
Enter choice: 1
Enter value: 10
=== Threaded BST Menu (Problem 7) ===
1. Insert
2. Inorder Traversal
0. Exit
Enter choice: 1
Enter value: 20
=== Threaded BST Menu (Problem 7) ===
1. Insert
2. Inorder Traversal
0. Exit
Enter choice: 1
Enter value: 5
=== Threaded BST Menu (Problem 7) ===
1. Insert
2. Inorder Traversal
0. Exit
Enter choice: 2
Inorder Traversal: 5 10 20
=== Threaded BST Menu (Problem 7) ===
1. Insert
2. Inorder Traversal
0. Exit
Enter choice: 0
Exiting...
*/