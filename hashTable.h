//
//  hashTable.h
//  Project4Files
//
//  Created by Chad Cooper on 7/1/17.
//  Copyright © 2017 Chad Cooper. All rights reserved.
//

#ifndef hashTable_h
#define hashTable_h

#include "vertex.h"
#include <array>

class HashTable {
    
private:
    
    
    array<Vertex, 19> vertexTable;
    
    int size;
    
    Vertex nullVertex;
    
    
public:
    
    // Default constructor is used.
    
//    HashTable(){
//        //vertexTable.fill(nullVertex);
//    }
    
    void addToTable(Vertex& vertex){
        
        int tablePosition = hash(vertex.getName());
        int actualPosition = 0;
        
        
        for(int i = 0; i < vertexTable.size(); i++){
            
            // if the entry at the relative table position has an empty name,
            // then the vertex is inserted at this table position.
            if( vertexTable[(tablePosition + i) % 19].getName()  == ""){
                
                actualPosition = (tablePosition + i) % 19;
                vertex.setHashPosition(actualPosition);
            
                vertexTable[actualPosition] = vertex;
                
                size++;
                
                return;
            }
            
        }
     
    }
    
    
    
    int hash(string vertextKey){
        int keySum = 0;
        
        for(int i = 0; i < vertextKey.length(); i++){
            keySum += vertextKey[i];
        }
        return keySum;
        
    }

    Vertex* retrieveFromTable(string key) throw(invalid_argument){
        int position = hash(key);
        
        for(int i = 0; i < vertexTable.size(); i++){
            
            // checks whether the name of the vertex at the hash position is
            // the correct vertex, according to the key.
            // If not, then it checks the next position, etc.
            if(vertexTable[(position + i) % 19].getName() == key){
                // returns the address of the vertex at this position.
                return &(vertexTable[(position + i)%19]);
            }
        }
     
        throw invalid_argument("A vertex with name \"" + key + "\" is not present.");
    }
    
    int getSize() const{
        return size;
    }
    
    
    void clearHashTable() {
        vertexTable.fill(nullVertex);
    }
    
    
    Vertex* getVertexAtPosition(int position){
        return &(vertexTable[position]);
    }
    
    // This is now useless, because DirGraph is a friend.
    void displayTable(){
        for(int i = 0; i < 19; i++){
            if(vertexTable[i].getName() != ""){
                cout << vertexTable[i] << endl;
            }
        }
    }
    
    friend class DirGraph;
    friend class Graph;
    
};


#endif /* hashTable_h */
