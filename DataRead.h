#pragma once
/*
 * data_read_with_label.h
 *
 *  Created on: January 8, 2019
 *      Author: Lyu
 */

#ifndef DATAREAD_H_
#define DATAREAD_H_

#include "DIGraph.h"

//#include <fstream.h>		For VS2017
#include <fstream>
#include <iostream>
#include <string> 
using namespace std;


//#define     DEFAULTMSGSIZE        2048
//#define     DEFAULTRANDOM         32

template<class VLabelType, class ELabelType>
class DataRead {
public:
	// variables
	DIGRAPH<VLabelType, ELabelType> graph;
	DIGRAPH<VLabelType, ELabelType>* graph_ptr;
	void Mapping();
	DataRead(string);
	~DataRead();

	//private:

};



template<class VLabelType, class ELabelType>
DataRead<VLabelType, ELabelType>::DataRead(string FileName) {
	ifstream OpenFile(FileName);
	char str[100];
	string temp;
	int counter = 0;
	VertexID src = 0, dst = 0;
	VLabelType label=0;
	unordered_map<VertexID, VLabelType> VLabels;

	while (!OpenFile.eof()) {

		/*print the title*/
		if (counter < 4 && (OpenFile.getline(str, 100))) { 
			//cout << str << endl;
			counter++;
			continue;
		}
		/*Initial the graph*/
		
		while(OpenFile >> temp){
			if(temp == "#"){
				OpenFile >> temp;
				src = stol(temp);
				OpenFile >> temp;
				label = stol(temp);
				VLabels[src] = label;
				graph.insertVertex(src, 0);
				continue;
			}else{
				dst = stol(temp);
				if(src == dst){
					if (!graph.isEdge(src, dst))				//to make sure the graph is not a multi-directed graph
					graph.insertEdge(src, dst, 0);
				}else{
					graph.insertVertex(dst, 0);
					if (!graph.isEdge(src, dst))				//to make sure the graph is not a multi-directed graph
						graph.insertEdge(src, dst, 0);
				}
			}

		}		
	}

	Mapping();
	/*Set the labels for the vertices*/
	graph.initVertexLabel(VLabels);
	

	this->graph_ptr = &this->graph;
	VLabels.clear();
	OpenFile.close();
}



template<class VLabelType, class ELabelType>
void DataRead<VLabelType, ELabelType>::Mapping() {
	/*initial the mapping from VertexID to the matrix number*/
	graph.initMap();
}




template<class VLabelType, class ELabelType>
DataRead<VLabelType, ELabelType>::~DataRead() {}



#endif 
