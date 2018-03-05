//
//  dirGraph.h
//  Project4Files
//
//  Created by Chad Cooper on 7/1/17.
//  Copyright © 2017 Chad Cooper. All rights reserved.
//

#ifndef dirGraph_h
#define dirGraph_h


#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include "hashTable.h"


class DirGraph{

private:
    // data members
    
    HashTable myVertices;
    
public:
    // member methods
    
    //Accessors
    
    //Returns true if the graph is empty, false otherwise.
    bool empty(){
        
        for(int i = 0; i < myVertices.vertexTable.size(); i++){
            if(myVertices.vertexTable[i].getName() != ""){
                return false;
            }
        }
        
        return true;
    }
    
    /* Returns the indegree of the vertex v. Throw an
     illegal argument exception if the argument does not correspond to an existing
     vertex.*/
    int inDegree(string v) throw (invalid_argument){
        
        try{
            Vertex tempVertex = *(myVertices.retrieveFromTable(v));
        
            int inDegree = tempVertex.edgesIn.size();
        
            return inDegree;
        } catch (exception &e){
            throw invalid_argument(e.what());
        }
        
    }
    
    /* Returns the outdegree of the vertex v. Throw
     an illegal argument exception if the argument does not correspond to an existing
     vertex.*/
    int outDegree(string v) throw (invalid_argument){
        try {
            Vertex tempVertex = *(myVertices.retrieveFromTable(v));
            
            int outDegree = tempVertex.edgesOut.size();
            
            return outDegree;
        } catch (exception &e){
            throw invalid_argument(e.what());
        }
        
    }
    
    // Returns the number of edges in the graph
    int edgeCount(){
        
        int totalEdges = 0;
        for(int i = 0; i < myVertices.vertexTable.size(); i++){
            totalEdges += myVertices.vertexTable[i].edgesOut.size();
        }
        
        return totalEdges;
        
    }
    
    /* Returns the weight of the edge connecting vertices u and v. 
     If the vertices are the same, return 0. If the vertices
     are not adjacent, return -1 (our representation of ifinity). Throw an illegal
     argument exception if the arguments do not correspond to existing vertices.*/
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
    
    
    
    /* Performs DFS traversal starting on vertex v. Reset ver-
     tices after the traversal. Prints the order of vertices visited.*/
    void DFS(string v) {
        
        Vertex* currentVertex = myVertices.retrieveFromTable(v);
        
        if(currentVertex->getVisited() == true){
            return;
        }
        
        // The vertex has been visited, so it will not be visited twice.
        currentVertex->setVisited(true);
        
        cout << currentVertex->getName() << " " ;
        
        // If the vertex is a dead end, back up
        if(currentVertex->edgesOut.size() == 0){
            return;
        }
        
        currentVertex->sortEdges();
        
        for(list<Edge>::iterator it = currentVertex->edgesOut.begin(); it != currentVertex->edgesOut.end(); it++){
            string neighbor = (*it).getTarget()->getName();
            DFS(neighbor);
        }
    }
    
    /* Performs BFS traversal starting on vertex v. Reset ver-
     tices after the traversal. Prints the order of vertices visited. */
    void BFS(string v){

        queue<Vertex*> pendingVertices;
        
        Vertex* startingVertex = myVertices.retrieveFromTable(v);
        startingVertex->setVisited(true);
        
        // The queue is initialized to contain only the starting vertex.
        pendingVertices.push(startingVertex);
        
        Vertex* currentVertex;
        
        while(!pendingVertices.empty()){
            
            // removes  the first element from the queue, and sets it to the current vertex.
            currentVertex = pendingVertices.front();
            pendingVertices.pop();
            
            // Sorts the edges into alphabetical order.
            currentVertex->sortEdges();
            
            cout << currentVertex->getName() << ", ";
            
            for(list<Edge>::iterator it = currentVertex->edgesOut.begin(); it != currentVertex->edgesOut.end(); it++){
                
                // If the neighbors have not already been visited, they will be added to the queue.
                if(!it->getTarget()->getVisited()){
                    pendingVertices.push(it->getTarget());
                    it->getTarget()->setVisited(true);
                }
                
            } // end for
            
        } // end while
        
    } // end BFS
    
