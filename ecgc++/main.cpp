#include <iostream>
#include <string>
#include "ECG_Net.h"
#include "SparseArray.h"
using namespace std;
ECG_CSV reader;
ECG** listaECG;
ECG_Net process;
int main(){
    /* Path of the initial raw ECG data
    */
    //string path = "C:/dataECG";
    //reader.NormalizeBeginingpoingECGDATA(path,1);
    /* Path of the preprocessed ECG data
    */
    string pathnorm = "C:/dataECG/norm";
    int sizearray= reader.sizearray(pathnorm);
    listaECG = reader.readfile(pathnorm,sizearray);
    SparseArray Array=process.cosineSimilarity(listaECG,sizearray);
    std::cout <<"Numero aristas creadas: "<<Array.get_nEdges()<<"\n";
    /*ECG_Net process(Array,sizearray);
    double thrs;
    thrs = process.threshold();
    reader.newNetwork(Array,thrs);*/
    return 0;
};