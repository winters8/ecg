#ifndef CSVREADER_H
#define CSVREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "ecg.h"

class CSVReader {
public:
    
    CSVReader(const std::string& directory, char delimiter = ',') :
        directory(directory), delimiter(delimiter) {}
    std::vector<ECG> readColumnFromCSV(int columnIndex);
    void printColumn(const std::vector<ECG>& column);
    int countTotalLinesInCSV(const std::string filename);

private:
    std::string directory;
    char delimiter;
};

#endif  // CSVREADER_H
