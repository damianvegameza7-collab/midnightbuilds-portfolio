#include "hanoi.cpp"
#include <iostream>
using namespace std;
int main() {
    cout <<"hanoi(3) moves = " << hanoi(3, 'A', 'C', 'B') << endl; 
    cout <<"hanoi (4) moves = " << hanoi(4, 'A', 'C', 'B') << endl;
}