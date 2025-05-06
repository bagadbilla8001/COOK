// Problem 5: Insert, all traversals (recursive and non-recursive), build from inorder and preorder
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

int search(int inorder[], int start, int end, int val) {
    for (int i = start; i <= end; i++)
        if (inorder[i] == val) return i;
    return -1;
}

Node* buildTree(int inorder[], int preorder[], int inStart, int inEnd, int& preIndex) {
    if (inStart > inEnd) return nullptr;
    int rootVal = preorder[preIndex++];
    Node* root = new Node(rootVal);
    int inIndex = search(inorder, inStart, inEnd, rootVal);
    root->left = buildTree(inorder, preorder, inStart, inIndex - 1, preIndex);
    root->right = buildTree(inorder, preorder, inIndex + 1, inEnd, preIndex);
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
        cout << "\n=== BST MENU (Problem 5) ===\n";
        cout << "1. Insert\n2. Inorder\n3. Preorder\n4. Postorder\n";
        cout << "5. Non-Recursive Inorder\n6. Build from Inorder & Preorder\n7. Exit\n";
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
            case 6: {
                int n;
                cout << "Enter number of nodes: ";
                cin >> n;
                int inorderArr[n], preorderArr[n];
                cout << "Enter inorder: ";
                for (int i = 0; i < n; i++) cin >> inorderArr[i];
                cout << "Enter preorder: ";
                for (int i = 0; i < n; i++) cin >> preorderArr[i];
                int preIndex = 0;
                deleteTree(root); // clear old tree
                root = buildTree(inorderArr, preorderArr, 0, n - 1, preIndex);
                cout << "Tree built. Inorder: "; inorder(root); cout << endl;
                break;
            }
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
/*=== BST MENU (Problem 5) ===
1. Insert
2. Inorder
3. Preorder
4. Postorder
5. Non-Recursive Inorder
6. Build from Inorder & Preorder
7. Exit
Enter choice: 1
Enter values to insert (-1 to stop): 40 20 10 30 60 50 70 -1

=== BST MENU (Problem 5) ===
Enter choice: 2
Inorder: 10 20 30 40 50 60 70 

=== BST MENU (Problem 5) ===
Enter choice: 3
Preorder: 40 20 10 30 60 50 70 

=== BST MENU (Problem 5) ===
Enter choice: 4
Postorder: 10 30 20 50 70 60 40 

=== BST MENU (Problem 5) ===
Enter choice: 5
Non-Recursive Inorder: 10 20 30 40 50 60 70 

=== BST MENU (Problem 5) ===
Enter choice: 6
Enter number of nodes: 7
Enter inorder: 10 20 30 40 50 60 70
Enter preorder: 40 20 10 30 60 50 70
Tree built. Inorder: 10 20 30 40 50 60 70 

=== BST MENU (Problem 5) ===
Enter choice: 7
Exiting...
*/
