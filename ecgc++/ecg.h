#ifndef ECG_H
#define ECG_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct deriv{
        double valor[5010];
};
struct derivNorm{
    double valor[3507];
};
/*A struct is created to store the normalized standard deviation
* and BPM of each ECG and then return these values more easily.*/

struct indexsECG{
    double normalizedStandardDeviation;
    double bpm;
};
class ecg_singlederiv
{
private:
    std:: string ID;
    deriv A_;
    double correlationindex;
    double BPM;
    derivNorm M_;
public:
    
    ecg_singlederiv(const std::string id, struct derivNorm A){
        ID=id;
        M_=A;
    };

    deriv getderiv() const {
        return A_;
    };
    
    std::string getID_ECG() const {
        return ID;
    };

    double getCorrelationindex() const{
        return correlationindex;
    };
    
    void setderiv(struct deriv A){
        A_=A;
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
    void setderivnorm(struct derivNorm M){
        M_=M;
    };
    derivNorm getderivnorm() const {
        return M_;
    };

    /*method to calculate the normalized 
    * standard deviation of each ECG*/
    indexsECG calculateNormalizedStandardDeviationAndBPM(std::string fileECG,const double* array,int size) {
    indexsECG indicesreturn;
    double maxAmplitude = array[0];
    for (size_t i = 1; i < size; ++i) {
        if (array[i] > maxAmplitude) {
            maxAmplitude = array[i];
        }
    }
    
    double threshold = 0.7 * maxAmplitude;
    std::vector<size_t> rPoints;

    // Find peaks above the threshold
    for (size_t i = 1; i < size - 1; ++i) {
        if (array[i] > threshold && array[i] > array[i - 1] && array[i] > array[i + 1]) {
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

    double normalizedStandardDeviation = standardDeviation / (size / 2.0);
    indicesreturn.normalizedStandardDeviation=normalizedStandardDeviation;
    std::cout << "indice desviacion normalizada: "<< normalizedStandardDeviation <<"\n";
    
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
    double bpm = 60.0 / averageTimeInterval;
    indicesreturn.bpm=bpm;
    return indicesreturn;
};
};
#endif
