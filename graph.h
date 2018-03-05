//
//  graph.h
//  Project4Files
//
//  Created by Chad Cooper on 7/9/17.
//  Copyright © 2017 Chad Cooper. All rights reserved.
//

#ifndef graph_h
#define graph_h


#define INF 0x3f3f3f3f
#include <utility>
#include<functional>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include "vertex.h"
#include "edge.h"
#include "hashTable.h"


typedef pair<double, Vertex*> myPair;

void Dijkstra(string u);

class Graph {
    
private:
    
    //Hash table to store vertices
    HashTable myVertices;
    
public:
    
    
    /*Accessors*/
    
    bool empty(){
        
        for(int i = 0; i < myVertices.vertexTable.size(); i++){
            if(myVertices.vertexTable[i].getName() != ""){
                return false;
            }
        }
        
        return true;
    }
    
    /*Returns the degree of the vertex v. Throw an illegal
     argument exception if the argument does not correspond to an existing vertex.*/
    int degree(string v) {
        
        Vertex temp = *(myVertices.retrieveFromTable(v));
        
        int mDegree = temp.adjVertices.size();
        
        return mDegree;
        
    }
    
    /*Returns the number of edges in the graph*/
    int edgeCount() {
        
        int numEdges = 0;
        
        for (int i = 0; i < myVertices.vertexTable.size(); i++) {
            
            numEdges += myVertices.vertexTable[i].adjVertices.size();
        }
        
        return numEdges / 2;
    }
    
    /*Determines if the graph is connected.*/
    bool isConnected() {
        
        
        int vertexPos = 0;
        
        for (int i = 0; i < myVertices.vertexTable.size(); i++) {
            
            if (myVertices.vertexTable[i].getName() != "") {
                
                vertexPos = i;
                break;
            }
        }
        
        utilityDFS(myVertices.vertexTable[vertexPos].getName());
        
        for (int i = 0; i < myVertices.vertexTable.size(); i++) {
            
            if (myVertices.vertexTable[i].getName() != "") {
                if (myVertices.vertexTable[i].visited == false) {
                    return false;
                }
            }
        }
        
        return true;
        
    }
    
    
    /*Returns the weight of the edge connecting vertices u and v.
     If the vertices are the same, return 0. If the vertices
     are not adjacent, return -1 (our representation of infinity). Throw an illegal
     argument exception if the arguments do not correspond to existing vertices.*/
    double adjacent(string u, string v) {
        
        // If 'u' and 'v' are the same, 0 is returned.
        if (u == v) {
            return 0;
        }
        // findEdgeBetween may throw an exception.
        try {
            
            // The edge between 'u' and 'v' is found.
            Edge* arc = findEdgeBetween(u, v);
            
            if (arc != nullptr) {
                return arc->getWeight();
            }
            else {
                return -1;
            }
            
        }
        // if 'v' or 'u' aren't in the graph, an exception is thrown.
        catch (exception &e) {
            throw underflow_error("The arguments do not correspond to existing vertices.\n");
        }
    }
    
    /*Performs DFS traversal starting on vertex v. Reset ver-
     tices after the traversal. Prints the order of vertices visited.*/
    void DFS(string v) {
        
        //Get start vertex.
        Vertex* temp = myVertices.retrieveFromTable(v);
        
        //If start vertex has not been visited, then mark as visited and print.
        if (temp->visited == false) {
            
          
            cout << temp->getName() << " ";
        
            
            temp->visited = true;
        }
        
        temp->sortEdgesUndir();
        
        //For all vertices adjacent to the start vertex, check if visited.
        for (list<Edge*>::iterator it = temp->adjVertices.begin(); it != temp->adjVertices.end(); it++) {
            
            Vertex* temp1 = myVertices.retrieveFromTable((*it)->getName());
            
            if (temp1->visited == false) {
                
                //Maintain recursion until all vertices have been visited.
                DFS(temp1->getName());
            }
        }
        
    }
    
    /*Performs BFS traversal starting on vertex v. Reset ver-
     tices after the traversal. Prints the order of vertices visited.*/
    void BFS(string v) {
        
        reset();
        
        //Get start vertex.
        Vertex* temp = myVertices.retrieveFromTable(v);
        
        //Create a queue.
        list<Vertex*> queue;
        
        //Mark start vertex as visited.
        temp->visited = true;
        
        //Initialize queue to contain only the start vertex.
        queue.push_back(temp);
        
        while (!queue.empty()) {
            
            Vertex* source;
            
            //Get the vertex at the front of the queue.
            source = queue.front();
            
            //Print visited vertex.
            cout << source->getName() << " ";
            
            //Remove Vertex at the front of the queue.
            queue.pop_front();
            
            source->sortEdgesUndir();
            
            //For all vertices adjacent to the start vertex. If a vertex has not been
            //visited then mark as visited and enqueue it.
            for (list<Edge*>::iterator it = source->adjVertices.begin(); it != source->adjVertices.end(); it++) {
                
                Vertex* temp1 = myVertices.retrieveFromTable((*it)->getName());
                
                if (temp1->visited == false) {
                    
                    temp1->visited = true;
                    
                    queue.push_back(temp1);
                }
                
            }
        }
        reset();
    }
    
