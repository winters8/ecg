#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "SparseArray.h"
class ecgInterface
{
public:
    virtual string getID_ECG()const{
        string id="";
        return id;
    };
    virtual NetworkCommunities::SparseArray getDerivation_ECG() const{
        NetworkCommunities::SparseArray array (1);
        return array;
    };
    virtual double compute_autocorrelation_index(NetworkCommunities::SparseArray ArrayDataDerivation) const{
        return 0;
    };
    virtual std::vector<double> detectRRIntervals(const std::vector<double>& ecgData, int samplingRate) const{
        std::vector<double> rrinterval;
        return rrinterval;
    };
};