#pragma once

#ifndef QUERYGENERATOR_H_
#define QUERYGENERATOR_H_

#include <iostream>
#include "DIGraph.h"
#include "DataRead.h"
#include <time.h>
#include <string.h>

using namespace std;


template <class VLabelType, class ELabelType>
class QueryGenerator
{
public:
    DIGRAPH<VLabelType, ELabelType>* graph_ptr;
    typedef unordered_map<VertexID, VLabelType> VLabels;
	QueryGenerator(DataRead<VLabelType, ELabelType> *, string, int, int, int, string);
	~QueryGenerator();
};

template <class VLabelType, class ELabelType>
QueryGenerator<VLabelType, ELabelType>::QueryGenerator(DataRead<VLabelType, ELabelType> *Graph, string GraphName, int QueryNum, int Diameter, int dia, string labelsize)
{   
    //int size[10] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    this->graph_ptr = Graph->graph_ptr;   
    VertexID root, vertex;
    int MaxNum, Number;
    string OutFileName;
    string QueryName;
    string S = "graph/slashdot" + labelsize;
    string D = "graph/dblp-un" + labelsize;
    string T = "graph/twitter" + labelsize;
    if(GraphName == S)
        QueryName = "Query-Slashdot/S";
    if(GraphName == D)
        QueryName = "Query-DBLP/D";
    if(GraphName == T)
        QueryName = "Query-Twitter/T";
    DIGRAPH<VLabelType, ELabelType>* query;
   
    int Count=0;
    while(Count < QueryNum){        
        
        root = this->graph_ptr->QGENgetRandomRoot();

            
        unordered_set<VertexID> s_neighbor;
        this->graph_ptr->getDNeighbor(root, Diameter, s_neighbor, this->graph_ptr);
        query = new DIGRAPH<VLabelType, ELabelType>;
        //cout<<s_neighbor.size()<<endl;
        Number = 0;
        for (auto it = s_neighbor.begin(); it != s_neighbor.end(); it++){
            //if(Number == size[i])

        ////////////////////////
        ////////////////////////
        /*Number is to control the vertices number of query*/
        ////////////////////////
        ////////////////////////
            if (Number == 10) 
                 break;
            if(rand()%6 != 0){ //randomly insert vertex  (for density)
                query->insertVertex(*it, this->graph_ptr->getVLabel(*it));
                if(!(query->isLabel(this->graph_ptr->getVLabel(*it))))
                    query->VLabelSet.insert(this->graph_ptr->getVLabel(*it));
                Number++;
            }
        }

        query->QGENInsertEdge(this->graph_ptr);

        
        //Maximum Connected Component
        VertexID place = query->QGENMaximumConnectComponent(Diameter, query);
        
        
        unordered_set<VertexID> S_N;
        query->getDNeighbor(place, Diameter, S_N, query);
        //int count = 0;

        //Obtain the corresponding graph
        unordered_map<VertexID, VLabelType> mark;

        for (auto it = query->getVLabel().begin(); it != query->getVLabel().end(); it++){
            vertex = it->first;            
            if(S_N.find(vertex) == S_N.end()){
                mark[vertex] = 0;                 
                //count++;
            }
        }         
        //cout<<"There are "<< count <<" vertices removed!"<<endl;
        query->QGENRemove(mark);

        
        
        query->getDiameter();

        if(query->diameter != dia || ((double) query->getEcnt()< query->getVcnt()*(query->getVcnt()-1)/6)||(query->getVcnt()!= (8))){ //for density     /////here 9 for the largest V_Q
            S_N.clear();  
            s_neighbor.clear();        
            query->~DIGRAPH(); 
            continue;
        }else{
            Count++;
            cout<<"root: "<<root<<endl;
            cout<<"place: "<<place<<endl;
            cout << "edge: " << query->getEcnt() << endl;
            cout << "vertex: "<< query->getVcnt() << endl;
            cout<<S_N.size()<<endl;
        }

        //Out File
        OutFileName = QueryName + to_string(Count) + "-" + labelsize;
        ofstream OutFile(OutFileName);
        OutFile << "# Undirected graph: ../../data/output/QueryGen-"<<Count<<".txt\r\n";
        OutFile << "# QUERY with Diameter " << query->diameter << "\r\n";
        OutFile << "# Nodes: "<< query->getVcnt() <<" Edges: "<< query->getEcnt() <<"\r\n";
        OutFile << "# FromNodeId\tLabel\tToNodeId";

        query->QGENOutFile(&OutFile);        

        OutFile.close();
        
        S_N.clear();  
        s_neighbor.clear();        
        query->~DIGRAPH(); 
        //delete query;
    
    }
}

template <class VLabelType, class ELabelType>
QueryGenerator<VLabelType, ELabelType>::~QueryGenerator(){}

#endif