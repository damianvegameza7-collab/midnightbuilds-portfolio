#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    const int N = 4000;
    string st[N]; char gender[N];
    int year[N]; string name[N]; int freq[N];

    ifstream inputfile;
    inputfile.open("Input.txt");
    if(!inputfile) {
        cerr <<"Unable to open file";
        exit(1);
    }
    int count = 0;
    while(inputfile >> st[count] >> gender[count] >> year[count] >> name[count] >> year[count]) {
        cout << st[count] <<" " << gender[count] <<" " << year[count] <<" " << name[count] <<" " << freq[count];
        count++;
    }
    inputfile.close();
    cout <<"Number of lines read: " << endl;

    for(int i = 0; i <= count; i++) {
        if(num[i].rfind("E", 0))
        cout << countLetter(s1, '1');
    }
     }