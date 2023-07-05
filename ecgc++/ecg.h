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
};
#endif
