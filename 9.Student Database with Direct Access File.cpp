#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Student {
    int roll;
    char name[30];
    char div[10];
    char addr[50];
};

const char* FILENAME = "StudentDB.dat";

void addStudent() {
    ofstream f(FILENAME, ios::app | ios::binary);
    if (!f) {
        cerr << "Error opening file!\n";
        return;
    }

    Student s;
    cout << "Enter student details:\n";
    cout << "Roll No: "; cin >> s.roll;
    cout << "Name: "; cin.ignore(); cin.getline(s.name, 30);
    cout << "Division: "; cin.getline(s.div, 10);
    cout << "Address: "; cin.getline(s.addr, 50);

    f.write(reinterpret_cast<char*>(&s), sizeof(s));
    cout << "Student added successfully!\n";
}

void displayAll() {
    ifstream f(FILENAME, ios::binary);
    if (!f) {
        cerr << "No records found!\n";
        return;
    }

    Student s;
    cout << "\nStudent Records:\n";
    cout << "------------------------------------------------------------\n";
    cout << "Roll No\tName\t\tDivision\tAddress\n";
    cout << "------------------------------------------------------------\n";

    while (f.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        cout << s.roll << "\t" << s.name << "\t" << s.div << "\t\t" << s.addr << endl;
    }
}

void searchStudent() {
    ifstream f(FILENAME, ios::binary);
    if (!f) {
        cerr << "No records found!\n";
        return;
    }

    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;

    Student s;
    bool found = false;
    while (f.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.roll == roll) {
            cout << "\nRecord Found:\n";
            cout << "Roll No: " << s.roll << endl;
            cout << "Name: " << s.name << endl;
            cout << "Division: " << s.div << endl;
            cout << "Address: " << s.addr << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Record not found!\n";
    }
}

void updateStudent() {
    fstream f(FILENAME, ios::in | ios::out | ios::binary);
    if (!f) {
        cerr << "No records found!\n";
        return;
    }

    int roll;
    cout << "Enter Roll No to update: ";
    cin >> roll;

    Student s;
    bool found = false;
    while (f.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.roll == roll) {
            cout << "\nCurrent Details:\n";
            cout << "Name: " << s.name << endl;
            cout << "Division: " << s.div << endl;
            cout << "Address: " << s.addr << endl;

            cout << "\nEnter new details:\n";
            cout << "Name: "; cin.ignore(); cin.getline(s.name, 30);
            cout << "Division: "; cin.getline(s.div, 10);
            cout << "Address: "; cin.getline(s.addr, 50);

            f.seekp(-static_cast<int>(sizeof(s)), ios::cur);
            f.write(reinterpret_cast<char*>(&s), sizeof(s));
            cout << "Record updated successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Record not found!\n";
    }
}

void deleteStudent() {
    ifstream inFile(FILENAME, ios::binary);
    if (!inFile) {
        cerr << "No records found!\n";
        return;
    }

    ofstream temp("temp.dat", ios::binary);
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    Student s;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.roll != roll) {
            temp.write(reinterpret_cast<char*>(&s), sizeof(s));
        } else {
            found = true;
        }
    }

    inFile.close();
    temp.close();

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found) {
        cout << "Record deleted successfully!\n";
    } else {
        cout << "Record not found!\n";
    }
}

void showMenu() {
    cout << "\nStudent Database Management System\n";
    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}