#pragma once
/*
 * GlobalDefinition.h
 *
 *  Created on: January 8, 2019
 *      Author: Lyu
 */

#ifndef DIGRAPH_H_
#define DIGRAPH_H_




#include "GlobalDefinition.h"
#include <vector>

//#include <tr1/unordered_map>
/*For VS*/
#include <unordered_map>
#include <iostream>
#include <queue>
#include <fstream>
#include <string> 
#include<stdlib.h>
#include<time.h>
using namespace std;

template<class VLabelType, class ELabelType>
class DIGRAPH {
public:
	/**
	 * Adj definition.
	 */
	template<class ELableType>
	class AdjElement {
	public:
		//    VertexID v;
		EdgeID eid;
		ELableType elabel;
		/**
		 * used and initialized in EL
		 */
		bool isVisited;

		AdjElement() {
			//      v =
			//      eid = elabel = -1;
		}

		// VertexID v : can be removed?
		AdjElement(EdgeID eid, const ELableType& _elabel)
			://v(v),
			eid(eid),
			elabel(_elabel) {
		}

		~AdjElement() {

		}
	};

	/*
	 * data structures for basic operations
	 */
	typedef unordered_map<VertexID, VLabelType> VLabels;
	typedef AdjElement<ELabelType> ADJELE;
	typedef unordered_map<VertexID, ADJELE> AdjList;
	typedef unordered_map<VertexID, AdjList> OutEdge;			//for directed graph, use adjacent link
	typedef unordered_map<VertexID, bool> AdjListBool;
	typedef unordered_map<VertexID, AdjListBool> InVertex;		//record the inVertex
	typedef unordered_map<VertexID, int> MapMatrix;				//record the map for the matrix


	GraphID graphId;	//for multiple graph
	int Vcnt, Ecnt;		//vertex count && edge count
	VLabels _vlabels;  // vertex label
	OutEdge _outEdges;  // out edge list
	InVertex _inVertex;  // in vertex
	int diameter;
	VertexID e;
	MapMatrix _map;		//for the array matrix
	VLabelType* matrix;
	unordered_set<VLabelType> VLabelSet;						//record the Label set

	/*
	 * basic operations
	 */
	DIGRAPH();
	~DIGRAPH();
	void reset();


	VLabels& getVLabel();
	OutEdge& getOutEdge();
	InVertex& getInVertex();
	int getVcnt();
	int getEcnt();
	bool isVertex(VertexID v);
	bool isEdge(VertexID s, VertexID d);
	bool isLabel(const VLabelType& label);
	VLabelType& getVLabel(VertexID v);
	void insertVertex(VertexID v, const VLabelType& label);
	void insertEdge(VertexID s, VertexID d, const ELabelType& el);
	void setVLabel(VertexID v, VLabelType& label);
	void setELabel(VertexID s, VertexID d, ELabelType& el);
	ELabelType& getELabel(VertexID s, VertexID d);
	void removeEdge(VertexID s, VertexID d, bool verify = true);
	void removeAllOutEdges(VertexID s);
	void removeAllInEdges(VertexID s);
	void removeVertex(VertexID s);
	void eraseVertex(VertexID s);
	int getDegree(VertexID v);
	int getOutDegree(VertexID v);
	int getInDegree(VertexID v);
	void printGraph(ostream& out);
	void getDiameter();
	void getDNeighbor(VertexID, int, unordered_set<VertexID>&, DIGRAPH*);
	void createBall(int);
	void countBall(int);
	void getDNeighbor_without_label_check_of_query(VertexID, int, unordered_set<VertexID>&
	);
	void ConstructInducedGraph(unordered_set<VertexID>&, DIGRAPH*);


	/*
	 * Do *NOT* use the below data structures
	 */
	MapLabelCnt _outLabelCnt;
	MapLabelCnt _inLabelCnt;
	AdjListBool _vVisited;

	void initVL();
	void initVL_Random();
	void initVertexLabel(unordered_map<VertexID, VLabelType>&);
	MapMatrix& getMap();
	void initMap();
	void initEL(VertexID x);
	void initEdgeVisited();
	void constLabelCnt();
	void setVertexVisited();


};







