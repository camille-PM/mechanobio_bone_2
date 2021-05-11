/************************************************************
    Algorithm to migrate cells
        7 jumps each iteration (for lattice point size 100µm)
        (30 micrometers/hour)
        MSCs only (fibroblasts possible)
************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>
#include "header.h"

using namespace std;

void Cell_migration(char cells_migration[LATTICE_X][LATTICE_Y][LATTICE_Z], short age_migration[LATTICE_X][LATTICE_Y][LATTICE_Z], 
	int lattice_points_element[LATTICE_X][LATTICE_Y][LATTICE_Z], int iter)
{
    int i,j,k;
    int cell_type;
    int MSCs=0;
    int migrated=0;
    vector<Point> indices;
    const int max_jumps = 25; // change according to simulation cases
    int jumps = 0;
    int migration_histo[max_jumps];
    for (i=0;i<max_jumps;i++) {
    	migration_histo[i] = 0;
	}
    
    // Get total number of MSCs
    int a,b,h;
	h = int(5/CELL_DIAMETER)+1;
    a = int(3.75/CELL_DIAMETER)+1; // long axis bone marrow
	b = int(4.4/CELL_DIAMETER)+1; // small axis bone marrow
    for (i=0;i<LATTICE_X;i++) {
        for (j=0;j<LATTICE_Y;j++) {
            for (k=0;k<LATTICE_Z;k++) {
                if (cells_migration[i][j][k]==1) { // it is an MSC
					if (lattice_points_element[i][j][k]!=0 || ((k<h || k>=LATTICE_Z-h) && (pow(i-(LATTICE_X-1)/2,2)/pow(a,2)+pow(j-(LATTICE_Y-1)/2,2)/pow(b,2)<=1))) { 
						// it is in an element or in the marrow cavity
						MSCs += 1;
						Point temp = {i,j,k};
						indices.push_back(temp);
					}
				}
            }
        }
    }
    
//    cout << "    Number of MSCs: " << MSCs << endl;
    random_shuffle(indices.begin(), indices.end()); // shuffle the vector of indices
    
	for(Point& p:indices) {
	    i = p.x;
	    j = p.y;
	    k = p.z;
	    
	    if (cells_migration[i][j][k]==1) {    
		    if (lattice_points_element[i][j][k]!=0 || ((k<h && h-k<=h/3 || k>=LATTICE_Z-h && k-LATTICE_Z+h<h/3) && 
				(pow(i-(LATTICE_X-1)/2,2)/pow(a,2)+pow(j-(LATTICE_Y-1)/2,2)/pow(b,2)<=1))) {  
		        //cout<<"i,j,k: "<<i<<" ,"<<j<<" ,"<<k<<endl;
		        cell_type=1;
		        jumps = Jump_migration(cells_migration,i,j,k,age_migration,cell_type,lattice_points_element, iter);
		        migrated += 1;
		        if (jumps>-1) { // add to histogram table
		        	migration_histo[jumps]++;
				}
		        //system("PAUSE");
		    }
		}
	}
	
	// Replace 6 by 1 for all migrated MSCs
    for (i=0;i<LATTICE_X;i++) {
        for (j=0;j<LATTICE_Y;j++) {
            for (k=0;k<LATTICE_Z;k++) {
                if (cells_migration[i][j][k]==6)
					cells_migration[i][j][k]=1;                      
            }
        }
    }
    
    // Write migration distribution to a file
    ofstream myfile;
	myfile.open("migration_distribution.txt", ios::app);
	for (i=0; i<max_jumps; i++) {
		myfile << migration_histo[i] << " ";
	}
	myfile << endl;
	myfile.close();
    
}
