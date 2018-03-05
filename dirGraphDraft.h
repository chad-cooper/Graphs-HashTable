//
//  dirGraphDraft.h
//  Project4Files
//
//  Created by Chad Cooper on 7/5/17.
//  Copyright © 2017 Chad Cooper. All rights reserved.
//

#ifndef dirGraphDraft_h
#define dirGraphDraft_h


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "vertex.h"
#include "edge.h"
#include "hashTable.h"


//template <typename Type>
class DirGraph{
    
    
    //    typedef Edge<Type> Edge;
    //    typedef Vertex<Type> Vertex;
    
private:
    // data members
    
    HashTable myVertices;
    
    vector<Edge> myEdges;
    
    
    
    
public:
    // member methods
    
    //Accessors
    
    //Returns true if the graph is empty, false otherwise.
    bool empty(){
        return true;
    }
    
    // Returns the indegree of the vertex v. Throw an
    // illegal argument exception if the argument does not correspond to an existing
    // vertex.
    int inDegree(string v){
        
        Vertex tempVertex = *(myVertices.retrieveFromTable(v));
        
        int inDegree = tempVertex.adjacentFrom.size();
        
        return inDegree;
        
    }
    
    // Returns the outdegree of the vertex v. Throw
    // an illegal argument exception if the argument does not correspond to an existing
    // vertex.
    int outDegree(string v){
        
        Vertex tempVertex = *(myVertices.retrieveFromTable(v));
        
        int outDegree = tempVertex.adjacentTo.size();
        
        return outDegree;
        
    }
    
    // Returns the number of edges in the graph
    int edgeCount(){
        
        return myEdges.size();
        
    }
    
    // Returns the weight of the edge connecting vertices u and v. If the vertices are the same, return 0. If the vertices
    // are not adjacent, return -1 (our representation of ifinity). Throw an illegal
    // argument exception if the arguments do not correspond to existing vertices.
    double adjacent( string u, string v ) throw (invalid_argument) {
        
        // If 'u' and 'v' are the same, 0 is returned.
        if(u == v){
            return 0;
        }
        
        // findEdgeBetween may throw an exception.
        try {
            
            // The edge between 'u' and 'v' is found.
            Edge* arc = findEdgeBetween(u, v);
            
            
            if(arc != nullptr){
                return arc->getWeight();
            } else {
                return -1;
            }
            
        }
        
        // if 'v' or 'u' aren't in the graph, an exception is thrown.
        catch (exception &e) {
            throw invalid_argument(e.what());
        }
    }
    
    
    
    // Performs DFS traversal starting on vertex v. Reset ver-
    // tices after the traversal. Prints the order of vertices visited.
    void DFS(string v) {
        
    }
    
    // Performs BFS traversal starting on vertex v. Reset ver-
    // tices after the traversal. Prints the order of vertices visited.
    void BFS(string v){
        
    }
    
    // Returns the shortest path using Dijkstra's between vertices u and v.
    // Throw an illegal argument exception if the arguments do not correspond to existing vertices.
    void shortPath( string u, string v ){
        
    }
    
    // Returns the shortest distance between vertices u and v.
    // Throw an illegal argument exception if the arguments do not correspond to existing vertices.
    // The distance between a vertex and itself is 0.0.
    // The distance between vertices that are not connected is -1 (our representation of infinity).
    double distance( string u, string v ){
        return 0;
    }
    
    
    
    
    
    // Mutators
    
    //Reads structure from a text file and builds a directed weighted graph.
    void buildGraph(){
        
        string fileName, line, inputVertex, initialVertex, terminalVertex;;
        double weight;
        
        // Gets the name of the file.
        cout << "Enter the name of the file from which you wish to build the graph.\n";
        //getline(cin, fileName);
        
        fileName = "graph.txt";
        
        ifstream graphFile;
        
        // Opens file and connects it to graphFile.
        graphFile.open(fileName);
        
        // The first line is different from the rest, in that it holds all the vertices.
        getline(graphFile, line);
        
        istringstream issVertex(line);
        
        while( getline(issVertex, inputVertex, ' ') ){
            insert(inputVertex);
        }
        
        while(getline(graphFile, line)){
            istringstream issEdge(line);
            
            issEdge >> initialVertex >> terminalVertex >> weight;
            //            issEdge >> terminalVertex;
            //            issEdge >> weight;
            
            insert(initialVertex, terminalVertex, weight);
        }
        
        
        graphFile.close();
        
    }
    
