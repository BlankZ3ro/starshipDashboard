#include <iostream>      // For input/output (std::cout, std::cin)
#include <string>        // For handling std::string
#include <vector>        // For handling std::vector (missions log)
#include <ctime>         // For getting the current time (std::time)
#include <limits>        // For input validation (std::numeric_limits)
#include "Helper.h"
#include "Starship.h"
#include "saveToFile.h"


Starship* findStarship(int id, const std::vector<Starship>& starships) {

    /*

Purpose: Takes a starshipID and a list of starships, finds the corresponding
ship, and returns a reference to the Starship. If not found, return a reference
to a default Starship (ID=0,name="",etc). (Optional: you can return a pointer
instead. This would allow the return to be a null pointer if you don't
find a Starship.)

    */


    const int SIZE = starships.size();
    for (int i = 0; i < SIZE; i++) {

        if (starships.at(i).getShipID() == id) {

            return const_cast<Starship*>(&starships.at(i));
        }
    }

    return nullptr;

}


double calculateMissionCost(const Starship& ship, int missionIndex) {
    /*

Purpose: Calculates and returns the cost of a specific mission based on the
formula:

cost=dailyRate * (endStardate - startStardate) + numRefuelings * fuelCapacity
* 5.

    */

    if (ship.getMissionLog().at(missionIndex).getMissionEnd() == 0) {
        return (ship.getDailyRate() * (getEpochTime()
            - ship.getMissionLog().at(missionIndex).getMissionStart())
            + ship.getMissionLog().at(missionIndex).getNumRefuelings()
            * ship.getFuelCapacity() * 5);
    }
    else {
        return (ship.getDailyRate() *
            (ship.getMissionLog().at(missionIndex).getMissionEnd()
                - ship.getMissionLog().at(missionIndex).getMissionStart())
            + ship.getMissionLog().at(missionIndex).getNumRefuelings()
            * ship.getFuelCapacity() * 5);

    }
}

double calculateTotalCost(const Starship& ship) {
    /*

    Purpose: Calculates and returns the total cost for all the missions
    completed by the starship.

    */
    int SIZE = ship.getMissionLog().size();

    double totalCost = 0;


    for (int i = 0; i < SIZE; i++) {

        totalCost += calculateMissionCost(ship, i);

    }

    return totalCost;

}

double calculateAverageTime(const Starship& ship) {

    /*

    Purpose: Used to calculate a ship ship's average hours spent

    expecting return of a double with no user inputs.

    */

    int SIZE = ship.getMissionLog().size();
    float timeToCalculate = 0;

    for (int i = 0; i < SIZE; i++) {

        timeToCalculate += ship.getMissionLog().at(i).getHoursSpent();

    }

    return timeToCalculate / SIZE;

}

double calculateAverageRefueling(const Starship& ship) {
    /*

    Purpose: Used to calculate a ship ship's average number of refuelings

    expecting return of a double with no user inputs.

    */


    int SIZE = ship.getMissionLog().size();
    int refuelingsToCalculate = 0;

    for (int i = 0; i < SIZE; i++) {

        refuelingsToCalculate += ship.getMissionLog().at(i).getNumRefuelings();

    }

    return refuelingsToCalculate / SIZE;


}

double calculateAverageNumOfDaysSpent(const Starship& ship) {

    /*

    Purpose: Used to calculate a ship number of days spent

    expecting return of a double with no user inputs.

    */

    int SIZE = ship.getMissionLog().size();
    float hoursSpentTotal = 0;

    for (int i = 0; i < SIZE; i++) {

        hoursSpentTotal += ship.getMissionLog().at(i).getHoursSpent();

    }

    return hoursSpentTotal / 24;


}

