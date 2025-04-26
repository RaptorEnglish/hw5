#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

// helper function to see if a schedule is valid
bool is_valid(
        Worker_T worker,
        size_t day,
        const DailySchedule& sched,
        const AvailabilityMatrix& avail,
        const size_t maxShifts
) {
    // Check availability
    if (!avail[day][worker]) return false;

    // Count how many times this worker has already been scheduled
    size_t sched_count = 0;
    for (const auto& day_sched : sched) {
        if (std::find(day_sched.begin(), day_sched.end(), worker) != day_sched.end()) {
            sched_count++;
        }
    }
    if (sched_count >= maxShifts) return false;

    // Check if already scheduled for this day
    if (std::find(sched[day].begin(), sched[day].end(), worker) != sched[day].end()) return false;

    return true;
}


// backtracking function that tests solutions recursively
// backtracking function that tests solutions recursively
bool backtrack(
        DailySchedule& sched,
        const AvailabilityMatrix& avail,
        const size_t dailyNeed,
        const size_t maxShifts

) {
    size_t day = sched.size() - 1;

    // base case all days have been scheduled
    if (sched.size() == avail.size() && sched[day].size() >= dailyNeed) {
        return true;
    }

    // move to next day if daily need has been met
    if (sched[day].size() >= dailyNeed) {
        sched.push_back(std::vector<Worker_T>());
        return backtrack(sched, avail, dailyNeed, maxShifts);
    }

    // check each worker
    size_t n_workers = avail[0].size();
    for (Worker_T i = 0; i < n_workers; i++) {
        if (is_valid(i, day, sched, avail, maxShifts)) {
            sched[day].push_back(i);

            // continue branch
            if (backtrack(sched, avail, dailyNeed, maxShifts)) {
                return true;
            }

            // backtrack
            sched[day].pop_back();

        }

    }

    // if we couldn't fill current day, backtrack further
    if (sched[day].empty()) {
        sched.pop_back();
    }

    return false;
}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    // Add your code below

    // print schedule
    for (auto& row : avail) {
        for (auto x : row) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
    std::cout << dailyNeed << " " << maxShifts << std::endl;

    // add first entry to schedule
    sched.push_back(std::vector<Worker_T>());

    // use backtrack function
    if (backtrack(sched, avail, dailyNeed, maxShifts)) {
        return true;
    } else {
        return false;
    }


}

