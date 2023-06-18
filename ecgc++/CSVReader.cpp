#include "CSVReader.h"
#include <algorithm>
namespace fs = std::filesystem;

std::vector<double> CSVReader::readColumnFromCSV(int columnIndex) {
    std::vector<double> columnData;

    for (const auto& entry : fs::directory_iterator(directory)) {
        const std::string& filename = entry.path().string();

        std::ifstream file(filename);
        std::cout << "opening file: " << filename;
        if (!file.is_open()) {
            std::cout << "Error opening file: " << filename << std::endl;
            continue;
        }

        std::string line;
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            std::string cell;
            
            for (int i = 0; i < columnIndex + 1; ++i) {
                if (!std::getline(lineStream, cell, delimiter)) {
                    std::cout << "Error: Column index out of range." << std::endl;
                    file.close();
                    return columnData;
                }
            }

            double value;
            std::cout << "datqa: " << cell;
            try {
                value = std::stod(cell);
                columnData.push_back(value);
            } catch (const std::exception& e) {
                std::cout << "Error converting cell to double: " << cell << std::endl;
            }
        }

        file.close();
    }

    return columnData;
}

void CSVReader::printColumn(const std::vector<double>& column) {
    for (double value : column) {
        std::cout << value << std::endl;
    }
}
