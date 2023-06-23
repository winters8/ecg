#include <iostream>
#include <string>

#include "processcsv.h"
#include "network_processes.h"

using namespace std;
NetworkProcesses processes;
ProcessCSV write;
int main(){
    string path = "C:/Users/plati/git/ECG/ecg/ECGDataDenoised";
    ProcessCSV reader;
    int columindex=1;
    std::vector<ecg_singlederiv> ECGList = reader.readColumnFromCSV(path,columindex);
    std::vector<ComparativeCosine> comparatives = processes.cosineSimilarity(ECGList);
// Replace 2 with the desired column index
    // Print the column data
    //processes.PrintListECGS(ECGList);
    write.WriteCSV(comparatives);
    return 0;
};