#pragma once

#ifndef STRONGSIMULATION_H_
#define STRONGSIMULATION_H_

#include <iostream>
#include "DIGraph.h"
#include "DataRead.h"
#include <time.h>
#include <sstream>
#include "cgbe.h"

using namespace std;

int cmp(const void *a, const void *b)
{

	return *(int *)a - *(int *)b; //ascending

	//return *(int *)b - *(int *)a; //descending
}

template <class VLabelType, class ELabelType>
class StrongSimulation
{
public:
	int *result, *result_EncSSim, *OneIterNL, *result_Path, *EncSpecial;
	int query_size, graph_size, query_selected_label_size, GlobalCountForBuildingReplaceTable, hoplength, pathlength;
	double exact_solution_num, OneIter_num, TwoIter_num, NeighborLabel_num, Path_num, portion;
	string OutFileName;
	string PathFileName;
	string Index1, Index2;
	double StrongSimulation_Time, Precompute_Q_Time, Enc_OneIter_Time, Enc_TwoIter_Time, NeighborLabel_Time, Path_Time, Enc_Time, Ball_Time, Decrypt_OneIter_Time, Decrypt_TwoIter_Time, Decrypt_NeighborLabel, Decrypt_Path, Index_Time;
	int NL_Improved, Path_Improved;
	DIGRAPH<VLabelType, ELabelType> *query;
	DIGRAPH<VLabelType, ELabelType> *graph;

	//
	typedef unordered_map<int, Ciphertext> P_Column_Value;
	typedef unordered_map<int, P_Column_Value> P_Row;

	//For Path
	typedef unordered_map<int, Ciphertext> EncPath;
	//typedef unordered_map<int, EncPath> Path_Index;
	typedef unordered_map<VertexID, EncPath> PathIndex;
	typedef unordered_map<int, PathIndex> Path_Index;

	//typedef unordered_map<VLabelType, int> Path_label;
	//typedef unordered_map<int, Path_label> Path_Label;
	typedef unordered_map<int, VLabelType> PathLabel;
	typedef unordered_map<int, PathLabel> Path_Label;

	//typedef unordered_map<int, VLabelType> Path_num;
	//typedef unordered_map<int, Path_num> Path_Num;
	//typedef unordered_map<VertexID, Path_Num> PathNum;
	typedef unordered_map<VLabelType, int> PathNum;
	typedef unordered_map<int, PathNum> Path_Num;

	//For NL 
	typedef unordered_map<VLabelType, int> LABEL;
	typedef unordered_map<VertexID, LABEL> Index;
	typedef unordered_map<int, Index> B_Index; //<hop, Vertex, Label, 1=exists>

	//For Two_Iter
	typedef unordered_map<int, Ciphertext> Ciphertext_Match;
	typedef unordered_map<int, Ciphertext_Match> Replace_Table; // <# for the vertex, # for the case, Ciphertext>

	//typedef unordered_map<VertexID, int> MapMatrix;				//record the map for the matrix
	typedef unordered_map<VertexID, VLabelType> VLabels;

	/*For query with random labels*/
	//StrongSimulation(Read<VLabelType, ELabelType> *, Read<VLabelType, ELabelType> *, string);

	/*For query with labels*/
	StrongSimulation(DataRead<VLabelType, ELabelType> *, DataRead<VLabelType, ELabelType> *, string, string, string, string, int, int);
	~StrongSimulation();
	void Match();
	void Exact(int **, int ***, int **, int, int, int);
	void Enc_OneIter(int **, Ciphertext **, P_Row &, int, int, CGBE *, Ciphertext &, Ciphertext &, int);
	void Enc_TwoIter(int **, Ciphertext **, Ciphertext **, P_Row &, int, int, CGBE *, Ciphertext &, Ciphertext &, Replace_Table &, Replace_Table &, Replace_Table &, Replace_Table &, int);
	void Enc_TwoIter_Random(int **, Ciphertext **, Ciphertext **, P_Row &, int, int, CGBE *, Ciphertext &, Ciphertext &, Replace_Table &, Replace_Table &, Replace_Table &, Replace_Table &, int, Ciphertext &, Ciphertext &, double);
	void Enc_NeighborLabel(int **, Ciphertext ***, Ciphertext ***, P_Row &, P_Row &, int, int, CGBE *, B_Index &, B_Index &, VLabelType *, Ciphertext &, Ciphertext &, int, VertexID, VertexID *);
	void NLTest(int **, int ***, int ***, int **, int, int, CGBE *, B_Index &G, B_Index &, VLabelType *, int, VertexID, VertexID *);
	void Enc_Path(Path_Label &, Path_Num &, Path_Index &, Path_Index &, int, int **, VertexID *, int, CGBE *, double &, int, VertexID, int);
	//void Enc_Path_Center(Path_Label &, Path_Label &, Path_Index &, int **, int, int, VertexID *, int, CGBE *);
	void PathMatch(DIGRAPH<VLabelType, ELabelType>*, Path_Num &, unordered_map<VertexID, unordered_map<int, int>> &, unordered_map<VertexID, unordered_map<int, int>> &, VLabelType *, int, int, int, VertexID, VertexID, int);
	//bool PathMatch(DIGRAPH<VLabelType, ELabelType>*, int *, int, int, int, VertexID);
	//bool PathMatch_Center(DIGRAPH<VLabelType, ELabelType>*, int *, int, int, int, int, VertexID);
	void Q_K_HOP(int ***, Ciphertext ***, Ciphertext ***, int ***, int ***, VLabelType *, CGBE *);
	void Q_Replace_Table_Child(int ***, Ciphertext **, Replace_Table &, Replace_Table &, CGBE *, Ciphertext &, Ciphertext &, int, int, int, Ciphertext &);
	void Q_Replace_Table_Parent(int ***, Ciphertext **, Replace_Table &, Replace_Table &, CGBE *, Ciphertext &, Ciphertext &, int, int, int, Ciphertext &);
	void BuildPathIndex(Path_Label &, Path_Num &, Path_Index &, Path_Index &, CGBE *, int, int, VLabelType*);
	void FindQueryPath(Path_Label &, Path_Num &, Path_Index &, Path_Index &, CGBE *, int, int, VLabelType*, VertexID, VertexID, int);
	int CantorExpansion(int, int *);
	void CantorExpansionDecode(int, int *, int);
	void ConstructBallMatrix(int **, VertexID *, int);
	void ConstructBallIndex(B_Index &, B_Index &, int **, VertexID *, int);
	void ConstructNLIndex(B_Index &, B_Index &, DIGRAPH<VLabelType, ELabelType> *,VertexID, VertexID, int, unordered_map<VertexID, int>&);
	void LoadNLIndex(B_Index &, B_Index &, string, string);
	
};

/*For query with random labels*/
/*
template <class VLabelType, class ELabelType>
StrongSimulation<VLabelType, ELabelType>::StrongSimulation(Read<VLabelType, ELabelType> *Q, Read<VLabelType, ELabelType> *G, string OutFile)
{
*/

/*For query with labels*/

template <class VLabelType, class ELabelType>
StrongSimulation<VLabelType, ELabelType>::StrongSimulation(DataRead<VLabelType, ELabelType> *Q, DataRead<VLabelType, ELabelType> *G, string OutFile, string Path, string Name1, string Name2, int khop, int pathlength)
{
	this->portion = 0.25; //Random TwoIter
	this->query = Q->graph_ptr;
	this->graph = G->graph_ptr;
	this->graph_size = this->graph->getVcnt();
	this->query_size = this->query->getVcnt();
	this->query_selected_label_size = this->query->VLabelSet.size();
	//if (this->query_selected_label_size > K_LABEL)
	//	this->query_selected_label_size = K_LABEL;
	this->exact_solution_num = 0;
	this->OneIter_num = 0;
	this->TwoIter_num = 0;
	this->NeighborLabel_num = 0;
	this->Path_num = 0;
	this->result = new int[graph_size];
	this->result_EncSSim = new int[graph_size];
	this->OneIterNL = new int[graph_size];
	this->EncSpecial = new int[graph_size];
	this->result_Path = new int[graph_size];
	this->StrongSimulation_Time = 0;
	this->Precompute_Q_Time = 0;
	this->Enc_OneIter_Time = 0;
	this->Enc_TwoIter_Time = 0;
	this->NeighborLabel_Time = 0;
	this->Path_Time = 0;
	this->Enc_Time = 0;
	this->Ball_Time = 0;
	this->GlobalCountForBuildingReplaceTable = 0;
	this->Decrypt_OneIter_Time = 0;
	this->Decrypt_TwoIter_Time = 0;
	this->Decrypt_NeighborLabel = 0;
	this->Decrypt_Path = 0;
	this->Index_Time = 0;
	this->OutFileName = OutFile;
	this->PathFileName = Path;
	this->Index1 = Name1;
	this->Index2 = Name2;
	this->NL_Improved = 0;
	this->Path_Improved = 0;
	this->hoplength = khop;
	this->pathlength = pathlength;
	cout << "*************************************" << endl;
	cout << "The Strong Simulation has been built!" << endl;
	cout << "*************************************" << endl;
	cout << endl;
}

template <class VLabelType, class ELabelType>
StrongSimulation<VLabelType, ELabelType>::~StrongSimulation()
{
	delete[] this->result;
	delete[] this->result_EncSSim;
	delete[] this->OneIterNL;
	delete[] this->EncSpecial;
	delete[] this->result_Path;
	cout << "The ptr in Strong Simulation has been deleted!" << endl;
}

