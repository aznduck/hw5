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

bool search(size_t day, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsWorked, size_t worker);
void addToSchedule(DailySchedule& sched, int row, int col, Worker_T id, vector<size_t>& shiftsWorked);
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
    vector<size_t> shiftsWorked(avail[0].size(), 0);
    size_t day = 0;
    size_t worker = 0;
    sched.resize(avail.size());
    if (search(day, avail, dailyNeed, maxShifts, sched, shiftsWorked, worker))
      return true;
    return false;
}

bool search(size_t day, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsWorked, size_t worker)
{
  if(day == avail.size()){
    cout << "solved";
    return true;
  }
  else
  {
    for(Worker_T w = worker; w < avail[0].size(); ++w)
    {
      if(avail[day][w] && shiftsWorked[w] < maxShifts)
      {
        sched[day].push_back(w);
        shiftsWorked[w]++;
        if (sched[day].size() == dailyNeed) {
                if (search(day + 1, avail, dailyNeed, maxShifts, sched, shiftsWorked, 0)) {
                    return true; 
                }
        } else {
        if(search(day, avail, dailyNeed, maxShifts, sched, shiftsWorked, w + 1)){
          return true;
        }
      }
      sched[day].pop_back();
      shiftsWorked[w]--;
    }
  }
  return false;
  }
}

