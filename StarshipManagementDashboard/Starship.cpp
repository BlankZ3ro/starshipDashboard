#pragma once

#include <string>
#include <vector>
#include "Mission.h"
#include <iostream>
#include "Starship.h"

Starship::Starship(int id, const std::string& name, float rate, float capacity)
    : shipID(id), shipName(name), dailyRate(rate), fuelCapacity(capacity) {}

// Starship operations
void Starship::startMission() {
    /*

    Purpose: If the ship has no ongoing mission, starts a new mission using the
    current stardate (getEpochTime()). If the last mission has not ended,
    inform the user.

    Output: Displays relevant information about whether the mission was
    successfully started or if there was an issue.

    */

    if (!missionLog.empty()) {

        if (missionLog.back().getMissionEnd() == 0) {

            std::cout << "Mission has not ended yet" << std::endl;
            std::cout << "Please end previous mission before starting another";
            std::cout << std::endl;
        }
        if (missionLog.back().getMissionEnd() != 0) {

            std::cout << "Starting new Mission" << std::endl;
            missionLog.push_back(Mission{ 0, getEpochTime(), 0, 0.0 });
        }
        return;

    }

    else if (missionLog.empty()) {
        std::cout << "Starting the first mission" << std::endl;
        missionLog.push_back(Mission{ 0, getEpochTime(), 0, 0.0 });

    }

}
void Starship::endMission() {
    /*
    Purpose: Ends the most recent mission (if it is ongoing...endStardate==0) by
    setting the missionEndStardate to the current time.

    Output: Prints out details of the mission (start and end stardates,
    refuelings, etc.).
    */
    if (!missionLog.empty()) {

        if (missionLog.back().getMissionEnd() == 0) {

            std::cout << "Mission ended at stardate ";
            missionLog.back().endMission();
            std::cout << missionLog.back().getMissionEnd() << std::endl;
            return;
        }
        if (missionLog.back().getMissionEnd() != 0) {

            std::cout << "Previous mission has already ended" << std::endl;
            std::cout << "Start a new mission before ending a mission";
            std::cout << std::endl;
            return;
        }

    }
    else if (missionLog.empty()) {

        std::cout << "ship's mission log is empty" << std::endl;
        std::cout << "No missions in mission log" << std::endl;
        std::cout << "Start a mission before ending a mission" << std::endl;
        return;
    }

    return;

}

void Starship::refuel() {
    /*
    Purpose: Increments the refueling count for the ongoing mission
    (if endStardate==0).

    Output: Prints out how many times the starship has been refueled on the
    current mission.

    */

    if (!missionLog.empty()
        && missionLog.back().getMissionEnd() == 0) {

        missionLog.back().refuel();
        std::cout << "Refueling successfully logged with ";
        std::cout << missionLog.back().getNumRefuelings();
        std::cout << " refuelings this mission" << std::endl;
        return;

    }
    else if (!missionLog.empty()
        && missionLog.back().getMissionEnd() != 0) {

        std::cout << "There are no active missions currently, please start a ";
        std::cout << "Mission before logging refuelings" << std::endl;
        return;
    }
    else if (missionLog.empty()) {
        std::cout << "There are no active missions, please start a mission";
        std::cout << " before logging refueling" << std::endl;
        return;
    }

    return;

}

// Mission cost calculation
double Starship::calculateMissionCost(int missionIndex) const {
    /*
    Purpose: Calculates and returns the cost of a specific mission based on the
    formula:

    cost=dailyRate * (endStardate - startStardate) + numRefuelings
    * fuelCapacity * 5.
    */

    if (missionLog.at(missionIndex).getMissionEnd() == 0) {
        return (dailyRate * (getEpochTime()
            - missionLog.at(missionIndex).getMissionStart())
            + missionLog.at(missionIndex).getNumRefuelings() * fuelCapacity * 5);
    }
    else {
        return (dailyRate * (missionLog.at(missionIndex).getMissionEnd()
            - missionLog.at(missionIndex).getMissionStart())
            + missionLog.at(missionIndex).getNumRefuelings() * fuelCapacity * 5);

    }

}

double Starship::calculateTotalCost() const {
    /*

    Purpose: Calculates and returns the total cost for all the missions
    completed by the starship.

    */
    int SIZE = missionLog.size();

    double totalCost = 0;


    for (int i = 0; i < SIZE; i++) {

        totalCost += calculateMissionCost(i);

    }

    return totalCost;

}

// Mission logging
void Starship::printMissionLog() const {

    /*

    Purpose: prints out mission log for a singular starship passed through

    */

    std::cout << "/------Mission Logs------\\" << std::endl;
    std::cout << "|" << std::endl;

    for (int i = 0; i < missionLog.size(); i++) {

        std::cout << "| Costs for mission " << i + 1 << ": ";
        std::cout << calculateMissionCost(i) << std::endl;
        std::cout << "| Hours Spent: " << missionLog.at(i).getHoursSpent();
        std::cout << std::endl;
        std::cout << "| Number of Refuelings: ";
        std::cout << missionLog.at(i).getNumRefuelings() << std::endl;
        std::cout << "| Mission Start Stardate: ";
        std::cout << missionLog.at(i).getMissionStart() << std::endl;

        if (missionLog.at(i).getMissionEnd() == 0) {

            std::cout << "| Mission End Stardate: ONGOING" << std::endl;

        }
        else {

            std::cout << "| Mission End Stardate: ";
            std::cout << missionLog.at(i).getMissionEnd() << std::endl;

        }
        std::cout << "|" << std::endl;
    }
    std::cout << "\\-------------------------/\n";

}

Starship Starship::makeStarship() {
    /*
    Expecting a inputs of a int, a string, and 2 floats to fill the shipID,
    shipName, dailyRate and fuelCapacity

    Expecting an output of a new Starship
    */

    int id = 0;
    std::string name = "";
    float capacity = 0;
    float dailyRate = 0;

    std::cout << "Please input your ship's ID" << std::endl;
    std::cout << "Starship ID: ";

    while (std::cin >> id && id < 0) {
        std::cout << "No IDs can be negative, please input ";
        std::cout << "your ship's ID number" << std::endl;
        std::cout << "Ship ID: ";
    }
    std::cin.ignore();
    std::cin.clear();

    std::cout << "Starship Name: ";
    std::getline(std::cin, name);

    std::cout << "Daily Rate: ";
    while (std::cin >> dailyRate && dailyRate <= 0) {
        std::cout << "This is a business not a charity, try again";
        std::cout << std::endl;
        std::cout << "Daily Rate: ";

    }

    std::cout << "Fuel Capacity: ";
    while (std::cin >> capacity && capacity <= 0) {

        std::cout << "Ships can't fly without fuel! Please enter your ";
        std::cout << "Ship's fuel capacity" << std::endl;
        std::cout << "Fuel Capacity: ";

    }

    Starship newStarship(id, name, dailyRate, capacity);
    return newStarship;
};
// Getter
int Starship::getShipID() const {
    return shipID;
}
std::string Starship::getShipName() const {
    return shipName;
}
std::vector<Mission> Starship::getMissionLog() const {
    return missionLog;
}
std::vector<Mission>& Starship::setMissionLog() {
    /*
    Purpose is to return a reference of the starship's mission log that can
    be editted/modified
    */
    return missionLog;
}

float Starship::getDailyRate() const {
    return dailyRate;
}
float Starship::getFuelCapacity() const {
    return fuelCapacity;
}

int shipID;
std::string shipName;
float dailyRate;
float fuelCapacity;
std::vector<Mission> missionLog;
