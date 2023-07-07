
#ifndef ECG_NET_H
#define ECG_NET_H
#include "ECG_CSV.h"
/* Function to calculate the cosine similarity index
* of two ECG data
*/
class ECG_Net{
private:
struct Edge {
      unsigned int originumber;
      unsigned int destinationnumber;
      double weight;              // Edge weight
    };
 unsigned long nNodes;    // Number of nodes
    unsigned long nEdges;    // Number of edges
    unsigned long nEdgesNew; // Number of edges in the minimum connected network
    double thrshld;          // Threshold edge weight
    double density;          // Edge density
    vector<Edge> *nodes;     // List of nodes
    double wMax, wMin;       // Maximum and minimum edge weights
public:
ECG_Net();
SparseArray cosineSimilarity(ECG * listECG[],int sizearray){
    /*Beginning of the part of the code 
    * to be parallelized with OpenMP
    */
   size_t sizetotal=sizearray*(sizearray-1)/2;
   SparseArray Array(sizetotal);
    #pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        /*for parallelized with OpenMP 
        * to improve efficiency with multi-thread
        * computing and with the shedule option 
        * to automatically distribute the work equally among them
        */
        #pragma omp for schedule(auto)
        for (int i=0; i < sizearray; ++i)   
            {
                int myThreadID = threadID;
                ECG* ecga= listECG[i];
                string IDA= ecga->getID_ECG();
                std::cout <<"el archivo: "<<IDA << " esta siendo procesado por el hilo: "<<myThreadID<<"\n";
                double* derivnormA = ecga->getderivnorm();
                double valuea;
                double sumOfSquaresaA = 0.0;
                int sizea = 3507;
                for (int z=0; z<sizea; ++z)
                    {
                      valuea=derivnormA[z];
                        sumOfSquaresaA += valuea * valuea;  
                    }
                    double sqrtA = std::sqrt(sumOfSquaresaA);

                for (int t=i+1; t<sizearray; ++t)
                    {
                    ECG* ecgb=listECG[t];
                    string IDB= ecgb->getID_ECG();
                   
                    double * derivnormB= ecgb->getderivnorm();    
                    double product = 0.0;
                        for (size_t m = 0; m < sizea; ++m)
                            {
                              
                                product += derivnormA[m] * derivnormB[m];
                               
                            }

                    double valueB;
                    double sumOfSquaresaB = 0.0;
                        for (int r=0; r< sizea; ++r)
                            {
                                valueB=derivnormB[r];
                                sumOfSquaresaB += valueB * valueB;
                            }
                        
                        double sqrtB = std::sqrt(sumOfSquaresaB);
                        double producctoAB = sqrtA * sqrtB;
                        double division = product/producctoAB;
                        /*fiter for incorrect valors*/
                        if(division<=1 && division>=-1){
                            Array.put(i,t,division);
                        }                    
                    }
            
            }
           
    }
return Array;
}

