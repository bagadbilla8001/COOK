#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    char c;
    int freq;
    Node *left, *right;

    Node(char ch, int f) : c(ch), freq(f), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) : c('#'), freq(l->freq + r->freq), left(l), right(r) {}
};

// Custom comparator for min-heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Recursive function to generate Huffman codes
void generateCodes(Node* root, string code, map<char, string>& codes) {
    if (!root) return;
    if (root->c != '#') {
        codes[root->c] = code;
    }
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    map<char, int> freqMap;
    while (n--) {
        char ch;
        int freq;
        cout << "Enter character and frequency: ";
        cin >> ch >> freq;
        freqMap[ch] = freq;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        pq.push(new Node(left, right));
    }

    Node* root = pq.top();
    map<char, string> codes;
    generateCodes(root, "", codes);

    char query;
    cout << "Enter a character to get Huffman code (or ! to print all): ";
    cin >> query;

    if (query == '!') {
        for (auto& pair : codes) {
            cout << pair.first << " -> " << pair.second << endl;
        }
    } else {
        if (codes.count(query))
            cout << query << " -> " << codes[query] << endl;
        else
            cout << "Character not found!" << endl;
    }

    return 0;
}
/*Enter number of characters: 4
Enter character and frequency: a 5
Enter character and frequency: b 9
Enter character and frequency: c 12
Enter character and frequency: d 13
Enter a character to get Huffman code (or ! to print all): !
*/