void costBreakDownReport(const std::vector<Starship>& starships) {

    /*
    Purpose: To print out a report showing mission by mission costs
    */


    for (int i = 0; i < starships.size(); i++) {

        std::cout << "/------Mission Cost Breakdown Report for ";
        std::cout << starships.at(i).getShipName();
        std::cout << "------\\" << std::endl;

        for (int j = 0; j < starships.at(i).getMissionLog().size(); j++) {

            std::cout << "| Costs for mission " << j + 1 << ": ";
            std::cout << calculateMissionCost(starships.at(i), j) << std::endl;
            std::cout << "| Daily Rate: " << starships.at(i).getDailyRate();
            std::cout << "\n" << "| Start/End Stardate Difference: ";

            if (starships.at(i).getMissionLog().at(j).getMissionEnd() == 0) {

                std::cout << "ONGOING" << std::endl;
            }
            else {

                std::cout << starships.at(i).getMissionLog().at(j).getMissionEnd()
                    - starships.at(i).getMissionLog().at(j).getMissionStart();
                std::cout << std::endl;
            }

            std::cout << "| Number of Refuelings: ";
            std::cout << starships.at(i).getMissionLog().at(j).getNumRefuelings();
            std::cout << "\n" << "| Fuel Capacity: ";
            std::cout << starships.at(i).getFuelCapacity() << std::endl;
            std::cout << "| Hours Tracked: ";
            std::cout << starships.at(i).getMissionLog().at(j).getHoursSpent();
            std::cout << "\n" << "|" << std::endl;
        }

    }

}

void totalCostReport(const std::vector<Starship>& starships) {

    /*
    Purpose: to print a report for a specific ship found by user input of the
    ship's ID
    */

    int findShipID = 0;
    std::cout << "| ship ID: ";
    findShipID = getInt();
    Starship* starshipToReport = findStarship(findShipID, starships);
    std::cout << "/------Total Cost Report------\\" << std::endl;
    std::cout << "| Ship Name: " << starshipToReport->getShipName();
    std::cout << std::endl << "| Total Costs: ";
    std::cout << calculateTotalCost(*starshipToReport) << std::endl;
    std::cout << "|" << std::endl;

    for (int i = 0; i < starshipToReport->getMissionLog().size(); i++) {

        std::cout << "| Costs for mission " << i + 1 << ": ";
        std::cout << calculateMissionCost(*starshipToReport, i) << std::endl;
        std::cout << "| Daily Rate: " << starshipToReport->getDailyRate();
        std::cout << "\n" << "| Start/End Difference: ";

        if (starshipToReport->getMissionLog().at(i).getMissionEnd() == 0) {

            std::cout << "ONGOING" << std::endl;

        }
        else {

            std::cout << starshipToReport
                ->getMissionLog().at(i).getMissionEnd()
                - starshipToReport->getMissionLog().at(i).getMissionStart();
            std::cout << std::endl;

        }

        std::cout << "| Number of Refuelings: ";
        std::cout << starshipToReport
            ->getMissionLog().at(i).getNumRefuelings();
        std::cout << std::endl;
        std::cout << "| Fuel Capacity: "
            << starshipToReport->getFuelCapacity();
        std::cout << std::endl;
        std::cout << "| Hours Tracked: ";
        std::cout << starshipToReport->getMissionLog().at(i).getHoursSpent();
        std::cout << "\n" << "|" << std::endl;


    }
    std::cout << "/---Mission Statistics Report---\\" << std::endl;
    std::cout << "|" << std::endl;
    std::cout << "| Average Time Spent: ";
    std::cout << calculateAverageTime(*starshipToReport) << std::endl;
    std::cout << "| Average Refueling: ";
    std::cout << calculateAverageRefueling(*starshipToReport) << std::endl;
    std::cout << "| Earth Days Spent: ";
    std::cout << calculateAverageNumOfDaysSpent(*starshipToReport) << std::endl;

    std::cout << "\\-----------------------------/\n";



}

