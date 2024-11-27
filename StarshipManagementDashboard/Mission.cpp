#pragma once
#include <string>
#include <iostream>
#include <ctime>
#include "Mission.h"

Mission::Mission(int numRefuelings, int missionStartStardate, int missionEndStardate, float hoursSpent)
    : numRefuelings(numRefuelings),
    missionStartStardate(missionStartStardate),
    missionEndStardate(missionEndStardate),
    hoursSpent(hoursSpent) {}

/*
After construction...numRefuelings should be 0, missionStartStardate
should system's time, and missionEndStardate should start at 0
*/

// Getters
int Mission::getNumRefuelings() const {
    return numRefuelings;
}

int Mission::getMissionStart() const {
    return missionStartStardate;
}

int Mission::getMissionEnd() const {
    return missionEndStardate;
}

float Mission::getHoursSpent() const {
    return hoursSpent;
}

// Setters
void Mission::endMission() {
    missionEndStardate = (getEpochTime());
} //use system's time
void Mission::refuel() {
    numRefuelings++;
}
void Mission::trackHoursSpent(float hoursToTrack) {
    hoursSpent += hoursToTrack;
}
