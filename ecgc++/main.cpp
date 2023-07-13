#include <iostream>
#include <string>

#include "processcsv.h"
#include "network_processes.h"
#include "Network.h"
using namespace std;
NetworkProcesses networkprocesses;
int main(){
    /* Path of the initial raw ECG data
    */
    string path = "C:/dataECG";

    /* Path of the preprocessed ECG data
    */
    string pathnorm = "C:/dataECG/norm";
    ProcessCSV reader;
    int columindex=1;

    auto inicio_secuencial1 = std::chrono::high_resolution_clock::now();
    reader.NormalizeBeginingpoingECGDATA(path,columindex);
    std::vector<ecg_singlederiv> ECGList = reader.readNormalizeCSV(pathnorm);
    auto fin_secuencial1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempoSecuencial1 = fin_secuencial1 - inicio_secuencial1;

    int size= ECGList.size();

    auto inicio_paralelo = std::chrono::high_resolution_clock::now();
    std::vector<ComparativeCosine> CosinesAll = networkprocesses.cosineSimilarity(ECGList);
    auto fin_paralelo = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempoParalelo = fin_paralelo - inicio_paralelo;

    auto inicio_secuencial2 = std::chrono::high_resolution_clock::now();
    Network ejem(CosinesAll,size);
    double thrs;
    thrs = ejem.threshold();
    reader.newNetwork(CosinesAll,thrs,size);
    auto fin_secuencial2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempoSecuencial2 = fin_secuencial2 - inicio_secuencial2;
    double tiempoSecuencialTotal = tiempoSecuencial1.count() + tiempoSecuencial2.count();
    double tiempoParaleloTotal = tiempoParalelo.count();
    double speedup = tiempoSecuencialTotal / tiempoParaleloTotal;

    std::cout << "Tiempo secuencial total: " << tiempoSecuencialTotal << " segundos" << std::endl;
    std::cout << "Tiempo paralelo: " << tiempoParaleloTotal << " segundos" << std::endl;
    std::cout << "Speedup: " << speedup << std::endl;
    return 0;
};