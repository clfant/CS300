#include "Course.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>


// Takes a string and splits it into pieces to use

void lineSplit(string inLine, vector<string>& outLine)
{
	outLine.clear();                    // clears previous data held in vector
	stringstream sLine(inLine);
	string item;
	while (getline(sLine, item, ','))   // iterates through line and adds data to the vector until the end of the line
	{
		outLine.push_back(item);
	}


}

// Prints the menu
void printMenu()
{
	cout << "1. Load Data Structure" << endl;
	cout << "2. Print Course List" << endl;
	cout << "3. Print Course" << endl;
	cout << "9. Exit" << endl;
}

// Reads from a file and puts the data into a vector to be used
bool reader(vector<Course>& courses)
{
	string fileName;
	ifstream file;
	vector <string> fileLine;
	string num;
	string name;
	bool fileOpen = false;


	cout << "What is the name of the file you would like to read?" << endl;    //gets user input
	cin >> fileName;
	cout << endl;

	file.open(fileName);   // opens file based on user input

	if (!file.is_open())
	{
		cout << "The file did not open." << endl << endl;   // checks if file is open and returns error message if it does not open
		return fileOpen;
	}
	else
	{
		while (!file.eof())    // iterates through file until it reaches the end
		{
			string line;
			getline(file, line);       // gets line from  file
			if (file.good())       // checks if there are errors with the file
			{
				lineSplit(line, fileLine);
				if (fileLine.size() < 2)     // checks to see if the file is formatted correctly
				{ 
					cout << "File is not formatted correctly" << endl;
					courses.clear();
					file.close();
					return fileOpen;
				}
				else
				{
					// adds data from file into a vector
					num = fileLine[0];
					name = fileLine[1];
					Course course(num, name);
					for (int i = 2; i < fileLine.size(); ++i)
					{
						course.preReqs.push_back(fileLine[i]);
					}

					courses.push_back(course);

				}
			}
		}
		file.close();   // closes file
	}
	fileOpen = true;
	cout << "File loaded succesfully." << endl << endl;   // lets user know the file loaded sucessfully
	return fileOpen;
}

// operator overload to compare Courses agaisnt each other to sort them in order
bool operator<(const Course& c1, const Course& c2)
{
	return c1.courseNum < c2.courseNum;
}

// prints a list of courses 
void printCourseList(vector<Course> courses)
{
	cout << "Here is a sample schedule: " << endl << endl;
	sort(courses.begin(), courses.end());   // fix me
	for (int i = 0; i < courses.size(); ++i)
	{
		cout << courses[i].courseNum << ", " << courses[i].courseName << endl;
	}
	cout << endl;
}

// converts a string to all uppercase
void upper(string& cls)
{
	int size = cls.size();
	for (int i = 0; i < size; ++i)
	{
		cls[i] = toupper(cls[i]);
	}
}

// finds and prints a user specified course
void printACourse(vector<Course>& courseList)
{
	string userClass;

	cout << "What course would you like to know about?" << endl;

	cin >> userClass;
	cout << endl;

	upper(userClass);

	int size = courseList.size();
	for (int i = 0; i < size; ++i)      // iterates through courses vector
	{
		if (courseList[i].courseNum.compare(userClass) == 0)    // compares current course number to user course number
		{
			cout << courseList[i].courseNum << ", " << courseList[i].courseName << endl;
			int preReqSize = courseList[i].preReqs.size();
			if (preReqSize > 0)                // checks if there are prereqs
			{
				cout << "Prerequisites: ";
				for (int j = 0; j < preReqSize; ++j)
				{
					if (j != preReqSize - 1)           // determines if the prereq is the last one for formatting purposes
					{
						cout << courseList[i].preReqs[j] << ", ";
					}
					else
					{
						cout << courseList[i].preReqs[j];
					}
				}
				cout << endl << endl;
			}
			return;
		}
		
	}
	cout << "This course does not exist." << endl << endl;   // lets user know that the course they were searching for doesn't exist
}

int main()
{
	cout << "Welcome to the course planner." << endl;

	int userChoice = 0;
	vector<Course> courses;

	while (userChoice != 9)        // switch case to operate menu based off user input
	{
		printMenu();

		cout << "What would you like to do?" << endl;

		cin >> userChoice;
		cout << endl;

		switch (userChoice)
		{
		case 1:
			reader(courses);
			break;
		case 2:
			printCourseList(courses);
			break;
		case 3:
			printACourse(courses);
			break;
		case 9:
			break;
		default:
			cout << "This is not a valid input. Please try again." << endl << endl;   // catch for invalid input into the menu
			break;
		}

	}

	cout << "Thank you for using the course planner!" << endl;
}