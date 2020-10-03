#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <vector>
#include<stdlib.h>
#include <unordered_map>
using namespace std;

//#define	GRAPH_LABEL_NUMBER	40

int main(int argc, char *argv[]) {
	//used in the DIGraph.h for the random label distribution
	//srand((int)time(0));
	//use the same randomness
	string tempsize = argv[2];
	int GRAPH_LABEL_NUMBER = stoi(tempsize);
	srand(0);
    typedef unordered_map<int, int> destination;
    typedef unordered_map<int, destination> Data;

    Data data;
	ifstream OpenFile(argv[1]);
	string tempname = argv[1];
	//string OutFileName = tempname + ".txt";
	int pos = tempname.find_last_of('.');
	string OutFileName(tempname.substr(0, pos));
	string OutFileNameWithLabel = OutFileName + tempsize;
    ofstream OutFile(OutFileNameWithLabel);
	int temp = -1;
	int label = -1;

	char str[100];
	int counter = 0;
	string str2;
	int src = 0, dst = 0;
	int line = 0;
    int edge = 0;
	cout << endl;
	while (!OpenFile.eof()) {
		/*print the title*/
		if(counter < 3 && (OpenFile.getline(str, 100))) {
			//cout<<"hello!"<<endl;
			string temp = str;
			cout << str <<endl;		
			OutFile << temp << "\n"; //fxxk, getline only get the content with string + "\r", but getline decides a line with "\r\n" 
			counter++;							
			continue;
		}
		if((counter == 3) && (OpenFile.getline(str, 100))){
			OutFile << "# FromNodeId\t" << "Label\t" << "ToNodeId";
			cout << str <<endl;	
			counter++;
		}


		OpenFile.getline(str, 100);
		line++;
		string str1, str2;
		str1 = str;
		stringstream ss(str1);
		if (ss >> str2)
			src = stoi(str2);

        if (ss >> str2)
			dst = stoi(str2);

        data[src][dst] = 1;
    }
    OpenFile.close();

    for(auto it = data.begin(); it != data.end(); it++){
		src = it->first;
		label = (rand()% GRAPH_LABEL_NUMBER);
		OutFile << "\n#\t" << src << "\t" << label;
        for(auto it1 = data[src].begin(); it1 != data[src].end(); it1++){
            dst = it1->first;
            OutFile << "\t" << dst;
            edge++;
        }
    }	
	cout<< "The number of edges for transformed graph: " << edge <<endl;		
	OutFile.close();
	return 0;
}



