#include "ecg.h"
#include "processcsv.h"
#include "network_processes.h"
namespace fs = std::filesystem;

std::vector<ecg_singlederiv> ProcessCSV::readColumnFromCSV(std::string directory,int columnIndex) {
    indexsECG indices;
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
        indices = calculateNormalizedStandardDeviation(fileECG,A.valor,size);
        ECG.setAutocorrelation_index(indices.normalizedStandardDeviation);
        ECG.setBpm_index(indices.bpm);
        ECG.setID_ECG(fileECG);
        ECG.setderiv(A);
        ECGVector.push_back(ECG);
        files_reader++;
        }
    return ECGVector;
};

indexsECG ProcessCSV::calculateNormalizedStandardDeviation(std::string fileECG,const double* array,int size) {
    indexsECG indicesreturn;
    double maxAmplitude = array[0];
    for (size_t i = 1; i < size; ++i) {
        if (array[i] > maxAmplitude) {
            maxAmplitude = array[i];
        }
    }
    
    double threshold = 0.7 * maxAmplitude;
    std::vector<size_t> rPoints;

    // Find peaks above the threshold
    for (size_t i = 1; i < size - 1; ++i) {
        if (array[i] > threshold && array[i] > array[i - 1] && array[i] > array[i + 1]) {
            rPoints.push_back(i);
        }
    }
/*
    for (const auto& position : rPoints) {
        std::cout << "posiciones: " << position << "\n ";
    }
*/

    std::vector<double> distances;
    for (size_t i = 1; i < rPoints.size(); ++i) {
        distances.push_back(rPoints[i] - rPoints[i - 1]);
    }

   
    double sum = 0.0;
    for (const auto& distance : distances) {
        sum += distance;
    }

    double mean = sum / distances.size();

    double squaredDifferencesSum = 0.0;
    for (const auto& distance : distances) {
        squaredDifferencesSum += pow(distance - mean, 2);
    }

    double standardDeviation = sqrt(squaredDifferencesSum / (distances.size() - 1));

    double normalizedStandardDeviation = standardDeviation / (size / 2.0);
    indicesreturn.normalizedStandardDeviation=normalizedStandardDeviation;
    std::cout << "indice desviacion normalizada: "<< normalizedStandardDeviation <<"\n";
    
    double sumTimeIntervals = 0.0;
    size_t numIntervals = rPoints.size() - 1;

    // Calculate time intervals between consecutive R points
    for (size_t i = 1; i < rPoints.size(); ++i) {
        double timeInterval = static_cast<double>(rPoints[i] - rPoints[i - 1]) / 500;
        sumTimeIntervals += timeInterval;
    }

    // Calculate average time duration per beat
    double averageTimeInterval = sumTimeIntervals / numIntervals;

    // Convert average time duration per beat to BPM
    double bpm = 60.0 / averageTimeInterval;
    indicesreturn.bpm=bpm;
    return indicesreturn;
};

int ProcessCSV::WriteCSV(std::vector<ComparativeCosine> comparatives){
    std::ofstream file("data.csv");

    if (file.is_open())
    {
        file << "IDA, IDB, weith\n";
        for(const ComparativeCosine comparative: comparatives){
            file << comparative.IDA <<","<<comparative.IDB<<","<<comparative.cosineindez<<"\n";
        }
        // Close the file
        file.close();
        std::cout << "CSV file created successfully." << std::endl;
    }
    else
    {
        std::cerr << "Failed to create the CSV file." << std::endl;
    }

    return 0;
};