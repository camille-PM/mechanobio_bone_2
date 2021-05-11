#include <fstream>
#include <iostream>
#include "header.h"

using namespace std;

// This function should be changed if the elements are not tetrahedral.

void Lattice_point_in_element (char lattice[LATTICE_X][LATTICE_Y][LATTICE_Z], int lattice_points_element[LATTICE_X][LATTICE_Y][LATTICE_Z], int element_min[NUMBER_ELEMS][3], 
	int element_max[NUMBER_ELEMS][3],float Global_min[3], float Global_max[3],float node_pos[NUMBER_NODES][3],int elem_nodes[NUMBER_ELEMS][NODES_PER_ELEM])
{
    int i,j,k;
    int elem;
    float xcoord,ycoord,zcoord;
    float face1[3][3],face2[3][3],face3[3][3],face4[3][3];
    int node;
    float s;

    for (i=0;i<LATTICE_X;i++) {
        for (j=0;j<LATTICE_Y;j++) {
            for (k=0;k<LATTICE_Z;k++) {
                // lattice[i][j][k]=88; //already initialized in main
                lattice_points_element[i][j][k]=0;
            }
        }
    }
   
   
    for (elem=0;elem<NUMBER_ELEMS;elem++)    
    {
       
        //cout<<"element: "<<elem<<endl;
        
        //Calculate the four faces of the element
                   
        //  face 1: n1,n3,n2
                   
        node=elem_nodes[elem][0];
        face1[0][0]=node_pos[node-1][0];
        face1[0][1]=node_pos[node-1][1];
        face1[0][2]=node_pos[node-1][2];

        node=elem_nodes[elem][2];
        face1[1][0]=node_pos[node-1][0];
        face1[1][1]=node_pos[node-1][1];
        face1[1][2]=node_pos[node-1][2];
                   
        node=elem_nodes[elem][1];
        face1[2][0]=node_pos[node-1][0];
        face1[2][1]=node_pos[node-1][1];
        face1[2][2]=node_pos[node-1][2];                   

                   
        //  face 2: n1,n2,n4
                   
        node=elem_nodes[elem][0];
        face2[0][0]=node_pos[node-1][0];
        face2[0][1]=node_pos[node-1][1];
        face2[0][2]=node_pos[node-1][2];

        node=elem_nodes[elem][1];
        face2[1][0]=node_pos[node-1][0];
        face2[1][1]=node_pos[node-1][1];
        face2[1][2]=node_pos[node-1][2];
                   
        node=elem_nodes[elem][3];
        face2[2][0]=node_pos[node-1][0];
        face2[2][1]=node_pos[node-1][1];
        face2[2][2]=node_pos[node-1][2];                   

        //  face 3: n1,n4,n3
                   
        node=elem_nodes[elem][0];
        face3[0][0]=node_pos[node-1][0];
        face3[0][1]=node_pos[node-1][1];
        face3[0][2]=node_pos[node-1][2];

        node=elem_nodes[elem][3];
        face3[1][0]=node_pos[node-1][0];
        face3[1][1]=node_pos[node-1][1];
        face3[1][2]=node_pos[node-1][2];
                   
        node=elem_nodes[elem][2];
        face3[2][0]=node_pos[node-1][0];
        face3[2][1]=node_pos[node-1][1];
        face3[2][2]=node_pos[node-1][2];                   

        //  face 4: n2,n3,n4
                   
        node=elem_nodes[elem][1];
        face4[0][0]=node_pos[node-1][0];
        face4[0][1]=node_pos[node-1][1];
        face4[0][2]=node_pos[node-1][2];

        node=elem_nodes[elem][2];
        face4[1][0]=node_pos[node-1][0];
        face4[1][1]=node_pos[node-1][1];
        face4[1][2]=node_pos[node-1][2];
                   
        node=elem_nodes[elem][3];
        face4[2][0]=node_pos[node-1][0];
        face4[2][1]=node_pos[node-1][1];
        face4[2][2]=node_pos[node-1][2];                   
       
       
        for (k=element_min[elem][2];k<=element_max[elem][2];k++) {
            for (j=element_min[elem][1];j<=element_max[elem][1];j++) {
                for (i=element_min[elem][0];i<=element_max[elem][0];i++) {
                   
                    //Calculate position of lattice point in global coordinates
                    xcoord=i*CELL_DIAMETER+Global_min[0];
                    ycoord=j*CELL_DIAMETER+Global_min[1];
                    zcoord=k*CELL_DIAMETER+Global_min[2];

                    if (lattice_points_element[i][j][k]==0) // if it is equal to an element number the lattice point has already been checked
                    {
                        //check if lattice point is below face 1 of the element                      
                        s=Plane_intersection(face1,xcoord,ycoord,zcoord);
                        if (s<=0) {
                            s=Plane_intersection(face2,xcoord,ycoord,zcoord);
                            if (s<=0) {
                                s=Plane_intersection(face3,xcoord,ycoord,zcoord);
                                if (s<=0) {
                                    s=Plane_intersection(face4,xcoord,ycoord,zcoord);
                                    if (s<=0) {
                                        lattice_points_element[i][j][k]=elem+1;
										lattice[i][j][k]=0; //the lattice point is inside an element (of the tissue/callus) and therefore we make free the position for a cell
										//cout<<"element: "<<elem<<endl;
										//cout<<"lattice_point: "<<i<<", "<<j<<", "<<k<<endl;
                                    }
                                }
                            }
                        }
                    }
                   //system("PAUSE");
                }
            }
        }
    //system("PAUSE");
    }//end for element
     
}
