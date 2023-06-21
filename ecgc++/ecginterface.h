#include <iostream>
#include <vector>
#include <string>
#include <cmath>
class ecgInterface
{
    struct deriv{
        double valor[5010];
    };
public:
    struct  deriv deriv;
    virtual std::string getID_ECG(){}
    virtual double compute_autocorrelation_index(struct deriv)const{};
    virtual std::vector<double> detectRRIntervals(const std::vector<double>& ecgData, int samplingRate) const{
        std::vector<double> rrinterval;
        return rrinterval;
    };
};