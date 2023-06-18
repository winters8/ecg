#ifndef CSVREADER_H
#define CSVREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

class CSVReader {
public:
    CSVReader(const std::string& directory, char delimiter = ',') :
        directory(directory), delimiter(delimiter) {}

    std::vector<double> readColumnFromCSV(int columnIndex);
    void printColumn(const std::vector<double>& column);

private:
    std::string directory;
    char delimiter;
};

#endif  // CSVREADER_H
