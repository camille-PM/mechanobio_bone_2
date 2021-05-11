#include <cstdlib>
#include "header.h"

bool Neighbour_presence(char cell_neighbour[LATTICE_X][LATTICE_Y][LATTICE_Z], int i_source, int j_source, int k_source,
	int i_dest, int j_dest, int k_dest) {
		
	// i-1
	if (i_source!=i_dest-1 && i_dest!=0 && cell_neighbour[i_dest-1][j_dest][k_dest]>1 && cell_neighbour[i_dest-1][j_dest][k_dest]!=6) // neither empty nor MSC
		return true;
	
	// i+1
	if (i_source!=i_dest+1 && i_dest!=LATTICE_X-1 && cell_neighbour[i_dest+1][j_dest][k_dest]>1 && cell_neighbour[i_dest+1][j_dest][k_dest]!=6)
		return true;
			
	// j-1
	if (j_source!=j_dest-1 && j_dest!=0 && cell_neighbour[i_dest][j_dest-1][k_dest]>1 && cell_neighbour[i_dest][j_dest-1][k_dest]!=6)
		return true;
		
	// j+1
	if (j_source!=j_dest+1 && j_dest!=LATTICE_Y-1 && cell_neighbour[i_dest][j_dest+1][k_dest]>1 && cell_neighbour[i_dest][j_dest+1][k_dest]!=6)
		return true;
	
	// k-1
	if (k_source!=k_dest-1 && k_dest!=0 && cell_neighbour[i_dest][j_dest][k_dest-1]>1 && cell_neighbour[i_dest][j_dest][k_dest-1]!=6)
		return true;
		
	// k+1	
	if (k_source!=k_dest+1 && k_dest!=LATTICE_Z-1 && cell_neighbour[i_dest][j_dest][k_dest+1]>1 && cell_neighbour[i_dest][j_dest][k_dest+1]!=6)
		return true;	
	
	return false; // the new position has no direct neighbour
}