/**
 * implementations
 */

#ifndef DEFAULT_VERTEX_NUMBER
#define DEFAULT_VERTEX_NUMBER   (256)
#endif


template<class VLabelType, class ELabelType>
typename DIGRAPH<VLabelType, ELabelType>::VLabels& DIGRAPH<VLabelType,
	ELabelType>::getVLabel() {
	return _vlabels;
}

template<class VLabelType, class ELabelType>
typename DIGRAPH<VLabelType, ELabelType>::OutEdge& DIGRAPH<VLabelType,
	ELabelType>::getOutEdge() {
	return _outEdges;
}

template<class VLabelType, class ELabelType>
typename DIGRAPH<VLabelType, ELabelType>::InVertex& DIGRAPH<VLabelType,
	ELabelType>::getInVertex() {
	return _inVertex;
}

template<class VLabelType, class ELabelType>
int DIGRAPH<VLabelType, ELabelType>::getVcnt() {
	return Vcnt;
}

template<class VLabelType, class ELabelType>
int DIGRAPH<VLabelType, ELabelType>::getEcnt() {
	return Ecnt;
}

/******************************************/

template<class VLabelType, class ELabelType>
bool DIGRAPH<VLabelType, ELabelType>::isVertex(VertexID v) {
	return (getVLabel().find(v) != getVLabel().end());
}


template<class VLabelType, class ELabelType>
bool DIGRAPH<VLabelType, ELabelType>::isEdge(VertexID s, VertexID d) {
	ASSERT(isVertex(s));
	ASSERT(isVertex(d));
	return (getOutEdge()[s].find(d) != getOutEdge()[s].end());
}


template<class VLabelType, class ELabelType>
bool DIGRAPH<VLabelType, ELabelType>::isLabel(const VLabelType& label) {
	return (VLabelSet.find(label) != VLabelSet.end());
}



template<class VLabelType, class ELabelType>
VLabelType& DIGRAPH<VLabelType, ELabelType>::getVLabel(VertexID v) {
	ASSERT(isVertex(v));
	return getVLabel()[v];
}



template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::insertVertex(VertexID v,
	const VLabelType& label) {
	if (!isVertex(v)) {
		Vcnt++;
	}
	getVLabel()[v] = label;
}



template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::insertEdge(VertexID s, VertexID d,
	const ELabelType& el) {
	Ecnt++;
	//  getOutEdge()[s][d] = AdjElement<ELabelType>(s, Ecnt, el);
	getOutEdge()[s][d] = AdjElement<ELabelType>(Ecnt, el);			//The number of edge 'Ecnt' is used as an ID for the edge.
	getInVertex()[d][s] = true;
}








template<class VLabelType, class ELabelType>
DIGRAPH<VLabelType, ELabelType>::DIGRAPH()
	: Vcnt(0),
	Ecnt(0),
	graphId(INVALID_GRAPH_ID) {
		this->matrix = NULL;
}

template<class VLabelType, class ELabelType>
DIGRAPH<VLabelType, ELabelType>::~DIGRAPH() {
	getVLabel().clear();
	getOutEdge().clear();
	getInVertex().clear();
	if(this->matrix != NULL)
		delete[] this->matrix;
	VLabelSet.clear();
}













template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::reset() {
	getVLabel().clear();
	getOutEdge().clear();
	getInVertex().clear();
	Vcnt = Ecnt = 0;
}