    /*Returns the minimum spanning tree using Prim's algorithm of those
     vertices which are connected to vertex v. Throw an illegal argument exception
     if the argument does not correspond to an existing vertex.*/
    void MST(string v) {
        
        int distance = 0;
        
        //Total capacity of vertices
        int count = myVertices.vertexTable.size();
        
        //Get start vertex.
        Vertex* temp = myVertices.retrieveFromTable(v);
        
        //Get the index of the start vertex.
        int stVertIndex = temp->getHashPosition();
        
        //Create a priority queue to used as a min heap.
        priority_queue< myPair, vector <myPair>, greater<myPair> > pq;
        
        //vector of keys that hold the weights.
        vector<double> key(count, INF);
        
        //vector to store the minimum path.
        vector<int> parent(count, -1);
        
        //Initialize priority queue to contain only the starting vertex.
        pq.push(make_pair(0, temp));
        
        //initialize the starting vertex key to 0.
        key[stVertIndex] = 0;
        
        //while the list is not empty.
        while (!pq.empty()) {
            
            Vertex* source;
            
            //Get the vertex with minimum weight from the priority queue.
            source = pq.top().second;
            
            //Get the index of that vertex
            int srcVertex = source->getHashPosition();
            
            //Remove Vertex at the top of the queue.
            pq.pop();
            
            //Mark the vertex as visited.
            source->visited = true;
            
            //Iterate through the edges of source vertex
            for (list<Edge*>::iterator it = source->adjVertices.begin(); it != source->adjVertices.end(); it++) {
                
                //Get vertex name and position, and weight of current adjacent vertex to source.
                Vertex* adjVertex = myVertices.retrieveFromTable((*it)->getName());
                int newVertIndex = adjVertex->getHashPosition();
                
                double currentWeight = adjacent(source->getName(), (*it)->getName());
                
                //If the adjacent vertex is not visited and the current weight is less than the minimum key
                if (adjVertex->visited == false && key[newVertIndex] > currentWeight) {
                    
                    //Update the minimum key to current weight.
                    key[newVertIndex] = currentWeight;
                    
                    //push new weight and vertex to the priority queue.
                    pq.push(make_pair(key[newVertIndex], adjVertex));
                    
                    //Update the minimum path from source to adjacent vertex.
                    parent[newVertIndex] = srcVertex;
                }
            }
            
        }
        
        for (int i = 0; i < myVertices.vertexTable.size(); i++) {
            
            if (myVertices.vertexTable[i].getName() != "" && parent[i] != -1) {
                
                distance += key[i];
                
                int index = parent[i];
                
                cout << myVertices.vertexTable[index].getName() << " " << myVertices.vertexTable[i].getName() << " " << key[i] << endl;
            }
        }
        
        cout << "Distance: " << distance << endl;
        
        /* My MST implementation
        
        // Clears the visited status.
        reset();
        
        vector<Vertex*> set;
        
        Vertex* startingVertex = myVertices.retrieveFromTable(v);
        Vertex* nextVertex;
        
        startingVertex->setVisited(true);
        
        double sumWeights = 0;
        
        Edge* nextMinEdge;
        
        set.push_back(startingVertex);
        
        for(int i = 0; i < 5; i++){
        
            
            nextMinEdge = minimumEdge(set);
            
            set.push_back(nextMinEdge->getTarget());
            
            
            cout << nextMinEdge->getSource()->getName() << " " << nextMinEdge->getTarget()->getName() <<
            " " << nextMinEdge->getWeight() << endl;
        
            sumWeights += nextMinEdge->getWeight();
            
        }
        cout << sumWeights << endl;
        */
        
        /*
        
        //Get start vertex.
        Vertex* temp = myVertices.retrieveFromTable(v);
        
        //Create a list to store vertices.
        list<Vertex*> pq;
        
        //list to store MST
        list<Edge*> pMST;
        
        //Initialize list to contain only the start vertex.
        pq.push_back(temp);
        
        //while the list is not empty.
        while (!pq.empty()) {
            
            Vertex* source;
            
            Vertex* newSource;
            
            //Set minimum weight to INF
            double minWeight = INF;
            
            //Get the vertex at the front of the list.
            source = pq.front();
            
            //Remove Vertex at the front of the list.
            pq.pop_front();
            
            //Mark the vertex as visited.
            source->visited = true;
            
            //Iterate through the edges of source vertex
            for (list<Edge*>::iterator it = source->adjVertices.begin(); it != source->adjVertices.end(); it++) {
                
                //Get vertex name and weight of current adjacent to source.
                Vertex* adjVertex = myVertices.retrieveFromTable((*it)->getName());
                double currentWeight = adjacent(source->getName(), (*it)->getName());
                
                //If the adjacent vertex is not visited and the current weight is less than the minimum
                if (adjVertex->visited == false && minWeight > currentWeight) {
                    
                    //Update the minimum and weight and the vertex which contains the minimum weight.
                    minWeight = currentWeight;
                    newSource = adjVertex;
                    
                }
            }
            
            //push the new vertex to the list
            pq.push_back(newSource);
            
            //Create an edge with the minimum weight and push back to the list cotaining the MST.
            Edge* edgeMST = new Edge(source, newSource, minWeight);
            
            pMST.push_back(edgeMST);
        }
        */
    }
    
    
    Edge* minimumEdge(vector<Vertex*> &set){
        
        Vertex* currentVertex = set[0];
        
        Edge* minimumEdge = currentVertex->adjVertices.front();
        
        // Will step through all vertices in the set, and check
        // each vertex's adjacency list
        for(vector<Vertex*>::iterator vIT = set.begin(); vIT != set.end(); vIT++){
            
            // This for loop goes through the adjacency list of the current vertex.
            for (list<Edge*>::iterator eIT = (*vIT)->adjVertices.begin(); eIT != (*vIT)->adjVertices.end(); eIT++) {
               
                // If the weight is less than the current min edge, and it's target vertex hasn't been visited
                if( (*eIT)->getWeight() < minimumEdge->getWeight() && ( !(*eIT)->getTarget()->getVisited())){
                    
                    minimumEdge = (*eIT);
                }
                
            }
            
            
        }
        
        minimumEdge->getTarget()->setVisited(true);
        
        return minimumEdge;
    }
    
    
    
    
    /*Mutators*/
    