template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::Match()
{
	clock_t startTime, endTime, startTime1, endTime1, startTimeTest, endTimeTest;
	clock_t startOne, endOne, startTwo, endTwo, startThree, endThree, startFour, endFour, startFive, endFive;

	/*Output the data*/
    ofstream OutFile(OutFileName);	
	string RuntimeName = OutFileName + "-runtime";
	string PrecisionName = OutFileName + "-Accuracy";
	string NumberName = OutFileName + "-Number";
	ofstream Runtime(RuntimeName);
	ofstream Precision(PrecisionName);
	ofstream Number(NumberName);
	Runtime << "# |V_Q| = " << query_size << endl;
	Runtime << "# ball size, exact, 2-iter, NL, Path" << endl;
	Precision << "# name, dataset" << endl;
	Number << "# name, dataset" << endl;


	///////////////////////////////////////
	/////////////   Client   //////////////
	///////////////////////////////////////
	//compute the diameter of Query
	this->query->getDiameter();
	int dia = this->query->diameter;
	cout << "The diameter of the Query is " << dia << endl;

	/*construct the matrix $\overline{M_Q}$ and encrypted one for the query*/
	startTime = clock();
	//Ciphertext ***EM_Q = new Ciphertext **[K_HOP];
	//used for one-hop neighbor
	int ***Q = new int **[hoplength];
	Q[0] = new int *[query_size];
	int ***Q_Child = new int **[hoplength];
	int ***Q_Parent = new int **[hoplength];
	Ciphertext **EM_Q = new Ciphertext *[query_size];
	Ciphertext **EM_Q_Two = new Ciphertext *[query_size];
	Ciphertext ***EM_Q_Child = new Ciphertext **[hoplength];
	Ciphertext ***EM_Q_Parent = new Ciphertext **[hoplength];
	CGBE *cgbe = new CGBE();



	Ciphertext cipher_one, cipher_zero; //for SP to compute in ciphertext
	mpz_init(cipher_one);
	mpz_init(cipher_zero);
	cgbe->setvalue(cipher_one, 1);
	cgbe->setvalue(cipher_zero, cgbe->encoding);
	cgbe->encrypt(cipher_one, cipher_one);
	cgbe->encrypt(cipher_zero, cipher_zero);

	Ciphertext cipher_one_Two;
	Ciphertext cipher_one_Four_Vq;
	mpz_init(cipher_one_Two);
	mpz_init(cipher_one_Four_Vq);
	cgbe->mul(cipher_one_Two, cipher_one, cipher_one);
	cgbe->mul(cipher_one_Two, cipher_one_Two, cipher_one_Two);
	cgbe->setvalue(cipher_one_Four_Vq, 1);
	for(int i = 0; i< query_size; i++){
		cgbe->mul(cipher_one_Four_Vq, cipher_one_Four_Vq, cipher_one_Two);
	}
	cgbe->mul(cipher_one_Two, cipher_one, cipher_one);


	//use for the ball structure in graph structure
	DIGRAPH<VLabelType, ELabelType>* Ball;
				
	/*intialize matrix M_Q*/
	for (int i = 0; i < query_size; i++)
	{
		Q[0][i] = new int[query_size];
		EM_Q[i] = new Ciphertext[query_size];
		EM_Q_Two[i] = new Ciphertext[query_size];
		for (int j = 0; j < query_size; j++)
		{
			Q[0][i][j] = 1;
			mpz_init(EM_Q[i][j]);
			mpz_init(EM_Q_Two[i][j]);
			cgbe->setvalue(EM_Q[i][j], 1);
			if (this->query->isEdge(this->query->matrix[i], this->query->matrix[j]))
			{
				Q[0][i][j] = 0;
				cgbe->setvalue(EM_Q[i][j], cgbe->encoding);
			}
			cout << Q[0][i][j] << " ";
			cgbe->encrypt(EM_Q[i][j], EM_Q[i][j]);
			cgbe->setvalue(EM_Q_Two[i][j], EM_Q[i][j]);
			cgbe->mul(EM_Q_Two[i][j], EM_Q_Two[i][j], EM_Q_Two[i][j]);
		}
		cout << endl;	
	}
	
	/*preprocessing for Q*/
	/*construct K_HOP indices for Q*/
	VLabelType *Column = new VLabelType[this->query_selected_label_size]; //label for column
	//NL
	Q_K_HOP(Q, EM_Q_Child, EM_Q_Parent, Q_Child, Q_Parent, Column, cgbe);
	endTime = clock();
	this->Enc_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;


	startTime = clock();
	//load the Path_Index
	Path_Index PathIndex1, PathIndex2;
	Path_Label PathLabel;
	Path_Num PathNum;
	for(int i = 3; i <= this->pathlength;i++)
		BuildPathIndex(PathLabel, PathNum, PathIndex1, PathIndex2, cgbe, i, 0, nullptr);
	endTime = clock();
	this->Enc_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
	startTime = clock();

	/*
	cout << "#######################" << endl;
	cout << "#######################" << endl;

	for(auto it = PathIndex2.begin();it != PathIndex2.end(); it++){
		cout << "Vertex " << it->first <<":" << endl;
		for(auto it2 = PathIndex2[it->first].begin(); it2 != PathIndex2[it->first].end(); it2++){
			cgbe->decrypt(it2->second, it2->second);
			if(cgbe->isZero(it2->second))
				cout << "Path " << it2->first << ": 0" <<endl;
			else
				cout << "Path " << it2->first << ": 1" <<endl;
		}

	}*/


	//Replace_Table
	Replace_Table Origin_Child, Replace_Child, Origin_Parent, Replace_Parent;
	Q_Replace_Table_Child(Q, EM_Q, Origin_Child, Replace_Child, cgbe, cipher_one, cipher_zero, 0, -1, 0, cipher_zero);
	Q_Replace_Table_Parent(Q, EM_Q, Origin_Parent, Replace_Parent, cgbe, cipher_one, cipher_zero, 0, -1, 0, cipher_zero);

	endTime = clock();
	this->Enc_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
	cout << endl;
	cout << "The runtime for preprocessing Q on Client is " << Enc_Time << endl;
	cout << "\n*************************************" << endl;


	//OutFile << "The runtime for preprocessing Q on Client is " << Enc_Time << endl;
	//OutFile << "\n*************************************" << endl;

	/////////////////
	/////////////////
	////////////////
	//Here
	//OutFile << "Ball#"<< "	"<< "BallSize"<< "	"<< "runtime"<< "	"<< "Time-Ball" "	"<< "Time-Index" << "	"<< "Time-Neighbor"<< "	"<< "Time-TwoIter"<< "	"<< "Time-Path" << "	"<< "Time-Exact" << endl;
	/////////////////
	/////////////////
	/////////////////


	///////////////////////////////////////
	/////////////   Server   //////////////
	///////////////////////////////////////

	//load the graph index
	/**/
	/**/
	/**/
	 
	//The new part

	/**/
	/**/
	/**/	
	startTimeTest = clock();
	B_Index Graph_Index, Graph_Index_Reverse;
	LoadNLIndex(Graph_Index, Graph_Index_Reverse, Index1, Index2);
	endTimeTest = clock();
	cout << "Indexes are loaded in " << (double)(endTimeTest - startTimeTest) / CLOCKS_PER_SEC << " seconds!" <<endl;

	//pointer for short test
	int pointer = 0;

	//Num_Ball_Computed
	int Num_Ball_Computed = 0, Num_Ball_Ignored = 0;

	double each_ball_time;
	//build each ball
	for (typename VLabels::iterator it1 = this->graph->getVLabel().begin();
		 it1 != this->graph->getVLabel().end(); it1++)
	{

		startOne =clock();
		//No need to short test now
		//if (pointer == 3000)
		//	break;

		//if (Num_Ball_Computed == 1)
		//	break;

		VertexID s = it1->first, t;

		/*if the center of the ball's label is not in the label set of query, then continue*/
		if (!(this->query->isLabel(this->graph->getVLabel(s))))
		{
			this->result_EncSSim[pointer] = 0;
			this->OneIterNL[pointer] = 0;
			this->EncSpecial[pointer] = 0;
			this->result_Path[pointer] = 0;
			pointer++;
			continue;
		}

		each_ball_time = 0;
		startTime = clock();
		startTwo = startTime;


		unordered_set<VertexID> s_neighbor;
		this->graph->getDNeighbor(s, dia, s_neighbor, query);
		int size_ball = s_neighbor.size();

		//If the ball is too large, continue
		/*if (size_ball > 3000)
		{
			OutFile << pointer << "	"<< size_ball << endl;
			pointer++;
			Num_Ball_Ignored++;
			continue;
		}*/

		VertexID *Matrix_ball = new VertexID[size_ball];
		unordered_map<VertexID, int> Matrix_Ball;
		int tempnum = 0;
		for (unordered_set<VertexID>::iterator it2 = s_neighbor.begin();
			 it2 != s_neighbor.end(); it2++)
		{
			t = *it2;
			Matrix_ball[tempnum] = t;
			Matrix_Ball[t] = tempnum;
			tempnum++;
			//	cout << "The vertex " << t << " is contained in the neighbor of vertex " << s << endl;
		}




		/*construct the matrix M_B for the ball*/
		int **M_B = new int *[size_ball];
		ConstructBallMatrix(M_B, Matrix_ball, size_ball);



	


		/*construct the matrix P for two methods*/
		P_Row P_OneIter, P_NeighborLabel, P_TwoIter, P_Replace;
		int **answer = new int *[query_size];

		//NLtest
		int **M_P = new int *[query_size];

		for (int i = 0; i < query_size; i++)
		{
			answer[i] = new int[size_ball];
			M_P[i] = new int[size_ball];
			/*intialize matrix P*/
			for (int j = 0; j < size_ball; j++)
			{
				answer[i][j] = 0;
				M_P[i][j] = 0;
				if (this->query->getVLabel(this->query->matrix[i]) == this->graph->getVLabel(Matrix_ball[j]))
				{
					answer[i][j] = 1;
					M_P[i][j] = 1;
					mpz_init(P_OneIter[i][j]);
					mpz_init(P_NeighborLabel[i][j]);
					mpz_init(P_Replace[i][j]);
					mpz_init(P_TwoIter[i][j]);
					cgbe->setvalue(P_OneIter[i][j], 1);
					//cgbe->encrypt(P_OneIter[i][j], P_OneIter[i][j]);
					cgbe->setvalue(P_NeighborLabel[i][j], 1);
					//cgbe->encrypt(P_NeighborLabel[i][j], P_NeighborLabel[i][j]);
					cgbe->setvalue(P_TwoIter[i][j], 1);
				}
			}
		}



		endTime = clock();
		endTwo = endTime;
		each_ball_time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
		this->Ball_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;

		/////////////////////Pruning Techniques///////////////////////
		//If there is one row in P equals to zero vector, then prune//
		//////////////////////////////////////////////////////////////
		bool Prune_flag;
		for (int i = 0; i < query_size; i++)
		{
			Prune_flag = true;
			for (int j = 0; j < size_ball; j++)
			{
				if (answer[i][j] != 0)
				{
					Prune_flag = false;
					break;
				}
			}
			if (Prune_flag)
				break;
		}

		if (Prune_flag)
		{
			this->result_EncSSim[pointer] = 0;
			this->OneIterNL[pointer] = 0;
			this->EncSpecial[pointer] = 0;
			this->result_Path[pointer] = 0;

			pointer++;
			/*free the space*/
			for (int i = 0; i < size_ball; i++)
			{
				delete[] M_B[i];
			}
			delete[] M_B;

			for (int i = 0; i < query_size; i++)
			{
				delete[] answer[i];
				delete[] M_P[i];
			}

			delete[] answer;
			delete[] M_P;
			delete[] Matrix_ball;
			Matrix_Ball.clear();
			s_neighbor.clear();
			P_OneIter.clear();
			P_TwoIter.clear();
			P_NeighborLabel.clear();
			P_Replace.clear();
			continue;
		}


		/////////////////////Pruning Techniques///////////////////////
		//If there is one row in P equals to zero vector, then prune//
		//////////////////////////////////////////////////////////////

		//Build the index for the NL technique

		/*Construct the indices for ball B */
		//B_Index Ball_Index, Ball_Index_Reverse;

		/* using the matrix multiplication */			
		//ConstructBallIndex(Ball_Index, Ball_Index_Reverse, M_B, Matrix_ball, size_ball);

	 	/* using the graph traverse */
		//startTime1 = clock();	
		//Ball = new DIGRAPH<VLabelType, ELabelType>;
		//Ball->ConstructInducedGraph(s_neighbor, this->graph);
		//ConstructNLIndex(Ball_Index, Ball_Index_Reverse, Ball, -1, -1, -1, Matrix_Ball);
		//endTime1 = clock();
		//this->Index_Time += (double)(endTime1 - startTime1) / CLOCKS_PER_SEC;
		this->result_EncSSim[pointer] = 1;
		this->OneIterNL[pointer] = 1;
		this->EncSpecial[pointer] = 1;
		this->result_Path[pointer] = 1;

		/*Enc_One_Iter Algorithm*/
		Enc_OneIter(M_B, EM_Q, P_OneIter, size_ball, pointer, cgbe, cipher_one, cipher_zero, Matrix_Ball[s]);
	
		/*Enc_Two_Iter Algorithm*/
		startFour = clock();
		if(this->portion == 1){
			Enc_TwoIter(M_B, EM_Q, EM_Q_Two, P_TwoIter, size_ball, pointer, cgbe, cipher_one, cipher_zero, Origin_Child, Replace_Child, Origin_Parent, Replace_Parent, Matrix_Ball[s]);
			//cout << "hello portion 1 " << this->portion << endl;
		}
		else
			Enc_TwoIter_Random(M_B, EM_Q, EM_Q_Two, P_TwoIter, size_ball, pointer, cgbe, cipher_one, cipher_zero, Origin_Child, Replace_Child, Origin_Parent, Replace_Parent, Matrix_Ball[s], cipher_one_Two, cipher_one_Four_Vq, this->portion);
		endFour = clock();

		/*Enc_NieghborLabel Algorithm*/
		startThree = clock();
		Enc_NeighborLabel(M_B, EM_Q_Child, EM_Q_Parent, P_NeighborLabel, P_Replace, size_ball, pointer, cgbe, Graph_Index, Graph_Index_Reverse, Column, cipher_one, cipher_zero, Matrix_Ball[s], s, Matrix_ball);
		endThree = clock();

		//NLTest(M_B, Q_Child, Q_Parent, M_P, size_ball, pointer, cgbe, Graph_Index, Graph_Index_Reverse, Column, Matrix_Ball[s], s, Matrix_ball);
		/*Enc_Path Algorithm*/
		startFive = clock();
		double PathTimeTemp = 0;
		for(int i = 3; i <= this->pathlength; i++)
			Enc_Path(PathLabel, PathNum, PathIndex1, PathIndex2, pointer, M_B, Matrix_ball, size_ball, cgbe, PathTimeTemp, Matrix_Ball[s], s, i); 
		endFive = clock();
		
		/*Exact strong simulation Algorithm*/
		startTime = clock();
		Exact(M_B, Q, answer, size_ball, pointer, Matrix_Ball[s]);
		endTime = clock();
		each_ball_time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
		this->StrongSimulation_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;


		
		/*free the space*/
		for (int i = 0; i < size_ball; i++)
		{
			delete[] M_B[i];
		}
		delete[] M_B;

		for (int i = 0; i < query_size; i++)
		{
			delete[] answer[i];
			delete[] M_P[i];
		}
		delete[] answer;
		delete[] M_P;
		delete[] Matrix_ball;
		Matrix_Ball.clear();
		s_neighbor.clear();
		P_OneIter.clear();
		P_TwoIter.clear();
		P_NeighborLabel.clear();
		P_Replace.clear();


		//Ball_Index.clear();
		//Ball_Index_Reverse.clear();
		//Ball->~DIGRAPH();
		Num_Ball_Computed++;
		pointer++;
		if (each_ball_time > 1)
		{
			cout << "The " << pointer << " ball is finished in " << each_ball_time << " seconds! The size is: " << size_ball << endl;
		}

		endOne = clock();

		Runtime << size_ball <<", " << (double)(endTime - startTime) * 1000 / CLOCKS_PER_SEC << ", " << (double)(endFour - startFour) * 1000 / CLOCKS_PER_SEC << ", " << (double)(endThree - startThree) * 1000 / CLOCKS_PER_SEC << ", " << PathTimeTemp << endl;

		//OutFile << pointer << "	"<< size_ball<< "	"<< (double)(endOne - startOne) / CLOCKS_PER_SEC<< "	"<< (double)(endTwo - startTwo) / CLOCKS_PER_SEC << "	" << (double)(endTime1 - startTime1) / CLOCKS_PER_SEC << "	"<< (double)(endThree - startThree) / CLOCKS_PER_SEC << "	"<< (double)(endFour - startFour) / CLOCKS_PER_SEC << "	"<< (double)(endFive - startFive) / CLOCKS_PER_SEC << "	" << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
	}



	if (this->query_selected_label_size <= 2)
		cout << "There are little labels to conduct the NeighborLabel Pruning!\n" << endl;

	//cout path number
	for(int i = 0; i < this->graph_size; i++){
		if(this->result_Path[i] == 1)
			Path_num++;
	}

	/*print the results */
	cout << OutFileName << endl;
	cout << "******************************************************************" << endl;
	cout << "\nTotal computed Ball: " << Num_Ball_Computed <<  endl;
	cout << "The runtime for constructing the traversed balls and Matrices Ps is " << Ball_Time << endl;
	cout << "Index time " << Index_Time << endl;
	cout << "******************************************************************" << endl;
	cout << exact_solution_num << " exact matches with " << StrongSimulation_Time << "seconds!"  << endl;
	cout << "******************************************************************" << endl;
	cout << OneIter_num << " OneIter matches with " << Enc_OneIter_Time << "seconds!"  << endl;
	cout << "Decryption Time: " << Decrypt_OneIter_Time << endl;
	cout << "******************************************************************" << endl;
	cout << TwoIter_num << " TwoIter-"<<this->portion << " matches with" << Enc_TwoIter_Time << "seconds!"  << endl;
	cout << "Decryption Time: " << Decrypt_TwoIter_Time << endl;
	cout << "******************************************************************" << endl;
	cout << NeighborLabel_num << " NL matches with " << NeighborLabel_Time << "seconds!"  << endl;
	cout << "Decryption Time: " << Decrypt_NeighborLabel << endl;
	cout << "The improvement of NL is " << NL_Improved <<endl;
	cout << "******************************************************************" << endl;
	cout <<  Path_num << " Path matches with " << Path_Time << "seconds!"  << endl;
	cout << "Decryption Time: " << Decrypt_Path << endl;
	cout << "The improvement of Path is " << Path_Improved <<endl;





	OutFile << "******************************************************************" << endl;
	OutFile << "\nTotal computed Ball: " << Num_Ball_Computed <<  endl;
	//OutFile << "\nThere are " << Num_Ball_Ignored << " ball been ignored!" << endl;	
	//OutFile << "The runtime for constructing the traversed balls and Matrices Ps is " << Ball_Time << endl;
	OutFile << "Index time: " << Index_Time << endl;
	OutFile << "******************************************************************" << endl;
	OutFile << exact_solution_num << " exact matches with " << StrongSimulation_Time << "seconds!"  << endl;
	OutFile << "******************************************************************" << endl;
	OutFile << OneIter_num << " OneIter matches with " << Enc_OneIter_Time << "seconds!"  << endl;
	OutFile << "Decryption Time: " << Decrypt_OneIter_Time << endl;
	OutFile << "******************************************************************" << endl;
	OutFile << TwoIter_num << " TwoIter-"<<this->portion << " matches with" << Enc_TwoIter_Time << "seconds!"  << endl;
	OutFile << "Decryption Time: " << Decrypt_TwoIter_Time << endl;
	OutFile << "******************************************************************" << endl;
	OutFile << NeighborLabel_num << " NL matches with " << NeighborLabel_Time << "seconds!"  << endl;
	OutFile << "Decryption Time: " << Decrypt_NeighborLabel << endl;
	OutFile << "The improvement of NL is " << NL_Improved <<endl;
	OutFile << "******************************************************************" << endl;
	OutFile <<  Path_num << " Path matches with " << Path_Time << "seconds!"  << endl;
	OutFile << "Decryption Time: " << Decrypt_Path << endl;
	OutFile << "The improvement of Path is " << Path_Improved <<endl;


	//if (exact_solution_num != 0)
	//	cout << "The false positive is " << OneIter_num - exact_solution_num << endl;

	int falseCount1 = 0;
	for (int i = 0; i < pointer; i++)
	{
		if ((result[i] == 1) && (result_EncSSim[i] != 1))
		{
			//cout << "Some Strong Simulations are missing!" << endl;
			falseCount1++;
		}
	}

	int trueCount1 = 0;
	for (int i = 0; i < pointer; i++)
	{
		if (result_EncSSim[i] == 1)
		{
			trueCount1++;
		}
	}

	OutFile << "There are total " << trueCount1 << " obtained by EncSSim with missing " << falseCount1 << endl;

	int falseCount2 = 0;
	for (int i = 0; i < pointer; i++)
	{
		if ((result[i] == 1) && (OneIterNL[i] != 1))
		{
			//cout << "Some Strong Simulations are missing!" << endl;
			falseCount2++;
		}
	}


	int OneCount = 0;
	for (int i = 0; i < pointer; i++)
	{
		if (OneIterNL[i] == 1)
		{
			OneCount++;
		}
	}

	int EncCount = 0;
	for (int i = 0; i < pointer; i++)
	{
		if (EncSpecial[i] == 1)
		{
			EncCount++;
		}
	}

	OutFile << "There are total " << OneCount << " obtained by One+EncSSim with missing " << falseCount2 << endl;


	Precision << "# Name, Dataset" << endl;
	Precision << "OneIter\t" << (1-(OneIter_num-exact_solution_num)/Num_Ball_Computed) << endl;	
	Precision << "TwoIter\t" << (1-(TwoIter_num-exact_solution_num)/Num_Ball_Computed) << endl;	
	Precision << "NL\t" << (1-(NeighborLabel_num-exact_solution_num)/Num_Ball_Computed) << endl;	
	Precision << "Path\t" << (1-(Path_num-exact_solution_num)/Num_Ball_Computed) << endl;	
	//Precision << "All,\t" << (1-(trueCount1-exact_solution_num)/Num_Ball_Computed) << endl;
	Precision << "Enc\t" << (1-(OneCount-exact_solution_num)/Num_Ball_Computed) << endl;
	Precision << "Enc*\t" << (1-(EncCount-exact_solution_num)/Num_Ball_Computed) << endl;

	Number << "# Name, Dataset" << endl;
	Number <<"All\t" << Num_Ball_Computed << endl;
	Number <<"Exact\t" << exact_solution_num << endl;
	Number << "OneIter\t" << OneIter_num << endl;
	Number << "TwoIter\t" << TwoIter_num << endl;
	Number << "NL\t" << NeighborLabel_num << endl;
	Number << "Path\t" << Path_num << endl;
	//Number << "All,\t" << trueCount1 << endl;
	Number << "Enc\t" << OneCount << endl;
	Number << "Enc*\t" << EncCount << endl;


	/*free the space for Queries */
	for (int i = 0; i < hoplength; i++)
	{
		for (int j = 0; j < query_size; j++)
		{
			delete[] Q[i][j];
			delete[] EM_Q_Child[i][j];
			delete[] EM_Q_Parent[i][j];
			delete[] Q_Child[i][j];
			delete[] Q_Parent[i][j];
		}
		delete[] Q[i];
		delete[] EM_Q_Child[i];
		delete[] EM_Q_Parent[i];
		delete[] Q_Child[i];
		delete[] Q_Parent[i];
	}

	for (int i = 0; i < query_size; i++){
		delete[] EM_Q[i];
		delete[] EM_Q_Two[i];
	}

	delete[] Q;
	delete[] EM_Q;
	delete[] EM_Q_Two;
	delete[] EM_Q_Child;
	delete[] EM_Q_Parent;
	delete[] Q_Parent;
	delete[] Q_Child;
	delete[] Column;
	delete cgbe;
	mpz_clear(cipher_one);
	mpz_clear(cipher_zero);
	mpz_clear(cipher_one_Two);
	mpz_clear(cipher_one_Four_Vq);
	Origin_Child.clear();
	Origin_Parent.clear();
	Replace_Child.clear();
	Replace_Parent.clear();
	PathIndex1.clear();
	PathIndex2.clear();
	PathLabel.clear();
	PathNum.clear();
	OutFile.close();
	Runtime.close();
}

