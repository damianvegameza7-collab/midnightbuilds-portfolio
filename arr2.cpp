#include <iostream>
using namespace std;

void printout(int *ptr, int size) {
    for(int i = 0; i <size; i++) {
        cout << ptr[i] << " ";
        cout << endl;
    }
}

int main() {
    const int N =5;
    int num[N] = {10, 20, 30, 40, 50};
    printout(num, N);
    printout(&(num[2]), 3);

    int num2[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    printout(num2, 10);
}