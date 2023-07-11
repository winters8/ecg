#ifndef READER_H
#define READER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "Network.h"
struct Edgenew {
      unsigned int originumber;
      unsigned int destinationnumber;
      double weight;              // Edge weight
    };
namespace fs = std::filesystem;
class reader{
public:
std::vector<Edgenew> readCSV(const std::string& filename);   
};
#endif