template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::Exact(int **M_B, int ***Q, int **answer, int size_ball, int pointer, int center)
{
	bool flag;
	int temp_value;

	/* For test of OneIter in Plaintext */

	// int **answer_fake = new int *[query_size];
	// for (int i = 0; i < query_size; i++){
	// 	answer_fake[i] = new int[size_ball];
	// 	for (int j =0; j< size_ball; j++)
	// 		answer_fake[i][j] = 0;
	// }

	// for (int iteration = 0; iteration < 1; iteration++)
	// {
	// 	flag = true;
	// 	for (int i = 0; i < query_size; i++)
	// 	{
	// 		for (int j = 0; j < size_ball; j++)
	// 		{
	// 			if(answer[i][j]==0)
	// 				continue;
	// 			answer_fake[i][j] = answer[i][j];
	// 			temp_value = answer[i][j];
	// 			int follow = 1, parent = 1, sum1, sum2;
	// 			for (int k = 0; k < query_size; k++)
	// 			{
	// 				sum1 = 0;
	// 				sum2 = 0;
	// 				for (int l = 0; l < size_ball; l++)
	// 				{
	// 					sum1 += (M_B[j][l] * answer[k][l]);
	// 					sum2 += (M_B[l][j] * answer[k][l]);
	// 				}
	// 				sum1 += Q[0][i][k];
	// 				sum2 += Q[0][k][i];
	// 				if ((sum1 != 0) && (sum2 != 0))
	// 					answer_fake[i][j] = answer_fake[i][j] * 1;
	// 				else
	// 					answer_fake[i][j] = 0;
	// 				if (answer[i][j] != temp_value)
	// 					flag = false;
	// 			}
	// 		}
	// 	}
	// 	if (flag)
	// 		break;
	// }

	// for (int i = 0; i < query_size; i++)
	// 	for (int j= 0; j< size_ball; j++)
	// 		answer[i][j] = answer_fake[i][j];

	/* since each element is updated immediately, the pruning is much better */
	for (int iteration = 0; iteration < size_ball; iteration++)
	{
		flag = true;
		for (int i = 0; i < query_size; i++)
		{
			for (int j = 0; j < size_ball; j++)
			{
				if (answer[i][j] == 0)
					continue;
				temp_value = answer[i][j];
				int follow = 1, parent = 1, sum1, sum2;
				for (int k = 0; k < query_size; k++)
				{
					sum1 = 0;
					sum2 = 0;
					for (int l = 0; l < size_ball; l++)
					{
						sum1 += (M_B[j][l] * answer[k][l]);
						sum2 += (M_B[l][j] * answer[k][l]);
					}
					sum1 += Q[0][i][k];
					sum2 += Q[0][k][i];
					if ((sum1 != 0) && (sum2 != 0))
						answer[i][j] = answer[i][j] * 1;
					else
						answer[i][j] = 0;
					if (answer[i][j] != temp_value)
						flag = false;
				}
			}
		}
		if (flag)
			break;
	}

	/*compute the result for this ball*/
	int product = 1, sum = 0;
	int match_num;
	for (int i = 0; i < query_size; i++)
	{
		sum += answer[i][center];
		match_num = 0;
		for (int j = 0; j < size_ball; j++)
		{
			match_num += answer[i][j];
		}
		product *= match_num;
		if(product > 0)
			product = 1;
				
	}



	if (product > 0 && sum > 0)
	{
		exact_solution_num++;
		this->result[pointer] = 1;
		//cout << "The " << pointer << " ball is a strong simulation match!" << endl;
	}
	else
	{
		if (product < 0)
			cout << "The product in Exact Algorithm is wrong!" << endl;
		this->result[pointer] = 0;
		//cout << "The " << pointer << " ball is not a strong simulation match!" << endl;
	}
}

