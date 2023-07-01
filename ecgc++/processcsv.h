#ifndef PROCESSCSV_H
#define PROCESSCSV_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "ecg.h"

/*Struct to store csv data, the id of each node, 
* and its position in the for that go through the comparisons,
* the cosine index is also stored.*/
struct ComparativeCosine{
        std::string IDA;
        std::string IDB;
        int i;
        int j;
        double cosineindez;
};

/*A struct is created to store the normalized standard deviation
* and BPM of each ECG and then return these values more easily.*/
struct indexsECG{
    double normalizedStandardDeviation;
    double bpm;
};

/*An alias is created for the function 
* std::filesystem for easier access*/
namespace fs = std::filesystem;

/*Only the declarations of the Process CSV class
* as well as its methods are made.*/
class ProcessCSV{
public:
int NormalizeBeginingpoingECGDATA(std::string directory,int columnIndex);
std::vector<ecg_singlederiv> readNormalizeCSV(std::string directory);
indexsECG calculateNormalizedStandardDeviation(std::string fileECG,const double* array, int size);
int findFirstRPeak(deriv A);
};
#endif
