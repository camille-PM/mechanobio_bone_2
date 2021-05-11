#include <cstdlib>        //Includes pseudo-random number generation
#include <iostream>       //To read and write data from files as input/output streams
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <cmath>
#include <math.h>
#include "header.h"


using namespace std;

void Initialize_lattice(char initial_lattice[LATTICE_X][LATTICE_Y][LATTICE_Z], short initial_age[LATTICE_X][LATTICE_Y][LATTICE_Z])
{
    int elem;
    int free_positions;
    int points=0;
    int r1,r2,r3;
    int osteoblasts_to_seed;
    int seeded_cells=0;
    int i,j,k;
    int i1,i2;
    int a, b, h; // replace with small and big axes of the ellipses  
 
    //*********************************************************************
    //          Seeding of MSCs: marrow cavity
    //********************************************************************
 	
	a = int(3.75/CELL_DIAMETER)+1;
	b = int(4.4/CELL_DIAMETER)+1;
	h = int(5/CELL_DIAMETER)+1; // 5 mm height
	
	for (i=0;i<LATTICE_X;i++) {
        for (j=0;j<LATTICE_Y;j++) {
            for (k=0;k<h/3;k+=3) { // 30% positions 
            	if (initial_lattice[i][j][h-k]==0 && pow(i-(LATTICE_X-1)/2,2)/pow(a,2)+pow(j-(LATTICE_Y-1)/2,2)/pow(b,2)<=1) { // in marrow cavity and free position
                	initial_lattice[i][j][h-k]=1; // seed one MSC with age 1
 					initial_age[i][j][h-k]=1;
 				}
 				if (initial_lattice[i][j][LATTICE_Z-h+k]==0 && pow(i-(LATTICE_X-1)/2,2)/pow(a,2)+pow(j-(LATTICE_Y-1)/2,2)/pow(b,2)<=1) { // in marrow cavity and free position
                	initial_lattice[i][j][LATTICE_Z-h+k]=1; // seed one MSC with age 1
 					initial_age[i][j][LATTICE_Z-h+k]=1;
 				}
 			}
 		}
 	}
	  
    //**********************
    //    Periosteum
    //**********************     
    
	a = int(7.5/CELL_DIAMETER);
	b = int(8.5/CELL_DIAMETER);
	h = int(5/CELL_DIAMETER)+1;
	
	for (i=0;i<LATTICE_X;i++) {
        for (j=0;j<LATTICE_Y;j++) {	 
		    for (k=0;k<h;k=k+3) { // 30% positions in h below defect
		        if (initial_lattice[i][j][h-k]==0 && pow(i-(LATTICE_X-1)/2,2)/pow(a,2)+pow(j-(LATTICE_Y-1)/2,2)/pow(b,2)>=1 && 
					pow(i-(LATTICE_X-1)/2,2)/pow(a,2)+pow(j-(LATTICE_Y-1)/2,2)/pow(b,2)<=1.05) {
		            initial_lattice[i][j][h-k]=1; // put an MSC with age 1
		            initial_age[i][j][h-k]=1;
		        }
		    }
		       
		    for (k=LATTICE_Z-h;k<LATTICE_Z;k=k+3) { // 30% positions in h above defect
		        if (initial_lattice[i][j][k]==0 && pow(i-(LATTICE_X-1)/2,2)/pow(a,2)+pow(j-(LATTICE_Y-1)/2,2)/pow(b,2)>=1 && 
					pow(i-(LATTICE_X-1)/2,2)/pow(a,2)+pow(j-(LATTICE_Y-1)/2,2)/pow(b,2)<=1.05) {
		            initial_lattice[i][j][k]=1;
		            initial_age[i][j][k]=1;
		        }
		    }
		}
	}

}