void startEndMissionMenu(std::vector<Starship>& starships) {

    /*

    Purpose: Takes in user char inputs, outputs based on that choice between
    start, end mission or exit.

    */

    char userInput = 'z';

    std::cout << "/-------------------------------------------\\" << std::endl;
    std::cout << "| Would you like to Start or End a Mission? |" << std::endl;
    std::cout << "|                                           |" << std::endl;
    std::cout << "| (s/S): Start Mission                      |" << std::endl;
    std::cout << "| (n/N): End Mission                        |" << std::endl;
    std::cout << "| (e/E): Back to dashboard                  |" << std::endl;
    std::cout << "\\-------------------------------------------/" << std::endl;

    while (std::cin >> userInput) {
        int findShipID = 0;


        if (userInput == 's' || userInput == 'S') {
            std::cout << "Starting Mission" << std::endl;

            std::cout << "Input a ship's ID";
            std::cin >> findShipID;
            (findStarship(findShipID, starships))->startMission();

            break;
        }
        else if (userInput == 'n' || userInput == 'N') {
            std::cout << "Ending Mission" << std::endl;

            std::cout << "Input a ship's ID: ";
            std::cin >> findShipID;

            (findStarship(findShipID, starships))->endMission();

            break;
        }
        else if (userInput == 'e' || userInput == 'E') {
            std::cout << "Exiting Start/End Mission" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid input detected" << std::endl;
            std::cout << "/-------------------------------------------\\";
            std::cout << std::endl;
            std::cout << "| Would you like to Start or End a Mission? |";
            std::cout << std::endl;
            std::cout << "|                                           |";
            std::cout << std::endl;
            std::cout << "| (s/S): Start Mission                      |";
            std::cout << std::endl;
            std::cout << "| (n/N): End Mission                        |";
            std::cout << std::endl;
            std::cout << "| (e/E): Back to dashboard                  |";
            std::cout << std::endl;
            std::cout << "\\-------------------------------------------/";
            std::cout << std::endl;
        }
    }

}

void refuelStarshipMenu(std::vector<Starship>& starships) {
    /*

    Purpose: Takes in user int inputs for a ship ID, where the inputted ship
    will "refuel". See refuel function for more details.

    */


    std::cout << "Input ship ID of ship you would like to refuel" << std::endl;
    std::cout << "Ship ID: ";
    (findStarship(getInt(), starships))->refuel();

}

void trackHoursMenu(Starship& ship) {
    /*

    Purpose: Takes in user int inputs for a ship ID and hours, assigning the
    hours to the ship with the same shipID.

    */

    if (!ship.getMissionLog().empty()) {

        if (ship.getMissionLog().back().getMissionEnd() == 0) {

            //float newHoursToTrack = 0;

            std::cout << "How many hours did this starship spend?" << std::endl;
            std::cout << "Hours Spent: ";

            Mission& lastMission = ship.setMissionLog().back();
            lastMission.trackHoursSpent(getFloat());
            std::cout << lastMission.getHoursSpent() << std::endl;

        }
        else if (ship.getMissionLog().back().getMissionEnd() != 0) {

            std::cout << "Previous mission has already concluded" << std::endl;
        }
        return;
    }

    else if (ship.getMissionLog().empty()) {

        std::cout << "No mission to track hours for, please start a ";
        std::cout << "mission before tracking hours" << std::endl;
    }

}

void calculateMissionCostsMenu(const std::vector<Starship>& starships) {

    /*

    Purpose: Takes in user char input, to choose between the 3 different options
    breakdown report, total cost report, and exit.

    It will then output based on which char you input.

    */

    char userInput = 'z';

    std::cout << "/-------------------------------------------\\" << std::endl;
    std::cout << "|     Would you like the BDR or TCR?        |" << std::endl;
    std::cout << "|                                           |" << std::endl;
    std::cout << "| (b/B): Breakdown Report (All ships)       |" << std::endl;
    std::cout << "| (t/T): Total Cost Report (single ship)    |" << std::endl;
    std::cout << "| (e/E): Back to dashboard                  |" << std::endl;
    std::cout << "\\-------------------------------------------/" << std::endl;

    while (std::cin >> userInput) {
        int findShipID = 0;


        if (userInput == 'b' || userInput == 'B') {

            std::cout << "| Breakdown Report Selected" << std::endl;
            costBreakDownReport(starships);

            break;
        }
        else if (userInput == 't' || userInput == 'T') {

            std::cout << "| Total Cost Report Selected" << std::endl;
            totalCostReport(starships);

            break;
        }
        else if (userInput == 'e' || userInput == 'E') {
            std::cout << "Exiting Reports Menu" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid input detected" << std::endl;
            std::cout << "/-------------------------------------------\\";
            std::cout << std::endl;
            std::cout << "|     Would you like the BDR or TCR?        |";
            std::cout << std::endl;
            std::cout << "|                                           |";
            std::cout << std::endl;
            std::cout << "| (b/B): Breakdown Report (All ships)       |";
            std::cout << std::endl;
            std::cout << "| (t/T): Total Cost Report (single ship)    |";
            std::cout << std::endl;
            std::cout << "| (e/E): Back to dashboard                  |";
            std::cout << std::endl;
            std::cout << "\\-------------------------------------------/";
            std::cout << std::endl;
        }
    }

}

