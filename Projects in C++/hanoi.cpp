#include <iostream>
using namespace std;

int hanoi(int n, char from, char to, char aux);

int hanoi(int n, char from, char to, char aux) {
    static int count = 0;
    count++;

    if(n == 1) {
        cout <<"Move disk " << n <<" from " << from <<" to " << to << endl;
        return count;
    }
    hanoi(n-1, from, aux, to);
    cout <<"Move disk " << n <<" from " << from <<" to " << to << endl;
    hanoi(n-1, aux, to, from);
    return count;
}