template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::setVLabel(VertexID v, VLabelType& label) {
	ASSERT(isVertex(v));
	getVLabel()[v] = label;
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::setELabel(VertexID s, VertexID d,
	ELabelType& el) {
	ASSERT(isEdge(s, d));
	getOutEdge()[s][d].elabel = el;
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::removeEdge(VertexID s, VertexID d,
	bool verify) {		
	if (verify)
		ASSERT(isEdge(s, d));
	Ecnt--;
	//   remove out edge
	getOutEdge()[s].erase(d);

	// remove in vertex
	getInVertex()[d].erase(s);

	// check isolated
	if (getDegree(s) == 0) {
		eraseVertex(s);
	}
	if (getDegree(d) == 0) {
		eraseVertex(d);
	}
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::removeAllOutEdges(VertexID s) {
	ASSERT(isVertex(s));

	for (typename AdjList::iterator it = getOutEdge()[s].begin();
		it != getOutEdge()[s].end(); it++) {
		VertexID d = it->first;
		// d will be isolated after removing s
		if (getDegree(d) == 1) {
			eraseVertex(d);
		}
		else {
			getInVertex()[d].erase(s);
		}
		Ecnt--;
	}
	getOutEdge().erase(s);
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::eraseVertex(VertexID s) {
	ASSERT(isVertex(s));

	getVLabel().erase(s);
	getOutEdge().erase(s);
	getInVertex().erase(s);
	Vcnt--;
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::removeVertex(VertexID s) {
	ASSERT(isVertex(s));

	removeAllOutEdges(s);
	removeAllInEdges(s);
	getVLabel().erase(s);
	Vcnt--;
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::removeAllInEdges(VertexID s) {
	ASSERT(isVertex(s));

	for (typename AdjListBool::iterator it = getInVertex()[s].begin();
		it != getInVertex()[s].end(); it++) {
		VertexID ps = it->first;

		// ps will be isolated after removing s
		if (getDegree(ps) == 1) {
			eraseVertex(ps);
		}
		else {
			getOutEdge()[ps].erase(s);
		}
		Ecnt--;
	}
	getInVertex().erase(s);
}



template<class VLabelType, class ELabelType>
ELabelType& DIGRAPH<VLabelType, ELabelType>::getELabel(VertexID s, VertexID d) {
	ASSERT(isEdge(s, d));
	return getOutEdge()[s][d].elabel;
}

template<class VLabelType, class ELabelType>
int DIGRAPH<VLabelType, ELabelType>::getInDegree(VertexID v) {
	ASSERT(isVertex(v));
	return (int)getInVertex()[v].size();
}

template<class VLabelType, class ELabelType>
int DIGRAPH<VLabelType, ELabelType>::getDegree(VertexID v) {
	ASSERT(isVertex(v));
	return (int)(getInVertex()[v].size() + getOutEdge()[v].size());
}

template<class VLabelType, class ELabelType>
int DIGRAPH<VLabelType, ELabelType>::getOutDegree(VertexID v) {
	ASSERT(isVertex(v));
	return (int)getOutEdge()[v].size();
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::printGraph(ostream& out) {
	out << "Vcnt " << "Ecnt " << endl;
	out << getVcnt() << " " << getEcnt() << " " << endl;

	out << "vid " << "vl " << "out " << "in " << endl;
	for (typename VLabels::iterator it = getVLabel().begin();
		it != getVLabel().end(); it++) {
		VertexID v = it->first;
		out << v << " " << getVLabel(v);
		out << " " << getOutDegree(v) << " " << getInDegree(v) << endl;
	}

	out << "eid " << "src " << "el " << "dest " << endl;
	for (typename VLabels::iterator it = getVLabel().begin();
		it != getVLabel().end(); it++) {
		VertexID s = it->first;
		VLabelType sl = getVLabel(s);

		for (typename AdjList::iterator it1 = getOutEdge()[s].begin();
			it1 != getOutEdge()[s].end(); it1++) {
			VertexID d = it1->first;
			VLabelType dl = getVLabel(d);

			EdgeID eid = it1->second.eid;
			ELabelType el = it1->second.elabel;

			out << eid << " " << s << " ";
			//      out << sl;
			//      out << " ";
			out << el;
			out << " " << d << " ";
			//      out << dl;
			out << endl;
		}
	}
}



/*For each vertex, count the number of all its neighbors as its label*/
template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::initVL() {
	VLabelType num=0;
	for (typename VLabels::iterator it = getVLabel().begin();
		it != getVLabel().end(); it++) {
		VertexID s = it->first;
		num = getOutDegree(s) + getInDegree(s);
		setVLabel(s, num);
		if (VLabelSet.find(num) == VLabelSet.end())
			VLabelSet.insert(num);
		//cout << "The label of vetex " << s << " is " << num << endl;	
	}
}



/*For each vertex, assign 50 labels randomly as its label*/
template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::initVL_Random() {	
	VLabelType num = 0;
	for (typename VLabels::iterator it = getVLabel().begin();
		it != getVLabel().end(); it++) {
		VertexID s = it->first;
		num = (rand()% GRAPH_LABEL_NUMBER);
		setVLabel(s, num);
		if (VLabelSet.find(num) == VLabelSet.end())
			VLabelSet.insert(num);
		//cout << "The label of vetex " << s << " is " << num << endl;	
	}
}



/*For each vertex, initial its label*/
template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::initVertexLabel(unordered_map<VertexID, VLabelType>& labelset) {
	VLabelType num = 0;
	for (typename VLabels::iterator it = labelset.begin();
		it != labelset.end(); it++) {
		VertexID s = it->first;
		num = labelset[s];
		setVLabel(s, num);
		if (VLabelSet.find(num) == VLabelSet.end())
			VLabelSet.insert(num);
		//cout << "The label of vetex " << s << " is " << num << endl;	
	}
}






template<class VLabelType, class ELabelType>
typename DIGRAPH<VLabelType, ELabelType>::MapMatrix& DIGRAPH<VLabelType, ELabelType>::getMap() {
	return _map;
}





/*initial the mapping from VertexID to the matrix number*/
template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::initMap() {
	int size = getVcnt();
	this->matrix = new VLabelType[size];
	int i = 0;
	for (typename VLabels::iterator it = getVLabel().begin();
		it != getVLabel().end(); it++) {
		VertexID s = it->first;
		getMap()[s] = i;
		this->matrix[i] = s;
		//cout << "The number of vetex " << s << " is " << i << endl;	
		i++;
		if (i == size)
			break;
	}
}





template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::constLabelCnt() {
	_outLabelCnt.clear();
	_inLabelCnt.clear();

	for (typename VLabels::iterator it = getVLabel().begin();
		it != getVLabel().end(); it++) {
		VertexID s = it->first;
		VLabelType sl = getVLabel(s);

		for (typename AdjList::iterator it1 = getOutEdge()[s].begin();
			it1 != _outEdges[s].end(); it1++) {
			VertexID d = it1->first;
			VLabelType dl = getVLabel(d);

			// out label
			if (_outLabelCnt[s].find(dl) == _outLabelCnt[s].end()) {
				_outLabelCnt[s][dl] = 1;
			}
			else {
				_outLabelCnt[s][dl]++;
			}

			// in label
			if (_inLabelCnt[d].find(sl) == _inLabelCnt[d].end()) {
				_inLabelCnt[d][sl] = 1;
			}
			else {
				_inLabelCnt[d][sl]++;
			}
		}
	}
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::setVertexVisited() {
	for (typename VLabels::iterator it = getVLabel().begin();
		it != getVLabel().end(); it++) {
		VertexID s = it->first;
		_vVisited[s] = false;
	}
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::initEdgeVisited() {
	for (typename VLabels::iterator it = getVLabel().begin();
		it != getVLabel().end(); it++) {
		VertexID s = it->first;
		for (typename AdjList::iterator it1 = getOutEdge()[s].begin();
			it1 != getOutEdge()[s].end(); it1++) {
			it1->second.isVisited = false;
		}
	}
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::initEL(VertexID x) {
	e = x;
	constLabelCnt();
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::getDiameter() {
	
	diameter = 0;
	VertexID x;

	//for each vertex x, do the BFS and find the largest value among all the undirected shortest length between x and the rest vertices  
	for (typename VLabels::iterator it = getVLabel().begin();
		it != getVLabel().end(); it++) {
		x = it->first;
		unordered_map<VertexID, int> map_hop;
		queue<VertexID> nodes;

		nodes.push(x);
		map_hop[x] = 0;

		// Begin BFS
		while (!nodes.empty()) {
			// for each node v
			VertexID v = nodes.front();
			nodes.pop();

			// for each out node u of v
			for (typename AdjList::iterator it1 = getOutEdge()[v].begin();
				it1 != getOutEdge()[v].end(); it1++) {
				VertexID u = it1->first;

				// u is visited
				if (map_hop.find(u) != map_hop.end()) {
					continue;
				}

				// add u into queue for next iteration
				nodes.push(u);
				map_hop[u] = map_hop[v] + 1;

				if (diameter < map_hop[u]) {
					diameter = map_hop[u];
				}
			}

			// for each in node u of v
			for (typename AdjListBool::iterator it2 = getInVertex()[v].begin();
				it2 != getInVertex()[v].end(); it2++) {
				VertexID u = it2->first;

				// u is visited
				if (map_hop.find(u) != map_hop.end()) {
					continue;
				}

				// add u into queue for next iteration
				nodes.push(u);
				map_hop[u] = map_hop[v] + 1;

				if (diameter < map_hop[u]) {
					diameter = map_hop[u];
				}
			}
		}
	}
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::getDNeighbor(
	VertexID s, int hops, unordered_set<VertexID>& visit_v, DIGRAPH* query) {
	
	visit_v.insert(s);
	unordered_map<VertexID, int> map_hop;
	queue<VertexID> nodes;
	nodes.push(s);
	map_hop[s] = 0;

	// for each node v
	while (!nodes.empty()) {
		VertexID v = nodes.front();
		nodes.pop();

		if (map_hop[v] == hops)
			continue;

		// for each out-node u of v
		for (typename AdjList::iterator it1 = getOutEdge()[v].begin();
			it1 != getOutEdge()[v].end(); it1++) {
			VertexID u = it1->first;

			// u is visited
			if (map_hop.find(u) != map_hop.end()) {
				continue;
			}

			// add u to next_nodes for iteration			
			if (query->isLabel(getVLabel(u))) {								//test whether the label of u is in the query
				map_hop[u] = map_hop[v] + 1;
				visit_v.insert(u);
				nodes.push(u);
			}
		}

		// for each in-node u of v
		for (typename AdjListBool::iterator it2 = getInVertex()[v].begin();
			it2 != getInVertex()[v].end(); it2++) {
			VertexID u = it2->first;

			// u is visited
			if (map_hop.find(u) != map_hop.end()) {
				continue;
			}

			// add u to next_nodes for iteration
			if (query->isLabel(getVLabel(u))) {								//test whether the label of u is in the query
				map_hop[u] = map_hop[v] + 1;
				visit_v.insert(u);
				nodes.push(u);
			}
		}
	}  // end of while
}


template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::createBall(int count) {

	for (typename VLabels::iterator it1 = this->getVLabel().begin();
		it1 != this->getVLabel().end(); it1++) {

		if (count == 0)
			break;

		string name1 = "D:\\dataset\\Ball_No_";
		string name2 = to_string(count);
		string name3 = ".txt";
		string name = name1 + name2 + name3;
		ofstream OutFile(name.c_str());



		VertexID s = it1->first;
		unordered_set<VertexID> s_neighbor;
		int l;
		VertexID t1, t2;
		int edge_num = 0;
		bool flag1=true;
		for (l = 0; l < 10; l++) {
			this->getDNeighbor_without_label_check_of_query(s, l, s_neighbor);

			//for vertex number constraint
			/*if (s_neighbor.size() > 1000) {
				s_neighbor.clear();
				break;
			}				
			if (s_neighbor.size() > 100) {
				flag1 = false;
				break;
			}*/

			//for edge number constraint
			for (unordered_set<VertexID>::iterator it1 = s_neighbor.begin();
				it1 != s_neighbor.end(); it1++) {
				t1 = *it1;
				for (unordered_set<VertexID>::iterator it2 = s_neighbor.begin();
					it2 != s_neighbor.end(); it2++) {
					t2 = *it2;
					if (t1 == t2)
						continue;
					if (this->isEdge(t1, t2))
						edge_num++;
				}				
			}
			edge_num = edge_num / 2;

			if (edge_num > 300) {
				s_neighbor.clear();
				break;
			}
			if (edge_num > 30) {
				flag1 = false;
				break;
			}


			s_neighbor.clear();
		
		}

		if (flag1)
			continue;

		cout << "The size of ball is " << s_neighbor.size() << endl;
		cout << "The number of edges in the ball is "<< edge_num << endl;

		int flag = 0;
		for (unordered_set<VertexID>::iterator it2 = s_neighbor.begin();
			it2 != s_neighbor.end(); it2++) {
			VertexID s = *it2;
			VertexID t;
			for (typename AdjList::iterator it = this->getOutEdge()[s].begin();
				it != this->getOutEdge()[s].end(); it++) {
				
				t = it->first;
				if (s_neighbor.find(t)!=s_neighbor.end()) {
					if (flag != 0)
						OutFile << endl;
					if (flag == 0)
						flag = 1;
					OutFile << s << " " << this->getVLabel(s) << endl;
					OutFile << t << " " << this->getVLabel(t) << endl;
					OutFile << s << " " << t << " " << 1 << endl;
				}
			}
		}
		s_neighbor.clear();
		OutFile.close();
		count--;
	}
}





template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::countBall(int count) {

	string name = "D:\\Ball_Count.txt";
	ofstream OutFile(name.c_str());
	OutFile << "VertexID" << " " << "Origin_Size" << " " << "Final_Size" << endl;

	for (typename VLabels::iterator it1 = this->getVLabel().begin();
		it1 != this->getVLabel().end(); it1++) {

		if (count > 0)
			count--;
		if (count == 0)
			break;

	
		VertexID s = it1->first;
		unordered_set<VertexID> s_neighbor;
		int l = 4;
		bool flag1 = true;		
		this->getDNeighbor_without_label_check_of_query(s, l, s_neighbor);



		OutFile <<s<<" "<< s_neighbor.size()<<" "<<0<< endl;

			   
		//cout << "The size of ball is " << s_neighbor.size() << endl;
				
		s_neighbor.clear();
	}
	OutFile.close();
}



template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::getDNeighbor_without_label_check_of_query(
	VertexID s, int hops, unordered_set<VertexID>& visit_v) {

	visit_v.insert(s);
	unordered_map<VertexID, int> map_hop;
	queue<VertexID> nodes;
	nodes.push(s);
	map_hop[s] = 0;

	// for each node v
	while (!nodes.empty()) {
		VertexID v = nodes.front();
		nodes.pop();

		if (map_hop[v] == hops)
			continue;

		// for each out-node u of v
		for (typename AdjList::iterator it1 = getOutEdge()[v].begin();
			it1 != getOutEdge()[v].end(); it1++) {
			VertexID u = it1->first;

			// u is visited
			if (map_hop.find(u) != map_hop.end()) {
				continue;
			}

			// add u to next_nodes for iteration			
				map_hop[u] = map_hop[v] + 1;
				visit_v.insert(u);
				nodes.push(u);
		}

		// for each in-node u of v
		for (typename AdjListBool::iterator it2 = getInVertex()[v].begin();
			it2 != getInVertex()[v].end(); it2++) {
			VertexID u = it2->first;

			// u is visited
			if (map_hop.find(u) != map_hop.end()) {
				continue;
			}

			// add u to next_nodes for iteration
				map_hop[u] = map_hop[v] + 1;
				visit_v.insert(u);
				nodes.push(u);
		}
	}  // end of while
}

template<class VLabelType, class ELabelType>
void DIGRAPH<VLabelType, ELabelType>::ConstructInducedGraph(unordered_set<VertexID>& NL, DIGRAPH* Graph){
	for (auto it = NL.begin(); it != NL.end(); it++){
			this->insertVertex(*it, Graph->getVLabel(*it));
                if(!(this->isLabel(Graph->getVLabel(*it))))
                    this->VLabelSet.insert(Graph->getVLabel(*it));
	}

	for (auto it1 = this->getVLabel().begin(); it1 != this->getVLabel().end(); it1++){
        for (auto it2 = this->getVLabel().begin(); it2 != this->getVLabel().end(); it2++){
             if(it1->first==it2->first)
                 continue;
            if(Graph->isEdge(it1->first, it2->first))
                this->insertEdge(it1->first, it2->first, 0);
        } 
    }	

}

#endif /* DIGRAPH_H_ */