template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::Enc_OneIter(int **M_B, Ciphertext **EM_Q, P_Row &P_OneIter, int size_ball, int pointer, CGBE *cgbe, Ciphertext &cipher_one, Ciphertext &cipher_zero, int center)
{
	//"pointer" here in case of saving the result for Enc_OneIter
	clock_t startTime, endTime;
	P_Row P_temp;

	/*For Decryption with different combined private key */
	// OneIter
	cgbe->setCombinedPrivateKey_OneIter(2 * query_size);

	/*Violation Detector for one time*/
	mpz_t sum1, sum2, follow, parent;
	mpz_init(sum1);
	mpz_init(sum2);
	mpz_init(follow);
	mpz_init(parent);

	startTime = clock();
	for (int i = 0; i < query_size; i++)
	{
		for (int j = 0; j < size_ball; j++)
		{
			//No need to compute 0 element
			if (P_OneIter[i].find(j) == P_OneIter[i].end())
				continue;
			mpz_init(P_temp[i][j]);
			cgbe->setvalue(follow, 1);
			cgbe->setvalue(parent, 1);
			for (int k = 0; k < query_size; k++)
			{
				cgbe->setvalue(sum1, 0);
				cgbe->setvalue(sum2, 0);
				for (int l = 0; l < size_ball; l++)
				{
					if (M_B[j][l] == 1)
					{
						if (P_OneIter[k].find(l) != P_OneIter[k].end())
							cgbe->add(sum1, sum1, P_OneIter[k][l]);
					}
					if (M_B[l][j] == 1)
					{
						if (P_OneIter[k].find(l) != P_OneIter[k].end())
							cgbe->add(sum2, sum2, P_OneIter[k][l]);
					}
				}
				if (!(cgbe->isZero(sum1)))
					cgbe->setvalue(sum1, cipher_one);
				if (!(cgbe->isZero(sum2)))
					cgbe->setvalue(sum2, cipher_one);

				cgbe->add(sum1, sum1, EM_Q[i][k]);
				cgbe->add(sum2, sum2, EM_Q[k][i]);
				cgbe->mul(follow, follow, sum1);
				cgbe->mul(parent, parent, sum2);
			}
			cgbe->mul(P_temp[i][j], P_OneIter[i][j], follow);
			//cgbe->mul(P_temp[i][j], P_OneIter[i][j], parent);   This is wrong!!!! Below is correct!!!! only 2*|V_Q| for combinedPrivateKey
			cgbe->mul(P_temp[i][j], P_temp[i][j], parent);
		}
	}

	//Update the value of matrix P
	for (int i = 0; i < query_size; i++)
	{
		for (int j = 0; j < size_ball; j++)
		{
			//No need to compute 0 element
			if (P_OneIter[i].find(j) == P_OneIter[i].end())
				continue;
			cgbe->setvalue(P_OneIter[i][j], P_temp[i][j]);
		}
	}
	endTime = clock();
	this->Enc_OneIter_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;

	////////////////////////////////////
	///////////    Result    ///////////
	////////////////////////////////////
	bool Result_flag, center_flag = false;
	for (int i = 0; i < query_size; i++)
	{
		startTime = clock();
		Result_flag = true;
		cgbe->setvalue(sum1, 0);
		for (int j = 0; j < size_ball; j++)
		{
			if (P_OneIter[i].find(j) == P_OneIter[i].end())
				continue;
			cgbe->add(sum1, sum1, P_OneIter[i][j]);
		}
		endTime = clock();
		this->Enc_OneIter_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;

		//decryption
		///////////////////////////////////////
		/////////////   Client   //////////////
		///////////////////////////////////////
		startTime = clock();
		cgbe->decryption_OneIter(sum1, sum1);
		cgbe->decryption_OneIter(P_OneIter[i][center], P_OneIter[i][center]);
		endTime = clock();
		this->Decrypt_OneIter_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;

		if (cgbe->isZero(sum1))
		{
			Result_flag = false;
			break;
		}
		if(!(cgbe->isZero(P_OneIter[i][center]))){
			center_flag = true;
		}

	}

	if (Result_flag && center_flag)
	{
		OneIter_num++;
		this->OneIterNL[pointer] = 1;
	}else{
		this->OneIterNL[pointer] = 0;
	}

	mpz_clear(sum1);
	mpz_clear(sum2);
	mpz_clear(parent);
	mpz_clear(follow);
	P_temp.clear();
}

template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::Enc_TwoIter(int **M_B, Ciphertext **EM_Q, Ciphertext **EM_Q_Two, P_Row &P_TwoIter, int size_ball, int pointer, CGBE *cgbe, Ciphertext &cipher_one, Ciphertext &cipher_zero, Replace_Table &Origin_Child, Replace_Table &Replace_Child, Replace_Table &Origin_Parent, Replace_Table &Replace_Parent, int center)
{
	//"pointer" here in case of saving the result for Enc_TwoIter
	clock_t startTime, endTime;
	P_Row P_temp;

	/*For Decryption with different combined private key */
	// TwoIter .... to be determined
	cgbe->setCombinedPrivateKey_TwoIter(4 * query_size);

	/*Violation Detector for the first time*/
	mpz_t sum1, sum2, follow, parent;
	mpz_init(sum1);
	mpz_init(sum2);
	mpz_init(follow);
	mpz_init(parent);

	startTime = clock();
	for (int i = 0; i < query_size; i++)
	{
		for (int j = 0; j < size_ball; j++)
		{
			//No need to compute 0 element
			if (P_TwoIter[i].find(j) == P_TwoIter[i].end())
				continue;
			mpz_init(P_temp[i][j]);
			cgbe->setvalue(follow, 1);
			cgbe->setvalue(parent, 1);
			for (int k = 0; k < query_size; k++)
			{
				cgbe->setvalue(sum1, 0);
				cgbe->setvalue(sum2, 0);
				for (int l = 0; l < size_ball; l++)
				{
					if (M_B[j][l] == 1)
					{
						if (P_TwoIter[k].find(l) != P_TwoIter[k].end())
							cgbe->add(sum1, sum1, P_TwoIter[k][l]);
					}
					if (M_B[l][j] == 1)
					{
						if (P_TwoIter[k].find(l) != P_TwoIter[k].end())
							cgbe->add(sum2, sum2, P_TwoIter[k][l]);
					}
				}
				if (!(cgbe->isZero(sum1)))
					cgbe->setvalue(sum1, cipher_one);
				else
					cgbe->setvalue(sum1, cipher_zero);

				if (!(cgbe->isZero(sum2)))
					cgbe->setvalue(sum2, cipher_one);
				else
					cgbe->setvalue(sum2, cipher_zero);

				cgbe->add(sum1, sum1, EM_Q[i][k]);
				cgbe->add(sum2, sum2, EM_Q[k][i]);
				cgbe->mul(follow, follow, sum1);
				cgbe->mul(parent, parent, sum2);
			}

			//Replacement of Ciphertext
			for (auto it = Origin_Child[i].begin(); it != Origin_Child[i].end(); it++)
			{
				if (cgbe->isEqual(it->second, follow))
				{
					cgbe->setvalue(follow, Replace_Child[i][it->first]);
					//cout << "Child Replacement Suceed! " <<endl;
					break;
				}
			}

			for (auto it = Origin_Parent[i].begin(); it != Origin_Parent[i].end(); it++)
			{
				if (cgbe->isEqual(it->second, parent))
				{
					cgbe->setvalue(parent, Replace_Parent[i][it->first]);
					//cout << "Parent Replacement Suceed! " <<endl;
					break;
				}
			}

			cgbe->mul(P_temp[i][j], P_TwoIter[i][j], follow);
			cgbe->mul(P_temp[i][j], P_temp[i][j], parent);
		}
	}

	//Update the value of matrix P
	for (int i = 0; i < query_size; i++)
	{
		for (int j = 0; j < size_ball; j++)
		{
			//No need to compute 0 element
			if (P_TwoIter[i].find(j) == P_TwoIter[i].end())
				continue;
			cgbe->setvalue(P_TwoIter[i][j], P_temp[i][j]);
		}
	}

	//mpz_t temp;
	//mpz_init(temp);
	/*Violation Detector for the second time*/
	for (int i = 0; i < query_size; i++)
	{
		for (int j = 0; j < size_ball; j++)
		{
			//No need to compute 0 element
			if (P_TwoIter[i].find(j) == P_TwoIter[i].end())
				continue;
			cgbe->setvalue(follow, 1);
			cgbe->setvalue(parent, 1);
			for (int k = 0; k < query_size; k++)
			{
				cgbe->setvalue(sum1, 0);
				cgbe->setvalue(sum2, 0);
				for (int l = 0; l < size_ball; l++)
				{
					if (M_B[j][l] == 1)
					{
						if (P_TwoIter[k].find(l) != P_TwoIter[k].end())
							cgbe->add(sum1, sum1, P_TwoIter[k][l]);
					}
					if (M_B[l][j] == 1)
					{
						if (P_TwoIter[k].find(l) != P_TwoIter[k].end())
							cgbe->add(sum2, sum2, P_TwoIter[k][l]);
					}
				}
				//cgbe->setvalue(temp, EM_Q[i][k]);
				//cgbe->mul(temp, temp, temp);
				//cgbe->add(sum1, sum1, temp);
				cgbe->add(sum1, sum1, EM_Q_Two[i][k]);
				//cgbe->setvalue(temp, EM_Q[k][i]);
				//cgbe->mul(temp, temp, temp);
				//cgbe->add(sum2, sum2, temp);
				cgbe->add(sum2, sum2, EM_Q_Two[k][i]);
				cgbe->mul(follow, follow, sum1);
				cgbe->mul(parent, parent, sum2);
			}

			cgbe->setvalue(P_temp[i][j], follow);
			cgbe->mul(P_temp[i][j], P_temp[i][j], parent);
		}
	}

	//Update the value of matrix P
	for (int i = 0; i < query_size; i++)
	{
		for (int j = 0; j < size_ball; j++)
		{
			//No need to compute 0 element
			if (P_TwoIter[i].find(j) == P_TwoIter[i].end())
				continue;
			cgbe->setvalue(P_TwoIter[i][j], P_temp[i][j]);
		}
	}

	endTime = clock();
	this->Enc_TwoIter_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;

	////////////////////////////////////
	///////////    Result    ///////////
	////////////////////////////////////
	bool Result_flag, center_flag = false;
	for (int i = 0; i < query_size; i++)
	{
		startTime = clock();
		Result_flag = true;
		cgbe->setvalue(sum1, 0);
		for (int j = 0; j < size_ball; j++)
		{
			if (P_TwoIter[i].find(j) == P_TwoIter[i].end())
				continue;
			cgbe->add(sum1, sum1, P_TwoIter[i][j]);
		}
		endTime = clock();
		this->Enc_TwoIter_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;

		//decryption
		///////////////////////////////////////
		/////////////   Client   //////////////
		///////////////////////////////////////
		startTime = clock();
		cgbe->decryption_TwoIter(sum1, sum1);
		endTime = clock();
		this->Decrypt_TwoIter_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
		if (cgbe->isZero(sum1))
		{
			Result_flag = false;
			break;
		}

		if(P_TwoIter[i].find(center)!=P_TwoIter[i].end()){
			startTime = clock();
			cgbe->decryption_TwoIter(P_TwoIter[i][center], P_TwoIter[i][center]);
			endTime = clock();
			this->Decrypt_TwoIter_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
			if(!(cgbe->isZero(P_TwoIter[i][center]))){
				center_flag = true;
			}
		}
	}

	if (Result_flag && center_flag)
	{
		TwoIter_num++;
		this->result_EncSSim[pointer] = 1;
	//	this->result_EncSSim[pointer] = 1;
	}
	else
	{
		this->result_EncSSim[pointer] = 0;
		this->OneIterNL[pointer] = 0;
		this->EncSpecial[pointer] = 0;
	}

	mpz_clear(sum1);
	mpz_clear(sum2);
	mpz_clear(parent);
	mpz_clear(follow);
	//mpz_clear(temp);
	P_temp.clear();
}