    /*Reads structure from a text le and builds a undirected weighted graph.*/
    void buildGraph() {
        
        string fileName, line, inputVertex, initialVertex, terminalVertex;
        
        double weight;
        
        cout << "Enter the name of the file from which you wish to build the graph.\n";
        
        getline(cin, fileName);
        
        ifstream graphFile;
        
        graphFile.open(fileName);
        
        getline(graphFile, line);
        
        istringstream issVertex(line);
        
        while (getline(issVertex, inputVertex, ' ')) {
            insert(inputVertex);
        }
        
        while (getline(graphFile, line)) {
            
            istringstream issEdge(line);
            
            issEdge >> initialVertex >> terminalVertex >> weight;
            
            insert(initialVertex, terminalVertex, weight);
        }
        
        graphFile.close();
    }
    
    /*Removes all the elements in the undirected weighted graph*/
    void clear() {
        
        myVertices.clearHashTable();
    }
    
    /*Iterates over all vertices in the graph and marks them as unvisited.*/
    void reset() {
        
        for (int i = 0; i < myVertices.vertexTable.size(); i++) {
            myVertices.vertexTable[i].setVisited(false);
        }
    }
    
    
    /*Insert function inserts a vertex*/
    void insert(string n) {
        
        // Checks whether this vertex is already in the table.
        try {
            myVertices.retrieveFromTable(n);
            cout << n + "  is already present in   the graph." << endl;
        }
        // If the vertex is not in the table, then a new one is added.
        catch (exception &e) {
            
            Vertex newVertex(n);
            
            // adds a new vertex with name 'n',
            myVertices.addToTable(newVertex);
        }
    }
    
