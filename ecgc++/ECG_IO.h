#ifndef ECG_IO_H
#define ECG_IO_H
#include "ecg.h"
#include <cmath>
#include <vector>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <queue>
#include <math.h>
#include <dirent.h>
#include "SparseArray.h"
#include "ECG_CSV.h"

namespace fs = std::filesystem;
class ECG_IO{
public:
     virtual ECG * readfile(std::string directory) = 0;
     virtual int NormalizeBeginingpoingECGDATA(std::string directory,int columnIndex) = 0;
     virtual int findFirstRPeak(double deriv[5010]) = 0;
     virtual double newNetwork(SparseArray Array, double thrd) = 0;
};
#endif
