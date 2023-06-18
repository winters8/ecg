#include "CSVReader.h"
#include <algorithm>

namespace fs = std::filesystem;

std::vector<ECG> CSVReader::readColumnFromCSV(int columnIndex) {
std::vector<ECG> ECGList;
int archivos_leidos=1;
    for (const auto& entry : fs::directory_iterator(directory)) {
        const std::string filename = entry.path().string();
        int lineas = countTotalLinesInCSV(filename);
        std::cout <<archivos_leidos<< "\n";
        std::vector<double> columnData;
        std::ifstream file(filename);
        std::vector<Derivation> derivations;
        if (!file.is_open()) {
            std::cout << "Error opening file: " << filename << std::endl;
            continue;
        }

        std::string line;
        std::getline(file, line);
        if (lineas<2502){
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
        }
        else{
            bool shouldReadLine = true;
            while (std::getline(file, line)) {
                if (shouldReadLine){
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
                shouldReadLine=!shouldReadLine;
            }
            /*std::size_t length = columnData.size();
            std::cout << "tamaño colum data: "<<length;*/
            file.close();
            const std::string derivation_name="II";
            Derivation Derivation(columnData,derivation_name);
            derivations.push_back(Derivation);
            std::filesystem::path filePath(filename);
            std::string fileECG = filePath.filename().string();
            ECG ecg(fileECG,derivations);
            ecg.compute_autocorrelation_index(columnData);

            ECGList.push_back(ecg);
        }
        archivos_leidos++;
        }
        
    return ECGList;
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

void CSVReader::printColumn(const std::vector<ECG>& column) {
    for (ECG value : column) {
        std::cout << "imprimiendo datos ecg";
        std::cout << value.getID_ECG();
        std::vector<Derivation> derivation =value.getDerivations();
        Derivation derivation1 = derivation[0];
        std::cout << derivation1.getString();
        std:: vector<double>derivation_data = derivation1.getderivationdata();
        for (const auto& value: derivation_data){
            std::cout << value << " ";
        }
        } 
}

