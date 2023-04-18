/*
	Name: Matthew Cochrane
	Course: CS-300
	Date: 11 April 2023
	Assignment: Project Two
*/

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Course class
class Course {
private:
	string courseNumber;
	string courseName;
	string prerequisites;
public:
	// Setters
	void set(string courseNumber, string courseName, string prerequisites) {
		this->courseNumber = courseNumber;
		this->courseName = courseName;
		this->prerequisites = prerequisites;
	}

	// Getters
	string getNum() const {
		return this->courseNumber;
	}
	string getName() const {
		return this->courseName;
	}
	string getPrereq() const {
		return this->prerequisites;
	}

	// Print course information
	void printCourse() {
		cout << "Number: " << this->courseNumber << endl;
		cout << "Name: " << this->courseName << endl;
		cout << "Prerequisites: " << this->prerequisites << "\n" << endl;

	}
};

// Read input file into a vector of course objects
vector<Course> readCourses(string courseFile) {
	// Initialize variables
	vector<Course> courses;
	vector<string> row;
	string line, word, prereq = "", name, number;
	int i;

	// Open file
	fstream file(courseFile, ios::in);

	// If file is open
	if (file.is_open()) {

		// While there is a next line
		while (getline(file, line)) {

			// Create course object and clear row for next course
			Course course;
			row.clear();

			// Read line
			stringstream str(line);

			// Put row elements into vector
			while (getline(str, word, ',')) {
				row.push_back(word);
			}
			number = row[0];
			name = row[1];

			// If there are prerequisites
			if (row.size() > 2) {
				prereq = row[2];
				for (i = 3; i < row.size(); i++) {
					prereq += ", " + row[i];
				}
			}
			// Add as course object and add to course list
			course.set(number, name, prereq);
			courses.push_back(course);

			// Clear prereq vector
			prereq.clear();
			}
	}
	else {
		cout << "Could not open." << endl;
	}
	return courses;
}

void abcPrint(vector<Course> courses) {
	int i, j, k;
	
	// Bubble sort by course number
	for (i = 0; i < courses.size(); i++) {
		for (j = 1; j < courses.size(); j++) {
			if (courses[j - 1].getNum() > courses[j].getNum()) {
				swap(courses[j], courses[j - 1]);
			}
		}
	}
	// Print sorted courses
	for (k = 0; k < courses.size(); k++) {
		courses[k].printCourse();
	}
}

void onePrint(vector<Course> courses, string userNum) {
	string num;
	int i;

	for (i = 0; i < courses.size(); i++) {
		num = courses[i].getNum();
		if (num == userNum) {
			courses[i].printCourse();
		}
	}
}

int main() {
	vector<Course> courses;
	string userNum;
	string courseFile = "Courses.csv";
	int choice = 0;

	cout << "Hello, please choose an option:\n" << endl;
	while (choice != 9) {
		
		cout << "1. Load Data Structure." << endl;
		cout << "2. Print Course List in Alphanumeric Order." << endl;
		cout << "3. Print a Specific Course." << endl;
		cout << "9. Exit." << endl;
		cin >> choice;

		switch (choice) {
		case 1:
			// Load data
			courses = readCourses(courseFile);
			for (int i = 0; i < courses.size(); i++) {
				courses[i].printCourse();
			}
			break;
		case 2:
			// Alphanumeric function call
			abcPrint(courses);
			break;
		case 3:
			// Print a course
			cout << "Enter the 7-digit course number you would like to query: ";
			cin >> userNum;
			cout << "\n";
			onePrint(courses, userNum);
			break;
		case 9:
			cout << "Thank you for your input." << endl;
			break;
		default:
			cout << "Invalid input." << endl;
			break;
		}
	}

}