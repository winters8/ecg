#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Function to split a string based on a delimiter
std::vector<std::string> splitString(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

// Function to read a CSV file and store the data in a vector of vectors
std::vector<std::vector<std::string>> readCSV(const std::string& filename, char delimiter) {
    std::ifstream file(filename);
    std::vector<std::vector<std::string>> data;

    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> row = splitString(line, delimiter);
            data.push_back(row);
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
    }

    return data;
}

int main() {
    std::string filename = "example.csv";  // Replace with your CSV file path
    char delimiter = ',';  // Replace with the appropriate delimiter used in your CSV file

    std::vector<std::vector<std::string>> csvData = readCSV(filename, delimiter);

    // Printing the CSV data
    for (const auto& row : csvData) {
        for (const auto& cell : row) {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}
