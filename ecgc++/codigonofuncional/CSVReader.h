#ifndef CSVREADER_H
#define CSVREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "ecg2.h"

class CSVReader {
public:
    
    CSVReader(const std::string& directory, char delimiter = ',') :
        directory(directory), delimiter(delimiter) {}
    std::vector<ECG2> readColumnFromCSV(int columnIndex);
    void printColumn(const std::vector<ECG2>& column);
    int countTotalLinesInCSV(const std::string filename);

private:
    std::string directory;
    char delimiter;
};

#endif  // CSVREADER_H
