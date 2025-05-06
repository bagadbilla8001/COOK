#include <iostream>
#include <list>
#include <string>
using namespace std;

const int TABLE_SIZE = 26; // hash by first letter

class HashTable {
    list<string> table[TABLE_SIZE];

    int hashFunction(string word) {
        return word[0] - 'a';
    }

public:
    void insert(string word) {
        int index = hashFunction(word);
        table[index].push_back(word);
    }

    bool search(string word) {
        int index = hashFunction(word);
        for (auto& w : table[index]) {
            if (w == word)
                return true;
        }
        return false;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << " => ";
            for (auto& word : table[i])
                cout << word << " -> ";
            cout << "NULL\n";
        }
    }
};

int main() {
    HashTable ht;
    int n;
    cout << "Enter number of words (at least 20): ";
    cin >> n;

    cout << "Enter " << n << " lowercase correctly spelled words:\n";
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        ht.insert(word);
    }

    cout << "\nEnter words to check spelling (type 'exit' to stop):\n";
    string check;
    while (true) {
        cout << "Check word: ";
        cin >> check;
        if (check == "exit") break;

        if (ht.search(check))
            cout << check << " is spelled correctly \n";
        else
            cout << check << " is NOT found \n";
    }

    return 0;
}

/*Enter number of words (at least 20): 20
Enter 20 lowercase correctly spelled words:
apple
banana
grape
orange
kiwi
mango
pear
plum
peach
melon
lemon
lime
berry
date
fig
guava
papaya
apricot
cherry
nectarine

Enter words to check spelling (type 'exit' to stop):
Check word: apple
apple is spelled correctly 
Check word: banana
banana is spelled correctly 
Check word: watermelon
watermelon is NOT found 
Check word: cherry
cherry is spelled correctly 
Check word: lychee
lychee is NOT found 
Check word: exit
*/