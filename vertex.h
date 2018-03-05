//
//  vertex.h
//  Project4Files
//
//  Created by Chad Cooper on 7/1/17.
//  Copyright © 2017 Chad Cooper. All rights reserved.
//

#ifndef vertex_h
#define vertex_h


#include <list>
#include <stdexcept>
#include "edge.h"

using namespace std;

class Vertex {

private:
    
    string vName;		//Vertex name(Key)
    
    bool visited;
    
    int hashPosition;
    
    list<Edge*> adjVertices;
    
    // Pointer to the predecessor vertex for Dijkstra's algorithm
    Vertex* pred;
    
    // Distance from predecessor vertex for Dijkstra's algorithm. 
    double distance;
    
    // a list of edges that holds all of the edges leading into this vertex.
    list<Edge> edgesIn;
    
    // a list of edges that holds all of the edges leading into this vertex.
    list<Edge> edgesOut;

public:
    
    // Constructor
    Vertex(string name = "") {
        
        vName = name;
        visited = false;
        hashPosition = -1;
        distance = -1;
        pred = nullptr;
        
    }
    
    //Accessors
    
    string getName() const {
        
        return vName;
    }
    
    
    int getHashPosition() const {
        
        return hashPosition;
    }
    
    bool getVisited() const {
        return visited;
    }
    
    double getDistance() const {
        return distance;
    }
    
    Vertex* getPredecessor() const{
        return pred;
    }
    
    
    
    //Mutators
    
    void setName(string name) {
        
        vName = name;
    }
    
    
    void setHashPosition(int pos) {
        
        hashPosition = pos;
    }
    
    void setVisited(bool b){
        visited = b;
    }
    
    void addEdge(Vertex* initial, Vertex* terminal, double weight){
        
        Edge edgeBetween(initial, terminal, weight);
        edgeBetween.setName(initial->vName + "->" + terminal->vName);
        
        if(this == initial){ // if this vertex is the initial vertex, then the edge goes out.
            edgesOut.push_back(edgeBetween);
        } else if(this == terminal){ // if this vertex is the terminal vertex, then the edges comes in.
            edgesIn.push_back(edgeBetween);
        }
    }
    
    void addEdgeUndir(Vertex* in, Vertex* ter, double weight) {
        
        Edge* edgeBetween = new Edge(in, ter, weight);
        edgeBetween->setName(ter->vName);
        
        if (this == in) {
            adjVertices.push_back(edgeBetween);
        }
        else if (this == ter) {
            adjVertices.push_back(edgeBetween);
        }
    }
    
    void removeEdge(Edge* e) {
        
        adjVertices.remove(e);
        
    }
    
    void setDistance(double dist){
        distance = dist;
    }
    
    void setPredecessor(Vertex* mPred){
        pred = mPred;
    }
    
    
    static bool edgeComparison(const Edge &one, const Edge &two){
        
        string name1, name2;
        
        name1 = one.getName();
        name2 = two.getName();
        
        for(int i = 0; (i < name1.size()) && (i < name2.size()); i++){
            
            if(toupper(name1[i]) < toupper(name2[i])){
                return true;
            } else if (toupper(name1[i]) > toupper(name2[i])){
                return false;
            }
            
        }
 
        return (name1.size() < name2.size());
        
    }
    
    void sortEdges(){
        
        edgesIn.sort(edgeComparison);
        edgesOut.sort(edgeComparison);
        
    }

    
    static bool unEdgeComparison(const Edge* one, const Edge *two) {
        
        string name1, name2;
        
        name1 = one->getName();
        name2 = two->getName();
        
        for (int i = 0; (i < name1.size()) && (i < name2.size()); i++) {
            
            if (toupper(name1[i]) < toupper(name2[i])) {
                return true;
            }
            else if (toupper(name1[i]) > toupper(name2[i])) {
                return false;
            }
            
        }
        
        return (name1.size() <  name2.size());
    }
    
    void sortEdgesUndir() {
        
        adjVertices.sort(unEdgeComparison);
    }
    
    
    
    
    
    
    
    friend ostream &operator<<(ostream &output, const Vertex &V) {
        
        output << "Name: \"" << V.vName << "\". Position: " << V.hashPosition
        << ". Visted: " << (V.visited?"Yes.":"No.") << " In degree: " << V.edgesIn.size()
        << ". Out degree: " << V.edgesOut.size();
        
        return output;
    }
    
    
    //overloaded = operator
    Vertex& operator=(const Vertex& rhsVertex){
        vName = rhsVertex.vName;
        visited = rhsVertex.visited;
        hashPosition = rhsVertex.hashPosition;
        edgesIn = rhsVertex.edgesIn;
        edgesOut = rhsVertex.edgesOut;
        
        return *this;
    }
    
    friend class DirGraph;
    friend class Graph;

};

#endif /* vertex_h */
