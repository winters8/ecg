#ifndef ECG_H
#define ECG_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "ecginterface.h"
struct deriv{
        double valor[5010];

};
class ecg_singlederiv: public ecgInterface
{
private:
    std:: string ID;
    deriv A_;
    double autocorrelationindex;
public:
    ecg_singlederiv(const std::string id, struct deriv A){
        ID=id;
        A_=A;
    };

    deriv getderiv() const {
        return A_;
    };
    
    std::string getID_ECG() const override{
        return ID;
    };
    void setderiv(struct deriv A){
        A_=A;
    };

    void setID_ECG(std::string id)override{
        ID=id;
    }
    void setAutocorrelation_index(double index) override {
        autocorrelationindex=index;
    }
};
#endif
