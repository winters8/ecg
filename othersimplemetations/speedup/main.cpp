#include <iostream>
#include <string>
#include "Network.h"
#include "reader.h"
using namespace std;

int main(){
    /* Path of the initial raw ECG data
    */
    string path = "C:/dataECG/erdosGephi10000.csv";

    /* Path of the preprocessed ECG data
    */
    
    reader reader;
    auto inicio_secuencial1 = std::chrono::high_resolution_clock::now();
    std::vector<Edgenew> ecgevector=reader.readCSV(path);
    int size= 10000;
    Network ejem(ecgevector,size);
    double thrs;
    thrs = ejem.threshold();
    std::cout <<"threshold: "<<thrs <<"\n";
    ejem.newNetwork(ecgevector,thrs,size);
    auto fin_secuencial1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempoSecuencial1 = fin_secuencial1 - inicio_secuencial1;

    double tiempoSecuencialTotal = tiempoSecuencial1.count(); 
    

    std::cout << "Tiempo secuencial total: " << tiempoSecuencialTotal << " segundos" << std::endl;
    //std::cout << "Tiempo paralelo: " << tiempoParaleloTotal << " segundos" << std::endl;
    //std::cout << "Speedup: " << speedup << std::endl;
    return 0;
};