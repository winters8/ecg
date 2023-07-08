#ifndef ECG_H
#define ECG_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <array>

class ECG
{
private:
    std:: string ID;
    double correlationindex;
    double BPM;
    double *derivnormalized;
    double *deriv;
public:
    ECG(const std::string id, double derivreader[3507]){
        ID=id;
        derivnormalized=derivreader;
    };

    double* getderiv() const {
        return deriv;
    };

    std::string getID_ECG() const {
        return ID;
    };
    double getCorrelationindex() const{
        return correlationindex;
    };

    void setID_ECG(std::string id){
        ID=id;
    }
    void setAutocorrelation_index(double index){
        correlationindex=index;
    }
    void setBpm_index(double index){
        BPM=index;
    }
    void setderivnorm(double derivnormalizedreader[3507]){
        derivnormalized=derivnormalizedreader;
    };
    double* getderivnorm() const {
        return derivnormalized;
    };
    ~ECG(){
        delete[] deriv;
        delete[] derivnormalized;
    }




/*method to calculate the normalized 
* standard deviation of each ECG*/
double calculateNormalizedStandardDeviation(double derivnormalize[3507]) {
    double indicesreturn;
    double maxAmplitude = derivnormalize[0];

    for (size_t i = 1; i < 3507; ++i) {
        if (derivnormalize[i] > maxAmplitude) {
            maxAmplitude = derivnormalize[i];
        }
    }
    
    double threshold = 0.7 * maxAmplitude;
    std::vector<size_t> rPoints;

    // Find peaks above the threshold
    for (size_t i = 1; i < 3507 - 1; ++i) {
        if (derivnormalize[i] > threshold && derivnormalize[i] > derivnormalize[i - 1] && derivnormalize[i] > derivnormalize[i + 1]) {
            rPoints.push_back(i);
        }
    }

    std::vector<double> distances;
    for (size_t i = 1; i < rPoints.size(); ++i) {
        distances.push_back(rPoints[i] - rPoints[i - 1]);
    }

   
    double sum = 0.0;
    for (const auto& distance : distances) {
        sum += distance;
    }

    double mean = sum / distances.size();

    double squaredDifferencesSum = 0.0;
    for (const auto& distance : distances) {
        squaredDifferencesSum += pow(distance - mean, 2);
    }

    double standardDeviation = sqrt(squaredDifferencesSum / (distances.size() - 1));

    double normalizedStandardDeviation = standardDeviation / (3507 / 2.0);

    std::cout << "indice desviacion normalizada: "<< normalizedStandardDeviation <<"\n";
    
    return normalizedStandardDeviation;
};

/*method to calculate the normalized 
* standard deviation of each ECG*/
double CalculateBPM(double derivnormalize[3507]){
    double maxAmplitude = derivnormalize[0];
    double threshold = 0.7 * maxAmplitude;
    std::vector<size_t> rPoints;
    double bpm= 0.0;
    // Find peaks above the threshold
    for (size_t i = 1; i < 3507- 1; ++i) {
        if (derivnormalize[i] > threshold && derivnormalize[i] > derivnormalize[i - 1] && derivnormalize[i] > derivnormalize[i + 1]) {
            rPoints.push_back(i);
        }
        double sumTimeIntervals = 0.0;
        size_t numIntervals = rPoints.size() - 1;

        // Calculate time intervals between consecutive R points
        for (size_t i = 1; i < rPoints.size(); ++i) {
            double timeInterval = static_cast<double>(rPoints[i] - rPoints[i - 1]) / 500;
            sumTimeIntervals += timeInterval;
        }

        // Calculate average time duration per beat
        double averageTimeInterval = sumTimeIntervals / numIntervals;

        // Convert average time duration per beat to BPM
        bpm = 60.0 / averageTimeInterval;
   
    }
    return bpm;
}
};
#endif
