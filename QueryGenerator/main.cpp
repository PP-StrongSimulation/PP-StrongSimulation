//#include <iostream>
//#include "cgbe.h"
#include "DataRead.h"
#include "DIGraph.h"
#include "QueryGenerator.h"
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

	//Query Generator
	int dia = stoi(argv[2]);
	int queryNum = stoi(argv[3]);
	string labelsize = argv[4];
	QueryGenerator<VertexLabel, EdgeLabel> QueryGen(&Graph, GraphName, queryNum, 3, dia, labelsize); //3 for the diameter of the origin subgraph for generation
	cout << "Query Generator done!" << endl;
	return 0;

}



