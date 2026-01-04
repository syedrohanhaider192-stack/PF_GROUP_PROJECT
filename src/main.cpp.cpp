// ---------------------------------------------
// Student Performance Management System
// Language: C++
// Course: Programming Fundamentals
// Description:
// This program manages student records,
// calculates grades and predicts performance.
// ---------------------------------------------

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Student {
    int roll;
    string name;
    string dept;

    float m1, m2, m3, m4, m5;
    float att;      // attendance
};

vector<Student> data;

// function declarations
void menu();
void addStd();
void showAll();
void findStd();
void updateStd();
void removeStd();
void predictStd();
void saveFile();

float calcAvg(Student s);
string getGrade(float avg);

// MAIN
int main() {

    int opt = 0;

    do {
        menu();
        cout << "Choose option: ";
        cin >> opt;

        if (opt == 1) addStd();
        else if (opt == 2) showAll();
        else if (opt == 3) findStd();
        else if (opt == 4) updateStd();
        else if (opt == 5) removeStd();
        else if (opt == 6) predictStd();
        else if (opt == 7) saveFile();
        else if (opt == 8) cout << "\nExiting program...\n";
        else cout << "Wrong option.\n";

    } while (opt != 8);

    return 0;
}

// SHOW MENU OPTIONS TO USER
void menu() {
    cout << "\n==============================\n";
    cout << " Student Performance System\n";
    cout << "==============================\n";
    cout << "1. Add Student\n";
    cout << "2. View Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Performance Prediction\n";
    cout << "7. Save To File\n";
    cout << "8. Exit\n";
}

// ADD NEW STUDENT RECORD
void addStd() {

    Student s;

    cout << "\nRoll No: ";
    cin >> s.roll;

    cin.ignore();
    cout << "Name: ";
    getline(cin, s.name);

    cout << "Department: ";
    getline(cin, s.dept);

    cout << "Enter 5 subject marks:\n";
    cin >> s.m1 >> s.m2 >> s.m3 >> s.m4 >> s.m5;

    cout << "Attendance (%): ";
    cin >> s.att;

    data.push_back(s);
    cout << "Student added.\n";
}

// DISPLAY ALL STUDENTS
void showAll() {

    if (data.size() == 0) {
        cout << "No data found.\n";
        return;
    }

    cout << "\nRoll   Name              Avg   Grade\n";
    cout << "-------------------------------------\n";

    for (int i = 0; i < data.size(); i++) {
        float avg = calcAvg(data[i]);
        cout << left << setw(6) << data[i].roll
             << setw(18) << data[i].name
             << setw(6) << fixed << setprecision(1) << avg
             << getGrade(avg) << endl;
    }
}

// SEARCH
void findStd() {

    int r;
    cout << "Enter roll to search: ";
    cin >> r;

    for (int i = 0; i < data.size(); i++) {
        if (data[i].roll == r) {

            float avg = calcAvg(data[i]);

            cout << "\nName: " << data[i].name << endl;
            cout << "Dept: " << data[i].dept << endl;
            cout << "Attendance: " << data[i].att << "%\n";
            cout << "Average: " << avg << endl;
            cout << "Grade: " << getGrade(avg) << endl;
            return;
        }
    }

    cout << "Student not found.\n";
}

// UPDATE
void updateStd() {

    int r;
    cout << "Roll to update: ";
    cin >> r;

    for (int i = 0; i < data.size(); i++) {
        if (data[i].roll == r) {

            cout << "Enter new marks:\n";
            cin >> data[i].m1 >> data[i].m2 >> data[i].m3
                >> data[i].m4 >> data[i].m5;

            cout << "New attendance: ";
            cin >> data[i].att;

            cout << "Updated.\n";
            return;
        }
    }

    cout << "Roll not found.\n";
}

// DELETE
void removeStd() {

    int r;
    cout << "Roll to delete: ";
    cin >> r;

    for (int i = 0; i < data.size(); i++) {
        if (data[i].roll == r) {
            data.erase(data.begin() + i);
            cout << "Deleted.\n";
            return;
        }
    }

    cout << "Roll not found.\n";
}

// AI PREDICTION
void predictStd() {

    int r;
    cout << "Roll for prediction: ";
    cin >> r;

    for (int i = 0; i < data.size(); i++) {
        if (data[i].roll == r) {

            float avg = calcAvg(data[i]);

            // Calculate prediction using average and attendance
            float est = (avg * 0.75) + (data[i].att * 0.25);

            if (est > 100) est = 100;

            cout << "\nPrediction (rough idea)\n";
            cout << "Average: " << avg << endl;
            cout << "Attendance: " << data[i].att << endl;
            cout << "Expected Score: " << est << endl;
            cout << "Expected Grade: " << getGrade(est) << endl;
            return;
        }
    }

    cout << "Student not found.\n";
}

// FILE SAVE
void saveFile() {

    ofstream out("students.txt");

    if (!out) {
        cout << "File error.\n";
        return;
    }

    for (int i = 0; i < data.size(); i++) {

        float avg = calcAvg(data[i]);

        out << "Roll: " << data[i].roll << endl;
        out << "Name: " << data[i].name << endl;
        out << "Dept: " << data[i].dept << endl;
        out << "Attendance: " << data[i].att << endl;
        out << "Average: " << avg << endl;
        out << "Grade: " << getGrade(avg) << endl;
        out << "---------------------\n";
    }

    out.close();
    cout << "Saved to students.txt\n";
}

// HELPERS
float calcAvg(Student s) {
    return (s.m1 + s.m2 + s.m3 + s.m4 + s.m5) / 5.0;
}

string getGrade(float a) {

    if (a >= 85) return "A";
    if (a >= 70) return "B";
    if (a >= 60) return "C";
    if (a >= 50) return "D";
    return "F";
}