    /*If the weight w < 0 or w = 1, throw an illegal argument exception.
     If the weight w is 0, remove any edge between u and v (if any).
     Otherwise, add an edge between vertices u and v with weight w.
     If an edge already exists, replace the weight of the edge with the new weight.
     If the vertices do not exist or are equal, throw an illegal argument exception.*/
    void insert(string u, string v, double w) {
        
        // If w is valid, and u & v aren't the same.
        if (w > 0 && u != v) {
            
            // Will throw exception if 'u' or 'v' don't exist.
            try {
                
                double currentWeight = adjacent(u, v);
                
                // If there is already an edge between 'u' and 'v',
                // then it will have a weight that is greater than 0.
                if (currentWeight > 0) {
                    
                    Edge* existingEdge1 = findEdgeBetween(u, v);
                    Edge* existingEdge2 = findEdgeBetween(v, u);
                    
                    existingEdge1->setWeight(w);
                    existingEdge2->setWeight(w);
                }
                // The vertices exist, but there is no edge between them yet.
                // Time to add an edge to these vertices.
                else {
                    // Vertex pointers to the source and target in the hash table
                    
                    Vertex* source = myVertices.retrieveFromTable(u);
                    Vertex* target = myVertices.retrieveFromTable(v);
                    
                    // source 'u' is adjacent to target 'v'
                    source->addEdgeUndir(source, target, w);
                    // target 'v' is adjacent to source 'u'
                    target->addEdgeUndir(target, source, w);
                    
                }
                // 'u' or 'v' don't exist.
            }
            catch (exception &e) {
                throw underflow_error("The arguments do not correspond to existing vertices.\n");
            }
        }
        // If w is 0, and u & v aren't the same.
        else if (w == 0 && u != v) {
            try {
                
                double currentWeight = adjacent(u, v);
                
                // If there is already an edge between 'u' and 'v',
                // then it will have a weight that is greater than 0.
                if (currentWeight > 0) {
                    
                    Vertex* source = myVertices.retrieveFromTable(u);
                    Vertex* target = myVertices.retrieveFromTable(v);
                    
                    Edge* existingEdge1 = findEdgeBetween(u, v);
                    Edge* existingEdge2 = findEdgeBetween(v, u);
                    
                    // source 'u' is adjacent to target 'v'
                    source->removeEdge(existingEdge1);
                    // target 'v' is adjacent to source 'u'
                    target->removeEdge(existingEdge2);
                    
                }
            }
            catch (exception &e) {
                throw underflow_error("The arguments do not correspond to existing vertices.\n");
            }
        }
        // w is invalid, or 'u' and 'v' are the same vertex.
        else {
            
            string reason = ((u == v) ? ("These vertices are the same.") : ("An edge's weight must be greater than 0."));
            
            throw invalid_argument(reason);
        }
    }
    
    
    /*Auxiliary Functions*/
    
    void utilityDFS(string v) {
        
        //Get start vertex.
        Vertex* temp = myVertices.retrieveFromTable(v);
        
        //If start vertex has not been visited, then mark as visited and print.
        if (temp->visited == false) {
            
            temp->visited = true;
        }
        
        temp->sortEdgesUndir();
        
        //For all vertices adjacent to the start vertex, check if visited.
        for (list<Edge*>::iterator it = temp->adjVertices.begin(); it != temp->adjVertices.end(); it++) {
            
            Vertex* temp1 = myVertices.retrieveFromTable((*it)->getName());
            
            if (temp1->visited == false) {
                
                //Maintain recursion until all vertices have been visited.
                utilityDFS(temp1->getName());
            }
        }
        
    }

    
    
    
    Edge* findEdgeBetween(string u, string v) {
        
        try {
            Vertex *sourceU = myVertices.retrieveFromTable(u);
            Vertex *targetV = myVertices.retrieveFromTable(v);
            
            for (list<Edge*>::iterator iter = sourceU->adjVertices.begin(); iter != sourceU->adjVertices.end(); iter++) {
                
                if ((*iter)->getTarget() == targetV) {
                    
                    Edge* edgePtr = (*iter);
                    
                    return edgePtr;
                }
            }
            return nullptr;
        }
        catch (exception &e) {
            // If 'u' or 'v' aren't in the graph, then an invalid argument exception is thrown.
            throw underflow_error("The arguments do not correspond to existing vertices.\n");
        }
    }
    
    void printEdges() {
        
        for (int i = 0; i < myVertices.vertexTable.size(); i++) {
            
            if (myVertices.vertexTable[i].getName() != "") {
                cout << myVertices.vertexTable[i].getName() << ": ";
                
                for (list<Edge*>::const_iterator it = myVertices.vertexTable[i].adjVertices.begin();
                     it != myVertices.vertexTable[i].adjVertices.end(); it++) {
                    cout << (*it)->getName() << " ";
                }
                cout << endl;
            }
        }
    }
    
    
    void printVertices() {
        for (int i = 0; i < myVertices.vertexTable.size(); i++) {
            
            if (myVertices.vertexTable[i].getName() != "") {
                cout << myVertices.vertexTable[i] << endl;
            }
        }
    }
    
};

#endif /* graph_h */
