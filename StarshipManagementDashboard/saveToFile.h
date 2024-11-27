#pragma once
#include <iostream>
#include <fstream>

void showFileContents(const std::string& filename);
std::vector<Starship> loadFromFile(const std::string& filename);
void saveToFile(const std::vector<Starship>& starships, const std::string& filename);
void clearSaveData(std::vector<Starship>& starships, const std::string& filename);
