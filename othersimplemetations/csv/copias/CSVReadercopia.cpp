#include "CSVReader.h"
#include <algorithm>

namespace fs = std::filesystem;

std::vector<ECG_singlederivation> CSVReader::readColumnFromCSV(int columnIndex) {
    std::vector<ECG_singlederivation> ECGList;
    int archivos_leidos=0;
    fs::directory_iterator it(directory);
    fs::directory_iterator end;
    while (it !=end) {
        const auto& entry = *it;
        const std::string filename = entry.path().string();
        int lineas = countTotalLinesInCSV(filename);
        NetworkCommunities::SparseArray ArrayDataDerivation(lineas);
        std::cout <<archivos_leidos<< "\n";
        std::ifstream file(filename);
        std::vector<Derivation> derivations;
        if (!file.is_open()) {
            std::cout << "Error opening file: " << filename << std::endl;
            continue;
        }
        std::string line;
        std::getline(file, line);
        int columarray=0;
        int rowarray=0;
        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            std::string cell;
            for (int i = 0; i < columnIndex + 1; ++i) {
                if (!std::getline(lineStream, cell, delimiter)) {
                    std::cout << "Error: Column index out of range." << std::endl;
                    file.close();
                    return ECGList;
                }
            }
            double value;
            try {
                value = std::stod(cell);
                ArrayDataDerivation.put(columarray,rowarray,value);
                columarray++;
            } catch (const std::exception& e) {
                std::cout << "Error converting cell to double: " << cell << std::endl;
            }
        }
        file.close();
        std::filesystem::path filePath(filename);
        std::string fileECG = filePath.filename().string();
        //ECG_singlederivation ecg(fileECG,ArrayDataDerivation);
        ECGList.emplace_back(archivos_leidos);
        archivos_leidos++;
        std::cout << archivos_leidos;
        ++it;
        }
    return ECGList;
}
void readDirectory(const std::string& directory, int columnIndex) {
    CSVReader csvReader;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        const std::string& filename = entry.path().string();
        std::vector<ECG_singlederivation> columnData = csvReader.readColumnFromCSV(filename, columnIndex);

        // Process the column data as desired
        for (const auto& data : columnData) {
            // Access the ECG_singlederivation members as needed
            std::cout << data.value << std::endl;
        }
    }
   
int CSVReader::countTotalLinesInCSV(const std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return -1;
    }
    int lineCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        lineCount++;
    }
    file.close();
    return lineCount;
}
/*
void CSVReader::printColumn(const std::vector<int>& ecgs) {
    for (const auto& ecg : ecgs) {
        std::cout << "imprimiendo datos ecg";
        std::cout << ecg.getID_ECG();
        NetworkCommunities::SparseArray derivation =ecg.getDerivation_ECG();
        for (int i=0; i<derivation.get_nEdges();i++){
            std::cout << derivation.v(i) << " ";
        }
    } 
}*/

