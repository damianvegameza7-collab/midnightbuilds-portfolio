#include <iostream>
#include <string>
using namespace std;

int countLetter(string str, char ch);

int countLetter(string str, char ch) {
    if(str.empty())
    return 0;

    int match = (str[0] == ch ? 1:0);
    int result = countLetter(str.substr(1), ch);
    return match + result;
}