ECG_Net (SparseArray Array, int size){
    std::cout<< "Procesando Array\n";
    Edge e;
    
    unsigned long aux;
    double w;
    nNodes = nEdges = nEdgesNew = 0;
    thrshld = 1.0;
    density = 1.0;
    nNodes=size;
    nEdges=Array.get_nEdges();
  
    nodes = new vector<Edge>[nNodes];

     
     e.originumber=Array.r(0);
     e.destinationnumber=Array.c(0);
     e.weight = wMax = wMin = w=Array.v(0);
    
    

     aux = 1;

     // Prime read
     for (int i=1;i<Array.get_nEdges();i++){
          e.weight =w;
          nodes[e.originumber].push_back(e);
          nodes[e.destinationnumber].push_back(e);
          if (w > wMax) wMax = w;
          if (w < wMin) wMin = w;
          e.originumber=Array.r(i);
          e.destinationnumber=Array.c(i);
          w= Array.v(i);
      aux++;    // Counting the actual number of edges read
     }
    

     if (aux != nEdges) {
       std::cout << " Number of edges read: " << aux << " number expected: "
            << nEdges <<". ERROR in data, check edges." << endl;
       exit(0);
     }

     std::cout << "Max weight: " << wMax << ", Min weight: " << wMin << endl;
     
   }


   
  /**
   * This method returns the node adjacent to another node along the edge
   * connecting them.
   * @param i The reference node
   * @param e The edge considered
   * @return The node adjacent to i along e
   */
   unsigned long adjacent (unsigned long i, Edge e) {
     if (e.originumber == i)
       return e.destinationnumber;
     else
       return e.originumber;
   }

   
  /**
   * Method threshold determines the edge weight value (threshold) from which
   * the network becomes unconnected. To determine connectivity a BFS traversal
   * is used. If the number of visited nodes equals the number of nodes in the
   * network, then, the network is connected and it is not otherwise. Open MP is
   * used to run BFS simultaneously with different threshold values. All nc
   * processors available in the system are used. The complexity is big oh
   * logarithm base (nc + 1) of the difference between the maximum and minimum
   * edge weight values.
   * @return The threshold edge value where the network is still connected.
   */
   double threshold(){
    std::cout << "procesando threshold \n";
     double delta, wIni, wEnd, epsilon;
     double *thresholds;
     int j, k, nIter;
     unsigned long *nodesConect;
     unsigned long m, u, z;
     queue<unsigned long> *aux;
     bool allConnected, goOn;

     const int nCores = 4;     // Recuperar el n�mero de cores con OpenMP
     epsilon = 0.01; // Maximum edge weight interval size
     thresholds = new double [nCores];
     aux = new queue<unsigned long> [nCores]; 
     bool visit [nCores][nNodes];
     nodesConect = new unsigned long[nCores];

     delta = (wMax - wMin);

     // Number of iterations to reach at least "precision"
     nIter = 1 + (log(delta) - log(epsilon))/log(nCores+1.0);

     wIni = wMin;
     wEnd = wMax;
     std::cout << endl << "Threshold iterations: " << nIter << endl << endl;

     for (int i = 0; i < nIter; i++) {
       std::cout << "Iteration: " << i << endl;
       allConnected = true;
       goOn = true;
       delta = (wEnd - wIni) / (nCores + 1); // Computing increment in this iteration
       for (k = 0; k < nCores; k++){
         thresholds[k] = wIni + delta * (k + 1);
         nodesConect[k] = 0;
         for (m = 0; m < nNodes; m++) visit [k][m] = false;
       }

       // Next loop in parallel
       for (j = 0; j < nCores; j++) {

         // DFS traversal
         aux[j].push(0);
         visit[j][0] = true;
         nodesConect[j]++;
         while (!aux[j].empty()){
           u = aux[j].front(); // Recovering first element
           aux[j].pop();       // Removing first element
           for (auto edg : nodes[u]){
             if (edg.weight > thresholds[j] ) {
               z = adjacent (u, edg);
               if (!visit[j][z]){
                 nodesConect[j]++; // Counting visited nodes
                 visit[j][z] = true;
                 aux[j].push(z);
               }
             }
           }
         }
       } // End of parallel for

       std::cout << "Thresholds     #Nodes" << endl;
       for (j = 0; j < nCores; j++) std::cout << thresholds[j] << "       "
                                         << nodesConect[j] << endl;
       for (j = 0; j < nCores && goOn; j++){
         if (nodesConect[j] != nNodes) {
           goOn = false;
           allConnected = false;
           wEnd = thresholds[j];
           if (j != 0) wIni = thresholds[j - 1];
         }
       }
       if (allConnected) {
         wEnd = wMax;
         wIni = thresholds[nCores - 1];
       }
       std::cout << "wIni, wEnd: " << wIni << " " << wEnd << endl << endl;
     }

     thrshld = wIni; // With a threshold > than this the network is unconnected

     return thrshld;
   }

};
#endif