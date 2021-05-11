#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "header.h"

using namespace std;

int Jump_migration(char cell_jump[LATTICE_X][LATTICE_Y][LATTICE_Z],int i_jump, int j_jump, int k_jump,short age_jump[LATTICE_X][LATTICE_Y][LATTICE_Z], 
	int cell_number, int lattice_points_element[LATTICE_X][LATTICE_Y][LATTICE_Z], int iter)
{
    int position_occupied;
    int positioned;
    int possibilities[6];
    int r,r1;
   
    position_occupied=0;
    positioned=0;
   
    const int number_jumps=7;  // velocity = 30 micrometers/hour
	int jumps=0;
    int distance;
    distance=0;
    
    const int i0 = i_jump;
    const int j0 = j_jump;
    const int k0 = k_jump;
   
    while  (jumps<number_jumps && position_occupied<6)
    {
        position_occupied=0;
        positioned=0;  
        possibilities[0]=0;
        possibilities[1]=1;
        possibilities[2]=2;
        possibilities[3]=3;
        possibilities[4]=4;
        possibilities[5]=5;    
        //cout<<"jump: "<<jumps<<endl;
        //cout<<"i_jump,j_jump,k_jump: "<<i_jump<<" ,"<<j_jump<<" ,"<<k_jump<<endl;
      
        while (positioned==0 && position_occupied<6)
        {
            r=nrand(6);
            r1=possibilities[r];
            if (r1!=999)
            {
                if (r1==0)  //move +x
                {
                    if (i_jump==LATTICE_X-1 || cell_jump[i_jump+1][j_jump][k_jump]!=0 
						|| !Neighbour_presence(cell_jump, i_jump, j_jump, k_jump, i_jump+1, j_jump, k_jump)) // add check for neighbours in the migration process
                    {
                        position_occupied=position_occupied+1;
                        possibilities[r]=999;
                    }
                    else
                    {
                        cell_jump[i_jump+1][j_jump][k_jump]=cell_number+5;
                        cell_jump[i_jump][j_jump][k_jump]=0;
                        age_jump[i_jump+1][j_jump][k_jump]=age_jump[i_jump][j_jump][k_jump];
                        age_jump[i_jump][j_jump][k_jump]=0;
                        positioned=1;
                        jumps=jumps+1;
                        i_jump=i_jump+1;
                    }
                }
                else
                if (r1==1) //move -x
                {
                    if (i_jump==0 || cell_jump[i_jump-1][j_jump][k_jump]!=0
						|| !Neighbour_presence(cell_jump, i_jump, j_jump, k_jump, i_jump-1, j_jump, k_jump)) // add check for neighbours in the migration process                    
                    {
                        position_occupied=position_occupied+1;
                        possibilities[r]=999;
                    }
                    else
                    {
                        cell_jump[i_jump-1][j_jump][k_jump]=cell_number+5;
                        cell_jump[i_jump][j_jump][k_jump]=0;
                        age_jump[i_jump-1][j_jump][k_jump]=age_jump[i_jump][j_jump][k_jump];
                        age_jump[i_jump][j_jump][k_jump]=0;
                        positioned=1;
                        jumps=jumps+1;
                        i_jump=i_jump-1;
                    }                            
                }
                else 
                if (r1==2) //move +y
                {
                    if (j_jump==LATTICE_Y-1 || cell_jump[i_jump][j_jump+1][k_jump]!=0
                    	|| !Neighbour_presence(cell_jump, i_jump, j_jump, k_jump, i_jump, j_jump+1, k_jump))
                    {
                        position_occupied=position_occupied+1;
                        possibilities[r]=999;
                    }
                    else
                    {
                        cell_jump[i_jump][j_jump+1][k_jump]=cell_number+5;
                        cell_jump[i_jump][j_jump][k_jump]=0;
                        age_jump[i_jump][j_jump+1][k_jump]=age_jump[i_jump][j_jump][k_jump];
                        age_jump[i_jump][j_jump][k_jump]=0;
                        positioned=1;
                        jumps=jumps+1;
                        j_jump=j_jump+1;
                    }                    
                }
                else 
                if (r1==3) //move -y
                {
                    if (j_jump==0 || cell_jump[i_jump][j_jump-1][k_jump]!=0
                    	|| !Neighbour_presence(cell_jump, i_jump, j_jump, k_jump, i_jump, j_jump-1, k_jump))
                    {
                        position_occupied=position_occupied+1;
                        possibilities[r]=999;
                    }
                    else
                    {
                        cell_jump[i_jump][j_jump-1][k_jump]=cell_number+5;
                        cell_jump[i_jump][j_jump][k_jump]=0;
                        age_jump[i_jump][j_jump-1][k_jump]=age_jump[i_jump][j_jump][k_jump];
                        age_jump[i_jump][j_jump][k_jump]=0;
                        positioned=1;
                        jumps=jumps+1;
                        j_jump=j_jump-1;
                    }                    
                }
                else 
                if (r1==4) //move +z
                {
                    if (k_jump==LATTICE_Z-1 || cell_jump[i_jump][j_jump][k_jump+1]!=0
                    	|| !Neighbour_presence(cell_jump, i_jump, j_jump, k_jump, i_jump, j_jump, k_jump+1))
                    {
                        position_occupied=position_occupied+1;
                        possibilities[r]=999;
                    }
                    else
                    {
                        cell_jump[i_jump][j_jump][k_jump+1]=cell_number+5;
                        cell_jump[i_jump][j_jump][k_jump]=0;
                        age_jump[i_jump][j_jump][k_jump+1]=age_jump[i_jump][j_jump][k_jump];
                        age_jump[i_jump][j_jump][k_jump]=0;
                        positioned=1;
                        jumps=jumps+1;
                        k_jump=k_jump+1;
                    }                     
                }
                else 
                if (r1==5) //move -z
                {
                    if (k_jump==0 || cell_jump[i_jump][j_jump][k_jump-1]!=0
                    	|| !Neighbour_presence(cell_jump, i_jump, j_jump, k_jump, i_jump, j_jump, k_jump-1))
                    {
                        position_occupied=position_occupied+1;
                        possibilities[r]=999;
                    }
                    else
                    {
                        cell_jump[i_jump][j_jump][k_jump-1]=cell_number+5;
                        cell_jump[i_jump][j_jump][k_jump]=0;
                        age_jump[i_jump][j_jump][k_jump-1]=age_jump[i_jump][j_jump][k_jump];
                        age_jump[i_jump][j_jump][k_jump]=0;
                        positioned=1;
                        jumps=jumps+1;
                        k_jump=k_jump-1;
                    }                     
                }                          
            }
        }     
    }
    
    // If the cell is not anymore in the callus and not in the bone marrow, it is removed
    int a,b,h;
	h = int(5/CELL_DIAMETER)+1;
    a = int(3.75/CELL_DIAMETER)+1; // long axis bone marrow
	b = int(4.4/CELL_DIAMETER)+1; // small axis bone marrow
    if (lattice_points_element[i_jump][j_jump][k_jump]==0 && !((k_jump<h && h-k_jump<=h/3 || k_jump>=LATTICE_Z-h && k_jump-LATTICE_Z+h<h/3) && 
		(pow(i_jump-(LATTICE_X-1)/2,2)/pow(a,2)+pow(j_jump-(LATTICE_Y-1)/2,2)/pow(b,2)<=1))) {
    	cell_jump[i_jump][j_jump][k_jump] = 0;
    	age_jump[i_jump][j_jump][k_jump] = 0;
    	distance=-1; 
	}
	else {
		distance = abs(i_jump-i0) + abs(j_jump-j0) + abs(k_jump-k0);
	}
	
	return distance; // number of jumps actually taken by the cell

}
