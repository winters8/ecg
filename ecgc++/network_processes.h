#ifndef NETWORK_PROCESSES_H
#define NETWORK_PROCESSES_H

#include "processcsv.h"
#include <omp.h>
#include "SparseArray.h"

class NetworkProcesses{

public:
    void PrintListECGS(std::vector<ecg_singlederiv> ECGList);
   
    std::vector<ComparativeCosine> cosineSimilarity(std::vector<ecg_singlederiv>& ECGList);

 };
#endif