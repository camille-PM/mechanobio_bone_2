#include <fstream>
#include <iostream>
#include "header.h"

using namespace std;

void Extremes_element(int extremes_element_nodes[NUMBER_ELEMS][NODES_PER_ELEM],float extremes_node_positions[NUMBER_NODES][3],int extreme_min[NUMBER_ELEMS][3],int extreme_max[NUMBER_ELEMS][3], float Global_min_extreme[3],float Global_max_extreme[3])
{
    int elem,node;
    int j; 
    float xmin,xmax,ymin,ymax,zmin,zmax;
     
    for (elem=0;elem<NUMBER_ELEMS;elem++) {
        node=extremes_element_nodes[elem][0];
        
        xmin=extremes_node_positions[node-1][0];
        xmax=extremes_node_positions[node-1][0];
        ymin=extremes_node_positions[node-1][1];
        ymax=extremes_node_positions[node-1][1];
        zmin=extremes_node_positions[node-1][2];
        zmax=extremes_node_positions[node-1][2];
         
        for (j=1;j<NODES_PER_ELEM;j++) {
            node=extremes_element_nodes[elem][j];
            if (extremes_node_positions[node-1][0]<xmin) {
                xmin=extremes_node_positions[node-1][0];
            }
            if (extremes_node_positions[node-1][0]>xmax) {
                xmax=extremes_node_positions[node-1][0];
            }
            if (extremes_node_positions[node-1][1]<ymin) {
                ymin=extremes_node_positions[node-1][1];
            }
            if (extremes_node_positions[node-1][1]>ymax) {
                ymax=extremes_node_positions[node-1][1];
            }
            if (extremes_node_positions[node-1][2]<zmin) {
                zmin=extremes_node_positions[node-1][2];
            }
            if (extremes_node_positions[node-1][2]>zmax) {
                zmax=extremes_node_positions[node-1][2];
            }
        }
         
//        cout<<"xmin: "<<xmin<<endl;
//        cout<<"xmax: "<<xmax<<endl;       
//        cout<<"ymin: "<<ymin<<endl;
//        cout<<"ymax: "<<ymax<<endl;   
//        cout<<"zmin: "<<zmin<<endl;
//        cout<<"zmax: "<<zmax<<endl;   
           
        extreme_min[elem][0]=int(((xmin-Global_min_extreme[0])/CELL_DIAMETER)+0.5); 
        extreme_min[elem][1]=int(((ymin-Global_min_extreme[1])/CELL_DIAMETER)+0.5);
        extreme_min[elem][2]=int(((zmin-Global_min_extreme[2])/CELL_DIAMETER)+0.5);
        extreme_max[elem][0]=int(((xmax-Global_min_extreme[0])/CELL_DIAMETER)+0.5);                  
        extreme_max[elem][1]=int(((ymax-Global_min_extreme[1])/CELL_DIAMETER)+0.5);
        extreme_max[elem][2]=int(((zmax-Global_min_extreme[2])/CELL_DIAMETER)+0.5);
         
//        cout<<"element: "<<elem<<endl;
//        cout<<"xmin cell: "<<extreme_min[elem][0]<<endl;
//        cout<<"xmax cell: "<<extreme_max[elem][0]<<endl;
//        cout<<"ymin cell: "<<extreme_min[elem][1]<<endl;
//        cout<<"ymax cell: "<<extreme_max[elem][1]<<endl;
//        cout<<"zmin cell: "<<extreme_min[elem][2]<<endl;
//        cout<<"zmax cell: "<<extreme_max[elem][2]<<endl;
			
    }
}
