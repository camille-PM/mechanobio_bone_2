#include <cstdlib>
#include <iostream>
#include <fstream>
#include "header.h"

/***** Function defining cell mitosis.
New position for the "new" cell is randomly chosen in the neighbourhood & checked if not occupied yet.
The "new" cell gets age 1, the "old" one keeps the same age.
*****/


using namespace std;

int Cell_mitosis(char cells_mitosis[LATTICE_X][LATTICE_Y][LATTICE_Z], int i1, int j1, int k1, int cellnumber,short age_mitosis[LATTICE_X][LATTICE_Y][LATTICE_Z])
{
    int posibilities=0;
    int max_possibilities = 6;
    int mitosis=0;
    int r,r1;
    int possibilities[6];
    int i;
    
    //srand((unsigned)time(0)); // not needed because already called in main
    
    for (i=0;i<6;i++)
    {
        possibilities[i]=i;
    }
    
    while (mitosis==0 && posibilities<max_possibilities)
    {
        r1=nrand(max_possibilities); //There are 21 possible states after mitosis
        r=possibilities[r1];
        if (r!=999)
        {         
            //******** Posibility 1 *******
            if (r==0)
            {
                if (i1==LATTICE_X-1 || cells_mitosis[i1+1][j1][k1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1+1][j1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=cellnumber+5;
                    mitosis=1;
                    age_mitosis[i1+1][j1][k1]=1;
//                    age_mitosis[i1][j1][k1]=1;
                }
            }
            //********************************
            else
            //******** Posibility 2 *********
            if (r==1)
            {
                if (i1==0 || cells_mitosis[i1-1][j1][k1]!=0)
                {
                   //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1-1][j1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=cellnumber+5;
                    mitosis=1;   
                    age_mitosis[i1-1][j1][k1]=1;
//                    age_mitosis[i1][j1][k1]=1;
                }      
            }
            //********************************
            else                        
            //******** Posibility 3 **********
            if (r==2)
            {
                if (j1==LATTICE_Y-1 || cells_mitosis[i1][j1+1][k1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1][j1+1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=cellnumber+5;
                    mitosis=1;   
                    age_mitosis[i1][j1+1][k1]=1;
//                    age_mitosis[i1][j1][k1]=1;
                }
            }
            //********************************
            else
            //****** Posibility 4 ************
            if (r==3)
            {
                if (j1==0 || cells_mitosis[i1][j1-1][k1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1][j1-1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=cellnumber+5;
                    mitosis=1;   
                    age_mitosis[i1][j1-1][k1]=1;
//                    age_mitosis[i1][j1][k1]=1;
                }
            }
            //********************************
            else
            //****** Posibility 5 ************
            if (r==4)
            {
                if (k1==LATTICE_Z-1 || cells_mitosis[i1][j1][k1+1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1][j1][k1+1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=cellnumber+5;
                    mitosis=1;   
                    age_mitosis[i1][j1][k1+1]=1;
//                    age_mitosis[i1][j1][k1]=1;
                }
            }
            //********************************
            else
            //****** Posibility 6 ************
            if (r==5)
            {
                if (k1==0 || cells_mitosis[i1][j1][k1-1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1][j1][k1-1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=cellnumber+5;
                    mitosis=1;   
                    age_mitosis[i1][j1][k1-1]=1;
//                    age_mitosis[i1][j1][k1]=1;
                }
            }
            //********************************
/*            else
            //****** Posibility 7 ************
            if (r==6)
            {
                if (i1==LATTICE_X-1 || j1==LATTICE_Y-1 || cells_mitosis[i1+1][j1][k1]!=0 || cells_mitosis[i1][j1+1][k1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1+1][j1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1+1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1+1][j1][k1]=1;
                    age_mitosis[i1][j1+1][k1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;   
    
                }
            }
            //********************************
            else
            //****** Posibility 8 ************
            if (r==7)
            {
                if (i1==LATTICE_X-1 || j1==0 || cells_mitosis[i1+1][j1][k1]!=0 || cells_mitosis[i1][j1-1][k1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1+1][j1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1-1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1+1][j1][k1]=1;
                    age_mitosis[i1][j1-1][k1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;   
                }
            }
            //********************************
            else
            //****** Posibility 9 ************
            if (r==8)
            {
                if (i1==LATTICE_X-1 || k1==LATTICE_Z-1 || cells_mitosis[i1+1][j1][k1]!=0 || cells_mitosis[i1][j1][k1+1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1+1][j1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1+1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1+1][j1][k1]=1;
                    age_mitosis[i1][j1][k1+1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;   
                }
            }
            //********************************
            else
            //****** Posibility 10 ************
            if (r==9)
            {
                if (i1==LATTICE_X-1 || k1==0 || cells_mitosis[i1+1][j1][k1]!=0 || cells_mitosis[i1][j1][k1-1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1+1][j1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1-1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1+1][j1][k1]=1;
                    age_mitosis[i1][j1][k1-1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;   
                }
            }
            //********************************
            else
            //****** Posibility 11 ************
            if (r==10)
            {
                if (i1==0 || j1==LATTICE_Y-1 || cells_mitosis[i1-1][j1][k1]!=0 || cells_mitosis[i1][j1+1][k1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1-1][j1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1+1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1-1][j1][k1]=1;
                    age_mitosis[i1][j1+1][k1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;   
                }
            }
            //********************************
            else
            //****** Posibility 12 ************
            if (r==11)
            {
                if (i1==0 || j1==0 || cells_mitosis[i1-1][j1][k1]!=0 || cells_mitosis[i1][j1-1][k1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1-1][j1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1-1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1-1][j1][k1]=1;
                    age_mitosis[i1][j1-1][k1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;                                  
               }
            }
            //********************************
            else
            //****** Posibility 13 ************
            if (r==12)
            {
                if (i1==0 || k1==LATTICE_Z-1|| cells_mitosis[i1-1][j1][k1]!=0 || cells_mitosis[i1][j1][k1+1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1-1][j1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1+1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1-1][j1][k1]=1;
                    age_mitosis[i1][j1][k1+1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;
                }
            }
            //********************************
            else
            //****** Posibility 14 ************
            if (r==13)
            {
                if (i1==0 || k1==0 || cells_mitosis[i1-1][j1][k1]!=0 || cells_mitosis[i1][j1][k1-1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1-1][j1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1-1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1-1][j1][k1]=1;
                    age_mitosis[i1][j1][k1-1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;        
                }
            }
            //********************************
            else
            //****** Posibility 15 ************
            if (r==14)
            {
                if (j1==LATTICE_Y-1 || k1==LATTICE_Z-1 || cells_mitosis[i1][j1+1][k1]!=0 || cells_mitosis[i1][j1][k1+1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1][j1+1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1+1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1][j1+1][k1]=1;
                    age_mitosis[i1][j1][k1+1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;        
                }
            }
            //********************************
            else
            //****** Posibility 16 ************
            if (r==15)
            {
                if (j1==LATTICE_Y-1 || k1==0 || cells_mitosis[i1][j1+1][k1]!=0 || cells_mitosis[i1][j1][k1-1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1][j1+1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1-1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1][j1+1][k1]=1;
                    age_mitosis[i1][j1][k1-1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;   
                }
            }
            //********************************
            else
            //****** Posibility 17 ************
            if (r==16)
            {
                if (j1==0 || k1==LATTICE_Z-1 || cells_mitosis[i1][j1-1][k1]!=0 || cells_mitosis[i1][j1][k1+1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1][j1-1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1+1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1][j1-1][k1]=1;
                    age_mitosis[i1][j1][k1+1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;   
                }
            }
            //********************************
            else
            //****** Posibility 18 ************
            if (r==17)
            {
                if (j1==0 || k1==0 || cells_mitosis[i1][j1-1][k1]!=0 || cells_mitosis[i1][j1][k1-1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1][j1-1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1-1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1][j1-1][k1]=1;
                    age_mitosis[i1][j1][k1-1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;              
                }
            }
            //********************************
            else
            //****** Posibility 19 ************
            if (r==18)
            {
                if (i1==LATTICE_X-1 || i1==0 || cells_mitosis[i1+1][j1][k1]!=0 || cells_mitosis[i1-1][j1][k1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1+1][j1][k1]=cellnumber+5;
                    cells_mitosis[i1-1][j1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1+1][j1][k1]=1;
                    age_mitosis[i1-1][j1][k1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;      
                }
            }
            //********************************
            else
            //****** Posibility 20 ************
            if (r==19)
            {
                if (j1==LATTICE_Y-1 || j1==0 || cells_mitosis[i1][j1+1][k1]!=0 || cells_mitosis[i1][j1-1][k1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1][j1+1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1-1][k1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1][j1+1][k1]=1;
                    age_mitosis[i1][j1-1][k1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;   
                }
            }
            //********************************
            else
            //****** Posibility 21 ************
            if (r==20)
            {
                if (k1==LATTICE_Z-1 || k1==0 || cells_mitosis[i1][j1][k1+1]!=0 || cells_mitosis[i1][j1][k1-1]!=0)
                {
                    //the cell is busy
                    posibilities=posibilities+1;
                    possibilities[r1]=999;
                }
                else
                {  
                    //the cell can proliferate 
                    cells_mitosis[i1][j1][k1+1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1-1]=cellnumber+5;
                    cells_mitosis[i1][j1][k1]=0;
                    age_mitosis[i1][j1][k1+1]=1;
                    age_mitosis[i1][j1][k1-1]=1;
                    age_mitosis[i1][j1][k1]=0;
                    mitosis=1;
                }
            } */
        } 
    }//end while
	return mitosis;
}//end function                                   

