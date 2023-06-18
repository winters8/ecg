#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "derivations.h"

class ECG{
public:
    std::string ID;
    std::vector<Derivation> derivations;
    double autocorrelation_index;
    //Constructor ECG
    ECG(const std::string& str,const std::vector<Derivation>& deriv){
    ID = str;
    derivations=deriv;
    }
    //Getter derivations list
    std::vector<Derivation> getDerivations() const{
        return derivations;
    }
    //Getter ECG ID
    std::string getID_ECG() const{
        return ID;
    }
    void add_derivation(Derivation Derivation) {
        derivations.push_back(Derivation);
        
    }

    //Set autocorrelation index
    double compute_autocorrelation_index(std::vector<double>& derivation_data){
       int n = derivation_data.size();
       int lag=40;// 250 Hz = 1 / 250 s = 40 samples
        double sum = 0.0;

        // Calculate the mean of the data
        double mean = 0.0;
        for (double value : derivation_data) {
            mean += value;
        }
        mean /= n;
        std::cout << "media:" << mean;
        // Calculate the autocovariance
        for (int i = 0; i < n - lag; ++i) {
            sum += (derivation_data[i] - mean) * (derivation_data[i + lag] - mean);
        }

        // Calculate the autocorrelation index
        double autocovariance = sum / (n - lag);
        double variance= 0.0;
        for (double value : derivation_data) {
        variance += std::pow(value - mean, 2);
        }
        variance /= n;
        double autocorrelation = autocovariance / variance;
        autocorrelation_index=autocorrelation;
        std::cout << "aurocorrelation_ index: "<< autocorrelation; 
        return autocorrelation;
}
std::vector<double> detectRRIntervals(const std::vector<double>& ecgData, int samplingRate) {
    std::vector<double> rrIntervals;
    
    // Assuming each value in ecgData represents the amplitude of the ECG signal

    // Perform your RR interval detection algorithm here

    // Example code: Calculate RR intervals using a fixed sampling rate
    double timeInterval = 1.0 / samplingRate;
    for (int i = 0; i < ecgData.size(); ++i) {
        // Perform your RR interval detection logic here
        // This example assumes the RR intervals are calculated based on peaks in the ECG signal
        // Modify this logic according to your specific RR interval detection algorithm
        
        // Example: Assuming peaks occur when the ECG amplitude crosses a certain threshold
        if (ecgData[i] > threshold) {
            double rrInterval = timeInterval * i;
            rrIntervals.push_back(rrInterval);
        }
    }

    return rrIntervals;
}

};