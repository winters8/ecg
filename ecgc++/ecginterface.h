#include <iostream>
#include <string>

class ecgInterface
{
public:
    virtual std::string getID_ECG(){}
    virtual double compute_autocorrelation_index(struct deriv)const{};
    virtual std::vector<double> detectRRIntervals(const std::vector<double>& ecgData, int samplingRate) const{};
};