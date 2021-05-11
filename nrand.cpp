#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include "header.h"

using namespace std;

int nrand(int n) {
	if(n<=0) {
		throw domain_error("Argument to nrand are out of the definition domain");
	}
	
	if(n<=RAND_MAX)	{
		const int bucket_size = RAND_MAX/n;
		int r;
		do r = rand() / bucket_size;
		while (r>=n);
		return r;
	}
	
	else { // n>RAND_MAX
		int r0, r1;
		const int bucket_size_0 = n/RAND_MAX;
		const int bucket_size_1 = n%RAND_MAX;
		r0 = nrand(bucket_size_0+1);
		r1 = nrand(bucket_size_1);
		return r0*RAND_MAX + r1;
	}
}
