# include <string>
# include <iostream>
# include <vector>
# include <algorithm>
# include <iomanip>
# include <random>
# include <fstream>
# include <sstream>
# include "Person.h"
using namespace std;

#define MEASURE_TIME(code) \
{ \
  auto start = std::chrono::high_resolution_clock::now (); \
  code \
  auto stop = std::chrono::high_resolution_clock::now (); \
  std::chrono::duration<double, std::milli> ms = stop - start; \
  std::cout << "Time taken: " << ms.count () << " ms\n"; \
}

int main() {
    cout << "Load file with (1) 10K (2) 100K records: ";
    int fileNum;
    cin >> fileNum;

    vector<Person> passedStudents;
    vector<Person> failedStudents;

    cout << "Enter homework final score calculation type (`a` for average, `m` for median): ";
    string inputHwFinalScoreType;
    cin >> inputHwFinalScoreType;
    HomeworkFinalScoreType hwFinalScoreType;
    if (inputHwFinalScoreType == "a") {
        hwFinalScoreType = AVERAGE;
    } else if (inputHwFinalScoreType == "m") {
        hwFinalScoreType = MEDIAN;
    } else {
        throw invalid_argument("Homework final score calculation type should be either `a` (average) or `m` (median)");
    }

    ifstream file;
    cout << "Measuring time for file load operation:\n";
    MEASURE_TIME({
        if (fileNum == 1) {
            file.open("Students10000.txt");
        } else if (fileNum == 2) {
            file.open("Students100000.txt");
        } else {
            throw invalid_argument("File number should be in the acceptable range.");
        }
    });


    string header;
    getline(file, header);

    string line;
    int numOfStudents = 0;
    while(getline(file, line)) {
        istringstream iss(line);
        Person student(hwFinalScoreType);
        iss >> student;
        ++numOfStudents;
        if (student.passed()) {
            passedStudents.push_back(student);
        } else {
            failedStudents.push_back(student);
        }
    }


    string finalPointTitle;
    if (hwFinalScoreType == AVERAGE) {
        finalPointTitle = "Final_Point(Ave.)";
    } else {
        finalPointTitle = "Final_Point(Med.)";
    }
    cout << left << setw(25) << "Name" <<  setw(25) << "Surname" << setw(25) << finalPointTitle << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "• Passed:\n";
    for (int i = 0; i < passedStudents.size(); i++) {
        cout << passedStudents[i] << endl;
    }

    cout << "• Failed:\n";
    for (int i = 0; i < failedStudents.size(); i++) {
        cout << failedStudents[i] << endl;
    }

    file.close();

    return 0;
}
