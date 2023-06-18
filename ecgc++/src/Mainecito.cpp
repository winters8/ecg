
#include <iostream>
#include <string>

#include "Network.h"

using namespace std;

int main(int argc, char** argv) {

  double thrs;

  Network ejem("./src/AntihisCOX2Tanimoto.txt");
  thrs = ejem.threshold();
  cout << "Threshold: " << thrs << endl;
  cout << "Edge density: " << ejem.newNetwork("./src/AntihisCOX2Tanimoto.txt", thrs);
  //ejem.~Network();

}
