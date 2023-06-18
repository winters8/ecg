#include "CSVReader.h"
#include <algorithm>

namespace fs = std::filesystem;

std::vector<ECG> CSVReader::readColumnFromCSV(int columnIndex) {
std::vector<ECG> ECGList;
    for (const auto& entry : fs::directory_iterator(directory)) {
        const std::string filename = entry.path().string();
        std::vector<double> columnData;
        std::ifstream file(filename);
        std::vector<Derivation> derivations;
        //std::cout << "opening file: " << filename;
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
                    return ECGList;
                }
            }

            double value;
            try {
                value = std::stod(cell);
                columnData.push_back(value);
            } catch (const std::exception& e) {
                std::cout << "Error converting cell to double: " << cell << std::endl;
            }
        }

        file.close();
        const std::string deriation_name="II";
        Derivation Derivation(columnData,deriation_name);
        derivations.push_back(Derivation);
        std::filesystem::path filePath(filename);
        std::string fileECG = filePath.filename().string();
        ECG ecg(fileECG,derivations);
        ECGList.push_back(ecg);
        std::cout << ecg.getID_ECG();
    }
    return ECGList;
}

void CSVReader::printColumn(const std::vector<ECG>& column) {
    for (ECG value : column) {
        std::cout << value.getID_ECG() << std::endl;
        std::vector<Derivation> derivation =value.getDerivations();
        for (const auto& derivation: derivation){
            std::string namederivation = derivation.getString();
            std::cout << namederivation;
            std::vector<double> dataderivation=derivation.getdoubleList();
            for (const auto& dataderivation: dataderivation){
                std::cout << dataderivation;
            }
        } 
}
}
