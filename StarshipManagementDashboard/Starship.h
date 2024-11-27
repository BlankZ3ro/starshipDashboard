#pragma once

#include <string>
#include <vector>
#include "Helper.h"
#include "Mission.h"

class Starship {
public:
    Starship(int id, const std::string& name, float rate, float capacity);

    // Starship operations
    void startMission();
    void endMission();
    void refuel();

    // Mission cost calculation
    double calculateMissionCost(int missionIndex) const;
    double calculateTotalCost() const;

    // Mission logging
    void printMissionLog() const;

    //Making
    static Starship makeStarship();

    // Getter
    int getShipID() const;
    std::string getShipName() const;
    std::vector<Mission> getMissionLog() const;
    std::vector<Mission>& setMissionLog();
    float getDailyRate() const;
    float getFuelCapacity() const;

private:
    int shipID;
    std::string shipName;
    float dailyRate;
    float fuelCapacity;
    std::vector<Mission> missionLog;
};