//#include <iostream>
//#include "cgbe.h"
#include "DataRead.h"
#include "StrongSimulation.h"
#include <fstream>
#include <string> 
#include "cgbe.h"
using namespace std;



int main(int argc, char *argv[]) {
	//used in the DIGraph.h for the random label distribution
	//srand((int)time(0));
	//use the same randomness
	srand(0);

	cout << "\n\n*************************************" << endl;
	cout << "********   Loading Data    **********" << endl;
	cout << "*************************************" << endl;
	string QueryName = argv[1];
	//data_read_with_label.h
	//Read<VertexLabel, EdgeLabel> Query(QueryName);		
	DataRead<VertexLabel, EdgeLabel> Query(QueryName);				
	cout << "Query has been read!\t";
	cout << "|V|: " << Query.graph_ptr->getVcnt() << "\t\t|E|: " << Query.graph_ptr->getEcnt() <<endl;
	//cout<< QueryName << endl;
	string GraphName = argv[2];
	int pos = QueryName.find_last_of('/');
	string temp(QueryName.substr(pos+1));
	replace(temp.begin(), temp.end(), '/', '-');
	string OutFile = "results/" + temp;
	//cout<< OutFile<< endl;

	//data_read.h
	DataRead<VertexLabel, EdgeLabel> Graph(GraphName);
	cout << "Graph has been read!\t";
	cout << "|V|: " << Graph.graph_ptr->getVcnt() << "\t|E|: " << Graph.graph_ptr->getEcnt() <<endl;
	cout << endl;

	string QueryPath = argv[3];
	string Index1 = argv[4];
	string Index2 = argv[5];
	int khop = stoi(argv[6]);
	int pathlength = stoi(argv[7]);
	StrongSimulation<VertexLabel, EdgeLabel> ssim(&Query, &Graph, OutFile, QueryPath, Index1, Index2, khop, pathlength);
	ssim.Match();
	cout << "Service done!" << endl;
	return 0;

}



