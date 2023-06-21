
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "ecginterface.h"
struct deriv{
        double valor[5010];

};
class ecg: public ecgInterface
{
private:
    std:: string ID;
    deriv A_;
public:
    ecg(std::string ID1,struct deriv A):ID(ID1),A_(A){};
    ~ecg();
};

