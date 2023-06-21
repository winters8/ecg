#include "network_processes.h"

void NetworkProcesses::PrintListECGS(std::vector<ecg_singlederiv> ECGList){
    for (const ecg_singlederiv& ecg: ECGList){
       std::cout << ecg.getID_ECG();
       deriv A;
        A=ecg.getderiv();
        int size = sizeof(A.valor) / sizeof(A.valor[0]);
        for (int i=0; i<size; i++){
            std::cout << A.valor[i]<<" "; 
        }
    }
}