#include <iostream>
#include <vector>
#include <string>
#include "derivations.h"

class ECG{
public:
    std::string ID;
    std::vector<Derivation> derivations;
    //Constructor ECG
    ECG(const std::string& str,const std::vector<Derivation>& deriv){
    ID = str;
    derivations=deriv;
    }
    //Getter derivations list
    std::vector<Derivation> getDerivations() const{
        return derivations;
    }
    //Getter ECG ID
    std::string getID_ECG() const{
        return ID;
    }
    void add_derivation(Derivation Derivation) {
        derivations.push_back(Derivation);
        
    }
};