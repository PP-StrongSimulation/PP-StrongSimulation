#pragma once

#ifndef PATHGENERATOR_H_
#define PATHGENERATOR_H_

#include <iostream>
#include "DIGraph.h"
#include "DataRead.h"
#include <time.h>
#include <string.h>

using namespace std;


template <class VLabelType, class ELabelType>
class PathGenerator
{
public:
    DIGRAPH<VLabelType, ELabelType>* graph_ptr;
    bool flag;
    int tempnum;
    typedef unordered_map<VertexID, VLabelType> VLabels;
	PathGenerator(DataRead<VLabelType, ELabelType> *, string, int, int, string, string);
    void BuildPath(unordered_map<int, int*>&, int, VLabelType*, int, int, VertexID);
  	~PathGenerator();
};

template <class VLabelType, class ELabelType>
PathGenerator<VLabelType, ELabelType>::PathGenerator(DataRead<VLabelType, ELabelType> *Graph, string GraphName, int pathlength, int pathnum, string No, string labelsize)
{   
    //int size[10] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    this->graph_ptr = Graph->graph_ptr;   
    VertexID root, vertex;
    int MaxNum, Number;
    string OutFileName;
    string PathName;
    string S = "Query-Slashdot/S"+ No + "-" + labelsize;
    string D = "Query-DBLP/D"+ No + "-" + labelsize;
    string T = "Query-Twitter/T"+ No + "-" + labelsize;
    if(GraphName == S)
        PathName = "Path-Slashdot/S";
    if(GraphName == D)
        PathName = "Path-DBLP/D";
    if(GraphName == T)
        PathName = "Path-Twitter/T";
    OutFileName = PathName + No + "-" + labelsize;
    cout << "The outfile name is " << OutFileName <<endl;


    unordered_map<int, VLabelType*> Path;   
    VLabelType* temppath = new VLabelType[pathlength];


    BuildPath(Path, pathlength, temppath, 0, 0, -1);        
    
   

    ofstream OutFile(OutFileName);
    OutFile << "# Undirected path: ../../PathGen-"<< No <<"\r\n";
    OutFile << "# Path " << "\r\n";
    OutFile << "# Nodes:  Edges: " <<"\r\n";
    OutFile << "# pathnum\tlabelnum\tlabel";
    int count = 0;
    for(auto it = Path.begin(); it != Path.end(); it++){
        OutFile << "\r\n" << count << "\t" << pathlength;
        for(int j = 0; j < pathlength; j++){
            OutFile << "\t" << it->second[j];
        }
        count++;
        //if(count > 5)
        //    break;
    }
    OutFile.close();
    Path.clear();
}

template <class VLabelType, class ELabelType>
void PathGenerator<VLabelType, ELabelType>::BuildPath(unordered_map<int, int*>& Path, int pathlength, VLabelType* temppath, int templength, int temp, VertexID tempvertex){

    if(templength == pathlength){
        /*
        bool test1 = true;
        for(int i = 0; i < tempnum; i++){
            bool test2 = false;   //assume that the two paths being compared are the same
            for(int j = 0; j < pathlength; j++){
                bool test3 = true; //assume there exists one label in temppath but not in existing path
                for(int k = 0; k < pathlength; k++){
                    if(temppath[j]==Path[i][k]){
                        test3 = false;
                        break;
                    }
                }
                if(test3){
                    test2 = true;
                    break;
                }               
            }
            if(!test2){
                test1 = false;
                break;
            }
        }
        if(test1){
            Path[tempnum] = new VLabelType[pathlength];
            for(int i =0; i< pathlength; i++){
                Path[tempnum][i] = temppath[i];   
            } 
            cout << "Path " << tempnum << " finished!" << endl;
            this->flag = true;
            return;
        }*/

        bool test1 = false;
        for(int i = 0; i < tempnum; i++){
            bool test2 = false;   //assume that the two paths being compared are the same
            for(int j = 0; j < pathlength; j++){
                if(temppath[j]!=Path[i][j]){
                    test2 = true;
                    break;
                }              
            }
            if(!test2){
                test1 = true;
                break;
            }
        }
        
        if(!test1){
            Path[tempnum] = new VLabelType[pathlength];
            for(int i =0; i< pathlength; i++){
                Path[tempnum][i] = temppath[i];   
            } 
            cout << "Path " << tempnum << " finished!" << endl;
            this->flag = true;
            return;
        }
            
    }else{
    if(templength == 0){
        tempnum = 0;
         

        this->flag = false;
        for(auto it = this->graph_ptr->getVLabel().begin();it != this->graph_ptr->getVLabel().end();it++){
            temppath[0] = it->second;            
            BuildPath(Path, pathlength, temppath, 1, temp, it->first);
            if(this->flag){
                this->flag = false;
                tempnum++;
            }
        }
    }else{      
        for(auto it2 = this->graph_ptr->getOutEdge()[tempvertex].begin(); it2 != this->graph_ptr->getOutEdge()[tempvertex].end(); it2++){
            VLabelType templabel = this->graph_ptr->getVLabel()[it2->first];
            bool test = false;
            for(int i = 0; i < templength; i++){
                if(templabel == temppath[i])
                    test = true;
            }
            if(test)
                continue;
            
            temppath[templength] = templabel;
            BuildPath(Path, pathlength, temppath, templength+1, temp, it2->first);
            if(this->flag){
                this->flag = false;
                tempnum++;
            }
        }
    }
    }

}

template <class VLabelType, class ELabelType>
PathGenerator<VLabelType, ELabelType>::~PathGenerator(){}

#endif