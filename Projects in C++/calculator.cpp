#include <iostream>
using namespace std;
int main() {
    double num1, num2;
    char op;


    while(true) {
        cout <<"Enter an operator: To quit, enter q" << endl;
        cin >> op;

        if(op == 'q')
        break;

        cout << "Enter two integers" << endl;
        cin >> num1 >> num2;


        if(op == '+')
        cout <<"= " << num1 + num2 << endl;
        else if(op == '-')
        cout << "= " << num1 - num2 << endl;
        else if(op == '*')
        cout <<"= " << num1 * num2 << endl;
        else if(op == '/') {
       
        if(num2 != 0)
        cout <<"= " << num1 / num2 << endl;
        else
        cout <<"Error: divison by zero" << endl;
        }
        else
        cout <<"Unknown operator" << endl;
    }
    return 0;

}