//#include <iostream>
//#include "cgbe.h"
#include "DataRead.h"
#include "DIGraph.h"
#include "PathGenerator.h"
#include <fstream>
#include <string> 

using namespace std;


int main(int argc, char *argv[]) {
	//used in the DIGraph.h for the random label distribution
	//srand((int)time(0));
	//use the same randomness
	srand(10);

	
	string GraphName = argv[1];	
	DataRead<VertexLabel, EdgeLabel> Graph(GraphName);
	cout << "|V|: " << Graph.graph_ptr->getVcnt() << "\t\t|E|: " << Graph.graph_ptr->getEcnt() <<endl;
	cout << "Graph has been read!\n" << endl;

	//Path Generator
	int pathlength = stoi(argv[2]);
	int pathnum = stoi(argv[3]);
	string No = argv[4];
	string labelsize = argv[5];
	cout << " pathlength = " << pathlength << "pathnum = " << pathnum << "Num = " << No << " labelsize = " << labelsize <<endl;
	PathGenerator<VertexLabel, EdgeLabel> QueryGen(&Graph, GraphName, pathlength, pathnum, No, labelsize); //3 for the diameter of the origin subgraph for generation
	cout << "Query Generator done!" << endl;
	return 0;

}



