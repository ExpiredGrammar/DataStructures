#include<iostream>
#include<string>
#include"HashTable.h"
using namespace std;

int main() {
	int choice = 0;
	int size;
	do {
		cout << "How big would you like the hash table: ";
		cin >> size;
	} while (size < 1);
	HashTableLinked<Student> StudentDirectory = HashTableLinked<Student>(size);
	string firstName = "", lastName = "";
	int bmonth = 0, bday = 0, byear = 0, mNumber;
	float gpa = 0.0;
	bool flag = false;
	Student* tempStudent;
	Student* removedStudent;
	string firstN = "Kyle";
	string lastN = "O'Connor";
	for (int f = 0; f < 50;f++) {
		tempStudent = new Student(firstN, lastN, 10000000 + f, 01, 21, 1997, 4.0);
		StudentDirectory.AddItem(tempStudent);
	}
	do {
		cout << "***************************************" << endl;
		cout << "Please select the the action you would like to complete" << endl;
		cout << "1. Add student to directory" << endl;
		cout << "2. Remove a student from the directory" << endl;
		cout << "3. Check if a student is in the directory" << endl;
		cout << "4. Check if directory is empty" << endl;
		cout << "5. Get the number of students in the directory." << endl;
		cout << "6. Get the information of a student in the directory." << endl;
		cout << "7. Display Hash Table. " << endl;
		cout << "0. Exit" << endl;
		cout << "Enter the number of the choice you wish to select: ";
		cin >> choice;
		if (cin.fail()) {
			choice = 10;
			cin.clear();
			cin.ignore(10000, '\n');
		}
		switch (choice) {
		case 1: cout << "You have chosen to add a student. " << endl;
			cout << "Enter the first name of the student: ";
			cin >> firstName;
			cout << "Enter the last name of the student: ";
			cin >> lastName;
			cout << "Enter the M Number of the student: ";
			cin >> mNumber;
			cout << "Enter the birthday month: ";
			cin >> bmonth;
			cout << "Enter the birthday day: ";
			cin >> bday;
			cout << "Enter the birthday year: ";
			cin >> byear;
			cout << "Enter the student's GPA: ";
			cin >> gpa;
			tempStudent = new Student(firstName, lastName, mNumber, bmonth, bday, byear, gpa);
			StudentDirectory.AddItem(tempStudent);
			firstName = "";
			lastName = "";
			mNumber = 0;
			bmonth = 0;
			bday = 0;
			byear = 0;
			gpa = 0.0;
			tempStudent = nullptr;
			break;
		case 2: cout << "Enter the M Number of the Student you would like to remove: ";
			cin >> mNumber;
			tempStudent = new Student(firstName, lastName, mNumber, bmonth, bday, byear, gpa);
			removedStudent = StudentDirectory.RemoveItem(tempStudent);
			if (removedStudent == nullptr) {
				cout << "There is no student in the directory with that M Number." << endl;
			}
			else {
				cout << "Here are details of the removed student: " << endl;
				cout << "Student Name: " << removedStudent->getName() << endl;
				cout << "Student M Number: " << removedStudent->getMNumber() << endl;
				cout << "Student Birthday: " << removedStudent->getBirthday() << endl;
				cout << "Student Age: " << removedStudent->getAge() << endl;
				delete removedStudent;
				removedStudent = nullptr;
			}
			delete tempStudent;
			tempStudent = nullptr;
			break;
		case 3: cout << "Enter the M Number of the student to check if they are in the directory: ";
			cin >> mNumber;
			tempStudent = new Student(firstName, lastName, mNumber, bmonth, bday, byear, gpa);
			cout << "The student is in the list?: ";
			flag = StudentDirectory.GetItem(tempStudent);
			if (flag) {
				cout << "Yes" << endl;
			}
			else {
				cout << "No" << endl;
			}

			delete tempStudent;
			tempStudent = nullptr;
			break;
		case 4: cout << "Is the directory empty?: ";
			if (StudentDirectory.GetLength() == 0) {
				cout << "Yes" << endl;
			}
			else {
				cout << "No" << endl;
			}
			break;
		case 5: cout << "The number of students in the directory: " << StudentDirectory.GetLength() << endl;
			break;
		case 6: cout << "Enter the M Number of the Student you would like to view: ";
			cin >> mNumber;
			tempStudent = new Student(firstName, lastName, mNumber, bmonth, bday, byear, gpa);
			removedStudent = StudentDirectory.GetItem(tempStudent); 
			// Removed student in this case does not mean the student has been removed from the directory
			if (removedStudent == nullptr) {
				cout << "There is no student in the directory with that M Number." << endl;
			}
			else {
				cout << "Here are details of the student: " << endl;
				cout << "Student Name: " << removedStudent->getName() << endl;
				cout << "Student M Number: " << removedStudent->getMNumber() << endl;
				cout << "Student Birthday: " << removedStudent->getBirthday() << endl;
				cout << "Student Age: " << removedStudent->getAge() << endl;
				/// delete removedStudent;
				removedStudent = nullptr;
			}
			delete tempStudent;
			tempStudent = nullptr;
			break;
		case 7: cout << StudentDirectory.toString();
			break;
		case 0: cout << "You have chosen to exit." << endl;
			break;
		default: cout << "You have entered an invalid choice." << endl;
			break;
		}
	} while (choice != 0);
	return 0;
}