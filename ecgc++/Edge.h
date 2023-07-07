/*
 * Edge.h
 *
 * Class to represent a weighted edge in a network
 *
 */

#ifndef EDGE_H_
#define EDGE_H_

class Edge {
  private:
    int row;        // First node
    int column;     // Second node
    double weight;  // Edge weight

  public:
    /**
     * Edge constructor
     *
     * @param r The row of the element
     * @param c The column of the element
     * @param w The weight of the (i, j) edge
     *
     */
    Edge (int r, int c, double w){
      row = r;
      column = c;
      weight = w;
    }

    /** Accessor method
     *
     * @return The row (first node) of the edge
     */
    int getRow () {
      return row;
    }

    /** Accessor method
     *
     * @return The column (second node) of the edge
     */
    int getColumn () {
      return column;
    }

    /** Accessor method
     *
     * @return The weight of the edge
     */
    double getWeight () {
      return weight;
    }

    /**
     * Destructor method
     */
    ~Edge() {};

};

#endif /* EDGE_H_ */