template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::Enc_TwoIter_Random(int **M_B, Ciphertext **EM_Q, Ciphertext **EM_Q_Two, P_Row &P_TwoIter, int size_ball, int pointer, CGBE *cgbe, Ciphertext &cipher_one, Ciphertext &cipher_zero, Replace_Table &Origin_Child, Replace_Table &Replace_Child, Replace_Table &Origin_Parent, Replace_Table &Replace_Parent, int center, Ciphertext &cipher_one_Two, Ciphertext &cipher_one_Four_Vq, double portion)
{
	//"pointer" here in case of saving the result for Enc_TwoIter
	clock_t startTime, endTime;
	P_Row P_temp;
	

	//int* randomarray = new int[size_ball];
	//for(int i = 0; i < size_ball; i++)
	//	randomarray[i] = 0;
	//int count = (portion - 1)*size_ball/portion; 
	int count;
	count = size_ball - (size_ball*portion);
	count--;
	if(count < 1){
		this->result_EncSSim[pointer] = 1;
		P_temp.clear();
		return;
	}
	////////////////////another improvement
	/*
	int place;
	unordered_set<int> rarray;
		for(int i =0; i < count; i++){		
		place = rand()%size_ball;		
		while(rarray.find(place)!=rarray.end()){
			place = (place + 1)%size_ball; 
		}
		rarray.insert(place);
	}*/


	/*
	int place;	
	for(int i =0; i < count; i++){		
		place = rand()%size_ball;		
		while(randomarray[place]!=0){
			place = (place + 1)%size_ball; 
		}
		randomarray[place] = 1;
	}*/
	

	int *randomarray = new int[count];	
	int place;	
	bool flag;
	for(int i =0; i < count; i++){	
		place = rand()%size_ball;		
		flag = true;
		while(flag){
			flag = false;
			for(int j = 0; j <= i; j++){
				if(randomarray[j] == place)
					flag = true;
			}
			if(place == center) //center cannot be always equal to 1
				flag = true;
			if(flag)
				place = (place + 1)%size_ball; 
		}		
		randomarray[i] = place;
	}

	int *indicate = new int[size_ball];
	for(int i = 0; i < size_ball; i++){
		indicate[i] = 0;
	}
	for(int i = 0; i < count; i++){
		indicate[randomarray[i]] = 1;
	}


	/*For Decryption with different combined private key */
	// TwoIter .... to be determined
	cgbe->setCombinedPrivateKey_TwoIter(4 * query_size);

	/*Violation Detector for the first time*/

	mpz_t sum1, sum2, follow, parent;
	mpz_init(sum1);
	mpz_init(sum2);
	mpz_init(follow);
	mpz_init(parent);

	startTime = clock();
	for (int i = 0; i < query_size; i++)
	{
		for (int j = 0; j < size_ball; j++)
		{
			//No need to compute 0 element
			if (P_TwoIter[i].find(j) == P_TwoIter[i].end())
				continue;

			mpz_init(P_temp[i][j]);

			/*
			if (randomarray[j] == 1){
				cgbe->setvalue(P_temp[i][j], cipher_one_Two);
				continue;
			}*/
			
			/*if (rarray.find(j)!=rarray.end()){
				cgbe->setvalue(P_temp[i][j], cipher_one_Two);
				continue;
			}*/

			if(indicate[j] == 1){
				cgbe->setvalue(P_temp[i][j], cipher_one_Two);
				continue;
			}
				
			
			cgbe->setvalue(follow, 1);
			cgbe->setvalue(parent, 1);
			for (int k = 0; k < query_size; k++)
			{
				cgbe->setvalue(sum1, 0);
				cgbe->setvalue(sum2, 0);

				/*
				for (auto it = rarray.begin(); it != rarray.end(); it++)
				{
					if (M_B[j][*it] == 1)
					{
						if (P_TwoIter[k].find(*it) != P_TwoIter[k].end())
							cgbe->add(sum1, sum1, P_TwoIter[k][*it]);
					}
					if (M_B[*it][j] == 1)
					{
						if (P_TwoIter[k].find(*it) != P_TwoIter[k].end())
							cgbe->add(sum2, sum2, P_TwoIter[k][*it]);
					}
				}*/
				
				for (int l = 0; l < size_ball; l++)
				{
					if (M_B[j][l] == 1)
					{
						if (P_TwoIter[k].find(l) != P_TwoIter[k].end())
							cgbe->add(sum1, sum1, P_TwoIter[k][l]);
					}
					if (M_B[l][j] == 1)
					{
						if (P_TwoIter[k].find(l) != P_TwoIter[k].end())
							cgbe->add(sum2, sum2, P_TwoIter[k][l]);
					}
				}

				/*
				for (int l = 0; l < count; l++)
				{
					if (M_B[j][randomarray[l]] == 1)
					{
						if (P_TwoIter[k].find(randomarray[l]) != P_TwoIter[k].end())
							cgbe->add(sum1, sum1, P_TwoIter[k][randomarray[l]]);
					}
					if (M_B[randomarray[l]][j] == 1)
					{
						if (P_TwoIter[k].find(randomarray[l]) != P_TwoIter[k].end())
							cgbe->add(sum2, sum2, P_TwoIter[k][randomarray[l]]);
					}
				}*/

				if (!(cgbe->isZero(sum1)))
					cgbe->setvalue(sum1, cipher_one);
				else
					cgbe->setvalue(sum1, cipher_zero);

				if (!(cgbe->isZero(sum2)))
					cgbe->setvalue(sum2, cipher_one);
				else
					cgbe->setvalue(sum2, cipher_zero);

				cgbe->add(sum1, sum1, EM_Q[i][k]);
				cgbe->add(sum2, sum2, EM_Q[k][i]);
				cgbe->mul(follow, follow, sum1);
				cgbe->mul(parent, parent, sum2);
			}

			//Replacement of Ciphertext
			for (auto it = Origin_Child[i].begin(); it != Origin_Child[i].end(); it++)
			{
				if (cgbe->isEqual(it->second, follow))
				{
					cgbe->setvalue(follow, Replace_Child[i][it->first]);
					//cout << "Child Replacement Suceed! " <<endl;
					break;
				}
			}

			for (auto it = Origin_Parent[i].begin(); it != Origin_Parent[i].end(); it++)
			{
				if (cgbe->isEqual(it->second, parent))
				{
					cgbe->setvalue(parent, Replace_Parent[i][it->first]);
					//cout << "Parent Replacement Suceed! " <<endl;
					break;
				}
			}

			cgbe->setvalue(P_temp[i][j], follow);
			cgbe->mul(P_temp[i][j], P_temp[i][j], parent);
		}
	}




	//Update the value of matrix P
	for (int i = 0; i < query_size; i++)
	{
		for (int j = 0; j < size_ball; j++)
		{
			//No need to compute 0 element
			if (P_TwoIter[i].find(j) == P_TwoIter[i].end())
				continue;
			cgbe->setvalue(P_TwoIter[i][j], P_temp[i][j]);
		}
	}

	//mpz_t temp;
	//mpz_init(temp);
	/*Violation Detector for the second time*/
	for (int i = 0; i < query_size; i++)
	{
		for (int j = 0; j < size_ball; j++)
		{
			//No need to compute 0 element
			if (P_TwoIter[i].find(j) == P_TwoIter[i].end())
				continue;

			/*
			if (randomarray[j] == 1){
				cgbe->setvalue(P_temp[i][j], cipher_one_Four_Vq);
				continue;
			}*/
			
			/*if (rarray.find(j)!=rarray.end()){
				cgbe->setvalue(P_temp[i][j], cipher_one_Four_Vq);
				continue;
			}*/

			if(indicate[j] == 1){
				cgbe->setvalue(P_temp[i][j], cipher_one_Four_Vq);
				continue;
			}


			cgbe->setvalue(follow, 1);
			cgbe->setvalue(parent, 1);
			for (int k = 0; k < query_size; k++)
			{
				cgbe->setvalue(sum1, 0);
				cgbe->setvalue(sum2, 0);
				
				/*for (auto it = rarray.begin(); it != rarray.end(); it++)
				{
					if (M_B[j][*it] == 1)
					{
						if (P_TwoIter[k].find(*it) != P_TwoIter[k].end())
							cgbe->add(sum1, sum1, P_TwoIter[k][*it]);
					}
					if (M_B[*it][j] == 1)
					{
						if (P_TwoIter[k].find(*it) != P_TwoIter[k].end())
							cgbe->add(sum2, sum2, P_TwoIter[k][*it]);
					}
				}*/
				
				for (int l = 0; l < size_ball; l++)
				{
					if (M_B[j][l] == 1)
					{
						if (P_TwoIter[k].find(l) != P_TwoIter[k].end())
							cgbe->add(sum1, sum1, P_TwoIter[k][l]);
					}
					if (M_B[l][j] == 1)
					{
						if (P_TwoIter[k].find(l) != P_TwoIter[k].end())
							cgbe->add(sum2, sum2, P_TwoIter[k][l]);
					}
				}
				/*
				for (int l = 0; l < count; l++)
				{
					if (M_B[j][randomarray[l]] == 1)
					{
						if (P_TwoIter[k].find(randomarray[l]) != P_TwoIter[k].end())
							cgbe->add(sum1, sum1, P_TwoIter[k][randomarray[l]]);
					}
					if (M_B[randomarray[l]][j] == 1)
					{
						if (P_TwoIter[k].find(randomarray[l]) != P_TwoIter[k].end())
							cgbe->add(sum2, sum2, P_TwoIter[k][randomarray[l]]);
					}
				}*/


				//cgbe->setvalue(temp, EM_Q[i][k]);
				//cgbe->mul(temp, temp, temp);
				//cgbe->add(sum1, sum1, temp);
				cgbe->add(sum1, sum1, EM_Q_Two[i][k]);
				//cgbe->setvalue(temp, EM_Q[k][i]);
				//cgbe->mul(temp, temp, temp);
				//cgbe->add(sum2, sum2, temp);
				cgbe->add(sum2, sum2, EM_Q_Two[k][i]);
				cgbe->mul(follow, follow, sum1);
				cgbe->mul(parent, parent, sum2);
			}

			cgbe->setvalue(P_temp[i][j], follow);
			cgbe->mul(P_temp[i][j], P_temp[i][j], parent);
		}
	}

	//Update the value of matrix P
	for (int i = 0; i < query_size; i++)
	{
		for (int j = 0; j < size_ball; j++)
		{
			//No need to compute 0 element
			if (P_TwoIter[i].find(j) == P_TwoIter[i].end())
				continue;
			cgbe->setvalue(P_TwoIter[i][j], P_temp[i][j]);
		}
	}

	endTime = clock();
	this->Enc_TwoIter_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;

	////////////////////////////////////
	///////////    Result    ///////////
	////////////////////////////////////
	bool Result_flag, center_flag = false;
	for (int i = 0; i < query_size; i++)
	{
		startTime = clock();
		Result_flag = true;
		cgbe->setvalue(sum1, 0);
		for (int j = 0; j < size_ball; j++)
		{
			if (P_TwoIter[i].find(j) == P_TwoIter[i].end())
				continue;
			cgbe->add(sum1, sum1, P_TwoIter[i][j]);
		}
		endTime = clock();
		this->Enc_TwoIter_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;

		//decryption
		///////////////////////////////////////
		/////////////   Client   //////////////
		///////////////////////////////////////
		startTime = clock();
		cgbe->decryption_TwoIter(sum1, sum1);
		endTime = clock();
		this->Decrypt_TwoIter_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
		if (cgbe->isZero(sum1))
		{
			Result_flag = false;
			break;
		}

		if(P_TwoIter[i].find(center)!=P_TwoIter[i].end()){
			startTime = clock();
			cgbe->decryption_TwoIter(P_TwoIter[i][center], P_TwoIter[i][center]);
			endTime = clock();
			this->Decrypt_TwoIter_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
			if(!(cgbe->isZero(P_TwoIter[i][center]))){
				center_flag = true;
			}
		}
	}

	if (Result_flag && center_flag)
	{
		TwoIter_num++;
		this->result_EncSSim[pointer] = 1;
	//	this->result_EncSSim[pointer] = 1;
	}
	else
	{
		this->result_EncSSim[pointer] = 0;
		this->OneIterNL[pointer] = 0;
		this->EncSpecial[pointer] = 0;
	}

	mpz_clear(sum1);
	mpz_clear(sum2);
	mpz_clear(parent);
	mpz_clear(follow);
	//mpz_clear(temp);
	P_temp.clear();
	delete[] randomarray;
	delete[] indicate;
}


template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::Enc_NeighborLabel(int **M_B, Ciphertext ***EM_Q_Child, Ciphertext ***EM_Q_Parent, P_Row &P_NeighborLabel, P_Row &P_Replace, int size_ball, int pointer, CGBE *cgbe, B_Index &Graph_Index, B_Index &Graph_Index_Reverse, VLabelType *Column, Ciphertext &cipher_one, Ciphertext &cipher_zero, int center, VertexID centerNo, VertexID *Matrix_ball)
{
	if (hoplength <= 2)
		return;

	/*For Decryption with different combined private key */
	// NeighborLabel
	//cgbe->setCombinedPrivateKey_NeighborLabel(2 * (K_HOP - 1) * this->query_selected_label_size); //from 2 hop
	
	//cgbe->setCombinedPrivateKey_NeighborLabel(2 * (hoplength) * this->query_selected_label_size); //from 1 hop
	cgbe->setCombinedPrivateKey_NeighborLabel(2 *  this->query_selected_label_size);

	clock_t startTime, endTime;

	
	mpz_t sum;
	mpz_init(sum);

	////////////////////////////////////
	/////////    Index Tech    /////////
	////////////////////////////////////
	int column_size = this->query_selected_label_size;


	bool Result_flag = false, result_temp;


	for (int i = 0; i < query_size; i++)
	{
		/////////////
		//for (int j = 0; j < size_ball; j++){

			//if (P_NeighborLabel[i].find(j) == P_NeighborLabel[i].end())
				//continue;
			//No need to compute 0 element
			
			/*
			for (int l = 0; l < K_HOP; l++)
			{
				for (int m = 0; m < column_size; m++)
				{
					if (Graph_Index[l][Matrix_ball[j]].find(Column[m]) == Graph_Index[l][Matrix_ball[j]].end())
					{
						cgbe->mul(P_NeighborLabel[i][j], P_NeighborLabel[i][j], EM_Q_Child[l][i][m]);
					}
					else
					{
						cgbe->mul(P_NeighborLabel[i][j], P_NeighborLabel[i][j], cipher_one);
					}

					if (Graph_Index_Reverse[l][Matrix_ball[j]].find(Column[m]) == Graph_Index_Reverse[l][Matrix_ball[j]].end())
					{
						cgbe->mul(P_NeighborLabel[i][j], P_NeighborLabel[i][j], EM_Q_Parent[l][i][m]);
					}
					else
					{
						cgbe->mul(P_NeighborLabel[i][j], P_NeighborLabel[i][j], cipher_one);
					}
				}
			}*/



			/*****************************/
			if (P_NeighborLabel[i].find(center) == P_NeighborLabel[i].end())
				continue;
			//l = 1 for two-hop neighbor, l = 2 for three-hop neighbor
			
			result_temp = true;
			for (int l = 0; l < hoplength; l++)	//each hop
			{
				cgbe->setvalue(P_Replace[i][center], P_NeighborLabel[i][center]);
				
				startTime = clock();
				for (int m = 0; m < column_size; m++)
				{
					
					if (Graph_Index[l][centerNo].find(Column[m]) == Graph_Index[l][centerNo].end())
					{
						cgbe->mul(P_Replace[i][center], P_Replace[i][center], EM_Q_Child[l][i][m]);
					}
					else
					{
						cgbe->mul(P_Replace[i][center], P_Replace[i][center], cipher_one);
					}

					if (Graph_Index_Reverse[l][centerNo].find(Column[m]) == Graph_Index_Reverse[l][centerNo].end())
					{
						cgbe->mul(P_Replace[i][center], P_Replace[i][center], EM_Q_Parent[l][i][m]);
					}
					else
					{
						cgbe->mul(P_Replace[i][center], P_Replace[i][center], cipher_one);
					}
				}
				endTime = clock();
				this->NeighborLabel_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;



				////////////////////////////////////
				///////////    Result    ///////////
				////////////////////////////////////

				//theorectically right without overflow, but here should combine every hop but not all the hops which may lead to overflow. Revise when have time.


				startTime = clock();
				cgbe->decryption_NeighborLabel(P_Replace[i][center], P_Replace[i][center]);
				endTime = clock();
				this->Decrypt_NeighborLabel += (double)(endTime - startTime) / CLOCKS_PER_SEC;

				if ((cgbe->isZero(P_Replace[i][center])))
				{
					result_temp = false;					
				}
			}
			if(result_temp)
				Result_flag = true;		
	}

	if (Result_flag)
	{
		NeighborLabel_num++;
		//this->result_EncSSim[pointer] = 1;
	}
	else
	{
		if(this->result_EncSSim[pointer] == 1)
			NL_Improved++;
		this->result_EncSSim[pointer] = 0;
		this->OneIterNL[pointer] = 0;
		this->EncSpecial[pointer] = 0;
	}
	mpz_clear(sum);
}


