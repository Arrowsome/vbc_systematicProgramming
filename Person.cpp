# include <string>
# include <iostream>
# include <vector>
# include <algorithm>
# include <iomanip>
using namespace std;

class Person {
    private:
        string mFirstname;
        string mLastname;
        double mExamScore;
        vector<double> mHomeworkScores;
        double mFinalGrade;

        double calcFinalGrade() {
            double hwFinalScore = calcAverage(mHomeworkScores);

            return (0.4 * hwFinalScore) + (0.6 * mExamScore);
        }

        double calcAverage(const vector<double>& numbers) {
            double sum = 0.0;

            for (const double& num : numbers) {
                sum += num;
            }

            return sum / numbers.size();
        }

    public:
        Person() {

        }

        Person(const Person& person) {
            mFirstname = person.mFirstname;
            mLastname = person.mLastname;
            mExamScore = person.mExamScore;
            mHomeworkScores = person.mHomeworkScores;
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

            int hwScore1;
            cout << "Enter homework score 1: ";
            cin >> hwScore1;
            person.mHomeworkScores.push_back(hwScore1);

            int hwScore2;
            cout << "Enter homework score 2: ";
            cin >> hwScore2;
            person.mHomeworkScores.push_back(hwScore2);

            int hwScore3;
            cout << "Enter homework score 3: ";
            cin >> hwScore3;
            person.mHomeworkScores.push_back(hwScore3);

            cout << "Enter exam score: ";
            in >> person.mExamScore;

            return in;
        }

        friend ostream& operator<<(ostream& os, Person& person) {
            os << person.mFirstname << "        " << person.mLastname << "      " << fixed << setprecision(2) << person.mFinalGrade;
            return os;
        }
};

int main() {
    cout << "Enter the number of students: ";
    vector<Person> students;
    int numOfStudents = 0;
    cin >> numOfStudents;


    int counter = 0;
    for (int i = 0; i < numOfStudents; ++i) {
        cout << "\n• Enter data for student number " << ++counter << ":\n\n";
        Person p;
        cin >> p;
        students.push_back(p);
    }

    cout << "Name       Surname       Final_Point(Aver.)" << endl;
    cout << "-------------------------------------------" << endl;

    for (int i = 0; i < students.size(); i++) {
        cout << students[i] << endl;
    }

    return 0;
}

