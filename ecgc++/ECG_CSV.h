
#ifndef ECG_CSV_H
#define ECG_CSV_H
#include "ECG_IO.h"

namespace fs = std::filesystem;


class ECG_CSV: public ECG_IO{
private:
struct Edge {
      unsigned int originumber;
      unsigned int destinationnumber;
      std::string origin;       // First node
      std::string destination;  // Second node
      double weight;              // Edge weight
    };

    unsigned long nNodes;    // Number of nodes
    unsigned long nEdges;    // Number of edges
    unsigned long nEdgesNew; // Number of edges in the minimum connected network
    double thrshld;          // Threshold edge weight
    double density;          // Edge density
    std::vector<Edge> *nodes;     // List of nodes
    double wMax, wMin;       // Maximum and minimum edge weights

public:

ECG** readfile(std::string directory,int sizearray) override {
    ECG ** listaECG= new ECG*[sizearray];
    int files_reader=0;
    int n=3507;
    int add=0;
    ECG *ecg;
    for (const auto& entry : fs::directory_iterator(directory)) {
        double deriv[n];
        const std::string filename = entry.path().string();
        std::cout <<files_reader<< "\n";
        std::ifstream file(filename);
            if (!file.is_open()) {
                std::cout << "Error opening file: " << filename << std::endl;
                continue;
            }
        std::string line;
        std::getline(file, line);
        int posarray=0;
        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            double value;
                try {
                    value = std::stod(line);
                    deriv[posarray]=value;
                    posarray++;
                } catch (const std::exception& e) {
                    std::cout << "Error converting cell to double: " << line << std::endl;
                }
        }
        file.close();
        ecg= new ECG("",deriv);
        std::filesystem::path filePath(filename);
        std::string fileECG = filePath.filename().string();
        ecg->setAutocorrelation_index(ecg->calculateNormalizedStandardDeviation(deriv));
        ecg->setBpm_index(ecg->CalculateBPM(deriv));
        ecg->setID_ECG(fileECG);
        listaECG[add]=ecg;
        files_reader++;
        }
    return listaECG;
}
int NormalizeBeginingpoingECGDATA(std::string directory,int columnIndex) override {
    std::vector<int> PosicionesprimerR;
    double derivraw[5010];
    int files_reader=1;
    char delimiter= ',';
    int discarded=0;
    for (const auto& entry : fs::directory_iterator(directory)) {
        const std::string filename = entry.path().string();
        std::cout <<files_reader<< "\n";
        std::ifstream file(filename);
            if (!file.is_open()) {
                std::cout << "Error opening file: " << filename << std::endl;
                continue;
            }
        std::string line;
        std::getline(file, line);
        int posarray=0;
        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            std::string cell;
            double value;
            for (int i = 0; i < columnIndex; i++) {
                if (!std::getline(lineStream, cell, ',')) {
                    break; // Invalid column number, or end of line reached
                }
            }
            if (std::getline(lineStream, cell, ',')) {
                try {
                    value = std::stod(cell);
                    derivraw[posarray]=value;
                    posarray++;
               
                } catch (const std::exception& e) {
                    std::cout << "Error converting cell to double: " << cell << std::endl;
                }
            }
        }
        file.close();
        int posicion = findFirstRPeak(derivraw);
        double derivnormalized[3507];
        if (posicion<1500){
            for(int z=posicion;z<3507;z++){
                derivnormalized[z-posicion]=derivraw[z];
            }
            files_reader++;
            fs::path filePath(filename);
            std::string file_Name = filePath.filename().string();
            std::cout <<"nombre archivo: "<< file_Name<<"\n";
            std::ofstream file2("C:/dataECG/norm/"+file_Name);
            file2<<"II\n";
            if (file2.is_open())
                {
                    for(int j=0;j<3507;j++){
                        file2 << std::to_string(derivnormalized[j]) <<"\n";
                    }
                    // Close the file
                    file2.close();
                    std::cout << "CSV file created successfully." << std::endl;
                }
                else
                {
                    std::cerr << "Failed to create the CSV file." << std::endl;
                }
        }
        else{
            discarded++;
        }
    }

    int max=0;
    for (const int posicion: PosicionesprimerR)
    {
        if(posicion>max){
            max=posicion;

        }
    }
    std::cout <<"archivos descartados : "<<discarded <<"\n";
    return 0;
};

int findFirstRPeak(double deriv[5010]) override {
    
    // Variables to track peak detection
    int rPeakIndex = -1;
    
    double maxAmplitude = deriv[0];
    for (int i = 1; i < 5010; ++i) {
        if (deriv[i] > maxAmplitude) {
            maxAmplitude = deriv[i];
        }
    }
    // Set a threshold for peak detection
    double threshold = 0.7 * maxAmplitude;
    std::cout << "el tamano de threshold en find es "<<threshold<<"\n";
    
    // Iterate over the ECG data
   for (int i = 1; i < 5010 - 1; ++i) {
        if (deriv[i] > deriv[i - 1] && deriv[i] > deriv[i + 1] && deriv[i] > threshold) {
            rPeakIndex = i;
            break;
        }
    }
    return rPeakIndex;
}
double newNetwork(SparseArray Array, double thrd)override{
    std::cout << "procesando new network \n";
     //ifstream inFile;
     std::ofstream outFile;
     unsigned long nNod, nEdg ,n;
     std::string o, d;
     double w;
     nEdgesNew = 0;
     //inFile.open(fileName);
     outFile.open("./src/newNetwork.csv");
     //inFile >> nNod;
     //outFile << nNod << endl;
     //inFile >> nEdg;
    nEdg=Array.get_nEdges();
     n = 0;
     for (unsigned long i = 0; i< nEdg; i++){
      o=Array.r(i);
      d=Array.c(i);
      w=Array.v(i);
      if (w >= thrd) {
        nEdgesNew++;
        outFile << o << " " << d << " " << w << endl;
        n++;
      }
    }
     outFile.close();

     // Edge density
     density = nEdgesNew/ ((nNodes * (nNodes - 1.0)) / 2.0);
     return density; // Edge density
   }
   int sizearray(std::string directory){ 
    DIR* dir;
    struct dirent* archivo;
    int contador = 0;

    // Abre el directorio
    dir = opendir(directory.c_str());

    if (dir) {
        // Itera sobre los archivos del directorio
        while ((archivo = readdir(dir)) != nullptr) {
            // Ignora los directorios "." y ".."
            if (archivo->d_name[0] != '.') {
                    contador++;
            }
        }

        // Cierra el directorio
        closedir(dir);
    }
    return contador;
}
};


#endif 