template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::NLTest(int **M_B, int ***Q_Child, int ***Q_Parent, int **M_P, int size_ball, int pointer, CGBE *cgbe, B_Index &Graph_Index, B_Index &Graph_Index_Reverse, VLabelType *Column, int center, VertexID centerNo, VertexID *Matrix_ball)
{
	if (hoplength <= 2)
		return;

	/*For Decryption with different combined private key */
	// NeighborLabel
	//cgbe->setCombinedPrivateKey_NeighborLabel(2 * (K_HOP - 1) * this->query_selected_label_size); //from 2 hop
	//cgbe->setCombinedPrivateKey_NeighborLabel(2 * (hoplength -2) * this->query_selected_label_size); //from 1 hop

	clock_t startTime, endTime;

	startTime = clock();
	mpz_t sum;
	mpz_init(sum);

	////////////////////////////////////
	/////////    Index Tech    /////////
	////////////////////////////////////
	int column_size = this->query_selected_label_size;

	for (int i = 0; i < query_size; i++)
	{
			/*****************************/
			if (M_P[i][center] == 0)
				continue;
			//l = 1 for two-hop neighbor, l = 2 for three-hop neighbor
			
			for (int l = 0; l < hoplength; l++)
			{
				for (int m = 0; m < column_size; m++)
				{
					if (Graph_Index[l][centerNo].find(Column[m]) == Graph_Index[l][centerNo].end())
					{
						if(Q_Child[l][i][m] == 0)
							M_P[i][center] = 0;
					}


					if (Graph_Index_Reverse[l][centerNo].find(Column[m]) == Graph_Index_Reverse[l][centerNo].end())
					{						
						if(Q_Parent[l][i][m] == 0)
							M_P[i][center] = 0;
										
					}
				}
			}

		/////////////
		//}
		
	}

	endTime = clock();
	this->NeighborLabel_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
	////////////////////////////////////
	///////////    Result    ///////////
	////////////////////////////////////
	
	//bool Result_flag = true;
	bool Result_flag = false;

	for (int i = 0; i < query_size; i++)
	{
		/*
		startTime = clock();
		cgbe->setvalue(sum, 0);
		for (int j = 0; j < size_ball; j++)
		{
			if (P_NeighborLabel[i].find(j) == P_NeighborLabel[i].end())
				continue;
			cgbe->add(sum, sum, P_NeighborLabel[i][j]);
		}
		endTime = clock();
		this->NeighborLabel_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;



		startTime = clock();
		cgbe->decryption_NeighborLabel(sum, sum);
 		endTime = clock();
 		this->Decrypt_NeighborLabel += (double)(endTime - startTime) / CLOCKS_PER_SEC;


		if (cgbe->isZero(sum)){
			Result_flag = false;
			break;
		}*/




		//decryption
		///////////////////////////////////////
		/////////////   Client   //////////////
		///////////////////////////////////////
		
		if (M_P[i][center] != 0)
		{
			Result_flag = true;
			break;
		}
	}

	if (Result_flag)
	{
		NeighborLabel_num++;
		//this->result_EncSSim[pointer] = 1;
	}
	else
	{
		if(this->OneIterNL[pointer] == 1)
			NL_Improved++;
		this->result_EncSSim[pointer] = 0;
		this->OneIterNL[pointer] = 0;
	}
	mpz_clear(sum);
}



template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::Enc_Path(Path_Label &PathLabel, Path_Num &PathNum, Path_Index &PathIndex1, Path_Index &PathIndex2, int pointer, int **M_B, VertexID *Matrix_ball, int size_ball, CGBE *cgbe, double & Time, int center, VertexID centerNo, int pathlength)
{
	int PathLength, RevisedLengthOfM_B, TotalCantorNum;
	int decodeNum = 0;
	//VLabelType

	clock_t startTime, endTime;
	//startTime = clock();

	Ciphertext PathPruning;
	Ciphertext Result;
	Ciphertext FinalResult;
	mpz_init(PathPruning);
	mpz_init(Result);
	mpz_init(FinalResult);
	cgbe->setvalue(PathPruning, 1);
	cgbe->setvalue(Result, 1);
	cgbe->setvalue(FinalResult, 0);

	DIGRAPH<VLabelType, ELabelType>* RBall = new DIGRAPH<VLabelType, ELabelType>;
	for (int i = 0; i < size_ball; i++){
		RBall->insertVertex(Matrix_ball[i], 0);
	}

	for (auto it3 = RBall->getVLabel().begin(); it3 != RBall->getVLabel().end(); it3++){
		for(auto it4 = RBall->getVLabel().begin(); it4 != RBall->getVLabel().end(); it4 ++){
			if(it3->first == it4->first)
				continue;
			if(this->graph->isEdge(it3->first, it4->first))
				RBall->insertEdge(it3->first, it4->first, 0);
			if(this->graph->isEdge(it4->first, it3->first))
				RBall->insertEdge(it4->first, it3->first, 0);

		}
	}

	startTime = clock();
	//Save the paths of center
	unordered_map<VertexID, unordered_map<int, int>> Path_Center_Child, Path_Center_Parent;

	//Find the paths of center
	PathMatch(RBall, PathNum, Path_Center_Child, Path_Center_Parent, nullptr, RevisedLengthOfM_B, pathlength, 0, centerNo, centerNo, -1);
	endTime = clock();
	this->Path_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
	Time += (double)(endTime - startTime) * 1000 / CLOCKS_PER_SEC;




	/*
	cout << "#######################" << endl;
	cout << "#######################" << endl;

	for(auto it = Path_Center_Child.begin();it != Path_Center_Child.end(); it++){
		cout << "Vertex " << it->first <<":" << endl;
		for(auto it2 = Path_Center_Child[it->first].begin(); it2 != Path_Center_Child[it->first].end(); it2++){
			cout <<"Sum:" << it2->first<<endl;
		}

	}*/

	
	//Match
	for(auto i = this->query->getVLabel().begin();i != this->query->getVLabel().end(); i++){
		if(this->query->getVLabel(i->first) != this->graph->getVLabel(centerNo))
			continue;

		for(auto it = PathIndex1[pathlength][i->first].begin();it != PathIndex1[pathlength][i->first].end(); it++){
			startTime = clock();
			if(Path_Center_Child[centerNo].find(it->first) == Path_Center_Child[centerNo].end()){
				decodeNum++;
				cgbe->mul(PathPruning, PathPruning, PathIndex1[pathlength][i->first][it->first]);
			}
			endTime = clock();
			this->Path_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
			Time += (double)(endTime - startTime) * 1000 / CLOCKS_PER_SEC;

			if(decodeNum == 50){
				cgbe->setCombinedPrivateKey_Path(decodeNum);
				startTime = clock();
				cgbe->decryption_Path(PathPruning, PathPruning);
				if(cgbe->isZero(PathPruning))
					cgbe->mul(Result, Result, cgbe->zero);				
				cgbe->setvalue(PathPruning, 1);
				decodeNum = 0;
				endTime = clock();
				this->Decrypt_Path += (double)(endTime - startTime) / CLOCKS_PER_SEC;
			}
		}
	

		for(auto it2 = PathIndex2[pathlength][i->first].begin();it2 != PathIndex2[pathlength][i->first].end(); it2++){


			startTime = clock();
			if(Path_Center_Parent[centerNo].find(it2->first) == Path_Center_Parent[centerNo].end()){
				decodeNum++;
				cgbe->mul(PathPruning, PathPruning, PathIndex2[pathlength][i->first][it2->first]);
			}
			endTime = clock();
			this->Path_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
			Time += (double)(endTime - startTime) * 1000 / CLOCKS_PER_SEC;

			if(decodeNum == 50){
				cgbe->setCombinedPrivateKey_Path(decodeNum);
				startTime = clock();
				cgbe->decryption_Path(PathPruning, PathPruning);
				if(cgbe->isZero(PathPruning))
					cgbe->mul(Result, Result, cgbe->zero);	
				cgbe->setvalue(PathPruning, 1);
				decodeNum = 0;
				endTime = clock();
				this->Decrypt_Path += (double)(endTime - startTime) / CLOCKS_PER_SEC;
			}
		}

		cgbe->setCombinedPrivateKey_Path(decodeNum);
		startTime = clock();
		cgbe->decryption_Path(PathPruning, PathPruning);
		if(cgbe->isZero(PathPruning))
					cgbe->mul(Result, Result, cgbe->zero);	
		endTime = clock();
		this->Decrypt_Path += (double)(endTime - startTime) / CLOCKS_PER_SEC;

		cgbe->add(FinalResult, FinalResult, Result);
		cgbe->setvalue(PathPruning, 1);
		cgbe->setvalue(Result, 1);
		decodeNum = 0;
	}
	
	


	
	
	//endTime = clock();
	//this->Path_Time += (double)(endTime - startTime) / CLOCKS_PER_SEC;

	/*		Client		*/
	

	if ((cgbe->isZero(FinalResult)))
	{
		if(this->result_EncSSim[pointer] == 1)
			Path_Improved++;
		this->result_EncSSim[pointer] = 0;
		this->OneIterNL[pointer] = 0;
		this->result_Path[pointer] = 0;
		this->EncSpecial[pointer] = 0;
	}
	mpz_clear(PathPruning);
	mpz_clear(Result);
	mpz_clear(FinalResult);
	delete RBall;
}


