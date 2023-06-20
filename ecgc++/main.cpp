#include <iostream>
#include "CSVReader.h"

using namespace std;

int main(){
    string path = "C:/Users/plati/git/ECG/ecg/ECGDataDenoised";
    CSVReader reader(path);
    int columindex=1;
    std::vector<ECG_singlederivation> ECGList = reader.readColumnFromCSV(columindex); // Replace 2 with the desired column index
    // Print the column data
    reader.printColumn(ECGList);

    return 0;
}