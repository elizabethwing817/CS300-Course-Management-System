#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

//==============================================================
// Name: ProjectTwo.cpp
// Author: Elizabeth Wing
// Course: CS 300
// Description: ABCU Advising Assistance Program
//==============================================================

// Structure to store course information
struct Course {
    string id;
    string title;
    vector<string> prerequisites;
};

// Trim whitespace from both ends of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    if (first == string::npos || last == string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}

// Convert string to uppercase
string toUpper(string str) {
    for (char& c : str) {
        c = toupper(c);
    }
    return str;
}

// Split a CSV line by commas
vector<string> splitCSV(const string& line) {
    vector<string> tokens;
    string token;
    stringstream ss(line);

    while (getline(ss, token, ',')) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

// Load courses from file into data structure
bool loadCourses(const string& filename,
    unordered_map<string, Course>& courseMap,
    vector<string>& courseIds) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file.\n";
        return false;
    }

    courseMap.clear();
    courseIds.clear();

    string line;
    while (getline(file, line)) {
        vector<string> data = splitCSV(line);

        if (data.size() < 2) {
            continue;
        }

        Course course;
        course.id = toUpper(data[0]);
        course.title = data[1];

        for (size_t i = 2; i < data.size(); i++) {
            if (!data[i].empty()) {
                course.prerequisites.push_back(toUpper(data[i]));
            }
        }

        courseMap[course.id] = course;
    }

    file.close();

    for (auto& pair : courseMap) {
        courseIds.push_back(pair.first);
    }

    cout << "Courses successfully loaded.\n";
    return true;
}

// Print all courses in alphanumeric order
void printCourseList(const unordered_map<string, Course>& courseMap,
    vector<string> courseIds) {

    sort(courseIds.begin(), courseIds.end());

    cout << "\nCourse List:\n";
    for (const string& id : courseIds) {
        auto it = courseMap.find(id);
        if (it != courseMap.end()) {
            cout << it->second.id << ", " << it->second.title << endl;
        }
    }
    cout << endl;
}

// Print a single course and its prerequisites
void printCourse(const unordered_map<string, Course>& courseMap,
    const string& courseId) {

    string id = toUpper(courseId);
    auto it = courseMap.find(id);

    if (it == courseMap.end()) {
        cout << "Error: Course not found.\n";
        return;
    }

    const Course& course = it->second;
    cout << "\n" << course.id << ", " << course.title << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None\n\n";
        return;
    }

    cout << "Prerequisites:\n";
    for (const string& preId : course.prerequisites) {
        auto preIt = courseMap.find(preId);
        if (preIt != courseMap.end()) {
            cout << "  " << preIt->second.id << ", "
                << preIt->second.title << endl;
        }
        else {
            cout << "  " << preId << endl;
        }
    }
    cout << endl;
}

// Display menu and get user choice
int displayMenu() {
    cout << "Menu:\n";
    cout << "  1. Load Data Structure\n";
    cout << "  2. Print Course List\n";
    cout << "  3. Print Course\n";
    cout << "  9. Exit\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;
    cin.ignore();
    return choice;
}

int main() {
    unordered_map<string, Course> courseMap;
    vector<string> courseIds;
    bool dataLoaded = false;
    string filename;

    cout << "Welcome to the ABCU Advising Assistance Program.\n";
    cout << "Enter the course data file name: ";
    getline(cin, filename);

    while (true) {
        int choice = displayMenu();

        switch (choice) {
        case 1:
            dataLoaded = loadCourses(filename, courseMap, courseIds);
            break;

        case 2:
            if (!dataLoaded) {
                cout << "Error: Please load data first.\n";
            }
            else {
                printCourseList(courseMap, courseIds);
            }
            break;

        case 3:
            if (!dataLoaded) {
                cout << "Error: Please load data first.\n";
            }
            else {
                cout << "Enter course number: ";
                string courseNumber;
                getline(cin, courseNumber);
                printCourse(courseMap, courseNumber);
            }
            break;

        case 9:
            cout << "Goodbye.\n";
            return 0;

        default:
            cout << "Error: Invalid menu option.\n";
        }
    }
}
