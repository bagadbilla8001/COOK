#include <iostream>
using namespace std;

const int TABLE_SIZE = 10;

struct Student {
    int pnr;
    int marks;
    bool occupied;

    Student() : pnr(-1), marks(0), occupied(false) {}
};

class HashTable {
    Student table[TABLE_SIZE];

    int hash(int pnr) {
        return pnr % TABLE_SIZE;
    }

public:
    void insert(int pnr, int marks) {
        int index = hash(pnr);

        if (!table[index].occupied) {
            table[index].pnr = pnr;
            table[index].marks = marks;
            table[index].occupied = true;
            return;
        }

        // Collision occurred
        int existingIndex = hash(table[index].pnr);
        if (existingIndex != index) {
            // Replace and reinsert existing entry
            Student temp = table[index];
            table[index].pnr = pnr;
            table[index].marks = marks;

            // Reinsert replaced entry
            for (int i = 1; i < TABLE_SIZE; i++) {
                int newIndex = (index + i) % TABLE_SIZE;
                if (!table[newIndex].occupied) {
                    table[newIndex] = temp;
                    table[newIndex].occupied = true;
                    return;
                }
            }
        } else {
            // Linear probing without replacement
            for (int i = 1; i < TABLE_SIZE; i++) {
                int newIndex = (index + i) % TABLE_SIZE;
                if (!table[newIndex].occupied) {
                    table[newIndex].pnr = pnr;
                    table[newIndex].marks = marks;
                    table[newIndex].occupied = true;
                    return;
                }
            }
        }

        cout << "Hash table full. Couldn't insert.\n";
    }

    void search(int pnr) {
        int index = hash(pnr);
        for (int i = 0; i < TABLE_SIZE; i++) {
            int curr = (index + i) % TABLE_SIZE;
            if (table[curr].occupied && table[curr].pnr == pnr) {
                cout << "PNR: " << pnr << ", Marks: " << table[curr].marks << endl;
                return;
            }
        }
        cout << "PNR not found.\n";
    }

    void display() {
        cout << "Hash Table:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].occupied)
                cout << i << ": PNR " << table[i].pnr << ", Marks " << table[i].marks << endl;
            else
                cout << i << ": Empty\n";
        }
    }
};

int main() {
    HashTable ht;
    int choice, pnr, marks;

    do {
        cout << "\nMenu:\n1. Insert\n2. Search\n3. Display\n0. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter PNR: ";
                cin >> pnr;
                cout << "Enter Marks: ";
                cin >> marks;
                ht.insert(pnr, marks);
                break;
            case 2:
                cout << "Enter PNR to search: ";
                cin >> pnr;
                ht.search(pnr);
                break;
            case 3:
                ht.display();
                break;
        }
    } while (choice != 0);

    return 0;
}
/*Menu:
1. Insert
2. Search
3. Display
0. Exit
Choice: 1
Enter PNR: 101
Enter Marks: 85

Menu:
1. Insert
2. Search
3. Display
0. Exit
Choice: 1
Enter PNR: 102
Enter Marks: 90

Menu:
1. Insert
2. Search
3. Display
0. Exit
Choice: 1
Enter PNR: 103
Enter Marks: 75

Menu:
1. Insert
2. Search
3. Display
0. Exit
Choice: 3
*/