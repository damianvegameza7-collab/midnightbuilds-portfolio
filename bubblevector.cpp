#include <iostream>
#include <vector>
using namespace std;

void bubble(vector <int> number) {
    for(int i = 0; i < number.size()-1; i++) {
        if(number[i] >number[i+1])
        swap(number[i], number[i+1]);
    }
}
void print(vector <int> number) {
    for(int i = 0; i < number.size(); i++) 
    cout << number[i] << " ";
    cout << endl;
}
int main() {
    const int N = 41;
    vector<int> number = {86, 43, 54, 98, 10, 17, 81, 65, 12, 4, 43, 24, 67, 42, 31};
    for(int i=0; i < N-1; i++) {
        bubble(number);
        print(number);
    }
}