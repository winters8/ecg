
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "Network.h"
#include "reader.h"
namespace fs = std::filesystem;

std::vector<Edgenew> reader::readCSV(const std::string& filename) {
    std::vector<Edgenew> ecgevector;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return ecgevector;
    }
      std::string line, header;
    if (std::getline(file, header)) {
        std::stringstream ss(header);
        std::string field;

        // Verify the header columns
        if (std::getline(ss, field, ',') && field != "Source") {
            std::cerr << "Invalid header column: Name" << std::endl;
            return ecgevector;
        }
        if (std::getline(ss, field, ',') && field != "Target") {
            std::cerr << "Invalid header column: Age" << std::endl;
            return ecgevector;
        }
        if (std::getline(ss, field, ',') && field != "Weight") {
            std::cerr << "Invalid header column: Score" << std::endl;
            return ecgevector;
        }
    }
    else {
        std::cerr << "Empty file: " << filename << std::endl;
        return ecgevector;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;

        Edgenew d;
        if (std::getline(ss, field, ',')) {
            d.originumber = std::stod(field);
        }
        if (std::getline(ss, field, ',')) {
            d.destinationnumber = std::stod(field);
        }
        if (std::getline(ss, field, ',')) {
            d.weight = std::stod(field);
        }
        ecgevector.push_back(d);
    }
    return ecgevector;
}