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

	int* data = new int[count];

	
	ifstream OpenFile2(filename);
	double sum = 0;
	string str1, str2;
	OpenFile2.getline(str, 100);
	OpenFile2.getline(str, 100);
	for(int i = 0; i < count; i++){
		OpenFile2.getline(str, 100);
		str1 = str;
		stringstream input(str1);
		getline(input, str2, ',');
		cout << str2 << endl;
		data[i] = stoi(str2);
		sum += data[i];
	}
	OpenFile2.close();

	cout<< "The sum is " << sum <<endl;
	double aver = sum / count;
	cout<< "The average ball size is " << aver << endl;

	double dev = 0, temp;
	for (int i = 0; i < count ; i++){
		temp = data[i] - aver;
		temp = temp * temp;
		if(temp < 0)
			cout<<"error on temp!"<<endl;
		dev += temp;
	}
	dev = dev/count;
	dev = sqrt(dev);
	cout << "The standard deviation of ball size is " << dev << endl;

	delete data;
	return 0;
}



