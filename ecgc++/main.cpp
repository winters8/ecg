#include <iostream>
#include <string>

#include "CSVReader.h"

using namespace std;

int main(){
    string path = "C:/Users/plati/git/ECG/ecg/ECGDataDenoised";
    CSVReader reader(path);
    std::vector<double> columnData = reader.readColumnFromCSV(1); // Replace 2 with the desired column index
    // Print the column data
    reader.printColumn(columnData);

    return 0;
}