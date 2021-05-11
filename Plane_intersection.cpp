#include <fstream>
#include <iostream>

using namespace std;

float Plane_intersection(float face[3][3],float x,float y,float z)
{
    float A,B,C,D;
    float x1,y1,z1;
    float x2,y2,z2;
    float x3,y3,z3;
    float s;   
    
    x1=face[0][0];
    y1=face[0][1];
    z1=face[0][2];

    x2=face[1][0];
    y2=face[1][1];
    z2=face[1][2];
    
    x3=face[2][0];
    y3=face[2][1];
    z3=face[2][2];
    
    //Equation of a plane: AX+BY+CZ+D=0
    
    A=y1*(z2-z3)+y2*(z3-z1)+y3*(z1-z2);
    B=z1*(x2-x3)+z2*(x3-x1)+z3*(x1-x2);
    C=x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2);
    D=-(x1*(y2*z3-y3*z2)+x2*(y3*z1-y1*z3)+x3*(y1*z2-y2*z1));
    
    s=A*x+B*y+C*z+D;
    
    return s;
    
}
