//
//  main.cpp
//  Project4Files
//
//  Created by Chad Cooper on 7/1/17.
//  Copyright © 2017 Chad Cooper. All rights reserved.
//

#include <iostream>
#include <string>
#include <ctime>
#include "graph.h"
#include "vertex.h"
#include "edge.h"
#include "dirGraph.h"
#include "graph.h"
#include "hashTable.h"

using namespace std;

int main() {

    
    int code;
    char letter;
    clock_t start, stop;
    
    
    cout << "Enter 'd' for a directed graph or 'u' for an undirected graph: ";
    cin >> letter;
    cout << endl;
    
    switch (letter) {
            
            
        case 'd':
        {
            cin.ignore();
            
            DirGraph myGraph;
            
            myGraph.buildGraph();

            
            cout << "\n1. Empty?\n"
            "2. InDegree (v)\n"
            "3. OutDegree (v)\n"
            "4. Edge count\n"
            "5. Adjacent (u, v)?\n"
            "6. DFS (v)\n"
            "7. BFS (v)\n"
            "8. Print Short path (v)\n"
            "9. Clear\n"
            "10. Insert (u, v, w)\n"
            "11. Exit\n\n";
            
            
            
            
            
            for (;;) {
                
                cout << "Enter operation code: ";
                cin >> code;
                cout << endl;
                
                
                switch (code) {
                        
                    case 1: // empty?
                    {
                        start = clock();
                        cout << "The graph is " << (myGraph.empty()?"":"not ") << "empty";
                        stop = clock();
                        break;
                    }
                    case 2: // in degree
                    {
                        string vertex;
                        cout << "Enter the vertex for which you wish to know the in-degree: ";
                        
                        cin.ignore();
                        getline(cin, vertex);
                        
                        try {
                            
                            start = clock();
                            myGraph.inDegree(vertex);
                            stop = clock();
                            
                            cout << "The in-degree of " << vertex << " is: " << myGraph.inDegree(vertex) << endl;
                            
                        }
                        catch (exception &e) {
                            stop = clock();
                            cout << e.what();
                        }

                        
                        break;
                    }
                    case 3: // out degree
                    {
                        
                        string vertex;
                        cout << "Enter the vertex for which you wish to know the out-degree: ";
                        
                        cin.ignore();
                        getline(cin, vertex);
                        
                        try {
                            
                            start = clock();
                            myGraph.outDegree(vertex);
                            stop = clock();
                            
                            cout << "The out-degree of " << vertex << " is: " << myGraph.outDegree(vertex) << endl;
                            
                        }
                        catch (exception &e) {
                            stop = clock();
                            cout << e.what();
                        }

                        break;
                    }
                    case 4: // edge count
                    {
                        start = clock();
                        cout << "There are " << myGraph.edgeCount() << " edges in your graph." << endl;
                        stop = clock();
                        
                        break;
                    }
                    case 5: // adjacent?
                    {
                        string vertex1, vertex2;
                        double weight;
                        
                        cout << "Enter the initial vertex: ";
                        cin.ignore();
                        getline(cin, vertex1);
                        
                        cout << "Enter the terminal vertex: ";
                        getline(cin, vertex2);
                        
                        try{
                            start = clock();
                            weight = myGraph.adjacent(vertex1, vertex2);
                            stop = clock();
                            
                            if(weight == 0){
                                cout << "These are the same vertex.\n";
                            } else if(weight == -1){
                                cout << "These vertices are not adjacent.\n";
                            } else {
                                cout << "These vertices are connected, and the weight of the edge between them is: "
                                << weight << endl;
                            }
                            
                            
                        } catch (exception &e) {
                            stop = clock();
                            cout << e.what();
                        }

                        break;
                    }
                    case 6: // DFS
                    {
                        string vertex;
                        
                        cout << "Enter the starting vertex: ";
                        cin.ignore();
                        getline(cin, vertex);
                        
                         cout << "Visiting vertices via DFS...\n";
                        
                        myGraph.reset();
                        
                        start = clock();
                        myGraph.DFS(vertex);
                        stop = clock();
                        
                        myGraph.reset();
                        break;
                    }
                    case 7: // BFS
                    {
                        string vertex;
                        
                        cout << "Enter the starting vertex: ";
                        cin.ignore();
                        getline(cin, vertex);
                        
                        cout << "Visiting vertices via BFS...\n";
                        
                        myGraph.reset();
                        
                        start = clock();
                        myGraph.DFS(vertex);
                        stop = clock();
                        
                        myGraph.reset();
                        break;
                    }
                    case 8: // print short path
                    {
                        string vertex;
                        
                        cout << "Enter the starting vertex: ";
                        cin.ignore();
                        getline(cin, vertex);
                        
                        cout << "Printing the shortest path from " + vertex + " to all other vertices...\n";
                        
                        myGraph.reset();
                        
                        try {
                            start = clock();
                            myGraph.shortestToAll(vertex);
                            stop = clock();
                            
                            myGraph.reset();
                        } catch (exception &e){
                            stop = clock();
                            cout << e.what();
                        }

                        break;
                    }
                    case 9: // clear
                    {
                        start = clock();
                        myGraph.clear();
                        stop = clock();
                        
                        cout << "The graph was cleared.\n";
                        
                        break;
                    }
                    case 10: // insert
                    {
                        string vertex1, vertex2;
                        double weight;
                        
                        cout << "Enter the initial vertex: ";
                        cin.ignore();
                        getline(cin, vertex1);
                        
                        cout << "Enter the terminal vertex: ";
                        getline(cin, vertex2);
                        
                        cout << "Enter the weight: ";
                        cin >> weight;
                        
                        try{
                            start = clock();
                            myGraph.insert(vertex1, vertex2, weight);
                            stop = clock();
                            
                            cout << "The edge was inserted.\n";
                            
                        } catch (exception &e) {
                            stop = clock();
                            
                            cout << "The edge was not inserted.\n";
                            cout << e.what();
                        }

                        
                        break;
                    }
                    case 11: // exit
                    {
                        cout << "Exit succesful." << endl;
                        return 0;
                    }
                    default:
                    {
                        cout << "Invalid code." << endl;
                    }
                } // end of code-switch statement
                
                 cout << "\nTime: " << (stop - start)/double(CLOCKS_PER_SEC)*1000 << " ms.\n";
                cout << endl;
                
            } // end of for(;;) statement
            break;
        } // end of general tree
            
        case 'u':
        {
            
            cin.ignore();
            
            Graph myGraph;
            
            myGraph.buildGraph();
            
            cout << "1. Empty?\n"
            "2. Return Degree\n"
            "3. Edge Count\n"
            "4. Connected?\n"
            "5. Adjacent\n"
            "6. Return DFS\n"
            "7. Return BFS\n"
            "8. Print MST\n"
            "9. Clear\n"
            "10. Insert\n"
            "11. Exit\n";
            
            for (;;) {
                
                cout << "Enter operation code: ";
                cin >> code;
                
                switch (code) {
                        
                    case 1:
                    {
                        start = clock();
                        cout << "Is graph empty? true = 1, false = 0: " << myGraph.empty() << endl;
                        stop = clock();
                        
                        break;
                    }
                    case 2:
                    {
                        string data;
                        cout << "Enter the vertex for which you wish to know the degree: ";
                        
                        cin.ignore();
                        getline(cin, data);
                        
                        try {
                            
                            myGraph.degree(data);
                            
                            start = clock();
                            cout << "The degree of " << data << " is: " << myGraph.degree(data) << endl;
                            stop = clock();
                        }
                        catch (exception &e) {
                            stop = clock();
                            cout << e.what();
                        }
                        break;
                    }
                    case 3:
                    {
                        start = clock();
                        cout << "Total number of edges: " << myGraph.edgeCount() << endl;
                        stop = clock();
                        
                        break;
                    }
                    case 4:
                    {
                        start = clock();
                        
                        if (myGraph.isConnected()) {
                            cout << "The Graph is Connected" << endl;
                        }
                        else {
                            cout << "The Graph is not Connected" << endl;
                        }
                        
                        myGraph.reset();
                        
                        stop = clock();
                        
                        break;
                    }
                    case 5:
                    {
                        string u, v;
                        
                        cout << "Enter the starting vertex: ";
                        
                        cin.ignore();
                        getline(cin, u);
                        
                        cout << "Enter the terminal vertex: ";
                        getline(cin, v);
                        
                        try {
                            
                            start = clock();
                            cout << "The weight of " << u << " and " << v << " is: " << myGraph.adjacent(u, v) << endl;
                            stop = clock();
                        }
                        catch (exception &e) {
                            stop = clock();
                            cout << e.what();
                        }
                        break;
                    }
                    case 6:
                    {
                        string ch;
                        cout << "Enter the starting vertex to run DFS: ";
                        
                        cin.ignore();
                        getline(cin, ch);
                        
                        try {
                            
                            start = clock();
                            cout << "DFS traversal: ";
                            myGraph.DFS(ch);
                            myGraph.reset();
                            cout << endl;
                            stop = clock();
                        }
                        catch (exception &e) {
                            stop = clock();
                            cout << e.what();
                        }
                        break;
                    }
                    case 7:
                    {
                        string ch1;
                        cout << "Enter the starting vertex to run BFS: ";
                        
                        cin.ignore();
                        getline(cin, ch1);
                        
                        try {
                            
                            start = clock();
                            cout << "BFS Traversal: ";
                            myGraph.BFS(ch1);
                            myGraph.reset();
                            cout << endl;
                            stop = clock();
                        }
                        catch (exception &e) {
                            stop = clock();
                            cout << e.what();
                        }
                        break;
                    }
                    case 8:
                    {
                        string ch2;
                        cout << "Enter the starting vertex to run MST: ";
                        
                        cin.ignore();
                        getline(cin, ch2);
                        
                        try {
                            
                            start = clock();
                            
                            myGraph.MST(ch2);
                            myGraph.reset();
                            stop = clock();
                        }
                        catch (exception &e) {
                            stop = clock();
                            cout << e.what();
                        }
                        break;
                    }
                    case 9:
                    {
                        start = clock();
                        myGraph.clear();
                        stop = clock();
                        
                        cout << "Clear Succesful.\n";
                        break;
                    }
                    case 10:
                    {
                        string u1, v1;
                        
                        double w;
                        
                        cout << "Enter the starting vertex: ";
                        
                        cin.ignore();
                        getline(cin, u1);
                        
                        cout << "Enter the terminal vertex: ";
                        getline(cin, v1);
                        
                        cout << "Enter the weight between the edge: ";
                        cin >> w;
                        
                        try {
                            
                            start = clock();
                            myGraph.insert(u1, v1, w);
                            stop = clock();
                        }
                        catch (exception &e) {
                            stop = clock();
                            cout << e.what();
                        }
                        
                        break;
                    }
                    case 11:
                    {
                        cout << "Exit succesful." << endl;
                        return 0;
                    }
                    default:
                    {
                        cout << "Invalid code." << endl;
                    }
                        
                } // end of code switch
                
                cout << "\nTime: " << (stop - start) / double(CLOCKS_PER_SEC) * 1000 << " ms.\n";
                
                cout << endl;
            }// end of for(;;)
        
            break;
        } // end undirected;
            
        default:
            cout << "Invalid code." << endl;
            
    } // end of tree selection switch
    
    return 0;


};
