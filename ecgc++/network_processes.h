#ifndef NETWORK_PROCESSES_H
#define NETWORK_PROCESSES_H

#include "processcsv.h"
#include <omp.h>

class NetworkProcesses{

public:
   
    std::vector<ComparativeCosine> cosineSimilarity(std::vector<ecg_singlederiv>& ECGList);

 };
#endif