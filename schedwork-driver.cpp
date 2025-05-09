// main() program to test your schedule function.
// Feel free to modify this program in any way you need for testing.
// It will not be graded. 
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "schedwork.h"

using namespace std;

void printSchedule(const DailySchedule& sched);

int main()
{

    size_t dailyNeed = 1;
    size_t maxShifts = 3;
    bool expectedResult = true;
    AvailabilityMatrix avail = {
            {1},
            {1},
            {1}
    };

//    // Replace the matrix below with your test case
//    AvailabilityMatrix avail = {
//        {1, 1, 1, 1},
//        {1, 0, 1, 0},
//        {1, 1, 0, 1},
//        {1, 0, 0, 1}
//    };
    DailySchedule sched;
    bool solutionFound = schedule(avail, dailyNeed, maxShifts, sched);
    std::cout << "solution " << solutionFound << std::endl;
    if(solutionFound)
    {
        printSchedule(sched);
    }
    else
    {
        cout << "No solution found!" << endl;
    }
    return 0;
}

void printSchedule(const DailySchedule& sched)
{
    int day = 0;
    for(auto s : sched)
    {
        cout << "Day " << day << ": ";
        for(auto nurse : s)
        {
            cout << nurse << " ";
        }
        cout << endl;
        day++;
    }
}
