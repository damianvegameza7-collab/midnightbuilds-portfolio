#include <iostream>
using namespace std;
int main() {
    int NUM_ROWS = 6;
    int NUM_COLS = 5;
    int numbers(NUM_ROWS)(NUM_COLS) = {2, 7, 9, 6, 4},
    {6, 1, 8, 10},
    {4, 3, 7, 2, 9},
    {9, 9, 0, 3, 1},
    {8, 8, 7, 8, 9},
    {1, 2, 1, 2, 3};

    //maxrow is not defined issue
       for(int i = 0; i < NUM_ROWS; i++) {
        int total = 0;
        for (int j = 0; j < NUM_COLS; j++) {
            total += numbers[i][j];

            if(j == 0 || maxsum < total) {
            maxsum = total; maxrow = i;        
            }
        }
}
    cout <<"The sum of row " << maxrow <<" is" << endl;
}