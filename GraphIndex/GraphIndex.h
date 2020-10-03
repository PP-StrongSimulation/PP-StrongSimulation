#pragma once

#ifndef GRAPHINDEX_H_
#define GRAPHINDEX_H_

#include <iostream>
#include "DIGraph.h"
#include "DataRead.h"
#include <time.h>
#include <string.h>

using namespace std;


template <class VLabelType, class ELabelType>
class GraphIndex
{
public:
    DIGRAPH<VLabelType, ELabelType>* graph_ptr;
    typedef unordered_map<VertexID, VLabelType> VLabels;
    
    //For NL
	typedef unordered_map<VLabelType, int> LABEL;
	typedef unordered_map<VertexID, LABEL> Index;
	typedef unordered_map<int, Index> B_Index; //<hop, Vertex, Label, 1=exists>

	GraphIndex(DataRead<VLabelType, ELabelType> *, string, int, string);
    void ConstructNLIndex(B_Index &, B_Index &, DIGRAPH<VLabelType, ELabelType> *,VertexID, VertexID, int);
	void ConstructIndex(B_Index &, B_Index &, DIGRAPH<VLabelType, ELabelType> *, int);
	void Output(B_Index &, ofstream &);
	~GraphIndex();
};

template <class VLabelType, class ELabelType>
GraphIndex<VLabelType, ELabelType>::GraphIndex(DataRead<VLabelType, ELabelType> *Graph, string GraphName, int khop, string labelsize)
{   
	clock_t startTime, endTime;
	startTime = clock();
    this->graph_ptr = Graph->graph_ptr;   
	string S = "graph/slashdot" + labelsize;
    string D = "graph/dblp-un" + labelsize;
    string T = "graph/twitter" + labelsize;
	string tempName;
    if(GraphName == S)
        tempName = "graph/S";
	if(GraphName == D)
        tempName = "graph/D";
	if(GraphName == T)
        tempName = "graph/T";
    string OutFileName1 = tempName + "-Index1"+"-"+labelsize;
	string OutFileName2 = tempName + "-Index2"+"-"+labelsize;
	cout << OutFileName1 << "	" << OutFileName2 <<endl;

    /*Construct the indices for ball B */
	B_Index Graph_Index, Graph_Index_Reverse;    
    //ConstructNLIndex(Graph_Index, Graph_Index_Reverse, Graph->graph_ptr, -1, -1, -1);
	ConstructIndex(Graph_Index, Graph_Index_Reverse, Graph->graph_ptr, khop);

    //Out File
    ofstream OutFile1(OutFileName1);
    OutFile1 << "$ hop # vertexID Label" << ".txt\r\n";
	Output(Graph_Index, OutFile1);
	OutFile1.close();

	ofstream OutFile2(OutFileName2);
	OutFile2 << "$ hop # vertexID Label" << ".txt\r\n";	
	Output(Graph_Index_Reverse, OutFile2);    
	OutFile2.close();

    Graph_Index.clear();
    Graph_Index_Reverse.clear();
	endTime = clock();
	cout << "The Index needs " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "seconds!" <<endl;
}

template <class VLabelType, class ELabelType>
GraphIndex<VLabelType, ELabelType>::~GraphIndex(){}

