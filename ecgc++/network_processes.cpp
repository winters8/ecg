#include <cmath>
#include <omp.h>
#include "network_processes.h"

/* Function to calculate the cosine similarity index
* of two ECG data
*/
std::vector<ComparativeCosine> NetworkProcesses::cosineSimilarity(std::vector<ecg_singlederiv>& ECGList){
    std::vector<ComparativeCosine> CosinesIndexAll;
    derivNorm A;
    derivNorm B;
    /*Beginning of the part of the code 
    * to be parallelized with OpenMP
    */
    #pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        std::vector<ComparativeCosine> cosineprivate;
        /*for parallelized with OpenMP 
        * to improve efficiency with multi-thread
        * computing and with the shedule option 
        * to automatically distribute the work equally among them
        */
        #pragma omp for schedule(auto)
        for (size_t i = 0; i < ECGList.size(); ++i)   
            {
                int myThreadID = threadID;
                ComparativeCosine compartiva;
                ecg_singlederiv ecga=ECGList[i];
                compartiva.IDA= ecga.getID_ECG();
                std::cout <<"el archivo: "<< ecga.getID_ECG()<< " esta siendo procesado por el hilo: "<<myThreadID<<"\n";
                A = ecga.getderivnorm();
                double valuea;
                double sumOfSquaresaA = 0.0;
                std::size_t sizea = sizeof(A.valor) / sizeof(A.valor[0]);
                for (size_t z=0; z< sizea; ++z)
                    {
                        valuea=A.valor[z];
                        sumOfSquaresaA += valuea * valuea;
                    }
                
                    double sqrtA = std::sqrt(sumOfSquaresaA);

                for (size_t t= i+1; t < ECGList.size(); ++t){
                    int j=t;
                    ecg_singlederiv ecgb=ECGList[t];
                    compartiva.IDB= ecgb.getID_ECG();
                    B= ecgb.getderivnorm();    
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
                        compartiva.i=i;
                        compartiva.j=j;
                        /*fiter for incorrect valors*/
                        if(division<=1 && division>=-1){
                        cosineprivate.push_back(compartiva);
                        }                    
                    }
            
            }
            /*Critical part where each thread stores 
            * the computation and where the reading
            * and writing processes must be controlled
            */
            #pragma omp critical
            {
            CosinesIndexAll.insert(CosinesIndexAll.end(), cosineprivate.begin(),cosineprivate.end());
            }
           
    }
return CosinesIndexAll;
};

