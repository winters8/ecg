#ifndef ECG_H_
#define ECG_H_

#include "ecgInterface.h"
class ECG_singlederivation : public ecgInterface
{ 
    public:
        ECG_singlederivation(const std::string& str,NetworkCommunities::SparseArray ArrayDataDerivation) 
        :ecgInterface(str,ArrayDataDerivation){}

        //Set autocorrelation index
        double compute_autocorrelation_index(NetworkCommunities::SparseArray ArrayDataDerivation) override;
        std::vector<double> detectRRIntervals(const std::vector<double>& ecgData, int samplingRate) override;
};
#endif