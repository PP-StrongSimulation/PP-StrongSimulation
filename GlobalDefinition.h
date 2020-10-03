#pragma once
/*
 * GlobalDefinition.h
 *
 *  Created on: January 8, 2019
 *      Author: Lyu
 */

#ifndef GLOBALDEFINITION_H
#define GLOBALDEFINITION_H

using namespace std;
//using namespace std::tr1;


#include <assert.h>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "cgbe.h"


//#include <tr1/unordered_map>
//#include <tr1/unordered_set>
/*For VS2017*/

#include <unordered_map>
#include <unordered_set>


//typedef unsigned long ULong;
typedef int GraphID;
typedef int VertexID;
typedef int EdgeID;
typedef int Label;
typedef Label EdgeLabel;
typedef Label VertexLabel;
typedef unsigned int HashCode;
typedef unordered_map<VertexLabel, set<VertexID> > VertexLabelMap;
typedef unordered_map<VertexLabel, int> VertexLabelMapCnt;

typedef int Plaintext;
typedef mpz_t Ciphertext;


typedef unsigned int HashCode;

typedef int Algorithm;

typedef int Status;

#define     OK          (1)

#undef      ASSERT
#define     ASSERT(f)     assert((f))

#define     NO_EDGE       (-1)
#define     NO_VERTEX     (-1)
#define     NO_LABEL      (-1)
#define     INVALID_GRAPH_ID  (-1)
#define     ALGORITHM_FGINDEX   (-1)  // useless, for gspan compile
#define     FILENAME_BUFF_SIZE  (256)
#define     DEFAULT_VERTEX_NUMBER (256)
//#define     max(X,Y)      ((X) > (Y) ? : (X) : (Y);)
//#define     min(X,Y)      ((X) < (Y) ? : (X) : (Y);)
#define     DEFAULT_MAX_VCNT    (10000)

#define     MATRIX_INDEX(u,v,Vcnt)    ((u) * (Vcnt) + (v))

#define     DEFAULTMSGSIZE        2048
#define     DEFAULTRANDOM         32
#define     DEFAULALPHAFORL       0.1

#define     DEFAULTENTITYFOREACHFILE  1000000
#define     DEFAULTHETAGD             1000000
#define     DEFAULTHETAORGGD          1000000
#define     DEFAULTHETAL              1000000

#define		GRAPH_LABEL_NUMBER	50
#define 	K_HOP	3
#define 	K_LABEL 10

/**
 * edge definition
 */
class Edge {
public:
	VertexID v, w;
	EdgeID edge_id;

	EdgeLabel label;

	Edge(EdgeID edge_id = NO_EDGE, VertexID v = NO_EDGE, VertexID w = NO_EDGE,
		EdgeLabel l = NO_LABEL)
		: v(v),
		w(w),
		edge_id(edge_id),
		label(l) {
	}

	Edge(std::string s1, std::string s2) {
		v = atoi(s1.c_str());
		w = atoi(s2.c_str());
	}

	~Edge() {
	}

	bool operator ==(Edge e) {
		if (e.v == v && e.w == w)
			return true;
		else if (e.w == v && e.v == w)
			return true;

		return false;
	}

	void operator =(const Edge& e) {
		this->v = e.v;
		this->w = e.w;
		this->label = e.label;
		this->edge_id = e.edge_id;
	}
};


typedef unordered_map<Label, int> LabelCnt;
typedef unordered_map<VertexID, LabelCnt> MapLabelCnt;
typedef unordered_map<VertexID, VertexID> Map;


#endif
