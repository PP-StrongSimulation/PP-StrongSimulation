#pragma once
/*
 * graph_read.h
 *
 *  Created on: January 8, 2019
 *      Author: Lyu
 */

#ifndef DATA_READ_H_
#define DATA_READ_H_

#include "DIGraph.h"

//#include <fstream.h>		For VS2017
#include <fstream>
#include <iostream>
#include <string> 
using namespace std;


//#define     DEFAULTMSGSIZE        2048
//#define     DEFAULTRANDOM         32

template<class VLabelType, class ELabelType>
class Read {
public:
	// variables
	DIGRAPH<VLabelType, ELabelType> graph;
	DIGRAPH<VLabelType, ELabelType>* graph_ptr;
	void Mapping();
	Read(string);
	~Read();

	

//private:
	
};



template<class VLabelType, class ELabelType>
Read<VLabelType, ELabelType>::Read(string FileName){
	ifstream OpenFile(FileName);
	char str1[100];
	int counter = 0;
	string str2;
	VertexID src = 0, dst = 0;
	while (!OpenFile.eof()) {

		/*print the title*/
		if(counter < 4 && (OpenFile.getline(str1, 100))) {
			cout << str1 <<endl;
			counter++;							
			continue;
		}


		OpenFile >> str2;
		if (OpenFile.eof())
			break;
		while(str2[0] == '\r'|| str2[0] == '\n') {
			OpenFile >> str2;
			if (OpenFile.eof())
				break;
		}

		if (OpenFile.eof())
			break;


		src = stol(str2);
		OpenFile >> str2;
		if (str2[0] == '\r' || str2[0] == '\n')
			break;
		dst = stol(str2);
		//cout << src << "	" << dst << endl;

		/*Initial the graph*/
		graph.insertVertex(src, 0);
		graph.insertVertex(dst, 0);
		if(!graph.isEdge(src,dst))				//to make sure the graph is not a multi-directed graph
			graph.insertEdge(src, dst, 0);
	}

	/*Set the labels for the vertices*/
	
	//graph.initVL();				//Label equals to degree
	// Or
	graph.initVL_Random();			//Label equals to randomness
	Mapping();

	this->graph_ptr = &this->graph;
	OpenFile.close();	
}



template<class VLabelType, class ELabelType>
void Read<VLabelType, ELabelType>::Mapping() {
	/*initial the mapping from VertexID to the matrix number*/
	graph.initMap();
}




template<class VLabelType, class ELabelType>
Read<VLabelType, ELabelType>::~Read() {}



#endif 
