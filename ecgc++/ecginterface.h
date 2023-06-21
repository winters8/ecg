#include <iostream>
#include <string>

class ecgInterface
{
public:
    virtual std::string getID_ECG() const {
        return " ";
    }
    virtual void setID_ECG(std::string id){}
    virtual void setAutocorrelation_index(double index){}
};