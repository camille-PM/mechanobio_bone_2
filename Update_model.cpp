/************************************************************

    Algorithm to update material properties
         in each of the elements
 
************************************************************/

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include "header.h"

using namespace std;


void Update_model(char lattice[LATTICE_X][LATTICE_Y][LATTICE_Z], float Young_modulus_prop[NUMBER_ELEMS][NUMBER_ITERATIONS], float Poison_ratio_prop[NUMBER_ELEMS][NUMBER_ITERATIONS], 
	int t_prop,int element_local_min[NUMBER_ELEMS][3], int element_local_max[NUMBER_ELEMS][3],int lattice_point_element[LATTICE_X][LATTICE_Y][LATTICE_Z])
{    
    float* Young_mod_elem = new float[NUMBER_ELEMS];
	float* Poison_rat_elem = new float[NUMBER_ELEMS];
	int* elset_index = new int[NUMBER_ELEMS];
     
	int elem, index;
    int i,j,k;
    int imin,jmin,kmin;
    int imax,jmax,kmax;
    float total;
    float number_MSC,number_chondrocytes,number_fibroblasts,number_mature_osteoblasts;
    int count;
    int count2;
    int first_element = 923281; // first element in callus

	const int number_sets=35;
	float Young_modulus_bins[number_sets];
	array<vector<int>, number_sets> elset_content;
	
	// Define material properties defining each set (could alternatively be read from a csv file)
	Young_modulus_bins[0] = 0.21;
	Young_modulus_bins[1] = 0.35;
	Young_modulus_bins[2] = 0.5;
	Young_modulus_bins[3] = 0.7;
	Young_modulus_bins[4] = 1;
	Young_modulus_bins[5] = 1.5;
	Young_modulus_bins[6] = 2;
	Young_modulus_bins[7] = 4;
	Young_modulus_bins[8] = 6;
	Young_modulus_bins[9] = 10;
	Young_modulus_bins[10] = 30;
	Young_modulus_bins[11] = 50;
	Young_modulus_bins[12] = 80;
	Young_modulus_bins[13] = 150;
	Young_modulus_bins[14] = 250;
	Young_modulus_bins[15] = 400;
	Young_modulus_bins[16] = 600;
	Young_modulus_bins[17] = 1000;
	Young_modulus_bins[18] = 1500;
	Young_modulus_bins[19] = 2000;
	Young_modulus_bins[20] = 3000;
	Young_modulus_bins[21] = 4000;
	Young_modulus_bins[22] = 5000;
	Young_modulus_bins[23] = 6000;
	Young_modulus_bins[24] = 7000;
	Young_modulus_bins[25] = 8000;
	Young_modulus_bins[26] = 9000;
	Young_modulus_bins[27] = 10000;	
	Young_modulus_bins[28] = 11000;	
	Young_modulus_bins[29] = 12000;	
	Young_modulus_bins[30] = 13000;	
	Young_modulus_bins[31] = 14000;	
	Young_modulus_bins[32] = 15000;	
	Young_modulus_bins[33] = 16000;	
	Young_modulus_bins[34] = 17001;	

//	ostringstream f;
//	f<<"mat_prop_"<<t_prop<<".txt";
//	string name=f.str();
//	ofstream file(name.c_str(), ios::app);

    for(elem=0;elem<NUMBER_ELEMS;elem++) {
        Young_mod_elem[elem]=Poison_rat_elem[elem]=0.0;
    }
    
    // Get properties in each element and attribute to a given material type / elset no.
    for (elem=0;elem<NUMBER_ELEMS;elem++) {
            
        imin=element_local_min[elem][0];
        jmin=element_local_min[elem][1];
        kmin=element_local_min[elem][2];
        imax=element_local_max[elem][0];
        jmax=element_local_max[elem][1];
        kmax=element_local_max[elem][2];
        total=0.0;
        
        for (i=imin;i<imax;i++) {
            for (j=jmin;j<jmax;j++) {
                for (k=kmin;k<kmax;k++) {
                   if (lattice_point_element[i][j][k]==elem+1) {
                        total=total+1.0;
                   }
                }
            }
        }
                        
        if (total==0.0) {
            Young_mod_elem[elem]=0.2;
            Poison_rat_elem[elem]=0.167;
        }
        else { // Count cells
            number_MSC=number_chondrocytes=number_fibroblasts=number_mature_osteoblasts=0;
            for (i=imin;i<imax;i++) {
                for (j=jmin;j<jmax;j++) {
                    for (k=kmin;k<kmax;k++) {
                        if (lattice_point_element[i][j][k]==elem+1) {
                            switch (lattice[i][j][k]) {
                                case 2:
                                    number_mature_osteoblasts=number_mature_osteoblasts+1.0;
                                    break;
                                case 4:
                                    number_chondrocytes=number_chondrocytes+1.0;  
                                    break;
                                case 5:
                                    number_fibroblasts=number_fibroblasts+1.0; 
                                    break;    
                            }   
                        }
                    }
                }
            } //end for
         
	        Young_modulus_prop[elem][t_prop]=(number_chondrocytes*10.0/total)+(number_fibroblasts*2.0/total)
				+(number_mature_osteoblasts*17000.0/total)+((total-number_fibroblasts-number_mature_osteoblasts-number_chondrocytes)*0.2/total); 
	        Poison_ratio_prop[elem][t_prop]=(number_chondrocytes*0.167/total)+(number_fibroblasts*0.167/total)
				+(number_mature_osteoblasts*0.3/total)+((total-number_fibroblasts-number_chondrocytes-number_mature_osteoblasts)*0.167/total);
	
	        i=t_prop;         
	        count=0;
	        while (i>=0 && count<10) {
	            Young_mod_elem[elem]=Young_mod_elem[elem]+Young_modulus_prop[elem][i];
	            Poison_rat_elem[elem]=Poison_rat_elem[elem]+Poison_ratio_prop[elem][i];
	            count=count+1;
	            i=i-1;
	        }
	         
	        //added to consider change of material properties****************
	        if (count<=9) {
	            count2=10-count;
	            Young_mod_elem[elem]=Young_mod_elem[elem]+0.2*count2;
	            Poison_rat_elem[elem]=Poison_rat_elem[elem]+0.167*count2;
	        }
	        //*******************************************************************
	        
	        // Compute properties with maturation time
	        Young_mod_elem[elem]=Young_mod_elem[elem]/10;
	        Poison_rat_elem[elem]=Poison_rat_elem[elem]/10;	
        } // end else total==0.0  
        
    	// Attribute an elset no. to the element depending on mat prop
        elset_index[elem] = -1;
        for (index=number_sets-1; index>=0; index--) { // from the biggest to the smallest to optimize comparisons
        	if (Young_modulus_bins[index]>=Young_mod_elem[elem]) {
        		elset_index[elem] = index;
//        		cout << elem << " " << Young_mod_elem[elem] << " " << index << endl;
			}
		}
		if (elset_index[elem] == -1) {// no element attributed(should not happen)
			elset_index[elem] = number_sets-1; // mechanical properties higher than anything in the table
		}
		
		// Append to elset_content[i] vector
		elset_content[elset_index[elem]].push_back(elem+first_element);
//		file << elem << " " << Young_mod_elem[elem] << " " << Poison_rat_elem[elem] << " " << elset_index[elem] << endl;	
    }// end for element
//    file.close();
     
	//************* Write to file ************
	system("rm PCL_model.inp");
	system("cp Scaffold_model_1.txt PCL_model.inp"); // cp in LINUX; copy in WINDOWS
	ofstream myfile;
	myfile.open("PCL_model.inp",ios::app);
	
	for (index=0;index<number_sets;index++) {
		if (elset_content[index].size()>0) {
			// Write ELSET
			myfile << "*Elset, elset=Elset_" << index+1 << endl;
			// Write elements (16 per row)
			for (elem=0; elem < elset_content[index].size()-1; ++elem) {
				myfile << elset_content[index][elem] << ((elem+1)%16 ? "," : "\n") ; 
			}
			// Write last element
			myfile << elset_content[index][elset_content[index].size()-1] << endl;
			
			// Write section definition
			myfile << "*Solid section, elset=Elset_" << index+1 << ", material=material_" << index+1 << endl;
			myfile << "1.," << endl;
		}
	}
	
	// Append Scaffold_model_2 content (end of the input file)
	ifstream file_end;
	file_end.open("Scaffold_model_2.txt");
	myfile << file_end.rdbuf();

	file_end.close();
    myfile.close();
	
	delete[] Young_mod_elem;
	delete[] Poison_rat_elem;
	delete[] elset_index;
}
