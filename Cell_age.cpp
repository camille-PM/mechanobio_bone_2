#include "header.h"

using namespace std;

void Cell_age(short age[LATTICE_X][LATTICE_Y][LATTICE_Z])
{
   int i,j,k;
   
   for (i=0;i<LATTICE_X;i++)
   {
       for(j=0;j<LATTICE_Y;j++)
       {
           for (k=0;k<LATTICE_Z;k++)
           {
               if (age[i][j][k]!=0)
               {
                   age[i][j][k]=age[i][j][k]+1;
               }
           }
       }
   }
     
}
