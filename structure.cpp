#include <iostream>
#include <vector>
#include "struct.hpp"
using namespace std;
int main() {

    Student s1, s2;
    s1.setSid(1001);
    s1.setSname("Smith");
    cout << s1.getSid() << " " << s1.getSname() << endl;
    s2 = s1;
    cout << s2.getSid() <<" " << s2.getSname() << endl;

    //Array of student
    Student students[3];
    students[0].setSid(1001);
    students[0].setSname("Smith");
    students[1].setAll(1002, "John");
    students[2] = students[0];
    printStudent(students, 3);

    //Vector of student
    vector<Student> studentVec;
    studentVec.push_back({1001, "Smith"});
    studentVec.push_back({1002, "John"});
    studentVec.push_back({1003, "Alice"});
    printStudent(studentVec);
}