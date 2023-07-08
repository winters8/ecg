#include "processcsv.h"
#include "network_processes.h"

namespace fs = std::filesystem;

/*method to read the datasheet, only the chosen column and perform a preprocessing 
* to normalize all the ECGs so that they all start at the first point R, 
* it will create CSV files with the normalized data.*/
int ProcessCSV::NormalizeBeginingpoingECGDATA(std::string directory,int columnIndex){
    //std::vector<int> PosicionesprimerR;
    int files_reader=1;
    deriv A;
    char delimiter= ',';
    int discarded=0;
    for (const auto& entry : fs::directory_iterator(directory)) {
        derivNorm M;
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
               
                } catch (const std::exception& e) {
                    std::cout << "Error converting cell to double: " << cell << std::endl;
                }
            }
        }
        file.close();
        int size = sizeof(A.valor) / sizeof(A.valor[0]);
        int posicion = findFirstRPeak(A);
        if (posicion <1500){
            for(int z=posicion;z<3507+posicion;z++){
                M.valor[z-posicion]=A.valor[z];
            }
            files_reader++;
            fs::path filePath(filename);
            std::string file_Name = filePath.filename().string();
            std::cout <<"nombre archivo: "<< file_Name<<"\n";
            std::ofstream file2("C:/dataECG/norm/"+file_Name);
            file2<<"II\n";
            if (file2.is_open())
                {
                    for(int j=0;j<3507;j++){
                        file2 << std::to_string(M.valor[j]) <<"\n";
                    }
                    // Close the file
                    file2.close();
                    std::cout << "CSV file created successfully." << std::endl;
                }
                else
                {
                    std::cerr << "Failed to create the CSV file." << std::endl;
                }
        }
        else{
            discarded++;
        }
    }

    /*int max=0;
    for (const int posicion: PosicionesprimerR)
    {
        if(posicion>max){
            max=posicion;

        }
    }*/
    std::cout <<"archivos descartados : "<<discarded <<"\n";
    return 0;
};

/* Method to read the already normalized files 
* and create a vector with the objects "ecg_singlederiv"
*/
std::vector<ecg_singlederiv> ProcessCSV::readNormalizeCSV(std::string directory) {
    indexsECG index;
    std::vector<ecg_singlederiv> ECGVector;
    int files_reader=1;
    derivNorm A;

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
            double value;
                try {
                    value = std::stod(line);
                    A.valor[posarray]=value;
                    posarray++;
                } catch (const std::exception& e) {
                    std::cout << "Error converting cell to double: " << line << std::endl;
                }
        }
        file.close();
        std::filesystem::path filePath(filename);
        std::string fileECG = filePath.filename().string();
        int size = sizeof(A.valor) / sizeof(A.valor[0]);
        std::cout <<"valor size "<< size<<"\n";
        index = calculateNormalizedStandardDeviation(fileECG,A.valor,size);
        ECG.setAutocorrelation_index(index.normalizedStandardDeviation);
        ECG.setBpm_index(index.bpm);
        ECG.setID_ECG(fileECG);
        ECG.setderivnorm(A);
        ECGVector.push_back(ECG);
        files_reader++;
        }
    return ECGVector;
};

/* method to find and fix the first R point 
* within the ECG data*/
int ProcessCSV::findFirstRPeak(deriv A) {
    

    // Variables to track peak detection
    int rPeakIndex = -1;
    int size = sizeof(A.valor) / sizeof(A.valor[0]);
    std::cout << "el tamano de a array en find es "<<size<<"\n";
    double maxAmplitude = A.valor[0];
    for (size_t i = 1; i < size; ++i) {
        if (A.valor[i] > maxAmplitude) {
            maxAmplitude = A.valor[i];
        }
    }
    // Set a threshold for peak detection
    double threshold = 0.7 * maxAmplitude;
    std::cout << "el tamano de threshold en find es "<<threshold<<"\n";
    
    // Iterate over the ECG data
   for (int i = 1; i < size - 1; ++i) {
        if (A.valor[i] > A.valor[i - 1] && A.valor[i] > A.valor[i + 1] && A.valor[i] > threshold) {
            rPeakIndex = i;
            break;
        }
    }
    return rPeakIndex;
}

/*method to calculate the normalized 
* standard deviation of each ECG*/
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
