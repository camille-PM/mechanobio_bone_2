#include <iostream>
#include <fstream>
#include "header.h"

using namespace std;    


void Read_element_file(int nodes_element[NUMBER_ELEMS][NODES_PER_ELEM])
{           

    ifstream infile("element_file.txt");
 	int element;
    int node; 	
    char comma;
    int i;
	int j;
        
 	for (i=0;i<NUMBER_ELEMS;i++)
    {   
        infile>>element;
                
        for(j=0;j<NODES_PER_ELEM;j++)
        {
           infile>>comma;
           infile>>node;
           nodes_element[i][j]=node;
           //cout<<"node: "<<nodes_element[i][j]<<endl;
        }
        //system("PAUSE");
                        
    } 
    //cout<<"last node: "<<nodes_element[i-1][0]<<endl;
    //cout<<"last node: "<<nodes_element[i-1][9]<<endl;
    //system("PAUSE");
}
