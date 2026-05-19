#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    //Our two variables for F and C
    double C;
    double F;

    cout <<"Enter temperature in Celsius: " << endl;
    cin >> C;

    F= (9 / 5.0) * C + 32;
    cout << setprecision(2) << fixed;
    cout <<"The temperature in Farenheit is: " << F << endl;
        return 0;
}