    /* Returns the shortest path using Dijkstra's between vertices u and v.
     Throw an illegal argument exception if the arguments do not correspond to existing vertices.*/
    void shortPath( string u, string v ) throw (invalid_argument) {
        
        try{
            
            Vertex* initialVertex = myVertices.retrieveFromTable(u);
            
            // If Dijkstra's algorithm has not already been used on this vertex,
            // it will be be called. Eliminates unnecessary calls of Dijkstra's algorithm.
            if(initialVertex->distance != 0){
                Dijkstra(u);
            }
            
            Vertex* terminalVertex = myVertices.retrieveFromTable(v);
            
            if(terminalVertex->getDistance() == -1){
                cout << u + " and " + v + " are not connected." << endl;
            } else {
                cout << terminalVertex->getName() << terminalVertex->getDistance() << endl;
            }
                
        } catch (exception &e) {
            
            throw invalid_argument(e.what());
        }
    } // end of shortPath function
                
    
    /* Returns the shortest distance between vertices u and v.
     Throw an illegal argument exception if the arguments do not correspond to existing vertices.
     The distance between a vertex and itself is 0.0.
     The distance between vertices that are not connected is -1 (our representation of infinity). */
    double distance( string u, string v ) throw (invalid_argument){
        
        // will throw an exception is u or v don't exist.
        try{
            Edge* UtoV = findEdgeBetween(u, v);
            
            // If u and v exist, and are not the same vertex
            if(UtoV != nullptr) {
                return UtoV->getWeight();
                
            } else {
                
                // There is no edge from U to V either because u == v or they aren't connected.
                // If u == v, 0.0 is returned. Otherwise, -1 is returned.
                return ((u == v)? 0.0: -1);
            }
        } catch (exception &e){
            throw invalid_argument(e.what());
        }
        
        return 0;
    }
    
    
    
    
    
    // Mutators
    
