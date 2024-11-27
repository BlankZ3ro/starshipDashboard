#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Starship.h"

void showFileContents(const std::string& filename) {

    /*

    Purpose: For printing the contents of a text file

    No input, only outputs contents of specified file

    */

    std::ifstream fin(filename);
    std::cout << "CONTENTS OF " << filename << "\n=======================\n";
    std::string line;
    while (std::getline(fin, line)) {
        std::cout << line << std::endl;
    }
    std::cout << "=======================\n\n";
}

std::vector<Starship> loadFromFile(const std::string& filename) {

    /*

    Purpose: For loading the starships and their mission data for current
    session

    NO input, only an output and populating the myStarshipFleet vector in main

    */


    int SHIP_SAVE_SIZE = 0;
    std::vector<Starship> saveFileShips;

    std::ifstream fin{ "saveFile.txt" };
    fin >> SHIP_SAVE_SIZE;

    for (int i = 0; i < SHIP_SAVE_SIZE; i++) {
        int id = 0;
        std::string name = "";
        float capacity = 0;
        float dailyRate = 0;
        int MISSION_SIZE = 0;

        fin >> id;
        std::cout << id << std::endl;
        fin >> name;
        std::cout << name << std::endl;
        fin >> dailyRate;
        std::cout << dailyRate << std::endl;
        fin >> capacity;
        std::cout << capacity << std::endl;

        Starship loadedStarship(id, name, dailyRate, capacity);
        saveFileShips.push_back(loadedStarship);

        fin >> MISSION_SIZE;

        for (int j = 0; j < MISSION_SIZE; j++) {
            float hoursSpent = 0;
            int numRefueling = 0;
            int missionStart = 0;
            int missionEnd = 0;

            fin >> hoursSpent;
            std::cout << hoursSpent << std::endl;
            fin >> numRefueling;
            std::cout << numRefueling << std::endl;
            fin >> missionStart;
            std::cout << missionStart << std::endl;
            fin >> missionEnd;
            std::cout << missionEnd << std::endl;

            Mission loadedMission(numRefueling, missionStart, missionEnd, hoursSpent);
            saveFileShips.at(i).setMissionLog().push_back(loadedMission);
        }
    }

    std::cout << "Load Finished" << std::endl;
    return saveFileShips;

}

void saveToFile(const std::vector<Starship>& starships, const std::string& filename) {

    /*

    Purpose: For saving current Starship and mission data to the "saveFile.txt"
    file.

    No input expected, only console output and population of starship data
    into "saveFile.txt"

    */


    std::ofstream fout{ "saveFile.txt" };

    int SIZE = starships.size();

    fout << SIZE << std::endl;

    for (int i = 0; i < SIZE; i++) {
        fout << starships.at(i).getShipID() << std::endl;
        fout << starships.at(i).getShipName() << std::endl;
        fout << starships.at(i).getDailyRate() << std::endl;
        fout << starships.at(i).getFuelCapacity() << std::endl;

        int MISSION_SIZE = 0;
        MISSION_SIZE = starships.at(i).getMissionLog().size();

        fout << MISSION_SIZE << std::endl;

        for (int j = 0; j < MISSION_SIZE; j++) {
            fout << starships.at(i).getMissionLog().at(j).getHoursSpent();
            fout << std::endl;
            fout << starships.at(i).getMissionLog().at(j).getNumRefuelings();
            fout << std::endl;
            fout << starships.at(i).getMissionLog().at(j).getMissionStart();
            fout << std::endl;
            fout << starships.at(i).getMissionLog().at(j).getMissionEnd();
            fout << std::endl;

        }
    }

    std::cout << "Save Successful" << std::endl;

    fout.close();
    showFileContents(filename);
}

void clearSaveData(std::vector<Starship>& starships, const std::string& filename) {

    /*

    Purpose: Removing all of the contents of the "saveFile.txt" file

    NO input, only console output and clearing of all data in the
    "saveFile.txt" file.

    */


    std::ofstream fout{ "saveFile.txt" };

    starships.clear();
    fout << "" << std::endl;
    fout.close();

    std::cout << "Clear Successful" << std::endl;
    showFileContents(filename);
}



