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
	//S 10 64 Accuracy
	string filename = argv[1];
	int number = stoi(argv[2]); 
	string labelsize = argv[3];
	string type = argv[4];
	string* dataset = new string[number];
	double all, exact, one, two, nl, path, enc, encS;
	all = 0;
	exact = 0;
	one = 0;
	two = 0;
	nl = 0;
	path = 0;
	enc = 0;
	encS = 0;

	for(int i = 0; i < number; i++){
		dataset[i] = filename+to_string(i+1)+"-"+labelsize+"-"+type;
		ifstream OpenFile(dataset[i]);
		char str[100];
		OpenFile.getline(str, 100);
		OpenFile.getline(str, 100);

		string str1, str2;
		//All
		OpenFile.getline(str, 100);
		str1 = str;
		stringstream input7(str1);
		getline(input7, str2, '\t');
		getline(input7, str2, '\t');
		all += stod(str2);
		cout << str2 << endl;

		//Exact
		OpenFile.getline(str, 100);
		str1 = str;
		stringstream input8(str1);
		getline(input8, str2, '\t');
		getline(input8, str2, '\t');
		exact += stod(str2);
		cout << str2 << endl;


		//one
		OpenFile.getline(str, 100);
		str1 = str;
		stringstream input1(str1);
		getline(input1, str2, '\t');
		getline(input1, str2, '\t');
		one += stod(str2);
		cout << str2 << endl;

		//two
		OpenFile.getline(str, 100);
		str1 = str;
		stringstream input2(str1);
		getline(input2, str2, '\t');
		getline(input2, str2, '\t');
		two += stod(str2);
		cout << str2 << endl;

		//nl
		OpenFile.getline(str, 100);
		str1 = str;
		stringstream input3(str1);
		getline(input3, str2, '\t');
		getline(input3, str2, '\t');
		nl += stod(str2);
		cout << str2 << endl;

		//path
		OpenFile.getline(str, 100);
		str1 = str;
		stringstream input4(str1);
		getline(input4, str2, '\t');
		getline(input4, str2, '\t');
		path += stod(str2);
		cout << str2 << endl;

		//enc
		OpenFile.getline(str, 100);
		str1 = str;
		stringstream input5(str1);
		getline(input5, str2, '\t');
		getline(input5, str2, '\t');
		enc += stod(str2);
		cout << str2 << endl;
		
		//enc*
		OpenFile.getline(str, 100);
		str1 = str;
		stringstream input6(str1);
		getline(input6, str2, '\t');
		getline(input6, str2, '\t');
		encS += stod(str2);
		cout << str2 << endl;

		cout << endl << endl;



		OpenFile.close();
	}


	cout << "The final average value is: " << endl;
	cout << all/number << endl;
	cout << exact/number << endl;
	cout << one/number << endl;
	cout << two/number << endl;
	cout << nl/number << endl;
	cout << path/number << endl;
	cout << enc/number << endl;
	cout << encS/number << endl;


	delete []dataset;	
	return 0;
}