void missionLogMenu(const std::vector<Starship>& starships) {

    /*

    Purpose: Prints out missionLogs for each starship found in starships.

    */

    for (int i = 0; i < starships.size(); i++) {

        if (starships.at(i).getMissionLog().empty()) {
            std::cout << "No Entries to report" << std::endl;
            return;
        }

        std::cout << "/-----" << starships.at(i).getShipName();
        std::cout << " Logs-----\\" << std::endl;
        starships.at(i).printMissionLog();
    }
}

void printDashboardOptions() {

    /*

    Purpose: To print out all of the different menu choices.

    */

    std::cout << "/------------------------------------------\\" << std::endl;
    std::cout << "|         Fleet Commander Dashboard        |" << std::endl;
    std::cout << "| 1: Create New Starship                   |" << std::endl;
    std::cout << "| 2: Start/End Mission                     |" << std::endl;
    std::cout << "| 3: Refuel Starship(s)                    |" << std::endl;
    std::cout << "| 4: Track Hours                           |" << std::endl;
    std::cout << "| 5: View Mission Log                      |" << std::endl;
    std::cout << "| 6: Calculate Mission Costs               |" << std::endl;
    std::cout << "| 7: Save Data                             |" << std::endl;
    std::cout << "| 8: Load Data                             |" << std::endl;
    std::cout << "| 9: Clear Data                            |" << std::endl;
    std::cout << "| 10: End Program                          |" << std::endl;
    std::cout << "\\------------------------------------------/" << std::endl;
}

int main() {

    std::vector<Starship> myStarshipFleet;
    int dashboardSelect;
    bool isGameRunning = true;
    printDashboardOptions();
    while (isGameRunning == true) {

        if (!(std::cin >> dashboardSelect) || dashboardSelect < 1
            || dashboardSelect > 10) {

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input" << std::endl;
            printDashboardOptions();
            continue;
        }

        if (dashboardSelect == 1) {

            myStarshipFleet.push_back(Starship::makeStarship());
            printDashboardOptions();

        }
        else if (dashboardSelect == 2) {

            startEndMissionMenu(myStarshipFleet);
            printDashboardOptions();

        }
        else if (dashboardSelect == 3) {

            refuelStarshipMenu(myStarshipFleet);
            printDashboardOptions();

        }
        else if (dashboardSelect == 4) {

            std::cout << "Input Ship ID: ";
            trackHoursMenu(*findStarship(getInt(), myStarshipFleet));
            printDashboardOptions();
        }
        else if (dashboardSelect == 5) {

            missionLogMenu(myStarshipFleet);
            printDashboardOptions();

        }
        else if (dashboardSelect == 6) {

            calculateMissionCostsMenu(myStarshipFleet);
            printDashboardOptions();

        }
        else if (dashboardSelect == 7) {

            //Save
            saveToFile(myStarshipFleet, "saveFile.txt");
            printDashboardOptions();
        }
        else if (dashboardSelect == 8) {

            //Load
            myStarshipFleet = loadFromFile("saveFile.txt");
            printDashboardOptions();

        }
        else if (dashboardSelect == 9) {
            //Clear
            clearSaveData(myStarshipFleet, "saveFile.txt");
            printDashboardOptions();
        }
        else if (dashboardSelect == 10) {
            isGameRunning = false;
            std::cout << "\\------------Exiting Application------------/\n";
            return 0;
        }

        else {

            std::cout << "There seems to have been an issue when selecting\n";

        }
    }
    return 0;
}