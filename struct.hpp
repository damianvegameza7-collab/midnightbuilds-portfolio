#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Student{
    private:
    int sid;
    string sname;

    public:
    Student() {
        sid = 0;
        sname = "";
    }
    Student(int id, string name) {
        sid = id;
        sname = name;
    }

    int getSid() {
        return sid;
    }

    void setSid(int id) {
        sid = id;
    }

    string getSname() {
        return sname;
    }
    void setSname(string name) {
        sname = name;
    }
    void setAll(int id, string name) {
        sid = id;
        sname = name;
    }
    void printsid() {
        cout << sid << endl;
    }
    void printname() {
        cout << sname << endl;
    }
    void printAll() {
        cout << sid <<" " << sname << endl;
    }
    };
    void printStudent(Student *ptr, int size) {
        for(int i = 0; i < size; i++)
            ptr[i].printAll();
    }
    void printStudent(const vector<Student> &v) {
        for(auto s : v)
        s.printAll();
    }