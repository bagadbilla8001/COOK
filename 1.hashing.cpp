#include <iostream>
using namespace std;

const int TABLE_SIZE = 10;

struct Student {
    int roll;
    int marks;
};

struct HashEntry {
    Student student;
    bool isOccupied = false;
};

class HashTable {
    HashEntry table[TABLE_SIZE];

public:
    void insertWithoutReplacement(Student s) {
        int index = s.roll % TABLE_SIZE;
        while (table[index].isOccupied) {
            index = (index + 1) % TABLE_SIZE;
        }
        table[index].student = s;
        table[index].isOccupied = true;
    }

    int searchWithoutReplacement(int roll) {
        int index = roll % TABLE_SIZE;
        int count = 0;
        while (table[index].isOccupied) {
            count++;
            if (table[index].student.roll == roll) {
                cout << "Found Roll: " << table[index].student.roll << ", Marks: "
                     << table[index].student.marks << " in " << count << " comparisons\n";
                return index;
            }
            index = (index + 1) % TABLE_SIZE;
        }
        cout << "Not found in " << count << " comparisons\n";
        return -1;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].isOccupied)
                cout << i << " => Roll: " << table[i].student.roll 
                     << ", Marks: " << table[i].student.marks << '\n';
            else
                cout << i << " => Empty\n";
        }
    }
};

int main() {
    HashTable ht;
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Student s;
        cout << "Enter roll number and marks for student " << i + 1 << ": ";
        cin >> s.roll >> s.marks;
        ht.insertWithoutReplacement(s);
    }

    cout << "\nHash Table:\n";
    ht.display();

    int rollToSearch;
    cout << "\nEnter roll number to search: ";
    cin >> rollToSearch;
    ht.searchWithoutReplacement(rollToSearch);

    return 0;
}

/*
5
101 85
102 90
113 75
124 88
135 70
113
//Enter number of students: 
Enter roll number and marks for student 1: 
Enter roll number and marks for student 2: 
Enter roll number and marks for student 3: 
Enter roll number and marks for student 4: 
Enter roll number and marks for student 5: 

Hash Table:
0 => Empty
1 => Roll: 101, Marks: 85
2 => Roll: 102, Marks: 90
3 => Roll: 113, Marks: 75
4 => Roll: 124, Marks: 88
5 => Roll: 135, Marks: 70
6 => Empty
7 => Empty
8 => Empty
9 => Empty

Enter roll number to search: 
Found Roll: 113, Marks: 75 in 1 comparisons
*/