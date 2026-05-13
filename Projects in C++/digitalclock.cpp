#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;
int main() {
     time_t t = time(NULL);
    tm *timePtr = localtime(&t);


    int hours = (timePtr-> tm_hour);
    int minutes =(timePtr -> tm_min);
    int seconds = (timePtr -> tm_sec);




while(true) {
    system("clear");


    cout <<"The digital time is: " << endl;
    cout <<"    |" << hours <<"    |" << minutes <<"    |" << seconds <<"     |" << endl;

    this_thread::sleep_for(chrono::seconds(1));
    seconds++;

    if(seconds >= 60) {
        seconds = 1;
        minutes++;
    }
    if(minutes >= 60) {
        minutes = 0;
        hours++;
    }
    if(hours > 24) {
        hours = 00;
    }
}
return 0;

}