#pragma once

#include <string>
#include <ctime>         // For getting the current time (std::time)
#include <iostream>
#include "Helper.h"
class Mission {
public:
    Mission(int numRefuelings, int missionStartStardate, int missionEndStardate, float hoursSpent); //After construction...numRefuelings should be 0, missionStartStardate should system's time, and missionEndStardate should start at 0

    // Getters
    int getNumRefuelings() const;
    int getMissionStart() const;
    int getMissionEnd() const;
    float getHoursSpent() const;

    // Setters
    void endMission(); //use system's time
    void refuel();
    void trackHoursSpent(float hoursToTrack);

private:
    int numRefuelings;
    float hoursSpent;
    int missionStartStardate;
    int missionEndStardate; // 0 indicates an ongoing mission
};

