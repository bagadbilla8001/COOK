#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Student {
    int rollNo;
    char name[30];
    char division;
    char address[50];
};

const char* FILENAME = "students_seq.dat";

void addStudent() {
    ofstream file(FILENAME, ios::app | ios::binary);
    Student s;
    
    cout << "Enter Roll No: "; cin >> s.rollNo;
    cout << "Enter Name: "; cin.ignore(); cin.getline(s.name, 30);
    cout << "Enter Division: "; cin >> s.division;
    cout << "Enter Address: "; cin.ignore(); cin.getline(s.address, 50);
    
    file.write(reinterpret_cast<char*>(&s), sizeof(s));
    file.close();
}

void displayAll() {
    ifstream file(FILENAME, ios::binary);
    if (!file) {
        cout << "No records found!\n";
        return;
    }

    Student s;
    cout << "\nAll Student Records:\n";
    cout << "Roll No\tName\t\tDivision\tAddress\n";
    cout << "------------------------------------------------\n";
    
    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        cout << s.rollNo << "\t" << s.name << "\t" << s.division << "\t\t" << s.address << endl;
    }
    file.close();
}

void searchStudent() {
    ifstream file(FILENAME, ios::binary);
    if (!file) {
        cout << "No records found!\n";
        return;
    }

    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;

    Student s;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "\nRecord Found:\n";
            cout << "Roll No: " << s.rollNo << endl;
            cout << "Name: " << s.name << endl;
            cout << "Division: " << s.division << endl;
            cout << "Address: " << s.address << endl;
            found = true;
            break;
        }
    }
    
    if (!found) cout << "Record not found!\n";
    file.close();
}

void deleteStudent() {
    ifstream inFile(FILENAME, ios::binary);
    if (!inFile) {
        cout << "No records found!\n";
        return;
    }

    ofstream temp("temp.dat", ios::binary);
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    Student s;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo != roll) {
            temp.write(reinterpret_cast<char*>(&s), sizeof(s));
        } else {
            found = true;
        }
    }

    inFile.close();
    temp.close();
    remove(FILENAME);
    rename("temp.dat", FILENAME);

    cout << (found ? "Record deleted!\n" : "Record not found!\n");
}

int main() {
    int choice;
    do {
        cout << "\nStudent Information System (Sequential Access)\n";
        cout << "1. Add Student\n";
        cout << "2. Display All\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 5);

    return 0;
}
/*Student Information System (Sequential Access)
1. Add Student
2. Display All
3. Search Student
4. Delete Student
5. Exit
Enter choice: 1
Enter Roll No: 1
Enter Name: John Doe
Enter Division: A
Enter Address: 123 Main St

Student Information System (Sequential Access)
1. Add Student
2. Display All
3. Search Student
4. Delete Student
5. Exit
Enter choice: 1
Enter Roll No: 2
Enter Name: Jane Smith
Enter Division: B
Enter Address: 456 Oak St

Student Information System (Sequential Access)
1. Add Student
2. Display All
3. Search Student
4. Delete Student
5. Exit
Enter choice: 2

All Student Records:
Roll No    Name            Division    Address
------------------------------------------------
1          John Doe        A           123 Main St
2          Jane Smith      B           456 Oak St

Student Information System (Sequential Access)
1. Add Student
2. Display All
3. Search Student
4. Delete Student
5. Exit
Enter choice: 3
Enter Roll No to search: 1

Record Found:
Roll No: 1
Name: John Doe
Division: A
Address: 123 Main St

Student Information System (Sequential Access)
1. Add Student
2. Display All
3. Search Student
4. Delete Student
5. Exit
Enter choice: 4
Enter Roll No to delete: 1

Record deleted!

Student Information System (Sequential Access)
1. Add Student
2. Display All
3. Search Student
4. Delete Student
5. Exit
Enter choice: 2

All Student Records:
Roll No    Name            Division    Address
------------------------------------------------
2          Jane Smith      B           456 Oak St

Student Information System (Sequential Access)
1. Add Student
2. Display All
3. Search Student
4. Delete Student
5. Exit
Enter choice: 5
*/