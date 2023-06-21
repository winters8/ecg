#include <iostream>
#include <string>

class ecgInterface
{
public:
    virtual std::string getID_ECG(){
        return " ";
    }
    virtual void setID_ECG(std::string id){}
    //virtual double compute_autocorrelation_index(A)const{};
    //virtual std::vector<double> detectRRIntervals(const std::vector<double>& ecgData, int samplingRate) const{};
};