    // Removes all the elements in the undirected weighted graph
    void clear(){
        myVertices.clearHashTable();
        myEdges.clear();
    }
    
    // Iterates over all vertices and marks them as unvisited.
    void reset(){
        
        for(int i = 0; i < myVertices.vertexTable.size(); i++){
            myVertices.vertexTable[i].setVisited(false);
        }
        
        /*
         // Pointer to current vertex.
         Vertex* currentVertex;
         
         for(int i = 0; i < 19; i++){
         currentVertex = myVertices.getVertexAtPosition(i);
         
         currentVertex->setVisited(false);
         }*/
        
    }
    
    
    // This inserts a single vertex.
    void insert(string n){
        
        // Checks whether this vertex is already in the table.
        // If it is, n
        try{
            myVertices.retrieveFromTable(n);
            
            cout << n + " is already present in the graph." << endl;
            
        }
        
        // If the vertex is not in the table, then a new one is added.
        catch (exception &e){
            
            Vertex newVertex(n);
            
            // adds a new vertex with name 'n',
            // by copying the contents of n to the hash table.
            myVertices.addToTable(newVertex);
            
        }
        
    }
    
    /* If the weight w <= 0, throw an illegal argument exception.
     If the weight is w > 0, add an edge between vertices
     u and v. If an edge already exists, replace the weight of the edge with the
     new weight. If the vertices do not exist or are equal, throw an illegal argument
     exception. */
    void insert(string u, string v, double w) throw (invalid_argument){
        
        // If w is valid, and u & v aren't the same.
        if(w > 0 && u != v){
            
            // Will throw exception if 'u' or 'v' don't exist.
            try{
                
                double currentWeight = adjacent(u, v);
                
                
                // If there is already an edge between 'u' and 'v',
                // then it will have a weight that is greater than 0.
                if(currentWeight > 0){
                    Edge* existingEdge = findEdgeBetween(u, v);
                    
                    existingEdge->setWeight(w);
                }
                
                // The vertices exist, but there is no edge between them yet.
                // Time to add an edge to these vertices.
                else {
                    
                    // Vertex pointers to the source and target in the hash table
                    Vertex* source = myVertices.retrieveFromTable(u);
                    Vertex* target = myVertices.retrieveFromTable(v);
                    
                    // Add vertices to respective adjacency lists.
                    
                    // source 'u' is adjacent to target 'v'
                    source->adjacentTo.push_front(target);
                    // target 'v' is adjacent from source 'u'
                    target->adjacentFrom.push_front(source);
                    
                    Edge edgeBetween(source, target, w);
                    
                    myEdges.push_back(edgeBetween);
                    
                }
                
                // 'u' or 'v' don't exist.
            } catch (exception &e){
                throw invalid_argument(e.what());
            }
            
            // w is invalid, or 'u' and 'v' are the same vertex.
        } else {
            
            string reason = ((u == v)?("These vertices are the same."):("An edge's weight must be greater than 0."));
            
            throw invalid_argument(reason);
        }
    }
    
    
    // Auxiliary Functions
    
    
    void printEdges(){
        for(int i = 0; i < myEdges.size(); i++){
            cout << myEdges[i] << endl;
        }
    }
    
    void printVertices(){
        
        for(int i = 0; i < myVertices.vertexTable.size(); i++){
            if(myVertices.vertexTable[i].getName() != ""){
                cout << myVertices.vertexTable[i] << endl;
            }
        }
        
        //myVertices.displayTable();
    }
    
    // Returns a pointer to the edge with source 'u' and target 'v'.
    Edge* findEdgeBetween(string u, string v){
        try{
            Vertex *sourceV = myVertices.retrieveFromTable(u);
            Vertex *targetV = myVertices.retrieveFromTable(v);
            
            // If there is an edge that has a source 'u' and target 'v', its address will
            // be returned
            for(int i =0; i < myEdges.size(); i++){
                if(myEdges[i].getSource() == sourceV && myEdges[i].getTarget() == targetV){
                    return &myEdges[i];
                }
            }
            
            // if there is no such edge, nullptr is returned;
            return nullptr;
            
        } catch (exception &e){
            // If 'u' or 'v' aren't in the graph, then an invalid argument exception is thrown.
            throw invalid_argument(e.what());
        }
    }
    
};


#endif /* dirGraphDraft_h */
