#ifndef DERIVATIONS_H
#define DERIVATIONS_H

#include <iostream>
#include <list>
#include <string>
#include <vector>

class Derivation {
    private:
        std::vector<double> derivation_data;
        std::string derivation_name;

    public:
        // Constructor derivation
        Derivation(const std::vector<double>& doubleList, const std::string& str) {
            derivation_data = doubleList;
            derivation_name = str;
        }
        
        // Getter derivation data
        std::vector<double> getdoubleList() const {
            return derivation_data;
        }

        // Getter name derivation
        std::string getString() const {
            return derivation_name;
        }

        // Setter data derivation
        void setIntList(const std::vector<double>& doubleList) {
            derivation_data = doubleList;
        }

        // Setter name derivation
        void setString(const std::string& str) {
            derivation_name = str;
        }
};
#endif 