template <class VLabelType, class ELabelType>
void GraphIndex<VLabelType, ELabelType>:: ConstructNLIndex(B_Index &Graph_Index, B_Index &Graph_Index_Reverse, DIGRAPH<VLabelType, ELabelType>* Graph, VertexID origin, VertexID place, int hop){
	if (hop == K_HOP)
		return;

	if(hop == -1){
		clock_t startTime, endTime;		
		for (auto it1 = Graph->getVLabel().begin(); it1 != Graph->getVLabel().end(); it1++){
			//cout << "Now is computing the vertex "<< it1->first<<endl;
			startTime = clock();
			for(auto it2 = Graph->getOutEdge()[it1->first].begin(); it2 != Graph->getOutEdge()[it1->first].end(); it2++){
				if (Graph_Index[0][it1->first].find(Graph->getVLabel(it2->first)) == Graph_Index[0][it1->first].end())
				{
					Graph_Index[0][it1->first][Graph->getVLabel(it2->first)] = 1;
				}

				if (Graph_Index_Reverse[0][it2->first].find(Graph->getVLabel(it1->first)) == Graph_Index_Reverse[0][it2->first].end())
				{
					Graph_Index_Reverse[0][it2->first][Graph->getVLabel(it1->first)] = 1; //both parent and children
				}
				ConstructNLIndex(Graph_Index, Graph_Index_Reverse, Graph, it1->first, it2->first, 1);
			}
			endTime = clock();
			if((double)(endTime - startTime) / CLOCKS_PER_SEC > 1)
				cout << "The computing of vertex "<< it1->first << " needs " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl;

		}
	}else{
		for (auto it = Graph->getOutEdge()[place].begin(); it != Graph->getOutEdge()[place].end(); it++){
			if (Graph_Index[hop][origin].find(Graph->getVLabel(it->first)) == Graph_Index[hop][origin].end())
			{
				Graph_Index[hop][origin][Graph->getVLabel(it->first)] = 1;
			}

			if (Graph_Index_Reverse[hop][it->first].find(Graph->getVLabel(origin)) == Graph_Index_Reverse[hop][it->first].end())
			{
				Graph_Index_Reverse[hop][it->first][Graph->getVLabel(origin)] = 1; //both parent and children
			}
			ConstructNLIndex(Graph_Index, Graph_Index_Reverse, Graph, origin, it->first, hop+1);
		}
	}
}


template <class VLabelType, class ELabelType>
void GraphIndex<VLabelType, ELabelType>:: ConstructIndex(B_Index &Graph_Index, B_Index &Graph_Index_Reverse, DIGRAPH<VLabelType, ELabelType>* Graph, int HOP){
	clock_t startTime, endTime;		
	for (int hop = 0; hop < HOP; hop++){
		if(hop == 0){			
			for (auto it1 = Graph->getVLabel().begin(); it1 != Graph->getVLabel().end(); it1++){
				//cout << "Now is computing the vertex "<< it1->first<<endl;
				startTime = clock();
				for(auto it2 = Graph->getOutEdge()[it1->first].begin(); it2 != Graph->getOutEdge()[it1->first].end(); it2++){
					Graph_Index[0][it1->first][Graph->getVLabel(it2->first)] = 1;
					Graph_Index_Reverse[0][it2->first][Graph->getVLabel(it1->first)] = 1; //both parent and children			
				}
				endTime = clock();
				if((double)(endTime - startTime) / CLOCKS_PER_SEC > 1)
					cout << "The computing of vertex "<< it1->first << " needs " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl;
			}
			cout << "The hop " << hop+1 << " is completed!" << endl; 
		}else{
			for (auto it1 = Graph->getVLabel().begin(); it1 != Graph->getVLabel().end(); it1++){
				//cout << "Now is computing the vertex "<< it1->first<<endl;
				startTime = clock();
				for(auto it2 = Graph->getOutEdge()[it1->first].begin(); it2 != Graph->getOutEdge()[it1->first].end(); it2++){
					for(auto it3 = Graph_Index[hop-1][it2->first].begin(); it3 != Graph_Index[hop-1][it2->first].end(); it3++){
						Graph_Index[hop][it1->first][it3->first] = 1;
					}

					for(auto it4 = Graph_Index_Reverse[hop-1][it1->first].begin(); it4 != Graph_Index_Reverse[hop-1][it1->first].end(); it4++){
						Graph_Index_Reverse[hop][it2->first][it4->first] = 1;
					}								
				}
				endTime = clock();
				if((double)(endTime - startTime) / CLOCKS_PER_SEC > 1)
					cout << "The computing of vertex "<< it1->first << " needs " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl;
			}	
			cout << "The hop " << hop+1 << " is completed!" << endl; 		
		}
	}
}



template <class VLabelType, class ELabelType>
void GraphIndex<VLabelType, ELabelType>::Output(B_Index &Index, ofstream &OutFile){
	for (auto it = Index.begin(); it != Index.end();it++){
		OutFile << "$" <<"	"<<it->first<< "\r\n";
		for (auto it1 = Index[it->first].begin(); it1 != Index[it->first].end(); it1++){
			OutFile << "#" << "	"<< it1->first;
			for (auto it2 = Index[it->first][it1->first].begin(); it2 != Index[it->first][it1->first].end(); it2++){
				OutFile << "	" << it2->first;
			}
			OutFile << "\r\n";
		}
		//OutFile <<"\r\n";
	}
}


#endif