/*
QUESTION:
    Department maintains a student information. The file contains roll number, name,
    division and address. Allow user to add, delete information of student. Display
    information of particular employee. If record of student does not exist an appropriate
    message is displayed. If it is, then the system displays the student details. Use sequential
    file to main the data.

OUTPUT:
    ----- Student Information System -----
    1. Add Student
    2. Delete Student
    3. Display Student
    4. Quit
    Enter your choice: 1
    Enter Roll Number: 1
    Enter Name: ADMIN
    Enter Division: A
    Enter Address: XYZ
    
    ----- Student Information System -----
    1. Add Student
    2. Delete Student
    3. Display Student
    4. Quit
    Enter your choice: 1
    Enter Roll Number: 10
    Enter Name: PAUL
    Enter Division: C
    Enter Address: ABC
    
    ----- Student Information System -----
    1. Add Student
    2. Delete Student
    3. Display Student
    4. Quit
    Enter your choice: 3
    Enter Roll Number of student to display: 10
    Roll Number: 10
    Name: PAUL
    Division: C
    Address: ABC

*/


#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Student {
    char roll[20];
    char name[50];
    char division[5];
    char address[100];
};

void addStudent() {
    Student s;
    ofstream out("students.txt", ios::app);

    cout << "Enter Roll Number: ";
    cin.getline(s.roll, 20);
    cout << "Enter Name: ";
    cin.getline(s.name, 50);
    cout << "Enter Division: ";
    cin.getline(s.division, 5);
    cout << "Enter Address: ";
    cin.getline(s.address, 100);

    out << s.roll << "," << s.name << "," << s.division << "," << s.address << "\n";
    out.close();
}

void deleteStudent(const char* targetRoll) {
    ifstream in("students.txt");
    ofstream out("temp.txt");
    char line[200];
    bool found = false;

    while (in.getline(line, 200)) {
        char roll[20];
        sscanf(line, "%[^,]", roll);  // extract roll number before the first comma

        if (strcmp(roll, targetRoll) != 0) {
            out << line << "\n";
        } else {
            found = true;
        }
    }

    in.close();
    out.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    cout << (found ? "Deleted successfully.\n" : "Student not found.\n");
}

void displayStudent(const char* targetRoll) {
    ifstream in("students.txt");
    char line[200];
    bool found = false;

    while (in.getline(line, 200)) {
        char roll[20], name[50], div[5], addr[100];
        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", roll, name, div, addr);

        if (strcmp(roll, targetRoll) == 0) {
            cout << "Roll: " << roll << "\nName: " << name
                 << "\nDivision: " << div << "\nAddress: " << addr << "\n";
            found = true;
            break;
        }
    }

    in.close();
    if (!found)
        cout << "Student not found.\n";
}

int main() {
    int choice;
    char roll[20];

    do {
        cout << "\n--- Student Information System ---\n";
        cout << "1. Add Student\n2. Delete Student\n3. Display Student\n4. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline after number input

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll Number to delete: ";
                cin.getline(roll, 20);
                deleteStudent(roll);
                break;
            case 3:
                cout << "Enter Roll Number to display: ";
                cin.getline(roll, 20);
                displayStudent(roll);
                break;
            case 4:
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}

