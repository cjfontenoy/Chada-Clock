//
// Created by Cody Fontenoy on 5/22/20.
//

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

using namespace std;


class Clock{
    struct tm* currtime;
    int hoursAdded = 0;
    int minutesAdded = 0;
    int currentMinutes;
    int currentSeconds;
    int secondsAdded = 0;

    void setTime() {
        time_t ct = time(0);
        currtime = localtime(&ct);
        currentSeconds = currtime->tm_sec;
        currentMinutes = currtime->tm_min;
    }

    void displayTime() {
        string amPm = AmPm();
        cout << "**************************" << "       **************************" << endl;
        cout << "*      12-Hour Clock     *" << "       *      24-Hour Clock     * " << endl;
        cout << "*        " << setfill('0') << setw(2) << getTwelveFormattedHour() << ":"
             << setw(2) << getMinutes() << ":"
             << setw(2) << getSeconds() << " "<< amPm << "     *       ";
        cout << "*        " << setfill('0') << setw(2) << getTwentyFourFormattedHour() << ":"
             << setw(2) << getMinutes() << ":"
             << setw(2) << getSeconds() << "        *" << endl;
        cout << "**************************" << "       **************************" << endl;
    }

    string AmPm() {
        setfill('0');
        setw(2);
        int hour = currtime->tm_hour;
        hour = hour + hoursAdded;
        hour = hour % 24;
        if(hour > 11){
            return "PM";
        }else{
            return "AM";
        }
    }

    int getMinutes() {
        setfill('0');
        setw(2);
        int minutes = currentMinutes;
        return minutes;
    }

    int getSeconds() {
        setfill('0');
        setw(2);
        int seconds = currtime->tm_sec;
        seconds = seconds + secondsAdded;
        seconds = seconds % 60;
        return seconds;
    }

    int getTwelveFormattedHour() {
        setfill('0');
        setw(2);
        int hour = currtime->tm_hour;
        hour = hour + hoursAdded;
        hour = hour % 12;
        if(hour == 0) {
            hour = 12;
        }
        return hour;
    }

    int getTwentyFourFormattedHour() {
        setfill('0');
        setw(2);
        int hour = currtime->tm_hour;
        hour = hour + hoursAdded;
        hour = hour % 24;
        return hour;
    }

    int displayMenu() {
        int input= 700;
        cout << "**************************" << endl;
        cout << "* 1 - Add One Hour       *" << endl;
        cout << "* 2 - Add One Minute     *" << endl;
        cout << "* 3 - Add One Second     *" << endl;
        cout << "* 4 - Exit Program       *" << endl;
        cout << "**************************" << endl;
        cin >> input;
        return input;
    }

    void addMinute() {
        minutesAdded = minutesAdded + 1;
        currentMinutes = currtime->tm_min + minutesAdded;
        if (currentMinutes == 60) {
            hoursAdded++;
            currentMinutes = 0;
            minutesAdded = 0;
        }

    }

    void addSecond() {
        secondsAdded = secondsAdded + 1;
        currentSeconds = currtime->tm_sec + secondsAdded;
        if (currentSeconds== 60) {
            minutesAdded++;
            currentSeconds = 0;
            secondsAdded = 0;
        }
    }


public:
    int runClock() {
        setTime();
        displayTime();
        int userInput = displayMenu();
        while (userInput != 4) {
            setTime();
            if (userInput == 1) {
                hoursAdded = hoursAdded + 1;
                displayTime();
            } else if (userInput == 2) {
                addMinute();
                displayTime();
            } else {
                addSecond();
                displayTime();
            }
            userInput = displayMenu();
        }
        return 0;
    }
};