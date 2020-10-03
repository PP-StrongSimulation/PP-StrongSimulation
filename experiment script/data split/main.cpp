#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <vector>
#include<stdlib.h>
#include <unordered_map>
#include<math.h>
using namespace std;

//#define	GRAPH_LABEL_NUMBER	40

int main(int argc, char *argv[]) {
	string filename = argv[1];
	char str[100];
	int count = 0;
	ifstream OpenFile1(filename);	
	while (!OpenFile1.eof()) {
		OpenFile1.getline(str, 100);
		count++;
	}
	OpenFile1.close();
	count = count -3;

	//int* data = new int[count];

	int size = stoi(argv[2]);
	int splitnum = stoi(argv[3]);
	int datanum = stoi(argv[4]); 
	int totalnum = stoi(argv[5]);

	string* OutFileName = new string[splitnum];
	ofstream* OutFile = new ofstream[splitnum];
	for(int i = 0; i < splitnum; i++){
		OutFileName[i] = filename + "-" + to_string(i+1);
		OutFile[i].open(OutFileName[i]);
	}

	ifstream OpenFile2(filename);

	string str1, str2;
	OpenFile2.getline(str, 100);
	for(int i = 0; i< splitnum;i++){
		str1 = str;
		OutFile[i] << str1 <<"\r\n";
	}
	OpenFile2.getline(str, 100);
	for(int i = 0; i< splitnum;i++){
		str1 = str;
		OutFile[i] << str1;
	}

	
	cout << "hello!"<<endl;
	for(int i = 0; i < count; i++){
		OpenFile2.getline(str, 100);
		str1 = str;
		stringstream input(str1);
		int interval, no;
    	for(int j = 0; j<5; j++){
			getline(input, str2, ',');			
			if(j == 0){
				int value = stoi(str2);
				if(value >= size)
					break;
				interval = size/splitnum;
				no = value/interval;
				//cout << "no: "<< no << endl;
				//int temp = no*interval + interval/totalnum*datanum;
				int temp = no*interval + interval/2;
				OutFile[no] << "\r\n" << to_string(temp);
				//OutFile[no] << "\r\n" << to_string(value);
			}else{
				OutFile[no] << ",\t"<< str2;
			}
    	} 		
	}



	for(int i = 0; i < splitnum; i++){
		OutFile[i].close();
	}
	OpenFile2.close();
	delete[] OutFileName;
	delete[] OutFile;




	return 0;
}



