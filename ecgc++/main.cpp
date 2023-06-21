#include <iostream>
#include <string>

#include "processcsv.h"
#include "network_processes.h"

using namespace std;
NetworkProcesses processes;
int main(){
    string path = "C:/Users/plati/git/ECG/ecg/ECGDataDenoised";
    ProcessCSV reader;
    int columindex=1;
    std::vector<ecg_singlederiv> ECGList = reader.readColumnFromCSV(path,columindex); // Replace 2 with the desired column index
    // Print the column data
    processes.PrintListECGS(ECGList);
    return 0;
    };