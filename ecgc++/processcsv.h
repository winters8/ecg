#ifndef PROCESSCSV_H
#define PROCESSCSV_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "ecg.h"
namespace fs = std::filesystem;

class ProcessCSV{
public:

std::vector<ecg_singlederiv> readColumnFromCSV(std::string directory,int columnIndex);

double CalculateCorrelationRRinterval(std::string file,const double* array, int size);
};
#endif
