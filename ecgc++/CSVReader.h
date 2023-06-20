#ifndef CSVREADER_H
#define CSVREADER_H


#include <fstream>
#include <sstream>
#include <filesystem>
#include "ecg.h"

class CSVReader {
public:
    
    CSVReader(const std::string& directory, char delimiter = ',') :
        directory(directory), delimiter(delimiter) {}

    std::vector<ECG_singlederivation> readColumnFromCSV(int columnIndex);
    void printColumn(const std::vector<ECG_singlederivation>& ecg);
    int countTotalLinesInCSV(const std::string filename);

private:
    std::string directory;
    char delimiter;
    int columnIndex;
};
#endif  // CSVREADER_H
