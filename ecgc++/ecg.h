#include <iostream>
#include <list>
#include <string>
#include "derivations.h"

class ECG{
private:
    std::string ID;
    std::list<Derivation> derivations;

public:
    //Constructor ECG
    ECG(const std::list<Derivation>& derivationList, const std::string& str){
    derivations = derivationList;
    ID = str;
    }
    //Getter derivations list
    std::list<Derivation> getDerivations() const{
        return derivations;
    }
    //Getter ECG ID
    std::string getID_ECG() const{
        return ID;
    }
};