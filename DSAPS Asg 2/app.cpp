#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
int menu();
bool Redundant(BST, Student);

int main() {
	ifstream inFile;
	Student student;
	const char *filename = "student.txt";
	inFile.open(filename);
	char s[256];
	BST stuTree;
	BST t2;
	do {
		switch (menu()) {

		case 1: // Read data to BST

			if (!readFile(filename, &stuTree)) {
			cout << "Unable to read " << filename << endl;
			}
			else
				cout << "Read successfully." << endl;
			cout << endl;
			system("pause");
			system("cls");
			break;

		case 2: // Print deepest nodes
			if (!stuTree.deepestNodes())
				cout << "Fail to get deepest node(s)." << endl;
			cout << endl;
			system("pause");
			system("cls");
			break;

		case 3: // Display student
			int order, source;
			cout << "Display order? (1 - ascending order / 2 - descending order): "; 
			cin >> order;
			cout << "Where do you want to display the output? (1 - Screen / 2 - File): ";
			cin >> source;
			cout << endl;

			if (stuTree.display(order, source)) {
				cout << "\nDisplayed successfully.\n" << endl;
			}
			else {
				cout << "\nFail to display.\n" << endl;
			}

			system("pause");
			system("cls");
			break;

		case 4: // Clone Subtree


			if (!t2.empty()) {
				cout << "t2 is not empty. Cloning operation is not executed." << endl;
			}
			else {
				Student tmp;
				cout << "\nEnter the id of a node you want to clone: ";
				cin >> tmp.id;
				cout << "\n";
				if (t2.CloneSubtree(stuTree, tmp)) {

					cout << "\n\n========================================================\n";
					cout << "                    Original tree\n";
					cout << "                  (pre-order print)\n";
					cout << "========================================================\n\n";
					stuTree.preOrderPrint();

					cout << "\n\n========================================================\n";
					cout << "                  Newly cloned subtree\n";
					cout << "                   (pre-order print)\n";
					cout << "========================================================\n\n";
					t2.preOrderPrint();
				}
				else
					cout << "Cannot clone subtree." << endl;
			}
			system("pause");
			system("cls");
			break;

		case 5: // Print Level Nodes

			stuTree.printLevelNodes();

			system("pause");
			system("cls");
			break;

		case 6: // Print Path

			stuTree.printPath();

			system("pause");
			system("cls");
			break;

		case 7: // Exit
			return 0;
		}
	} while (1);
}


int menu() {
	int option;

	cout << "-------------------------------------" << endl;
	cout << "                MENU" << endl;
	cout << "-------------------------------------" << endl;
	cout << "1. Read data to BST" << endl
		<< "2. Print deepest nodes" << endl
		<< "3. Display student" << endl
		<< "4. Clone Subtree" << endl
		<< "5. Print Level Nodes" << endl
		<< "6. Print Path" << endl
		<< "7. Exit" << endl;
	cout << "-------------------------------------" << endl;
	cout << "Please input your option (1-7): ";
	cin >> option;

	while (cin.fail()) { // input validation
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Not an integer! Enter again: ";
		cin >> option;
	}

	while (option < 1 || option > 7) { // input validation
		cout << "Out of range! Enter again: ";
		cin >> option;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Not an integer! Enter again: ";
			cin >> option;
		}
	}
	return option;
}


bool readFile(const char* filename, BST* t1) {

	char s[256];
	ifstream inFile;
	inFile.open(filename);
	Student student;

	if (inFile.fail()) {
		cout << "Unable to open the file" << endl;
		return false;
	}
	else {
		while (!inFile.eof()) {
			for (int i = 0; i < 3; i++) {	//for loop is used to read the data from txt file and insert them into Student struct
				inFile >> s;
			}
			inFile >> student.id;

			for (int i = 0; i < 2; i++) {
				inFile >> s;
			}
			inFile >> student.name;
			inFile.getline(s, 256);
			strcat_s(student.name, s);

			for (int i = 0; i < 2; i++) {
				inFile >> s;
			}
			inFile >> student.address;
			inFile.getline(s, 256);
			strcat_s(student.address, s);

			for (int i = 0; i < 2; i++) {
				inFile >> s;
			}
			inFile >> student.DOB;

			for (int i = 0; i < 3; i++) {
				inFile >> s;
			}
			inFile >> student.phone_no;

			for (int i = 0; i < 2; i++) {
				inFile >> s;
			}
			inFile >> student.course;

			for (int i = 0; i < 2; i++) {
				inFile >> s;
			}
			inFile >> student.cgpa;

			if (!Redundant(*t1, student)) {		//if the data does not exist in the tree, it will be inserted.
				t1->insert(student);
			}
			else
				cout << student.name << " already exist." << endl;
		}
		inFile.close();

		cout << endl;
		cout << "The number of student record successfully read: " << t1->countNode() << endl << endl;	//display the no. of nodes in the tree.

	}
	
	return true;
}

bool Redundant(BST stuTree, Student student)
{
	Student temp;
	BTNode* cur;

	if (stuTree.empty())
		return false;

	cur = stuTree.root;
	while (cur != NULL) {
		if (cur->item.compare2(student)) //if node value same as item, then return true
			return true;

		if (cur->item.compare1(student))
			cur = cur->left;
		else 
			cur = cur->right;
	}
	
	return false;
}


