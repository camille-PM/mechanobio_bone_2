#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <string>
#include "header.h"

using namespace std;

void Read_stimulus(char stimulus_read[NUMBER_ELEMS],int elements_read[NUMBER_ELEMS][NODES_PER_ELEM])
{
    int elem;
    float min_E_read;
    float HP_read;
   
    ifstream infile("PCL_model.dat");
	string temp;
 	string line;
   
    infile>>temp;
    
    while (temp!="FOOT-")
    {
    	infile>>temp;
    }
    getline (infile,line);
    getline (infile,line);
    getline (infile,line);
    infile>>temp; //first element
    //cout<<"element: "<<temp<<endl;

    float a,b,c,d,e,f;
    int j;
    
    for (elem=0;elem<NUMBER_ELEMS;elem++) 
    {
        min_E_read=0; // min ppal strain
        HP_read=0; // hydrostatic stress
        a=b=c=d=e=f=0;
        
        infile>>temp;  //node
        infile>>a;     //e1
        //cout<<"E11: "<<a<<endl;
        infile>>b;     //e2
        infile>>c;     //e3
        infile>>d; // s1
        infile>>e; // s2
        infile>>f;  // s3
        
        min_E_read = a;
        HP_read = -(d+e+f)/3;
        
        infile>>temp;  //next element      
        //system("PAUSE");
        
        // Define stimulus
        if (abs(HP_read)<0.0016 && abs(min_E_read)<0.0004) { // 0.04%; alternative for HP: 0.0016 MPa instead of 0.15 MPa.
        	stimulus_read[elem]=1;
		}
		else {
	        if (abs(HP_read)<0.15 && abs(min_E_read)<0.05) {
	        	stimulus_read[elem]=2; // intramembranous
			}
			else {
				if (HP_read<-0.15 && abs(min_E_read)<0.15) {
					stimulus_read[elem]=4; // endochondral

				}
				else {
					stimulus_read[elem]=5; // fibrocartilage or connective	
				}
			}
		}
    }
    
}
