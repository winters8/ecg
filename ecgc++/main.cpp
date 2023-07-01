#include <iostream>
#include <string>

#include "processcsv.h"
#include "network_processes.h"
#include "Network.h"
using namespace std;
NetworkProcesses networkprocesses;
ProcessCSV write;
int main(){
    string path = "C:/dataECG";
    string pathnorm = "C:/dataECG/norm";
    ProcessCSV reader;
    int columindex=1;

    //reader.NormalizeBeginingpoingECGDATA(path,columindex);
    std::vector<ecg_singlederiv> ECGList = reader.readNormalizeCSV(pathnorm);
    int size= ECGList.size();
    std::vector<ComparativeCosine> CosinesAll = networkprocesses.cosineSimilarity(ECGList);
    Network ejem(CosinesAll,size);
    double thrs;
    thrs = ejem.threshold();
    ejem.newNetwork(CosinesAll,thrs);
    return 0;
};