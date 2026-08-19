
// Khizar
// Momin-ul-Hassan
// ( DUO )
// =======================

#include <iostream>
using namespace std;

const int MAX = 50;

int rollNo[MAX];
int age[MAX];
int marks[MAX];
char name[MAX][30];

int totalStudents = 0;

void addStudent() {
  cout << endl << "Enter Student Name: ";
  cin >> name[totalStudents];

  cout << "Enter Roll Number: ";
  cin >> rollNo[totalStudents];

  cout << "Enter Age: ";
  cin >> age[totalStudents];

  cout << "Enter Marks: ";
  cin >> marks[totalStudents];

  totalStudents++;

  cout << endl << "Student added successfully!" << endl;
}

void displayStudents() {
  if (totalStudents == 0) {
    cout << endl << "No student record found." << endl;
    return;
  }

  cout << endl << "===== STUDENT RECORDS =====" << endl;

  for (int i = 0; i < totalStudents; i++) {
    cout << endl << "Student " << i + 1 << endl;
    cout << "Name: " << name[i] << endl;
    cout << "Roll Number: " << rollNo[i] << endl;
    cout << "Age: " << age[i] << endl;
    cout << "Marks: " << marks[i] << endl;
  }
}

void searchStudent() {
  int searchRoll;
  bool found = false;

  cout << endl << "Enter Roll Number to Search: ";
  cin >> searchRoll;

  for (int i = 0; i < totalStudents; i++) {
    if (rollNo[i] == searchRoll) {
      cout << endl << "Student Found!" << endl;
      cout << "Name: " << name[i] << endl;
      cout << "Roll Number: " << rollNo[i] << endl;
      cout << "Age: " << age[i] << endl;
      cout << "Marks: " << marks[i] << endl;

      found = true;
      break;
    }
  }

  if (found == false) {
    cout << endl << "Student not found." << endl;
  }
}

void calculateGrade() {
  int searchRoll;

  cout << endl << "Enter Roll Number: ";
  cin >> searchRoll;

  for (int i = 0; i < totalStudents; i++) {
    if (rollNo[i] == searchRoll) {
      cout << "Marks: " << marks[i] << endl;

      if (marks[i] >= 80)
        cout << "Grade: A" << endl;
      else if (marks[i] >= 70)
        cout << "Grade: B" << endl;
      else if (marks[i] >= 60)
        cout << "Grade: C" << endl;
      else if (marks[i] >= 50)
        cout << "Grade: D" << endl;
      else
        cout << "Grade: F" << endl;

      return;
    }
  }

  cout << "Student not found." << endl;
}

int main() {
  int choice;

  do {
    cout << endl << "==============================" << endl;
    cout << "   STUDENT MANAGEMENT SYSTEM" << endl;
    cout << "==============================" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Display Students" << endl;
    cout << "3. Search Student" << endl;
    cout << "4. Calculate Grade" << endl;
    cout << "5. Exit" << endl;

    cout << endl << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      addStudent();
      break;

    case 2:
      displayStudents();
      break;

    case 3:
      searchStudent();
      break;

    case 4:
      calculateGrade();
      break;

    case 5:
      cout << endl << "Program ended. Thank you!" << endl;
      break;

    default:
      cout << endl << "Invalid choice!" << endl;
    }

  } while (choice != 5);

  return 0;
}