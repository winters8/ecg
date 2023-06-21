#ifndef ECG_H_
#define ECG_H_

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "SparseArray.h"
class ecgInterface
{
private:
    std::string ID;
    double autocorrelation_index;
    NetworkCommunities::SparseArray thisArrayDataDerivation;
public:
    ecgInterface(const std::string& str,NetworkCommunities::SparseArray ArrayDataDerivation): thisArrayDataDerivation(ArrayDataDerivation)
    {
            ID = str;
    };
    NetworkCommunities::SparseArray getDerivations(){
            return thisArrayDataDerivation;
    };
    string getID_ECG() {
            return ID;
    }
    virtual double compute_autocorrelation_index(NetworkCommunities::SparseArray ArrayDataDerivation) = 0;
    virtual std::vector<double> detectRRIntervals(const std::vector<double>& ecgData, int samplingRate)=0;
};
class ECG_singlederivation : public ecgInterface
{
    public:
        
        ECG_singlederivation(const std::string& str,NetworkCommunities::SparseArray ArrayDataDerivation):ecgInterface(str,ArrayDataDerivation){}
        //Set autocorrelation index
        double compute_autocorrelation_index(NetworkCommunities::SparseArray ArrayDataDerivation) override {
        int n = ArrayDataDerivation.get_nEdges();
        int lag=40;// 250 Hz = 1 / 250 s = 40 samples
        /*
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
            std::cout << "aurocorrelation_ index: "<< autocorrelation; */
            return n;
    }
    std::vector<double> detectRRIntervals(const std::vector<double>& ecgData, int samplingRate) override  {
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
            int threshold =20;
            if (ecgData[i] > threshold) {
                double rrInterval = timeInterval * i;
                rrIntervals.push_back(rrInterval);
            }
        }

        return rrIntervals;
    }
};
#endif