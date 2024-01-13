# include <string>
# include <iostream>
# include <vector>
# include <algorithm>
# include <iomanip>
# include <random>
# include <fstream>
# include <sstream>
using namespace std;

enum HomeworkFinalScoreType {
    AVERAGE,
    MEDIAN
};

class Person {
    private:
        string mFirstname;
        string mLastname;
        double mExamScore;
        vector<double> mHomeworkScores;
        double mFinalGrade;
        HomeworkFinalScoreType mHomeworkFinalScoreType;

        double calcFinalGrade() {
            double hwFinalScore = calcAverage(mHomeworkScores);
            if (mHomeworkFinalScoreType == AVERAGE) {
                hwFinalScore = calcAverage(mHomeworkScores);
            } else {
                hwFinalScore = calcMedian(mHomeworkScores);
            }

            return (0.4 * hwFinalScore) + (0.6 * mExamScore);
        }

        double calcAverage(const vector<double>& numbers) {
            double sum = 0.0;

            for (const double& num : numbers) {
                sum += num;
            }

            return sum / numbers.size();
        }

        double calcMedian(const vector<double>& numbers) {
            size_t size = numbers.size();
            if (size % 2 == 0) {
                double midNum1 = numbers[size / 2 - 1];
                double midNum2 = numbers[size / 2];
                return (midNum1 + midNum2) / 2;
            } else {
                return numbers[size / 2];
            }
        }

        double generateRandomScore() {
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<double> distribution(1.0, 10.0);

            return distribution(gen);
        }

    public:
        Person(HomeworkFinalScoreType homeworkFinalScoreType) {
            mHomeworkFinalScoreType = homeworkFinalScoreType;
        }

        Person(const Person& person) {
            mFirstname = person.mFirstname;
            mLastname = person.mLastname;
            mExamScore = person.mExamScore;
            mHomeworkScores = person.mHomeworkScores;
            mHomeworkFinalScoreType = person.mHomeworkFinalScoreType;
            sort(mHomeworkScores.begin(), mHomeworkScores.end());
            mFinalGrade = calcFinalGrade();
        }

        ~Person() {}

        Person& operator=(const Person& person) {
            return *this;
        }

        friend istream& operator>>(istream& in, Person& person) {
            person.mHomeworkScores.resize(5);
            in >> person.mFirstname >> person.mLastname >> person.mHomeworkScores[0] >> person.mHomeworkScores[1] >> person.mHomeworkScores[2] >> person.mHomeworkScores[3] >> person.mHomeworkScores[4] >> person.mExamScore;
            person.mFinalGrade = person.calcFinalGrade();
            return in;
        }

        friend ostream& operator<<(ostream& os, Person& person) {
            os << left << setw(25) << person.mFirstname << setw(25) << person.mLastname << setw(25) << fixed << setprecision(2) << person.mFinalGrade;
            return os;
        }
};

int main() {
    vector<Person> students;

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

    ifstream file("Students.txt");

    string header;
    getline(file, header);

    string line;
    int numOfStudents = 0;
    while(getline(file, line)) {
        istringstream iss(line);
        Person student(hwFinalScoreType);
        iss >> student;
        ++numOfStudents;
        students.push_back(student);
    }


    string finalPointTitle;
    if (hwFinalScoreType == AVERAGE) {
        finalPointTitle = "Final_Point(Ave.)";
    } else {
        finalPointTitle = "Final_Point(Med.)";
    }
    cout << left << setw(25) << "Name" <<  setw(25) << "Surname" << setw(25) << finalPointTitle << endl;
    cout << "------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < numOfStudents; i++) {
        cout << students[i] << endl;
    }

    return 0;
}
