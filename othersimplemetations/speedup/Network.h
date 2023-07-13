/*
 * Netwokk.h
 * Created on: 13 abr. 2021
 * Author: Alfonso Niño 
 */

#ifndef NETWORK2_H_
#define NETWORK2_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <math.h>
#include "reader.h"
using namespace std;

/**
 * \brief Defines a simple, compact network to determine connectivity
 *
 * 
 * This class uses a very simple and compact implementation of an adjacency
 * list based graph data structure. Its main goal is to determine the threshold
 * value of edge weights making a complete network to became unconnected. 
 * The connectivity is determined in parallel using the nc cores of the system.
 * The complexity is big oh logarithm base (nc + 1) of the difference between 
 * the maximum and minimum edge weight values.
 *  
 * @author SciCom research group. Universidad de Castilla-La Mancha. SPAIN
 * @date April 20, 2021
 */

class Network {

  // Private class members
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

  // Public class members
  public:

   /**
    * Constructor method. Here, the network is read and build. Also, the
    * maximum and minimum edge weight values are determined.
    * @param fileName The file to read to define the network
    */
   Network (std::vector<Edgenew> Edges,int size){
    std::cout<< "Procesando Array\n";
    Edge e;
    
    unsigned long aux;
    double w;
    nNodes = nEdges = nEdgesNew = 0;
    thrshld = 1.0;
    density = 1.0;
    nNodes=size;
    nEdges=Edges.size();
  
    nodes = new vector<Edge>[nNodes];

     
     e.originumber=Edges[0].originumber;
     e.destinationnumber=Edges[0].destinationnumber;
     e.weight = wMax = wMin = w=Edges[0].weight;
    
    

     aux = 1;

     // Prime read
     for (int i=1;i<Edges.size();i++){
          e.weight =w;
          nodes[e.originumber].push_back(e);
          nodes[e.destinationnumber].push_back(e);
          if (w > wMax) wMax = w;
          if (w < wMin) wMin = w;
          e.originumber=Edges[i].originumber;
          e.destinationnumber=Edges[i].destinationnumber;
          w=Edges[i].weight;
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
         //wEnd = wMax;
         wIni = thresholds[nCores - 1];
       }
       std::cout << "wIni, wEnd: " << wIni << " " << wEnd << endl << endl;
     }

     thrshld = wIni; // With a threshold > than this the network is unconnected

     return thrshld;
   }

   ~Network() {
     // Poner bien el destructor
     //delete[] nodes;
   }

double newNetwork(std::vector<Edgenew> CosinesAll, double thrd,unsigned long nNodes){
    unsigned long nEdgesNew;
    double density;
    std::cout << "procesando new network \n";
     std::ofstream outFile;
     unsigned long nNod, nEdg ,n;
     std::string o, d;
     double w;
     nEdgesNew = 0;
     outFile.open("./src/newNetwork.csv");
      nEdg=CosinesAll.size();
     n = 0;
     for (unsigned long i = 0; i< nEdg; i++){
      o=CosinesAll[i].originumber;
      d=CosinesAll[i].destinationnumber;
      w=CosinesAll[i].weight;
      if (w >= thrd) {
        nEdgesNew++;
        outFile << o << " " << d << " " << w << std::endl;
        n++;
      }
    }
     outFile.close();

     // Edge density
     density = nEdgesNew/ ((nNodes * (nNodes - 1.0)) / 2.0);
return density; // Edge density
}


};

#endif /* NETWORK_H_ */
