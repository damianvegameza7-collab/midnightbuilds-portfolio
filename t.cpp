#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

const int NUMCOURSE = 2;
struct Student{
    int id;
    string name;
    int score[NUMCOURSE];
    int sum;
    double avg;
    Student(int i, string n, int s[]) {
        id = i; name = n; sum = 0;
    for(int i = 0; i < NUMCOURSE; i++) {
        score[i] = s[i];
        sum += score[i];
    }
    avg = sum / NUMCOURSE;
    }

    void printout() {
        cout << id <<"\t" << name <<"\t";
        for(int i = 0; i <NUMCOURSE; i++)
        cout << score[i] << "\t";
        cout <<"sum " << sum << "\tavg" << avg << endl;     
    }
    
};

    void makeStudentVector(vector<Student> &students) {
    ifstream ifs("Students.txt");
        if(!ifs) {
    cout <<"Failed to open file" << endl;
    return;
}
    int id, s[NUMCOURSE];
    string name;
    while(ifs >> id >> name) {
        for(int i = 0; i<NUMCOURSE; i++) {
            ifs >> s[i];
        }
        students.push_back(Student(id, name, s));
}
    ifs.close();
    }
int main() {
    vector<Student> students;
    makeStudentVector(students);
    for(auto s : students) {
        s.printout();
        //sortbykeys(students, 1, 0);
    }
}