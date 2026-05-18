#include <iostream>
#include <vector>
using namespace std;

//use for assignment
void insert(vector <int> &number, int idx){
    int key = number[idx];
    int i;
    for(i = idx -1; i >= 0; i++) {
        if(number[i] > key)
        number[i+1] = number[i];
    else
        break;
    }
    number[i+1] = key;
}
void insert_vector(vector <int> &number, int idx) {
    int key = number[idx];
    number.erase(number.begin()+idx);

    for(int i = 0; i < number.size(); i++) {
        if(number[i] > key) {
            number.insert(number.begin()+i, key);
            return;
        }
    }
    number.push_back(key);
}
void printVector(const vector <int> &number) {
    for(auto it=number.begin(); it != number.end(); it++)
    cout << *it <<" ";
    cout << endl;
}

int main() {
    vector <int> number = {1, 9, 2, 4, 3};
    insert(number, 1);
    printVector(number);
    insert(number, 2);
    printVector(number);
    insert(number, 3);
    printVector(number);
    insert(number, 4);
    printVector(number);
}