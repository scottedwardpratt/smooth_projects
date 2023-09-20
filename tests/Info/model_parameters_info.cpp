#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdio>
#include<vector>
using namespace std;
#include<cstdlib>
#include <fstream>





int main()
{
    string s = "linear";
    double min,max;
    FILE *fptr;
    fptr = fopen("mod_parameters_info.txt","w");

    for(int i = 1; i < 10; i ++)
    {
        min = ((double)rand()) / ((double)RAND_MAX) / 2.0;
        max = ((double)rand()) / ((double)RAND_MAX) / 2.0 + 0.5;
        fprintf(fptr,"par%d %s %10.3f %10.3f\n",i,s.c_str(),min,max);
    }
    fclose(fptr);


}
