#include <fstream>
#include <sstream>
#include <filesystem>
#include "ecg2.h"

namespace fs = std::filesystem;
class CSVReader {
public:
    CSVReader(const std::string& directory, char delimiter = ',') :
        directory(directory), delimiter(delimiter) {}

    std::vector<ECG2> readColumnFromCSV(int columnIndex){
    std::vector<ECG2> ECGList;
    int archivos_leidos=1;
        for (const auto& entry : fs::directory_iterator(directory)) {
            const std::string filename = entry.path().string();
            int lineas = countTotalLinesInCSV(filename);
            NetworkCommunities::SparseArray ArrayDataDerivation(lineas);
            std::ifstream file(filename);

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
            std::cout << fileECG;
            try{
                ECG2 ecg(filename,ArrayDataDerivation);
                std::cout << "creado objeto ecg: \n ";
                archivos_leidos++;
                std::cout << archivos_leidos;
                continue;
                //ECGList.push_back(ecg);
            }catch (const std::exception& e) {
                    std::cout << "Error create objetc ecg: " << std::endl;
            }
            
        }
        return ECGList;
    }

    int countTotalLinesInCSV(const std::string filename) {
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

private:
    std::string directory;
    char delimiter;
    int columnIndex;
};

