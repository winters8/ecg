/*

Copyright (C) 2023  A. Ni�o

Network.h is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Network.h is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Network.h.  If not, see <https://www.gnu.org/licenses/>.

*/



/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: July 2023, August, 2018
*
* Purpose: Definition (header) and implementation file for class SparseArray
*          Class SparseArray is essentially a compact form of representing
*          adjacency matrices. It can represent dense arrays without problems,
*          but its structure allows also representing efficiently sparse
*          arrays.
*****************************************************************************/

/**
 * @file
 * Definition (header) and implementation file for class SparseArray.
 * This class is part of the package networkCommunities.
*/

#ifndef SPARSEARRAY_H
#define SPARSEARRAY_H

#include "Edge.h"

  /**
 * \brief Defines a sparse (usually) array representation of an adjacency matrix
 *
 * This class represents an adjacency matrix where only non-zero elements are
 * stored.
 * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
 *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
 *
 * @date July 2023, August, 2018
 */


class SparseArray {
  private:
    Edge* matrix;    // Array of edges
    int M;           // Number of edges added to the network
    int index;       // Current index of array matrix

  public:

    /**
     * Constructor
     * @param n The number of rows (edges) in the array
     */
    SparseArray(int n){
      M = n;
      index = -1;
      matrix = new Edge[M];
    }


    /**
     * Method for adding the i, j element to the sparse array.
     * @param i The row of the edge
     * @param j The column of the edge
     * @param value The weight of the (i, j) edge
     */
    void put (int i, int j, double value){
      index++;
      matrix[index] = Edge (i, j, value);
    }


    /**
     * Method for retrieving the row of the ith edge from the sparse array
     * @param i The edge index of the element
     * @return The row (first node) of the ith element (edge)
     */
    int r (int i){
      return matrix[i].getRow();
    }


    /**
     * Method for retrieving the column of the ith element from the
     * sparse array
     * @param i The edge index of the element
     * @return The column (second node) of the ith element (edge)
     */
    int c (int i){
      return matrix[i].getColumn();
    }


    /**
     * Method for retrieving the weight of the ith element from the
     * sparse array
     * @param i The edge index of the element
     * @return The value (weight) of the ith element (edge)
     */
    double v (int i){
      return matrix[i].getWeight();
    }


    /**
     * Method for getting the number of edges (non-zero elements) in the
     * network
     * @return The number of edges in the network.
     */
    int get_nEdges(){
      return M;
    }


    /**
     * Destructor method
     */
    ~SparseArray(){
      delete[] matrix;
    }
};

#endif /* SPARSEARRAY_H */
