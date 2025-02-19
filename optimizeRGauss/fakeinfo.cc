#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <complex>
#include <string>
#include <cstring>
const double PI=4.0*atan(1.0);
const double HBARC=197.3269602;

using namespace std;

int main(int argc,char *argv[]){
	unsigned int NPars,NObs;
	double ALPHA;
	unsigned int ipar,iy;
	char dummy[200];
	FILE *fptr;
	string parname, obsname;
	fptr=fopen("NParsNObs.txt","r");
	fgets(dummy,200,fptr);
	fscanf(fptr,"%d %d %lf",&NPars,&NObs,&ALPHA);
	fclose(fptr);
	
	fptr=fopen("smooth_data/Info/modelpar_info.txt","w");
	fprintf(fptr,"# par_name        dist_type    xmin    xmax  ThetaScale\n");
	for(ipar=0;ipar<NPars;ipar++){
		parname="par"+to_string(ipar);
		fprintf(fptr,"%7s gaussian 0 100  1.0\n",parname.c_str());
	}
	fclose(fptr);
	
	fptr=fopen("smooth_data/Info/observable_info.txt","w");
	for(iy=0;iy<NObs;iy++){
		obsname="obs"+to_string(iy);
		fprintf(fptr,"%7s 0.0001\n",obsname.c_str());
	}
	fclose(fptr);
	
  return 0;
}


