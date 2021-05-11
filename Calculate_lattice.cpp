#include <fstream>
#include <iostream>
#include "header.h"

using namespace std;

void Calculate_lattice(int lattice_element[NUMBER_ELEMS][NODES_PER_ELEM], float lattice_node_position[NUMBER_NODES][3], float Global_min[3], float Global_max[3])
{
    float xmin,xmax;
    float ymin,ymax;
    float zmin,zmax;
    
    int x,y,z;    
    int node,element;
    int j;
    
    node=lattice_element[0][0];
      
    xmin=lattice_node_position[node-1][0];
    xmax=lattice_node_position[node-1][0];
    
    ymin=lattice_node_position[node-1][1];
    ymax=lattice_node_position[node-1][1];
    
    zmin=lattice_node_position[node-1][2];
    zmax=lattice_node_position[node-1][2];
    
    
    for (element=0;element<NUMBER_ELEMS;element++)
    {
    
        for (j=0;j<NODES_PER_ELEM;j++)
        {
            node=lattice_element[element][j];
            //cout<<"node: "<<node<<endl;
            //cout<<"position x: "<<lattice_node_position[node-1][0]<<endl;
            //cout<<"xmin: "<<xmin<<endl;
        
        
            if (lattice_node_position[node-1][0]<xmin && lattice_node_position[node-1][0]!=999999)
            {
               xmin=lattice_node_position[node-1][0];
            }
            if (lattice_node_position[node-1][0]>xmax && lattice_node_position[node-1][0]!=999999)
            {
               xmax=lattice_node_position[node-1][0];
            }
            if (lattice_node_position[node-1][1]<ymin && lattice_node_position[node-1][0]!=999999)
            {
               ymin=lattice_node_position[node-1][1];
            }
            if (lattice_node_position[node-1][1]>ymax && lattice_node_position[node-1][0]!=999999)
            {
               ymax=lattice_node_position[node-1][1];
            }
            if (lattice_node_position[node-1][2]<zmin && lattice_node_position[node-1][0]!=999999)
            {
               zmin=lattice_node_position[node-1][2];
            }
            if (lattice_node_position[node-1][2]>zmax && lattice_node_position[node-1][0]!=999999)
            {
               zmax=lattice_node_position[node-1][2];
            }
        
            //system("PAUSE");
        }
    }
    
    Global_min[0]=xmin; 
    Global_min[1]=ymin;
    Global_min[2]=zmin;
    
//    cout<<"Global minimum x: "<<Global_min[0]<<endl;
//    cout<<"Global minimum y: "<<Global_min[1]<<endl;
//    cout<<"Global minimum z: "<<Global_min[2]<<endl;
    
    Global_max[0]=xmax;
    Global_max[1]=ymax;
    Global_max[2]=zmax;

/*    cout<<"Global maximum x: "<<Global_max[0]<<endl;
    cout<<"Global maximum y: "<<Global_max[1]<<endl;
    cout<<"Global maximum z: "<<Global_max[2]<<endl;
    
    // Global lattice dimensions
    x=int(((xmax-xmin)/CELL_DIAMETER)+0.5)+1;
    y=int(((ymax-ymin)/CELL_DIAMETER)+0.5)+1;
    z=int(((zmax-zmin)/CELL_DIAMETER)+0.5)+1;
    
            
    cout<<"number cells x direction: "<<x<<endl;
    cout<<"number cells y direction: "<<y<<endl;
    cout<<"number cells z direction: "<<z<<endl; 
    system("PAUSE"); */

}
