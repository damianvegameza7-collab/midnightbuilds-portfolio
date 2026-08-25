#include <iostream>
using namespace std;
int main() {
    int num[5] = {10, 20, 30, 40,  50};
    int num2[5] = {10, 20, 30, 40, 50};


    int *ptr;
    cout << num[4] << endl;
    cout << *(num+4) << endl;


    for(int i = 0; i< 5; i++) {
        cout << num[i] << " ";
        cout << endl;
    }
    for(int i = 0; i <5; i++) {
        cout << *(num+i) <<" ";
        cout << endl;
        ptr = num;
    }
    for(int i = 0;i <5; i++) {
        cout <<*(ptr + i) << " ";
        cout << endl;
        ptr = &num[2];
        cout << *ptr << endl;
    }
    for(int i = 0; i < 3; i++) {
        cout <<*(ptr+i) << " ";
        ptr = num2;
    }
}
