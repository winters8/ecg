#ifndef ECG2_H
#define ECG2_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "SparseArray.h"
class ECG2 {
public:
    // Constructor
    ECG2(std::string str, NetworkCommunities::SparseArray ArrayData):ID(str),ArrayDataDerivation(ArrayData) {
        ID = str;
        ArrayDataDerivation = ArrayData;
    }

    // Métodos para acceder a los atributos
    std::string getID() const {
        return ID;
    }

    NetworkCommunities::SparseArray getderivationdata() const {
        return ArrayDataDerivation;
    }

    // Métodos para modificar los atributos
    void setID(std::string str) {
        ID = str;
    }

    void setderivationdata(NetworkCommunities::SparseArray ArrayData) {
        ArrayDataDerivation = ArrayData;
    }

private:
    std::string ID;
    NetworkCommunities::SparseArray ArrayDataDerivation;
};
#endif