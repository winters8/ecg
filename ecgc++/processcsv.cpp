#include "ecg.h"
#include "processcsv.h"

namespace fs = std::filesystem;

std::vector<ecg_singlederiv> ProcessCSV::readColumnFromCSV(std::string directory,int columnIndex) {
    std::vector<ecg_singlederiv> ECGVector;
    int files_reader=1;
    deriv A;
    char delimiter= ',';
    for (const auto& entry : fs::directory_iterator(directory)) {
        ecg_singlederiv ECG("",A);
        const std::string filename = entry.path().string();
        std::cout <<files_reader<< "\n";
        std::ifstream file(filename);
            if (!file.is_open()) {
                std::cout << "Error opening file: " << filename << std::endl;
                continue;
            }
        std::string line;
        std::getline(file, line);
        int posarray=0;
        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            std::string cell;
            double value;
            for (int i = 0; i < columnIndex; i++) {
                if (!std::getline(lineStream, cell, ',')) {
                    break; // Invalid column number, or end of line reached
                }
            }
            if (std::getline(lineStream, cell, ',')) {
                try {
                    value = std::stod(cell);
                    A.valor[posarray]=value;
                    posarray++;
                //columnData.push_back(value);
                } catch (const std::exception& e) {
                    std::cout << "Error converting cell to double: " << cell << std::endl;
                }
            }
        }
        file.close();
        std::filesystem::path filePath(filename);
        std::string fileECG = filePath.filename().string();
        ECG.setID_ECG(fileECG);
        ECG.setderiv(A);
        ECGVector.push_back(ECG);
        files_reader++;
        }
    return ECGVector;
};
    