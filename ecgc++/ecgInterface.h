#ifndef ECGINTERFACE_H_
#define ECGINTERFACE_H_

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "derivations.h"
#include "SparseArray.h"
class ecgInterface
{
private:
        std::string ID;
        double autocorrelation_index;
        NetworkCommunities::SparseArray thisArrayDataDerivation;
public:
    ecgInterface(const std::string& str,NetworkCommunities::SparseArray ArrayDataDerivation)
    : ID(str),thisArrayDataDerivation(ArrayDataDerivation){};

    NetworkCommunities::SparseArray getDerivations()const {
        return thisArrayDataDerivation;
    };
    string getID_ECG() const {
        return ID;
    };
    virtual double compute_autocorrelation_index(NetworkCommunities::SparseArray ArrayDataDerivation) = 0;
    virtual std::vector<double> detectRRIntervals(const std::vector<double>& ecgData, int samplingRate) = 0;
};
#endif