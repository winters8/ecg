#include <cmath>
#include "network_processes.h"
struct Position {
    int row;
    int col;
};
void NetworkProcesses::PrintListECGS(std::vector<ecg_singlederiv> ECGList){
    for (const ecg_singlederiv& ecg: ECGList){
       std::cout << ecg.getID_ECG()<< "\n";
        double correlation = ecg.getCorrelationindex();
        std::cout << "indice de correlacion rescatado: " << correlation << "\n";
    }
}