template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::PathMatch(DIGRAPH<VLabelType, ELabelType>* RBall, Path_Num &PathNum, unordered_map<VertexID, unordered_map<int, int>> &Path_Center_Child, unordered_map<VertexID, unordered_map<int, int>> &Path_Center_Parent, VLabelType *Path, int RevisedBallSize, int PathLength, int iter, VertexID center, VertexID pointer, int point)
{
	if (iter == PathLength){
		int sum = 0;
		for(int i = 1; i < PathLength; i++){
			int temp = 1;
			for(int j = 1; j < i; j++){
				temp = temp *PathNum[PathLength][-1];
			}
		sum += temp*PathNum[PathLength][Path[i]];
		}
		if(point == 0){
			Path_Center_Child[center][sum] = 1;
		}
		if(point == 1){
			Path_Center_Parent[center][sum] = 1;
		}
		return;
	}
		

	if (iter == 0)
	{
		//for center only 2020.8.28
		//if (this->graph->getVLabel(pointer) != Path[iter])
		//	return false;			
		//if (PathMatch(RBall, Path, RevisedBallSize, PathLength, iter + 1, pointer))
		//	return true;

		//for center only 2020.8.28

		
		VLabelType *temppath1 = new VLabelType[PathLength];
		VLabelType *temppath2 = new VLabelType[PathLength];
		//for child
		temppath1[0] = this->graph->getVLabel(center);
		PathMatch(RBall, PathNum, Path_Center_Child, Path_Center_Parent, temppath1, RevisedBallSize, PathLength, iter+1, center, center, 0);


		//for parent
		temppath2[0] = this->graph->getVLabel(center);
		PathMatch(RBall, PathNum, Path_Center_Child, Path_Center_Parent, temppath2, RevisedBallSize, PathLength, iter+1, center, center, 1);

		delete[] temppath1;
		delete[] temppath2;
	}else if (iter < PathLength)
	{
		
		if(point == 0){
			for (auto it3 = RBall->getOutEdge()[pointer].begin(); it3 != RBall->getOutEdge()[pointer].end(); it3++)
			{			
				bool flag = true;
				for(int i = 0; i < iter; i++){
					if ((this->graph->getVLabel(it3->first) == Path[i])){
						flag = false;
						break;
					}
				}
				if(flag){
					Path[iter] = this->graph->getVLabel(it3->first);
					PathMatch(RBall, PathNum, Path_Center_Child, Path_Center_Parent, Path, RevisedBallSize, PathLength, iter+1, center, it3->first, 0);
				}
			}
		}


		if(point == 1){
			for (auto it4 = RBall->getInVertex()[pointer].begin(); it4 != RBall->getInVertex()[pointer].end(); it4++)
			{			
				bool flag = true;
				for(int i = 0; i < iter; i++){
					if ((this->graph->getVLabel(it4->first) == Path[i])){
						flag = false;
						break;
					}
				}
				if(flag){
					Path[iter] = this->graph->getVLabel(it4->first);
					PathMatch(RBall, PathNum, Path_Center_Child, Path_Center_Parent, Path, RevisedBallSize, PathLength, iter+1, center, it4->first, 1);
				}
			}
		}
	}
}











template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::Q_K_HOP(int ***Q, Ciphertext ***EM_Q_Child, Ciphertext ***EM_Q_Parent, int ***Q_Child, int ***Q_Parent, VLabelType *Column, CGBE *cgbe)
{

	for (int i = 1; i < hoplength; i++)
	{
		Q[i] = new int *[query_size];
		for (int j = 0; j < query_size; j++)
		{
			Q[i][j] = new int[query_size];
			for (int k = 0; k < query_size; k++)
			{
				Q[i][j][k] = 1;
			}
		}
	}



	for (int i = 1; i < hoplength; i++)
	{
		for (int j = 0; j < query_size; j++)
		{
			for (int k = 0; k < query_size; k++)
			{
				//no cycles
				//if(j==k){
				//	Q[i][j][k] = 1;
				//	continue;
				//}

				int sum_value_temp = 1;
				/*compute the neighbor hop information*/
				for (int l = 0; l < query_size; l++)
				{
					sum_value_temp *= (Q[i - 1][j][l] + Q[0][l][k]);
					if (sum_value_temp == 0)
					{
						Q[i][j][k] = 0;
					}
				}

				//cout << Q[i][j][k] << " ";
			}
			//cout << endl;
		}
		//cout << endl;
	}

	int column = this->query_selected_label_size; //actual value for column

	/*Randomly choose |K_Label| labels to build the MQ_(K_HOP)*/
	int length = this->query->VLabelSet.size();
	int *Randombit = new int[length]; 
	int location;
	if (length < K_LABEL) //use all the labels in Q
	{
		for (int i = 0; i < length; i++)
			Randombit[i] = 1;
	}
	else //use K_LABEL labels in Q
	{
		for (int i = 0; i < length; i++)
			Randombit[i] = 0;
		for (int i = 0; i < K_LABEL; i++)
		{
			location = rand() % length;
			while (Randombit[location] == 1)
				location = ((location + 1) % length);
			Randombit[location] = 1;
		}
	}

	/*obtain the randomly chosen labels of Q*/
	location = 0;
	int pointer = 0;
	for (auto it1 = this->query->VLabelSet.begin(); it1 != this->query->VLabelSet.end(); it1++)
	{
		if (Randombit[location] == 1)
		{
			Column[pointer] = *it1;
			pointer++;
		}
		location++;
	}

	for (int i = 0; i < hoplength; i++)
	{
		Q_Child[i] = new int *[query_size];
		Q_Parent[i] = new int *[query_size];
		EM_Q_Child[i] = new Ciphertext *[query_size];
		EM_Q_Parent[i] = new Ciphertext *[query_size];
		for (int j = 0; j < query_size; j++)
		{
			Q_Child[i][j] = new int [query_size];
			Q_Parent[i][j] = new int [query_size];
			EM_Q_Child[i][j] = new Ciphertext[column];
			EM_Q_Parent[i][j] = new Ciphertext[column];
			for (int k = 0; k < column; k++)
			{
				mpz_init(EM_Q_Child[i][j][k]);
				mpz_init(EM_Q_Parent[i][j][k]);
				cgbe->setvalue(EM_Q_Child[i][j][k], 1);
				cgbe->setvalue(EM_Q_Parent[i][j][k], 1);
				Q_Child[i][j][k] = 1;
				Q_Parent[i][j][k] = 1;

				for (int l = 0; l < query_size; l++)
				{

					if ((Q[i][j][l] == 1) && (Q[i][l][j] == 1)) //   \overline{M_Q}
						continue;
					if (this->query->getVLabel(this->query->matrix[l]) == Column[k])
					{
						if (Q[i][j][l] == 0){
							cgbe->setvalue(EM_Q_Child[i][j][k], cgbe->encoding);
							Q_Child[i][j][k] = 0;
						}

						if (Q[i][l][j] == 0){
							cgbe->setvalue(EM_Q_Parent[i][j][k], cgbe->encoding);
							Q_Parent[i][j][k] = 0;
						}
					}
				}
				cgbe->encrypt(EM_Q_Child[i][j][k], EM_Q_Child[i][j][k]);
				cgbe->encrypt(EM_Q_Parent[i][j][k], EM_Q_Parent[i][j][k]);
				//cout<<endl;
			}
			//cout<<"The next Matrix \n"<<endl;
		}
	}

	delete[] Randombit;
}

template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::Q_Replace_Table_Child(int ***Q, Ciphertext **EM_Q, Replace_Table &Origin, Replace_Table &Replace, CGBE *cgbe, Ciphertext &cipher_one, Ciphertext &cipher_zero, int recursion_length, int vertex, int value, Ciphertext &cipher)
{

	if (vertex == -1)
	{
		Ciphertext temp;
		mpz_init(temp);
		for (int i = 0; i < query_size; i++)
		{
			GlobalCountForBuildingReplaceTable = 0;
			cgbe->setvalue(temp, 1);
			Q_Replace_Table_Child(Q, EM_Q, Origin, Replace, cgbe, cipher_one, cipher_zero, 0, i, 1, temp);
		}
		mpz_clear(temp);
		return;
	}

	//if(recursion_length == (query_size - 1)){
	if (recursion_length == query_size)
	{
		cgbe->setvalue(Origin[vertex][GlobalCountForBuildingReplaceTable], cipher);
		if (value == 1)
			cgbe->setvalue(Replace[vertex][GlobalCountForBuildingReplaceTable], cipher_one);
		else
			cgbe->setvalue(Replace[vertex][GlobalCountForBuildingReplaceTable], cipher_zero);
		// <# for the vertex, # for the case, Ciphertext>
		GlobalCountForBuildingReplaceTable++;
		return;
	}
	else
	{
		int location;
		Ciphertext temp1, temp2;
		mpz_init(temp1);
		mpz_init(temp2);
		//if(recursion_length < vertex)
		//	location = recursion_length;
		//else
		//	location = recursion_length + 1;
		location = recursion_length;

		int temp_value;
		temp_value = value * Q[0][vertex][location];
		if (temp_value > 1)
			temp_value = 1;

		//case 0 for the location-th vertex
		cgbe->add(temp1, EM_Q[vertex][location], cipher_zero);
		//cgbe->setvalue(temp1, EM_Q[vertex][location]);
		cgbe->mul(temp1, temp1, cipher);
		Q_Replace_Table_Child(Q, EM_Q, Origin, Replace, cgbe, cipher_one, cipher_zero, (recursion_length + 1), vertex, temp_value, temp1);

		//case 1 for the location-th vertex
		cgbe->add(temp2, EM_Q[vertex][location], cipher_one);
		cgbe->mul(temp2, temp2, cipher);
		Q_Replace_Table_Child(Q, EM_Q, Origin, Replace, cgbe, cipher_one, cipher_zero, (recursion_length + 1), vertex, value * 1, temp2);

		mpz_clear(temp1);
		mpz_clear(temp2);
	}
}

template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::Q_Replace_Table_Parent(int ***Q, Ciphertext **EM_Q, Replace_Table &Origin, Replace_Table &Replace, CGBE *cgbe, Ciphertext &cipher_one, Ciphertext &cipher_zero, int recursion_length, int vertex, int value, Ciphertext &cipher)
{

	if (vertex == -1)
	{
		Ciphertext temp;
		mpz_init(temp);
		for (int i = 0; i < query_size; i++)
		{
			GlobalCountForBuildingReplaceTable = 0;
			cgbe->setvalue(temp, 1);
			Q_Replace_Table_Parent(Q, EM_Q, Origin, Replace, cgbe, cipher_one, cipher_zero, 0, i, 1, temp);
		}
		mpz_clear(temp);
		return;
	}

	//if(recursion_length == (query_size - 1)){
	if (recursion_length == query_size)
	{
		cgbe->setvalue(Origin[vertex][GlobalCountForBuildingReplaceTable], cipher);
		if (value == 1)
			cgbe->setvalue(Replace[vertex][GlobalCountForBuildingReplaceTable], cipher_one);
		else
			cgbe->setvalue(Replace[vertex][GlobalCountForBuildingReplaceTable], cipher_zero);
		// <# for the vertex, # for the case, Ciphertext>
		GlobalCountForBuildingReplaceTable++;
		return;
	}
	else
	{
		int location;
		Ciphertext temp1, temp2;
		mpz_init(temp1);
		mpz_init(temp2);
		//if(recursion_length < vertex)
		//	location = recursion_length;
		//else
		//	location = recursion_length + 1;
		location = recursion_length;

		int temp_value;
		temp_value = value * Q[0][location][vertex];
		if (temp_value > 1)
			temp_value = 1;

		//case 0 for the location-th vertex
		cgbe->add(temp1, EM_Q[location][vertex], cipher_zero);
		//cgbe->setvalue(temp1, EM_Q[location][vertex]);
		cgbe->mul(temp1, temp1, cipher);
		Q_Replace_Table_Parent(Q, EM_Q, Origin, Replace, cgbe, cipher_one, cipher_zero, (recursion_length + 1), vertex, temp_value, temp1);

		//case 1 for the location-th vertex
		cgbe->add(temp2, EM_Q[location][vertex], cipher_one);
		cgbe->mul(temp2, temp2, cipher);
		Q_Replace_Table_Parent(Q, EM_Q, Origin, Replace, cgbe, cipher_one, cipher_zero, (recursion_length + 1), vertex, value * 1, temp2);

		mpz_clear(temp1);
		mpz_clear(temp2);
	}
}

template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::ConstructBallMatrix(int **M_B, VertexID *Matrix_ball, int size)
{
	for (int i = 0; i < size; i++)
	{
		M_B[i] = new int[size];
		/*intialize matrix M_B*/
		for (int j = 0; j < size; j++)
		{
			M_B[i][j] = 0;
			if (this->graph->isEdge(Matrix_ball[i], Matrix_ball[j]))
				M_B[i][j] = 1;
		}
	}
}

