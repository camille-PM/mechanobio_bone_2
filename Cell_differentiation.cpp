#include <cstdlib>
#include <iostream>
#include <fstream>
#include "header.h"
#include <ctime>

using namespace std;

void Cell_differentiation(char cells_dif[LATTICE_X][LATTICE_Y][LATTICE_Z],short age_dif[LATTICE_X][LATTICE_Y][LATTICE_Z],char stimulus_dif[NUMBER_ELEMS], 
	int element_local_min[NUMBER_ELEMS][3],int element_local_max[NUMBER_ELEMS][3],int lattice_point_element[LATTICE_X][LATTICE_Y][LATTICE_Z],int iter)
{
     
    /************************************************************
        			CLAES-HEIGELE STIMULUS
		If Stimulus = 5               Fibrous tissue
        If Stimulus = 4               Cartilage (endochondral ossif)        
        If Stimulus = 2        		  Bone    
		If Stimulus = 1				  Resorption      
    *************************************************************/
     
     
    int elem;
    int points;
    int i,j,k;
    int imin,imax,jmin,jmax,kmin,kmax;
    int r1,r2,r3;
    int i1,j1,k1;
    int i2,j2,k2;
    int i3,j3,k3;
    int cells_to_differentiate;
    int cells_differentiated;
    int mature_osteoblasts,chondrocytes,fibroblasts;
    const int age_mature_cell=6;
	int MSCs, to_diff, osteo_diff, chondro_diff, fibro_diff; // to store total number of MSCs and how many differentiate into each phenotype
	MSCs=to_diff=osteo_diff=chondro_diff=fibro_diff=0;
        
    int chondrocytes_apoptosis;
    int fibroblasts_apoptosis;
    int mature_osteoblasts_apoptosis;
    
    const float apoptosis_rate_osteoblasts=0.16;
    const float apoptosis_rate_chondrocytes=0.1;
    const float apoptosis_rate_fibroblasts=0.05;
    
    int chondrocytes_removed;
    int fibroblasts_removed;
    int mature_osteoblasts_removed;
    
    for (elem=0;elem<NUMBER_ELEMS;elem++)
    {
        cells_to_differentiate=0;
        cells_differentiated=0;

        mature_osteoblasts=0;
        chondrocytes=0;
        fibroblasts=0;
        
        imax=element_local_max[elem][0];
        imin=element_local_min[elem][0];
        jmax=element_local_max[elem][1];
        jmin=element_local_min[elem][1];
        kmax=element_local_max[elem][2];
        kmin=element_local_min[elem][2];
         
        for (i=imin;i<imax;i++)
        {
            for (j=jmin;j<jmax;j++)
            {
                for (k=kmin;k<kmax;k++)
                {
                    if (lattice_point_element[i][j][k]==elem+1)
                    {
                        
                        if (cells_dif[i][j][k]==1 && age_dif[i][j][k]>=age_mature_cell && Neighbour_presence(cells_dif, i,j,k,i,j,k))
                        {
                            cells_to_differentiate=cells_to_differentiate+1;
                        }
                        if (cells_dif[i][j][k]==2)
                        {
                            mature_osteoblasts=mature_osteoblasts+1;                          
                        }
                        if (cells_dif[i][j][k]==4)
                        {
                           chondrocytes=chondrocytes+1;
                        }
                        if (cells_dif[i][j][k]==5)
                        {
                           fibroblasts=fibroblasts+1;
                        }
                    }
                }
            }
        }
        
		MSCs += cells_to_differentiate;
		if (iter<ACTIVITY_MAX)
        	cells_to_differentiate=int(cells_to_differentiate*0.3);
        else
        	cells_to_differentiate=int(cells_to_differentiate*0.15); // lower activity after latency period
		to_diff += cells_to_differentiate;
        
        mature_osteoblasts_apoptosis=int(mature_osteoblasts*apoptosis_rate_osteoblasts);
        chondrocytes_apoptosis=int(chondrocytes*apoptosis_rate_chondrocytes);
        fibroblasts_apoptosis=int(fibroblasts*apoptosis_rate_fibroblasts);
        chondrocytes_removed=fibroblasts_removed=mature_osteoblasts_removed=0;
        
        /*********************************************************************************************************
                                            FIBROUS TISSUE         
        **********************************************************************************************************/
        if (stimulus_dif[elem]==5)
        {
            //cout<<"fibroblast differentiation"<<endl;                 
            //CELL APOPTOSIS
            while (chondrocytes_removed<chondrocytes_apoptosis)
            {
                //cout<<"apoptosis chondrocytes under fibroblast stimulus"<<endl;
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {                       
                    if (cells_dif[i][j][k]==4)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;   
                        chondrocytes_removed=chondrocytes_removed+1;                    
                    }
                }
            }
                  
            //CELL DIFFERENTIATION
            while (cells_differentiated<cells_to_differentiate)
            {
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==1 && age_dif[i][j][k]>=age_mature_cell && Neighbour_presence(cells_dif, i,j,k,i,j,k))
                    {
                        cells_dif[i][j][k]=5;
                        age_dif[i][j][k]=1;
                        cells_differentiated=cells_differentiated+1;
                    }                                        
                }
            }
			fibro_diff+=cells_differentiated;
        }//end stimulus fibrous tissue
        
        /*********************************************************************************************************
                                             CHONDROCYTES         
        **********************************************************************************************************/
          
        if (stimulus_dif[elem]==4)
        {
            //cout<<"cartilage differentiation"<<endl;
            //CELL APOPTOSIS
            while (fibroblasts_removed<fibroblasts_apoptosis)
            {
                //cout<<"apoptosis fibroblasts under cartilage stimulus"<<endl;
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==5)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;   
                        fibroblasts_removed=fibroblasts_removed+1;                    
                    }
                }
            }
                  
            //CELL DIFFERENTIATION
            while (cells_differentiated<cells_to_differentiate)
            {
                //cout<<"cartilage differentiation"<<endl;
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==1 && age_dif[i][j][k]>=age_mature_cell && Neighbour_presence(cells_dif, i,j,k,i,j,k))
                    {
                        cells_dif[i][j][k]=4;
                        age_dif[i][j][k]=1;
                        cells_differentiated=cells_differentiated+1;
                    }                                     
                }
            }
			chondro_diff+=cells_differentiated;
                                  
        } //end stimulus chondrocyte
                 
        /*********************************************************************************************************
                                             MATURE BONE         
        **********************************************************************************************************/                  
        if (stimulus_dif[elem]==2)
        {
            //cout<<"mature bone differentiation"<<endl;                    
            //CELL APOPTOSIS
            while (fibroblasts_removed<fibroblasts_apoptosis)
            {
                       
                //cout<<"fibroblast apoptosis under mature bone stimulus"<<endl;                    
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==5)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;   
                        fibroblasts_removed=fibroblasts_removed+1;                    
                    }                                         
                }
            }

            while (chondrocytes_removed<chondrocytes_apoptosis)
            {
                //cout<<"chondrocytes apoptosis under mature bone stimulus"<<endl; 
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==4)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;
                        chondrocytes_removed=chondrocytes_removed+1;                    
                    }                                             
                }
            }        
     
            //CELL DIFFERENTIATION
            while (cells_differentiated<cells_to_differentiate)
            {
                r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==1 && age_dif[i][j][k]>=age_mature_cell && Neighbour_presence(cells_dif, i,j,k,i,j,k))
                    {
                        cells_dif[i][j][k]=2;
                        age_dif[i][j][k]=1;
                        cells_differentiated=cells_differentiated+1;
                    }
                }// end if         
            }
			osteo_diff+=cells_differentiated;			
        } //end stimulus mature osteoblasts

        /*********************************************************************************************************
                                             BONE RESORPTION      
        **********************************************************************************************************/        
        if (stimulus_dif[elem]==1)
        {
                //CELL APOPTOSIS
            //cout<<"bone resorption"<<endl;

            while (fibroblasts_removed<fibroblasts_apoptosis)
            {
	            r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
            	i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==5)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;   
                        fibroblasts_removed=fibroblasts_removed+1;                    
                    }                                      
                }
            }
              
            while (chondrocytes_removed<chondrocytes_apoptosis)
            {
            	//cout<<"apoptosis chondrocytes under fibroblast stimulus"<<endl;
	            r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {                       
                    if (cells_dif[i][j][k]==4)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;   
                        chondrocytes_removed=chondrocytes_removed+1;                    
                    }
                }
            }

            while (mature_osteoblasts_removed<mature_osteoblasts_apoptosis)
            {
	            r1=nrand(imax-imin+1); //r1=rand()%(imax-imin+1);
                r2=nrand(jmax-jmin+1); //r2=rand()%(jmax-jmin+1);
                r3=nrand(kmax-kmin+1); //r3=rand()%(kmax-kmin+1);
                i=imin+r1;
                j=jmin+r2;
                k=kmin+r3;
                if (lattice_point_element[i][j][k]==elem+1)
                {
                    if (cells_dif[i][j][k]==2)
                    {
                        cells_dif[i][j][k]=0;
                        age_dif[i][j][k]=0;   
                        mature_osteoblasts_removed=mature_osteoblasts_removed+1;                    
                    } 
                }
        	} 
        }//end for bone resorption
	        // system("PAUSE");
    }// end for element
	
	// Write differentiation info to a file
    ofstream myfile;
	myfile.open("differentiation.txt", ios::app); // total number of MSCs, how many should differentiation, then differentiation in following order: osteoblasts, chondrocytes, fibroblasts
	myfile << MSCs << " " << to_diff << " " << osteo_diff << " " << chondro_diff << " " << fibro_diff << endl;
	myfile.close();
} 
