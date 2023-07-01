#ifndef PROCESSCSV_H
#define PROCESSCSV_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "ecg.h"
struct ComparativeCosine{
        std::string IDA;
        std::string IDB;
        int i;
        int j;
        double cosineindez;
};
struct indexsECG{
    double normalizedStandardDeviation;
    double bpm;
};

namespace fs = std::filesystem;

class ProcessCSV{
public:
std::vector<ecg_singlederiv> readNormalizeCSV(std::string directory);
indexsECG calculateNormalizedStandardDeviation(std::string fileECG,const double* array, int size);
int WriteCSV(std::vector<ComparativeCosine> comparative);
int NormalizeBeginingpoingECGDATA(std::string directory,int columnIndex);
int findFirstRPeak(deriv A);
int CreateCSVNorm(std::string filename, ecg_singlederiv ecg);
};
#endif
