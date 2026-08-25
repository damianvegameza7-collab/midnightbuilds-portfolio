#include <iostream>
#include<vector>
#include <algorithm>
using namespace std;
int main() {
    vector<int> num(10);
    for(int i = 0; i <num.size(); i++) {
        num[i] = rand() % 100;
    }
    for(auto v: num)
        cout << v << " ";
    cout << endl;
    num.push_back(999);

    for(auto v: num)
    cout << v <<" ";
    cout << endl;

    vector<int>::iterator it = num.begin();
    num.insert(it+3, 555);
    num.erase(num.end()-1);
    cout << num.back() << endl;
    num.pop_back();
    sort(num.begin(), num.end());

    for(auto it = num.begin(); it != num.end(); it++) {
        cout << *it << " ";
    cout << "Found 77 in postion " << distance(num.begin(), find(num.begin(), num.end(), 77));
    cout << find(num.begin(), num.end(), 77) - num.begin() << endl;
    }
}