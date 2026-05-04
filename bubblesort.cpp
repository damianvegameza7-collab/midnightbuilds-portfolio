#include <iostream>
using namespace std;

void bubble(int *ptr, int N, int phase) {
    for(int i = 0; i <N-phase-1; i++) {
        if(ptr[i] > ptr[i+1])
        swap(ptr[i], ptr[i+1]);
    }
}

void print(int *ptr, int N) {
    for(int i= 0; i <N; i++)
        cout << ptr[i] << " ";
        cout << endl;
}
int main() {
    const int N = 14;
    int number[N] = {5, 1, 2, 7, 6, 10, 4, 32};
    
    for(int i = 0; i<N-1; i++)
        bubble(number, N, i);
        print(number, N);

}