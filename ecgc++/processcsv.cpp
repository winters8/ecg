#include "ecg.h"
#include "processcsv.h"
#include "network_processes.h"
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
        int size = sizeof(A.valor) / sizeof(A.valor[0]);
        double correlation = CalculateCorrelationRRinterval(fileECG,A.valor,size);
        ECG.setAutocorrelation_index(correlation);
        ECG.setID_ECG(fileECG);
        ECG.setderiv(A);
        ECGVector.push_back(ECG);
        files_reader++;
        }
    return ECGVector;
};

double ProcessCSV::CalculateCorrelationRRinterval(std::string fileECG,const double* array, int size){
    double max = array[0];
    int maxIndex = 0;

    // Find the maximum value and its index
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
            maxIndex = i;
        }
    }
    // Calculate the correlation coefficient
    double sumXY = 0.0;
    double sumX = 0.0;
    double sumY = 0.0;
    double sumXSquared = 0.0;
    double sumYSquared = 0.0;

    for (int i = 0; i < size; i++) {
        sumXY += (i - maxIndex) * (array[i] - max);
        sumX += i - maxIndex;
        sumY += array[i] - max;
        sumXSquared += std::pow(i - maxIndex, 2);
        sumYSquared += std::pow(array[i] - max, 2);
    }

    double correlation = sumXY / std::sqrt(sumXSquared * sumYSquared);
    return correlation;
}