template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::BuildPathIndex(Path_Label &PathLabel, Path_Num &PathNum, Path_Index &PathIndex1, Path_Index &PathIndex2, CGBE *cgbe, int pathlength, int templength, VLabelType* temppath)
{
	//intial each path
	if(templength == pathlength){
		int sum = 0;
		for(int i = 1; i < pathlength; i++){
			int temp = 1;
			for(int j = 1; j < i; j++){
				temp = temp *PathNum[pathlength][-1];
			}
			sum += temp*PathNum[pathlength][temppath[i]];
			//cout<<"Path["<<i<<"]:"<<temppath[i]<<endl;
		}
	
		for (auto it = this->query->getVLabel().begin(); it != this->query->getVLabel().end(); it++){
			bool flag = true;
			for(int k = 0; k < pathlength; k++){
				if(it->second == temppath[k]){
					flag = false;
					break;
				}
			}
			if(flag){
				mpz_init(PathIndex1[pathlength][it->first][sum]);
				cgbe->setvalue(PathIndex1[pathlength][it->first][sum], 1);
				mpz_init(PathIndex2[pathlength][it->first][sum]);
				cgbe->setvalue(PathIndex2[pathlength][it->first][sum], 1);
			}
		}
		return;
	}


	// encryption
	if(templength == -1){
		for(auto it1 = PathIndex1[pathlength].begin(); it1 != PathIndex1[pathlength].end(); it1++){
			for(auto it2 = PathIndex1[pathlength][it1->first].begin(); it2 != PathIndex1[pathlength][it1->first].end(); it2++){
				cgbe->encrypt(it2->second, it2->second);
			}
		}

		for(auto it3 = PathIndex2[pathlength].begin(); it3 != PathIndex2[pathlength].end(); it3++){
			for(auto it4 = PathIndex2[pathlength][it3->first].begin(); it4 != PathIndex2[pathlength][it3->first].end(); it4++){
				cgbe->encrypt(it4->second, it4->second);
			}
		}
		
		return;
	}



	//initial all the possible path
	if(templength == 0){
		int labelnum = 0;
		VLabelType templabel;
		for (auto it = this->query->getVLabel().begin(); it != this->query->getVLabel().end(); it++){
			templabel = it->second;
			bool flag = true;
			for(int i = 0; i < labelnum; i++){
				if(templabel == PathLabel[pathlength][i]){
					flag = false;
					break;
				}
			}
			if(flag){
				PathLabel[pathlength][labelnum] = templabel;
				PathNum[pathlength][templabel] = labelnum;
				labelnum++;				
			}
		}	

		//PathLabel[-1] = labelnum;
		PathNum[pathlength][-1] = labelnum;

		VLabelType* path = new VLabelType[pathlength];
		for(int i = 0; i < pathlength; i++){
			path[i] = -1;
		}
		for(auto it = PathLabel[pathlength].begin(); it != PathLabel[pathlength].end(); it++){
			if(it->first == -1)
				continue;
			path[0] = it->second;
			BuildPathIndex(PathLabel, PathNum, PathIndex1, PathIndex2, cgbe, pathlength, 1, path);
		}


		//for(auto it1 = PathNum.begin();it1 !=PathNum.end();it1++){
		//cout<<"Vertex " << it1->first << ": " << it1->second << endl;
		//}



		FindQueryPath(PathLabel, PathNum, PathIndex1, PathIndex2, cgbe, pathlength, 0, nullptr, 0, 0, 0);

		BuildPathIndex(PathLabel, PathNum, PathIndex1, PathIndex2, cgbe, pathlength, -1, path);
		delete[] path;
	}else{
		for(auto it2 = PathLabel[pathlength].begin(); it2 != PathLabel[pathlength].end(); it2++){
			bool flag = true;
			for(int i = 0; i < templength; i++){
				if(it2->second == temppath[i]){
					flag = false;
					break;
				}
			}
			if(flag){
				temppath[templength] = it2->second;
				BuildPathIndex(PathLabel, PathNum, PathIndex1, PathIndex2, cgbe, pathlength, templength+1, temppath);
			}
		}
	}
}


template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::FindQueryPath(Path_Label &PathLabel, Path_Num &PathNum, Path_Index &PathIndex1, Path_Index &PathIndex2, CGBE *cgbe, int pathlength, int templength, VLabelType* temppath, VertexID vertex, VertexID tempvertex, int point)
{	
	if(templength == pathlength){
		int sum = 0;
		for(int i = 1; i < pathlength; i++){
			int temp = 1;
			for(int j = 1; j < i; j++){
				temp = temp *PathNum[pathlength][-1];
			}
			sum += temp*PathNum[pathlength][temppath[i]];
		}
		if(point == 0)
			cgbe->setvalue(PathIndex1[pathlength][vertex][sum], cgbe->encoding);
		if(point == 1)
			cgbe->setvalue(PathIndex2[pathlength][vertex][sum], cgbe->encoding);
		return;
	}

	if(templength == 0){
		VLabelType* path1 = new VLabelType[pathlength]; // ?????may need two paths?
		VLabelType* path2 = new VLabelType[pathlength];
		for(int i = 0; i < pathlength; i++){
			path1[i] = -1;
			path2[i] = -1;
		}

		for(auto it = this->query->getVLabel().begin(); it != this->query->getVLabel().end(); it++){
			path1[0] = this->query->getVLabel(it->first);
			FindQueryPath(PathLabel, PathNum, PathIndex1, PathIndex2, cgbe, pathlength, 1, path1, it->first, it->first, 0);
			path2[0] = this->query->getVLabel(it->first);
			FindQueryPath(PathLabel, PathNum, PathIndex1, PathIndex2, cgbe, pathlength, 1, path2, it->first, it->first, 1);
		}
		delete[] path1;
		delete[] path2;
	}else{
		//for child path
		if(point == 0){
			for(auto it = this->query->getOutEdge()[tempvertex].begin(); it != this->query->getOutEdge()[tempvertex].end(); it++){
				bool flag = true;
				for(int i = 0; i < templength; i++){
					if(this->query->getVLabel(it->first) == temppath[i]){
						flag = false;
						break;
					}
				}
				if(flag){
					temppath[templength] = this->query->getVLabel(it->first);
					FindQueryPath(PathLabel, PathNum, PathIndex1, PathIndex2, cgbe, pathlength, templength+1, temppath, vertex, it->first, 0);
				}
			}
		}

		//for parent path
		if(point == 1){
			for(auto it = this->query->getInVertex()[tempvertex].begin(); it != this->query->getInVertex()[tempvertex].end(); it++){
				bool flag = true;
				for(int i = 0; i < templength; i++){
					if(this->query->getVLabel(it->first) == temppath[i]){
						flag = false;
						break;
					}
				}
				if(flag){
					temppath[templength] = this->query->getVLabel(it->first);
					FindQueryPath(PathLabel, PathNum, PathIndex1, PathIndex2, cgbe, pathlength, templength+1, temppath, vertex, it->first, 1);
				}				
			}
		}		
	}
}



template <class VLabelType, class ELabelType>
int StrongSimulation<VLabelType, ELabelType>::CantorExpansion(int length, int *array)
{
	int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320}; //n!
	int cnt, sum;
	sum = 0;
	for (int i = 0; i < length; i++)
	{
		cnt = 0;
		for (int j = i + 1; j < length; j++)
			if (array[j] < array[i])
				cnt++;
		sum += cnt * fac[length - i - 1];
	}
	return sum;
}

template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::CantorExpansionDecode(int length, int *array, int value)
{
	int i, j, t;
	const int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320}; //n!

	bool vis[10];
	memset(vis, 0, sizeof(vis));
	value--;
	for (i = 0; i < length; ++i)
	{
		t = value / fac[length - i - 1];
		for (j = 1; j <= length; j++)
			if (!vis[j])
			{
				if (t == 0)
					break;
				t--;
			}
		array[i] = j, vis[j] = true;
		value %= fac[length - i - 1]; //remainder
	}
}

template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>::ConstructBallIndex(B_Index &Ball_Index, B_Index &Ball_Index_Reverse, int **M_B, VertexID *Matrix_ball, int size)
{

	/*intialize matrix temp for saving the k_hop neighbors*/
	int ***temp = new int **[hoplength];
	for (int i = 1; i < hoplength; i++)
	{
		temp[i] = new int *[size];
		for (int j = 0; j < size; j++)
		{
			temp[i][j] = new int[size];
			for (int k = 0; k < size; k++)
				temp[i][j][k] = 0;
		}
	}

	for (int i = 0; i < hoplength; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				//no cycles
				//if(j == k){
				//	continue;
				//}
				if (0 < i && i < hoplength)
				{
					for (int l = 0; l < size; l++)
					{
						if (i == 1)
						{
							temp[i][j][k] += (M_B[j][l] * M_B[l][k]);
						}
						else
						{
							temp[i][j][k] += (temp[i - 1][j][l] * M_B[l][k]);
						}

						if (temp[i][j][k] > 0)
						{
							temp[i][j][k] = 1;
							if (Ball_Index[i][j].find(this->graph->getVLabel(Matrix_ball[k])) == Ball_Index[i][j].end())
							{
								Ball_Index[i][j][this->graph->getVLabel(Matrix_ball[k])] = 1;
							}

							if (Ball_Index_Reverse[i][k].find(this->graph->getVLabel(Matrix_ball[j])) == Ball_Index_Reverse[i][k].end())
							{
								Ball_Index_Reverse[i][k][this->graph->getVLabel(Matrix_ball[j])] = 1; //both parent and children
							}
						}
						else
						{
							if (temp[i][j][k] != 0)
								cout << "The ball index constructing is wrong!" << endl;
						}
					}
				}
				else
				{
					if (M_B[j][k] > 0) //The "i = 0" is used for the 1-hop
					{
						if (Ball_Index[i][j].find(this->graph->getVLabel(Matrix_ball[k])) == Ball_Index[i][j].end())
						{
							Ball_Index[i][j][this->graph->getVLabel(Matrix_ball[k])] = 1;
						}

						if (Ball_Index_Reverse[i][k].find(this->graph->getVLabel(Matrix_ball[j])) == Ball_Index_Reverse[i][k].end())
						{
							Ball_Index_Reverse[i][k][this->graph->getVLabel(Matrix_ball[j])] = 1; //both parent and children
						}
					}
					else
					{
						if (M_B[j][k] != 0)
							cout << "The ball index constructing is wrong!" << endl;
					}
				}
			}
		}
	}

	for (int i = 1; i < hoplength; i++)
	{
		for (int j = 0; j < size; j++)
			delete[] temp[i][j];
		delete[] temp[i];
	}
	delete[] temp;
}


template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>:: ConstructNLIndex(B_Index &Ball_Index, B_Index &Ball_Index_Reverse, DIGRAPH<VLabelType, ELabelType>* Ball, VertexID origin, VertexID place, int hop, unordered_map<VertexID, int>& Matrix_Ball){
	if (hop == hoplength)
		return;

	if(hop == -1){
		for (auto it1 = Ball->getVLabel().begin(); it1 != Ball->getVLabel().end(); it1++){
			for(auto it2 = Ball->getOutEdge()[it1->first].begin(); it2 != Ball->getOutEdge()[it1->first].end(); it2++){
				if (Ball_Index[0][Matrix_Ball[it1->first]].find(Ball->getVLabel(it2->first)) == Ball_Index[0][Matrix_Ball[it1->first]].end())
				{
					Ball_Index[0][Matrix_Ball[it1->first]][Ball->getVLabel(it2->first)] = 1;
				}

				if (Ball_Index_Reverse[0][Matrix_Ball[it2->first]].find(Ball->getVLabel(it1->first)) == Ball_Index_Reverse[0][Matrix_Ball[it2->first]].end())
				{
					Ball_Index_Reverse[0][Matrix_Ball[it2->first]][Ball->getVLabel(it1->first)] = 1; //both parent and children
				}
				ConstructNLIndex(Ball_Index, Ball_Index_Reverse, Ball, it1->first, it2->first, 1, Matrix_Ball);
			}
		}
	}else{
		for (auto it = Ball->getOutEdge()[place].begin(); it != Ball->getOutEdge()[place].end(); it++){
			if (Ball_Index[hop][Matrix_Ball[origin]].find(Ball->getVLabel(it->first)) == Ball_Index[hop][origin].end())
			{
				Ball_Index[hop][Matrix_Ball[origin]][Ball->getVLabel(it->first)] = 1;
			}

			if (Ball_Index_Reverse[hop][Matrix_Ball[it->first]].find(Ball->getVLabel(origin)) == Ball_Index_Reverse[hop][Matrix_Ball[it->first]].end())
			{
				Ball_Index_Reverse[hop][Matrix_Ball[it->first]][Ball->getVLabel(origin)] = 1; //both parent and children
			}
			ConstructNLIndex(Ball_Index, Ball_Index_Reverse, Ball, origin, it->first, hop+1, Matrix_Ball);
		}
	}
}

template <class VLabelType, class ELabelType>
void StrongSimulation<VLabelType, ELabelType>:: LoadNLIndex(B_Index &Graph_Index, B_Index &Graph_Index_Reverse, string Index1, string Index2){
	int hop;
	VertexID vertex;
	VLabelType label;
	char str[100];
	string temp;

	ifstream OpenFile1(Index1);
	if (!(OpenFile1.getline(str, 100))){
		cout << "The Index cannot be loaded!"<<endl;		
		return;
	}
	while (!OpenFile1.eof()) {		
		OpenFile1 >> temp;
		if(temp == "$"){
			//cout<<temp<<endl;
			OpenFile1 >> temp;
			//cout<<temp<<endl;
			hop = stol(temp);
		}else if(temp == "#"){
			OpenFile1 >> temp;
			vertex = stol(temp);
		}else{
			//cout<<temp<<endl;
			label = stol(temp);
			Graph_Index[hop][vertex][label] = 1;
		}
				
	}
	OpenFile1.close();

	ifstream OpenFile2(Index2);
	if (!(OpenFile2.getline(str, 100))){
		cout << "The Index cannot be loaded!"<<endl;
		return;
	}
	while (!OpenFile2.eof()) {
		OpenFile2 >> temp;
		if(temp == "$"){
			OpenFile2 >> temp;
			hop = stol(temp);
		}else if(temp == "#"){
			OpenFile2 >> temp;
			vertex = stol(temp);
		}else{
			label = stol(temp);
			Graph_Index_Reverse[hop][vertex][label] = 1;
		}
				
	}
	OpenFile2.close();
}




#endif