    //Reads structure from a text file and builds a directed weighted graph.
    void buildGraph(){
        
        string fileName, line, inputVertex, initialVertex, terminalVertex;;
        double weight;
        
        // Gets the name of the file.
        cout << "Enter the name of the file from which you wish to build the graph.\n";
        getline(cin, fileName);
        
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
            
            insert(initialVertex, terminalVertex, weight);
        }
        
        
        graphFile.close();
      
    }
    
    // Removes all the elements in the undirected weighted graph
    void clear(){
        myVertices.clearHashTable();
    }
    
    // Iterates over all vertices and marks them as unvisited.
    void reset(){
        
        for(int i = 0; i < myVertices.vertexTable.size(); i++){
            myVertices.vertexTable[i].setVisited(false);
            myVertices.vertexTable[i].setDistance(-1);
            myVertices.vertexTable[i].setPredecessor(nullptr);
        }
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
                    
                    // Will add an edge out of source.
                    source->addEdge(source, target, w);
                    
                    // Will add an edge in to target.
                    target->addEdge(source, target, w);
                    
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
        
        for(int i = 0; i < myVertices.vertexTable.size(); i++){
            
            for(list<Edge>::const_iterator it = myVertices.vertexTable[i].edgesOut.begin();
                it != myVertices.vertexTable[i].edgesOut.end(); it++){
                cout << "Name: " << it->getName() << ". Weight: " << it->getWeight() << ".\n";
            }
            
            
        }

    }
    
    void printVertices(){
        
        for(int i = 0; i < myVertices.vertexTable.size(); i++){
            if(myVertices.vertexTable[i].getName() != ""){
                cout << myVertices.vertexTable[i] << endl;
            }
        }
        
    }
    
    
    // Returns a pointer to the edge with source 'u' and target 'v'.
    Edge* findEdgeBetween(string u, string v){
        try{
            Vertex *sourceU = myVertices.retrieveFromTable(u);
            Vertex *targetV = myVertices.retrieveFromTable(v);
            
            // The sources edgesOut list is traversed until an edge with target 'u' is found.
            // A pointer to this edge is returned.
            for(list<Edge>::iterator iter = sourceU->edgesOut.begin(); iter != sourceU->edgesOut.end(); iter++){
                
                if((*iter).getTarget() == targetV){
                    
                    Edge *edgePtr = &(*iter);
                    
                    return edgePtr;
                }
                
            }
            
            // if there is no such edge, nullptr is returned;
            return nullptr;
            
        } catch (exception &e){
            // If 'u' or 'v' aren't in the graph, then an invalid argument exception is thrown.
            throw invalid_argument(e.what());
        }
    }
                
            
    void shortestToAll(string u) throw(invalid_argument) {
        
        try{
            Dijkstra(u);
            
            Vertex* startingVertex = myVertices.retrieveFromTable(u);
            
            int stVertIndex = startingVertex->getHashPosition();
            
            // starts at the current vertex, then proceeds through all non-null hash positions.
            for(int i = 0; i < myVertices.vertexTable.size(); i++ ){
                if( myVertices.vertexTable[(i+stVertIndex) % 19].getName() != ""){
                    shortPath(u, myVertices.vertexTable[(i+stVertIndex) % 19].getName());
                }
            }
            
        } catch (exception &e) {
            throw invalid_argument(e.what());
        }
        
    }
    
                
    void Dijkstra(string u) throw (invalid_argument){
        try{
            vector<Vertex*> set; // this is the set of finished vertices
            vector<Vertex*> verVec; // this holds the vertices
            
            Vertex* nextVertex; // this is the next vertex that will be added to the set.
            
            // Adds the non-null vertices to a vector for easy access.
            for(int i = 0; i < myVertices.vertexTable.size(); i++){
                if(myVertices.vertexTable[i].getName() != ""){
                    verVec.push_back(&myVertices.vertexTable[i]);
                }
            }
            
            int setSize = verVec.size();
            
            // vertex 'u' is vertex which we wish to know the distance of 'v' from.
            set.push_back(myVertices.retrieveFromTable(u));
            
            // set[0] is vector 'u', and therefore has a distance of 0,
            // is automattically the shortest, and has no predecessor.
            set[0]->setDistance(0.0);
            set[0]->setPredecessor(nullptr);
            removeFromVector(set[0], verVec);
            
            // Will step through the set to find the distance from each vertex.
            // Runs for one less than setSize because an element has already been removed from verVec.
            for(int j = 0; j < setSize - 1; j++){
                
                // The number of iterations will reduce by one everytime a vertex is removed from verVec.
                for(int i = 0; i < verVec.size(); i++){
                    
                    double currentDist = verVec[i]->getDistance();
                    
                    double distToNeighbor = distance(set[j]->getName(), verVec[i]->getName());
                    
                    double potentialShortest = set[j]->getDistance() + distToNeighbor;
                    
                    
                    /* If the current distance is -1 (inifinity), the distance is set to distance(set[j], verVec[i]),
                     and the predecessor is changed, as long as this distance is not infinity as well. */
                    if((currentDist == -1) && (distToNeighbor != -1)){
                        
                        verVec[i]->setDistance(potentialShortest);
                        verVec[i]->setPredecessor(set[j]);
                        
                    } else { // The current distance is not inifinity, so it must be checked against a tentative shortest distance.
                        
                        /* If the potential shortest distance (distance to set[j] + distance between set[j] and verVec[i])
                         is shorter than the current distance, and the distance to the neighbor is not -1 (infinity)
                         then the current distance and predecessor are updated.*/
                        if((potentialShortest < currentDist) && (distToNeighbor != -1)) {
                            
                            verVec[i]->setDistance(potentialShortest);
                            verVec[i]->setPredecessor(set[j]);
                            
                        }
                    } // The distance/predecessor has been updated
                    
                    
                } // End of verVec for loop.
                
                nextVertex = minimumDistance(verVec);
                removeFromVector(nextVertex, verVec);
                set.push_back(nextVertex);
                
                
            } // End of set for loop.
        } catch (exception &e){
            throw invalid_argument(e.what());
        }
        
    } // end of Dijkstra's Algorithm
    
    
    Vertex* minimumDistance(vector<Vertex*> &vertices){
        
        // finds the index of the first vertex in the vector whose distance is not infinity.
        int i = 0;
        while((vertices[i]->getDistance() == -1) && (i < vertices.size())){
            i++;
        }
        
        Vertex* minVertex = vertices[i];
        
        // Finds the vertex with the minimum distance, excluding -1.
        for(int t = 0; t < vertices.size(); t++){
            
            if(vertices[t]->getDistance() != -1){
                
                if(vertices[t]->getDistance() < minVertex->getDistance()){
                    minVertex = vertices[t];
                }
                
            }
            
        } // end of min finding for loop.
        
        return minVertex;
        
    }
    
    void removeFromVector(Vertex* thisOne, vector<Vertex*> &vertices){
        
        // Steps through the vector of vertices, and finds the index
        // of the vertex that will be removed.
        for(vector<Vertex*>::iterator i = vertices.begin(); i != vertices.end(); i++){
            if(*i == thisOne){
                vertices.erase(i);
                return;
            }
        }
    
    }
    
};



#endif /* dirGraph_h */
