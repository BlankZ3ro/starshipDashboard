#pragma once
#include <iostream>
#include <string>
#include <ctime>


std::string getString(const std::string& prompt) {
    /*
    Purpose: To get a string input from the user and return that input

    */
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;

}

float getFloat() {
    /*
    Purpose: To get a interger input from the user and return that input
    */

    float num = 0;
    bool isValid = false;

    while (isValid == false) {

        if (std::cin >> num && num >= 0) {
            isValid = true;
        }
        else if (num < 0) {

            std::cin.clear();
            std::cin.ignore();
            std::cout << "Negative number input found" << std::endl;
            std::cout << "Please input a positive float" << std::endl;

        }
        else if (num >= 0) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "something other than a float was inputted\n";
            std::cout << "Please input a float" << std::endl;
        }
    }

    return num;
}

int getInt() {

    /*
    Purpose: To get a interger input from the user and return that input

    */

    int num = 0;
    bool isValid = false;

    while (isValid == false) {

        if (std::cin >> num && num >= 0) {
            isValid = true;
        }
        else if (num < 0) {

            std::cin.clear();
            std::cin.ignore();
            std::cout << "Negative number input found" << std::endl;
            std::cout << "Please input an interger" << std::endl;

        }
        else if (num >= 0) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "something other than an interger was inputted\n";
            std::cout << "Please input an interger" << std::endl;
        }
    }

    return num;
}

int getEpochTime() {
    //Returns the current epoch time, which can be used as a stardate.
    return static_cast<int>(std::time(nullptr));
}

//Helper Functions END