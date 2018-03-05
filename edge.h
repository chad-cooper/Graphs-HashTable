//
//  edge.h
//  Project4Files
//
//  Created by Chad Cooper on 7/1/17.
//  Copyright © 2017 Chad Cooper. All rights reserved.
//

#ifndef edge_h
#define edge_h

#include <string>
#include <stdexcept>

class Vertex;

using namespace std;


class Edge {
private:
    
    string edgeName;
    
    Vertex *source, *target;

    double weight;
    
public:
    
    // Constructor
    Edge(Vertex *edgeSource = nullptr, Vertex *edgeTarget = nullptr, double edgeWeight = 1){
        source = edgeSource;
        target = edgeTarget;
        weight = edgeWeight;
        
    }
    
    
    
    
    
    // Accessors
    
    Vertex* getSource() const {
        return source;
    }
    
    Vertex* getTarget() const {
        return target;
    }
    
    double getWeight() const {
        return weight;
    }
    
    string getName() const {
        return edgeName;
    }
    
    
    
    
    
    // Mutators
    
    void setSource(Vertex* edgeSource) {
        source = edgeSource;
    }
    
    void setTarget(Vertex* edgeTarget) {
        target = edgeTarget;
    }
    
    void setWeight(double edgeWeight){
        weight = edgeWeight;
    }
    
    void setName(string name){
        edgeName = name;
    }
    
    //overloaded = operator
    Edge& operator=(const Edge& rhsEdge){
        
        edgeName = rhsEdge.edgeName;
        source = rhsEdge.source;
        target = rhsEdge.target;
        weight = rhsEdge.weight;
        
        return *this;
    }

    friend ostream &operator<<(ostream &output, const Edge &E) {
        
        output << "Name: " << E.edgeName << ". Weight: " << E.weight;
        
        return output;
    }
    
    //Overloaded < operator
    bool operator<(const Edge& e) const {
        
        return weight > e.weight;
    }

    friend class DirGraph;
    friend class Graph;
    
    
}; // end of Edge class definition


#endif /* edge_h */
