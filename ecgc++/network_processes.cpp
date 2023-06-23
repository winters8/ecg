#include <cmath>
#include <omp.h>
#include "network_processes.h"
struct Position {
    int row;
    int col;
};

void NetworkProcesses::PrintListECGS(std::vector<ecg_singlederiv> ECGList){
    for (const ecg_singlederiv& ecg: ECGList){
       std::cout << ecg.getID_ECG()<< "\n";
        double correlation = ecg.getCorrelationindex();
        std::cout << "correlation index: " <<correlation<< "\n";
    }
};
// Function to calculate the dot product of two arrays
std::vector<ComparativeCosine> NetworkProcesses::cosineSimilarity(std::vector<ecg_singlederiv>& ECGList){
    std::vector<ComparativeCosine> CosinesIndexAll;
    deriv A;
    deriv B;
    #pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        std::vector<ComparativeCosine> cosineprivate;
        #pragma omp for
        for (size_t i = 0; i < ECGList.size(); ++i)   
            {
                int myThreadID = threadID;
                ComparativeCosine compartiva;
                ecg_singlederiv ecga=ECGList[i];
                compartiva.IDA= ecga.getID_ECG();
                std::cout <<"el archivo: "<< ecga.getID_ECG()<< " esta siendo procesado por el hilo: "<<myThreadID<<"\n";
                A = ecga.getderiv();
                double valuea;
                double sumOfSquaresaA = 0.0;
                std::size_t sizea = sizeof(A.valor) / sizeof(A.valor[0]);

                for (size_t z=0; z< sizea; ++z)
                    {
                        valuea=A.valor[z];
                        sumOfSquaresaA += valuea * valuea;
                    }
                
                    double sqrtA = std::sqrt(sumOfSquaresaA);
                    std::cout << "sqrt A: " << sqrtA <<"\n";

                for (size_t j = 1; j < ECGList.size(); ++j)
                    {
                    ecg_singlederiv ecgb=ECGList[j];
                    compartiva.IDB= ecgb.getID_ECG();
                    B= ecgb.getderiv();    
                    double product = 0.0;
                        for (size_t m = 0; m < sizea; ++m)
                            {
                                product += A.valor[m] * B.valor[m];
                            }
                    double valueB;
                    double sumOfSquaresaB = 0.0;
                        for (size_t r=0; r< sizea; ++r)
                            {
                                valueB=B.valor[r];
                                sumOfSquaresaB += valueB * valueB;
                            }
                        
                        double sqrtB = std::sqrt(sumOfSquaresaB);
                        double producctoAB = sqrtA * sqrtB;
                        double division = product/producctoAB;
                        compartiva.cosineindez= division;
                        //std::cout <<"indice comparativo: " << compartiva.cosineindez<<"\n";
                        //std::cout << "division: "<< compartiva.cosineindez <<"\n";
                        cosineprivate.push_back(compartiva);
                        std::cout <<"el archivo: " <<ecga.getID_ECG()<< " en el hilo: "<< myThreadID<< " ha terminado\n";
                    }
            
            }
            #pragma omp critical
            {
            CosinesIndexAll.insert(CosinesIndexAll.end(), cosineprivate.begin(),cosineprivate.end());
            }
    }
    return CosinesIndexAll;
};
