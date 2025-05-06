#include <iostream>
#include <stack>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void nonRecursiveInorder(Node* root) {
    stack<Node*> st;
    Node* curr = root;
    while (curr || !st.empty()) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top(); st.pop();
        cout << curr->data << " ";
        curr = curr->right;
    }
}

bool isEqual(Node* t1, Node* t2) {
    if (!t1 && !t2) return true;
    if (!t1 || !t2) return false;
    return (t1->data == t2->data) &&
           isEqual(t1->left, t2->left) &&
           isEqual(t1->right, t2->right);
}

int main() {
    Node *root1 = NULL, *root2 = NULL;
    int choice, val, n;
    cout << "Binary Search Tree Operations\n";
    cout << "1. Insert into Tree 1\n2. Insert into Tree 2\n3. Inorder (Tree 1)\n4. Preorder (Tree 1)\n5. Postorder (Tree 1)\n";
    cout << "6. Non-Recursive Inorder (Tree 1)\n7. Check if both trees are equal\n0. Exit\n";

    do {
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                cout << "Enter number of nodes to insert in Tree 1: ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    cout << "Enter value: ";
                    cin >> val;
                    root1 = insert(root1, val);
                }
                break;
            case 2:
                cout << "Enter number of nodes to insert in Tree 2: ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    cout << "Enter value: ";
                    cin >> val;
                    root2 = insert(root2, val);
                }
                break;
            case 3:
                cout << "Inorder (Tree 1): ";
                inorder(root1);
                cout << endl;
                break;
            case 4:
                cout << "Preorder (Tree 1): ";
                preorder(root1);
                cout << endl;
                break;
            case 5:
                cout << "Postorder (Tree 1): ";
                postorder(root1);
                cout << endl;
                break;
            case 6:
                cout << "Non-recursive Inorder (Tree 1): ";
                nonRecursiveInorder(root1);
                cout << endl;
                break;
            case 7:
                if (isEqual(root1, root2))
                    cout << "Both BSTs are equal.\n";
                else
                    cout << "BSTs are not equal.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
/*Binary Search Tree Operations
1. Insert into Tree 1
2. Insert into Tree 2
3. Inorder (Tree 1)
4. Preorder (Tree 1)
5. Postorder (Tree 1)
6. Non-Recursive Inorder (Tree 1)
7. Check if both trees are equal
0. Exit

Enter your choice: 1
Enter number of nodes to insert in Tree 1: 3
Enter value: 10
Enter value: 5
Enter value: 15

Enter your choice: 2
Enter number of nodes to insert in Tree 2: 3
Enter value: 10
Enter value: 5
Enter value: 15

Enter your choice: 3
Inorder (Tree 1): 5 10 15

Enter your choice: 4
Preorder (Tree 1): 10 5 15

Enter your choice: 5
Postorder (Tree 1): 5 15 10

Enter your choice: 6
Non-recursive Inorder (Tree 1): 5 10 15

Enter your choice: 7
Both BSTs are equal.

Enter your choice: 0
*/