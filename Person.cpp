# include <string>
# include <iostream>
# include <vector>
# include <algorithm>
# include <iomanip>
# include <random>
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
            double midNum1 = numbers[(numbers.size() / 2) - 1];
            double midNum2 = numbers[(numbers.size() / 2) + 1];
            return (midNum1 + midNum2) / 2;
        }

        double generateRandomScore() {
            random_device rd;
            mt19937 gen(rd());  // Mersenne Twister 19937 generator
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
            cout << "Enter firstname: ";
            in >> person.mFirstname;
            cout << "Enter lastname: ";
            in >> person.mLastname;

            cout << "You have the option to generate scores randomly (y/N): ";
            string randomScoresInput;
            cin >> randomScoresInput;
            bool randomize = randomScoresInput == "y" || randomScoresInput == "Y";

            if (randomize) {
                person.mExamScore = person.generateRandomScore();
                person.mHomeworkScores.push_back(person.generateRandomScore());
                person.mHomeworkScores.push_back(person.generateRandomScore());
                person.mHomeworkScores.push_back(person.generateRandomScore());
            } else {
                cout << "Enter homework scores one by one (enter `-1` to finish): " << endl;
                double hwScoreInput;
                while ((in >> hwScoreInput) && hwScoreInput != -1) {
                    person.mHomeworkScores.push_back(hwScoreInput);
                }

                cout << "Enter exam score: ";
                in >> person.mExamScore;
            }

            return in;
        }

        friend ostream& operator<<(ostream& os, Person& person) {
            os << person.mFirstname << "            " << person.mLastname << "          " << fixed << setprecision(2) << person.mFinalGrade;
            return os;
        }
};

int main() {
    cout << "Enter the number of students: ";
    vector<Person> students;
    int numOfStudents = 0;
    cin >> numOfStudents;

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


    int counter = 0;
    for (int i = 0; i < numOfStudents; ++i) {
        cout << "\n• Enter data for student number " << ++counter << ":\n\n";
        Person p(hwFinalScoreType);
        cin >> p;
        students.push_back(p);
    }

    string hwCalcTypeTitle;
    if (hwFinalScoreType == AVERAGE) {
        hwCalcTypeTitle = "Ave.";
    } else {
        hwCalcTypeTitle = "Med.";
    }
    cout << "Name       Surname       Final_Point(" << hwCalcTypeTitle << ")" << endl;
    cout << "-------------------------------------------" << endl;

    for (int i = 0; i < students.size(); i++) {
        cout << students[i] << endl;
    }

    return 0;
}
