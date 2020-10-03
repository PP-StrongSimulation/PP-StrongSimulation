//#include <iostream>
//#include "cgbe.h"
#include "DataRead.h"
#include "GraphIndex.h"
#include <fstream>
#include <string> 
#include "DIGraph.h"

using namespace std;


int main(int argc, char *argv[]) {
	//used in the DIGraph.h for the random label distribution
	//srand((int)time(0));
	//use the same randomness
	srand(13);

	
	string GraphName = argv[1];	
	DataRead<VertexLabel, EdgeLabel> Graph(GraphName);
	cout << "|V|: " << Graph.graph_ptr->getVcnt() << "\t\t|E|: " << Graph.graph_ptr->getEcnt() <<endl;
	cout << "Graph has been read!\n" << endl;

	//Graph Index
	int hop = stoi(argv[2]);
	string labelname = argv[3];
	GraphIndex<VertexLabel, EdgeLabel> GraphIndex(&Graph, GraphName, hop, labelname);
	cout << "Graph Index done!" << endl;
	return 0;

}



