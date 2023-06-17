#include <iostream>
#include <list>
#include <string>

class Derivation {
private:
    std::list<double> derivation_data;
    std::string derivation_name;

public:
    // Constructor derivation
    Derivation(const std::list<double>& doubleList, const std::string& str) {
        derivation_data = doubleList;
        derivation_name = str;
    }
    
    // Getter derivation data
    std::list<double> getdoubleList() const {
        return derivation_data;
    }

    // Getter name derivation
    std::string getString() const {
        return derivation_name;
    }

    // Setter data derivation
    void setIntList(const std::list<double>& doubleList) {
        derivation_data = doubleList;
    }

    // Setter name derivation
    void setString(const std::string& str) {
        derivation_name = str;
    }
};