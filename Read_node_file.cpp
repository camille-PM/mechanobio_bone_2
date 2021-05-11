#include <iostream>
#include <fstream>
#include "header.h"

using namespace std;

void Read_node_file(float nodes_position[NUMBER_NODES][3])
{
    ifstream infile("node_file.txt");

    int node;
    float pos_x,pos_y,pos_z;
    char comma;
    int i,j;

    for (i=0;i<NUMBER_NODES;i++)
    {
//    	cout << i << endl;
        for (j=0;j<3;j++)
        {
            nodes_position[i][j]=999999;
        }
    }
  
    while (!infile.eof() )
    {
        infile>>node;
        infile>>comma;
        infile>>pos_x;
        nodes_position[node-1][0]=pos_x; 
        infile>>comma;
        infile>>pos_y;
        nodes_position[node-1][1]=pos_y;
        infile>>comma;
        infile>>pos_z;
        nodes_position[node-1][2]=pos_z;
        //cout<<"node: "<<node<<endl;
        //cout<<"position x: "<<nodes_position[node-1][0]<<endl;
        //cout<<"position y: "<<nodes_position[node-1][1]<<endl;
        //cout<<"position z: "<<nodes_position[node-1][2]<<endl;
        //system("PAUSE");
    }
  
    //cout<<"last node: "<<node<<endl;
    //cout<<"position x: "<<nodes_position[node-1][0]<<endl;
    //cout<<"position y: "<<nodes_position[node-1][1]<<endl;
    //cout<<"position z: "<<nodes_position[node-1][2]<<endl;
    //system("PAUSE");   
}
